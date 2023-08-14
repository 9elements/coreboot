/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef EC_LENOVO_H8EC_CFR_H
#define EC_LENOVO_H8EC_CFR_H

#include <drivers/option/cfr.h>
#include <inttypes.h>

struct sm_object *h8_cfr_get_contents(void);

#if CONFIG(DRIVERS_OPTION_CFR)
void h8_cfr_update(bool bdc,
		   bool wwan,
		   bool uwb,
		   bool kb_bl,
		   bool pm_beep,
		   char *version);
#else
static inline
void h8_cfr_update(bool bdc,
		   bool wwan,
		   bool uwb,
		   bool kb_bl,
		   bool pm_beep,
		   char *version)
{
}
#endif
#endif
