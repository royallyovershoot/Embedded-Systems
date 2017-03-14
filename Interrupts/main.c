#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

#include "lcd.h"
#include "keypad.h"
#include "7seg.h"
#include "c_utils.h"

/////////////////////RTI Related//////////////////////////////////

volatile unsigned int counter_for_real_time_interrupt = 0;
                                                                

void rti_init(unsigned char rti_ctl_value, unsigned int counter_limit);
void rti_init(unsigned char rti_ctl_value, unsigned int counter_limit)
{

  /**
   * RTICTL can be calculated like:
   * i.e: RTICTL == 0x63 == set rate to 32.768ms:
   * The clock divider is set in register RTICTL and is: (N+1)*2^(M+9), 
   * where N is the bit field RTR3 through RTR0 
   * and M is the bit field RTR6 through RTR4. 
   * 0110 0011 = 0x63 ==> 1 / (4MHz / 4*2^15) == 4*2^15 / 4,000 = 32.768ms
   * 0111 1111 = 0x7F ==> 1 / (4MHz / 16*2^16) == 2^20  / 4,000 = 262.144ms
   */
  RTICTL = rti_ctl_value;

  // How many times we had RTI intruppts
  counter_for_real_time_interrupt = 0;


  // Enable RTI interrupts
  CRGINT |= 0x80;
  // Clear RTI Flag
  CRGFLG = 0x80;
}



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void rti_isr(void)
{
  //clear the RTI - don't block the other interrupts  
  CRGFLG = 0x80;
  
  if (counter_for_real_time_interrupt == 1000)  
  {  
    PORTB = 0x00;
  } 
  else if (counter_for_real_time_interrupt == 2000)  
  {
    PORTB = 0x66;
    counter_for_real_time_interrupt = 0;
  }
  counter_for_real_time_interrupt ++;    
}

/* end of isr_default */
#pragma CODE_SEG DEFAULT


/////////////////////RTI Related//////////////////////////////////


void main(void)
{
  //Defenitions - Start ///////////////////////////////////////////		
	volatile char c = 0;	//used for input_from_keypad		
	//used for the structure of our calculator a+b=c
  typedef struct my_calc
  {
    char string_a[8] ;
    char string_b[8] ;
    char string_result[16] ;
    int int_a;
    int int_b;
    int int_result;
    char operand;
  }MyCalc;
     
   int i = 0;    
  //Defenitions - END //////////////////////////////////////////////	
	
	
	/////////////////////How to use LCD - START///////////////////////
	LCD_Init();	
	LCDWriteLine(1, "Hello World!");
	LCDWriteLine(2, "Line 2 ..." ); 
	/////////////////////How to use LCD - END/////////////////////////


	///////How to use Keypad and LCD to make a calculator-Start //////
	keypad_init();
	seven_seg_init();
  
   rti_init(0x11, 1);
   asm("cli");
     
  
  for(;;) //scan forever
  {  
    MyCalc calc;
    char str[16];
    //make sure our buffer is clean and empty
    for (i = 0; i < 16; i++)
    {
      str[i] = ' ';
    }
    str[0] = '\0';
    
    
  	//now we want to read a+b=c in our calculator
  	//first we read "a+" part of the "a+b=c"
  	for (i = 0; i < 8; i++)
    {     
       c = getchar();
       if (c >=0 && c <=9) 
       {
          calc.string_a[i] = '0' + c;
          //show the digits on 7-seg LEDs for debug
          show_on_seven_seg(c, 1);  
       }
       else //user input reaches the operand
       {
          calc.string_a[i] = '\0';
          calc.operand = c;


                    
          //keys 12 to 15 ... which are the fourth of the keypad:
          //     -----------------
          //     | 0 | 1 | 2 | 3 |
          //     -----------------
          //     | 4 | 5 | 6 | 7 |
          //     -----------------
          //     | 8 | 9 | = | = |
          //     -----------------
          //     | + | - | / | * |
          //     -----------------
          if (calc.operand == 12) calc.operand = '+';
          else if (calc.operand == 13) calc.operand = '-';
          else if (calc.operand == 14) calc.operand = '/';
          else if (calc.operand == 15) calc.operand = '*';                     
          calc.int_a = atoi(calc.string_a);                        
          break;
       }
    }
    //lets update the input in our LCD
    strcat(str, calc.string_a);  
    strcat(str, " ");
    strcat_char(str, calc.operand); 
    strcat(str, " ");
    LCDWriteLine(1, str); 
    
       
    
    //here we read "b=" part in "a+b=c"
    for (i = 0; i < 16; i++)
    {
       c = getchar();
       if (c >=0 && c <=9)
       {
          calc.string_b[i] = '0' + c;
          show_on_seven_seg(c, 2);
       }
       else
       {
          calc.string_b[i] = '\0';
          calc.int_b = atoi(calc.string_b);
          break;
       }
    }
    //lets update the input in our LCD  
    strcat(str, calc.string_b);
    strcat(str, " = ");
    LCDWriteLine(1, str); 
   
   
    
    //here we calculate "c" part in "a+b=c"
    if (calc.operand == '+') calc.int_result = calc.int_a + calc.int_b;
    else if (calc.operand == '-') calc.int_result = calc.int_a - calc.int_b;
    else if (calc.operand == '/') calc.int_result = calc.int_a / calc.int_b;
    else if (calc.operand == '*') calc.int_result = calc.int_a * calc.int_b;

    //lets write the result on the second line of the LCD   
    itoa (calc.int_result, calc.string_result, 10);        
    LCDWriteLine(2, calc.string_result); 
  	
  	mSDelay(50);		
  }	
	////////How to use Keypad and LCD to make a calculator-END ///////////////
	

}
