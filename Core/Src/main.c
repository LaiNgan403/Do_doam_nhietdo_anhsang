#include "stm32f4xx.h"
#include "pwm.h"
#include "dht22.h"
#include "delay.h"
#include "uart.h"
#include "adc.h"
#include "gpio.h"
#include <stdio.h>

int main(void) {
    UART_Init();
    Timer1_Init();
    Timer2_Init();
    ADC1_Init();
    GPIOB0_Init();
    GPIOC0_Init();

    uint8_t dhtResponse;
    uint8_t humidityHighByte;
    uint8_t humidityLowByte;
    uint8_t temperatureHighByte;
    uint8_t temperatureLowByte;
    uint8_t checksum;
    uint16_t rawHumidity;
    uint16_t rawTemperature;
    float humidity;
    float temperature;
    float light;
    int i = 0;
    
    uint32_t adcValue;
    
    uint8_t dirtSensorStatus; //bat tat GPIOB0
    while (1) {
        // Dirt sensor
        dirtSensorStatus = GPIOC0_Read();
        if (dirtSensorStatus == 1) {
            GPIOB0_Off();
        } else {
            GPIOB0_On();
        }
        // Light sensor
        adcValue = ADC_Read();
        DatchukyPWM(adcValue);
        
        // Humidity and temperature sensor
        DHT22_Start();
        dhtResponse = DHT22_Check_Response();
        if (dhtResponse == 2) {
            UART_Transmit_String("Error");
        } else {
            humidityHighByte = DHT22_Read();
            humidityLowByte = DHT22_Read();
            temperatureHighByte = DHT22_Read();
            temperatureLowByte = DHT22_Read();
            checksum = DHT22_Read();
            rawHumidity = (humidityHighByte << 8) | humidityLowByte;
            rawTemperature = (temperatureHighByte << 8) | temperatureLowByte;
            humidity = rawHumidity / 10.0f;
            temperature = rawTemperature / 10.0f;
            light = adcValue / 40.95f;
        
            UART_Transmit_Float(humidity, temperature, light);
        }
        delay_us(500000);
    }
}
