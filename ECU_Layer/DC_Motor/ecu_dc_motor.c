/* 
 * File:   ecu_dc_motor.h
 * Author: sameh
 *
 * Created on July 18, 2023, 1:18 PM
 */
#include "ecu_dc_motor.h"


/**
 * @brief initialize the pin of dc motor to output
 * @param _dc_motor
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{        
        gpio_pin_initialize(&(_dc_motor->dc_motor[0]));
        gpio_pin_initialize(&(_dc_motor->dc_motor[1]));
        
        ret = E_OK;
    }
    return ret;
}
/**
 * @brief make the motor rotate towards right
 * @param _dc_motor
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor[0]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor[1]), GPIO_LOW);
        ret = E_OK;
    }
    return ret;
}
/**
 * @brief make the motor rotate towards left
 * @param _dc_motor
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor[1]), GPIO_HIGH);
        ret = E_OK;
    }
    return ret;
}
/**
 * @brief Stop the motor
 * @param _dc_motor
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor[1]), GPIO_LOW);
        ret = E_OK;
    }
    return ret;
}
