/* 
 * File:   ecu_seven_seg.c
 * Author: sameh
 *
 * Created on July 19, 2023, 9:43 PM
 */

#include "ecu_seven_seg.h"

/**
 * 
 * @param seg
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == seg){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
        ret = E_OK;
    }
    return ret;
}
/**
 * 
 * @param seg
 * @param number
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == seg) || (number > 9)){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), number&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), (number >> 1)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), (number >> 2)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), (number >> 3)&0x01);
        ret = E_OK;
    }
    return ret;
}
