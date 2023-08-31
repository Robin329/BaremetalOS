#!/bin/bash

sudo ./rkbin/tools/x86/loaderimage --pack --uboot u-boot.bin uboot.img
sleep 2
sudo rkdeveloptool db rkbin/bin/rk33/rk3399_loader_v1.12.112.bin
sleep 2
sudo rkdeveloptool wl 0x4000 uboot.img
sleep 2
sudo rkdeveloptool rd