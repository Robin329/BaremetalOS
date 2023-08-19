// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2023
 * Robin, Kernel Software Engineering, jiangrenbin329@gmail.com.
 */

/*
 * Baremetal Hello support
 */

#include <common.h>
#include <command.h>

static int print_hello(struct cmd_tbl *cmd, int flag, int argc,
		       char *const argv[])
{
	int select;

	if (argc != 2)
		return CMD_RET_USAGE;

	select = dectoul(argv[1], NULL);

	switch (select) {
	case 1:
		printf("\n");
		printf("--------------------------\n");
		printf("|   Welcom Baremetal OS  |\n");
		printf("--------------------------\n");
		printf("\n");
		break;
	case 2:
		printf("\n");
		printf("--------------------------\n");
		printf("|   Hello Baremetal OS   |\n");
		printf("--------------------------\n");
		printf("\n");
		break;
#if defined(CONFIG_BAREMETAL_HELLO_PRINT)
	case 3:
		printf("\n");
		printf(" __                                                __             ___                     \n");
		printf("/\\ \\                                              /\\ \\__         /\\_ \\                    \n");
		printf("\\ \\ \\____     __     _ __    __    ___ ___      __\\ \\ ,_\\    __  \\//\\ \\     ___     ____  \n");
		printf(" \\ \\ '__`\\  /'__`\\  /\\`'__\\/'__`\\/' __` __`\\  /'__`\\ \\ \\/  /'__`\\  \\ \\ \\   / __`\\  /',__\\ \n");
		printf("  \\ \\ \\L\\ \\/\\ \\L\\.\\_\\ \\ \\//\\  __//\\ \\/\\ \\/\\ \\/\\  __/\\ \\ \\_/\\ \\L\\.\\_ \\_\\ \\_/\\ \\L\\ \\/\\__, `\\\n");
		printf("   \\ \\_,__/\\ \\__/.\\_\\\\ \\_\\\\ \\____\\ \\_\\ \\_\\ \\_\\ \\____\\\\ \\__\\ \\__/.\\_\\/\\____\\ \\____/\\/\\____/\n");
		printf("    \\/___/  \\/__/\\/_/ \\/_/ \\/____/\\/_/\\/_/\\/_/\\/____/ \\/__/\\/__/\\/_/\\/____/\\/___/  \\/___/ \n");
		printf("\n");
		break;
#endif
	default:
		printf("\n");
		printf("--------------------------\n");
		printf("|    Bye~ Baremetal OS   |\n");
		printf("--------------------------\n");
		printf("\n");
		break;
	}

	return CMD_RET_SUCCESS;
}

/***************************************************/

BARE_BOOT_CMD(bare_hello, 3, 1, print_hello,
	      "print bare hello device informatio\n",
	      "         <num>:\n"
	      "            1 - Welcom Baremetal OS.\n"
	      "            2 - Hello Baremetal OS.\n"
#if defined(CONFIG_BAREMETAL_HELLO_PRINT)
	      "            3 - Print BareMetal LOGO."
#endif
);
