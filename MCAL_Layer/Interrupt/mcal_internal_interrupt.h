/* 
 * File:   mcal_internal_interrupt.h
 * Author: sameh
 *
 * Created on August 4, 2023, 1:26 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* =========== Section : Includes =========== */
#include "mcal_interrupt_config.h"

/* =========== Section : Macro Declarations =========== */


/* =========== Section : Macro Functions Declarations =========== */
#if ADC_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the ADC module */
#define ADC_InterruptDisable()              (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable the ADC module */
#define ADC_InterruptEnable()               (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC module */
#define ADC_InterruptFlagClear()            (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the ADC module Interrupt priority to be high priority */
#define ADC_HighPrioritySet()               (IPR1bits.ADIP = 1)
/* This routine set the ADC module Interrupt priority to be low priority */
#define ADC_LowPrioritySet()                (IPR1bits.ADIP = 0)
#endif
#endif


#if TIMER0_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the TIMER0 module */
#define TIMER0_InterruptDisable()              (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable the TIMER0 module */
#define TIMER0_InterruptEnable()               (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the TIMER0 module */
#define TIMER0_InterruptFlagClear()            (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TIMER0 module Interrupt priority to be high priority */
#define TIMER0_HighPrioritySet()               (INTCON2bits.TMR0IP = 1)
/* This routine set the TIMER0 module Interrupt priority to be low priority */
#define TIMER0_LowPrioritySet()                (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if TIMER1_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the TIMER1 module */
#define TIMER1_InterruptDisable()              (PIE1bits.TMR1IE = 0)
/* This routine sets the interrupt enable the TIMER1 module */
#define TIMER1_InterruptEnable()               (PIE1bits.TMR1IE = 1)
/* This routine clears the interrupt flag for the TIMER1 module */
#define TIMER1_InterruptFlagClear()            (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TIMER1 module Interrupt priority to be high priority */
#define TIMER1_HighPrioritySet()               (IPR1bits.TMR1IP = 1)
/* This routine set the TIMER1 module Interrupt priority to be low priority */
#define TIMER1_LowPrioritySet()                (IPR1bits.TMR1IP = 0)
#endif
#endif

#if TIMER2_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the TIMER2 module */
#define TIMER2_InterruptDisable()              (PIE1bits.TMR2IE = 0)
/* This routine sets the interrupt enable the TIMER2 module */
#define TIMER2_InterruptEnable()               (PIE1bits.TMR2IE = 1)
/* This routine clears the interrupt flag for the TIMER2 module */
#define TIMER2_InterruptFlagClear()            (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TIMER2 module Interrupt priority to be high priority */
#define TIMER2_HighPrioritySet()               (IPR1bits.TMR2IP = 1)
/* This routine set the TIMER1 module Interrupt priority to be low priority */
#define TIMER2_LowPrioritySet()                (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the TIMER3 module */
#define TIMER3_InterruptDisable()              (PIE2bits.TMR3IE = 0)
/* This routine sets the interrupt enable the TIMER3 module */
#define TIMER3_InterruptEnable()               (PIE2bits.TMR3IE = 1)
/* This routine clears the interrupt flag for the TIMER3 module */
#define TIMER3_InterruptFlagClear()            (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the TIMER3 module Interrupt priority to be high priority */
#define TIMER3_HighPrioritySet()               (IPR2bits.TMR3IP = 1)
/* This routine set the TIMER3 module Interrupt priority to be low priority */
#define TIMER3_LowPrioritySet()                (IPR2bits.TMR3IP = 0)
#endif
#endif

#if CCP1_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the CCP1 module */
#define CCP1_InterruptDisable()              (PIE1bits.CCP1IE = 0)
/* This routine sets the interrupt enable the CCP1 module */
#define CCP1_InterruptEnable()               (PIE1bits.CCP1IE = 1)
/* This routine clears the interrupt flag for the CCP1 module */
#define CCP1_InterruptFlagClear()            (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the CCP1 module Interrupt priority to be high priority */
#define CCP1_HighPrioritySet()               (IPR1bits.CCP1IP = 1)
/* This routine set the CCP1 module Interrupt priority to be low priority */
#define CCP1_LowPrioritySet()                (IPR1bits.CCP1IP = 0)
#endif
#endif

#if CCP2_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the CCP2 module */
#define CCP2_InterruptDisable()              (PIE2bits.CCP2IE = 0)
/* This routine sets the interrupt enable the CCP2 module */
#define CCP2_InterruptEnable()               (PIE2bits.CCP2IE = 1)
/* This routine clears the interrupt flag for the CCP2 module */
#define CCP2_InterruptFlagClear()            (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the CCP2 module Interrupt priority to be high priority */
#define CCP2_HighPrioritySet()               (IPR2bits.CCP2IP = 1)
/* This routine set the CCP1 module Interrupt priority to be low priority */
#define CCP2_LowPrioritySet()                (IPR2bits.CCP2IP = 0)
#endif
#endif

#if ESUART_TX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the ESUART_TX */
#define ESUART_TX_InterruptDisable()              (PIE1bits.TXIE = 0)
/* This routine sets the interrupt enable the ESUART_TX */
#define ESUART_TX_InterruptEnable()               (PIE1bits.TXIE = 1)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the ESUART_TX module Interrupt priority to be high priority */
#define ESUART_TX_HighPrioritySet()               (IPR1bits.TXIP = 1)
/* This routine set the ESUART_TX module Interrupt priority to be low priority */
#define ESUART_TX_LowPrioritySet()                (IPR1bits.TXIP = 0)
#endif
#endif

#if ESUART_RX_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the ESUART_RX */
#define ESUART_RX_InterruptDisable()              (PIE1bits.RCIE = 0)
/* This routine sets the interrupt enable the ESUART_RX */
#define ESUART_RX_InterruptEnable()               (PIE1bits.RCIE = 1)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the ESUART_RX module Interrupt priority to be high priority */
#define ESUART_RX_HighPrioritySet()               (IPR1bits.RCIP = 1)
/* This routine set the ESUART_RX module Interrupt priority to be low priority */
#define ESUART_RX_LowPrioritySet()                (IPR1bits.RCIP = 0)
#endif
#endif

#if SPI_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the SPI */
#define SPI_InterruptDisable()              (PIE1bits.SSPIE = 0)
/* This routine sets the interrupt enable the SPI */
#define SPI_InterruptEnable()               (PIE1bits.SSPIE = 1)
/* This routine clears the interrupt flag for the SPI module */
#define SPI_InterruptFlagClear()            (PIR1bits.SSPIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the SPI module Interrupt priority to be high priority */
#define SPI_HighPrioritySet()               (IPR1bits.SSPIP = 1)
/* This routine set the SPI module Interrupt priority to be low priority */
#define SPI_LowPrioritySet()                (IPR1bits.SSPIP = 0)
#endif
#endif

#if I2C_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable the I2C */
#define I2C_InterruptDisable()              (PIE1bits.SSPIE = 0)
#define I2C_Bus_Col_InterruptDisable()      (PIE2bits.BCLIE = 0)
/* This routine sets the interrupt enable the I2C */
#define I2C_InterruptEnable()               (PIE1bits.SSPIE = 1)
#define I2C_Bus_Col_InterruptEnable()       (PIE2bits.BCLIE = 1)
/* This routine clears the interrupt flag for the I2C module */
#define I2C_InterruptFlagClear()            (PIR1bits.SSPIF = 0)
#define I2C_Bus_Col_InterruptFlagClear()    (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the I2C module Interrupt priority to be high priority */
#define I2C_HighPrioritySet()               (IPR1bits.SSPIP = 1)
#define I2C_Bus_Col_HighPrioritySet()       (IPR2bits.BCLIP = 1)
/* This routine set the I2C module Interrupt priority to be low priority */
#define I2C_LowPrioritySet()                (IPR1bits.SSPIP = 0)
#define I2C_Bus_Col_LowPrioritySet()        (IPR2bits.BCLIP = 0)
#endif
#endif
/* =========== Section : Data Types Declarations =========== */

/* =========== Section : Function Declarations =========== */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

