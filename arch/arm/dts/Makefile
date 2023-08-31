# SPDX-License-Identifier: GPL-2.0+

dtb-$(CONFIG_ROCKCHIP_RK3399) += \
	rk3399-roc-pc.dtb


dtb-$(CONFIG_ARCH_QEMU) += qemu-arm.dtb qemu-arm64.dtb

dtb-$(CONFIG_TARGET_CORSTONE1000) += corstone1000-mps3.dtb \
				corstone1000-fvp.dtb

include $(srctree)/scripts/Makefile.dts

targets += $(dtb-y)

# Add any required device tree compiler flags here
DTC_FLAGS += -a 0x8

PHONY += dtbs
dtbs: $(addprefix $(obj)/, $(dtb-y))
	@:

clean-files := *.dtb *.dtbo *_HS
