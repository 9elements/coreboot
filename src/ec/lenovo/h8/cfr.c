/* SPDX-License-Identifier: GPL-2.0-only */

#include <string.h>
#include <stdlib.h>
#include "cfr.h"

static struct sm_object serial_number = SM_DECLARE_VARCHAR({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "h8_id",
	.ui_name	= "H8 EC Firmware",
});

static struct sm_object bdc_detected = SM_DECLARE_BOOL({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "bdc_detected",
	.ui_name	= "BDC detected",
	.ui_helptext	= "A BDC is installed.",
});

static struct sm_object uwb_supported = SM_DECLARE_BOOL({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "uwb_support",
	.ui_name	= "UWB supported",
	.ui_helptext	= "UWB is supported by this device, but not necessarily installed",
});

static struct sm_object uwb_enabled = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "uwb",
	.ui_name	= "UWB enabled",
	.ui_helptext	= "UWB module is enabled.",
	.default_value	= true,
});

static struct sm_object wwan_detected = SM_DECLARE_BOOL({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "wwan_detected",
	.ui_name	= "WWAN detected",
	.ui_helptext	= "A WWAN module is installed.",
});

static struct sm_object wwan_enabled = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "wwan",
	.ui_name	= "WWAN enabled",
	.ui_helptext	= "WWAN module is enabled.",
	.default_value	= true,
});

static struct sm_object wifi_enabled = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "wlan",
	.ui_name	= "WIFI enabled",
	.ui_helptext	= "WIFI module is enabled.",
	.default_value	= true,
});

static struct sm_enum_value usb_always_on_values[] = {
	{ "Off",    0 },
	{ "AC and Battery",  1 },
	{ "AC only", 2 },
	SM_ENUM_VALUE_END,
};

static struct sm_object usb_always_on = SM_DECLARE_ENUM({
	.opt_name	= "usb_always_on",
	.ui_name	= "USB Always On",
	.ui_helptext	= "Yellow USB port configuration when Off",
	.default_value	= 0,
	.values		= usb_always_on_values,
});

static struct sm_object volume = SM_DECLARE_NUMBER({
	.flags		= 0,
	.opt_name	= "volume",
	.ui_name	= "Initial speaker volume [0-255]",
	.ui_helptext	= "The default speaker volume before the OS loads.",
	.default_value	= 255,
});

static struct sm_object kb_bl_supported = SM_DECLARE_BOOL({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "kb_bl_supported",
	.ui_name	= "Keyboard backlight supported",
	.ui_helptext	= "The device supports keyboard backlight.",
});

static struct sm_enum_value kb_bl_values[] = {
	{ "Both",    0 },
	{ "Keyboard Only",  1 },
	{ "Thinklight Only", 2 },
	{ "None", 2 },
	SM_ENUM_VALUE_END,
};

static struct sm_object kb_bl_setting = SM_DECLARE_ENUM({
	.flags		= 0,
	.opt_name	= "backlight",
	.ui_name	= "Keyboard Backlight",
	.ui_helptext	= "Selects the keyboard backlight configuration.",
	.default_value	= 0,
	.values		= kb_bl_values,
});

static struct sm_object pm_beep_supported = SM_DECLARE_BOOL({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "power_management_beeps_supported",
	.ui_name	= "PWR MGMT Beep supported",
	.ui_helptext	= 0,
	.default_value	= pm_beep,
});

static struct sm_object pm_beep_enabled = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "power_management_beeps",
	.ui_name	= "PWR MGMT Beep enabled",
	.ui_helptext	= 0,
	.default_value	= true,
});

static struct sm_object low_bat_beep_enabled = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "low_battery_beep",
	.ui_name	= "Low Battery Beep enabled",
	.ui_helptext	= 0,
	.default_value	= true,
});

static struct sm_object fn_ctrl_swap = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "fn_ctrl_swap",
	.ui_name	= "Swap Fn and Ctrl keys",
	.ui_helptext	= 0,
	.default_value	= CONFIG(H8_FN_CTRL_SWAP),
});

static struct sm_object sticky_fn = SM_DECLARE_BOOL({
	.flags		= 0,
	.opt_name	= "sticky_fn",
	.ui_name	= "Fn key is sticky",
	.ui_helptext	= 0,
	.default_value	= false,
});

static struct sm_object f1_to_f12_as_primary = SM_DECLARE_BOOL({
	.flags		= CONFIG(H8_HAS_PRIMARY_FN_KEYS) ? 0 : CFR_OPTFLAG_SUPPRESS,
	.opt_name	= "f1_to_f12_as_primary",
	.ui_name	= "F1 to F12 are primary",
	.ui_helptext	= 0,
	.default_value	= true,
});

static struct sm_enum_value first_battery_values[] = {
	{ "Secondary first",    0 },
	{ "Primary first",  1 },
	SM_ENUM_VALUE_END,
};

static struct sm_object first_battery = SM_DECLARE_ENUM({
	.opt_name	= "first_battery",
	.ui_name	= "Battery charge priority",
	.ui_helptext	= 0,
	.default_value	= 1,
	.values		= first_battery_values,
});

static struct sm_object flash_leds_on_death = SM_DECLARE_BOOL({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "flash_leds_on_death",
	.ui_name	= "Flash LEDs on fatal error",
	.ui_helptext	= "Indicate fatal boot failure by flashing all LEDs.",
	.default_value	= CONFIG(H8_FLASH_LEDS_ON_DEATH),
});

static struct sm_object flash_beep_on_death = SM_DECLARE_BOOL({
	.flags		= CFR_OPTFLAG_READONLY | CFR_OPTFLAG_VOLATILE,
	.opt_name	= "flash_beep_on_death",
	.ui_name	= "Beep on fatal error",
	.ui_helptext	= "Indicate fatal boot failure by making some noise.",
	.default_value	= CONFIG(H8_BEEP_ON_DEATH),
});

static struct sm_object contents[] = {
	&bdc_detected,
	&uwb_supported,
	&uwb_enabled,
	&wwan_detected,
	&wwan_enabled,
	&wifi_enabled,
	&pm_beep_supported,
	&pm_beep_enabled,
	&low_bat_beep_enabled,
	&f1_to_f12_as_primary,
	&sticky_fn,
	&fn_ctrl_swap,
	&kb_bl_supported,
	&kb_bl_setting,
	&usb_always_on,
	&volume,
	&first_battery,
	&serial_number,
	&flash_leds_on_death,
	&flash_beep_on_death,
	NULL
};

void h8_cfr_update(bool bdc,
		   bool wwan,
		   bool uwb,
		   bool kb_bl,
		   bool pm_beep,
		   char *version)
{
	serial_number.sm_varchar.default_value = strdup(version);
	bdc_detected.sm_bool.default_value = bdc;
	uwb_supported.sm_bool.default_value = uwb;
	uwb_enabled.sm_bool.flags = !uwb ? CFR_OPTFLAG_SUPPRESS: 0;
	wwan_detected.sm_bool.default_value = wwan;
	wwan_enabled.sm_bool.flags = !wwan ? CFR_OPTFLAG_SUPPRESS: 0;
	kb_bl_supported.sm_bool.default_value = kb_bl;
	kb_bl_setting.sm_enum.flags = !kb_bl ? CFR_OPTFLAG_SUPPRESS: 0;
	pm_beep_supported.sm_bool.default_value = pm_beep;
	pm_beep_enabled.sm_bool.flags = !pm_beep ? CFR_OPTFLAG_SUPPRESS: 0;
	low_bat_beep_enabled.sm_bool.flags = !pm_beep ? CFR_OPTFLAG_SUPPRESS: 0;
}

struct sm_object *h8_cfr_get_contents(void)
{
	*num_objects = h8_num_objects;
	return contents;
}