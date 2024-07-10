/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <types.h>
#include <vendorcode/google/chromeos/chromeos.h>

/* Pad configuration in ramstage */
/* Leave eSPI pins untouched from default settings */
static const struct pad_config gpio_table[] = {
/* RCIN# */		PAD_NC(GPP_A0, NONE), /* TP308 */
/* ESPI_IO0 */
/* ESPI_IO1 */
/* ESPI_IO2 */
/* ESPI_IO3 */
/* ESPI_CS# */
/* SERIRQ */		PAD_NC(GPP_A6, NONE), /* TP331 */
/* PIRQA# */		PAD_CFG_GPI_INT(GPP_A7, UP_20K, DEEP,
					EDGE_SINGLE), /* SD_CDZ */
/* CLKRUN# */		PAD_NC(GPP_A8, NONE), /* TP329 */
/* ESPI_CLK */
/* CLKOUT_LPC1 */	PAD_NC(GPP_A10, NONE), /* TP188 */
/* PME# */		PAD_NC(GPP_A11, NONE), /* TP149 */
/* BM_BUSY# */		PAD_NC(GPP_A12, NONE),
/* SUSWARN# */		PAD_CFG_GPI_GPIO_DRIVER(GPP_A13, NONE,
						DEEP), /* eSPI mode */
/* ESPI_RESET# */
/* SUSACK# */		PAD_NC(GPP_A15, NONE), /* TP150 */
/* SD_1P8_SEL */	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),
/* SD_PWR_EN# */	PAD_CFG_NF(GPP_A17, NONE, DEEP, NF1),
/* ISH_GP0 */		PAD_CFG_GPO(GPP_A18, 0, DEEP), /* 7322_OE */
/* ISH_GP1 */		PAD_CFG_GPI_GPIO_DRIVER(GPP_A19, NONE, DEEP), /* HDPO */
/* ISH_GP2 */		PAD_NC(GPP_A20, NONE),
/* ISH_GP3 */		PAD_NC(GPP_A21, NONE),
/* ISH_GP4 */		PAD_NC(GPP_A22, NONE),
/* ISH_GP5 */		PAD_NC(GPP_A23, NONE),

/* CORE_VID0 */		PAD_NC(GPP_B0, NONE), /* TP156 */
/* CORE_VID1 */		PAD_NC(GPP_B1, NONE),
/* VRALERT# */		PAD_NC(GPP_B2, NONE), /* TP152 */
/* CPU_GP2 */		PAD_NC(GPP_B3, NONE),
/* CPU_GP3 */		PAD_NC(GPP_B4, NONE),
/* SRCCLKREQ0# */	PAD_CFG_NF(GPP_B5, NONE, DEEP,
				   NF1), /* CLK_PCIE_LAN_REQ# */
/* SRCCLKREQ1# */	PAD_CFG_NF(GPP_B6, NONE, DEEP,
				   NF1), /* PCIE_CLKREQ_SSD# */
/* SRCCLKREQ2# */	PAD_CFG_NF(GPP_B7, NONE, DEEP,
				   NF1), /* PCIE_CLKREQ_NGFF1# */
/* SRCCLKREQ3# */	PAD_NC(GPP_B8, NONE), /* TP333 */
/* SRCCLKREQ4# */	PAD_NC(GPP_B9, NONE), /* TP139 */
/* SRCCLKREQ5# */	PAD_CFG_NF(GPP_B10, NONE, DEEP,
				   NF1), /* PCIE_CLKREQ_WLAN# */
/* EXT_PWR_GATE# */	PAD_CFG_NF(GPP_B11, NONE, DEEP, NF1), /* MPHY_EXT_PWR */
/* SLP_S0# */		PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1), /* PM_SLP_S0# */
/* PLTRST# */		PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1), /* PCI_PLTRST# */
/* SPKR */		PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1), /* SPKR */
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CS_L */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CLK */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MISO */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MOSI */
/* GSPI1_CS# */		PAD_NC(GPP_B19, NONE), /* TP111 */
/* GSPI1_CLK */		PAD_CFG_GPI_GPIO_DRIVER(GPP_B20, UP_20K,
						DEEP), /* VR_DISABLE_L */
/* GSPI1_MISO */	PAD_CFG_GPI_GPIO_DRIVER(GPP_B21, UP_20K,
						DEEP), /* HWA_TRST_N */
/* GSPI1_MOSI */	PAD_NC(GPP_B22, NONE), /* GSPI1_MOSI */
/* SML1ALERT# */	PAD_NC(GPP_B23, NONE), /* TP141 */

/* SMBCLK */		PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1), /* PCH_MBCLK0_R */
/* SMBDATA */		PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1), /* PCH_MBDAT0_R */
/* SMBALERT# */		PAD_NC(GPP_C2, NONE),
/* SML0CLK */		PAD_NC(GPP_C3, NONE),
/* SML0DATA */		PAD_NC(GPP_C4, NONE),
/* SML0ALERT# */	PAD_CFG_NF(GPP_C5, NONE, DEEP, NF1),
/* SM1CLK */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C6, UP_20K,
						DEEP), /* EC_IN_RW */
/* SM1DATA */		PAD_NC(GPP_C7, NONE), /* TP310 */
/* UART0_RXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C8, UP_20K,
							DEEP), /* GPIO1 */
/* UART0_TXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C9, UP_20K,
							DEEP), /* GPIO2 */
/* UART0_RTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C10, UP_20K,
						DEEP), /* GPIO3 */
/* UART0_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C11, UP_20K,
						DEEP), /* GPIO4 */
/* UART1_RXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C12, NONE,
							DEEP), /* SKU_ID0 */
/* UART1_TXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C13, NONE,
							DEEP), /* SKU_ID1 */
/* UART1_RTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C14, NONE,
						DEEP), /* SKU_ID2 */
/* UART1_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C15, NONE,
						DEEP), /* SKU_ID3 */
/* I2C0_SDA */		PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),
/* I2C0_SCL */		PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),
/* I2C1_SDA */		PAD_NC(GPP_C18, NONE),
/* I2C1_SCL */		PAD_NC(GPP_C19, NONE),
/* UART2_RXD */		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), /* SERVO */
/* UART2_TXD */		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), /* SERVO */
/* UART2_RTS# */	PAD_NC(GPP_C22, NONE), /* TP309 */
/* UART2_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C23, NONE,
				    DEEP), /* SCREW_SPI_WP_STATUS */

/* SPI1_CS# */		PAD_NC(GPP_D0, NONE), /* TP259 */
/* SPI1_CLK */		PAD_NC(GPP_D1, NONE), /* TP260 */
/* SPI1_MISO */		PAD_NC(GPP_D2, NONE), /* TP261 */
/* SPI1_MOSI */		PAD_NC(GPP_D3, NONE), /* TP262 */
/* FASHTRIG */		PAD_NC(GPP_D4, NONE), /* TP153 */
/* ISH_I2C0_SDA */	PAD_NC(GPP_D5, NONE),
/* ISH_I2C0_SCL */	PAD_NC(GPP_D6, NONE),
/* ISH_I2C1_SDA */	PAD_NC(GPP_D7, NONE),
/* ISH_I2C1_SCL */	PAD_NC(GPP_D8, NONE),
/* ISH_SPI_CS# */	PAD_CFG_GPI_INT(GPP_D9, NONE,
					PLTRST, EDGE_SINGLE), /* HP_IRQ_GPIO */
/* ISH_SPI_CLK */	PAD_CFG_GPI_GPIO_DRIVER(GPP_D10, NONE,
						DEEP), /* OEM_ID1 */
/* ISH_SPI_MISO */	PAD_CFG_GPI_GPIO_DRIVER(GPP_D11, NONE,
						DEEP), /* OEM_ID2 */
/* ISH_SPI_MOSI */	PAD_CFG_GPI_GPIO_DRIVER(GPP_D12, NONE,
						DEEP), /* OEM_ID3 */
/* ISH_UART0_RXD */	PAD_NC(GPP_D13, NONE),
/* ISH_UART0_TXD */	PAD_NC(GPP_D14, NONE),
/* ISH_UART0_RTS# */	PAD_NC(GPP_D15, NONE),
/* ISH_UART0_CTS# */	PAD_NC(GPP_D16, NONE),
/* DMIC_CLK1 */		PAD_NC(GPP_D17, NONE),
/* DMIC_DATA1 */	PAD_NC(GPP_D18, NONE),
/* DMIC_CLK0 */		PAD_NC(GPP_D19, NONE), /* TP121 */
/* DMIC_DATA0 */	PAD_NC(GPP_D20, NONE), /* TP122 */
/* SPI1_IO2 */		PAD_NC(GPP_D21, NONE), /* TP257 */
/* SPI1_IO3 */		PAD_NC(GPP_D22, NONE), /* TP258 */
/* I2S_MCLK */		PAD_CFG_NF(GPP_D23, NONE, DEEP, NF1), /* I2S_MCLK */

/* SATAXPCI0 */		PAD_CFG_GPI_APIC(GPP_E0, NONE, PLTRST, LEVEL,
					 INVERT), /* H1_PCH_INT_ODL */
/* SATAXPCIE1 */	PAD_CFG_NF(GPP_E1, NONE, DEEP,
				   NF1), /* MB_PCIE_SATA#_DET */
/* SATAXPCIE2 */	PAD_CFG_NF(GPP_E2, UP_20K, DEEP,
				   NF1), /* DB_PCIE_SATA#_DET */
/* CPU_GP0 */		PAD_NC(GPP_E3, NONE),
/* SATA_DEVSLP0 */	PAD_NC(GPP_E4, NONE), /* TP103 */
/* SATA_DEVSLP1 */	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1), /* DEVSLP1_MB */
/* SATA_DEVSLP2 */	PAD_NC(GPP_E6, NONE), /* DEVSLP2_DB */
/* CPU_GP1 */		PAD_NC(GPP_E7, NONE),
/* SATALED# */		PAD_NC(GPP_E8, NONE), /* TP314 */
/* USB2_OCO# */		PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1), /* USB-C */
/* USB2_OC1# */		PAD_CFG_NF(GPP_E10, NONE, DEEP,
					NF1), /* Rear Dual-Stack USB Ports */
/* USB2_OC2# */		PAD_CFG_NF(GPP_E11, NONE, DEEP,
					   NF1), /* Front USB Ports */
/* USB2_OC3# */		PAD_CFG_NF(GPP_E12, NONE, DEEP,
					   NF1), /* Rear Single USB Port */
/* DDPB_HPD0 */		PAD_CFG_NF(GPP_E13, NONE, DEEP,
					   NF1), /* INT_HDMI_HPD */
/* DDPC_HPD1 */		PAD_CFG_NF(GPP_E14, NONE, DEEP,
					   NF1), /* DDI2_HPD */
/* DDPD_HPD2 */		PAD_NC(GPP_E15, NONE), /* TP325 */
/* DDPE_HPD3 */		PAD_NC(GPP_E16, NONE), /* TP326 */
/* EDP_HPD */		PAD_CFG_NF(GPP_E17, NONE, DEEP, NF1),
/* DDPB_CTRLCLK */	PAD_CFG_NF(GPP_E18, NONE, DEEP,
				   NF1), /* HDMI_DDCCLK_SW */
/* DDPB_CTRLDATA */	PAD_CFG_NF(GPP_E19, DN_20K, DEEP,
				   NF1), /* HDMI_DDCCLK_DATA */
/* DDPC_CTRLCLK */	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF1), /* CRT CLK */
/* DDPC_CTRLDATA */	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF1), /* CRT DATA */
/* DDPD_CTRLCLK */	PAD_NC(GPP_E22, NONE),
/* DDPD_CTRLDATA */	PAD_NC(GPP_E23, NONE),

/* I2S2_SCLK */		PAD_NC(GPP_F0, NONE), /* TP191 */
/* I2S2_SFRM */		PAD_NC(GPP_F1, NONE), /* TP192 */
/* I2S2_TXD */		PAD_NC(GPP_F2, NONE), /* TP190 */
/* I2S2_RXD */		PAD_NC(GPP_F3, NONE), /* TP189 */
/* I2C2_SDA */		PAD_CFG_NF(GPP_F4, NONE, DEEP,
				   NF1), /* PCH_I2C2_H1_3V3_SDA */
/* I2C2_SCL */		PAD_CFG_NF(GPP_F5, NONE, DEEP,
				   NF1), /* PCH_I2C2_H1_3V3_SCL */
/* I2C3_SDA */		PAD_NC(GPP_F6, NONE),
/* I2C3_SCL */		PAD_NC(GPP_F7, NONE),
/* I2C4_SDA */		PAD_NC(GPP_F8, NONE),
/* I2C4_SCL */		PAD_NC(GPP_F9, NONE),
/* I2C5_SDA */		PAD_CFG_NF_1V8(GPP_F10, NONE, DEEP,
				       NF1), /* PCH_I2C2_AUDIO_1V8_SDA */
/* I2C5_SCL */		PAD_CFG_NF_1V8(GPP_F11, NONE, DEEP,
				       NF1), /* PCH_I2C2_AUDIO_1V8_SCL */
/* EMMC_CMD */		PAD_NC(GPP_F12, NONE),
/* EMMC_DATA0 */	PAD_NC(GPP_F13, NONE),
/* EMMC_DATA1 */	PAD_NC(GPP_F14, NONE),
/* EMMC_DATA2 */	PAD_NC(GPP_F15, NONE),
/* EMMC_DATA3 */	PAD_NC(GPP_F16, NONE),
/* EMMC_DATA4 */	PAD_NC(GPP_F17, NONE),
/* EMMC_DATA5 */	PAD_NC(GPP_F18, NONE),
/* EMMC_DATA6 */	PAD_NC(GPP_F19, NONE),
/* EMMC_DATA7 */	PAD_NC(GPP_F20, NONE),
/* EMMC_RCLK */		PAD_NC(GPP_F21, NONE),
/* EMMC_CLK */		PAD_NC(GPP_F22, NONE),
/* RSVD */		PAD_NC(GPP_F23, NONE),

/* SD_CMD */		PAD_CFG_NF(GPP_G0, NONE, DEEP, NF1),
/* SD_DATA0 */		PAD_CFG_NF(GPP_G1, NONE, DEEP, NF1),
/* SD_DATA1 */		PAD_CFG_NF(GPP_G2, NONE, DEEP, NF1),
/* SD_DATA2 */		PAD_CFG_NF(GPP_G3, NONE, DEEP, NF1),
/* SD_DATA3 */		PAD_CFG_NF(GPP_G4, NONE, DEEP, NF1),
/* SD_CD# */		PAD_CFG_NF(GPP_G5, NONE, DEEP, NF1), /* SD_CDZ */
/* SD_CLK */		PAD_CFG_NF(GPP_G6, NONE, DEEP, NF1),
/* SD_WP */		PAD_NC(GPP_G7, NONE), /* TP292 */

/* BATLOW# */		PAD_NC(GPD0, NONE), /* TP148 */
/* ACPRESENT */		PAD_CFG_NF(GPD1, NONE, DEEP, NF1), /* PCH_ACPRESENT */
/* LAN_WAKE# */		PAD_CFG_NF(GPD2, NONE, DEEP, NF1), /* EC_PCH_WAKE# */
/* PWRBTN# */		PAD_CFG_NF(GPD3, UP_20K, DEEP, NF1), /* PCH_PWRBTN# */
/* SLP_S3# */		PAD_CFG_NF(GPD4, NONE, DEEP, NF1), /* PM_SLP_S3# */
/* SLP_S4# */		PAD_CFG_NF(GPD5, NONE, DEEP, NF1), /* PM_SLP_S4# */
/* SLP_A# */		PAD_NC(GPD6, NONE), /* TP147 */
/* RSVD */		PAD_NC(GPD7, NONE),
/* SUSCLK */		PAD_CFG_NF(GPD8, NONE, DEEP, NF1), /* SUS_CLK */
/* SLP_WLAN# */		PAD_NC(GPD9, NONE), /* TP146 */
/* SLP_S5# */		PAD_NC(GPD10, NONE), /* TP143 */
/* LANPHYC */		PAD_NC(GPD11, NONE),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CS_L */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CLK */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MISO */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MOSI */
/* SATAXPCI0 */		PAD_CFG_GPI_APIC(GPP_E0, NONE, PLTRST, LEVEL,
					 INVERT), /* H1_PCH_INT_ODL */
/* Ensure UART pins are in native mode for H1. */
/* UART2_RXD */		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), /* SERVO */
/* UART2_TXD */		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), /* SERVO */
/* UART2_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C23, NONE,
				    DEEP), /* SCREW_SPI_WP_STATUS */
/* SATAXPCIE1 */       PAD_CFG_NF(GPP_E1, NONE, DEEP,
				  NF1), /* MB_PCIE_SATA#_DET */
/* SATA_DEVSLP1 */     PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1), /* DEVSLP1_MB */

/* SM1CLK */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C6, UP_20K,
						DEEP), /* EC_IN_RW */
};

const struct pad_config * __weak variant_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

const struct pad_config * __weak
	variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_DEVICE_NAME),
	CROS_GPIO_WP_AH(GPIO_PCH_WP, CROS_GPIO_DEVICE_NAME),
};

DECLARE_WEAK_CROS_GPIOS(cros_gpios);
