## SPDX-License-Identifier: GPL-2.0-only

subdirs-y += sdram_params/

bootblock-y += memlayout.ld
bootblock-y += bootblock.c
bootblock-y += chromeos.c

verstage-y += memlayout.ld
verstage-y += chromeos.c
verstage-y += reset.c

romstage-y += memlayout.ld
romstage-y += boardid.c
romstage-y += chromeos.c
romstage-y += regulator.c
romstage-y += reset.c
romstage-y += romstage.c
romstage-y += sdram_configs.c

ramstage-y += memlayout.ld
ramstage-y += boardid.c
ramstage-y += chromeos.c
ramstage-y += mainboard.c
ramstage-y += reset.c
ramstage-y += regulator.c
