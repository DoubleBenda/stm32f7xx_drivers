/*
 * 004_spi_tx_testing.c
 *
 *  Created on: 26 nov 2026
 *      Author: drbg
 */

#include "stm32f746xx.h"
#include "stm32f746_spi_driver.h"
#include "stm32f746_gpio_driver.h"

/* Utilizziamo la periferica SPI2
 * *
 * 	PB9  : 	SPI2_NSS
 *
 * 	PB10 : 	SPI2_SCK
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

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5U;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Configure SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	GPIO_Init(&SPIPins);

	// Configure NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&SPIPins);

	// Configure MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	// Configure MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);
}

int main(void)
{
	// this function is used to initialize the GPIO Ping to behave as SPI2 Pins
	SPI_GPIO_Inits();



	return 0;
}
