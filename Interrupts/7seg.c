#include "7seg.h"


//we have 4 7-segment LEDs, which one should be active?
volatile unsigned char SEG_LED_BLOCK_INDEX = 0; //values from 0,1,2,3 are acceptable

//decode values to show on 7-seg LEDs
unsigned char sevenseg_decoder[]= { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, 0x76 };
//   correspodning numbers           0     1	    2     3     4     5     6     7     8      9     A     B     C     D    E     F     G      H


void seven_seg_init(void)
{
	DDRB = 0xFF;   // Set port B to output for LEDs (PB7:0 are LED anodes).	
	DDRP = 0xFF;   // Set port P to output, (to turn off 7-seg display).
	PTP = 0xFF;    // PP3:0 are 7-segment common cathodes: turn them off.	
  //SEG_LED_BLOCK_INDEX lets you to use block 0,1,2 and 3 of 7segment display. If you don't use PTP, the entire 4 blocks will be turned on.	
	PTP = ~ (1 << (3 - SEG_LED_BLOCK_INDEX));	
	//7-segmnets LED decoder: 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H
	//sevenseg_decoder[1] will shine 1 on 7-segment display	
	PORTB = sevenseg_decoder[0]; 
	//e.g. show 0 on the 7-segment display	
}


//c should be from 0-17 and block_index from 0-3
void show_on_seven_seg(unsigned char c, unsigned char block_index)
{
    if (block_index != SEG_LED_BLOCK_INDEX)
    {        
      SEG_LED_BLOCK_INDEX = block_index;
  	  PTP = ~ (1 << (3 - SEG_LED_BLOCK_INDEX));	    	  
    }
    
    PORTB = sevenseg_decoder[c];
}