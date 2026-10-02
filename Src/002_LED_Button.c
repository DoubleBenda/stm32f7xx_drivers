/*
 * 002_LED_Button.c
 *
 *  Created on: 2 lug 2026
 *      Author: dario.benvegnu
 */

#include "stm32f746xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 50000; i++)
	{

	}
}

int main(void)
{
	// Creiamo variabili Handle per le porte GPIO che ci interessano, una per il LED e l'altra per il Bottone
	GPIO_Handle_t GPIO_Led, GPIO_Btn;

	// Configurazione LED ****************************************
	GPIO_Led.pGPIOx = GPIOI;
	GPIO_Led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GPIO_Led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_Led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIO_Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_Led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Configurazione User Button ****************************************
	GPIO_Btn.pGPIOx = GPIOI;
	GPIO_Btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;	// il bottone è connesso al pin 11 della porta GPIO I
	GPIO_Btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;		// La modalita è "Input"
	GPIO_Btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;	// non abbiamo bisogno delle resistenze di Pull Up o Pull Down

	// Abilitazione dei clock delle periferiche
	//GPIO_PeripheralClockControl(GPIO_Led.pGPIOx, ENABLE);
	GPIO_PeripheralClockControl(GPIO_Btn.pGPIOx, ENABLE); // dato che i pin che sto utilizzando sono connessi alla stessa porta GPIO basta abilitare il clock una sola volta

	// Inizializzazione delle Periferiche utilizzate
	GPIO_Init(&GPIO_Led);
	GPIO_Init(&GPIO_Btn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIO_Btn.pGPIOx, GPIO_Btn.GPIO_PinConfig.GPIO_PinNumber) == BUTTON_PRESSED)
		{
			GPIO_WriteToOutputPin(GPIO_Led.pGPIOx,GPIO_Led.GPIO_PinConfig.GPIO_PinNumber,HIGH);
		}
		else
		{
			GPIO_WriteToOutputPin(GPIO_Led.pGPIOx,GPIO_Led.GPIO_PinConfig.GPIO_PinNumber,LOW);
		}
		/*if(GPIO_ReadFromInputPin(GPIO_Btn.pGPIOx, GPIO_Btn.GPIO_PinConfig.GPIO_PinNumber) == BUTTON_PRESSED)
		{
			delay(); // introduce a little delay to debounce the button
			GPIO_ToggleOutputPin(GPIO_Led.pGPIOx,GPIO_Led.GPIO_PinConfig.GPIO_PinNumber);
		}*/
	}
	return 0;
}



