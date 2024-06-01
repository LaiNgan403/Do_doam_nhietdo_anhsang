#include "stm32f4xx.h" 
#include "delay.h"

void Timer1_Init(void) { //Khoi tao Timer 2 và tao ra ham doi chính xác theo don vi micro giây.
	//Clock enable 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
}

void delay_us(uint32_t us) {
	//Prescaler 
	TIM2->PSC = 16-1;  //chia tan so xung dong ho cho 16
	//Auto-reload (chu ky)
	TIM2->ARR = us; 
	//Forced update 
	TIM2->EGR = TIM_EGR_UG;
	//Clear update flag
	TIM2->SR &= ~TIM_SR_UIF; 
	//Timer enable 
	TIM2->CR1 |= TIM_CR1_CEN; 
	//Wait till update flag is set 
	while (!(TIM2->SR & TIM_SR_UIF)); 
	//Clear update flag 
	TIM2->SR &= ~TIM_SR_UIF; //Clear update flag
	TIM2->CR1 &= ~TIM_CR1_CEN; //Stop timer 
}