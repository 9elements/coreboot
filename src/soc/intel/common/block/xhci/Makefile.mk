## SPDX-License-Identifier: GPL-2.0-only
ramstage-$(CONFIG_SOC_INTEL_COMMON_BLOCK_XHCI) += xhci.c
ramstage-$(CONFIG_SOC_INTEL_COMMON_BLOCK_XHCI_ELOG) += elog.c

smm-$(CONFIG_SOC_INTEL_COMMON_BLOCK_XHCI) += xhci.c
smm-$(CONFIG_SOC_INTEL_COMMON_BLOCK_XHCI_ELOG) += elog.c
