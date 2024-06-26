/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: nikhil
 */
#include "timer.h"
#include "i2c_lcd.h"
#include<stdio.h>


void TimerInit(uint32_t ms) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->PSC = TIM_PR-1;

	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM7->ARR = cnt - 1;
	TIM7->CNT = 0;
	TIM7->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM7_IRQn);
	TIM7->CR1 |= TIM_CR1_CEN;
}

void TimerDelayMs(uint32_t ms) {

	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM7->ARR = cnt - 1;
	TIM7->CNT = 0;
	TIM7->CR1 |= TIM_CR1_CEN;
	while(! (TIM7->SR & TIM_SR_UIF))
		;
	TIM7->SR &= ~TIM_SR_UIF;
	TIM7->CR1 &= ~TIM_CR1_CEN;
}


int cnt = 0;

void TIM7_IRQHandler(void)
{
     static int flag = 0;
		// check if interrupt occurred
		if(TIM7->SR & TIM_SR_UIF) {
			// then clear (ack) the interrupt
			TIM7->SR &= ~TIM_SR_UIF;
			// toggle LED
			if(flag == 0) {
				cnt++;
				flag = 1;
			} else {

				flag = 0;
			}
		}
	}



