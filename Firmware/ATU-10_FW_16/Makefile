XC8 ?= /home/bgelb/.local/microchip/xc8/v3.10/bin/xc8-cc
MDFP ?= /home/bgelb/.mchp_packs/Microchip/PIC16F1xxxx_DFP/1.28.431/xc8

TARGET ?= ATU-10
OUTDIR ?= build

SRCS := main.c pic_init.c oled_control.c Soft_I2C.c xc8_compat.c xc8_adc.c

CFLAGS := -mcpu=16lf18877 -mdfp=$(MDFP) -O1
CFLAGS += -mwarn=1

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
