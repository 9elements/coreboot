## SPDX-License-Identifier: GPL-2.0-only

ramstage-$(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC) += data_fabric_helper.c
ramstage-$(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC_DOMAIN) += domain.c

ifeq ($(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC_MULTI_PCI_SEGMENT),y)
ramstage-$(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC_DOMAIN) += pci_segment_multi.c
else
ramstage-$(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC_DOMAIN) += pci_segment_single.c
endif

ifeq ($(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC_EXTENDED_MMIO),y)
ramstage-$(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC_DOMAIN) += extended_mmio.c
else
ramstage-$(CONFIG_SOC_AMD_COMMON_BLOCK_DATA_FABRIC_DOMAIN) += mmio.c
endif
