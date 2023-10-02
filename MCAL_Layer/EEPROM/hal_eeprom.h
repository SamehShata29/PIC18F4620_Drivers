/* 
 * File:   hal_eeprom.h
 * Author: sameh
 *
 * Created on August 8, 2023, 10:13 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* ============== Includes ============== */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ============== Macro Declarations ============== */
/* Flash Program or Data EEPROM Memory Select */
#define ACCESS_FLASH_PROGRAM_MEMORY 1
#define ACCESS_DATA_EEPROM_MEMORY   0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS 1
#define ACCESS_FLASH_EEPROM_MEMORY 0
/* Flash Program/Data EEPROM Enable */
#define ALLOW_WRITE_CYLCE_FLASH_EEPROM 1
#define INHIBIT_WRITE_CYLCE_FLASH_EEPROM 0
/* Write control */
#define INITIATES_DATA_EEPROM_WRITE_ERASE 1
#define DATA_EEPROM_WRITE_ERASE_COMPLETE 0
/* Read control */
#define INITIATES_DATA_EEPROM_READ 1
/* ============== Macro Functions Declarations ============== */


/* ============== Data type Declarations ============== */


/* ============== Software Interfaces Declarations ============== */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);


#endif	/* HAL_EEPROM_H */

