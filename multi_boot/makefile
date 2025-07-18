CROSS_COMPILE:=arm-none-eabi-
CC:=$(CROSS_COMPILE)gcc 
CFLAGS:=-g -ggdb -Wall -mthumb -mcpu=cortex-m3 -Wno-main -fstack-check
LD:=$(CROSS_COMPILE)ld
LDFLAGS:=-gc-sections -nostdlib
OBJCOPY:=$(CROSS_COMPILE)objcopy

all: bin/image.bin

bin/image.bin: bin/bootloader.bin bin/app.bin
	cat $^ > $@ 

bin/app.bin: int/app.elf
	$(OBJCOPY) -O binary $< $@

bin/bootloader.bin: int/bootloader.elf
	mkdir -p bin
	$(OBJCOPY) -O binary --pad-to=0x001000 --gap-fill=0xFF $< $@

int/app.elf: int/startup.o src/app.ld
	$(LD) $(LDFLAGS) $< -o $@ -T src/app.ld -Map=int/app.map

int/bootloader.elf: int/startup_bl.o int/utils.o src/bootloader.ld
	$(LD) $(LDFLAGS) int/startup_bl.o int/utils.o -o $@ -T src/bootloader.ld -Map=int/bootloader.map
int/startup_bl.o: src/startup_bl.c
	mkdir -p int
	$(CC) $(CFLAGS) -o $@ -c $<
int/utils.o: src/utils.c
	$(CC) $(CFLAGS) -o $@ -c $<
int/startup.o: src/startup.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf bin int
