# XC8 executable selection (priority: XC8_CC, XC8_BIN, then PATH)
XC8_CC ?=
XC8_BIN ?=
XC8 ?= $(if $(XC8_CC),$(XC8_CC),$(if $(XC8_BIN),$(XC8_BIN)/xc8-cc,xc8-cc))

# Pack discovery (priority: MDFP, PACK_ROOT, env vars; otherwise default ~/.mchp_packs)
PACK_ROOT ?= $(if $(PIC_PACK_ROOT),$(PIC_PACK_ROOT),$(if $(MCHP_PACK_ROOT),$(MCHP_PACK_ROOT),$(HOME)/.mchp_packs/Microchip/PIC16F1xxxx_DFP))
# Use the latest installed PIC16F1xxxx DFP under PACK_ROOT unless MDFP is provided.
MDFP ?= $(lastword $(sort $(wildcard $(PACK_ROOT)/*/xc8)))
ifeq ($(MDFP),)
$(error No PIC16F1xxxx DFP found. Install one or set MDFP=/path/to/PIC16F1xxxx_DFP/<version>/xc8 or set PACK_ROOT/PIC_PACK_ROOT/MCHP_PACK_ROOT)
endif

GIT_HASH ?= $(shell git rev-parse --short=7 HEAD 2>/dev/null || echo unknown)

TARGET ?= ATU-10
OUTDIR ?= build

SRCS := main.c bb_uart.c pic_init.c oled_control.c Soft_I2C.c xc8_compat.c xc8_adc.c

CFLAGS := -mcpu=16lf18877 -mdfp=$(MDFP) -O1
CFLAGS += -mwarn=1
CFLAGS += -DGIT_HASH=\"$(GIT_HASH)\"

OBJS := $(SRCS:%.c=$(OUTDIR)/%.o)

all: $(OUTDIR)/$(TARGET).hex

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OUTDIR)/%.o: %.c | $(OUTDIR)
	$(XC8) $(CFLAGS) -c $< -o $@

$(OUTDIR)/$(TARGET).elf: $(SRCS) | $(OUTDIR)
	$(XC8) $(CFLAGS) $(SRCS) -o $@ -Wl,-Map=$(OUTDIR)/$(TARGET).map

$(OUTDIR)/$(TARGET).hex: $(OUTDIR)/$(TARGET).elf
	@true

clean:
	rm -rf $(OUTDIR)

.PHONY: all clean
