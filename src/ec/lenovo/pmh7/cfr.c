/* SPDX-License-Identifier: GPL-2.0-only */

#include <string.h>
#include <stdlib.h>

#include "cfr.h"
#include "pmh7.h"

static struct sm_object *pmh7_contents = NULL;
static size_t pmh7_num_objects = 0;


static struct sm_object touchpad_enabled = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "touchpad",
	.ui_name	= "Touchpad enabled",
	.ui_helptext	= "The touchpad is operational.",
	.default_value	= true,
});

static struct sm_object trackpoint_enabled = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "trackpoint",
	.ui_name	= "Trackpoint enabled",
	.ui_helptext	= "The trackpoint is operational.",
	.default_value	= true,
});

static char pmh7_id_str[20];
static struct sm_object serial_number = SM_DECLARE_VARCHAR({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "pmh7_id",
	.ui_name	= "PMH7 Revision",
	.default_value	= pmh7_id_str,
});

struct sm_object contents[] = {
	&touchpad_enabled,
	&trackpoint_enabled,
	&serial_number,
	NULL
};

static void pmh7_cfr_update(void)
{
	snprintf(pmh7_id_str, sizeof(pmh7_id_str), "ID %02x Revision %02x",
	       pmh7_register_read(EC_LENOVO_PMH7_REG_ID),
	       pmh7_register_read(EC_LENOVO_PMH7_REG_REV));
}

struct sm_object *pmh7_cfr_get_contents(void)
{
	pmh7_cfr_update();

	return contents;
}