// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2001
 * Denis Peter, MPL AG Switzerland
 *
 * Adapted for U-Boot driver model
 * (C) Copyright 2015 Google, Inc
 *
 * Most of this source has been derived from the Linux USB
 * project.
 */

#include <common.h>
#include <blk.h>
#include <bootstage.h>
#include <command.h>
#include <console.h>
#include <dm.h>
#include <dm/uclass-internal.h>
#include <memalign.h>
#include <asm/byteorder.h>
#include <asm/unaligned.h>
#include <part.h>
#include <usb.h>

#ifdef CONFIG_USB_STORAGE
static int usb_stor_curr_dev = -1; /* current device */
#endif
#if defined(CONFIG_USB_HOST_ETHER) && !defined(CONFIG_DM_ETH)
static int __maybe_unused usb_ether_curr_dev = -1; /* current ethernet device */
#endif

/* some display routines (info command) */
static char *usb_get_class_desc(unsigned char dclass)
{
	switch (dclass) {
	case USB_CLASS_PER_INTERFACE:
		return "See Interface";
	case USB_CLASS_AUDIO:
		return "Audio";
	case USB_CLASS_COMM:
		return "Communication";
	case USB_CLASS_HID:
		return "Human Interface";
	case USB_CLASS_PRINTER:
		return "Printer";
	case USB_CLASS_MASS_STORAGE:
		return "Mass Storage";
	case USB_CLASS_HUB:
		return "Hub";
	case USB_CLASS_DATA:
		return "CDC Data";
	case USB_CLASS_VENDOR_SPEC:
		return "Vendor specific";
	default:
		return "";
	}
}

static void usb_display_class_sub(unsigned char dclass, unsigned char subclass,
				  unsigned char proto)
{
	switch (dclass) {
	case USB_CLASS_PER_INTERFACE:
		blog_info("See Interface");
		break;
	case USB_CLASS_HID:
		blog_info("Human Interface, Subclass: ");
		switch (subclass) {
		case USB_SUB_HID_NONE:
			blog_info("None");
			break;
		case USB_SUB_HID_BOOT:
			blog_info("Boot ");
			switch (proto) {
			case USB_PROT_HID_NONE:
				blog_info("None");
				break;
			case USB_PROT_HID_KEYBOARD:
				blog_info("Keyboard");
				break;
			case USB_PROT_HID_MOUSE:
				blog_info("Mouse");
				break;
			default:
				blog_info("reserved");
				break;
			}
			break;
		default:
			blog_info("reserved");
			break;
		}
		break;
	case USB_CLASS_MASS_STORAGE:
		blog_info("Mass Storage, ");
		switch (subclass) {
		case US_SC_RBC:
			blog_info("RBC ");
			break;
		case US_SC_8020:
			blog_info("SFF-8020i (ATAPI)");
			break;
		case US_SC_QIC:
			blog_info("QIC-157 (Tape)");
			break;
		case US_SC_UFI:
			blog_info("UFI");
			break;
		case US_SC_8070:
			blog_info("SFF-8070");
			break;
		case US_SC_SCSI:
			blog_info("Transp. SCSI");
			break;
		default:
			blog_info("reserved");
			break;
		}
		blog_info(", ");
		switch (proto) {
		case US_PR_CB:
			blog_info("Command/Bulk");
			break;
		case US_PR_CBI:
			blog_info("Command/Bulk/Int");
			break;
		case US_PR_BULK:
			blog_info("Bulk only");
			break;
		default:
			blog_info("reserved");
			break;
		}
		break;
	default:
		blog_info("%s", usb_get_class_desc(dclass));
		break;
	}
}

static void usb_display_string(struct usb_device *dev, int index)
{
	ALLOC_CACHE_ALIGN_BUFFER(char, buffer, 256);

	if (index != 0) {
		if (usb_string(dev, index, &buffer[0], 256) > 0)
			blog_info("String: \"%s\"", buffer);
	}
}

static void usb_display_desc(struct usb_device *dev)
{
	uint packet_size = dev->descriptor.bMaxPacketSize0;

	if (dev->descriptor.bDescriptorType == USB_DT_DEVICE) {
		blog_info("%d: %s,  USB Revision %x.%x\n", dev->devnum,
		usb_get_class_desc(dev->config.if_desc[0].desc.bInterfaceClass),
				   (dev->descriptor.bcdUSB>>8) & 0xff,
				   dev->descriptor.bcdUSB & 0xff);

		if (strlen(dev->mf) || strlen(dev->prod) ||
		    strlen(dev->serial))
			blog_info(" - %s %s %s\n", dev->mf, dev->prod,
				dev->serial);
		if (dev->descriptor.bDeviceClass) {
			blog_info(" - Class: ");
			usb_display_class_sub(dev->descriptor.bDeviceClass,
					      dev->descriptor.bDeviceSubClass,
					      dev->descriptor.bDeviceProtocol);
			blog_info("\n");
		} else {
			blog_info(" - Class: (from Interface) %s\n",
			       usb_get_class_desc(
				dev->config.if_desc[0].desc.bInterfaceClass));
		}
		if (dev->descriptor.bcdUSB >= cpu_to_le16(0x0300))
			packet_size = 1 << packet_size;
		blog_info(" - PacketSize: %d  Configurations: %d\n",
			packet_size, dev->descriptor.bNumConfigurations);
		blog_info(" - Vendor: 0x%04x  Product 0x%04x Version %d.%d\n",
			dev->descriptor.idVendor, dev->descriptor.idProduct,
			(dev->descriptor.bcdDevice>>8) & 0xff,
			dev->descriptor.bcdDevice & 0xff);
	}

}

static void usb_display_conf_desc(struct usb_config_descriptor *config,
				  struct usb_device *dev)
{
	blog_info("   Configuration: %d\n", config->bConfigurationValue);
	blog_info("   - Interfaces: %d %s%s%dmA\n", config->bNumInterfaces,
	       (config->bmAttributes & 0x40) ? "Self Powered " : "Bus Powered ",
	       (config->bmAttributes & 0x20) ? "Remote Wakeup " : "",
		config->bMaxPower*2);
	if (config->iConfiguration) {
		blog_info("   - ");
		usb_display_string(dev, config->iConfiguration);
		blog_info("\n");
	}
}

static void usb_display_if_desc(struct usb_interface_descriptor *ifdesc,
				struct usb_device *dev)
{
	blog_info("     Interface: %d\n", ifdesc->bInterfaceNumber);
	blog_info("     - Alternate Setting %d, Endpoints: %d\n",
		ifdesc->bAlternateSetting, ifdesc->bNumEndpoints);
	blog_info("     - Class ");
	usb_display_class_sub(ifdesc->bInterfaceClass,
		ifdesc->bInterfaceSubClass, ifdesc->bInterfaceProtocol);
	blog_info("\n");
	if (ifdesc->iInterface) {
		blog_info("     - ");
		usb_display_string(dev, ifdesc->iInterface);
		blog_info("\n");
	}
}

static void usb_display_ep_desc(struct usb_endpoint_descriptor *epdesc)
{
	blog_info("     - Endpoint %d %s ", epdesc->bEndpointAddress & 0xf,
		(epdesc->bEndpointAddress & 0x80) ? "In" : "Out");
	switch ((epdesc->bmAttributes & 0x03)) {
	case 0:
		blog_info("Control");
		break;
	case 1:
		blog_info("Isochronous");
		break;
	case 2:
		blog_info("Bulk");
		break;
	case 3:
		blog_info("Interrupt");
		break;
	}
	blog_info(" MaxPacket %d", get_unaligned(&epdesc->wMaxPacketSize));
	if ((epdesc->bmAttributes & 0x03) == 0x3)
		blog_info(" Interval %dms", epdesc->bInterval);
	blog_info("\n");
}

/* main routine to diasplay the configs, interfaces and endpoints */
static void usb_display_config(struct usb_device *dev)
{
	struct usb_config *config;
	struct usb_interface *ifdesc;
	struct usb_endpoint_descriptor *epdesc;
	int i, ii;

	config = &dev->config;
	usb_display_conf_desc(&config->desc, dev);
	for (i = 0; i < config->no_of_if; i++) {
		ifdesc = &config->if_desc[i];
		usb_display_if_desc(&ifdesc->desc, dev);
		for (ii = 0; ii < ifdesc->no_of_ep; ii++) {
			epdesc = &ifdesc->ep_desc[ii];
			usb_display_ep_desc(epdesc);
		}
	}
	blog_info("\n");
}

/*
 * With driver model this isn't right since we can have multiple controllers
 * and the device numbering starts at 1 on each bus.
 * TODO(sjg@chromium.org): Add a way to specify the controller/bus.
 */
static struct usb_device *usb_find_device(int devnum)
{
#ifdef CONFIG_DM_USB
	struct usb_device *udev;
	struct udevice *hub;
	struct uclass *uc;
	int ret;

	/* Device addresses start at 1 */
	devnum++;
	ret = uclass_get(UCLASS_USB_HUB, &uc);
	if (ret)
		return NULL;

	uclass_foreach_dev(hub, uc) {
		struct udevice *dev;

		if (!device_active(hub))
			continue;
		udev = dev_get_parent_priv(hub);
		if (udev->devnum == devnum)
			return udev;

		for (device_find_first_child(hub, &dev);
		     dev;
		     device_find_next_child(&dev)) {
			if (!device_active(hub))
				continue;

			udev = dev_get_parent_priv(dev);
			if (udev->devnum == devnum)
				return udev;
		}
	}
#else
	struct usb_device *udev;
	int d;

	for (d = 0; d < USB_MAX_DEVICE; d++) {
		udev = usb_get_dev_index(d);
		if (udev == NULL)
			return NULL;
		if (udev->devnum == devnum)
			return udev;
	}
#endif

	return NULL;
}

static inline const char *portspeed(int speed)
{
	switch (speed) {
	case USB_SPEED_SUPER:
		return "5 Gb/s";
	case USB_SPEED_HIGH:
		return "480 Mb/s";
	case USB_SPEED_LOW:
		return "1.5 Mb/s";
	default:
		return "12 Mb/s";
	}
}

/* shows the device tree recursively */
static void usb_show_tree_graph(struct usb_device *dev, char *pre)
{
	int index;
	int has_child, last_child;

	index = strlen(pre);
	blog_info(" %s", pre);
#ifdef CONFIG_DM_USB
	has_child = device_has_active_children(dev->dev);
	if (device_get_uclass_id(dev->dev) == UCLASS_MASS_STORAGE) {
		struct udevice *child;

		for (device_find_first_child(dev->dev, &child);
		     child;
		     device_find_next_child(&child)) {
			if (device_get_uclass_id(child) == UCLASS_BLK)
				has_child = 0;
		}
	}
#else
	/* check if the device has connected children */
	int i;

	has_child = 0;
	for (i = 0; i < dev->maxchild; i++) {
		if (dev->children[i] != NULL)
			has_child = 1;
	}
#endif
	/* check if we are the last one */
#ifdef CONFIG_DM_USB
	/* Not the root of the usb tree? */
	if (device_get_uclass_id(dev->dev->parent) != UCLASS_USB) {
		last_child = device_is_last_sibling(dev->dev);
#else
	if (dev->parent != NULL) { /* not root? */
		last_child = 1;
		for (i = 0; i < dev->parent->maxchild; i++) {
			/* search for children */
			if (dev->parent->children[i] == dev) {
				/* found our pointer, see if we have a
				 * little sister
				 */
				while (i++ < dev->parent->maxchild) {
					if (dev->parent->children[i] != NULL) {
						/* found a sister */
						last_child = 0;
						break;
					} /* if */
				} /* while */
			} /* device found */
		} /* for all children of the parent */
#endif
		blog_info("\b+-");
		/* correct last child */
		if (last_child && index)
			pre[index-1] = ' ';
	} /* if not root hub */
	else
		blog_info(" ");
	blog_info("%d ", dev->devnum);
	pre[index++] = ' ';
	pre[index++] = has_child ? '|' : ' ';
	pre[index] = 0;
	blog_info(" %s (%s, %dmA)\n", usb_get_class_desc(
					dev->config.if_desc[0].desc.bInterfaceClass),
					portspeed(dev->speed),
					dev->config.desc.bMaxPower * 2);
	if (strlen(dev->mf) || strlen(dev->prod) || strlen(dev->serial))
		blog_info(" %s  %s %s %s\n", pre, dev->mf, dev->prod, dev->serial);
	blog_info(" %s\n", pre);
#ifdef CONFIG_DM_USB
	struct udevice *child;

	for (device_find_first_child(dev->dev, &child);
	     child;
	     device_find_next_child(&child)) {
		struct usb_device *udev;

		if (!device_active(child))
			continue;

		udev = dev_get_parent_priv(child);

		/*
		 * Ignore emulators and block child devices, we only want
		 * real devices
		 */
		if (udev &&
		    (device_get_uclass_id(child) != UCLASS_BOOTDEV) &&
		    (device_get_uclass_id(child) != UCLASS_USB_EMUL) &&
		    (device_get_uclass_id(child) != UCLASS_BLK)) {
			usb_show_tree_graph(udev, pre);
			pre[index] = 0;
		}
	}
#else
	if (dev->maxchild > 0) {
		for (i = 0; i < dev->maxchild; i++) {
			if (dev->children[i] != NULL) {
				usb_show_tree_graph(dev->children[i], pre);
				pre[index] = 0;
			}
		}
	}
#endif
}

/* main routine for the tree command */
static void usb_show_subtree(struct usb_device *dev)
{
	char preamble[32];

	memset(preamble, '\0', sizeof(preamble));
	usb_show_tree_graph(dev, &preamble[0]);
}

#ifdef CONFIG_DM_USB
typedef void (*usb_dev_func_t)(struct usb_device *udev);

static void usb_for_each_root_dev(usb_dev_func_t func)
{
	struct udevice *bus;

	for (uclass_find_first_device(UCLASS_USB, &bus);
		bus;
		uclass_find_next_device(&bus)) {
		struct usb_device *udev;
		struct udevice *dev;

		if (!device_active(bus))
			continue;

		device_find_first_child(bus, &dev);
		if (dev && device_active(dev)) {
			udev = dev_get_parent_priv(dev);
			func(udev);
		}
	}
}
#endif

void usb_show_tree(void)
{
#ifdef CONFIG_DM_USB
	usb_for_each_root_dev(usb_show_subtree);
#else
	struct usb_device *udev;
	int i;

	for (i = 0; i < USB_MAX_DEVICE; i++) {
		udev = usb_get_dev_index(i);
		if (udev == NULL)
			break;
		if (udev->parent == NULL)
			usb_show_subtree(udev);
	}
#endif
}

static int usb_test(struct usb_device *dev, int port, char* arg)
{
	int mode;

	if (port > dev->maxchild) {
		blog_info("Device is no hub or does not have %d ports.\n", port);
		return 1;
	}

	switch (arg[0]) {
	case 'J':
	case 'j':
		blog_info("Setting Test_J mode");
		mode = USB_TEST_MODE_J;
		break;
	case 'K':
	case 'k':
		blog_info("Setting Test_K mode");
		mode = USB_TEST_MODE_K;
		break;
	case 'S':
	case 's':
		blog_info("Setting Test_SE0_NAK mode");
		mode = USB_TEST_MODE_SE0_NAK;
		break;
	case 'P':
	case 'p':
		blog_info("Setting Test_Packet mode");
		mode = USB_TEST_MODE_PACKET;
		break;
	case 'F':
	case 'f':
		blog_info("Setting Test_Force_Enable mode");
		mode = USB_TEST_MODE_FORCE_ENABLE;
		break;
	default:
		blog_info("Unrecognized test mode: %s\nAvailable modes: "
		       "J, K, S[E0_NAK], P[acket], F[orce_Enable]\n", arg);
		return 1;
	}

	if (port)
		blog_info(" on downstream facing port %d...\n", port);
	else
		blog_info(" on upstream facing port...\n");

	if (usb_control_msg(dev, usb_sndctrlpipe(dev, 0), USB_REQ_SET_FEATURE,
			    port ? USB_RT_PORT : USB_RECIP_DEVICE,
			    port ? USB_PORT_FEAT_TEST : USB_FEAT_TEST,
			    (mode << 8) | port,
			    NULL, 0, USB_CNTL_TIMEOUT) == -1) {
		blog_info("Error during SET_FEATURE.\n");
		return 1;
	} else {
		blog_info("Test mode successfully set. Use 'usb start' "
		       "to return to normal operation.\n");
		return 0;
	}
}


/******************************************************************************
 * usb boot command intepreter. Derived from diskboot
 */
#ifdef CONFIG_USB_STORAGE
static int do_usbboot(struct cmd_tbl *cmdtp, int flag, int argc,
		      char *const argv[])
{
	return common_diskboot(cmdtp, "usb", argc, argv);
}
#endif /* CONFIG_USB_STORAGE */

static int do_usb_stop_keyboard(int force)
{
#if !defined CONFIG_DM_USB && defined CONFIG_USB_KEYBOARD
	if (usb_kbd_deregister(force) != 0) {
		blog_info("USB not stopped: usbkbd still using USB\n");
		return 1;
	}
#endif
	return 0;
}

static void do_usb_start(void)
{
	bootstage_mark_name(BOOTSTAGE_ID_USB_START, "usb_start");

	if (usb_init() < 0)
		return;

	/* Driver model will probe the devices as they are found */
# ifdef CONFIG_USB_STORAGE
	/* try to recognize storage devices immediately */
	usb_stor_curr_dev = usb_stor_scan(1);
# endif
#ifndef CONFIG_DM_USB
# ifdef CONFIG_USB_KEYBOARD
	drv_usb_kbd_init();
# endif
#endif /* !CONFIG_DM_USB */
}

#ifdef CONFIG_DM_USB
static void usb_show_info(struct usb_device *udev)
{
	struct udevice *child;

	usb_display_desc(udev);
	usb_display_config(udev);
	for (device_find_first_child(udev->dev, &child);
	     child;
	     device_find_next_child(&child)) {
		if (device_active(child) &&
		    (device_get_uclass_id(child) != UCLASS_BOOTDEV) &&
		    (device_get_uclass_id(child) != UCLASS_USB_EMUL) &&
		    (device_get_uclass_id(child) != UCLASS_BLK)) {
			udev = dev_get_parent_priv(child);
			if (udev)
				usb_show_info(udev);
		}
	}
}
#endif

/******************************************************************************
 * usb command intepreter
 */
static int do_usb(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	struct usb_device *udev = NULL;
	int i;

	if (argc < 2)
		return CMD_RET_USAGE;

	if (strncmp(argv[1], "start", 5) == 0) {
		if (usb_started)
			return 0; /* Already started */
		blog_info("starting USB...\n");
		do_usb_start();
		return 0;
	}

	if (strncmp(argv[1], "reset", 5) == 0) {
		blog_info("resetting USB...\n");
		if (do_usb_stop_keyboard(1) != 0)
			return 1;
		usb_stop();
		do_usb_start();
		return 0;
	}
	if (strncmp(argv[1], "stop", 4) == 0) {
		if (argc != 2)
			console_assign(stdin, "serial");
		if (do_usb_stop_keyboard(0) != 0)
			return 1;
		blog_info("stopping USB..\n");
		usb_stop();
		return 0;
	}
	if (!usb_started) {
		blog_info("USB is stopped. Please issue 'usb start' first.\n");
		return 1;
	}
	if (strncmp(argv[1], "tree", 4) == 0) {
		puts("USB device tree:\n");
		usb_show_tree();
		return 0;
	}
	if (strncmp(argv[1], "inf", 3) == 0) {
		if (argc == 2) {
#ifdef CONFIG_DM_USB
			usb_for_each_root_dev(usb_show_info);
#else
			int d;
			for (d = 0; d < USB_MAX_DEVICE; d++) {
				udev = usb_get_dev_index(d);
				if (udev == NULL)
					break;
				usb_display_desc(udev);
				usb_display_config(udev);
			}
#endif
			return 0;
		} else {
			/*
			 * With driver model this isn't right since we can
			 * have multiple controllers and the device numbering
			 * starts at 1 on each bus.
			 */
			i = dectoul(argv[2], NULL);
			blog_info("config for device %d\n", i);
			udev = usb_find_device(i);
			if (udev == NULL) {
				blog_info("*** No device available ***\n");
				return 0;
			} else {
				usb_display_desc(udev);
				usb_display_config(udev);
			}
		}
		return 0;
	}
	if (strncmp(argv[1], "test", 4) == 0) {
		if (argc < 5)
			return CMD_RET_USAGE;
		i = dectoul(argv[2], NULL);
		udev = usb_find_device(i);
		if (udev == NULL) {
			blog_info("Device %d does not exist.\n", i);
			return 1;
		}
		i = dectoul(argv[3], NULL);
		return usb_test(udev, i, argv[4]);
	}
#ifdef CONFIG_USB_STORAGE
	if (strncmp(argv[1], "stor", 4) == 0)
		return usb_stor_info();

	return blk_common_cmd(argc, argv, UCLASS_USB, &usb_stor_curr_dev);
#else
	return CMD_RET_USAGE;
#endif /* CONFIG_USB_STORAGE */
}

U_BOOT_CMD(
	usb,	5,	1,	do_usb,
	"USB sub-system",
	"start - start (scan) USB controller\n"
	"usb reset - reset (rescan) USB controller\n"
	"usb stop [f] - stop USB [f]=force stop\n"
	"usb tree - show USB device tree\n"
	"usb info [dev] - show available USB devices\n"
	"usb test [dev] [port] [mode] - set USB 2.0 test mode\n"
	"    (specify port 0 to indicate the device's upstream port)\n"
	"    Available modes: J, K, S[E0_NAK], P[acket], F[orce_Enable]\n"
#ifdef CONFIG_USB_STORAGE
	"usb storage - show details of USB storage devices\n"
	"usb dev [dev] - show or set current USB storage device\n"
	"usb part [dev] - print partition table of one or all USB storage"
	"    devices\n"
	"usb read addr blk# cnt - read `cnt' blocks starting at block `blk#'\n"
	"    to memory address `addr'\n"
	"usb write addr blk# cnt - write `cnt' blocks starting at block `blk#'\n"
	"    from memory address `addr'"
#endif /* CONFIG_USB_STORAGE */
);


#ifdef CONFIG_USB_STORAGE
U_BOOT_CMD(
	usbboot,	3,	1,	do_usbboot,
	"boot from USB device",
	"loadAddr dev:part"
);
#endif /* CONFIG_USB_STORAGE */
