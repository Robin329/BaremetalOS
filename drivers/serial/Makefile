# SPDX-License-Identifier: GPL-2.0+
#
# (C) Copyright 2006-2009
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.

ifeq ($(CONFIG_$(SPL_TPL_)DM_SERIAL),y)
obj-y += serial-uclass.o
else
obj-y += serial.o
endif

obj-$(CONFIG_$(SPL_)SYS_NS16550_SERIAL) += serial_ns16550.o
obj-$(CONFIG_SYS_NS16550) += ns16550.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_USB_TTY) += usbtty.o
endif
