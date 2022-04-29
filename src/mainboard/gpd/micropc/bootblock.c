/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <bootblock_common.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8987e/it8987e.h>

#define SERIAL2_DEV	PNP_DEV(0x2e, IT8987E_SP2)

void bootblock_mainboard_early_init(void)
{
	ite_enable_serial(SERIAL2_DEV, CONFIG_TTYS0_BASE);
}
