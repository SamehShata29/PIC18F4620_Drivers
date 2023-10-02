/* 
 * File:   mcal_external_interrupt.c
 * Author: sameh
 *
 * Created on August 4, 2023, 1:26 PM
 */

#include "mcal_external_interrupt.h"

static void(*INT0_InterruptHandler)(void) = NULL;
static void(*INT1_InterruptHandler)(void) = NULL;
static void(*INT2_InterruptHandler)(void) = NULL;

static void(*RB4_InterruptHandler_HIGH)(void) = NULL;
static void(*RB4_InterruptHandler_LOW)(void) = NULL;
static void(*RB5_InterruptHandler_HIGH)(void) = NULL;
static void(*RB5_InterruptHandler_LOW)(void) = NULL;
static void(*RB6_InterruptHandler_HIGH)(void) = NULL;
static void(*RB6_InterruptHandler_LOW)(void) = NULL;
static void(*RB7_InterruptHandler_HIGH)(void) = NULL;
static void(*RB7_InterruptHandler_LOW)(void) = NULL;


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the External interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External interrupt did not occur */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External interrupt edge */
        ret = Interrupt_INTx_Edge_Init(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Configure External interrupt priority */
        ret = Interrupt_INTx_Priority_Init(int_obj);
#endif
        /* Configure External interrupt I/O pin */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Configure External interrupt CallBack */
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the External interrupt */
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

void INT0_ISR(void){
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    /* code */
    
    /* Callback function gets called every time this ISR executes */
     if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
}

void INT1_ISR(void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    /* code */
    
    /* Callback function gets called every time this ISR executes */
     if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
}

void INT2_ISR(void){
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    /* code */
    
    /* Callback function gets called every time this ISR executes */
     if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
}  
void RB4_ISR(uint8 RB4_source){
    /* The RB4 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Callback function gets called every time this ISR executes */
    if(0 == RB4_source)
    {
        if(RB4_InterruptHandler_LOW){RB4_InterruptHandler_LOW();}
    }
    else if(1 == RB4_source){
        if(RB4_InterruptHandler_HIGH){RB4_InterruptHandler_HIGH();}
    }
    else{/* Nothing */}
}
void RB5_ISR(uint8 RB5_source){
    /* The RB5 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Callback function gets called every time this ISR executes */
    if(0 == RB5_source)
    {
        if(RB5_InterruptHandler_LOW){RB5_InterruptHandler_LOW();}
    }
    else if(1 == RB5_source){
        if(RB5_InterruptHandler_HIGH){RB5_InterruptHandler_HIGH();}
    }
    else{/* Nothing */}
}
void RB6_ISR(uint8 RB6_source){
    /* The RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Callback function gets called every time this ISR executes */
    if(0 == RB6_source)
    {
        if(RB6_InterruptHandler_LOW){RB6_InterruptHandler_LOW();}
    }
    else if(1 == RB6_source){
        if(RB6_InterruptHandler_HIGH){RB6_InterruptHandler_HIGH();}
    }
    else{/* Nothing */}
}
void RB7_ISR(uint8 RB7_source){
    /* The RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Callback function gets called every time this ISR executes */
    if(0 == RB7_source)
    {
        if(RB7_InterruptHandler_LOW){RB7_InterruptHandler_LOW();}
    }
    else if(1 == RB7_source){
        if(RB7_InterruptHandler_HIGH){RB7_InterruptHandler_HIGH();}
    }
    else{/* Nothing */}
}
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* This routine clear the interrupt for the external interrupt RBx */
        EXT_RBx_InterruptDisable();
        /* This routine clears the interrupt flag for the external interrupt RBx */
        EXT_RBx_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            /* This macro will enable low priority global interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            /* This routine set the RBx External interrupt priority to be low priority */
            EXT_RBx_ProrityLow();
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
            /* This macro will enable high priority global interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            /* This routine set the RBx External interrupt priority to be high priority */
            EXT_RBx_ProrityHigh();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        /* Initialize the RBx pin to be input */
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
        /* Initialize the call back function */
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4 :
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN5 :
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN6 :
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN7 :
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            default :
                ret = E_NOT_OK;
        }
        /* This routine sets the interrupt enable for the external interrupt RBx */
        EXT_RBx_InterruptEnable();
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}
/* ==================== HELPER FUNCTIONS ====================*/
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif                
                EXT_INT1_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif               
                EXT_INT2_InterruptEnable();
                ret = E_OK;
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptDisable();
                ret = E_OK;
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT1_LowPrioritySet(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_HighPrioritySet(); }
                else{/* Nothing */}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT2_LowPrioritySet(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_HighPrioritySet(); }
                else{/* Nothing */}
                ret = E_OK;
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT0_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT0_RisingEdgeSet(); }
                else{/* Nothing */}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT1_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT1_RisingEdgeSet(); }
                else{/* Nothing */}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT2_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT2_RisingEdgeSet(); }
                else{/* Nothing */}
                ret = E_OK;
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(int_obj->mcu_pin));
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptFlagClear();
                ret = E_OK;
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
}
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
}
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
}
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}
