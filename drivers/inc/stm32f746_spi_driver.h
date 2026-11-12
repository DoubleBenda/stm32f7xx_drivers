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


#endif /* INC_STM32F746_SPI_DRIVER_H_ */
