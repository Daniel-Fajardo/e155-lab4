// Daniel Fajardo
// dfajardo@g.hmc.edu
// 10/06/2024
// 
// source code for pwm functions

#include "STM32L432KC_TIM.h"
#include <math.h>
#include <stdint.h>

void configureTIM(TIMxx_TypeDef *TIMx){
    //set ccmr1 to pwm mode
    TIMx->CCMR1 &= ~(0b111<<4); // OC1M bits [2:0] cleared
    TIMx->CCMR1 |= (0b110<<4); // OC1M bits [2:0] set to PWM mode 1
    //enable preload ccmr1
    TIMx->CCMR1 |= (1<<3); // OC1PE enabled
    //set arpe cr1 register
    TIMx->CR1 |= (1<<7); // ARPE enabled
    TIMx->PSC &= ~(65535<<0); // prescalar bits cleared
    TIMx->PSC |= (1023<<0); // prescalar set to 15
    TIMx->CCER |= (1<<0); // enabled CC1E bit to enable output
    TIMx->BDTR |= (1<<15); // enabled MOE (main output enable)
    //set ug bit in egr
    TIMx->EGR |= (1<<0); // UG enabled
    TIMx->CR1 |= (1<<0); // CEN
};

void setfreq(int freq, TIMxx_TypeDef *TIMx){
    /*Find duration of period for input frequency*/
    if (freq==0) {
        TIMx->ARR &= ~(65535<<0); // clear ARR
        TIMx->CR1 &= ~(1<<0); // CEN disabled
    }
    else {
        int newARR = (80000000/(1024)/freq); // might need to replace with manual input
        TIMx->ARR &= ~(65535<<0); // auto-reload register bits cleared
        TIMx->ARR |= (newARR<<0); // ARR bits set to desired period length
        int dutycycle = newARR/2; // duty cycle set to 50%
        TIMx->CCR1 &= ~(65535<<0); // clear CCR bits
        TIMx->CCR1 |= (dutycycle<<0); // set CCR bits
        TIMx->EGR |= (1<<0); // update event
        TIMx->CR1 |= (1<<0); // CEN enabled
    }
};

void setdur(int dur, TIMxx_TypeDef *TIMx){
    int ticks = 80000000/(1024)/1000*dur; // calculated ticks per ms
    TIMx->ARR = ticks; // ARR set to desired length
    TIMx->EGR |= (1<<0); // update event
    TIMx->SR &= ~(1<<0); // wait for flag to be raised marking overflow in CNT
    TIMx->CNT = 0; // reset counter to 0 before while loop
    
    while (!(TIMx->SR & (1<<0))); // waits until counter reaches tick count
};
