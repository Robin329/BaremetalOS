// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2023
 * Robin, Kernel Software Engineering, jiangrenbin329@gmail.com.
 */

/*
 * dump global data structure support
 */

#include <asm/global_data.h>
#include <command.h>
#include <common.h>

void print_gd(struct cmd_tbl *cmd, int flag, int argc, char *const argv[]) {
    printf("===== Dump gd data =====\n");
    printf("    === bd_info ===\n");
    printf("        bi_flashstart: %lu\n", gd->bd->bi_flashstart);
    printf("        bi_flashsize: %lu\n", gd->bd->bi_flashsize);
    printf("        bi_flashoffset: %lu\n", gd->bd->bi_flashoffset);
    printf("        bi_sramstart: %lu\n", gd->bd->bi_sramstart);
    printf("        bi_sramsize: %lu\n", gd->bd->bi_sramsize);
    printf("        bi_arm_freq: %lu\n", gd->bd->bi_arm_freq);
    printf("        bi_dsp_freq: %lu\n", gd->bd->bi_dsp_freq);
    printf("        bi_ddr_freq: %lu\n", gd->bd->bi_ddr_freq);
    printf("        bi_bootflags: %lu\n", gd->bd->bi_bootflags);
    printf("        bi_ip_addr:  %lu\n", gd->bd->bi_ip_addr);
    printf("        bi_ethspeed: %d\n", gd->bd->bi_ethspeed);
    printf("        bi_intfreq: %lu\n", gd->bd->bi_intfreq);
    printf("        bi_busfreq: %lu\n", gd->bd->bi_busfreq);
    printf("        bi_arch_number: %lu\n", gd->bd->bi_arch_number);
    printf("        bi_boot_params: %lu\n", gd->bd->bi_boot_params);
    printf("        bi_dram - start: %llu\n", gd->bd->bi_dram[0].start);
    printf("        bi_dram - size:  %llu\n", gd->bd->bi_dram[0].size);
    printf("    === bd_info ===\n");
    printf("      flags: %lu\n", gd->flags);
    printf("      baudrate: %lu\n", gd->baudrate);
    printf("      cpu_clk: %lu\n", gd->cpu_clk);
    printf("      bus_clk: %lu\n", gd->bus_clk);
    printf("      pci_clk: %lu\n", gd->pci_clk);
    printf("      mem_clk: %lu\n", gd->mem_clk);
#if CONFIG_IS_ENABLED(VIDEO)
    printf("      fb_base: %lu\n", gd->fb_base);
#endif
    printf("      have_console: %lu\n", gd->have_console);
    printf("      env_addr: %lu\n", gd->env_addr);
    printf("      env_valid: %lu\n", gd->env_valid);
    printf("      env_load_prio: %d\n", gd->env_load_prio);
    printf("      ram_base: %lu\n", gd->ram_base);
    printf("      ram_top: %llu\n", gd->ram_top);
    printf("      relocaddr: %lu\n", gd->relocaddr);
    printf("      ram_size: %llu\n", gd->ram_size);
    printf("      mon_len: %lu\n", gd->mon_len);
    printf("      irq_sp: %lu\n", gd->irq_sp);
    printf("      start_addr_sp: %lu\n", gd->start_addr_sp);
    printf("      reloc_off: %lu\n", gd->reloc_off);
    printf("      new_gd: %p\n", gd->new_gd);
    printf("      dm_root: %p\n", gd->dm_root);
    printf("      dm_root_f: %p\n", gd->dm_root_f);
    printf("      fdt_blob: %p\n", gd->fdt_blob);
    printf("      new_fdt: %p\n", gd->new_fdt);
    printf("      fdt_size: %lu\n", gd->fdt_size);
    printf("      fdt_src: %d\n", gd->fdt_src);
    printf("      jt: %p\n", gd->jt);
    printf("      env_buf: %s\n", gd->env_buf);
    printf("      timebase_h: %d\n", gd->timebase_h);
    printf("      timebase_l: %d\n", gd->timebase_l);
    printf("      malloc_base: %lu\n", gd->malloc_base);
    printf("      malloc_ptr: %lu\n", gd->malloc_ptr);
    printf("      malloc_limit: %lu\n", gd->malloc_limit);
    printf("      cur_serial_dev: %p\n", gd->cur_serial_dev);
    printf("    === arch global data ===\n");
    printf("        timer_rate_hz: %lu\n", gd->arch.timer_rate_hz);
    printf("        tbu: %d\n", gd->arch.tbu);
    printf("        tbl: %d\n", gd->arch.tbl);
    printf("        lastinc: %lu\n", gd->arch.lastinc);
    printf("        timer_reset_value: %llu\n", gd->arch.timer_reset_value);
#if !(CONFIG_IS_ENABLED(SYS_ICACHE_OFF) && CONFIG_IS_ENABLED(SYS_DCACHE_OFF))
    printf("        tlb_addr: %lu\n", gd->arch.tlb_addr);
    printf("        tlb_size: %lu\n", gd->arch.tlb_size);
#if defined(CONFIG_ARM64)
    printf("        tlb_fillptr: %lu\n", gd->arch.tlb_fillptr);
    printf("        tlb_emerg: %lu\n", gd->arch.tlb_emerg);
    printf("        first_block_level: %d\n", gd->arch.first_block_level);
    printf("        has_hafdbs: %d\n", gd->arch.has_hafdbs);
#endif
#endif
    printf("    === arch global data ===\n");
    printf("===== Dump gd data =====\n");
}

/***************************************************/

BARE_BOOT_CMD(dump_gd, 1, 1, print_gd, "print global data informatio\n",
              "         <num>:\n"
              "            1 - Dump all global data.\n");
