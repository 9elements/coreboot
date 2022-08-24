/* SPDX-License-Identifier: GPL-2.0-only */

#include <variant/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage */
static const struct pad_config override_gpio_table[] = {
	/* A7  : I2S2_SCLK ==> I2S1_SPKR_SCLK */
	PAD_CFG_NF(GPP_A7, NONE, DEEP, NF1),
	/* A8  : I2S2_SFRM ==> I2S1_SPKR_SFRM */
	PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1),
	/* A9  : I2S2_TXD ==> I2S1_PCH_TX_SPKR_RX */
	PAD_CFG_NF(GPP_A9, NONE, DEEP, NF1),
	/* A10 : I2S2_RXD ==> I2S1_PCH_RX_SPKR */
	PAD_CFG_NF(GPP_A10, NONE, DEEP, NF1),
	/* A13 : PMC_I2C_SCL ==> BT_DISABLE_L */
	PAD_CFG_GPO(GPP_A13, 1, DEEP),
	/* A16 : USB_OC3# ==> USB_C0_OC_ODL */
	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),
	/* A18 : DDSP_HPDB ==> HDMI_HPD */
	PAD_CFG_NF(GPP_A18, NONE, DEEP, NF1),
	/* A21 : DDPC_CTRCLK ==> EN_FP_PWR */
	PAD_CFG_GPO(GPP_A21, 1, DEEP),
	/* A22 : DDPC_CTRLDATA ==> EN_HDMI_PWR */
	PAD_CFG_GPO(GPP_A22, 1, DEEP),

	/* B2  : VRALERT# ==> EN_PP3300_SSD */
	PAD_CFG_GPO(GPP_B2, 1, PLTRST),
	/* B7  : ISH_12C1_SDA ==> ISH_I2C1_SENSOR_SDA */
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF1),
	/* B8  : ISH_I2C1_SCL ==> ISH_I2C1_SENSOR_SCL */
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF1),
	/* B9  : I2C5_SDA ==> PCH_I2C5_TRACKPAD_SDA */
	PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1),
	/* B10 : I2C5_SCL ==> PCH_I2C5_TRACKPAD_SCL */
	PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1),
	/* B22 : GSPI1_MOSI ==> NC */
	PAD_NC(GPP_B22, NONE),
	/* B23 : SML1ALERT# ==> GPP_B23_STRAP # */
	PAD_NC(GPP_B23, DN_20K),

	/* C0  : SMBCLK ==> EN_PP3300_WLAN */
	PAD_CFG_GPO(GPP_C0, 1, DEEP),
	/* C2  : SMBALERT# ==> GPP_C2_STRAP */
	PAD_NC(GPP_C2, DN_20K),
	/* C5  : SML0ALERT# ==> USB_SMB_INT_L_BOOT_STRAP0 */
	PAD_NC(GPP_C5, DN_20K),
	/* C7  : SML1DATA ==> EN_USI_CHARGE */
	PAD_CFG_GPO(GPP_C7, 1, DEEP),
	/* C10 : UART0_RTS# ==> USI_RST_L */
	PAD_CFG_GPO(GPP_C10, 1, DEEP),
	/* C11 : UART0_CTS# ==> TOUCHSCREEN_STOP_L_R */
	PAD_CFG_GPO(GPP_C11, 1, DEEP),
	/* C13 : UART1_TXD ==> EN_PP5000_TRACKPAD */
	PAD_CFG_GPO(GPP_C13, 1, DEEP),
	/* C16 : I2C0_SDA ==> PCH_I2C0_1V8_AUDIO_SDA */
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),
	/* C17 : I2C0_SCL ==> PCH_I2C0_1V8_AUDIO_SCL */
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),
	/* C18 : I2C1_SDA ==> PCH_I2C1_TOUCH_USI_SDA */
	PAD_CFG_NF(GPP_C18, NONE, DEEP, NF1),
	/* C19 : I2C1_SCL ==> PCH_I2C1_TOUCH_USI_SCL */
	PAD_CFG_NF(GPP_C19, NONE, DEEP, NF1),

	/* D0  : ISH_GP0 ==> ISH_IMU_INT_L */
	PAD_CFG_GPI(GPP_D0, NONE, DEEP),
	/* D1  : ISH_GP1 ==> ISH_ACCEL_INT_L */
	PAD_CFG_GPI(GPP_D1, NONE, DEEP),
	/* D2  : ISH_GP2 ==> ISH_LID_OPEN */
	PAD_CFG_GPI(GPP_D2, NONE, DEEP),
	/* D8  : SRCCLKREQ3# ==> SD_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D8, NONE, DEEP, NF1),
	/* D10 : ISH_SPI_CLK ==> PCH_GSPI2_CVF_CLK_STRAP */
	PAD_CFG_NF(GPP_D10, DN_20K, DEEP, NF7),
	/* D12 : ISH_SPI_MOSI ==> PCH_GSPI2_CVF_MISO_STRAP */
	PAD_CFG_NF(GPP_D12, DN_20K, DEEP, NF7),
	/* D13 : ISH_UART0_RXD ==> UART_ISH_RX_DEBUG_TX */
	PAD_CFG_NF(GPP_D13, NONE, DEEP, NF1),
	/* D14 : ISH_UART0_TXD ==> UART_ISH_TX_DEBUG_RX */
	PAD_CFG_NF(GPP_D14, NONE, DEEP, NF1),
	/* D16 : ISH_UART0_CTS# ==> EN_PP3300_SD */
	PAD_CFG_GPO(GPP_D16, 1, DEEP),

	/* E1  : SPI1_IO2 ==> PEN_DET_ODL */
	PAD_CFG_GPI_SCI_LOW(GPP_E1, NONE, DEEP, EDGE_SINGLE),
	/* E3  : CPU_GP0 ==> USI_REPORT_EN */
	PAD_CFG_GPO(GPP_E3, 1, DEEP),
	/* E7  : CPU_GP1 ==> USI_INT */
	PAD_CFG_GPI_APIC(GPP_E7, NONE, PLTRST, LEVEL, NONE),
	/* E10 : SPI1_CS# ==> NC */
	PAD_NC(GPP_E10, NONE),
	/* E11 : SPI1_CLK ==> SD_PE_WAKE_ODL */
	PAD_CFG_GPI(GPP_E11, NONE, DEEP),
	/* E12 : SPI1_MISO_IO1 ==> PEN_ALERT_ODL */
	PAD_CFG_GPI(GPP_E12, NONE, DEEP),
	/* E13 : SPI1_MOSI_IO0 ==> NC */
	PAD_NC(GPP_E13, NONE),
	/* E15 : ISH_GP6 ==> TRACKPAD_INT_ODL */
	PAD_CFG_GPI_IRQ_WAKE(GPP_E15, NONE, DEEP, LEVEL, INVERT),
	/* E16 : ISH_GP7 ==> USB_A0_RT_RST_ODL */
	PAD_CFG_GPO(GPP_E16, 1, DEEP),
	/* E17 : THC0_SPI1_INT# ==> PEN_DET_ODL */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_E17, NONE, PLTRST),
	/* E19 : DDP1_CTRLDATA ==> USB0_C0_LSX_SOC_RX_STRAP */
	PAD_CFG_NF(GPP_E19, DN_20K, DEEP, NF4),
	/* E20 : DDP2_CTRLCLK ==> NC */
	PAD_NC(GPP_E20, NONE),
	/* E22 : DDPA_CTRLCLK ==> USB_C1_AUXP_DC: Retimer FW drives this pin */
	PAD_CFG_GPO(GPP_E22, 1, DEEP),
	/* E23 : DDPA_CTRLDATA ==> USB_C1_AUXN_DC: Retimer FW drives this pin */
	PAD_CFG_GPO(GPP_E23, 1, DEEP),

	/* F7  : GPPF7_STRAP */
	PAD_NC(GPP_F7, DN_20K),
	/* F11 : THC1_SPI2_CLK ==> NC */
	PAD_NC(GPP_F11, NONE),
	/* F12 : GSXDOUT ==> EN_PP3300_TRACKPAD */
	PAD_CFG_GPO(GPP_F12, 1, DEEP),
	/* F13 : GSXDOUT ==> WiFi_DISABLE_L */
	PAD_CFG_GPO(GPP_F13, 1, DEEP),
	/* F16 : GSXCLK ==> EN_PP3300_TOUCHSCREEN */
	PAD_CFG_GPO(GPP_F16, 1, DEEP),
	/* F17 : WWAN_RF_DISABLE_ODL ==> EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_F17, NONE, DEEP),
	/* F18 : THC1_SPI2_INT# ==> EN_SPKR_PA */
	PAD_CFG_GPO(GPP_F18, 1, DEEP),

	/* H0  : GPPH0_BOOT_STRAP1 */
	PAD_NC(GPP_H0, DN_20K),
	/* H1  : GPPH1_BOOT_STRAP2 */
	PAD_NC(GPP_H1, DN_20K),
	/* H2  : GPPH2_BOOT_STRAP3 */
	PAD_NC(GPP_H2, DN_20K),
	/* H3  : SX_EXIT_HOLDOFF# ==> SD_PERST_L */
	PAD_CFG_GPO(GPP_H3, 1, DEEP),
	/* H10 : SRCCLKREQ4# ==> NC */
	PAD_NC(GPP_H10, NONE),
	/* H13 : M2_SKT2_CFG1 # ==> SPKR_INT_L */
	PAD_CFG_GPI(GPP_H13, NONE, DEEP),

	/* R0 : HDA_BCLK ==> I2S0_HP_SCLK */
	PAD_CFG_NF(GPP_R0, NONE, DEEP, NF2),
	/* R1 : HDA_SYNC ==> I2S0_HP_SFRM */
	PAD_CFG_NF(GPP_R1, NONE, DEEP, NF2),
	/* R2 : HDA_SDO ==> I2S0_PCH_TX_HP_RX_STRAP */
	PAD_CFG_NF(GPP_R2, DN_20K, DEEP, NF2),
	/* R3 : HDA_SDIO ==> I2S0_PCH_RX_HP_TX */
	PAD_CFG_NF(GPP_R3, NONE, DEEP, NF2),
	/* R5 : HDA_SDI1 ==> HP_INT_L */
	PAD_CFG_GPI_INT(GPP_R5, NONE, PLTRST, EDGE_BOTH),

	/* S4 : SNDW2_CLK ==> DMIC_CLK1 */
	PAD_CFG_NF(GPP_S4, NONE, DEEP, NF2),
	/* S5 : SNDW2_DATA ==> DMIC_DATA1 */
	PAD_CFG_NF(GPP_S5, NONE, DEEP, NF2),
	/* S6 : SNDW3_CLK ==> DMIC_CLK0 */
	PAD_CFG_NF(GPP_S6, NONE, DEEP, NF2),
	/* S7 : SNDW3_DATA ==> DMIC_DATA0 */
	PAD_CFG_NF(GPP_S7, NONE, DEEP, NF2),

	/* GPD6: SLP_A# ==> NC */
	PAD_NC(GPD6, NONE),
	/* GPD9: SLP_WLAN# ==> SLP_WLAN_L */
	PAD_CFG_NF(GPD9, NONE, DEEP, NF1),
};

const struct pad_config *variant_override_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(override_gpio_table);
	return override_gpio_table;
}

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* A12 : SATAXPCIE1 ==> M2_SSD_PEDET */
	PAD_CFG_NF(GPP_A12, NONE, DEEP, NF1),
	/* A13 : PMC_I2C_SCL ==> BT_DISABLE_L */
	/* assert reset on reboot */
	PAD_CFG_GPO(GPP_A13, 0, DEEP),
	/* A17 : DDSP_HPDC ==> MEM_CH_SEL */
	PAD_CFG_GPI(GPP_A17, NONE, DEEP),

	/* B2  : VRALERT# ==> EN_PP3300_SSD */
	PAD_CFG_GPO(GPP_B2, 1, PLTRST),
	/* B11 : PMCALERT# ==> PCH_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_B11, NONE, DEEP),
	/* B15 : GSPI0_CS0# ==> PCH_GSPI0_H1_TPM_CS_L */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),
	/* B16 : GSPI0_CLK ==> PCH_GSPI0_H1_TPM_CLK */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),
	/* B17 : GSPI0_MISO ==> PCH_GSPI0_H1_TPM_MISO */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),
	/* B18 : GSPI0_MOSI ==> PCH_GSPI0_H1_TPM_MOSI_STRAP */
	PAD_CFG_NF(GPP_B18, DN_20K, DEEP, NF1),

	/* C0  : SMBCLK ==> EN_PP3300_WLAN */
	PAD_CFG_GPO(GPP_C0, 1, DEEP),
	/* C21 : UART2_TXD ==> H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_C21, NONE, PLTRST, LEVEL, INVERT),

	/* D16 : ISH_UART0_CTS# ==> EN_PP3300_SD */
	PAD_CFG_GPO(GPP_D16, 1, DEEP),

	/* E12 : SPI1_MISO_IO1 ==> PEN_ALERT_ODL */
	PAD_CFG_GPI(GPP_E12, NONE, DEEP),

	/* F17 : WWAN_RF_DISABLE_ODL ==> EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_F17, NONE, DEEP),
};

const struct pad_config *variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}
