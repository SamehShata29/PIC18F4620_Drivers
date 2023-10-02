/* 
 * File:   application.c
 * Author: sameh
 *
 * Created on July 7, 2023, 2:46 PM
 */

#include "application.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

i2c_t i2c_obj;
volatile uint8 i2c_slave2_rec_counter;

void I2C_DefaultInterruptHandler(void){
    i2c_slave2_rec_counter++;
}

int main() {
    Std_ReturnType ret = E_NOT_OK;
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_slave_address = 0x62;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE;
    i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE;
    i2c_obj.I2C_DefaultInterruptHandler = I2C_DefaultInterruptHandler;
    i2c_obj.I2C_Report_Receive_Overflow = NULL;
    i2c_obj.I2C_Report_Write_Collision = NULL;
    
    ret = I2C_Init(&i2c_obj);
    
    
    while(1){
        
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    
}
