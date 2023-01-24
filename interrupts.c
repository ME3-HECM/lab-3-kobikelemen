#include <xc.h>
#include "interrupts.h"
#include "LEDarray.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
    PIE2bits.C1IE = 1; 	//enable interrupt source C1IE
    INTCONbits.GIE = 1;
//    PIE0bits.INT0IE=1; 	//enable interrupt source INT0
//    INTCONbits.GIE=1; 
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
    if(PIR2bits.C1IF) {    //check the interrupt source
        LEDarray_disp_bin(100);
        PIR2bits.C1IF = 0;  //clear the interrupt flag!
	}
//    if(PIR0bits.INT0IF) {    //check the interrupt source
//        
//        LEDarray_disp_bin(100);
//        PIR0bits.INT0IF = 0;  //clear the interrupt flag!
//	}
}

//void __interrupt(high_priority) HighISR()
//{
//	if(PIR0bits.INT0IF){ 					//check the interrupt source
////	some code you want to execute here;
//        LEDarray_disp_bin(100);
//        PIR0bits.INT0IF=0; 						//clear the interrupt flag!
//	}
//}

