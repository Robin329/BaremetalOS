# Baremetal OS

In order to support Arm Trust Firmware(ATF), we can use either SPL or
miniloader from rockchip to do:
* do DRAM init
* load and verify ATF image
* load and verify U-Boot image

Here is the step-by-step to boot to U-Boot on rk3399.

## Get the Source and prebuild binary

```sh
  > mkdir ~/evb_rk3399
  > cd ~/evb_rk3399
  > git clone https://github.com/ARM-software/arm-trusted-firmware.git
  > git clone https://github.com/rockchip-linux/rkbin.git
  > git clone https://github.com/rockchip-linux/rkdeveloptool.git
```
## Compile the ATF

```sh
  > cd arm-trusted-firmware
  > make realclean
  > make CROSS_COMPILE=aarch64-linux-gnu- PLAT=rk3399 bl31
```
Or you can get the bl31.elf directly from Rockchip:
```sh
  > cp rkbin/rk33/rk3399_bl31_v1.00.elf ../u-boot/bl31.elf
```
Get bl31.elf in this step, copy it to U-Boot root dir:
```sh
  > cp bl31.elf ../u-boot/
```
## Compile the U-Boot

```sh
  > cd ../u-boot
  > export ARCH=arm64
  > export CROSS_COMPILE=aarch64-linux-gnu-
  > make evb-rk3399_defconfig
  # for firefly-rk3399, use below instead:
  > make roc-pc-rk3399_defconfig
  > make
  > make u-boot.itb
```
  Get spl/u-boot-spl.bin and u-boot.itb in this step.

## Compile the rkdeveloptool
  Follow instructions in latest README
```sh
  > cd ../rkdeveloptool
  > autoreconf -i
  > ./configure
  > make
  > sudo make install
```
  Get rkdeveloptool in you Host in this step.

Both origin binaries and Tool are ready now, choose either option 1 or
option 2 to deploy U-Boot.

## Package the image

Package the image for Rockchip miniloader
------------------------------------------

```sh
  > cd ..
  > cp arm-trusted-firmware/build/rk3399/release/bl31/bl31.elf rkbin/rk33
  > ./tools/trust_merger rkbin/MKTRUST/RK3399TRUST.ini
  > ./tools/loaderimage --pack --uboot u-boot-dtb.bin uboot.img
```

  Get trust.img and uboot.img in this step.

## Flash the image to eMMC

Flash the image with Rockchip miniloader
----------------------------------------
Power on(or reset with RESET KEY) with MASKROM KEY preesed, and then:
```sh
sudo rkdeveloptool db rkbin/bin/rk33/rk3399_loader_v1.12.112.bin
sudo rkdeveloptool ul rkbin/bin/rk33/rk3399_loader_v1.12.112.bin
sudo rkdeveloptool wl 0x4000 uboot.img
sudo rkdeveloptool wl 0x6000 rkbin/img/trust.img
sudo rkdeveloptool rd
```
