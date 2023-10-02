/* 
 * File:   mcal_external_interrupt.h
 * Author: sameh
 *
 * Created on August 4, 2023, 1:26 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/* =========== Section : Includes =========== */
#include "mcal_interrupt_config.h"

/* =========== Section : Macro Declarations =========== */


/* =========== Section : Macro Functions Declarations =========== */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the external interrupt INT0 */
#define EXT_INT0_InterruptDisable()         (INTCONbits.INT0E = 0)
/* This routine sets the interrupt enable for the external interrupt INT0 */
#define EXT_INT0_InterruptEnable()          (INTCONbits.INT0E = 1)
/* This routine clears the interrupt flag for the external interrupt INT0 */
#define EXT_INT0_InterruptFlagClear()       (INTCONbits.INT0F = 0) 
/* This routine set the edge detect of the external interrupt INT0 to negative edge */
#define EXT_INT0_FallingEdgeSet()           (INTCON2bits.INTEDG0 = 0)
/* This routine set the edge detect of the external interrupt INT0 to positive edge */
#define EXT_INT0_RisingEdgeSet()            (INTCON2bits.INTEDG0 = 1)

/* This routine clears the interrupt enable for the external interrupt INT1 */
#define EXT_INT1_InterruptDisable()         (INTCON3bits.INT1E = 0)
/* This routine sets the interrupt enable for the external interrupt INT1 */
#define EXT_INT1_InterruptEnable()          (INTCON3bits.INT1E = 1)
/* This routine clears the interrupt flag for the external interrupt INT1 */
#define EXT_INT1_InterruptFlagClear()       (INTCON3bits.INT1F = 0) 
/* This routine set the edge detect of the external interrupt INT1 to negative edge */
#define EXT_INT1_FallingEdgeSet()           (INTCON2bits.INTEDG1 = 0)
/* This routine set the edge detect of the external interrupt INT1 to positive edge */
#define EXT_INT1_RisingEdgeSet()            (INTCON2bits.INTEDG1 = 1)

/* This routine clears the interrupt enable for the external interrupt INT2 */
#define EXT_INT2_InterruptDisable()         (INTCON3bits.INT2E = 0)
/* This routine sets the interrupt enable for the external interrupt INT2 */
#define EXT_INT2_InterruptEnable()          (INTCON3bits.INT2E = 1)
/* This routine clears the interrupt flag for the external interrupt INT2 */
#define EXT_INT2_InterruptFlagClear()       (INTCON3bits.INT2F = 0) 
/* This routine set the edge detect of the external interrupt INT2 to negative edge */
#define EXT_INT2_FallingEdgeSet()           (INTCON2bits.INTEDG2 = 0)
/* This routine set the edge detect of the external interrupt INT2 to positive edge */
#define EXT_INT2_RisingEdgeSet()            (INTCON2bits.INTEDG2 = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the INT1 External Interrupt priority to be high priority */
#define EXT_INT1_HighPrioritySet()          (INTCON3bits.INT1IP = 1)
/* This routine set the INT1 External Interrupt priority to be low priority */
#define EXT_INT1_LowPrioritySet()           (INTCON3bits.INT1IP = 0)
/* This routine set the INT2 External Interrupt priority to be high priority */
#define EXT_INT2_HighPrioritySet()          (INTCON3bits.INT2IP = 1)
/* This routine set the INT2 External Interrupt priority to be low priority */
#define EXT_INT2_LowPrioritySet()           (INTCON3bits.INT2IP = 0)

#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the external interrupt, RBx */
#define EXT_RBx_InterruptDisable()          (INTCONbits.RBIE = 0)
/* This routine sets the interrupt enable for the external interrupt, RBx */
#define EXT_RBx_InterruptEnable()           (INTCONbits.RBIE = 1)
/* This routine clears the interrupt flag for the external interrupt, RBx */
#define EXT_RBx_InterruptFlagClear()        (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the RBx External interrupt priority to be high priority */
#define EXT_RBx_ProrityHigh()               (INTCON2bits.RBIP = 1)
/* This routine set the RBx External interrupt priority to be low priority */
#define EXT_RBx_ProrityLow()                (INTCON2bits.RBIP = 0)
#endif

#endif
/* =========== Section : Data Types Declarations =========== */
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE       
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2,
}interrupt_INTx_src;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;

typedef struct{
    void (* EXT_InterruptHandler_HIGH)(void);
    void (* EXT_InterruptHandler_LOW)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;

/* =========== Section : Function Declarations =========== */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

