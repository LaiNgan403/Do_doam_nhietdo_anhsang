#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"

void UART_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable clock for GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; //Enable clock for UART

    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1; //cau hinh PA2, PA3 lm chan chuc nang thay the

    GPIOA->AFR[0] |= 0x00007700;//�at chuc nang thay the cho PA2 v� PA3 l� AF7 (USART2)

    USART2->BRR = 0x683;// dat baud rate cho USART2 la 9600(gia tri 0x683 tuong ung voi baud rate 9600 khi clock nguon l� 16 MHz).)

    USART2->CR1 |= USART_CR1_UE; //enable UARST2

    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; //ena chuyen va nhan
    USART2->CR1 |= USART_CR1_RXNEIE; //Enable RXNE (Receive Not Empty) interrupt
    NVIC_EnableIRQ(USART2_IRQn); ////Bat ngat khi du lieu nhan v� cho ph�p ngat USART2 trong NVIC
}

void UART_Transmit(char c) { // truyen 1 ki tu qua uart
    while (!(USART2->SR & USART_SR_TXE));  // Cho cho den khi bo truyen san s�ng truyen du lieu
    USART2->DR = c;// Ghi du lieu vao thanh ghi truyen (DR)
}

void UART_Transmit_String(char* str) {  // truyen 1 chuoi kt qua
    while (*str) {
        UART_Transmit(*str++);
    }
}

void UART_Transmit_Float(float humidity, float temperature, float light) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%g %g %g\n", humidity, temperature, light);
    UART_Transmit_String(buffer);
}
