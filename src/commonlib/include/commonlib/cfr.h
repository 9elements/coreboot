/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef COMMONLIB_OPTION_CFR_H
#define COMMONLIB_OPTION_CFR_H

#include <stdint.h>
#include <types.h>

/*
 * The CFR table information is for conveying available boot
 * option of the firmware to the loaded OS image or payload.
 * Primarily this is expected to be information that is user
 * visible.
 *
 * The boot options are grouped into forms, where each form hold
 * one ore more options.
 * Boot options that are not used in the current boot flow, but
 * are reachable under certain conditions should be marked as hidden.
 *
 * A boot option can be one of the following types:
 * - boolean
 * - number
 * - enum
 * - string
 *
 * Each boot option has an UI name and UI help text that is free to
 * choose. All strings are in ASCII.
 *
 * All of the information should be Position Independent Data.
 * That is it should be safe to relocated any of the information
 * without it's meaning/correctness changing.   For table that
 * can reasonably be used on multiple architectures the data
 * size should be fixed.  This should ease the transition between
 * 32 bit and 64 bit architectures etc.
 *
 * CFR records form a tree structure. The size of a record includes
 * the size of its own fields plus the size of all children records.
 * CFR tags can appear multiple times except for `LB_TAG_CFR` which
 * is used for the root record.
 *
 * The following structures have comments that describe the supported
 * children records. These comments cannot be replaced with code! The
 * structures are variable-length, so the offsets won't be valid most
 * of the time. Besides, the implementation uses `sizeof()` to obtain
 * the size of the "record header" (the fixed-length members); adding
 * the children structures as struct members will increase the length
 * returned by `sizeof()`, which complicates things for zero reason.
 *
 */

enum cfr_tags {
	CFR_TAG_OPTION_FORM		= 1,
	CFR_TAG_ENUM_VALUE		= 2,
	CFR_TAG_OPTION_ENUM		= 3,
	CFR_TAG_OPTION_NUMBER		= 4,
	CFR_TAG_OPTION_BOOL		= 5,
	CFR_TAG_OPTION_VARCHAR		= 6,
	CFR_TAG_VARCHAR_OPT_NAME	= 7,
	CFR_TAG_VARCHAR_UI_NAME		= 8,
	CFR_TAG_VARCHAR_UI_HELPTEXT	= 9,
	CFR_TAG_VARCHAR_DEF_VALUE	= 10,
	CFR_TAG_OPTION_COMMENT		= 11,
};

enum cfr_option_flags {
	CFR_OPTFLAG_READONLY	= 1 << 0,
	CFR_OPTFLAG_GRAYOUT	= 1 << 1,
	CFR_OPTFLAG_SUPPRESS	= 1 << 2,
	CFR_OPTFLAG_VOLATILE	= 1 << 3,
};

struct lb_cfr_varbinary {
	uint32_t tag;		/* Any CFR_VARBINARY or CFR_VARCHAR */
	uint32_t size;		/* Length of the entire structure */
	uint32_t data_length;	/* Length of data, including NULL terminator for strings */
	uint8_t data[];
};

struct lb_cfr_enum_value {
	uint32_t tag;
	uint32_t size;
	uint32_t value;
	/*
	 * struct lb_cfr_varbinary 		ui_name
	 */
};

/* Supports multiple option types: ENUM, NUMBER, BOOL */
struct lb_cfr_numeric_option {
	uint32_t tag;		/* CFR_OPTION_ENUM, CFR_OPTION_NUMBER, CFR_OPTION_BOOL */
	uint32_t size;
	uint32_t object_id;
	uint32_t flags;		/* enum cfr_option_flags */
	uint32_t default_value;
	/*
	 * struct lb_cfr_varbinary		opt_name
	 * struct lb_cfr_varbinary		ui_name
	 * struct lb_cfr_varbinary		ui_helptext (Optional)
	 * struct lb_cfr_enum_value		enum_values[]
	 */
};

struct lb_cfr_varchar_option {
	uint32_t tag;		/* CFR_OPTION_VARCHAR */
	uint32_t size;
	uint32_t object_id;
	uint32_t flags;		/* enum cfr_option_flags */
	/*
	 * struct lb_cfr_varbinary		default_value
	 * struct lb_cfr_varbinary		opt_name
	 * struct lb_cfr_varbinary		ui_name
	 * struct lb_cfr_varbinary		ui_helptext (Optional)
	 */
};

/*
 * A CFR option comment is roughly equivalent to a Kconfig comment.
 * Option comments are *NOT* string options (see CFR_OPTION_VARCHAR
 * instead) but they're considered an option for simplicity's sake.
 */
struct lb_cfr_option_comment {
	uint32_t tag;		/* CFR_OPTION_COMMENT */
	uint32_t size;
	uint32_t object_id;
	uint32_t flags;		/* enum cfr_option_flags */
	/*
	 * struct lb_cfr_varbinary		ui_name
	 * struct lb_cfr_varbinary		ui_helptext (Optional)
	 */
};

/* CFR forms are considered options as they can be nested inside other forms */
struct lb_cfr_option_form {
	uint32_t tag;		/* CFR_OPTION_FORM */
	uint32_t size;
	uint32_t object_id;
	uint32_t flags;		/* enum cfr_option_flags */
	/*
	 * struct lb_cfr_varbinary		ui_name
	 * struct lb_cfr_varchar_option		options[]
	 */
};

struct lb_cfr_header {
	uint32_t tag;
	uint32_t size;
};

#endif	/* DRIVERS_OPTION_CFR_H */
