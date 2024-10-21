// Daniel Fajardo
// dfajardo@g.hmc.edu
// 10/06/2024
// 
// headerfile for pwm pins

#ifndef STM32L4_TIM_H
#define STM32L4_TIM_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

// Base addresses
#define TIM15_BASE (0x40014000)
#define TIM16_BASE (0x40014400)

// TIM16 register structs
typedef struct{
    volatile uint32_t CR1; // TIMx_CR1 offset 0x00
    volatile uint32_t CR2; // TIMx_CR2 offset 0x04
    volatile uint32_t reserved1;
    volatile uint32_t DIER; // TIMx_DIER offset 0x0C
    volatile uint32_t SR; // TIMx_SR offset 0x10
    volatile uint32_t EGR; // TIMx_EGR offset 0x14
    volatile uint32_t CCMR1; // TIMx_CCMR1 offset 0x18
    volatile uint32_t reserved2;  
    volatile uint32_t CCER; // TIMx_CCER offset 0x20
    volatile uint32_t CNT; // TIMx_CNT offset 0x24
    volatile uint32_t PSC; // TIMx_PSC offset 0x28
    volatile uint32_t ARR; // TIMx_ARR offset 0x2C
    volatile uint32_t RCR; // TIMx_RCR offset 0x30
    volatile uint32_t CCR1; // TIMx_CCR1 offset 0x34
    volatile uint32_t reserved3 [3];


    volatile uint32_t BDTR; // TIMx_BDTR offset 0x44
    volatile uint32_t DCR; // TIMx_DCR offset 0x48
    volatile uint32_t DMAR; // TIMx_DMAR offset 0x4C
    volatile uint32_t OR1; // TIMx_OR1 offset 0x50
    volatile uint32_t reserved4 [3];

    
    volatile uint32_t OR2; // TIMx_OR2 offset 0x60
} TIMxx_TypeDef;

#define TIM15 ((TIMxx_TypeDef *) TIM15_BASE)
#define TIM16 ((TIMxx_TypeDef *) TIM16_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void configureTIM(TIMxx_TypeDef *TIMx);

void setfreq(int freq, TIMxx_TypeDef *TIMx);

void setdur(int dur, TIMxx_TypeDef *TIMx);

#endif