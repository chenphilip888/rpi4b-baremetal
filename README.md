Bare metal experiments on the Raspberry PI 4B board.
Purpose: To initialize ddr, load test code from sd card to ddr and run test code from ddr.

Cross compiler used : aarch64-linux-gnu-
The following 10 tests are included: ( see below for tests summary )
1. uart test
2. led test
3. button test
4. pwm led test
5. i2c lcd test
6. tongsong
7. servo
8. spi oled test
9. ddr test
a. dmac test

-------------------------------------------------------------------
To compile and flash to sd card:
Download Lite OS
cd rpi4b-baremetal
wget https://downloads.raspberrypi.org/raspios_lite_armhf/images/raspios_lite_armhf-2020-12-04/2020-12-02-raspios-buster-armhf-lite.zip
unzip 2020-12-02-raspios-buster-armhf-lite.zip
sudo fdisk -l 2020-12-02-raspios-buster-armhf-lite.img
plugin a formated sd card to PC ( see below to format sd card )
Do following 2 steps only once to populate boot dir from Lite OS to sd card.
  1. make populate_boot
  2. eject sd card.
plugin sd card to PC.
make clean
make test
make burn_sdcard
plugin the sd card to Raspberry PI 4B board.
Connect Raspberry PI 4B board gpio Pin 10 to serial USB cable RX.
Connect Raspberry PI 4B board gpio pin 8 to serial USB cable TX. 
Connect Raspberry PI 4B board gpio pin 39 to serial USB cable ground. 
Type "script ~/outputfile.txt" on PC.
Plugin serial USB cable to PC.
Type "sudo screen /dev/ttyUSB0 115200" on PC.
Power on the Raspberry PI 4B board.
It should display the test menu with 10 test items on PC.
After tests done, hit q to exit tests.
Power off the Raspberry PI 4B board.
Unplug serial USB cable from PC.
Type "exit" on PC.

-------------------------------------------------------------------------
To format sd card using PC:
plugin sd card to PC.
sudo dd if=/dev/zero of=/dev/mmcblk0 bs=1M count=1024 conv=notrunc,fsync
sudo fdisk /dev/mmcblk0 <<EOF
o
n
p
1
8192
532479
n
p
2
532480

t
1
c
t
2
83
a
1
w
q
EOF
sync
eject sd card.
Plugin sd card to PC.
sudo fdisk -l /dev/mmcblk0
sudo mkfs.vfat -n boot /dev/mmcblk0p1
sudo mkfs.ext4 -L rootfs /dev/mmcblk0p2
sync
eject sd card.

-----------------------------------------------------------------------
Here are the summary of the tests: ( see GPIO-Pinout-rpi4b.png )
These tests used Seeed Grove starter kit LED, button, buzzer, Grove-LCD RGB Backlight V3.0 JHD1313M2, Analog Servo and Adafruit SSD1306 128x32 SPI OLED Display.
1. uart test. 
   This test is to test uart tx and rx.
   Connect gpio pin 10 to serial USB cable RX.
   Connect gpio pin 8 to serial USB cable TX.
   Connect gpio pin 39 to serial USB cable ground.
   Enter a sentence and hit return key. 
2. led test.
   This test will blink led 5 times. 
   Connect gpio pin 16 to led control. 
   Connect gpio pin 2 to led 5V. 
   Connect gpio pin 9 to led ground.
3. button test. 
   Connect gpio pin 16 to led control. 
   Connect gpio pin 2 to led 5V. 
   Connect gpio pin 9 to led ground. 
   Connect gpio pin 23 to button control.
   Connect gpio pin 4 to button 5V.
   Connect gpio pin 6 to button ground.
4. pwm led test.
   This test will dim led 10 times.
   Connect gpio pin 33 to led control.
   Connect gpio pin 2 to led 5V.
   Connect gpio pin 9 to led ground.
5. i2c lcd test.
   This test will change lcd backlight color for 5 cycles.
   Then it will display two sentences on lcd display.
   Connect gpio pin 3 to lcd display SDA.
   Connect gpio pin 5 to lcd display SCL.
   Connect gpio pin 2 to lcd display 5V.
   Connect gpio pin 9 to lcd display ground.
6. tongsong.
   This test will generate song using buzzer.
   Connect gpio pin 33 to buzzer control.
   Connect gpio pin 2 to buzzer 5V.
   Connect gpio pin 9 to buzzer ground. 
7. servo.
   This test will turn servo 90 degree - 180 degree - 90 degree - 0 degree etc.
   Connect gpio pin 33 to servo control.
   Connect gpio pin 2 to servo 5V.
   Connect gpio pin 9 to servo ground.
8. spi oled test.
   This test will show some ascii characters on the oled display.
   Connect gpio pin 16 to oled display DC.
   Connect gpio pin 24 to oled display CS.
   Connect gpio pin 19 to oled display TX.
   Connect gpio pin 23 to oled display CLK.
   Connect gpio pin 1 to oled display 3.3V.
   Connect gpio pin 9 to oled display ground.
9. ddr test.
   This test will write random data to ddr address from 0x10000000 to 0x1fffffff
   Then read ddr address from 0x10000000 to 0x1fffffff compare to expected data.
   It will stop when any data mismatch.
a. dmac test.
   This test will dma from ddr address 0x10000000 to ddr address 0x20000000 for 16 KB.
   Then dma from ddr address 0x20000000 to ddr address 0x30000000 for 16 KB.

-----------------------------------------------------------------------------
Download compiler from :
wget https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-linux-gnu/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz
sudo tar xvf gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz  -C /usr/local/
export PATH=/usr/local/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin:$PATH
which aarch64-linux-gnu-gcc
