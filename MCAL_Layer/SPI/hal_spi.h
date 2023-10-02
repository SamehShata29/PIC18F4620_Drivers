/* 
 * File:   hal_spi.h
 * Author: sameh
 *
 * Created on September 10, 2023, 12:55 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* ============== Includes ============== */
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* ============== Macro Declarations ============== */
/* Enable/Disable SPI module [SSPEN] */
#define SPI_ENABLE                  1
#define SPI_DISABLE                 0
/* Clock Polarity select [CKP] */
#define CLK_HIGH_LEVEL              1
#define CLK_LOW_LEVEL               0
/* SPI Clock Select [CKE] */
#define TRANSMIT_ON_ACTIVE_TO_IDLE  1
#define TRANSMIT_ON_IDLE_TO_ACTIVE  0
/* Sampling Mode [SMP] */
#define SAMPLE_AT_OUTPUT_END        1
#define SAMPLE_AT_OUTPUT_MID        0
/* Buffer Status [BF] */
#define BUFFER_FULL                 1
#define BUFFER_EMPTY                0
/* Write Collision Detect [WCOL] */
#define COLLISION_OCCURED           1
#define NO_COLLISION                0
/*  Receive Overflow Indicator [SSPOV] */
#define OVERFLOW_OCCURED            1
#define NO_OVERFLOW                 0
/* ============== Macro Functions Declarations ============== */
#define SPI_MODULE_ENABLE()           (SSPCON1bits.SSPEN = SPI_ENABLE)
#define SPI_MODULE_DISABLE()          (SSPCON1bits.SSPEN = SPI_DISABLE)
/* ============== Data type Declarations ============== */
/* Master Synchronous Serial Port Mode Select */
typedef enum{
    MASTER_MODE_CLK_DIV_BY_4 = 0,
    MASTER_MODE_CLK_DIV_BY_16,
    MASTER_MODE_CLK_DIV_BY_64,
    MASTER_MODE_CLK_TMR2,
    SLAVE_MODE_CLK_SCK_SS_ENABLE,
    SLAVE_MODE_CLK_SCK_SS_DISABLE
}spi_mode_select_t;

typedef struct{
    spi_mode_select_t spi_mode;
    uint8 clk_phase : 1;
    uint8 clk_polarity : 1;
    uint8 sample : 1;
    void(*SPI_DefaultInterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg priority;
#endif
}spi_t;
/* ============== Software Interfaces Declarations ============== */
Std_ReturnType SPI_Init(const spi_t* spi);
Std_ReturnType SPI_DeInit(const spi_t* spi);

Std_ReturnType SPI_SendByte(const spi_t* spi, uint8 data);
Std_ReturnType SPI_ReadByte(const spi_t* spi, uint8 *data);

#endif	/* HAL_SPI_H */

