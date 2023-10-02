/* 
 * File:   hal_usart.c
 * Author: sameh
 *
 * Created on September 7, 2023, 6:55 PM
 */
#include "hal_usart.h"

static void ESUART_Baud_Rate_Calculation(const usart_t *_esuart);
static void ESUART_ASYNC_TX_Init(const usart_t *_esuart);
static void ESUART_ASYNC_RX_Init(const usart_t *_esuart);

#if ESUART_TX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (* ESUART_TX_InterruptHandler)(void) = NULL;
#endif
#if ESUART_RX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (* ESUART_RX_InterruptHandler)(void) = NULL;
    static void (* ESUART_FramingErrorInterruptHandler)(void) = NULL;
    static void (* ESUART_OverrunErrorInterruptHandler)(void) = NULL;
#endif

Std_ReturnType ESUART_ASYNC_Init(const usart_t *_esuart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _esuart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = ESUART_MODULE_DISABLE;
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        ESUART_Baud_Rate_Calculation(_esuart);
        ESUART_ASYNC_TX_Init(_esuart);
        ESUART_ASYNC_RX_Init(_esuart);
        
        RCSTAbits.SPEN = ESUART_MODULE_ENABLE;
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType ESUART_ASYNC_DeInit(const usart_t *_esuart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _esuart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = ESUART_MODULE_DISABLE;
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType ESUART_ASYNC_ReadByteBlocking(uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *_data = RCREG;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ESUART_ASYNC_ReadByteNonBlocking(uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.RCIF){
            *_data = RCREG;
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType ESUART_ASYNC_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN = 0; /* Enable Receiver */ 
    RCSTAbits.CREN = 1; /* Disable Receiver */ 
    return ret;
}

Std_ReturnType ESUART_ASYNC_WriteByteBlocking(uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    while(!TXSTAbits.TRMT);
#if ESUART_TX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    ESUART_TX_InterruptEnable();
#endif
    TXREG = _data;
    ret = E_OK;
    return ret;
}

Std_ReturnType ESUART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len){
    Std_ReturnType ret = E_NOT_OK;
    uint16 char_counter = 0;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        for(char_counter = 0; char_counter < str_len; char_counter++){
            ret = ESUART_ASYNC_WriteByteBlocking(_data[char_counter]);
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ESUART_ASYNC_WriteByteNonBlocking(uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    if(1 == TXSTAbits.TRMT){
    #if ESUART_TX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ESUART_TX_InterruptEnable();
    #endif
        TXREG = _data;
        ret = E_OK;
        __delay_ms(2);
    }
    else
    {
        ret =E_NOT_OK;
    }
    return ret;
}

Std_ReturnType ESUART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len){
    Std_ReturnType ret = E_NOT_OK;
    uint16 char_counter = 0;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        for(char_counter = 0; char_counter < str_len; char_counter++){
            ret = ESUART_ASYNC_WriteByteNonBlocking(_data[char_counter]);
        }
        ret = E_OK;
    }
    return ret;
}

/* ========== Helper Functions ==========*/
static void ESUART_Baud_Rate_Calculation(const usart_t *_esuart){
    float Baud_Rate_Temp = 0;
    switch(_esuart->baudrate_gen_config){
        case BAUDRATE_ASYN_8BIT_LOW_SPEED :
            TXSTAbits.SYNC = ESUART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = ESUART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = ESUART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_esuart->baudrate) / 64) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED :
            TXSTAbits.SYNC = ESUART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = ESUART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = ESUART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_esuart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED :
            TXSTAbits.SYNC = ESUART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = ESUART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = ESUART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_esuart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED :
            TXSTAbits.SYNC = ESUART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = ESUART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = ESUART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_esuart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_8BIT :
            TXSTAbits.SYNC = ESUART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = ESUART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_esuart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT :
            TXSTAbits.SYNC = ESUART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = ESUART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_esuart->baudrate) / 4) - 1;
            break;
        default : ;
    }
    SPBRG  = (uint8)((uint32)Baud_Rate_Temp);
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp) >> 8);
}

static void ESUART_ASYNC_TX_Init(const usart_t *_esuart){
    if(ESUART_ASYNCHRONOUS_TX_ENABLE == _esuart->usart_tx_cfg.usart_tx_enable){
        /* Enable TX */
        TXSTAbits.TXEN = ESUART_ASYNCHRONOUS_TX_ENABLE;
        /* ESUART Transmit Interrupt Configuration */
        if(ESUART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _esuart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TX1IE = ESUART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
#if ESUART_TX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ESUART_TX_InterruptEnable();
        ESUART_TX_InterruptHandler = _esuart->ESUART_TxDefaultInterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == _esuart->usart_tx_cfg.usart_tx_int_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            ESUART_TX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _esuart->usart_tx_cfg.usart_tx_int_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            ESUART_TX_LowPrioritySet();
        }
        else{/* NOTHING */}
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        }
        else if(ESUART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _esuart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TX1IE = ESUART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else{/* Nothing */}
        /* ESUART Transmit 9-Bit Configuration */
        if(ESUART_ASYNCHRONOUS_9BIT_TX_ENABLE == _esuart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = ESUART_ASYNCHRONOUS_9BIT_TX_ENABLE;
        }
        else if(ESUART_ASYNCHRONOUS_9BIT_TX_DISABLE == _esuart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = ESUART_ASYNCHRONOUS_9BIT_TX_DISABLE;
        }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}

static void ESUART_ASYNC_RX_Init(const usart_t *_esuart){
    if(ESUART_ASYNCHRONOUS_RX_ENABLE == _esuart->usart_rx_cfg.usart_rx_enable){
        /* Enable RX */
        RCSTAbits.CREN = ESUART_ASYNCHRONOUS_RX_ENABLE;
        /* ESUART Receiver Interrupt Configuration */
        if(ESUART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _esuart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = ESUART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
#if ESUART_RX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ESUART_RX_InterruptEnable();
        ESUART_RX_InterruptHandler = _esuart->ESUART_RxDefaultInterruptHandler;
        ESUART_FramingErrorInterruptHandler = _esuart->ESUART_FramingerrorHandler;
        ESUART_OverrunErrorInterruptHandler = _esuart->ESUART_OverrunErrorHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == _esuart->usart_rx_cfg.usart_rx_int_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            ESUART_RX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _esuart->usart_rx_cfg.usart_rx_int_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            ESUART_RX_LowPrioritySet();
        }
        else{/* NOTHING */}
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        }
        else if(ESUART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _esuart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = ESUART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else{/* Nothing */}
        /* ESUART Receiver 9-Bit Configuration */
        if(ESUART_ASYNCHRONOUS_9BIT_RX_ENABLE == _esuart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = ESUART_ASYNCHRONOUS_9BIT_RX_ENABLE;
        }
        else if(ESUART_ASYNCHRONOUS_9BIT_RX_DISABLE == _esuart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = ESUART_ASYNCHRONOUS_9BIT_RX_DISABLE;
        }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}

void ESUART_TX_ISR(void){
    ESUART_TX_InterruptDisable();
    if(ESUART_TX_InterruptHandler){
        ESUART_TX_InterruptHandler();
    }
}
void ESUART_RX_ISR(void){
    if(ESUART_RX_InterruptHandler){
        ESUART_RX_InterruptHandler();
    }
    if(ESUART_FramingErrorInterruptHandler){
        ESUART_FramingErrorInterruptHandler();
    }
    if(ESUART_OverrunErrorInterruptHandler){
        ESUART_OverrunErrorInterruptHandler();
    }
}