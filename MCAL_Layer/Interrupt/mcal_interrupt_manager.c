/* 
 * File:   mcal_interrupt_manager.c
 * Author: sameh
 *
 * Created on August 4, 2023, 1:27 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1;
static volatile uint8 RB5_Flag = 1;
static volatile uint8 RB6_Flag = 1;
static volatile uint8 RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/* Nothing */}
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/* Nothing */}
}       
#else
void __interrupt() InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/* Nothing */}
    /* ====================PortB External on change interrupt start==================== */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
        (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 1)){
        RB5_Flag = 0;
        RB5_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 0)){
        RB5_Flag = 1;
        RB5_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 1)){
        RB6_Flag = 0;
        RB6_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
       (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 0)){
        RB6_Flag = 1;
        RB6_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 1)){
        RB7_Flag = 0;
        RB7_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 0)){
        RB7_Flag = 1;
        RB7_ISR(0);
    }
    else{/* Nothing */}
    
    /* ====================ADC interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{/* Nothing */}
    /* ====================TIMER0 interrupt start==================== */
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_ENABLE == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
    else{/* Nothing */}
    /* ====================TIMER1 interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_ENABLE == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
    else{/* Nothing */}
    /* ====================TIMER2 interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_ENABLE == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    else{/* Nothing */}
    /* ====================TIMER3 interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_ENABLE == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
    else{/* Nothing */}
    /* ====================CCP1 interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_ENABLE == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    else{/* Nothing */}
    /* ====================CCP2 interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_ENABLE == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    else{/* Nothing */}
    /* ====================ESUART TX interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_ENABLE == PIR1bits.TXIF)){
        ESUART_TX_ISR();
    }
    else{/* Nothing */}
    /* ====================ESUART RX interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_ENABLE == PIR1bits.RCIF)){
        ESUART_RX_ISR();
    }
    else{/* Nothing */}
    /* ====================SPI interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_ENABLE == PIR1bits.SSPIF)){
        SPI_ISR();
    }
    else{/* Nothing */}
    /* ====================I2C interrupt start==================== */
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_ENABLE == PIR1bits.SSPIF)){
        I2C_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_ENABLE == PIR2bits.BCLIF)){
        I2C_BC_ISR();
    }
    else{/* Nothing */}
}
#endif