/* 
 * File:   hal_i2c.h
 * Author: sameh
 *
 * Created on September 14, 2023, 10:14 AM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H
/* ============== Includes ============== */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ============== Macro Declarations ============== */
/* Slew rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE       1
#define I2C_SLEW_RATE_ENABLE        0
/* SMBus Enable/Disable */
#define I2C_SMBus_ENABLE            1
#define I2C_SMBus_DISABLE           0
/* Slave Mode Data/Address Indication */
#define I2C_LAST_BYTE_DATA          1
#define I2C_LAST_BYTE_ADDRESS       0
/* Stop Condition indication */
#define STOP_BIT_DETECTED           1
#define STOP_BIT_NOT_DETECTED       0
/* Start Condition Indication */
#define START_BIT_DETECTED          1
#define START_BIT_NOT_DETECTED      0

/* I2C : Master or Slave Mode */
#define MSSP_I2C_MSATER_MODE        1
#define MSSP_I2C_SLAVE_MODE         0
/* Master Synchronous Serial Port Mode Select */
#define I2C_SLAVE_MODE_7BIT_ADDRESS                 0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS                0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE   0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE  0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK               0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED         0x0BU

/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE     1
#define I2C_GENERAL_CALL_DISABLE    0
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE   1
#define I2C_MASTER_RECEIVE_DISABLE  0

/* Acknowledge Status bit (Master transmit mode only) */
#define I2C_ACK_REC_FROM_SLAVE      0
#define I2C_ACK_NOT_REC_FROM_SLAVE  1

/* Acknowledge Status bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK         0
#define I2C_MASTER_SEND_NOT_ACK     1
/* ============== Macro Functions Declarations ============== */
/* Master Synchronous Serial Port Enable */
#define MSSP_MODULE_ENABLE()                (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE()               (SSPCON1bits.SSPEN = 0)
/* Slew Rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE_CFG()         (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()          (SSPSTATbits.SMP = 0)
/* SMBus Enable/Disable */
#define I2C_SMBus_DISABLE_CFG()             (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()              (SSPSTATbits.CKE = 1)
/* General Call Enable */
#define I2C_GENERAL_CALL_DISABLE_CFG()      (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE_CFG()       (SSPCON2bits.GCEN = 1)
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 1)
/* ============== Data type Declarations ============== */
typedef struct{
    uint8 i2c_mode_cfg;
    uint8 i2c_slave_address;
    uint8 i2c_mode : 1;
    uint8 i2c_slew_rate : 1;
    uint8 i2c_SMBus_control : 1;
    uint8 i2c_general_call : 1;
    uint8 i2c_master_rec_mode : 1;
    uint8 : 3;
#if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg mssp_i2c_priortiy;
    interrupt_priority_cfg mssp_i2c_bc_priortiy;
#endif
}i2c_configs_t;

typedef struct{
    uint32 i2c_clock;
#if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*I2C_Report_Write_Collision)(void);
    void(*I2C_DefaultInterruptHandler)(void);
    void(*I2C_Report_Receive_Overflow)(void);
#endif

    i2c_configs_t i2c_cfg;
}i2c_t;
/* ============== Software Interfaces Declarations ============== */
Std_ReturnType I2C_Init(const i2c_t *i2c_obj);
Std_ReturnType I2C_DeInit(const i2c_t *i2c_obj);
Std_ReturnType I2C_Master_Send_Start(const i2c_t *i2c_obj);
Std_ReturnType I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj);
Std_ReturnType I2C_Master_Send_Stop(const i2c_t *i2c_obj);
Std_ReturnType I2C_Master_Write_Blocking(const i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType I2C_Master_Read_Blocking(const i2c_t *i2c_obj, uint8 ack,uint8 *i2c_data);

#endif	/* HAL_I2C_H */

