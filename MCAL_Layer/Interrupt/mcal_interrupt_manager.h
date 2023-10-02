/* 
 * File:   mcal_interrupt_manager.h
 * Author: sameh
 *
 * Created on August 4, 2023, 1:27 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/* =========== Section : Includes =========== */
#include "mcal_interrupt_config.h"

/* =========== Section : Macro Declarations =========== */

/* =========== Section : Macro Functions Declarations =========== */

/* =========== Section : Data Types Declarations =========== */

/* =========== Section : Function Declarations =========== */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void ESUART_TX_ISR(void);
void ESUART_RX_ISR(void);
void SPI_ISR(void);
void I2C_ISR(void);
void I2C_BC_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

