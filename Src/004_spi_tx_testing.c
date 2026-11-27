/*
 * 004_spi_tx_testing.c
 *
 *  Created on: 26 nov 2026
 *      Author: drbg
 */

#include "stm32f746xx.h"
#include <string.h>

/* Utilizziamo la periferica SPI2
 * *
 * 	PI0  : 	SPI2_NSS
 *
 * 	PI1 : 	SPI2_SCK
 *
 * 	PB14 : 	SPI2_MISO
 *
 *	PB15 : 	SPI2_MOSI
 *
 *	ALT Function Mode : 5
 *
 *	Questa non è l'unica possibile configurazione, si potrebbero usare anche altri pin.
 *	ho deciso di utilizzare questi per occupare una sola porta GPIO
 *
*/

void SPI_GPIO_Inits()
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOI;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5U;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Configure SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GPIO_Init(&SPIPins);

	// Configure NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIO_Init(&SPIPins);

	SPIPins.pGPIOx = GPIOB;

	// Configure MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	// Configure MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);
}

void SPI2_Inits()
{
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.BusConfig = SPI_BUS_CONFIG_FULLDUPLEX;
	SPI2Handle.SPIConfig.DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SclkSpeed = SPI_SCLK_SPEED_DIV_2; // generate serial clock of 8 MHz
	SPI2Handle.SPIConfig.DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SSM = SPI_SSM_DI;

	SPI_Init(&SPI2Handle);
}

int main(void)
{
	char user_data[] = "Hello Woorld";

	// this function is used to initialize the GPIO Ping to behave as SPI2 Pins
	SPI_GPIO_Inits();

	SPI2_Inits();
	SPI2->CR2 |= (1U << SPI_CR2_SSOE) | (1U << SPI_CR2_NSSP);

	// Enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2, ENABLE);

	while(1)
	{
		SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));
	}

	return 0;
}
