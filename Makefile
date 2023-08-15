CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
GCCFLAGS += -Iinclude -DCONFIG_ARM64 -D__ASSEMBLY__ -DCONFIG_TEXT_BASE=0x00200000
GCCPATH = $(shell dirname $(shell whereis aarch64-linux-gnu-gcc | cut -d ' ' -f 2))
PATH=arch/arm64/roc-rk3399-pc
all: clean baremetal.img

boot.o: $(PATH)/boot.S
	$(GCCPATH)/aarch64-linux-gnu-gcc $(GCCFLAGS) -c $(PATH)/boot.S -o boot.o

%.o: %.c
	$(GCCPATH)/aarch64-linux-gnu-gcc $(GCCFLAGS) -c $< -o $@

baremetal.img: boot.o $(OFILES)
	$(GCCPATH)/aarch64-linux-gnu-ld -nostdlib boot.o $(OFILES) -T $(PATH)/baremetal.ld -o baremetal.elf
	$(GCCPATH)/aarch64-linux-gnu-objcopy -O binary baremetal.elf baremetal.img

clean:
	/bin/rm baremetal.elf *.o *.img > /dev/null 2> /dev/null || true