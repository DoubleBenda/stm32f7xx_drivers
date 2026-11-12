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

}

/*
* Init and De-Init
*/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{

}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}

/*
* Data Send and Receive
*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t lenght)
{

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
