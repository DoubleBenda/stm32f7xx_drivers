/*
 * stm32f746_gpio_driver.h
 *
 *  Created on: 19 giu 2026
 *      Author: dario.benvegnu
 *
 *      This is the header file for the GPIO driver specific data
 */

#ifndef INC_STM32F746_GPIO_DRIVER_H_
#define INC_STM32F746_GPIO_DRIVER_H_

#include "stm32f746xx.h"

/*
* This is the Configuration Structure for a GPIO Pin
*/
typedef struct
{
	uint8_t GPIO_PinNumber;			/*!< Possible values from @GPIO_PIN_NUMBERS >*/
	uint8_t GPIO_PinMode;			/*!< Possible values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed;			/*!< Possible values from @GPIO_PIN_SPEEDS >*/
	uint8_t GPIO_PinPuPdControl;	/*!< Possible values from @GPIO_PIN_PULL_UP_PULL_DOWN_CONFIGURATION >*/
	uint8_t GPIO_PinOPType;			/*!< Possible values from @GPIO_PIN_OUTPUT_TYPES >*/
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

/*
* This is the Handle Structure for a GPIO Pin
*/
typedef struct
{
	GPIO_RegDef_t *pGPIOx; /* This holds the base address of the GPIO Port to which the pin belongs*/
	GPIO_PinConfig_t GPIO_PinConfig; /* THis holds GPIO pin Configuration Settings */
}GPIO_Handle_t;

/**
 * @GPIO_PIN_NUMBERS
 * GPIO Pin Possible Modes
 */
#define GPIO_PIN_NO_0 					0
#define GPIO_PIN_NO_1 					1
#define GPIO_PIN_NO_2 					2
#define GPIO_PIN_NO_3 					3
#define GPIO_PIN_NO_4 					4
#define GPIO_PIN_NO_5 					5
#define GPIO_PIN_NO_6 					6
#define GPIO_PIN_NO_7 					7
#define GPIO_PIN_NO_8 					8
#define GPIO_PIN_NO_9 					9
#define GPIO_PIN_NO_10 					10
#define GPIO_PIN_NO_11					11
#define GPIO_PIN_NO_12					12
#define GPIO_PIN_NO_13					13
#define GPIO_PIN_NO_14					14
#define GPIO_PIN_NO_15 					15

/**
 * @GPIO_PIN_MODES
 * GPIO Pin Possible Modes
 */
#define GPIO_MODE_IN 					0	/* GPIO pin input mode */
#define GPIO_MODE_OUT					1	/* GPIO pin output mode */
#define GPIO_MODE_ALTFN 				2	/* GPIO pin alternate function mode */
#define GPIO_MODE_ANALOG				3	/* GPIO pin analog mode */
#define GPIO_MODE_IT_FT					4	/* Interrupt Mode Falling Edge */
#define GPIO_MODE_IT_RT					5	/* Interrupt Mode Rising Edge */
#define GPIO_MODE_IT_RF					6	/* Interrupt Mode Rising/Falling Edge */

/**
 * @GPIO_PIN_OUTPUT_TYPES
 * GPIO Pin Possible Modes
 */
#define GPIO_OP_TYPE_PP					0	/* Gpio output type push pull */
#define GPIO_OP_TYPE_OD					1	/* Gpio output type open drain */

/**
 * @GPIO_PIN_SPEEDS
 * GPIO Pin Possible Output Speeds
 */
#define GPIO_SPEED_LOW 					0
#define GPIO_SPEED_MEDIUM				1
#define GPIO_SPEED_FAST 				2
#define GPIO_SPEED_HIGH 				3

/**
 * @GPIO_PIN_PULL_UP_PULL_DOWN_CONFIGURATION
 * GPIO Pin Possible Pull Up and Pull Down configurations
 */
#define GPIO_NO_PUPD					0 	/* GPIO no pull up / pull down */
#define GPIO_PIN_PU						1 	/* GPIO pull up */
#define GPIO_PIN_PD						2 	/* GPIO pull down */

/***************************************************************************************
* 								API functions Definitions
****************************************************************************************/

/*
* Peripheral Clock Setup
*/
void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnableOrDisable);

/*
* Init and De-Init
*/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
* Data read and write
*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t values);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
* IRQ Configuration and ISR Handling
*/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnableOrDisable);// We could also add the parameter "IRQGrouping"
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32F746_GPIO_DRIVER_H_ */
