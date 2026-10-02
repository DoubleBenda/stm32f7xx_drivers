/*
 * stm32f746_gpio_driver.c
 *
 *  Created on: 19 giu 2026
 *      Author: dario.benvegnu
 */

#include "stm32f746_gpio_driver.h"

/***************************************************************************************
* 								API functions Implementations
****************************************************************************************/

/*********************************************************************
 * @fn      		  - GPIO_PeripheralClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros

 */
void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnableOrDisable)
{
	if(EnableOrDisable ==  ENABLE)
	{
		     if(pGPIOx == GPIOA)	GPIOA_PCLK_EN();
		else if(pGPIOx == GPIOB)	GPIOB_PCLK_EN();
		else if(pGPIOx == GPIOC)	GPIOC_PCLK_EN();
		else if(pGPIOx == GPIOD)	GPIOD_PCLK_EN();
		else if(pGPIOx == GPIOE)	GPIOE_PCLK_EN();
		else if(pGPIOx == GPIOF)	GPIOF_PCLK_EN();
		else if(pGPIOx == GPIOG)	GPIOG_PCLK_EN();
		else if(pGPIOx == GPIOH)	GPIOH_PCLK_EN();
		else if(pGPIOx == GPIOI)	GPIOI_PCLK_EN();
		else if(pGPIOx == GPIOJ) 	GPIOJ_PCLK_EN();
		else if(pGPIOx == GPIOK) 	GPIOK_PCLK_EN();
	}
	else
	{
	     	  if(pGPIOx == GPIOA)	GPIOA_PCLK_DI();
	     else if(pGPIOx == GPIOB)	GPIOB_PCLK_DI();
	     else if(pGPIOx == GPIOC)	GPIOC_PCLK_DI();
	     else if(pGPIOx == GPIOD)	GPIOD_PCLK_DI();
	     else if(pGPIOx == GPIOE)	GPIOE_PCLK_DI();
	     else if(pGPIOx == GPIOF)	GPIOF_PCLK_DI();
	     else if(pGPIOx == GPIOG)	GPIOG_PCLK_DI();
	     else if(pGPIOx == GPIOH)	GPIOH_PCLK_DI();
	     else if(pGPIOx == GPIOI)	GPIOI_PCLK_DI();
	     else if(pGPIOx == GPIOJ) 	GPIOJ_PCLK_DI();
	     else if(pGPIOx == GPIOK) 	GPIOK_PCLK_DI();

	}
}

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This Function Initializes a given GPIO peripheral
 *
 * @param[in]         - handle of the gpio peripheral
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0; // temp. register

	// 1. configure the mode of the gpio pin ****************************
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// non interrupt modes
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
		pGPIOHandle->pGPIOx->MODER |= temp; // setting
	}
	else
	{
		// interrupt modes
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// 1. configure the FTSR falling trigger selection register
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clear the corresponding RTSR bit
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// 1. configure the RTSR rising trigger selection register
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clear the corresponding FTSR bit
			EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RF)
		{
			// 1. configure both FTSR and RTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		// 2. Configure the GPIO port Selection in SYSCFG_EXTICR
		uint8_t controlRegisterNumber = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t controlRegisterPosition = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN(); // Enable the clock
		SYSCFG->EXTICR[controlRegisterNumber] = portCode << (controlRegisterPosition * 4);

		// 3. Enable the EXTI interrupt delivery using the IMR (interrupt mask register)
		EXTI->IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	temp = 0;

	// 2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp; // setting

	temp = 0;

	// 3. configure the pull up / pull down settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp; // setting
	temp = 0;

	// 4. configure the output type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;

	// 5. configure the alternate functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t AFRIndex= pGPIOHandle->GPIO_PinConfig.GPIO_PinMode / 8;
		uint8_t position = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode % 8;

		pGPIOHandle->pGPIOx->AFR[AFRIndex] &= ~( 0xF << (4 * position)); // clearing
		pGPIOHandle->pGPIOx->AFR[AFRIndex] |= pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * position); // setting
	}
	temp = 0;
}

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This Function Initializes a given GPIO peripheral
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	     if(pGPIOx == GPIOA)	GPIOA_REG_RESET();
	else if(pGPIOx == GPIOB)	GPIOB_REG_RESET();
	else if(pGPIOx == GPIOC)	GPIOC_REG_RESET();
	else if(pGPIOx == GPIOD)	GPIOD_REG_RESET();
	else if(pGPIOx == GPIOE)	GPIOE_REG_RESET();
	else if(pGPIOx == GPIOF)	GPIOF_REG_RESET();
	else if(pGPIOx == GPIOG)	GPIOG_REG_RESET();
	else if(pGPIOx == GPIOH)	GPIOH_REG_RESET();
	else if(pGPIOx == GPIOI)	GPIOI_REG_RESET();
	else if(pGPIOx == GPIOJ) 	GPIOJ_REG_RESET();
	else if(pGPIOx == GPIOK) 	GPIOK_REG_RESET();
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             - This Function Reads data from a GPIO Pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - Pin Number
 *
 * @return    - 0 or 1
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             - This Function Reads all the data from a GPIO Port
 *
 * @param[in]         - base address of the gpio peripheralù
 *
 * @return            -
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             - This Function writes data to a GPIO Pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - Pin Number
 * @param[in]         - The value to be written
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		// write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= ( 0x1 << PinNumber );
	}
	else
	{
		// write 0 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR &= ~( 0x1 << PinNumber );
	}
}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             - This Function writes data to a GPIO Port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - The data to be written
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}

/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             - This Function toggles a GPIO pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - The number of the Pin to be toggled
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}


/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             - This function configures the IRQ
 *
 * @param[in]         - IRQ Number
 * @param[in]         - IRQPriority
 * @param[in]         - ENABLE or DISABLE macro
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnableOrDisable) // We could also add the parameter "IRQGrouping"
{
	if(EnableOrDisable == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if((IRQNumber > 31) && (IRQNumber < 64))
		{
			// program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if((IRQNumber >= 64) && (IRQNumber < 96))
		{
			// program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			// program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if((IRQNumber > 31) && (IRQNumber < 64))
		{
			// program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if((IRQNumber >= 64) && (IRQNumber < 96))
		{
			// program ICER2 register
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}

/*********************************************************************
 * @fn      		  - GPIO_IRQPriorityConfig
 *
 * @brief             - This function handles and IRQ
 *
 * @param[in]         - Number of the pin who caused the IRQ
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	// 1. first let's find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*( NVIC_PR_BASE_ADDR + iprx * 4 ) |= ( IRQPriority << shift_amount );


}

/*********************************************************************
 * @fn      		  - GPIO_IRQHandling
 *
 * @brief             - This function handles and IRQ
 *
 * @param[in]         - Number of the pin who caused the IRQ
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
