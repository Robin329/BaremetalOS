#!/bin/bash

./rkbin/tools/loaderimage --pack --uboot u-boot-dtb.bin uboot.img
sudo rkdeveloptool db rkbin/bin/rk33/rk3399_loader_v1.12.112.bin
sleep 2
sudo rkdeveloptool wl 0x4000 uboot.img
sleep 2
sudo rkdeveloptool rd