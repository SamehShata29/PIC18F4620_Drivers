/* 
 * File:   hal_spi.c
 * Author: sameh
 *
 * Created on September 10, 2023, 12:55 PM
 */
#include "hal_spi.h"



static void Master_Pins(void);
static void Slave_Pins(const spi_t* spi);

#if SPI_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (* SPI_InterruptHandler)(void) = NULL;
#endif

Std_ReturnType SPI_Init(const spi_t* spi){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == spi){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_MODULE_DISABLE();
        /* Mode Select */
        SSPCON1bits.SSPM = spi->spi_mode;
        /* Pins configuration & Sample bit */
        if((spi->spi_mode == 4) || (spi->spi_mode == 5)){
            Slave_Pins(spi);
        }
        else if(((spi->spi_mode >= 0) || (spi->spi_mode <= 3))){
            Master_Pins();
        }
        /* Sample bit */
        SSPSTATbits.SMP = spi->sample;
        /* Clock Polarity */
        SSPCON1bits.CKP = spi->clk_polarity;
        /* Clock phase */
        SSPSTATbits.CKE = spi->clk_phase;
#if SPI_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        SPI_InterruptEnable();
        SPI_InterruptFlagClear();
        SPI_InterruptHandler = spi->SPI_DefaultInterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        SPI_InterruptHandler = spi->SPI_DefaultInterruptHandler;
        if(INTERRUPT_HIGH_PRIORITY == spi->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            SPI_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == spi->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            SPI_LowPrioritySet();
        }
        else{/* NOTHING */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        SPI_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_DeInit(const spi_t* spi){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == spi){
        ret = E_NOT_OK;
    }
    else{
        SPI_MODULE_DISABLE();
#if SPI_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        SPI_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_SendByte(const spi_t* spi, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == spi){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = data;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_ReadByte(const spi_t* spi, uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == spi || NULL == data){
        ret = E_NOT_OK;
    }
    else{
        if(SSPSTATbits.BF){
            *data = SSPBUF;
            SPI_InterruptFlagClear();
            SSPCON1bits.SSPOV = 0;
            ret = E_OK;
        }
    }
    return ret;
}
/* =================== HELPER FUNCTIONS =================== */
static void Master_Pins(void){
    pin_config_t SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SCK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT};
    
    gpio_pin_initialize(&SDO);
    gpio_pin_initialize(&SCK);
}
static void Slave_Pins(const spi_t* spi){
    pin_config_t SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SCK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SS  = {.port = PORTA_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_INPUT};

    gpio_pin_initialize(&SDO);
    gpio_pin_initialize(&SCK);
    
    if(SLAVE_MODE_CLK_SCK_SS_ENABLE == spi->spi_mode){
        ADCON1bits.PCFG = 11;   
        gpio_pin_initialize(&SS);
    }
}

void SPI_ISR(void){
    SPI_InterruptFlagClear();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
}