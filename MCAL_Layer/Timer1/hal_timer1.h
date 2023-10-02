/* 
 * File:   hal_timer1.h
 * Author: sameh
 *
 * Created on August 30, 2023, 6:07 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* ============== Includes ============== */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ============== Macro Declarations ============== */

#define TIMER1_COUNTER_MODE             1
#define TIMER1_TIMER_MODE               0

#define TIEMR1_ASYNC_COUTNER_MODE       1
#define TIEMR1_SYNC_COUTNER_MODE        0
/* Timer1 Oscillator */
#define TIMER1_OSC_ENABLE               1
#define TIMER1_OSC_DISABLE              0
/* Timer1 Clock Pre-scaler values */
#define TIMER1_PRESCALER_DIV_BY_1       0
#define TIMER1_PRESCALER_DIV_BY_2       1
#define TIMER1_PRESCALER_DIV_BY_4       2
#define TIMER1_PRESCALER_DIV_BY_8       3
/* 16 Bit read/write mode */
#define TIMER1_RW_REG_8BIT_MODE         0
#define TIMER1_RW_REG_16BIT_MODE        1

/* ============== Macro Functions Declarations ============== */

#define TIMER1_MODULE_ENABLE()              (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()             (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 0)

#define TIMER1_OSC_HW_ENABLE()              (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()             (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)

#define TIMER1_SYSTEM_CLK_STATUS()          (T1CONbits.T1RUN)
/* 16 Bit read/write mode */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE      (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE     (T1CONbits.RD16 = 1)

/* ============== Data type Declarations ============== */

typedef struct{
#if TIMER1_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer1_preload_value;
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_reg_wr_mode : 1;
    uint8 timer0_reserved : 2;
}timer1_t;

/* ============== Software Interfaces Declarations ============== */
Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 value);
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *value);


#endif	/* HAL_TIMER1_H */

