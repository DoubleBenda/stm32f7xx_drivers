/*
 * 001_LED_Toggle.c
 *
 *  Created on: 26 giu 2026
 *      Author: dario.benvegnu
 */

#include "stm32f746xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++)
	{

	}
}

int main(void)
{
	// Creiamo una variabile Handle per la porta GPIO che ci interessa
	GPIO_Handle_t GPIO_Led;

	// Configurazione
	GPIO_Led.pGPIOx = GPIOI;
	GPIO_Led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GPIO_Led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_Led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIO_Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_Led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Abilitiamo il clock della periferica
	GPIO_PeripheralClockControl(GPIO_Led.pGPIOx, ENABLE);
	//GPIO_PeripheralClockControl(GPIOI, ENABLE);

	// Abilitazione della Periferica GPIO
	GPIO_Init(&GPIO_Led);

	while(1)
	{
		GPIO_ToggleOutputPin(
				GPIO_Led.pGPIOx,
				GPIO_Led.GPIO_PinConfig.GPIO_PinNumber
				);

		delay();
	}


	return 0;
}
