
/* 
 * File:   ecu_button.c
 * Author: sameh
 *
 * Created on July 14, 2023, 2:56 PM
 */

#include "ecu_button.h"

/**
 * @brief initialize the button pin
 * @param btn
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == btn){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&btn->button_pin);
    }
    return ret;
}

/**
 * @brief read the button state
 * @param btn
 * @param btn_state
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_NOT_OK;
    logic_t Pin_Logic_Status = GPIO_LOW;
    if((NULL == btn) || (NULL == btn_state)){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn->button_pin),&Pin_Logic_Status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(GPIO_HIGH == Pin_Logic_Status){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection){
            if(GPIO_HIGH == Pin_Logic_Status){
                *btn_state = BUTTON_RELEASED;
            }
            else{
                *btn_state = BUTTON_PRESSED;
            }
        }
        else{ /* NOTHING */ }
        ret = E_OK;
    }
    return ret;
}

