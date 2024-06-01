#include "stm32f4xx.h"
#include "dht22.h"
#include "delay.h"

void DHT22_Start(void) 
{   
    // Configure PA4 as output de gui tin hieu dieu khien
    GPIOA->MODER &= ~(GPIO_MODER_MODER4); // xoa cau hinh cu chan PA4
    GPIOA->MODER |= GPIO_MODER_MODER4_0; //dat PA4 lm output
    
		GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR4); //xoa cau hinh PUPD cua PA4
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR4_0; //Dat PA4 lm pull-up(chan DATA muc cao khi ko co tin hieu dieu khien)

    // Set PA4 as high speed
    GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR4);
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
	
    // Reset PA4(pull low)
    GPIOA->ODR &= ~GPIO_ODR_ODR_4;
    delay_us(1000);

    // Set PA4(pull high)
    GPIOA->ODR |= GPIO_ODR_ODR_4;
    delay_us(20);
		GPIOA->ODR &= ~GPIO_ODR_ODR_4;
    // Set PA4 as input de nhan du lieu tu cam bien
    GPIOA->MODER &= ~GPIO_MODER_MODER4; // Dat PA4 lm input
		GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR4; //xoa cau hinh PUPD
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR4; //xoa cau hinh toc do
}

uint8_t DHT22_Check_Response (void) { //ktra sau khi gui tin hieu
    uint8_t response = 0;
    delay_us(40);
	
	//Check if the data is ready to be sent
    if (!(GPIOA->IDR & GPIO_IDR_IDR_4)) // Kiem tra neu PA4 là low
    {
        delay_us(80);

        if (GPIOA->IDR & GPIO_IDR_IDR_4) response = 1; // Kiem tra neu PA4 là high, cam bien phan hoi thanh cong
        else response = 2;
    }

    while (GPIOA->IDR & GPIO_IDR_IDR_4); //cho den khi PA4 low=> ss gui yeu cau va doc du lieu

    return response;
}

uint8_t DHT22_Read()
{
    uint8_t data, i;
	//Read 8 bit
    for(i = 0; i < 8; i++)
    {
        while (!(GPIOA->IDR & GPIO_IDR_IDR_4));// cho den het muc thap den muc cao thoat khoi while
        delay_us(40);
        if (!(GPIOA->IDR & GPIO_IDR_IDR_4)) {//neu la muc thap				
						data &= ~(1<<(7-i)); //=0
				}
        else
        {
            data |= (1<<(7-i));//=1
        }
		while (GPIOA->IDR & GPIO_IDR_IDR_4);//cho den khi PA4 low
    }
	return data;
}
