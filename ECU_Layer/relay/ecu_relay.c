/* 
 * File:   ecu_relay.c
 * Author: sameh
 *
 * Created on July 16, 2023, 11:31 AM
 */


#include "ecu_relay.h"
/**
 * @brief initial relay pin to output
 * @param _relay
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_initialize(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = _relay->relay_port,
            .pin  = _relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        gpio_pin_initialize(&pin_obj);
        ret = E_OK;
    }
    return ret;
}
/**
 * @breif apply 5v to relay pin
 * @param _relay
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = _relay->relay_port,
            .pin  = _relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
        ret = E_OK;
    }
    return ret;
}
/**
 * @brief apply 0v to relay pin
 * @param _relay
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = _relay->relay_port,
            .pin  = _relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj , GPIO_LOW);

        ret = E_OK;
    }
    return ret;
}


