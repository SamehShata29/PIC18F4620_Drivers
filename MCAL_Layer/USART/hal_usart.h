/* 
 * File:   hal_usart.h
 * Author: sameh
 *
 * Created on September 7, 2023, 6:55 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H
/* ============== Includes ============== */
#include "hal_usart_cfg.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* ============== Macro Declarations ============== */
/* Enable/Disable ESUART Module */
#define ESUART_MODULE_ENABLE            1
#define ESUART_MODULE_DISABLE           0
/* Selecting ESUART Working Mode */
#define ESUART_SYNCHRONOUS_MODE         1
#define ESUART_ASYNCHRONOUS_MODE        0
/* Baud Rate Generator Asynchronous Speed Mode */
#define ESUART_ASYNCHRONOUS_HIGH_SPEED  1
#define ESUART_ASYNCHRONOUS_LOW_SPEED   0
/* Baud Rate Generator Register Size */
#define ESUART_16BIT_BAUDRATE_GEN       1
#define ESUART_08BIT_BAUDRATE_GEN       0
/* ESUART Transmitter Enable */
#define ESUART_ASYNCHRONOUS_TX_ENABLE   1
#define ESUART_ASYNCHRONOUS_TX_DISABLE  0
/* ESUART Transmitter Interrupt Enable */
#define ESUART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE  1
#define ESUART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE 0
/* ESUART 9-Bit Transmitter Enable */
#define ESUART_ASYNCHRONOUS_9BIT_TX_ENABLE   1
#define ESUART_ASYNCHRONOUS_9BIT_TX_DISABLE  0
/* ESUART Receiver Enable */
#define ESUART_ASYNCHRONOUS_RX_ENABLE   1
#define ESUART_ASYNCHRONOUS_RX_DISABLE  0
/* ESUART Receiver Interrupt Enable */
#define ESUART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE  1
#define ESUART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE 0
/* ESUART 9-Bit Receiver Enable */
#define ESUART_ASYNCHRONOUS_9BIT_RX_ENABLE   1
#define ESUART_ASYNCHRONOUS_9BIT_RX_DISABLE  0
/* EUSART Framing Error */
#define ESUART_FRAMING_ERROR_DETECTED        1
#define ESUART_FRAMING_ERROR_CLEARED         0
/* ESUART Overrun Error */
#define ESUART_OVERRUN_ERROR_DETECTED        1
#define ESUART_OVERRUN_ERROR_CLEARED         0
/* ============== Macro Functions Declarations ============== */

/* ============== Data type Declarations ============== */
typedef enum{
    BAUDRATE_ASYN_8BIT_LOW_SPEED = 0,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct{
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9bit_enable : 1;
    interrupt_priority_cfg usart_tx_int_priority;
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9bit_enable : 1;
    interrupt_priority_cfg usart_rx_int_priority;
}usart_rx_cfg_t;

typedef union{
    struct{
        uint8 usart_tx_reserved :6;
        uint8 usart_ferr : 1;
        uint8 usart_oerr : 1;
    };
    uint8 status;
}usart_error_status_t;

typedef struct{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t usart_error_status;
    void(*ESUART_TxDefaultInterruptHandler)(void);
    void(*ESUART_RxDefaultInterruptHandler)(void);
    void(*ESUART_FramingerrorHandler)(void);
    void(*ESUART_OverrunErrorHandler)(void);
}usart_t;

/* ============== Software Interfaces Declarations ============== */

Std_ReturnType ESUART_ASYNC_Init(const usart_t *_esuart);
Std_ReturnType ESUART_ASYNC_DeInit(const usart_t *_esuart);

Std_ReturnType ESUART_ASYNC_ReadByteBlocking(uint8 *_data);
Std_ReturnType ESUART_ASYNC_ReadByteNonBlocking(uint8 *_data);
Std_ReturnType ESUART_ASYNC_RX_Restart(void);

Std_ReturnType ESUART_ASYNC_WriteByteBlocking(uint8 _data);
Std_ReturnType ESUART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len);
Std_ReturnType ESUART_ASYNC_WriteByteNonBlocking(uint8 _data);
Std_ReturnType ESUART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len);

#endif	/* HAL_USART_H */

