/* 
 * File:   ecu_layer_init.h
 * Author: sameh
 *
 * Created on July 20, 2023, 1:06 AM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "relay/ecu_relay.h"
#include "7-seg/ecu_seven_seg.h"
#include "keypad/ecu_keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"
#include "../MCAL_Layer/EEPROM/hal_eeprom.h"
#include "../MCAL_Layer/ADC/hal_adc.h"
#include "../MCAL_Layer/Timer0/hal_timer0.h"
#include "../MCAL_Layer/Timer1/hal_timer1.h"
#include "../MCAL_Layer/Timer2/hal_timer2.h"
#include "../MCAL_Layer/TImer3/hal_timer3.h"
void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

