# SPDX-License-Identifier: GPL-2.0+
#
# (C) Copyright 2000-2007
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.


# U-Boot build
ifeq ($(CONFIG_SPL_BUILD)$(CONFIG_TPL_BUILD),)
obj-y += spi/
#SPL/TPL build
else
obj-$(CONFIG_$(SPL_TPL_)SPI_FLASH_SUPPORT) += spi/
endif
