/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 */

#ifndef _ASM_ARMV8_MMU_H_
#define _ASM_ARMV8_MMU_H_

#include <const.h>

/*
 * block/section address mask and size definitions.
 */

/* PAGE_SHIFT determines the page size */
#undef PAGE_SIZE
#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define PAGE_MASK (~(PAGE_SIZE - 1))

/***************************************************************/

/*
 * Memory types
 */
#define MT_DEVICE_NGNRNE 0
#define MT_DEVICE_NGNRE 1
#define MT_DEVICE_GRE 2
#define MT_NORMAL_NC 3
#define MT_NORMAL 4

#define MEMORY_ATTRIBUTES                                               \
  ((0x00 << (MT_DEVICE_NGNRNE * 8)) | (0x04 << (MT_DEVICE_NGNRE * 8)) | \
   (0x0c << (MT_DEVICE_GRE * 8)) | (0x44 << (MT_NORMAL_NC * 8)) |       \
   (UL(0xff) << (MT_NORMAL * 8)))

/*
 * Hardware page table definitions.
 *
 */

#define PTE_TYPE_MASK (3 << 0)
#define PTE_TYPE_FAULT (0 << 0)
#define PTE_TYPE_TABLE (3 << 0)
#define PTE_TYPE_PAGE (3 << 0)
#define PTE_TYPE_BLOCK (1 << 0)
#define PTE_TYPE_VALID (1 << 0)

#define PTE_RDONLY BIT(7)
#define PTE_DBM BIT(51)

#define PTE_TABLE_PXN BIT(59)
#define PTE_TABLE_XN BIT(60)
#define PTE_TABLE_AP BIT(61)
#define PTE_TABLE_NS BIT(63)

/*
 * Block
 */
#define PTE_BLOCK_MEMTYPE(x) ((x) << 2)
#define PTE_BLOCK_NS (1 << 5)
#define PTE_BLOCK_NON_SHARE (0 << 8)
#define PTE_BLOCK_OUTER_SHARE (2 << 8)
#define PTE_BLOCK_INNER_SHARE (3 << 8)
#define PTE_BLOCK_AF (1 << 10)
#define PTE_BLOCK_NG (1 << 11)
#define PTE_BLOCK_PXN (UL(1) << 53)
#define PTE_BLOCK_UXN (UL(1) << 54)

/*
 * AttrIndx[2:0]
 */
#define PMD_ATTRINDX(t) ((t) << 2)
#define PMD_ATTRINDX_MASK (7 << 2)
#define PMD_ATTRMASK \
  (PTE_BLOCK_PXN | PTE_BLOCK_UXN | PMD_ATTRINDX_MASK | PTE_TYPE_VALID)

/*
 * TCR flags.
 */
#define TCR_T0SZ(x) ((64 - (x)) << 0)
#define TCR_IRGN_NC (0 << 8)
#define TCR_IRGN_WBWA (1 << 8)
#define TCR_IRGN_WT (2 << 8)
#define TCR_IRGN_WBNWA (3 << 8)
#define TCR_IRGN_MASK (3 << 8)
#define TCR_ORGN_NC (0 << 10)
#define TCR_ORGN_WBWA (1 << 10)
#define TCR_ORGN_WT (2 << 10)
#define TCR_ORGN_WBNWA (3 << 10)
#define TCR_ORGN_MASK (3 << 10)
#define TCR_SHARED_NON (0 << 12)
#define TCR_SHARED_OUTER (2 << 12)
#define TCR_SHARED_INNER (3 << 12)
#define TCR_TG0_4K (0 << 14)
#define TCR_TG0_64K (1 << 14)
#define TCR_TG0_16K (2 << 14)
#define TCR_EPD1_DISABLE (1 << 23)

#define TCR_EL1_HA BIT(39)
#define TCR_EL1_HD BIT(40)

#define TCR_EL2_HA BIT(21)
#define TCR_EL2_HD BIT(22)

#define TCR_EL3_HA BIT(21)
#define TCR_EL3_HD BIT(22)

#define TCR_EL1_RSVD (1U << 31)
#define TCR_EL2_RSVD (1U << 31 | 1 << 23)
#define TCR_EL3_RSVD (1U << 31 | 1 << 23)

#define HCR_EL2_E2H_BIT 34

#endif /* _ASM_ARMV8_MMU_H_ */
