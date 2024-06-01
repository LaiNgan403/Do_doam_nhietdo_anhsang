#include <stm32f4xx.h>

void Timer2_Init(void) {// có the dieu chinh do sáng cua dèn LED. 
	//GPIOA Clock
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//Timer 3 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//PA6 alternative function mode
		GPIOA->MODER &= ~GPIO_MODER_MODER6;
    GPIOA->MODER |= GPIO_MODER_MODER6_1;
	//PA6 PWM mode
    GPIOA->AFR[0] |= (2 << (4*6));
	//Prescaler value
    TIM3->PSC = 0;
	//Auto reload value
    TIM3->ARR = 100;
	//Set channel 1 for PWM
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
  //Enable channel 1 compare output
		TIM3->CCER |= TIM_CCER_CC1E;
	//Enable timer 3
    TIM3->CR1 |= TIM_CR1_CEN;
}

void DatchukyPWM(uint32_t adcValue) { //dat chu ky cua PWM dua trên giá tri doc tu cam bien ánh sáng.
    uint32_t pwmValue = (adcValue * 100) / 4095;
    TIM3->CCR1 = pwmValue;
}