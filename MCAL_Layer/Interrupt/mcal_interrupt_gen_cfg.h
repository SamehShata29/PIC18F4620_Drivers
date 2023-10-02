/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: sameh
 *
 * Created on August 4, 2023, 1:57 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/* =========== Section : Includes =========== */

/* =========== Section : Macro Declarations =========== */

#define INTERRUPT_FEATURE_ENABLE                    1U
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE            INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE      INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE  INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEAUTRE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_FEAUTRE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEAUTRE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEAUTRE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEAUTRE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_FEAUTRE_ENABLE               INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEAUTRE_ENABLE               INTERRUPT_FEATURE_ENABLE
#define ESUART_TX_INTERRUPT_FEAUTRE_ENABLE          INTERRUPT_FEATURE_ENABLE
#define ESUART_RX_INTERRUPT_FEAUTRE_ENABLE          INTERRUPT_FEATURE_ENABLE
#define SPI_INTERRUPT_FEAUTRE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define I2C_INTERRUPT_FEAUTRE_ENABLE                INTERRUPT_FEATURE_ENABLE
/* =========== Section : Macro Functions Declarations =========== */

/* =========== Section : Data Types Declarations =========== */

/* =========== Section : Function Declarations =========== */

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

