// Daniel Fajardo
// dfajardo@g.hmc.edu
// 10/06/2024
// 
// source code for pwm functions

#include "STM32L432KC_TIM.h"
#include <math.h>
void configureTIM(void){
    //set ccmr1 to pwm mode
    TIM16->CCMR1 &= ~(0b111<<4); // OC1M bits [2:0] cleared
    TIM16->CCMR1 |= (0b110<<4); // OC1M bits [2:0] set to PWM mode 1
    //enable preload ccmr1
    TIM16->CCMR1 |= (1<<3); // OC1PE enabled
    //set arpe cr1 register
    TIM16->CR1 |= (1<<7); // ARPE enabled
    //set ug bit in egr
    TIM16->EGR |= (1<<0); // UG enabled
    TIM16->PSC &= ~(65536<<0); // prescalar bits cleared
    TIM16->PSC &= ~(16<<0); // prescalar set to 16
    TIM16->CCER |= (1<<0); // enabled CC1E bit to enable output
    TIM16->BDTR |= (1<<15); // enabled MOE (main output enable)
};

void setfreq(int freq, int clk){
    /*Find duration of period for input frequency*/
    if (freq==0){
        TIM16->CR1 &= ~(1<<0); // CEN disabled
    }
    else {
        int newARR = (clk/(TIM16->PSC+1)/freq)-1;
        TIM16->ARR &= ~(65536<<0); // auto-reload register bits cleared
        TIM16->ARR |= (newARR<<0); // ARR bits set to desired period length
        int dutycycle = newARR/2; // duty cycle set to 50%
        TIM16->CCR1 &= ~(65536<<0); // clear CCR bits
        TIM16->CCR1 |= (dutycycle<<0); // set CCR bits
        TIM16->CR1 |= (1<<0); // CEN enabled
    }
};

void setdur(int dur, int clk){
    int ticks = clk/(TIM16->PSC+1)/1000*dur; // calculated ticks
    TIM16->CNT = 0; // reset counter to 0 before while loop
    while (TIM16->CNT < ticks); // waits until counter reaches tick count

};
