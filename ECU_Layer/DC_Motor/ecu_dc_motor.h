/* 
 * File:   ecu_dc_motor.h
 * Author: sameh
 *
 * Created on July 18, 2023, 1:18 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H



/* Section : Includes */
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* Section : Macro Declarations */
#define DC_MOTOR_ON_STATUS 0x01U
#define DC_MOTOR_OFF_STATUS 0x00U
/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */

typedef struct{
    pin_config_t dc_motor[2];
}dc_motor_t;

/* Section : Function Declarations */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

