#include <msp430g2553.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0; /*se selecciona bit0 como salida */
	P1OUT |= BIT0; //se selecciona salida en alto

	P1DIR &= ~BIT3; //se selecciona bit3 como entrada
	P1REN |=  BIT3; //se habilita resistencia de pull-up
	P1OUT |= BIT3; // se habilita salida en alto
	P1IES |= BIT3; //se habilita una interrupción de flanco
	P1IE |= BIT3; //se activa la interrupción en alto

	__enable_interrupt();

	for(;;){}
	
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void ISR_SW(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) ISR_SW (void)
#else
#error Compiler not supported!
#endif
{
    if((P1IN&BIT3)!=BIT3){ //se compara si la entrada ha cambiado
        P1OUT ^=BIT0; //se cambia el estado del led
        P1IFG &=~BIT3; //se apaga la bandera una vez acabada la interrupción.
    }

}


