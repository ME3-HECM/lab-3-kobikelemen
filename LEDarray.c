
#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers for pins connected to LED array
	//set initial output LAT values (they may have random values when powered on)
    TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
//    TRISBbits.TRISB1 = 0;
    
    LATGbits.LATG0 = 0;
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATFbits.LATF6 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATBbits.LATB0 = 0;
//    LATBbits.LATB1 = 0;
    
    
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
	//see Readme.md for examples
    
    // sets each output pin to true if the corresponding bit from number is 1
    LATGbits.LATG0 = (number & 0b000000001);
    LATGbits.LATG1 = (number & 0b000000010) >> 1;
    LATAbits.LATA2 = (number & 0b000000100) >> 2;
    LATFbits.LATF6 = (number & 0b000001000) >> 3;
    LATAbits.LATA4 = (number & 0b000010000) >> 4;
    LATAbits.LATA5 = (number & 0b000100000) >> 5;
    LATFbits.LATF0 = (number & 0b001000000) >> 6;
    LATBbits.LATB0 = (number & 0b010000000) >> 7;
//    LATBbits.LATB1 = (number & 0b100000000) >> 8;
    
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{	
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array
    unsigned int disp_val = 1;
    if (number < 10) { // don't display any lights when less than 10
        LEDarray_disp_bin(0);
        return;
    }
    int i = 10;
    unsigned int count = 0;
    while (i <= number-10) { // count number of tens that fit into number    
        disp_val = disp_val << 1;
        i += 10;
    }
    
    disp_val = disp_val << 1; // fill in all lights up disp_val-th light
    disp_val --;
    
	LEDarray_disp_bin(disp_val); //display value on LED array
}


void LED_intensity_meter(unsigned int val) {
    int num_bits_LED = 8;
    int max_val_LED = 1 << num_bits_LED;
    int delta_intensity_meter = max_val_LED / num_bits_LED; // finding what each intensity bar should represent when split equally
    int sum = 0;
    int num_lit = 0; 
    while (sum < val) { // counting number of intensity bars that fit into val, this gives proportion of LEDs that should be lit
        sum += delta_intensity_meter;
        num_lit ++;
    }
    LEDarray_disp_bin((1 << (num_lit + 1) ) - 1); // displaying all LEDs up to num_lit using bit shift
}


void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max) {
    int num_bits_LED = 8;
    int max_val_LED = 1 << num_bits_LED;
    int delta_intensity_meter = max_val_LED / num_bits_LED; // finding what each intensity bar should represent when split equally
    int sum = 0;
    int num_linear_lit = 0; 
    while (sum < cur_val) { // counting number of intensity bars that fit into cur_val, this gives proportion of LEDs that should be lit
        sum += delta_intensity_meter;
        num_linear_lit ++;
    }
    sum = 0;
    int num_max_lit = 0; 
    while (sum < max) { // counting number of intensity bars that fit into max
        sum += delta_intensity_meter;
        num_max_lit ++;
    }
    unsigned int linear_loading_bar = ((1 << (num_linear_lit + 1) ) - 1);
    unsigned int single_bar = (1 << num_max_lit);
    LEDarray_disp_bin(linear_loading_bar | single_bar); // OR them to combine in LED   
}



/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
