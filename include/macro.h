#ifndef __ASM_ARM_MACRO_H__
#define __ASM_ARM_MACRO_H__

#ifdef CONFIG_ARM64

/*
 * SCTLR_EL1/SCTLR_EL2/SCTLR_EL3 bits definitions
 */
#define CR_M (1 << 0)    /* MMU enable			*/
#define CR_A (1 << 1)    /* Alignment abort enable	*/
#define CR_C (1 << 2)    /* Dcache enable		*/
#define CR_SA (1 << 3)   /* Stack Alignment Check Enable	*/
#define CR_I (1 << 12)   /* Icache enable		*/
#define CR_WXN (1 << 19) /* Write Permision Imply XN	*/
#define CR_EE (1 << 25)  /* Exception (Big) Endian	*/

#define ES_TO_AARCH64 1
#define ES_TO_AARCH32 0

/*
 * SCR_EL3 bits definitions
 */
#define SCR_EL3_RW_AARCH64 (1 << 10) /* Next lower level is AArch64     */
#define SCR_EL3_RW_AARCH32 (0 << 10) /* Lower lowers level are AArch32  */
#define SCR_EL3_HCE_EN (1 << 8)      /* Hypervisor Call enable          */
#define SCR_EL3_SMD_DIS (1 << 7)     /* Secure Monitor Call disable     */
#define SCR_EL3_RES1 (3 << 4)        /* Reserved, RES1                  */
#define SCR_EL3_EA_EN (1 << 3)       /* External aborts taken to EL3    */
#define SCR_EL3_NS_EN (1 << 0)       /* EL0 and EL1 in Non-scure state  */

/*
 * SPSR_EL3/SPSR_EL2 bits definitions
 */
#define SPSR_EL_END_LE (0 << 9)     /* Exception Little-endian          */
#define SPSR_EL_DEBUG_MASK (1 << 9) /* Debug exception masked           */
#define SPSR_EL_ASYN_MASK (1 << 8)  /* Asynchronous data abort masked   */
#define SPSR_EL_SERR_MASK (1 << 8)  /* System Error exception masked    */
#define SPSR_EL_IRQ_MASK (1 << 7)   /* IRQ exception masked             */
#define SPSR_EL_FIQ_MASK (1 << 6)   /* FIQ exception masked             */
#define SPSR_EL_T_A32 (0 << 5)      /* AArch32 instruction set A32      */
#define SPSR_EL_M_AARCH64 (0 << 4)  /* Exception taken from AArch64     */
#define SPSR_EL_M_AARCH32 (1 << 4)  /* Exception taken from AArch32     */
#define SPSR_EL_M_SVC (0x3)         /* Exception taken from SVC mode    */
#define SPSR_EL_M_HYP (0xa)         /* Exception taken from HYP mode    */
#define SPSR_EL_M_EL1H (5)          /* Exception taken from EL1h mode   */
#define SPSR_EL_M_EL2H (9)          /* Exception taken from EL2h mode   */

/*
 * CPTR_EL2 bits definitions
 */
#define CPTR_EL2_RES1 (3 << 12 | 0x3ff) /* Reserved, RES1 */

/*
 * SCTLR_EL2 bits definitions
 */
#define SCTLR_EL2_RES1                               \
  (3 << 28 | 3 << 22 | 1 << 18 | 1 << 16 | 1 << 11 | \
   3 << 4)                             /* Reserved, RES1 */
#define SCTLR_EL2_EE_LE (0 << 25)      /* Exception Little-endian          */
#define SCTLR_EL2_WXN_DIS (0 << 19)    /* Write permission is not XN       */
#define SCTLR_EL2_ICACHE_DIS (0 << 12) /* Instruction cache disabled       */
#define SCTLR_EL2_SA_DIS (0 << 3)      /* Stack Alignment Check disabled   */
#define SCTLR_EL2_DCACHE_DIS (0 << 2)  /* Data cache disabled              */
#define SCTLR_EL2_ALIGN_DIS (0 << 1)   /* Alignment check disabled         */
#define SCTLR_EL2_MMU_DIS (0)          /* MMU disabled                     */

/*
 * CNTHCTL_EL2 bits definitions
 */
#define CNTHCTL_EL2_EL1PCEN_EN (1 << 1)  /* Physical timer regs accessible   */
#define CNTHCTL_EL2_EL1PCTEN_EN (1 << 0) /* Physical counter accessible */

/*
 * HCR_EL2 bits definitions
 */
#define HCR_EL2_API                        \
  (1 << 41) /* Trap pointer authentication \
               instructions                     */
#define HCR_EL2_APK                                                 \
  (1 << 40)                          /* Trap pointer authentication \
                                        key access                       */
#define HCR_EL2_RW_AARCH64 (1 << 31) /* EL1 is AArch64                   */
#define HCR_EL2_RW_AARCH32 (0 << 31) /* Lower levels are AArch32         */
#define HCR_EL2_HCD_DIS (1 << 29)    /* Hypervisor Call disabled         */
#define HCR_EL2_AMO_EL2 (1 << 5)     /* Route SErrors to EL2             */

/*
 * ID_AA64ISAR1_EL1 bits definitions
 */
#define ID_AA64ISAR1_EL1_GPI                    \
  (0xF << 28) /* Implementation-defined generic \
                 code auth algorithm            */
#define ID_AA64ISAR1_EL1_GPA             \
  (0xF << 24) /* QARMA generic code auth \
                 algorithm                      */
#define ID_AA64ISAR1_EL1_API                                              \
  (0xF << 8)                            /* Implementation-defined address \
                                           auth algorithm                 */
#define ID_AA64ISAR1_EL1_APA (0xF << 4) /* QARMA address auth algorithm   */

/*
 * ID_AA64PFR0_EL1 bits definitions
 */
#define ID_AA64PFR0_EL1_EL3 (0xF << 12) /* EL3 implemented                */
#define ID_AA64PFR0_EL1_EL2 (0xF << 8)  /* EL2 implemented                */

/*
 * CPACR_EL1 bits definitions
 */
#define CPACR_EL1_FPEN_EN (3 << 20) /* SIMD and FP instruction enabled  */

/*
 * SCTLR_EL1 bits definitions
 */
#define SCTLR_EL1_RES1 \
  (3 << 28 | 3 << 22 | 1 << 20 | 1 << 11) /* Reserved, RES1 */
#define SCTLR_EL1_UCI_DIS (0 << 26)       /* Cache instruction disabled       */
#define SCTLR_EL1_EE_LE (0 << 25)         /* Exception Little-endian          */
#define SCTLR_EL1_WXN_DIS (0 << 19)       /* Write permission is not XN       */
#define SCTLR_EL1_NTWE_DIS (0 << 18)      /* WFE instruction disabled         */
#define SCTLR_EL1_NTWI_DIS (0 << 16)      /* WFI instruction disabled         */
#define SCTLR_EL1_UCT_DIS (0 << 15)       /* CTR_EL0 access disabled          */
#define SCTLR_EL1_DZE_DIS (0 << 14)       /* DC ZVA instruction disabled      */
#define SCTLR_EL1_ICACHE_DIS (0 << 12)    /* Instruction cache disabled       */
#define SCTLR_EL1_UMA_DIS (0 << 9)        /* User Mask Access disabled        */
#define SCTLR_EL1_SED_EN (0 << 8)         /* SETEND instruction enabled       */
#define SCTLR_EL1_ITD_EN (0 << 7)         /* IT instruction enabled           */
#define SCTLR_EL1_CP15BEN_DIS (0 << 5)    /* CP15 barrier operation disabled  */
#define SCTLR_EL1_SA0_DIS (0 << 4)        /* Stack Alignment EL0 disabled     */
#define SCTLR_EL1_SA_DIS (0 << 3)         /* Stack Alignment EL1 disabled     */
#define SCTLR_EL1_DCACHE_DIS (0 << 2)     /* Data cache disabled              */
#define SCTLR_EL1_ALIGN_DIS (0 << 1)      /* Alignment check disabled         */
#define SCTLR_EL1_MMU_DIS (0)             /* MMU disabled                     */

#endif /* CONFIG_ARM64 */

#ifdef __ASSEMBLY__

/*
 * These macros provide a convenient way to write 8, 16 and 32 bit data
 * to any address.
 * Registers r4 and r5 are used, any data in these registers are
 * overwritten by the macros.
 * The macros are valid for any ARM architecture, they do not implement
 * any memory barriers so caution is recommended when using these when the
 * caches are enabled or on a multi-core system.
 */

.macro	write32, addr, data
	ldr	r4, =\addr
	ldr	r5, =\data
	str	r5, [r4]
.endm

.macro	write16, addr, data
	ldr	r4, =\addr
	ldrh	r5, =\data
	strh	r5, [r4]
.endm

.macro	write8, addr, data
	ldr	r4, =\addr
	ldrb	r5, =\data
	strb	r5, [r4]
.endm

/*
 * This macro generates a loop that can be used for delays in the code.
 * Register r4 is used, any data in this register is overwritten by the
 * macro.
 * The macro is valid for any ARM architeture. The actual time spent in the
 * loop will vary from CPU to CPU though.
 */

.macro	wait_timer, time
	ldr	r4, =\time
1:
	nop
	subs	r4, r4, #1
	bcs	1b
.endm

#ifdef CONFIG_ARM64
/*
 * Register aliases.
 */
lr	.req	x30

/*
 * Branch according to exception level
 */
.macro	switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, #0x8
	b.gt	\el3_label
	b.eq	\el2_label
	b.lt	\el1_label
.endm

/*
 * Branch if we are not in the highest exception level
 */
.macro	branch_if_not_highest_el, xreg, label
	switch_el \xreg, 3f, 2f, 1f

2:	mrs	\xreg, ID_AA64PFR0_EL1
	and	\xreg, \xreg, #(ID_AA64PFR0_EL1_EL3)
	cbnz	\xreg, \label
	b	3f

1:	mrs	\xreg, ID_AA64PFR0_EL1
	and	\xreg, \xreg, #(ID_AA64PFR0_EL1_EL3 | ID_AA64PFR0_EL1_EL2)
	cbnz	\xreg, \label

3:
.endm

/*
 * Branch if current processor is a Cortex-A57 core.
 */
.macro	branch_if_a57_core, xreg, a57_label
	mrs	\xreg, midr_el1
	lsr	\xreg, \xreg, #4
	and	\xreg, \xreg, #0x00000FFF
	cmp	\xreg, #0xD07		/* Cortex-A57 MPCore processor. */
	b.eq	\a57_label
.endm

/*
 * Branch if current processor is a Cortex-A53 core.
 */
.macro	branch_if_a53_core, xreg, a53_label
	mrs	\xreg, midr_el1
	lsr	\xreg, \xreg, #4
	and	\xreg, \xreg, #0x00000FFF
	cmp	\xreg, #0xD03		/* Cortex-A53 MPCore processor. */
	b.eq	\a53_label
.endm

/*
 * Branch if current processor is a slave,
 * choose processor with all zero affinity value as the master.
 */
.macro	branch_if_slave, xreg, slave_label
#ifdef CONFIG_ARMV8_MULTIENTRY
	mrs	\xreg, mpidr_el1
	and	\xreg, \xreg,  0xffffffffff	/* clear bits [63:40] */
	and	\xreg, \xreg, ~0x00ff000000	/* also clear bits [31:24] */
	cbnz	\xreg, \slave_label
#endif
.endm

/*
 * Branch if current processor is a master,
 * choose processor with all zero affinity value as the master.
 */
.macro	branch_if_master, xreg, master_label
#ifdef CONFIG_ARMV8_MULTIENTRY
	mrs	\xreg, mpidr_el1
	and	\xreg, \xreg,  0xffffffffff	/* clear bits [63:40] */
	and	\xreg, \xreg, ~0x00ff000000	/* also clear bits [31:24] */
	cbz	\xreg, \master_label
#else
	b	\master_label
#endif
.endm

/*
 * Switch from EL3 to EL2 for ARMv8
 * @ep:     kernel entry point
 * @flag:   The execution state flag for lower exception
 *          level, ES_TO_AARCH64 or ES_TO_AARCH32
 * @tmp:    temporary register
 *
 * For loading 32-bit OS, x1 is machine nr and x2 is ftaddr.
 * For loading 64-bit OS, x0 is physical address to the FDT blob.
 * They will be passed to the guest.
 */
.macro armv8_switch_to_el2_m, ep, flag, tmp
	msr	cptr_el3, xzr		/* Disable coprocessor traps to EL3 */
	mov	\tmp, #CPTR_EL2_RES1
	msr	cptr_el2, \tmp		/* Disable coprocessor traps to EL2 */

	/* Initialize Generic Timers */
	msr	cntvoff_el2, xzr

	/* Initialize SCTLR_EL2
	 *
	 * setting RES1 bits (29,28,23,22,18,16,11,5,4) to 1
	 * and RES0 bits (31,30,27,26,24,21,20,17,15-13,10-6) +
	 * EE,WXN,I,SA,C,A,M to 0
	 */
	ldr	\tmp, =(SCTLR_EL2_RES1 | SCTLR_EL2_EE_LE |\
			SCTLR_EL2_WXN_DIS | SCTLR_EL2_ICACHE_DIS |\
			SCTLR_EL2_SA_DIS | SCTLR_EL2_DCACHE_DIS |\
			SCTLR_EL2_ALIGN_DIS | SCTLR_EL2_MMU_DIS)
	msr	sctlr_el2, \tmp

	mov	\tmp, sp
	msr	sp_el2, \tmp		/* Migrate SP */
	mrs	\tmp, vbar_el3
	msr	vbar_el2, \tmp		/* Migrate VBAR */

	/* Check switch to AArch64 EL2 or AArch32 Hypervisor mode */
	cmp	\flag, #ES_TO_AARCH32
	b.eq	1f

/*
 * The next lower exception level is AArch64, 64bit EL2 | HCE |
 * RES1 (Bits[5:4]) | Non-secure EL0/EL1.
 * and the SMD depends on requirements.
 */
#ifdef CONFIG_ARMV8_PSCI
	ldr	\tmp, =(SCR_EL3_RW_AARCH64 | SCR_EL3_HCE_EN |\
			SCR_EL3_RES1 | SCR_EL3_NS_EN)
#else
	ldr	\tmp, =(SCR_EL3_RW_AARCH64 | SCR_EL3_HCE_EN |\
			SCR_EL3_SMD_DIS | SCR_EL3_RES1 |\
			SCR_EL3_NS_EN)
#endif

#ifdef CONFIG_ARMV8_EA_EL3_FIRST
	orr	\tmp, \tmp, #SCR_EL3_EA_EN
#endif
	msr	scr_el3, \tmp

	/* Return to the EL2_SP2 mode from EL3 */
	ldr	\tmp, =(SPSR_EL_DEBUG_MASK | SPSR_EL_SERR_MASK |\
			SPSR_EL_IRQ_MASK | SPSR_EL_FIQ_MASK |\
			SPSR_EL_M_AARCH64 | SPSR_EL_M_EL2H)
	msr	spsr_el3, \tmp
	msr	elr_el3, \ep
	eret

1:
	/*
	 * The next lower exception level is AArch32, 32bit EL2 | HCE |
	 * SMD | RES1 (Bits[5:4]) | Non-secure EL0/EL1.
	 */
	ldr	\tmp, =(SCR_EL3_RW_AARCH32 | SCR_EL3_HCE_EN |\
			SCR_EL3_SMD_DIS | SCR_EL3_RES1 |\
			SCR_EL3_NS_EN)
	msr	scr_el3, \tmp

	/* Return to AArch32 Hypervisor mode */
	ldr     \tmp, =(SPSR_EL_END_LE | SPSR_EL_ASYN_MASK |\
			SPSR_EL_IRQ_MASK | SPSR_EL_FIQ_MASK |\
			SPSR_EL_T_A32 | SPSR_EL_M_AARCH32 |\
			SPSR_EL_M_HYP)
	msr	spsr_el3, \tmp
	msr     elr_el3, \ep
	eret
.endm

/*
 * Switch from EL2 to EL1 for ARMv8
 * @ep:     kernel entry point
 * @flag:   The execution state flag for lower exception
 *          level, ES_TO_AARCH64 or ES_TO_AARCH32
 * @tmp:    temporary register
 *
 * For loading 32-bit OS, x1 is machine nr and x2 is ftaddr.
 * For loading 64-bit OS, x0 is physical address to the FDT blob.
 * They will be passed to the guest.
 */
.macro armv8_switch_to_el1_m, ep, flag, tmp, tmp2
	/* Initialize Generic Timers */
	mrs	\tmp, cnthctl_el2
	/* Enable EL1 access to timers */
	orr	\tmp, \tmp, #(CNTHCTL_EL2_EL1PCEN_EN |\
		CNTHCTL_EL2_EL1PCTEN_EN)
	msr	cnthctl_el2, \tmp
	msr	cntvoff_el2, xzr

	/* Initilize MPID/MPIDR registers */
	mrs	\tmp, midr_el1
	msr	vpidr_el2, \tmp
	mrs	\tmp, mpidr_el1
	msr	vmpidr_el2, \tmp

	/* Disable coprocessor traps */
	mov	\tmp, #CPTR_EL2_RES1
	msr	cptr_el2, \tmp		/* Disable coprocessor traps to EL2 */
	msr	hstr_el2, xzr		/* Disable coprocessor traps to EL2 */
	mov	\tmp, #CPACR_EL1_FPEN_EN
	msr	cpacr_el1, \tmp		/* Enable FP/SIMD at EL1 */

	/* SCTLR_EL1 initialization
	 *
	 * setting RES1 bits (29,28,23,22,20,11) to 1
	 * and RES0 bits (31,30,27,21,17,13,10,6) +
	 * UCI,EE,EOE,WXN,nTWE,nTWI,UCT,DZE,I,UMA,SED,ITD,
	 * CP15BEN,SA0,SA,C,A,M to 0
	 */
	ldr	\tmp, =(SCTLR_EL1_RES1 | SCTLR_EL1_UCI_DIS |\
			SCTLR_EL1_EE_LE | SCTLR_EL1_WXN_DIS |\
			SCTLR_EL1_NTWE_DIS | SCTLR_EL1_NTWI_DIS |\
			SCTLR_EL1_UCT_DIS | SCTLR_EL1_DZE_DIS |\
			SCTLR_EL1_ICACHE_DIS | SCTLR_EL1_UMA_DIS |\
			SCTLR_EL1_SED_EN | SCTLR_EL1_ITD_EN |\
			SCTLR_EL1_CP15BEN_DIS | SCTLR_EL1_SA0_DIS |\
			SCTLR_EL1_SA_DIS | SCTLR_EL1_DCACHE_DIS |\
			SCTLR_EL1_ALIGN_DIS | SCTLR_EL1_MMU_DIS)
	msr	sctlr_el1, \tmp

	mov	\tmp, sp
	msr	sp_el1, \tmp		/* Migrate SP */
	mrs	\tmp, vbar_el2
	msr	vbar_el1, \tmp		/* Migrate VBAR */

	/* Check switch to AArch64 EL1 or AArch32 Supervisor mode */
	cmp	\flag, #ES_TO_AARCH32
	b.eq	1f

	/* Initialize HCR_EL2 */
	/* Only disable PAuth traps if PAuth is supported */
	mrs	\tmp, id_aa64isar1_el1
	ldr	\tmp2, =(ID_AA64ISAR1_EL1_GPI | ID_AA64ISAR1_EL1_GPA | \
		      ID_AA64ISAR1_EL1_API | ID_AA64ISAR1_EL1_APA)
	tst	\tmp, \tmp2
	mov	\tmp2, #(HCR_EL2_RW_AARCH64 | HCR_EL2_HCD_DIS)
	orr	\tmp, \tmp2, #(HCR_EL2_APK | HCR_EL2_API)
	csel	\tmp, \tmp2, \tmp, eq
	msr	hcr_el2, \tmp

	/* Return to the EL1_SP1 mode from EL2 */
	ldr	\tmp, =(SPSR_EL_DEBUG_MASK | SPSR_EL_SERR_MASK |\
			SPSR_EL_IRQ_MASK | SPSR_EL_FIQ_MASK |\
			SPSR_EL_M_AARCH64 | SPSR_EL_M_EL1H)
	msr	spsr_el2, \tmp
	msr     elr_el2, \ep
	eret

1:
	/* Initialize HCR_EL2 */
	ldr	\tmp, =(HCR_EL2_RW_AARCH32 | HCR_EL2_HCD_DIS)
	msr	hcr_el2, \tmp

	/* Return to AArch32 Supervisor mode from EL2 */
	ldr	\tmp, =(SPSR_EL_END_LE | SPSR_EL_ASYN_MASK |\
			SPSR_EL_IRQ_MASK | SPSR_EL_FIQ_MASK |\
			SPSR_EL_T_A32 | SPSR_EL_M_AARCH32 |\
			SPSR_EL_M_SVC)
	msr     spsr_el2, \tmp
	msr     elr_el2, \ep
	eret
.endm

#if defined(CONFIG_GICV3)
.macro gic_wait_for_interrupt_m xreg1
0 :	wfi
	mrs     \xreg1, ICC_IAR1_EL1
	msr     ICC_EOIR1_EL1, \xreg1
	cbnz    \xreg1, 0b
.endm
#elif defined(CONFIG_GICV2)
.macro gic_wait_for_interrupt_m xreg1, wreg2
0 :	wfi
	ldr     \wreg2, [\xreg1, GICC_AIAR]
	str     \wreg2, [\xreg1, GICC_AEOIR]
	and	\wreg2, \wreg2, #0x3ff
	cbnz    \wreg2, 0b
.endm
#endif

#endif /* CONFIG_ARM64 */

#endif /* __ASSEMBLY__ */
#endif /* __ASM_ARM_MACRO_H__ */