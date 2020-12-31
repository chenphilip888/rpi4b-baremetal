CROSS_COMPILE = aarch64-linux-gnu-
STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main
INCLUDE = -I.
CFLAGS  = -g -march=armv8-a -O1 -Wl,--build-id=none -nostdlib -fno-builtin $(INCLUDE)
LDSCRIPTS=-L. -T linker.ld -lgcc
LFLAGS= $(LDSCRIPTS)

test: kernel8.img

kernel8.img: test.elf
	$(CROSS_COMPILE)objcopy -O binary $< $@
	$(CROSS_COMPILE)objdump -S $< > test.list

test.elf: boot.S test.c uart.c printf.c timer.c gpio.c pwm.c i2c.c spi.c dmac.c
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ $(LFLAGS) -o $@

.PHONY: populate_boot burn_sdcard clean test

populate_boot:
	sudo dd if=./2020-12-02-raspios-buster-armhf-lite.img skip=1024 of=/dev/mmcblk0 seek=1024 bs=4096 count=65536 conv=notrunc,fsync
	sync
	sudo umount /media/${USER}/boot
	sudo umount /media/${USER}/rootfs

burn_sdcard: kernel8.img
	\rm /media/${USER}/boot/*.img
	cp kernel8.img /media/${USER}/boot
	cp cmdline.txt /media/${USER}/boot
	cp config.txt /media/${USER}/boot
	sync
	sudo umount /media/${USER}/boot
	sudo umount /media/${USER}/rootfs

clean:
	rm -f kernel8.img test.bin *.elf test.list
