/* 
 * File:   hal_timer2.h
 * Author: sameh
 *
 * Created on September 1, 2023, 3:14 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/* ============== Includes ============== */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ============== Macro Declarations ============== */

/* Timer2 Clock Post-scaler values */
#define TIMER2_POSTSCALER_DIV_BY_1       0
#define TIMER2_POSTSCALER_DIV_BY_2       1
#define TIMER2_POSTSCALER_DIV_BY_3       2
#define TIMER2_POSTSCALER_DIV_BY_4       3
#define TIMER2_POSTSCALER_DIV_BY_5       4
#define TIMER2_POSTSCALER_DIV_BY_6       5
#define TIMER2_POSTSCALER_DIV_BY_7       6
#define TIMER2_POSTSCALER_DIV_BY_8       7
#define TIMER2_POSTSCALER_DIV_BY_9       8
#define TIMER2_POSTSCALER_DIV_BY_10      9
#define TIMER2_POSTSCALER_DIV_BY_11      10
#define TIMER2_POSTSCALER_DIV_BY_12      11
#define TIMER2_POSTSCALER_DIV_BY_13      12
#define TIMER2_POSTSCALER_DIV_BY_14      13
#define TIMER2_POSTSCALER_DIV_BY_15      14
#define TIMER2_POSTSCALER_DIV_BY_16      15
/* Timer2 Clock Pre-scaler values */
#define TIMER2_PRESCALER_DIV_BY_1        0
#define TIMER2_PRESCALER_DIV_BY_4        1
#define TIMER2_PRESCALER_DIV_BY_16       2
/* ============== Macro Functions Declarations ============== */
/* Timer2 Enable */
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT(_PRESCALER_) (T2CONbits.T2CKPS = _PRESCALER_)

#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_) (T2CONbits.TOUTPS = _POSTSCALER_)




/* ============== Data type Declarations ============== */

typedef struct{
#if TIMER2_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 tiemr2_preload_value;
    uint8 timer2_postscaler_value: 4;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_reserved : 2;
}timer2_t;

/* ============== Software Interfaces Declarations ============== */
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *value);


#endif	/* HAL_TIMER2_H */

