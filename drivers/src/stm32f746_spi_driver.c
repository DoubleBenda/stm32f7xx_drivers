/*
 * stm32f746_spi_driver.c
 *
 *  Created on: 12 nov 2026
 *      Author: drbg
 */

#include "stm32f746_spi_driver.h"

/*
* Peripheral Clock Setup
*/
void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx, uint8_t EnableOrDisable)
{
	if(EnableOrDisable ==  ENABLE)
	{
		     if(pSPIx == SPI1)	SPI1_PCLK_EN();
		else if(pSPIx == SPI2)	SPI2_PCLK_EN();
		else if(pSPIx == SPI3)	SPI3_PCLK_EN();
		else if(pSPIx == SPI4)	SPI4_PCLK_EN();
		else if(pSPIx == SPI5)	SPI5_PCLK_EN();
		else if(pSPIx == SPI6)	SPI6_PCLK_EN();
	}
	else
	{
	     	 if(pSPIx == SPI1)	SPI1_PCLK_DI();
	    else if(pSPIx == SPI2)	SPI2_PCLK_DI();
		else if(pSPIx == SPI3)	SPI3_PCLK_DI();
		else if(pSPIx == SPI4)	SPI4_PCLK_DI();
		else if(pSPIx == SPI5)	SPI5_PCLK_DI();
		else if(pSPIx == SPI6)	SPI6_PCLK_DI();
	}
}


/*
* Init and De-Init
*/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// first lets configure the SPI_CR1 register
	uint32_t tempregCR1 = 0;
	uint32_t tempregCR2 = 0;

	//1. configure the device mode
	tempregCR1 |= pSPIHandle->SPIConfig.DeviceMode << SPI_CR1_MSTR;

	//2 configure the bus
	if(pSPIHandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_FULLDUPLEX)
	{
		// bidi mode should be cleared
		tempregCR1 &= ~(1U << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_HALFDUPLEX)
	{
		// bidi mode should be set
		tempregCR1 |= (1U << SPI_CR1_BIDIMODE);
		tempregCR1 |= (1U << SPI_CR1_BIDIOE);
	}
	else if(pSPIHandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		// bidi mode should be cleared
		// RXOnly Bit must be set
		tempregCR1 &= ~(1U << SPI_CR1_BIDIMODE);
		tempregCR1 |= (1U << SPI_CR1_RXONLY);
	}
	/*else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_TXONLY)
	{
		// bidi mode should be cleared
		// TXOnly Bit must be cleared
		tempreg &= ~(1 << 15);
		tempreg |= (1 << 10);
	}*/
	tempregCR1 |= pSPIHandle->SPIConfig.CPHA << SPI_CR1_CPHA;
	tempregCR1 |= pSPIHandle->SPIConfig.CPOL << SPI_CR1_CPOL;
	tempregCR1 |= (uint32_t)pSPIHandle->SPIConfig.SSM << SPI_CR1_SSM;
	tempregCR1 |= pSPIHandle->SPIConfig.SclkSpeed << SPI_CR1_BR;

	if ((pSPIHandle->SPIConfig.SSM == SPI_SSM_EN) &&
	    (pSPIHandle->SPIConfig.DeviceMode == SPI_DEVICE_MODE_MASTER))
	{
	    tempregCR1 |= (1U << SPI_CR1_SSI);
	}

	tempregCR2 |= pSPIHandle->SPIConfig.DFF << SPI_CR2_DS;
	if (pSPIHandle->SPIConfig.DFF <= SPI_DFF_8BITS)
	{
	    tempregCR2 |= (1U << SPI_CR2_FRXTH);
	}

	pSPIHandle->pSPIx->CR1 = tempregCR1;
	pSPIHandle->pSPIx->CR2 = tempregCR2;

}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	     if(pSPIx == SPI1)	SPI1_REG_RESET();
	else if(pSPIx == SPI2)	SPI2_REG_RESET();
	else if(pSPIx == SPI3)	SPI3_REG_RESET();
	else if(pSPIx == SPI4)	SPI4_REG_RESET();
	else if(pSPIx == SPI5)	SPI5_REG_RESET();
	else if(pSPIx == SPI6)	SPI6_REG_RESET();
}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/*
* Data Send and Receive
*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t lenght)
{
	// Blocking Call

	//2. Check the Data Size fields in CR2
	uint8_t dataSize = (uint8_t)((pSPIx->CR2 >> 8U) & 0xFU);
	if ((dataSize > 7U) && ((lenght & 1U) != 0U))
	{
	    return;
	}

	uint16_t data = 0U;

	while(lenght > 0)
	{
		//1. Wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		if(dataSize > 7U)
		{
			data = (uint16_t)((uint16_t)pTxBuffer[1] << 8U)
					| (uint16_t)pTxBuffer[0];

			//*((volatile uint16_t*)&pSPIx->DR) = data;
			pSPIx->DR = data;

			pTxBuffer += 2;
			lenght -= 2;
		}
		else
		{
			*((volatile uint8_t*)&pSPIx->DR) = *pTxBuffer;
			pTxBuffer++;
			lenght--;
		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t lenght)
{

}

/*
* IRQ Configuration and ISR Handling
*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnableOrDisable)
{

}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

}

void SPI_IRQHandling(SPI_Handle_t *pHandle)
{

}
