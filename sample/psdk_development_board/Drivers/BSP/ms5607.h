/**
  ******************************************************************************
  * @file    ms5607.h
  * @version V0.0.0
  * @date    2017/11/17
  * @brief   
  *
  * @copyright 2017 DJI. All right reserved.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEMO_RTOS_RTTHREAD_MS5607_H
#define DEMO_RTOS_RTTHREAD_MS5607_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <os_util.h>

/* Defines, configurable -----------------------------------------------------*/

/* Defines, fixed ------------------------------------------------------------*/
#define MS5607_SPI                              SPI2
#define MS5607_SPI_CLK                          RCC_APB1Periph_SPI2
#define MS5607_SPI_CLK_INIT                     RCC_APB1PeriphClockCmd

#define MS5607_SPI_SCK_PIN                      GPIO_Pin_13
#define MS5607_SPI_SCK_GPIO_PORT                GPIOB
#define MS5607_SPI_SCK_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define MS5607_SPI_SCK_SOURCE                   GPIO_PinSource13
#define MS5607_SPI_SCK_AF                       GPIO_AF_SPI2

#define MS5607_SPI_MISO_PIN                     GPIO_Pin_14
#define MS5607_SPI_MISO_GPIO_PORT               GPIOB
#define MS5607_SPI_MISO_GPIO_CLK                RCC_AHB1Periph_GPIOB
#define MS5607_SPI_MISO_SOURCE                  GPIO_PinSource14
#define MS5607_SPI_MISO_AF                      GPIO_AF_SPI2

#define MS5607_SPI_MOSI_PIN                     GPIO_Pin_15
#define MS5607_SPI_MOSI_GPIO_PORT               GPIOB
#define MS5607_SPI_MOSI_GPIO_CLK                RCC_AHB1Periph_GPIOB
#define MS5607_SPI_MOSI_SOURCE                  GPIO_PinSource15
#define MS5607_SPI_MOSI_AF                      GPIO_AF_SPI2

#define MS5607_CS_GPIO_PORT                     GPIOB
#define MS5607_CS_PIN                           GPIO_Pin_12
#define MS5607_CS_GPIO_CLK                      RCC_AHB1Periph_GPIOB

#define MS5607_CMD_RESET                        0x1E // ADC reset command
#define MS5607_CMD_ADC_READ                     0x00 // ADC read command
#define MS5607_CMD_ADC_CONV                     0x40 // ADC conversion command
#define MS5607_CMD_ADC_D1                       0x00 // ADC D1 conversion
#define MS5607_CMD_ADC_D2                       0x10 // ADC D2 conversion
#define MS5607_CMD_ADC_256                      0x00 // ADC OSR=256
#define MS5607_CMD_ADC_512                      0x02 // ADC OSR=512
#define MS5607_CMD_ADC_1024                     0x04 // ADC OSR=1024
#define MS5607_CMD_ADC_2048                     0x06 // ADC OSR=2056
#define MS5607_CMD_ADC_4096                     0x08 // ADC OSR=4096
#define MS5607_CMD_PROM_RD                      0xA0 // Prom read command
#define MS5607_CSB_HIGH()                       (GPIO_SetBits(MS5607_CS_GPIO_PORT, MS5607_CS_PIN)) // setting CSB high
#define MS5607_CSB_LOW()                        (GPIO_ResetBits(MS5607_CS_GPIO_PORT, MS5607_CS_PIN)) // setting CSB low

#define MS5607_DELAY(msT)                       OS_DELAY(msT)

/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void Ms5607Spi_Init(void);
int Ms5607_Init(void);

/* *Temperature in degrees Celsius (°C) , *Pressure im mbar */
int Ms5607_GetSenorData(double *temperature, double *pressure);

int testMs5607(void);

#ifdef __cplusplus
}
#endif

#endif //DEMO_RTOS_RTTHREAD_MS5607_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
