/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "registers.h"

/* CRU_CLKSEL25_CON */
#define SPI0_PLL_SHIFT          7
#define SPI0_PLL_MASK           1 << SPI0_PLL_SHIFT
#define SPI0_PLL_SELECT_GENERAL 1
#define SPI0_DIV_SHIFT          0
#define SPI0_DIV_MASK           0x7f << SPI0_DIV_SHIFT

/* CRU_CLKSEL39_CON */
#define SPI2_PLL_SHIFT          7
#define SPI2_PLL_MASK           1 << SPI2_PLL_SHIFT
#define SPI2_PLL_SELECT_GENERAL 1
#define SPI2_DIV_SHIFT          0
#define SPI2_DIV_MASK           0x7f << SPI2_DIV_SHIFT

/* CTRLR0 */
enum {
	DFS_SHIFT	= 0,	/* Data Frame Size */
	DFS_MASK	= 3,
	DFS_4BIT	= 0,
	DFS_8BIT,
	DFS_16BIT,
	DFS_RESV,

	CFS_SHIFT	= 2,	/* Control Frame Size */
	CFS_MASK	= 0xf,

	SCPH_SHIFT	= 6,	/* Serial Clock Phase */
	SCPH_MASK	= 1,
	SCPH_TOGMID	= 0,	/* SCLK toggles in middle of first data bit */
	SCPH_TOGSTA,		/* SCLK toggles at start of first data bit */

	SCOL_SHIFT	= 7,	/* Serial Clock Polarity */
	SCOL_MASK	= 1,
	SCOL_LOW	= 0,	/* Inactive state of serial clock is low */
	SCOL_HIGH,		/* Inactive state of serial clock is high */

	CSM_SHIFT	= 8,	/* Chip Select Mode */
	CSM_MASK	= 0x3,
	CSM_KEEP	= 0,	/* ss_n stays low after each frame  */
	CSM_HALF,		/* ss_n high for half sclk_out cycles */
	CSM_ONE,		/* ss_n high for one sclk_out cycle */
	CSM_RESV,

	SSN_DELAY_SHIFT	= 10,	/* SSN to Sclk_out delay */
	SSN_DELAY_MASK	= 1,
	SSN_DELAY_HALF	= 0,	/* 1/2 sclk_out cycle */
	SSN_DELAY_ONE	= 1,	/* 1 sclk_out cycle */

	SEM_SHIFT	= 11,	/* Serial Endian Mode */
	SEM_MASK	= 1,
	SEM_LITTLE	= 0,	/* little endian */
	SEM_BIG,		/* big endian */

	FBM_SHIFT	= 12,	/* First Bit Mode */
	FBM_MASK	= 1,
	FBM_MSB		= 0,	/* first bit is MSB */
	FBM_LSB,		/* first bit in LSB */

	HALF_WORD_TX_SHIFT = 13,	/* Byte and Halfword Transform */
	HALF_WORD_MASK	= 1,
	HALF_WORD_ON	= 0,	/* apb 16bit write/read, spi 8bit write/read */
	HALF_WORD_OFF,		/* apb 8bit write/read, spi 8bit write/read */

	RXDSD_SHIFT	= 14,	/* Rxd Sample Delay, in cycles */
	RXDSD_MASK	= 3,

	FRF_SHIFT	= 16,	/* Frame Format */
	FRF_MASK	= 3,
	FRF_SPI		= 0,	/* Motorola SPI */
	FRF_SSP,			/* Texas Instruments SSP*/
	FRF_MICROWIRE,		/* National Semiconductors Microwire */
	FRF_RESV,

	TMOD_SHIFT	= 18,	/* Transfer Mode */
	TMOD_MASK	= 3,
	TMOD_TR		= 0,	/* xmit & recv */
	TMOD_TO,		/* xmit only */
	TMOD_RO,		/* recv only */
	TMOD_RESV,

	OMOD_SHIFT	= 20,	/* Operation Mode */
	OMOD_MASK	= 1,
	OMOD_MASTER	= 0,	/* Master Mode */
	OMOD_SLAVE,		/* Slave Mode */
};

/* SR */
enum {
	SR_MASK		= 0x7f,
	SR_BUSY		= 1 << 0,
	SR_TF_FULL	= 1 << 1,
	SR_TF_EMPT	= 1 << 2,
	SR_RF_EMPT	= 1 << 3,
	SR_RF_FULL	= 1 << 4,
};

#define ROCKCHIP_SPI_TIMEOUT_MS		1000

/*
 * We limit the maximum bitrate to 50MBit/s (50MHz) due to an assumed
 * hardware limitation...  the Linux kernel source has the following
 * comment:
 *   "sclk_out: spi master internal logic in rk3x can support 50Mhz"
 */
#define ROCKCHIP_SPI_MAX_RATE		50000000

void ssd1306_test( void );

#endif
