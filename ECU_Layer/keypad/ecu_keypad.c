/* 
 * File:   ecu_keypad.c
 * Author: sameh
 *
 * Created on July 20, 2023, 12:38 AM
 */

#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROW][ECU_KEYPAD_COLOUMNS] ={
                                                                        {'7', '8', '9', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'},
                                                                    };

/**
 * 
 * @param _keypad_obj
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_NOT_OK;
    uint8 rows_counter = 0, cols_counter = 0;
    if(NULL == _keypad_obj){
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROW; rows_counter++){
            ret = gpio_pin_initialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(cols_counter = 0; cols_counter < ECU_KEYPAD_COLOUMNS; cols_counter++){
            ret = gpio_pin_initialize(&(_keypad_obj->keypad_coloumn_pins[cols_counter]));
        }
    }
    return ret;
}
/**
 * 
 * @param _keypad_obj
 * @param value
 * @return Status of the function
 *         (E_OK) :  The function done successfully
 *         (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_NOT_OK;
    uint8 rows_counter = 0, cols_counter = 0, counter = 0;
    logic_t coloumn_logic = GPIO_LOW;
    if((NULL == _keypad_obj) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROW; rows_counter++){
            for(counter = 0; counter < ECU_KEYPAD_ROW; counter++){
                gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[counter]),GPIO_LOW);
            }
            gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[rows_counter]),GPIO_HIGH);
            for(cols_counter = 0; cols_counter < ECU_KEYPAD_COLOUMNS; cols_counter++){
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_coloumn_pins[cols_counter]), &coloumn_logic);
                if(GPIO_HIGH == coloumn_logic){
                    *value = btn_values[rows_counter][cols_counter];
                }
            }
            
        }
    }
    return ret;
}
