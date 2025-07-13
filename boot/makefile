CROSS_COMPILE:=arm-none-eabi-
CC:=$(CROSS_COMPILE)gcc
LD:=$(CROSS_COMPILE)ld
OBJCOPY:=$(CROSS_COMPILE)objcopy

CFLAGS:=-mcpu=cortex-m3 -mthumb -g -ggdb -Wall -Wno-main
LDFLAGS:=-T src/boot.ld -gc-sections -nostdlib -Map=bin/image.map

#all: bin/image.bin

bin/image.bin: int/image.elf
	$(OBJCOPY) -O binary $^ $@

int/image.elf: int/boot.o src/boot.ld
	mkdir -p bin
	$(LD) $(LDFLAGS) int/boot.o -o $@
	
int/boot.o: src/boot.c
	mkdir -p int
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf ./int ./bin
