#ifndef _NVIC_COMMON_H_
#define _NVIC_COMMON_H_

#include "typedef.h"
#include "memorymap.h"

typedef enum {
    NVIC_WWDG,                      // Window Watchdog interrupt
    NVIC_PVD,                       // PVD through EXTI line detection interrupt
    NVIC_TAMP_STAMP,                // Tamper and TimeStamp interrupts through the EXTI line
    NVIC_RTC_WKUP,                  // RTC Wakeup interrupt through the EXTI line
    NVIC_FLASH,                     // Flash global interrupt
    NVIC_RCC,                       // RCC global interrupt
    NVIC_EXTI0,                     // EXTI Line0 interrupt
    NVIC_EXTI1,                     // EXTI Line1 interrupt
    NVIC_EXTI2,                     // EXTI Line2 interrupt
    NVIC_EXTI3,                     // EXTI Line3 interrupt
    NVIC_EXTI4,                     // EXTI Line4 interrupt
    NVIC_DMA1_Stream0,              // DMA1 Stream0 global interrupt
    NVIC_DMA1_Stream1,              // DMA1 Stream1 global interrupt
    NVIC_DMA1_Stream2,              // DMA1 Stream2 global interrupt
    NVIC_DMA1_Stream3,              // DMA1 Stream3 global interrupt
    NVIC_DMA1_Stream4,              // DMA1 Stream4 global interrupt
    NVIC_DMA1_Stream5,              // DMA1 Stream5 global interrupt
    NVIC_DMA1_Stream6,              // DMA1 Stream6 global interrupt
    NVIC_ADC,                       // ADC1, ADC2 and ADC3 global interrupts
    NVIC_CAN1_TX,                   // CAN1 TX interrupts
    NVIC_CAN1_RX0,                  // CAN1 RX0 interrupts
    NVIC_CAN1_RX1,                  // CAN1 RX1 interrupts
    NVIC_CAN1_SCE,                  // CAN1 SCE interrupt
    NVIC_EXTI9_5,                   // EXTI Line[9:5] interrupts
    NVIC_TIM1_BRK_TIM9,             // TIM1 Break interrupt and TIM9 global interrupt
    NVIC_TIM1_UP_TIM10,             // TIM1 Update interrupt and TIM10 global interrupt
    NVIC_TIM1_TRG_COM_TIM11,        // TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
    NVIC_TIM1_CC,                   // TIM1 Capture compare interrupt
    NVIC_TIM2,                      // TIM2 global interrupt
    NVIC_TIM3,                      // TIM3 global interrupt
    NVIC_TIM4,                      // TIM4 global interrupt
    NVIC_I2C1_EV,                   // I2C1 event interrupt
    NVIC_I2C1_ER,                   // I2C1 error interrupt
    NVIC_I2C2_EV,                   // I2C2 event interrupt
    NVIC_I2C2_ER,                   // I2C2 error interrupt
    NVIC_SPI1,                      // SPI1 global interrupt
    NVIC_SPI2,                      // SPI2 global interrupt
    NVIC_USART1,                    // USART1 global interrupt
    NVIC_USART2,                    // USART2 global interrupt
    NVIC_USART3,                    // USART3 global interrupt
    NVIC_EXTI15_10,                 // EXTI Line[15:10] interrupts
    NVIC_RTC_Alarm,                 // RTC Alarms (A and B) through EXTI line interrupt
    NVIC_OTG_FS_WKUP,               // USB On-The-Go FS Wakeup through EXTI line interrupt
    NVIC_TIM8_BRK_TIM12,            // TIM8 break interrupt and TIM12 global interrupt
    NVIC_TIM8_UP_TIM13,             // TIM8 Update interrupt and TIM13 global interrupt
    NVIC_TIM8_TRG_COM_TIM14,        // TIM8 Trigger and Commutation interrupts and TIM14 global interrupt
    NVIC_TIM8_CC,                   // TIM8 Capture compare interrupt
    NVIC_DMA1_Stream7,              // DMA1 Stream7 global interrupt
    NVIC_FMC,                       // FMC global interrupt
    NVIC_SDIO,                      // SDIO global interrupt
    NVIC_TIM5,                      // TIM5 global interrupt
    NVIC_SPI3,                      // SPI3 global interrupt
    NVIC_UART4,                     // UART4 global interrupt
    NVIC_UART5,                     // UART5 global interrupt
    NVIC_TIM6_DAC,                  // TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts 
    NVIC_TIM7,                      // TIM7 global interrupt
    NVIC_DMA2_Stream0,              // DMA2 Stream0 global interrupt
    NVIC_DMA2_Stream1,              // DMA2 Stream1 global interrupt
    NVIC_DMA2_Stream2,              // DMA2 Stream2 global interrupt
    NVIC_DMA2_Stream3,              // DMA2 Stream3 global interrupt
    NVIC_DMA2_Stream4,              // DMA2 Stream4 global interrupt
    NVIC_CAN2_TX,                   // CAN2 TX interrupts
    NVIC_CAN2_RX0,                  // CAN2 RX0 interrupts
    NVIC_CAN2_RX1,                  // CAN2 RX1 interrupt
    NVIC_CAN2_SCE,                  // CAN2 SCE interrupt
    NVIC_OTG_FS,                    // USB On The Go FS global interrupt
    NVIC_DMA2_Stream5,              // DMA2 Stream5 global interrupt
    NVIC_DMA2_Stream6,              // DMA2 Stream6 global interrupt
    NVIC_DMA2_Stream7,              // DMA2 Stream7 global interrupt
    NVIC_USART6,                    // USART6 global interrupt
    NVIC_I2C3_EV,                   // I2C3 event interrupt
    NVIC_I2C3_ER,                   // I2C3 error interrupt
    NVIC_OTG_HS_EP1_OUT,            // USB On The Go HS End Point 1 Out global interrupt
    NVIC_OTG_HS_EP1_IN,             // USB On The Go HS End Point 1 In global interrupt
    NVIC_OTG_HS_WKUP,               // USB On The Go HS Wakeup through EXTI interrupt
    NVIC_OTG_HS,                    // USB On The Go HS global interrupt
    NVIC_DCMI,                      // DCMI global interrupt
    NVIC_FPU,                       // FPU global interrupt
    NVIC_SPI4,                      // SPI 4 global interrupt
    NVIC_SAI1,                      // SAI1 global interrupt
    NVIC_SAI2,                      // SAI2 global interrupt
    NVIC_QuadSPI,                   // QuadSPI global interrupt
    NVIC_HDMI_CEC,                  // HDMI-CEC global interrupt
    NVIC_SPDIF_Rx,                  // SPDIF-Rx global interrupt
    NVIC_FMPI2C1,                   // FMPI2C1 event interrupt
    NVIC_FMPI2C1_error,             // FMPI2C1 error interrupt
    NVIC_END
} NVIC_LIST;

static const BYTE NVIC_TABLE[NVIC_END] = {
    [NVIC_WWDG]               =      0, 
    [NVIC_PVD]                =      1,
    [NVIC_TAMP_STAMP]         =      2,
    [NVIC_RTC_WKUP]           =      3,
    [NVIC_FLASH]              =      4,
    [NVIC_RCC]                =      5,
    [NVIC_EXTI0]              =      6,
    [NVIC_EXTI1]              =      7,
    [NVIC_EXTI2]              =      8,
    [NVIC_EXTI3]              =      9,
    [NVIC_EXTI4]              =     10,
    [NVIC_DMA1_Stream0]       =     11,  
    [NVIC_DMA1_Stream1]       =     12,
    [NVIC_DMA1_Stream2]       =     13,
    [NVIC_DMA1_Stream3]       =     14,
    [NVIC_DMA1_Stream4]       =     15,
    [NVIC_DMA1_Stream5]       =     16,
    [NVIC_DMA1_Stream6]       =     17,
    [NVIC_ADC]                =     18,
    [NVIC_CAN1_TX]            =     19,
    [NVIC_CAN1_RX0]           =     20,
    [NVIC_CAN1_RX1]           =     21,
    [NVIC_CAN1_SCE]           =     22,
    [NVIC_EXTI9_5]            =     23,
    [NVIC_TIM1_BRK_TIM9]      =     24,
    [NVIC_TIM1_UP_TIM10]      =     25,
    [NVIC_TIM1_TRG_COM_TIM11] =     26, 
    [NVIC_TIM1_CC]            =     27,
    [NVIC_TIM2]               =     28,
    [NVIC_TIM3]               =     29,
    [NVIC_TIM4]               =     30,
    [NVIC_I2C1_EV]            =     31,
    [NVIC_I2C1_ER]            =     32,
    [NVIC_I2C2_EV]            =     33,
    [NVIC_I2C2_ER]            =     34,
    [NVIC_SPI1]               =     35,
    [NVIC_SPI2]               =     36,
    [NVIC_USART1]             =     37,
    [NVIC_USART2]             =     38,
    [NVIC_USART3]             =     39,
    [NVIC_EXTI15_10]          =     40,
    [NVIC_RTC_Alarm]          =     41,
    [NVIC_OTG_FS_WKUP]        =     42,
    [NVIC_TIM8_BRK_TIM12]     =     43,
    [NVIC_TIM8_UP_TIM13]      =     44,
    [NVIC_TIM8_TRG_COM_TIM14] =     45,
    [NVIC_TIM8_CC]            =     46,
    [NVIC_DMA1_Stream7]       =     47,
    [NVIC_FMC]                =     48,
    [NVIC_SDIO]               =     49,
    [NVIC_TIM5]               =     50,
    [NVIC_SPI3]               =     51,
    [NVIC_UART4]              =     52,
    [NVIC_UART5]              =     53,
    [NVIC_TIM6_DAC]           =     54,
    [NVIC_TIM7]               =     55,
    [NVIC_DMA2_Stream0]       =     56,
    [NVIC_DMA2_Stream1]       =     57,
    [NVIC_DMA2_Stream2]       =     58,
    [NVIC_DMA2_Stream3]       =     59,
    [NVIC_DMA2_Stream4]       =     60,
    // RESERVED               =     61,
    // RESERVED               =     62,
    [NVIC_CAN2_TX]            =     63,
    [NVIC_CAN2_RX0]           =     64,
    [NVIC_CAN2_RX1]           =     65,
    [NVIC_CAN2_SCE]           =     66,
    [NVIC_OTG_FS]             =     67,
    [NVIC_DMA2_Stream5]       =     68,
    [NVIC_DMA2_Stream6]       =     69,
    [NVIC_DMA2_Stream7]       =     70,
    [NVIC_USART6]             =     71,
    [NVIC_I2C3_EV]            =     72,
    [NVIC_I2C3_ER]            =     73,
    [NVIC_OTG_HS_EP1_OUT]     =     74,
    [NVIC_OTG_HS_EP1_IN]      =     75,
    [NVIC_OTG_HS_WKUP]        =     76,
    [NVIC_OTG_HS]             =     77,
    [NVIC_DCMI]               =     78,
    // RESERVED               =     79,
    // RESERVED               =     80,
    [NVIC_FPU]                =     81,
    // RESERVED               =     82,
    // RESERVED               =     83,
    [NVIC_SPI4]               =     84,  
    // RESERVED               =     85,
    // RESERVED               =     86,
    [NVIC_SAI1]               =     87,
    // RESERVED               =     88,
    // RESERVED               =     89,
    // RESERVED               =     90,
    [NVIC_SAI2]               =     91,
    [NVIC_QuadSPI]            =     92,
    [NVIC_HDMI_CEC]           =     93,
    [NVIC_SPDIF_Rx]           =     94,
    [NVIC_FMPI2C1]            =     95,
    [NVIC_FMPI2C1_error]      =     96
};


// Interrupt Set-enable Registers
#define NVIC_ISER_OFFSET     (0x00000000)
#define NVIC_ISER            GET_ADDR(NVIC_BASE + NVIC_ISER_OFFSET)

// NVIC_ISER0 ~ NVIC_ISER07
#define NVIC_ISER0_OFFSET          0x00
#define NVIC_ISER1_OFFSET          0x04
#define NVIC_ISER2_OFFSET          0x08
#define NVIC_ISER3_OFFSET          0x0C
#define NVIC_ISER4_OFFSET          0x10
#define NVIC_ISER5_OFFSET          0x14
#define NVIC_ISER6_OFFSET          0x18
#define NVIC_ISER7_OFFSET          0x1C

#define READ_NVIC_ISERx(ISERx)                READ_REG_LWORD(NVIC_ISER, NVIC_ISER0_OFFSET + (ISERx)*4)
#define WRITE_NVIC_ISERx(ISERx, u32Value)     WRITE_REG_LWORD(NVIC_ISER, NVIC_ISER0_OFFSET + (ISERx)*4, READ_NVIC_ISERx(ISERx) | (u32Value))

#define SET_INTERRUPT_ENABLE(interrupt)       WRITE_NVIC_ISERx(NVIC_TABLE[interrupt] / 32, 1 << (NVIC_TABLE[interrupt] % 32))      

#endif