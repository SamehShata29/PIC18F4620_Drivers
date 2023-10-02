/* 
 * File:   application.h
 * Author: sameh
 *
 * Created on July 7, 2023, 3:34 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/device_config.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */

/* Section : Data Types Declarations */
extern keypad_t keypad1;
extern chr_lcd_4bit_t lcd_1;
extern chr_lcd_8bit_t lcd_2;
/* Section : Function Declarations */
void application_initialize(void);
void Int0_APP_ISR(void);
#endif	/* APPLICATION_H */

