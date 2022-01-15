/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/device.h>
#include <device/pnp.h>
#include <pc80/keyboard.h>
#include <superio/conf_mode.h>
#include <superio/ite/common/env_ctrl.h>

#include "it8987e.h"
#include "chip.h"

static void it8987e_init(struct device *const dev)
{
	const struct superio_ite_it8987e_config *conf;
	const struct resource *res;

	if (!dev->enabled)
		return;

	switch (dev->path.pnp.device) {
	case IT8987E_KBCK:
		pc_keyboard_init(NO_AUX_DEVICE);
		break;
	default:
		break;
	}
}

static struct device_operations ops = {
	.read_resources   = pnp_read_resources,
	.set_resources    = pnp_set_resources,
	.enable_resources = pnp_enable_resources,
	.enable           = pnp_alt_enable,
	.init             = it8987e_init,
	.ops_pnp_mode     = &pnp_conf_mode_870155_aa,
};

static struct pnp_info pnp_dev_info[] = {
	/* Serial Port 1 */
	{ },
	/* Serial Port 2 */
	{ },
	/* System Wake-Up Control */
	{ },
	/* KBC Keyboard */
	{ },
	/* KBC Mouse */
	{ },
	/* GPIO */
	{ },
	/* Consumer Infrared */
	{ },
	/* Shared Memory/Flash Interface */
	{ },
	/* RTC-like Timer */
	{ },
	/* Power Management I/F Channel 1 */
	{ },
	/* Power Management I/F Channel 2 */
	{ },
	/* Serial Peripheral Interface */
	{ },
	/* Platform Environment Control Interface */
	{ },
	/* Power Management I/F Channel 3 */
	{ },
	/* Power Management I/F Channel 4 */
	{ },
	/* Power Management I/F Channel 5 */
	{ },
};

static void enable_dev(struct device *dev)
{
	pnp_enable_devices(dev, &ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);
}

struct chip_operations superio_ite_it8987e_ops = {
	CHIP_NAME("ITE IT8987E Super I/O")
	.enable_dev = enable_dev,
};
