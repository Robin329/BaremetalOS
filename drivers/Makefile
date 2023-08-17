# SPDX-License-Identifier: GPL-2.0+

obj-$(CONFIG_$(SPL_TPL_)BLK) += block/
obj-$(CONFIG_$(SPL_TPL_)CLK) += clk/
obj-$(CONFIG_$(SPL_TPL_)DM) += core/
obj-$(CONFIG_$(SPL_TPL_)DFU) += dfu/
obj-$(CONFIG_$(SPL_TPL_)EXTCON) += extcon/
obj-$(CONFIG_$(SPL_TPL_)GPIO) += gpio/
obj-$(CONFIG_$(SPL_TPL_)DRIVERS_MISC) += misc/
obj-$(CONFIG_$(SPL_TPL_)SYSRESET) += sysreset/
obj-$(CONFIG_$(SPL_TPL_)I2C) += i2c/
obj-$(CONFIG_$(SPL_TPL_)INPUT) += input/
obj-$(CONFIG_$(SPL_TPL_)LED) += led/
obj-$(CONFIG_$(SPL_TPL_)MMC) += mmc/
obj-y += mtd/
obj-$(CONFIG_$(SPL_TPL_)ETH) += net/

obj-$(CONFIG_$(SPL_TPL_)PHY) += phy/
obj-$(CONFIG_$(SPL_TPL_)PINCTRL) += pinctrl/
obj-$(CONFIG_$(SPL_TPL_)RAM) += ram/
obj-$(CONFIG_$(SPL_TPL_)SERIAL) += serial/
obj-$(CONFIG_$(SPL_TPL_)SPI) += spi/
obj-$(CONFIG_$(SPL_)DM_MAILBOX) += mailbox/

ifndef CONFIG_VPL_BUILD
ifdef CONFIG_SPL_BUILD

obj-$(CONFIG_SPL_CPU) += cpu/
obj-$(CONFIG_SPL_CRYPTO) += crypto/
obj-$(CONFIG_SPL_DM_RESET) += reset/
obj-$(CONFIG_SPL_USB_GADGET) += usb/gadget/
obj-$(CONFIG_SPL_USB_GADGET) += usb/common/
obj-$(CONFIG_SPL_USB_GADGET) += usb/gadget/udc/
obj-$(CONFIG_SPL_USB_HOST) += usb/host/
obj-$(CONFIG_SPL_LEGACY_BLOCK) += block/

endif
endif

ifeq ($(CONFIG_SPL_BUILD)$(CONFIG_TPL_BUILD),)

obj-y += adc/
obj-$(CONFIG_DM_DEMO) += demo/
obj-y += block/
obj-$(CONFIG_CPU) += cpu/
obj-y += crypto/
obj-$(CONFIG_FASTBOOT) += fastboot/
obj-y += misc/
obj-$(CONFIG_MMC) += mmc/
obj-$(CONFIG_MULTIPLEXER) += mux/
obj-y += video/
obj-y += mtd/
obj-y += pwm/
obj-y += reset/
obj-y += input/
# SOC specific infrastructure drivers.


obj-$(CONFIG_MACH_PIC32) += ddr/microchip/
obj-$(CONFIG_DM_RNG) += rng/
endif
