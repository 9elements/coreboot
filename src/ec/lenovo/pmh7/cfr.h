/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef EC_LENOVO_H8EC_PMH7_H
#define EC_LENOVO_H8EC_PMH7_H

#include <drivers/option/cfr.h>
#include <inttypes.h>

struct sm_object *
pmh7_cfr_get_contents(void);

#endif