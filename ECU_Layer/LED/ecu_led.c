/* 
 * File:   ecu_led.c
 * Author: sameh
 *
 * Created on July 7, 2023, 3:31 PM
 */

#include "ecu_led.h"
/**
 * @brief Initialize the assigned pin as output and turn the led off
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status
        };
        gpio_pin_initialize(&pin_obj);
    }
}

/**
 * @brief Turn the led ON
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
}

/**
 * @brief Turn the led OFF
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
}

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_DIRECTION_OUTPUT,
        .logic = led->led_status
        };
        gpio_pin_toggle_logic(&pin_obj);
    }
}