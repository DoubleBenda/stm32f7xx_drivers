/*
* stm32f746xx.h
*
* Created on: 12 giu 2026
* Author: dario.benvegnu
*	This is the MCU Specific Header file, it containts all the specific data for our MCU
*/

#ifndef INC_STM32F746XX_H_
#define INC_STM32F746XX_H_

#include <stdint.h>

/**************************************** CPU SPECIFIC DETAILS *******************************************************************************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx / NVIC ICERx register Addresses
 */
#pragma region CPU_SPECIFIC_DETAILS

#define NVIC_ISER0 				((volatile uint32_t*) 0xE000E100)
#define NVIC_ISER1 				((volatile uint32_t*) 0xE000E104)
#define NVIC_ISER2 				((volatile uint32_t*) 0xE000E108)
#define NVIC_ISER3 				((volatile uint32_t*) 0xE000E10C)

#define NVIC_ICER0 				((volatile uint32_t*) 0xE000E180)
#define NVIC_ICER1 				((volatile uint32_t*) 0xE000E184)
#define NVIC_ICER2 				((volatile uint32_t*) 0xE000E188)
#define NVIC_ICER3 				((volatile uint32_t*) 0xE000E18C)

#define NVIC_PR_BASE_ADDR   	((volatile uint32_t*) 0xE000E400)

# define NO_PR_BITS_IMPLEMENTED 4

#pragma endregion
/**************************************** CPU SPECIFIC DETAILS *******************************************************************************************/

// Utility Macros
#define ENABLE      1
#define DISABLE     0
#define SET         ENABLE
#define RESET       DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET
#define HIGH ENABLE
#define LOW DISABLE
#define BUTTON_PRESSED HIGH
#define BUTTON_NOT_PRESSED LOW

/*
* Definizione degli indirizzi base delle porzioni di memoria
*/
#define FLASH_BASEADDR 0x08000000U /* Indirizzo base della Memoria Flash */
#define SRAM1_BASEADDR 0x20010000U /* Indirizzo base della Memoria SRAM 1 */
#define SRAM SRAM1_BASEADDR /* Helper - la memoria SRAM principale è la SRAM1 */
#define SRAM2_BASEADDR 0x2004C000U /* Indirizzo base della Memoria SRAM 2 */
#define ROM 0x1FF00000U /* Indirizzo base della Memoria ROM (System Memory) */

/*
* Definizione degli indirizzi base dei BUS
*/
#define PERIPH_BASE 0x40000000U /* Indirizzo base delle periferiche */
#define APB1PERIPH_BASE PERIPH_BASE /* Indirizzo base dell' Advanced Peripherap Bus 1 */
#define APB2PERIPH_BASE 0x40010000U /* Indirizzo base dell' Advanced Peripherap Bus 2 */
#define AHB1PERIPH_BASE 0x40020000U /* Indirizzo base dell' Advanced High Speed Peripherap Bus 1 */
#define AHB2PERIPH_BASE 0x50000000U /* Indirizzo base dell' Advanced High Speed Peripherap Bus 2 */

/*
* Definizione degli indirizzi base delle periferiche connesse al bus AHB1
*/
//#define GPIOA_BASEADDR 0x40020000U /* Indirizzo base della periferica GPIO A */
#define GPIOA_BASEADDR (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR (AHB1PERIPH_BASE + 0x2000)
#define GPIOJ_BASEADDR (AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASEADDR (AHB1PERIPH_BASE + 0x2800)

#define RCC_BASEADDR   (AHB1PERIPH_BASE + 0x3800) //0x4002 3800

/*
* Definizione degli indirizzi base delle periferiche connesse al bus APB1
*/
#define I2C1_BASEADDR (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR (APB1PERIPH_BASE + 0x5C00)
#define I2C4_BASEADDR (APB1PERIPH_BASE + 0x6000)
#define USART2_BASEADDR (APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR (APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR (APB1PERIPH_BASE + 0x4C00)
#define SPI2_BASEADDR (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR (APB1PERIPH_BASE + 0x3C00)

/*
* Definizione degli indirizzi base delle periferiche connesse al bus APB2
*/
#define EXTI_BASEADDR (APB2PERIPH_BASE + 0x3C00)
#define SPI1_BASEADDR (APB2PERIPH_BASE + 0x3000)
#define USART1_BASEADDR (APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR (APB2PERIPH_BASE + 0x1400)
#define SYSCFG_BASEADDR (APB2PERIPH_BASE + 0x3800)

#define SPI_CONTROL_REGISTER_1 (SPI1_BASEADDR + 0x00)
#define SPI_CONTROL_REGISTER_2 (SPI1_BASEADDR + 0x04)
#define SPI_STATUS_REGISTER (SPI1_BASEADDR + 0x08)
#define SPI_DATA_REGISTER (SPI1_BASEADDR + 0x0C)
#define SPI_CRC_POLYNOMIAL_REGISTER (SPI1_BASEADDR + 0x10)
#define SPI_RXCRC_REGISTER (SPI1_BASEADDR + 0x14)
#define SPI_TXCRC_REGISTER (SPI1_BASEADDR + 0x18)
#define SPI_I2S_CONFIGURATION_REGISTER (SPI1_BASEADDR + 0x1C)
#define SPI_I2S_PRESCALER_REGISTER (SPI1_BASEADDR + 0x20)

/*
 * peripheral register definition structure for GPIO
 */
typedef struct
{
	volatile uint32_t MODER;     // offset : 0x00
	volatile uint32_t OTYPER;    // offset : 0x04
	volatile uint32_t OSPEEDR;   // offset : 0x08
	volatile uint32_t PUPDR;     // offset : 0x0C
	volatile uint32_t IDR;       // offset : 0x10
	volatile uint32_t ODR;       // offset : 0x14
	volatile uint32_t BSRRL;     // offset : 0x18
	volatile uint32_t BSRRH;     // offset : 0x1A
	volatile uint32_t LCKR;      // offset : 0x1C
	volatile uint32_t AFR[2];    // offset : 0x20 - 0x24
}GPIO_RegDef_t;

/*
 * peripheral register definition structure for RCC
 */
typedef struct
{
	volatile uint32_t CR; 				// offest : 0x00
	volatile uint32_t PLLCFGR;			// offset : 0x04
	volatile uint32_t CFGR;				// offset : 0x08
	volatile uint32_t CIR;				// offset : 0x0C
	volatile uint32_t AHB1RSTR;			// offset : 0x10
	volatile uint32_t AHB2RSTR;			// offset : 0x14
	volatile uint32_t AHB3RSTR;			// offset : 0x18
	volatile uint32_t RESERVED_0;		// offset : 0x1C
	volatile uint32_t APB1RSTR;			// offset : 0X20
	volatile uint32_t APB2RSTR;			// offset : 0X24
	volatile uint32_t RESERVED_1;		// offset : 0x28
	volatile uint32_t RESERVED_2;		// offset : 0x2C
	volatile uint32_t AHB1ENR;			// offset : 0X30
	volatile uint32_t AHB2ENR;			// offset : 0X34
	volatile uint32_t AHB3ENR;  		// offset : 0X38
	volatile uint32_t APB1ENR;			// offset : 0x40
	volatile uint32_t APB2ENR;			// offset : 0x44
	volatile uint32_t RESERVED_3;		// offset : 0x48
	volatile uint32_t RESERVED_4;		// offset : 0x4C
	volatile uint32_t AHB1LPENR;		// offset : 0x50
	volatile uint32_t AHB2LPENR;		// offset : 0x54
	volatile uint32_t AHB3LPENR;		// offset : 0x58
	volatile uint32_t RESERVED_5;		// offset : 0x5C
	volatile uint32_t APB1LPENR;		// offset : 0x60
	volatile uint32_t APB2LPENR;		// offset : 0x64
	volatile uint32_t RESERVED_6;		// offset : 0x68
	volatile uint32_t RESERVED_7;		// offset : 0x6C
	volatile uint32_t BDCR;				// offset : 0x70
	volatile uint32_t CSR;				// offset : 0x74
	volatile uint32_t RESERVED_8;		// offset : 0x78
	volatile uint32_t RESERVED_9;		// offset : 0x7C
	volatile uint32_t SSCGR;			// offset : 0x80
	volatile uint32_t PLLI2SCFGR;		// offset : 0x84
	volatile uint32_t PLLSAICFGR;		// offset : 0x88
	volatile uint32_t DCKCFGR1;			// offset : 0x8C
	volatile uint32_t DCKCFGR2;			// offset : 0x90
}RCC_RegDef_t;

/*
 * peripheral register definition structure for EXTI
 */
typedef struct
{
	volatile uint32_t IMR; 		/* Interrupt Mask Register*/
	volatile uint32_t EMR; 		/* Interrupt Mask Register*/
	volatile uint32_t RTSR; 	/* Interrupt Mask Register*/
	volatile uint32_t FTSR; 	/* Interrupt Mask Register*/
	volatile uint32_t SWIER; 	/* Interrupt Mask Register*/
	volatile uint32_t PR; 		/* Interrupt Mask Register*/
}EXTI_RegDef_t;

/*
 * peripheral register definition structure for SYSCFG
 */
typedef struct
{
	volatile uint32_t MEMRMP;		/* Memory Remap Register 						Offset : 0x00 			*/
	volatile uint32_t PMC;			/* Peripheral Mode Configuration Register 		Offset : 0x04 			*/
	volatile uint32_t EXTICR[4];	/* External Interrupt Configuration Registers  	Offset : 0x08 - 0x14 	*/
	uint32_t RESERVED_1[2];			/* Reserved Bytes								Offset : 0x18 - 0x1C    */
	volatile uint32_t CMPCR;		/* Compensation Cell Control Register			Offset : 0x20 			*/
}SYSCFG_RegDef_t;

// Peripheral Definition Macros
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ ((GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK ((GPIO_RegDef_t*)GPIOK_BASEADDR)

#define RCC 		((RCC_RegDef_t*) RCC_BASEADDR)

#define EXTI 		((EXTI_RegDef_t*) EXTI_BASEADDR)

#define SYSCFG 		((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

/*
 * CLOCK ENABLE MACROS #############################################################
 */

// Clock Enable Macros for GPIOx Peripherals
#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 0 ))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 1 ))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 2 ))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 3 ))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 4 ))
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 5 ))
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 6 ))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 7 ))
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 8 ))
#define GPIOJ_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 9 ))
#define GPIOK_PCLK_EN() (RCC->AHB1ENR |= ( 1 << 10))

// Clock Enable Macros for I2Cx Peripherals
#define I2C1_PCLK_EN() (RCC->APB1ENR |= ( 1 << 21))
#define I2C2_PCLK_EN() (RCC->APB1ENR |= ( 1 << 22))
#define I2C3_PCLK_EN() (RCC->APB1ENR |= ( 1 << 23))

// Clock Enable Macros for SPIx Peripherals
#define SPI1_PCLK_EN() (RCC->APB2ENR |= ( 1 << 12 ))

#define SPI2_PCLK_EN() (RCC->APB1ENR |= ( 1 << 14 ))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= ( 1 << 15 ))

#define SPI4_PCLK_EN() (RCC->APB2ENR |= ( 1 << 13 ))
#define SPI5_PCLK_EN() (RCC->APB2ENR |= ( 1 << 20 ))
#define SPI6_PCLK_EN() (RCC->APB2ENR |= ( 1 << 21 ))

// Clock Enable Macros for USARTx Peripherals
#define USART1_PCLK_EN() (RCC->APB2ENR |= ( 1 << 4 ))

#define USART2_PCLK_EN() (RCC->APB1ENR |= ( 1 << 17 ))
#define USART3_PCLK_EN() (RCC->APB1ENR |= ( 1 << 18 ))
#define USART4_PCLK_EN() (RCC->APB1ENR |= ( 1 << 19 ))
#define USART5_PCLK_EN() (RCC->APB1ENR |= ( 1 << 20 ))

#define USART6_PCLK_EN() (RCC->APB2ENR |= ( 1 << 5 ))

#define USART7_PCLK_EN() (RCC->APB1ENR |= ( 1 << 30 ))
#define USART8_PCLK_EN() (RCC->APB1ENR |= ( 1 << 31 ))

// Clock Enable Macros for SYSCFG Peripheral
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= ( 1 << 14 ))

/*
 * CLOCK DISABLE MACROS #############################################################
 */

// Clock disable Macros for GPIOx Peripherals
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 0 ))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 1 ))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 2 ))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 3 ))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 4 ))
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 5 ))
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 6 ))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 7 ))
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 8 ))
#define GPIOJ_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 9 ))
#define GPIOK_PCLK_DI() (RCC->AHB1ENR &= ~( 1 << 10))

// Clock Disable Macros for I2Cx Peripherals
#define I2C1_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 21))
#define I2C2_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 22))
#define I2C3_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 23))

// Clock Disable Macros for SPIx Peripherals
#define SPI1_PCLK_DI() (RCC->APB2ENR &= ~( 1 << 12 ))

#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 14 ))
#define SPI3_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 15 ))

#define SPI4_PCLK_DI() (RCC->APB2ENR &= ~( 1 << 13 ))
#define SPI5_PCLK_DI() (RCC->APB2ENR &= ~( 1 << 20 ))
#define SPI6_PCLK_DI() (RCC->APB2ENR &= ~( 1 << 21 ))

// Clock Disable Macros for USARTx Peripherals
#define USART1_PCLK_DI() (RCC->APB2ENR &= ~( 1 << 4 ))

#define USART2_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 17 ))
#define USART3_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 18 ))
#define USART4_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 19 ))
#define USART5_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 20 ))

#define USART6_PCLK_DI() (RCC->APB2ENR &= ~( 1 << 5 ))

#define USART7_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 30 ))
#define USART8_PCLK_DI() (RCC->APB1ENR &= ~( 1 << 31 ))

// Clock Disable Macros for SYSCFG Peripheral
#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~( 1 << 14 ))

/*
 * Macros to Reset GPIOx peripherals
 *
 * */
#define GPIOA_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 0));  (RCC->AHB1RSTR &= ~(1 << 0));} while(0)
#define GPIOB_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 1));  (RCC->AHB1RSTR &= ~(1 << 1));} while(0)
#define GPIOC_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 2));  (RCC->AHB1RSTR &= ~(1 << 2));} while(0)
#define GPIOD_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 3));  (RCC->AHB1RSTR &= ~(1 << 3));} while(0)
#define GPIOE_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 4));  (RCC->AHB1RSTR &= ~(1 << 4));} while(0)
#define GPIOF_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 5));  (RCC->AHB1RSTR &= ~(1 << 5));} while(0)
#define GPIOG_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 6));  (RCC->AHB1RSTR &= ~(1 << 6));} while(0)
#define GPIOH_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 7));  (RCC->AHB1RSTR &= ~(1 << 7));} while(0)
#define GPIOI_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 8));  (RCC->AHB1RSTR &= ~(1 << 8));} while(0)
#define GPIOJ_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 9));  (RCC->AHB1RSTR &= ~(1 << 9));} while(0)
#define GPIOK_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 10));  (RCC->AHB1RSTR &= ~(1 << 10));} while(0)

#include "stm32f746_gpio_driver.h"

#define GPIO_BASEADDR_TO_CODE(x)    (x == GPIOA) ?  0 : \
									(x == GPIOB) ?  1 : \
									(x == GPIOC) ?  2 : \
									(x == GPIOD) ?  3 : \
									(x == GPIOE) ?  4 : \
									(x == GPIOF) ?  5 : \
									(x == GPIOG) ?  6 : \
									(x == GPIOH) ?  7 : \
									(x == GPIOI) ?  8 : \
									(x == GPIOJ) ?  9 : \
									(x == GPIOK) ? 10 : 0

/*
 *	 IRQ (Interrupt Request) Numbers of STM32F746x MCU
 */
#define IRQ_NO_EXTI0			 6
#define IRQ_NO_EXTI1			 7
#define IRQ_NO_EXTI2			 8
#define IRQ_NO_EXTI3			 9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI9_5			30
#define IRQ_NO_EXTI15_10		47

#endif /* INC_STM32F746XX_H_ */











































