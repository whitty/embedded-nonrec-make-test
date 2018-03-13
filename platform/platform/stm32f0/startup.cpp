// (C) Copyright 2018 Greg Whiteley

#include <stdlib.h>
#include <string.h>
#include "abort.h"
#include "../../platform_common.hpp"

extern "C" uint32_t SystemInit(void);

// Peripheral base-addresses from memory map

#define GPIOF_BASE 0x48001400
#define GPIOD_BASE 0x48000C00
#define GPIOC_BASE 0x48000800
#define GPIOB_BASE 0x48000400
#define GPIOA_BASE 0x48000000
#define TSC_BASE 0x40024000
#define CRC_BASE 0x40023000
#define FLASH_MEMORY_INTERFACE_BASE 0x40022000
#define RCC_BASE 0x40021000
#define DMA_BASE 0x40020000
#define DBGMCU_BASE 0x40015800
#define TIM17_BASE 0x40014800
#define TIM16_BASE 0x40014400
#define TIM15_BASE 0x40014000
#define USART1_BASE 0x40013800
#define SPI1_I2S1_BASE 0x40013000
#define TIM1_BASE 0x40012C00
#define ADC_BASE 0x40012400
#define EXTI_BASE 0x40010400
#define SYSCFG_COMP_BASE 0x40010000
#define CEC_BASE 0x40007800
#define DAC_BASE 0x40007400
#define PWR_BASE 0x40007000
#define I2C2_BASE 0x40005800
#define I2C1_BASE 0x40005400
#define USART2_BASE 0x40004400
#define SPI2_BASE 0x40003800
#define IWDG_BASE 0x40003000
#define WWDG_BASE 0x40002C00
#define RTC_BASE 0x40002800
#define TIM14_BASE 0x40002000
#define TIM6_BASE 0x40001000
#define TIM3_BASE 0x40000400
#define TIM2_BASE 0x40000000

using RegT = volatile unsigned uint32_t;

struct RCC_registers
{
    RegT CR;
    RegT CFGR;
    RegT CIR;
    RegT APB2RSTR;
    RegT APB1RSTR;
    RegT AHBENR;
    RegT APB2ENR;
    RegT APB1ENR;
    RegT BDCR;
    RegT CSR;
    RegT AHBRSTR;
    RegT CFGR2;
    RegT CFGR3;
    RegT CR2;
};

#define RCC ((struct RCC_registers*)RCC_BASE)

struct FLASH_registers
{
    RegT ACR;
    RegT KEYR;
    RegT OPTKEYR;
    RegT SR;
    RegT CR;
    RegT AR;
    RegT RESVD18;
    RegT OBR;
    RegT WRPR;
};

#define FLASH ((struct FLASH_registers*)FLASH_MEMORY_INTERFACE_BASE)

#define DEF_FIELD(name, top, bottom)                                    \
    static constexpr uint32_t name = mask32((top), (bottom));           \
    static constexpr uint32_t name##_SHIFT = (bottom);

// NOTE has "preserve bits"
DEF_FIELD(RCC_CR_HSION, 0, 0);
DEF_FIELD(RCC_CR_HSIRDY, 1, 1);
DEF_FIELD(RCC_CR_HSITRIM, 7, 3);
DEF_FIELD(RCC_CR_HSICAL, 15, 8);
DEF_FIELD(RCC_CR_HSEON, 16, 16);
DEF_FIELD(RCC_CR_HSERDY, 17, 17);
DEF_FIELD(RCC_CR_HSEBYP, 18, 18);
DEF_FIELD(RCC_CR_CSSON, 19, 19);
DEF_FIELD(RCC_CR_PLLON, 24, 24);
DEF_FIELD(RCC_CR_PLLRDY, 25, 25);

// NOTE has "preserve bits"
DEF_FIELD(RCC_CFGR_SW, 1, 0)
DEF_FIELD(RCC_CFGR_SWS, 3, 2);
DEF_FIELD(RCC_CFGR_HPRE, 7, 4);
DEF_FIELD(RCC_CFGR_PPRE, 10, 8);
DEF_FIELD(RCC_CFGR_ADC_PRE, 14, 14);
DEF_FIELD(RCC_CFGR_PLLSRC, 16, 15);
DEF_FIELD(RCC_CFGR_PLLXTPRE, 17, 17);
DEF_FIELD(RCC_CFGR_PLLMUL, 21, 18);
DEF_FIELD(RCC_CFGR_MCO, 27, 24);
DEF_FIELD(RCC_CFGR_MCOPRE, 30, 28);
DEF_FIELD(RCC_CFGR_PLLNODIV, 31, 31);

// NOTE has "preserve bits"
DEF_FIELD(RCC_CFGR2_PREDIV, 3, 0);

// NOTE has "preserve bits"
DEF_FIELD(RCC_CFGR3_USART1SW, 1, 0);
DEF_FIELD(RCC_CFGR3_I2C1SW, 4, 4);
DEF_FIELD(RCC_CFGR3_CECSW, 6, 6);
DEF_FIELD(RCC_CFGR3_USBSW, 7, 7);
DEF_FIELD(RCC_CFGR3_ADCSW, 8, 8);
DEF_FIELD(RCC_CFGR3_USART2SW, 19, 18);
DEF_FIELD(RCC_CFGR3_USART3SW, 17, 16);

// NOTE has "preserve bits"
DEF_FIELD(RCC_CR2_HSI14ON, 0, 0);
DEF_FIELD(RCC_CR2_HSI14RDY, 1, 1);
DEF_FIELD(RCC_CR2_HSI14DIS, 2, 2);
DEF_FIELD(RCC_CR2_HSI14TRIM, 7, 3);
DEF_FIELD(RCC_CR2_HSI14CAL, 7, 3);
DEF_FIELD(RCC_CR2_HSI48ON, 16, 16);
DEF_FIELD(RCC_CR2_HSI48RDY, 17, 17);
DEF_FIELD(RCC_CR2_HSI48CAL, 31, 24);

DEF_FIELD(FLASH_ACR_LATENCY, 0, 0);
DEF_FIELD(FLASH_ACR_PRFTBE, 4, 4);
DEF_FIELD(FLASH_ACR_PRFTBS, 5, 5);

uint32_t SystemInit(void)
{
    RCC->CR |= RCC_CR_HSION;

    // Clear bits that don't depend on PLL state
    RCC->CFGR &= ~(RCC_CFGR_SW | RCC_CFGR_ADC_PRE | RCC_CFGR_HPRE | RCC_CFGR_MCO | RCC_CFGR_MCOPRE);

    // other clocks off
    RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);
    // HSE must be off first before clearing
    RCC->CR &= ~(RCC_CR_HSEBYP);
    // PLL disabled, clear configuration
    RCC->CFGR &= ~(RCC_CFGR_PLLNODIV | RCC_CFGR_PLLMUL | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC);
    // Clear CFGR2
    RCC->CFGR2 &= ~RCC_CFGR2_PREDIV;
    // Clear CFGR3 simple HSI clock sources
    RCC->CFGR3 &= ~(RCC_CFGR3_I2C1SW | RCC_CFGR3_CECSW | RCC_CFGR3_ADCSW);

    // Clear HSI14
    RCC->CR2 &= ~(RCC_CR2_HSI14ON);

    // Disable interrupts
    RCC->CIR = 0;

    // Now enable clocks

    // TODO - consider using HSI instead of HSE
    // Definitely use HSI instead of HSE for this example - power-mode 1,...

    // or leave us at HSI - 8MHz is OK for boot-time, until
    // higher-power is required?
#ifndef NO_PLL

    RCC->CR |= RCC_CR_HSEON;
    unsigned count;
    for (count = 0x500; count && ((RCC->CR & RCC_CR_HSERDY) == 0); --count)
        continue;

    if (count)
        return 1; // failed - what now?

    // Enable wait-states for higher rate operation and enable prefetch
    FLASH->ACR = FLASH_ACR_LATENCY | FLASH_ACR_PRFTBE;

    // PLL for 48MHz from 8MHz HSE
    uint32_t val = RCC->CFGR;
    val &= (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL);
    val |= (2 << RCC_CFGR_PLLSRC_SHIFT) | // HSE / prediv
        ((6 - 2) << RCC_CFGR_PLLMUL_SHIFT); // PLL multiplier == 6
    RCC->CFGR = val;

    // enable PLL
    RCC->CR |= RCC_CR_PLLON;

    for (count = 0x500; count && ((RCC->CR & RCC_CR_PLLRDY) == 0); --count)
        continue;

    if (count)
        return 1; // failed - what now?

    val = RCC->CFGR;
    val &= ~RCC_CFGR_SW;
    val |= 2 << RCC_CFGR_SW_SHIFT; // PLL
    RCC->CFGR = val;

    for (count = 0x500; count &&
             ((RCC->CFGR & RCC_CFGR_SWS) != (2U << RCC_CFGR_SWS_SHIFT)); --count)
        continue;

    if (count)
        return 1; // failed - what now?
#endif
    return 0;
}
