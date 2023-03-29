/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef DRIVERS_OPTION_CFR_H
#define DRIVERS_OPTION_CFR_H

#include <commonlib/coreboot_tables.h>
#include <commonlib/cfr.h>
#include <types.h>

/* Front-end */
struct sm_enum_value {
	const char *ui_name;
	uint32_t value;
};

#define SM_ENUM_VALUE_END	((struct sm_enum_value) {0})

struct sm_obj_enum {
	uint32_t flags;		/* enum cfr_option_flags */
	const char *opt_name;
	const char *ui_name;
	const char *ui_helptext;
	uint32_t default_value;
	const struct sm_enum_value *values;
};

struct sm_obj_number {
	uint32_t flags;		/* enum cfr_option_flags */
	const char *opt_name;
	const char *ui_name;
	const char *ui_helptext;
	uint32_t default_value;
};

struct sm_obj_bool {
	uint32_t flags;		/* enum cfr_option_flags */
	const char *opt_name;
	const char *ui_name;
	const char *ui_helptext;
	bool default_value;
};

struct sm_obj_varchar {
	uint32_t flags;		/* enum cfr_option_flags */
	const char *opt_name;
	const char *ui_name;
	const char *ui_helptext;
	const char *default_value;
};

struct sm_obj_comment {
	uint32_t flags;		/* enum cfr_option_flags */
	const char *ui_name;
	const char *ui_helptext;
};

struct sm_object;

struct sm_obj_form {
	uint32_t flags;		/* enum cfr_option_flags */
	const char *ui_name;
	struct sm_object *obj_list[];	/* NULL terminated */
};

enum sm_object_kind {
	SM_OBJ_NONE = 0,
	SM_OBJ_ENUM,
	SM_OBJ_NUMBER,
	SM_OBJ_BOOL,
	SM_OBJ_VARCHAR,
	SM_OBJ_COMMENT,
	SM_OBJ_FORM,
};

struct sm_object {
	enum sm_object_kind kind;
	union {
		struct sm_obj_enum sm_enum;
		struct sm_obj_number sm_number;
		struct sm_obj_bool sm_bool;
		struct sm_obj_varchar sm_varchar;
		struct sm_obj_comment sm_comment;
		struct sm_obj_form sm_form;
	};
};

/* sm_object helpers with type checking */
#define SINGLE_ARG(...) __VA_ARGS__

#define SM_DECLARE_ENUM(...)	{ .kind = SM_OBJ_ENUM,    .sm_enum    = __VA_ARGS__ }
#define SM_DECLARE_NUMBER(...)	{ .kind = SM_OBJ_NUMBER,  .sm_number  = __VA_ARGS__ }
#define SM_DECLARE_BOOL(...)	{ .kind = SM_OBJ_BOOL,    .sm_bool    = __VA_ARGS__ }
#define SM_DECLARE_VARCHAR(...)	{ .kind = SM_OBJ_VARCHAR, .sm_varchar = __VA_ARGS__ }
#define SM_DECLARE_COMMENT(...)	{ .kind = SM_OBJ_COMMENT, .sm_comment = __VA_ARGS__ }
#define SM_DECLARE_FORM(...)	{ .kind = SM_OBJ_FORM,    .sm_form    = __VA_ARGS__ }

struct setup_menu_root {
	const struct sm_obj_form *form_list;
	size_t num_forms;
};

void cfr_write_setup_menu(struct lb_header *header, const struct setup_menu_root *sm_root);

#endif	/* DRIVERS_OPTION_CFR_H */
