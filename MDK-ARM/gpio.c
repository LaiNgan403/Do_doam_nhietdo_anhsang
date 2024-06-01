#include "stm32f4xx.h"
#include "gpio.h"

void GPIOB0_Init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //bat clock cho GPIOB

	GPIOB->MODER &= ~GPIO_MODER_MODER0; //clear 
	GPIOB->MODER |= GPIO_MODER_MODER0_0; //set PB0 as output
}

void GPIOC0_Init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //bat clock cho GPIOC

	GPIOC->MODER &= ~GPIO_MODER_MODER0; //set PC0 as output
}

void GPIOB0_Off(void) {
	GPIOB->ODR &= ~GPIO_ODR_ODR_0;// Ğat bit 0 cua thanh ghi ODR (Output Data Register) cua GPIOB ve 0, làm cho chân PB0 chuyen sang muc thap (off)
}

void GPIOB0_On(void) {
	GPIOB->ODR |= GPIO_ODR_ODR_0; // Ğat bit 0 cua thanh ghi ODR (Output Data Register) cua GPIOB ve 1, làm cho chân PB0 chuyen sang muc cao (On)
}

uint8_t GPIOC0_Read(void) {//doc tu chân PC0
	uint8_t data = (GPIOC->IDR & GPIO_IDR_IDR_0) >> 0;
	return data;
}