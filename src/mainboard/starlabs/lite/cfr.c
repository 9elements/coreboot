/* SPDX-License-Identifier: GPL-2.0-only */

#include <boot/coreboot_tables.h>
#include <commonlib/coreboot_tables.h>
#include <drivers/option/cfr.h>
#include <inttypes.h>
#include <string.h>
#include <types.h>
#include <variants.h>

static struct sm_object boot_option = SM_DECLARE_ENUM({
	.opt_name	= "boot_option",
	.ui_name	= "Boot Option",
	.ui_helptext	= "Change the boot device in the event of a failed boot",
	.default_value	= 0,
	.values		= (const struct sm_enum_value[]) {
		{	"Fallback",	0		},
		{	"Normal",	1		},
		SM_ENUM_VALUE_END,
	}
});

static struct sm_object debug_level = SM_DECLARE_ENUM({
	.opt_name	= "debug_level",
	.ui_name	= "Debug Level",
	.ui_helptext	= "Set the verbosity of the debug output.",
	.default_value	= 0,
	.values		= (const struct sm_enum_value[]) {
		{	"Emergency",	0		},
		{	"Alert",	1		},
		{	"Critical",	2		},
		{	"Error",	3		},
		{	"Warning",	4		},
		{	"Notice",	5		},
		{	"Info",		6		},
		{	"Debug",	7		},
		{	"Spew",		8		},
		SM_ENUM_VALUE_END,
});

static struct sm_object kbl_timeout = SM_DECLARE_ENUM({
	.opt_name	= "kbl_timeout",
		.ui_name	= "Keyboard Backlight Timeout",
		.ui_helptext	= "Set the amount of time before the keyboard backlight turns off when un-used",
		.default_value	= 0,
		.values		= (const struct sm_enum_value[]) {
			{	"30 seconds",	0		},
			{	"1 minute",	1		},
			{	"3 minutes",	2		},
			{	"5 minutes",	3		},
			{	"Never",	4		},
			SM_ENUM_VALUE_END,
		}
	}
});

static struct sm_object power_profile = SM_DECLARE_ENUM({
		.opt_name	= "power_profile",
		.ui_name	= "Power Profile",
		.ui_helptext	= "Select whether to maximise performance, battery life or both.",
		.default_value	= 1,
		.values		= (const struct sm_enum_value []) {
			{	"Power Saver",	PP_POWER_SAVER	},
			{	"Balanced",	PP_BALANCED	},
			{	"Performance",	PP_PERFORMANCE	},
			SM_ENUM_VALUE_END,
		},
	}
});

#if CONFIG(EC_STARLABS_FAST_CHARGE)
static struct sm_object fast_charge = SM_DECLARE_BOOL({
	.opt_name	= "fast_charge",
	.ui_name	= "Fast Charge",
	.ui_helptext	= "Charge the battery faster at the cost of heat and battery wear.",
	.default_value	= false,
});
#endif

static struct sm_object fn_ctrl_swap = SM_DECLARE_BOOL({
		.opt_name	= "fn_ctrl_swap",
		.ui_name	= "Fn Ctrl Reverse",
		.ui_helptext	= "Swap the functions of the [Fn] and [Ctrl] keys",
		.default_value	= false,
});

static struct sm_object legacy_8254_timer = SM_DECLARE_BOOL({
	.opt_name	= "legacy_8254_timer",
	.ui_name	= "Legacy 8254 Timer",
	.ui_helptext	= "Enable or disable the legacy 8254 timer. Increases power consumption"
			"by disabling clock gating, but increases compatibility with older"
			"Operating Systems",
	.default_value	= false,
});

static struct sm_object hyper_threading = SM_DECLARE_BOOL({
	.opt_name	= "hyper_threading",
	.ui_name	= "Hyper-Threading",
	.ui_helptext	= "Enable or disable Hyper-Threading",
	.default_value	= true,
});

#if CONFIG(EC_STARLABS_MIRROR_SUPPORT)
static struct sm_object mirror_flag = SM_DECLARE_BOOL({
	.opt_name	= "mirror_flag",
	.ui_name	= "Mirror Flag",
	.ui_helptext	= "Use the mirror flag to automatically update the EC firmware from coreboot.",
	.default_value	= false,
});
#endif

static struct sm_object vtd = SM_DECLARE_BOOL({
	.opt_name	= "vtd",
	.ui_name	= "VT-d",
	.ui_helptext	= "Enable or disable Intel VT-d (virtualisation)",
	.default_value	= true,
});

static struct sm_object webcam = SM_DECLARE_BOOL({
	.opt_name	= "webcam",
	.ui_name	= "Webcam",
	.ui_helptext	= "Enable or disable the built-in webcam",
	.default_value	= true,
});

static struct sm_object wireless = SM_DECLARE_BOOL({
	.opt_name	= "wireless",
	.ui_name	= "Wireless",
	.ui_helptext	= "Enable or disable the built-in wireless card",
	.default_value	= true,
});

#if CONFIG(EC_STARLABS_MIRROR_SUPPORT)
static struct sm_object mirror_flag_counter = SM_DECLARE_NUMBER({
	.opt_name	= "mirror_flag_counter",
	.ui_name	= "Mirror Flag Counter",
	.flags		= CFR_OPTFLAG_SUPPRESS,
	.default_value	= 0,
});
#endif

static struct sm_object reboot_counter = SM_DECLARE_NUMBER({
	.opt_name	= "reboot_counter",
	.ui_name	= "Reboot Counter",
	.flags		= CFR_OPTFLAG_SUPPRESS,
	.default_value	= 0,
});

static const struct sm_obj_form general_options = {
	.ui_name	= "General Options",
	.obj_list	= {
		&power_profile,
		&kbl_timeout,
		&fn_ctrl_swap,
#if CONFIG(EC_STARLABS_FAST_CHARGE)
		&fast_charge,
#endif
		NULL
	},
};

static const struct sm_obj_form devices = {
	.ui_name	= "Devices",
	.obj_list	= {
		&wireless,
		&webcam,
		NULL
	},
};

static const struct sm_obj_form chipset = {
	.ui_name	= "Chipset",
	.obj_list	= {
		&legacy_8254_timer,
		&hyper_threading,
		&vtd,
		NULL
	},
};

static const struct sm_obj_form coreboot = {
	.ui_name	= "coreboot",
	.obj_list	= {
		&boot_option,
		&debug_level,
		&reboot_counter,
		NULL
	},
};

static const struct sm_obj_form ec = {
	.ui_name	= "Embedded Controller",
	.obj_list	= {
#if CONFIG(EC_STARLABS_MIRROR_SUPPORT)
		&mirror_flag,
		&mirror_flag_counter,
#endif
		NULL
	},
};

static const struct sm_obj_form root_contents[] = {
	general_options,
	devices,
	chipset,
	coreboot,
	ec
};

static const struct setup_menu_root sm_root = {
	.form_list	= root_contents,
	.num_forms	= ARRAY_SIZE(root_contents),
};

void lb_board(struct lb_header *header)
{
	cfr_write_setup_menu(header, &sm_root);
}

