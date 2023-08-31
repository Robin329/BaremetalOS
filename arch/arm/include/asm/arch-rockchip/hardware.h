/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2015 Google, Inc
 */

#ifndef _ASM_ARCH_HARDWARE_H
#define _ASM_ARCH_HARDWARE_H

#define RK_CLRSETBITS(clr, set) ((((clr) | (set)) << 16) | (set))
#define RK_SETBITS(set)		RK_CLRSETBITS(0, set)
#define RK_CLRBITS(clr)		RK_CLRSETBITS(clr, 0)
#if defined(CONFIG_BAREMETAL_REG_DEBUG)
#define rk_clrsetreg(addr, clr, set)                                           \
	do {                                                                   \
		writel(((clr) | (set)) << 16 | (set), addr);                   \
		printf("clrsetreg   %#lx = %#x\n", addr,                          \
		       ((clr) | (set)) << 16 | (set));                         \
	} while (0)
#define rk_clrreg(addr, clr)                                                   \
	do {                                                                   \
		writel((clr) << 16, addr);                                     \
		printf("clrreg      %#lx = %#x\n", addr, (clr) << 16);               \
	} while (0)
#define rk_setreg(addr, set)                                                   \
	do {                                                                   \
		writel((set) << 16 | (set), addr);                             \
		printf("setreg      %#lx = %#x\n", addr, (set) << 16 | (set));       \
	} while (0)
#else
#define rk_clrsetreg(addr, clr, set)                                           \
	do {                                                                   \
		writel(((clr) | (set)) << 16 | (set), addr);                   \
	} while (0)
#define rk_clrreg(addr, clr)                                                   \
	do {                                                                   \
		writel((clr) << 16, addr);                                     \
	} while (0)
#define rk_setreg(addr, set)                                                   \
	do {                                                                   \
		writel((set) << 16 | (set), addr);                             \
	} while (0)
#endif
#endif
