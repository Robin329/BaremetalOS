// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2023
 * Robin, Kernel Software Engineering, jiangrenbin329@gmail.com.
 */

#include <common.h>
#include <command.h>
#include <asm/io.h>

#define WORK_LED_GPIO_BASE (void *)0xff780000
#define WORK_LED_ON	   BIT(27)
#define WORK_LED_OFF	   ~BIT(27)

#define DIY_LED_GPIO_BASE (void *)0xff720000
#define DIY_LED_ON	  BIT(13)
#define DIY_LED_OFF	  ~BIT(13)

#define YELLOW_LED_GPIO_BASE (void *)0xff720000
#define YELLOW_LED_ON	     BIT(2)
#define YELLOW_LED_OFF	     ~BIT(2)

static int green_led_start(void *base)
{
	u32 status, count = 0;

	while (count <= 10) {
		status = readl(base);
		if (count % 2) {
			status |= WORK_LED_ON;
		} else {
			status &= WORK_LED_OFF;
		}
		writel(status, base);
		printf("%#x = %#x (%s)\n", base, status,
		       status & WORK_LED_ON ? "ON" : "OFF");
		count++;
		udelay(100 * 1000);
	}
	return 0;
}

static int red_led_start(void *base)
{
	u32 status, count = 0;

	while (count <= 10) {
		status = readl(base);
		if (count % 2) {
			status |= DIY_LED_ON;
		} else {
			status &= DIY_LED_OFF;
		}
		writel(status, base);
		printf("%#x = %#x (%s)\n", base, status,
		       status & DIY_LED_ON ? "ON" : "OFF");
		count++;
		udelay(100 * 1000);
	}
	return 0;
}

static int yellow_led_start(void *base)
{
	u32 status, count = 0;

	while (count <= 10) {
		status = readl(base);
		if (count % 2) {
			status |= YELLOW_LED_ON;
		} else {
			status &= YELLOW_LED_OFF;
		}
		writel(status, base);
		printf("%#x = %#x (%s)\n", base, status,
		       status & YELLOW_LED_ON ? "ON" : "OFF");
		count++;
		udelay(100 * 1000);
	}
	return 0;
}
static int leds_init(void)
{
	return 0;
}

static int leds_test(struct cmd_tbl *cmd, int flag, int argc,
		     char *const argv[])
{
	int option;
	int ret;

	if (argc != 2)
		return CMD_RET_USAGE;

	option = dectoul(argv[1], NULL);

	leds_init();

	switch (option) {
	case 0:
		ret = green_led_start(WORK_LED_GPIO_BASE);
		break;
	case 1:
		ret = red_led_start(DIY_LED_GPIO_BASE);
		break;
	case 2:
		ret = yellow_led_start(YELLOW_LED_GPIO_BASE);
		break;
	default:
		return CMD_RET_USAGE;
	}
	printf("== Test %s!(%d) == \n", ret > 0 ? "FAIL" : "SUCCESS", ret);
	if (ret) {
		return CMD_RET_FAILURE;
	}

	return CMD_RET_SUCCESS;
}

/***************************************************/

BARE_BOOT_CMD(bare_leds, CONFIG_SYS_MAXARGS, 1, leds_test,
	      "set/get bare leds device\n",
	      " <id> :\n"
	      "  0 - work   led on/off test.\n"
	      "  1 - diy    led on/off test.\n"
	      "  2 - yellow led on/off test.");
