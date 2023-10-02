/* 
 * File:   hal_i2c.h
 * Author: sameh
 *
 * Created on September 14, 2023, 10:14 AM
 */
#include "hal_i2c.h"

static inline void MSSP_I2C_MODE_GPIO_CFG(void);
static inline void I2C_Master_Mode_Clock_Configurations(const i2c_t *i2c_obj);
static inline void I2C_Interrupt_Configurations(const i2c_t *i2c_obj);
static inline void I2C_Slave_Mode_Configurations(const i2c_t *i2c_obj);


#if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*I2C_Report_Write_Collision_InterruptHandler)(void) = NULL;
static void(*I2C_DefaultInterruptHandler)(void) = NULL;
static void(*I2C_Report_Receive_Overflow_InterruptHandler)(void) = NULL;
#endif

Std_ReturnType I2C_Init(const i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE();
        /* MSSP I2C Select Mode */
        if(MSSP_I2C_MSATER_MODE == i2c_obj->i2c_cfg.i2c_mode){
            /* MSSP I2C Master Mode Configurations */
            /* I2C Master Mode Clock Configurations */
            I2C_Master_Mode_Clock_Configurations(i2c_obj);
        }
        else if(MSSP_I2C_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode){
            /* MSSP I2C Slave Mode Configurations */
            /* I2C Slave Mode General Call Configurations */
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else{/* Nothing */}
            /* Clear the Write Collision Detect */
            SSPCON1bits.WCOL = 0;
            /* Clear the Receive Overflow Indicator */
            SSPCON1bits.SSPOV = 0;
            /* Release the clock */
            SSPCON1bits.CKP = 1;
            /* Assign the I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
            /* I2C Slave Configurations */
            I2C_Master_Mode_Clock_Configurations(i2c_obj);
        }
        else{/* Nothing */}
        /* I2C Mode GPIO Configurations */
        MSSP_I2C_MODE_GPIO_CFG();
        /* MSSP I2C Slew Rate Control */
        if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
                I2C_SLEW_RATE_DISABLE_CFG();
            }
        else if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
                I2C_SLEW_RATE_ENABLE_CFG();
        }
        else{/* Nothing */}
        /* MSSP I2C SMBus Control */
        if(I2C_SMBus_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
                I2C_SMBus_DISABLE_CFG();
            }
        else if(I2C_SMBus_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
                I2C_SMBus_ENABLE_CFG();
        }
        /* Interrupt Configuration */
#if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        I2C_Interrupt_Configurations(i2c_obj);
#endif
        /* Enable MSSP I2C Module */
        MSSP_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType I2C_DeInit(const i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable MSSP I2C MODULE */
        MSSP_MODULE_DISABLE();
        /* Disable MSSP Interrupt */
#if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        I2C_InterruptDisable();
        I2C_Bus_Col_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType I2C_Master_Send_Start(const i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initiates Start Condition on SDA and SCL pins */
        SSPCON2bits.SEN = 1;
        /* Wait for the completion of the Start Condition */
        while(SSPCON2bits.SEN);
        /* Clear the MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report the Start Condition Detection */
        if(START_BIT_DETECTED == SSPSTATbits.S){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}
Std_ReturnType I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initiates Repeated Start Condition on SDA and SCL pins */
        SSPCON2bits.RSEN = 1;
        /* Wait for the completion of the Repeated Start Condition */
        while(SSPCON2bits.RSEN);
        /* Clear the MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType I2C_Master_Send_Stop(const i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initiates Stop Condition on SDA and SCL pins */
        SSPCON2bits.PEN = 1;
        /* Wait for the completion of the Stop Condition */
        while(SSPCON2bits.PEN);
        /* Clear the MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report the Stop Condition Detection */
        if(STOP_BIT_DETECTED == SSPSTATbits.P){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}
Std_ReturnType I2C_Master_Write_Blocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj || NULL == _ack){
        ret = E_NOT_OK;
    }
    else{
        /* Write Data to the Data Register */
        SSPBUF = i2c_data;
        /* wait the transmission to be completed */
        while(!PIR1bits.SSPIF);
        /* Clear the MSSP Interrupt Flag bit */
        PIR1bits.SSPIF = 0;
        /* Report the acknowledge received from the slave */
        if(I2C_ACK_REC_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *_ack = I2C_ACK_REC_FROM_SLAVE;
        }
        else{
            *_ack = I2C_ACK_NOT_REC_FROM_SLAVE;
        }
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType I2C_Master_Read_Blocking(const i2c_t *i2c_obj, uint8 ack,uint8 *i2c_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_obj || NULL == i2c_data){
        ret = E_NOT_OK;
    }
    else{
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /* Wait for buffer full flag : A complete Byte is received */
        while(!SSPSTATbits.BF);
        /* Copy the data registers to buffer variable */
        *i2c_data = SSPBUF;
        /* Send ACK or NACK after read */
        if(I2C_MASTER_SEND_ACK == ack){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN);
        }
        else if(I2C_MASTER_SEND_NOT_ACK == ack){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_NOT_ACK;
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN);
        }
        else{/* Nothing */}

        ret = E_OK;
    }
    return ret;
}

/* =================== HELPER FUNCTIONS =================== */
void I2C_ISR(void){
    #if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    I2C_InterruptFlagClear();
    if(I2C_DefaultInterruptHandler){
        I2C_DefaultInterruptHandler();
    }
    #endif
}

void I2C_BC_ISR(void){
    #if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    I2C_Bus_Col_InterruptFlagClear();
    if(I2C_Report_Write_Collision_InterruptHandler){
        I2C_Report_Write_Collision_InterruptHandler();
    }
    #endif
}


static inline void MSSP_I2C_MODE_GPIO_CFG(void){
    TRISCbits.RC3 = 1; /* SCL */
    TRISCbits.RC4 = 1; /* SDA */
}

static inline void I2C_Master_Mode_Clock_Configurations(const i2c_t *i2c_obj){
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock) - 1);
}

static inline void I2C_Slave_Mode_Configurations(const i2c_t *i2c_obj){
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
}

static inline void I2C_Interrupt_Configurations(const i2c_t *i2c_obj){
#if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
        I2C_InterruptEnable();
        I2C_Bus_Col_InterruptEnable();
        I2C_InterruptFlagClear();
        I2C_Bus_Col_InterruptFlagClear();
        I2C_Report_Write_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
        I2C_DefaultInterruptHandler = i2c_obj->I2C_DefaultInterruptHandler;
        I2C_Report_Receive_Overflow_InterruptHandler = i2c_obj->I2C_Report_Receive_Overflow;
        /* Interrupt Priority configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priortiy){
            INTERRUPT_GlobalInterruptHighEnable();
            I2C_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priortiy){
            INTERRUPT_GlobalInterruptLowEnable();
            I2C_LowPrioritySet();
        }
        else{/* NOTHING */}
        
        if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priortiy){
            INTERRUPT_GlobalInterruptHighEnable();
            I2C_Bus_Col_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priortiy){
            INTERRUPT_GlobalInterruptLowEnable();
            I2C_Bus_Col_LowPrioritySet();
        }
        else{/* NOTHING */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
}