/* 
 * File:   ecu_keypad.h
 * Author: sameh
 *
 * Created on July 20, 2023, 12:38 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
/* Section : Includes */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define ECU_KEYPAD_ROW          4
#define ECU_KEYPAD_COLOUMNS     4

/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */
typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROW];
    pin_config_t keypad_coloumn_pins[ECU_KEYPAD_COLOUMNS];
}keypad_t;

/* Section : Function Declarations */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);


#endif	/* ECU_KEYPAD_H */

