/* SPDX-License-Identifier: GPL-2.0-only */

#include <soc/gpe.h>
#include <soc/gpio.h>
#include <variant/gpio.h>

/* Name format: <pad name> / <net/pin name in schematics> */
static const struct pad_config gpio_table[] = {
	/* ------- GPIO Group GPD ------- */
	PAD_NC(GPD0, NONE),
	PAD_CFG_NF(GPD1, NATIVE, DEEP, NF1),		/* ACPRESENT / AC_PRESENT */
	PAD_NC(GPD2, NONE),
	PAD_CFG_NF(GPD3, UP_20K, DEEP, NF1),		/* PWRBTN# / PWR_BTN# */
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1),		/* SLP_S3# / SUSB#_PCH */
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1),		/* SLP_S4# / SUSC#_PCH */
	PAD_NC(GPD6, NONE),
	PAD_NC(GPD7, NONE),
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),		/* SUSCLK / SUS_CLK */
	PAD_NC(GPD9, NONE),
	PAD_NC(GPD10, NONE),
	PAD_NC(GPD11, NONE),

	/* ------- GPIO Group GPP_A ------- */
	PAD_CFG_NF(GPP_A0, UP_20K, DEEP, NF1),		/* ESPI_IO0 / ESPI_IO_0 */
	PAD_CFG_NF(GPP_A1, UP_20K, DEEP, NF1),		/* ESPI_IO1 / ESPI_IO_1 */
	PAD_CFG_NF(GPP_A2, UP_20K, DEEP, NF1),		/* ESPI_IO2 / ESPI_IO_2 */
	PAD_CFG_NF(GPP_A3, UP_20K, DEEP, NF1),		/* ESPI_IO3 / ESPI_IO_3 */
	PAD_CFG_NF(GPP_A4, UP_20K, DEEP, NF1),		/* ESPI_CS# / ESPI_CS_N */
	PAD_CFG_NF(GPP_A5, DN_20K, DEEP, NF1),		/* ESPI_CLK */
	PAD_CFG_NF(GPP_A6, NONE, DEEP, NF1),		/* ESPI_RESET# / ESPI_RESET_N */
	PAD_NC(GPP_A7, NONE),
	PAD_CFG_NF(GPP_A8, NONE, DEEP, NF2),		/* CNV_RF_RESET# / CNVI_RST# */
	PAD_CFG_NF(GPP_A9, UP_20K, DEEP, NF2),		/* MODEM_CLKREQ / CNVI_CLKREQ */
	PAD_NC(GPP_A10, NONE),
	PAD_NC(GPP_A11, NONE),
	PAD_CFG_NF(GPP_A12, UP_20K, DEEP, NF1),		/* SATAXPCIE1 / SATAGP1 (wrong name!) */
	PAD_CFG_GPO(GPP_A13, 1, DEEP),			/* GPP_A13 / PCH_BT_EN */
	PAD_NC(GPP_A14, NONE),
	PAD_NC(GPP_A15, NONE),
	PAD_NC(GPP_A16, NONE),
	PAD_NC(GPP_A17, NONE),
	PAD_CFG_NF(GPP_A18, NONE, DEEP, NF1),		/* DDSP_HPDB / HDMI_HPD */
	PAD_NC(GPP_A19, NONE),
	PAD_NC(GPP_A20, NONE),
	PAD_NC(GPP_A21, NONE),
	PAD_NC(GPP_A22, NONE),
	PAD_CFG_GPO(GPP_A23, 0, PLTRST),		/* GPP_A23 / TC_RETIMER_FORCE_PWR */

	/* ------- GPIO Group GPP_B ------- */
	PAD_CFG_NF(GPP_B0, NONE, DEEP, NF1),		/* CORE_VID0 / VCCIN_AUX_VID0 */
	PAD_CFG_NF(GPP_B1, NONE, DEEP, NF1),		/* CORE_VID1 / VCCIN_AUX_VID1 */
	PAD_CFG_NF(GPP_B2, NONE, DEEP, NF1),		/* VRALERT# */
	PAD_CFG_GPI_APIC_LOW(GPP_B3, NONE, DEEP),	/* GPP_B3 (touchpad interrupt) */
	PAD_NC(GPP_B4, NONE),
	PAD_NC(GPP_B5, NONE),
	PAD_NC(GPP_B6, NONE),
	PAD_NC(GPP_B7, NONE),
	PAD_NC(GPP_B8, NONE),
	PAD_NC(GPP_B9, NONE),
	PAD_NC(GPP_B10, NONE),
	PAD_CFG_NF(GPP_B11, NONE, DEEP, NF1),		/* GPP_B11 / TBTA_I2C_INT */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),		/* SLP_S0# */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),		/* PLT_RST# */
	PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1),		/* SPKR / PCH_SPKR */
	PAD_NC(GPP_B15, NONE),
	PAD_NC(GPP_B16, NONE),
	PAD_NC(GPP_B17, NONE),
	PAD_NC(GPP_B18, NONE),
	PAD_NC(GPP_B19, NONE),
	PAD_NC(GPP_B20, NONE),
	PAD_NC(GPP_B21, NONE),
	PAD_NC(GPP_B22, NONE),
	PAD_NC(GPP_B23, NONE),

	/* ------- GPIO Group GPP_C ------- */
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),		/* SMBCLK / SMB_CLK_DDR */
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1),		/* SMBDATA / SMB_DAT_DDR */
	PAD_NC(GPP_C2, NONE),
	PAD_CFG_NF(GPP_C3, NONE, DEEP, NF1),		/* SML0CLK */
	PAD_CFG_NF(GPP_C4, NONE, DEEP, NF1),		/* SML0_DATA */
	PAD_NC(GPP_C5, NONE),
	PAD_CFG_NF(GPP_C6, NONE, DEEP, NF1),		/* SML1CLK / TBT_I2C_SCL */
	PAD_CFG_NF(GPP_C7, NONE, DEEP, NF1),		/* SML1_DATA / TBT_I2C_SDA */
	PAD_NC(GPP_C8, NONE),
	PAD_CFG_GPI_APIC_LOW(GPP_C9, NONE, DEEP),	/* GPP_C9 / TPM_PIRQ# */
	PAD_NC(GPP_C10, NONE),
	PAD_NC(GPP_C11, NONE),
	PAD_NC(GPP_C12, NONE),
	PAD_CFG_GPO(GPP_C13, 1, DEEP),			/* GPP_C13 / SSD1_PWR_DN# */
	PAD_NC(GPP_C14, NONE),
	PAD_NC(GPP_C15, NONE),
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),		/* I2C0_SDA / T_SDA (touchpad) */
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),		/* I2C0_SCL / T_SCL (touchpad) */
	PAD_CFG_NF(GPP_C18, NONE, DEEP, NF1),		/* I2C1_SDA / PCH_I2C_SDA (retimer rom) */
	PAD_CFG_NF(GPP_C19, NONE, DEEP, NF1),		/* I2C1_SCL / PCH_I2C_SCL (retimer rom) */
	PAD_CFG_NF(GPP_C20, UP_20K, DEEP, NF1),		/* UART2_RXD */
	PAD_CFG_NF(GPP_C21, UP_20K, DEEP, NF1),		/* UART2_TXD */
	PAD_CFG_GPO(GPP_C22, 1, DEEP),			/* GPP_C22 / GPP_C12_RTD3 (SSD1) */
	PAD_NC(GPP_C23, UP_20K),			/* GPP_C23 / PCH_GPP_C23 (WLAN_WAKEUP#) */

	/* ------- GPIO Group GPP_D ------- */
	PAD_CFG_GPO(GPP_D0, 1, DEEP),			/* GPP_D0 / SB_BLON */
	PAD_NC(GPP_D1, NONE),
	PAD_NC(GPP_D2, NONE),				/* LEDKB_DET# (unused; not sold w/o KBLED) */
	PAD_NC(GPP_D3, NONE),				/* BOARD_ID (unused; always high) */
	PAD_NC(GPP_D4, NONE),
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF1),		/* SRCCLKREQ0# / SSD1_CLKREQ# (for SSD2!) */
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF1),		/* SRCCLKREQ1# / WLAN_CLKREQ# */
	PAD_CFG_NF(GPP_D7, NONE, DEEP, NF1),		/* SRCCLKREQ2# / CARD_CLKREQ# */
	PAD_CFG_NF(GPP_D8, NONE, DEEP, NF1),		/* SRCCLKREQ3# / SSD2_CLKREQ# (for SSD1!) */
	PAD_CFG_GPO(GPP_D9, 1, DEEP),			/* GPP_D9 / GPP_D13_RTD3 (SSD2) */
	PAD_NC(GPP_D10, NONE),
	PAD_NC(GPP_D11, NONE),
	PAD_NC(GPP_D12, NONE),
	PAD_NC(GPP_D13, NONE),
	PAD_CFG_GPO(GPP_D14, 1, DEEP),			/* GPP_D14 / SSD2_PWR_DN# */
	PAD_NC(GPP_D15, NONE),
	PAD_NC(GPP_D16, NONE),
	PAD_NC(GPP_D17, NONE),
	PAD_NC(GPP_D18, NONE),
	PAD_NC(GPP_D19, NONE),

	/* ------- GPIO Group GPP_E ------- */
	PAD_NC(GPP_E0, NONE),
	PAD_CFG_GPO(GPP_E1, 0, DEEP),			/* GPP_E1 / ROM_I2C_EN */
	PAD_NC(GPP_E2, NONE),
	PAD_NC(GPP_E3, NONE),				/* SB_KBCRST# (eSPI Virtual Wire) */
	PAD_NC(GPP_E4, NONE),
	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1),		/* DEVSLP1 */
	PAD_NC(GPP_E6, NONE),
	PAD_NC(GPP_E7, NONE),
	PAD_NC(GPP_E8, NONE),
	PAD_NC(GPP_E9, NONE),
	PAD_NC(GPP_E10, NONE),
	PAD_NC(GPP_E11, NONE),
	PAD_NC(GPP_E12, NONE),
	PAD_NC(GPP_E13, NONE),
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),		/* DDSP_HPDA / EDP_HPD */
	PAD_NC(GPP_E15, NONE),				/* SCI# (eSPI Virtual Wire) */
	PAD_NC(GPP_E16, NONE),				/* SMI# (eSPI Virtual Wire) */
	PAD_NC(GPP_E17, NONE),
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF2),		/* TBT_LSX0_TXD */
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF2),		/* TBT_LSX0_RXD */
	PAD_NC(GPP_E20, NONE),				/* SWI# (eSPI Virtual Wire) */
	PAD_NC(GPP_E21, NONE),
	PAD_NC(GPP_E22, NONE),
	PAD_NC(GPP_E23, NONE),

	/* ------- GPIO Group GPP_F ------- */
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),		/* CNV_BRI_DT / CNVI_BRI_DT */
	PAD_CFG_NF(GPP_F1, UP_20K, DEEP, NF1),		/* CNV_BRI_RSP / CNVI_BRI_RSP */
	PAD_CFG_NF(GPP_F2, NONE, DEEP, NF1),		/* CNV_RGI_DT / CNVI_RGI_DT */
	PAD_CFG_NF(GPP_F3, UP_20K, DEEP, NF1),		/* CNV_RGI_RSP / CNVI_RGI_RSP */
	PAD_NC(GPP_F4, NONE),
	PAD_NC(GPP_F5, NONE),
	PAD_NC(GPP_F6, NONE),
	PAD_NC(GPP_F7, NONE),
	PAD_NC(GPP_F8, NONE),
	PAD_NC(GPP_F9, NONE),
	PAD_NC(GPP_F10, NONE),
	PAD_NC(GPP_F11, NONE),
	PAD_NC(GPP_F12, NONE),
	PAD_NC(GPP_F13, NONE),
	PAD_NC(GPP_F14, NONE),
	PAD_NC(GPP_F15, NONE),
	PAD_NC(GPP_F16, NONE),
	PAD_CFG_GPI(GPP_F17, UP_20K, DEEP),		/* GPP_F17 / TPM_DET# */
	PAD_NC(GPP_F18, NONE),
	PAD_NC(GPP_F19, NONE),
	PAD_NC(GPP_F20, NONE),
	PAD_NC(GPP_F21, NONE),
	PAD_NC(GPP_F22, NONE),
	PAD_NC(GPP_F23, NONE),

	/* ------- GPIO Group GPP_H ------- */
	PAD_NC(GPP_H0, NONE),
	PAD_NC(GPP_H1, NONE),
	PAD_NC(GPP_H2, NONE),
	PAD_NC(GPP_H3, NONE),
	PAD_NC(GPP_H4, NONE),
	PAD_NC(GPP_H5, NONE),
	PAD_NC(GPP_H6, NONE),
	PAD_NC(GPP_H7, NONE),
	PAD_NC(GPP_H8, NONE),
	PAD_NC(GPP_H9, NONE),
	PAD_NC(GPP_H10, NONE),
	PAD_NC(GPP_H11, NONE),
	PAD_NC(GPP_H12, NONE),
	PAD_NC(GPP_H13, NONE),
	PAD_NC(GPP_H14, NONE),
	PAD_NC(GPP_H15, NONE),
	PAD_CFG_NF(GPP_H16, NONE, DEEP, NF1),		/* DDPB_CTRLCLK / HDMI_CTRLCLK */
	PAD_CFG_NF(GPP_H17, NONE, DEEP, NF1),		/* DDPB_CTRLDATA / HDMI_CTRLDATA */
	PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1),		/* CPU_C10_GATE# */
	PAD_NC(GPP_H19, NONE),				/* GPP_H19 / CNVI_WAKE#
							   (UART_WAKE# in M.2 spec; unused)
							 */
	PAD_NC(GPP_H20, NONE),
	PAD_NC(GPP_H21, NONE),
	PAD_NC(GPP_H22, NONE),
	PAD_NC(GPP_H23, NONE),

	/* ------- GPIO Group GPP_R ------- */
	PAD_CFG_NF(GPP_R0, NONE, DEEP, NF1),		/* HDA_BCLK / HDA_BITCLK */
	PAD_CFG_NF(GPP_R1, NATIVE, DEEP, NF1),		/* HDA_SYNC */
	PAD_CFG_NF(GPP_R2, NATIVE, DEEP, NF1),		/* HDA_SDO / HDA_SDOUT */
	PAD_CFG_NF(GPP_R3, NATIVE, DEEP, NF1),		/* HDA_SDI0 / HDA_SDIN0 */
	PAD_CFG_NF(GPP_R4, NONE, DEEP, NF1),		/* HDA_RST# / AZ_RST#_R */
	PAD_NC(GPP_R5, NONE),
	PAD_NC(GPP_R6, NONE),
	PAD_NC(GPP_R7, NONE),

	/* ------- GPIO Group GPP_S ------- */
	PAD_NC(GPP_S0, NONE),
	PAD_NC(GPP_S1, NONE),
	PAD_NC(GPP_S2, NONE),
	PAD_NC(GPP_S3, NONE),
	PAD_NC(GPP_S4, NONE),
	PAD_NC(GPP_S5, NONE),
	PAD_NC(GPP_S6, NONE),
	PAD_NC(GPP_S7, NONE),

	/* ------- GPIO Group GPP_T ------- */
	PAD_NC(GPP_T2, NONE),
	PAD_NC(GPP_T3, NONE),

	/* ------- GPIO Group GPP_U ------- */
	PAD_NC(GPP_U4, NONE),
	PAD_NC(GPP_U5, NONE),
};

void variant_configure_gpios(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}
