## SPDX-License-Identifier: GPL-2.0-only

romstage-$(CONFIG_HAVE_INTEL_PTT) += ptt.c
ramstage-$(CONFIG_HAVE_INTEL_PTT) += ptt.c
postcar-$(CONFIG_HAVE_INTEL_PTT) += ptt.c
verstage-$(CONFIG_HAVE_INTEL_PTT) += ptt.c
