#include "stm32f4xx.h"
#include "adc.h"
#include "uart.h"

void ADC1_Init() {
    // Enable GPIOA Clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // Set PA1 to analog mode
    GPIOA->MODER |= (1 << 2) | (1 << 3);
    // Enable ADC1 Clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // Configure ADC1 to start on channel 1
    ADC1->SQR3 = 1;
    // Enable ADC1
    ADC1->CR2 |= ADC_CR2_ADON;
}

void ADC2_Init() {
    // Enable GPIOA Clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // Set PA0 to analog mode
    GPIOA->MODER |= (1 << 0) | (1 << 1);
    // Enable ADC1 Clock (assuming ADC2 is a typo and it's supposed to be ADC1)
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // Configure ADC1 to start on channel 0
    ADC1->SQR3 = 0;
    // Enable ADC1
    ADC1->CR2 |= ADC_CR2_ADON;
}

uint32_t ADC_Read() {
    // Start conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;
    // Wait for conversion to complete
    while (!(ADC1->SR & ADC_SR_EOC)) {};
    // Return the converted result
    return ADC1->DR;
}
