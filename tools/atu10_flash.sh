#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage:
  tools/atu10_flash.sh [--uart|--no-uart] [--volume NAME] [--baud N] [--remount] [--no-eject]

Builds ATU-10 firmware and copies `Firmware/ATU-10_FW_16/build/ATU-10.hex`
to the ATU-10 USB mass-storage volume (PIC16F1454 programmer).

Options:
  --uart, --no-uart   Build with UART_CONSOLE=1 (default: --no-uart)
  --volume NAME       Volume name under /Volumes (default: auto-detect)
  --baud N            (Optional) Print suggested screen command (default: 115200)
  --remount           Attempt to remount the device after eject (may not work if the programmer disconnects)
  --no-eject          Do not eject/unmount after copying

Examples:
  tools/atu10_flash.sh --uart --volume ATU10
  tools/atu10_flash.sh --no-uart
EOF
}

uart=0
volume=""
baud="115200"
do_eject=1
do_remount=0

while [[ $# -gt 0 ]]; do
  case "$1" in
    --uart) uart=1; shift ;;
    --no-uart) uart=0; shift ;;
    --volume) volume="${2:-}"; shift 2 ;;
    --baud) baud="${2:-}"; shift 2 ;;
    --remount) do_remount=1; shift ;;
    --no-eject) do_eject=0; shift ;;
    -h|--help) usage; exit 0 ;;
    *) echo "Unknown arg: $1" >&2; usage; exit 2 ;;
  esac
done

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
fw_dir="$repo_root/Firmware/ATU-10_FW_16"
hex_path="$fw_dir/build/ATU-10.hex"

echo "[1/3] Building firmware (UART_CONSOLE=$uart)…"
pushd "$fw_dir" >/dev/null
make clean
if [[ "$uart" -eq 1 ]]; then
  make UART_CONSOLE=1
else
  make
fi
popd >/dev/null

if [[ ! -f "$hex_path" ]]; then
  echo "Missing hex: $hex_path" >&2
  exit 1
fi

detect_volume() {
  # Heuristic: ATU-10 typically enumerates as a writable volume under /Volumes.
  # Prefer volumes containing "ATU" (case-insensitive); otherwise, show a list.
  local candidates=()
  local filter_cmd=(cat)
  if command -v rg >/dev/null 2>&1; then
    filter_cmd=(rg -i 'atu|tuner|pic|boot|mass')
  else
    filter_cmd=(grep -Ei 'atu|tuner|pic|boot|mass')
  fi
  while IFS= read -r v; do
    candidates+=("$v")
  done < <(ls -1 /Volumes 2>/dev/null | "${filter_cmd[@]}" || true)

  if [[ "${#candidates[@]}" -eq 1 ]]; then
    echo "${candidates[0]}"
    return 0
  fi

  echo ""  # empty => caller will error w/ guidance
  return 0
}

if [[ -z "$volume" ]]; then
  volume="$(detect_volume)"
fi

if [[ -z "$volume" ]]; then
  echo "Could not auto-detect the ATU-10 volume." >&2
  echo "Connected volumes under /Volumes:" >&2
  ls -1 /Volumes >&2 || true
  echo "Re-run with: tools/atu10_flash.sh --volume <NAME>" >&2
  exit 1
fi

mount_point="/Volumes/$volume"
if [[ ! -d "$mount_point" ]]; then
  echo "Volume not mounted: $mount_point" >&2
  echo "Connected volumes under /Volumes:" >&2
  ls -1 /Volumes >&2 || true
  exit 1
fi

disk_id="$(diskutil info "$mount_point" 2>/dev/null | awk -F': ' '/Device Identifier/ {print $2; exit}')"
parent_disk="${disk_id%%s*}"

echo "[2/3] Copying $(basename "$hex_path") -> $mount_point …"
cp -f "$hex_path" "$mount_point/ATU-10.hex"
sync || true

if [[ "$do_eject" -eq 1 ]]; then
  echo "[3/3] Ejecting $mount_point …"
  diskutil eject "$mount_point" >/dev/null || true
else
  echo "[3/3] Skipping eject (per --no-eject)"
fi

if [[ "$do_eject" -eq 1 && "$do_remount" -eq 1 && -n "$parent_disk" ]]; then
  echo "Attempting remount of /dev/$parent_disk …"
  for _ in {1..20}; do
    if diskutil mountDisk "$parent_disk" >/dev/null 2>&1; then
      break
    fi
    sleep 0.5
  done
fi

cat <<EOF
Done.

If the ATU-10 still requires a physical replug to reboot into the new firmware,
you'll still need to unplug/replug the USB-C cable (macOS can't reliably power-cycle
a USB port purely in software without a controllable hub).

Suggested serial command:
  sudo screen /dev/cu.usbserial-* $baud
EOF
