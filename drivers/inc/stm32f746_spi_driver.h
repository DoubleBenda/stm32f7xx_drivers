/*
 * stm32f746_spi_driver.h
 *
 *  Created on: 12 nov 2026
 *      Author: drbg
 */

#ifndef INC_STM32F746_SPI_DRIVER_H_
#define INC_STM32F746_SPI_DRIVER_H_

#include "stm32f746xx.h"

/*
 * Configuration Structure For SPIx peripheral
 * */
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

/*
 * Handle Structure for SPIx peripheral
 * */
typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPIConfig;
}SPI_Handle_t;

/*
 * @SPI Device Mode
 * */
#define SPI_DEVICE_MODE_MASTER 	1
#define SPI_DEVICE_MODE_SLAVE 	0

/*
 * @SPI Bus Config
 * */
#define SPI_BUS_CONFIG_FULLDUPLEX		1
#define SPI_BUS_CONFIG_HALFDUPLEX		2
#define SPI_BUS_CONFIG_SIMPLEX_TXONLY	3
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	4

/*
 * @SPI Clock Speed
 * */
#define SPI_SCLK_SPEED_DIV_2			0
#define SPI_SCLK_SPEED_DIV_4			1
#define SPI_SCLK_SPEED_DIV_8			2
#define SPI_SCLK_SPEED_DIV_16			3
#define SPI_SCLK_SPEED_DIV_32			4
#define SPI_SCLK_SPEED_DIV_64			5
#define SPI_SCLK_SPEED_DIV_128			6
#define SPI_SCLK_SPEED_DIV_256			7

/*
 * @SPI Data Frame Format
 * */
#define SPI_DFF_8BITS 	0
#define SPI_DFF_16BITS	1

/*
 * @SPI Clock Polarity
 * */
#define SPI_CPOL_HIGH 	1
#define SPI_CPOL_LOW 	0

/*
 * @SPI Clock Phase
 * */
#define SPI_CPHA_HIGH 	1
#define SPI_CPHA_LOW 	0

/*
 * @SPI Slave Select Management
 * */
#define SPI_SSM_HW 		1
#define SPI_SSM_SW		0

/***************************************************************************************
* 								API functions Definitions
****************************************************************************************/

/*
* Peripheral Clock Setup
*/
void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx, uint8_t EnableOrDisable);

/*
* Init and De-Init
*/
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
* Data Send and Receive
*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t lenght);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t lenght);

/*
* IRQ Configuration and ISR Handling
*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnableOrDisable);// We could also add the parameter "IRQGrouping"
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

#endif /* INC_STM32F746_SPI_DRIVER_H_ */
