/* 
 * File:   hale_timer3.h
 * Author: sameh
 *
 * Created on September 1, 2023, 3:14 PM
 */

#ifndef HALE_TIMER3_H
#define	HALE_TIMER3_H
/* ============== Includes ============== */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ============== Macro Declarations ============== */

#define TIMER3_COUNTER_MODE             1
#define TIMER3_TIMER_MODE               0

#define TIEMR3_ASYNC_COUTNER_MODE       1
#define TIEMR3_SYNC_COUTNER_MODE        0
/* Timer3 Clock Pre-scaler values */
#define TIMER3_PRESCALER_DIV_BY_1       0
#define TIMER3_PRESCALER_DIV_BY_2       1
#define TIMER3_PRESCALER_DIV_BY_4       2
#define TIMER3_PRESCALER_DIV_BY_8       3
/* 16 Bit read/write mode */
#define TIMER3_RW_REG_8BIT_MODE         0
#define TIMER3_RW_REG_16BIT_MODE        1
/* ============== Macro Functions Declarations ============== */

#define TIMER3_MODULE_ENABLE()              (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()             (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()          (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()        (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 0)

#define TIMER3_PRESCALER_SELECT(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_)
/* Timer3 16 Bit read/write mode */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE      (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE     (T3CONbits.RD16 = 1)


/* ============== Data type Declarations ============== */

typedef struct{
#if TIMER3_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value : 2;
    uint8 timer3_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_reg_wr_mode : 1;
    uint8 timer3_reserved : 3;
}timer3_t;

/* ============== Software Interfaces Declarations ============== */
Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 value);
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *value);


#endif	/* HALE_TIMER3_H */

