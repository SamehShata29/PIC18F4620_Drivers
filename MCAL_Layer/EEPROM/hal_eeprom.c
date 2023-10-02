/* 
 * File:   hal_eeprom.h
 * Author: sameh
 *
 * Created on August 8, 2023, 10:13 PM
 */

#include "hal_eeprom.h"
/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    /* Read the Interrupt Status "Enabled or disabled" */
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH = (uint8)(bAdd >> 8) & 0x03;
    EEADR  = (uint8)(bAdd & 0xFF);
    /* Update the Data Register */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allow write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYLCE_FLASH_EEPROM;
    /* Disable all interrupt "General Interrupt" */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
#else
    INTERRUPT_GlobalInterruptDisable();
#endif
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATES_DATA_EEPROM_WRITE_ERASE;
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBIT_WRITE_CYLCE_FLASH_EEPROM;
    /* Restore the interrupt status Enabled/disabled */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}
/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == bData){
        ret = E_NOT_OK;
    }
    else{
        /* Update the Address Registers */
        EEADRH = (uint8)(bAdd >> 8) & 0x03;
        EEADR  = (uint8)(bAdd & 0xFF);
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATES_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* Return data */
        *bData = EEDATA;
        ret = E_OK;
    }
    return ret;
}
