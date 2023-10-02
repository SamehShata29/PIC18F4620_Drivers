/* 
 * File:   hal_adc.h
 * Author: sameh
 *
 * Created on August 21, 2023, 11:20 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/* ============== Includes ============== */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "hal_adc_cfg.h"

/* ============== Macro Declarations ============== */

#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define ADC_RESULT_RIGHT    0x01U
#define ADC_RESULT_LEFT     0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLED   0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLED  0x00U

/* ============== Macro Functions Declarations ============== */

/* A/D Conversion Status : A/D conversion in progress - A/D Idle */
#define ADC_CONVERSION_STATUS()     (ADCON0bits.GO_nDONE)

/*
 * @breif Start the Analog-To-Digital Conversion
 */
#define ADC_START_CONVERSION()      (ADCON0bits.GODONE = 1)

/**
 *@brief  Analog-To-Digital Control
 *@note   ADC_CONVERTER_ENABLE()  : Enable the Analog-To-Digital 
 *        ADC_CONVERTER_DISABLE() : Disable the Analog-To-Digital
 */
#define ADC_CONVERTER_ENABLE()      (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()     (ADCON0bits.ADON = 0)

/*
 *@brief Voltage Reference configuration
 * @note ADC_ENABLE_VOLTAGE_REFERENCE()  : Voltage ref is VREF- & VREF+
 *       ADC_DISABLE_VOLTAGE_REFERENCE() : Voltage ref is VSS & VDD
 * 
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG0 = 1;\
                                           ADCON1bits.VCFG1 = 1;\
                                          }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG0 = 0;\
                                            ADCON1bits.VCFG1 = 0;\
                                          }while(0)

/*
 *@brief Analog-To_Digital Port Configuration Control
 *@note  Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
 *       when ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *       AN4,AN3,AN2,AN1,AN0 are Analog
 *@ref   Analog-To_Digital Port Configuration Control
 */        
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

/*
 *@brief A/D Result Format Select
 */
#define ADC_RESULT_RIGHT_FORMAT()   (ADCON2bits.ADFM = ADC_RESULT_RIGHT)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON2bits.ADFM = ADC_RESULT_LEFT)

/* ============== Data type Declarations ============== */

typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,            
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,            
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,            
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,            
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,            
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,            
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    adc_acquisition_time_t acquisition_time; /* @ref adc_acquisition_time_t*/
    adc_conversion_clock_t conversion_clock; /* @ref adc_conversion_clock_t*/
    adc_channel_select_t adc_channel;        /* @ref adc_channel_select_t */
    uint8 voltage_reference : 1;             /* Voltage reference configuration */
    uint8 result_format : 1;                 /* A/D Result Format Select */
    uint8 ADC_Reserved  : 6;
}adc_conf_t;
/* ============== Software Interfaces Declarations ============== */
Std_ReturnType ADC_Init(const adc_conf_t *_adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, uint16 *conversion_result);
Std_ReturnType ADC_GetConvcersion_Blocking(const adc_conf_t *_adc,
                                           adc_channel_select_t channel,
                                           uint16 *conversion_result);
Std_ReturnType ADC_StartConvcersion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

