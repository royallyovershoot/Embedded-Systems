#include <hidef.h>      /* common defines and macros */
#include <mc9s12dp256.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


  
  
#define LCD_DATA PORTK
#define LCD_CTRL PORTK
#define RS 0x01
#define EN 0x02

void COMWRT4(unsigned char);
void DATWRT4(unsigned char);
void MSDelay(unsigned int);
void mSDelay(unsigned int);

int readNumber(void);
int numDigits(int digit);
char readInput(void);

void calculate(int num1, char opchar, int num2);

void printNumber(int num);
void output(char val, int digit);

const unsigned char charmap[4][4] =
{
'1','2','3','+',
'4','5','6','-',
'7','8','9','*',
'!','0','=','/'
};


//Easier look up table numlist[0] = 0, [1] = 1 etc
char numlist[10] = {
'0', '1', '2', '3' ,'4' ,'5' ,'6' ,'7' ,'8' ,'9'
};

unsigned char column,row;

int num1 = 0, num2 = 0, res = 0;
char opchar = '0';






void main(void) 
{
    DDRA = 0x0F;                        //MAKE ROWS INPUT AND COLUMNS OUTPUT
    DDRK = 0xFF;
   
          COMWRT4(0x01);  //Clear display
          MSDelay(1);
          COMWRT4(0x80);  //set start posistion, home positio
          MSDelay(1);
            
        while(1) {

            char ans[4];
          
            char digit[2];
            
            char secondDigit[2];
            
            
            digit[0] = readInput();          
            digit[1] = readInput();
            
			
			//1 digit
			
            if ((digit[1] == '+') || (digit[1] == '-') || (digit[1] == '*') || (digit[1] == '/')){
             opchar = digit[1];
             num1 = atoi(digit);
             
             digit[0] = readInput();
             digit[1] = readInput();
              
			  // 1 digit op 1 digit
              if (digit[1] == '='){
              
               num2 = atoi(digit);
               
               calculate(num1, opchar, num2);
               
               COMWRT4(0x01);  //Clear display
               MSDelay(1);
               COMWRT4(0x80);  //set start posistion, home positio
               MSDelay(1);
                
              } 
              
			  //1 op 2
              else 
              {
          
                num2 = atoi(digit);
              
                DATWRT4('=');
                calculate(num1, opchar, num2);
   
                
                COMWRT4(0x01);  //Clear display
                MSDelay(1);
                COMWRT4(0x80);  //set start posistion, home positio
                MSDelay(1);
              }
              
            } 
			
			//2 digit 
            else {
             

              num1 = atoi(digit);         
              opchar = readInput();
             
             
              digit[0] = readInput();
              digit[1] = readInput();
			  
			  //2 digit op 1
              
              if (digit[1] == '='){
              
               num2 = atoi(digit);
               
               calculate(num1, opchar, num2);
               
               COMWRT4(0x01);  //Clear display
               MSDelay(1);
               COMWRT4(0x80);  //set start posistion, home positio
               MSDelay(1);
                
              } 
			  
			  //2 digit op 2
              
              else 
              {
          
                num2 = atoi(digit);
              
                DATWRT4('=');
                calculate(num1, opchar, num2);
   
                
                COMWRT4(0x01);  //Clear display
                MSDelay(1);
                COMWRT4(0x80);  //set start posistion, home positio
                MSDelay(1);
              }
            }
            
        
        }   //CLOSE WHILE
     
        
        
          
     
        
 
        
        
        
        
	
} //CLOSE MAIN



/**********************SUBROUTINES***********/
void mSDelay(unsigned int itime){
   unsigned int i; unsigned int j;
   for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);
}


//Calculates the amount of digits in a number
int numDigits(int digit){
  int count = 0;
    while(digit != 0)
    {
        digit /= 10;
        ++count;
    }
    return count;
}

/*
Takes two numbers and arithmetic operator and calcualtes the result.
Maxium 2 digit operations. 
It then converts the Integer value to a Character array 
and displays it.
It waits 2 seconds, and in the main function it clears the display
for next set of operations. 
*/
void calculate(int num1, char opchar, int num2){

   int res;
   char ans[4];

   if(opchar == '+') {
	   res = num1 + num2;
   } else if(opchar == '-') {
       res = num1 - num2; 
   } else if(opchar == '*') {
       res = num1 * num2;
   } else if(opchar == '/' && num2 != 0) {
       res = num1 / num2; 
   } else {
       res = 0; 
   } 
                sprintf(ans, "%d", res);
                
                if(numDigits(res)== 1){
                
                  DATWRT4(ans[0]);
                  MSDelay(5);
                  
                } else if (numDigits(res) == 2){
                
                  DATWRT4(ans[0]);
                  MSDelay(5);
                  DATWRT4(ans[1]);
                  MSDelay(5);
                  
                } else if (numDigits(res) == 3){
                
                  DATWRT4(ans[0]);
                  MSDelay(5);
                  DATWRT4(ans[1]);
                  MSDelay(5);
                  DATWRT4(ans[2]);
                  MSDelay(5);
                  
                } else if (numDigits(res) == 4){
                
                  DATWRT4(ans[0]);
                  MSDelay(5);
                  DATWRT4(ans[1]);
                  MSDelay(5);
                  DATWRT4(ans[2]);
                  MSDelay(5);
                  DATWRT4(ans[3]);
                
                }

                
                
                MSDelay(2000);

}


int readNumber() {
char input = readInput();

   if(input > '0' && input < '9') {
        return input - '0';  
      } else {
        return 0;  
      } 
      
}

char readInput() {
    char input;

    do{                                 //OPEN do1
       PORTA = PORTA | 0x0F;            //COLUMNS SET HIGH
       row = PORTA & 0xF0;              //READ ROWS
    }while(row == 0x00);                //WAIT UNTIL KEY PRESSED //CLOSE do1


    do{                                 //OPEN do2
       do{                              //OPEN do3
          mSDelay(1);                   //WAIT
          row = PORTA & 0xF0;           //READ ROWS
       }while(row == 0x00);             //CHECK FOR KEY PRESS //CLOSE do3
       
       mSDelay(7);                      //WAIT FOR DEBOUNCE
       row = PORTA & 0xF0;
    }while(row == 0x00);                //FALSE KEY PRESS //CLOSE do2

    while(1){                           //OPEN while(1)
       PORTA &= 0xF0;                   //CLEAR COLUMN
       PORTA |= 0x01;                   //COLUMN 0 SET HIGH
       row = PORTA & 0xF0;              //READ ROWS
       if(row != 0x00){                 //KEY IS IN COLUMN 0
          column = 0;
          break;                        //BREAK OUT OF while(1)
       }
       PORTA &= 0xF0;                   //CLEAR COLUMN
       PORTA |= 0x02;                   //COLUMN 1 SET HIGH
       row = PORTA & 0xF0;              //READ ROWS
       if(row != 0x00){                 //KEY IS IN COLUMN 1
          column = 1;
          break;                        //BREAK OUT OF while(1)
       }

       PORTA &= 0xF0;                   //CLEAR COLUMN
       PORTA |= 0x04;                   //COLUMN 2 SET HIGH
       row = PORTA & 0xF0;              //READ ROWS
       if(row != 0x00){                 //KEY IS IN COLUMN 2
          column = 2;
          break;                        //BREAK OUT OF while(1)
       }
       PORTA &= 0xF0;                   //CLEAR COLUMN
       PORTA |= 0x08;                   //COLUMN 3 SET HIGH
       row = PORTA & 0xF0;              //READ ROWS
       if(row != 0x00){                 //KEY IS IN COLUMN 3
          column = 3;
          break;                        //BREAK OUT OF while(1)
       }
       row = 0;                         //KEY NOT FOUND
       break;                           //step out of while(1) loop to not get stuck
    }                                   //end while(1)

    if(row == 0x10){
       //PORTK = keypad[0][column];         //OUTPUT TO PORTB LED
       input = charmap[0][column];
       DATWRT4(input);
    }
    else if(row == 0x20){
     //  PORTK = keypad[1][column];
       input = charmap[1][column];
       DATWRT4(input);
    }
    else if(row == 0x40){
     //  PORTK = keypad[2][column];
       input = charmap[2][column];
       DATWRT4(input);
    }
    else if(row == 0x80){
     //  PORTK = keypad[3][column];
       input = charmap[3][column];
       DATWRT4(input);
    }
    
  

    do{
       mSDelay(15);
       PORTA = PORTA | 0x0F;            //COLUMNS SET HIGH
       row = PORTA & 0xF0;              //READ ROWS
    }while(row != 0x00);                //MAKE SURE BUTTON IS NOT STILL HELD
    
    return input;
}

void COMWRT4(unsigned char command)
  {
        unsigned char x;
        
        x = (command & 0xF0) >> 2;         //shift high nibble to center of byte for Pk5-Pk2
      LCD_DATA =LCD_DATA & ~0x3C;          //clear bits Pk5-Pk2
        LCD_DATA = LCD_DATA | x;          //sends high nibble to PORTK
        MSDelay(1);
        LCD_CTRL = LCD_CTRL & ~RS;         //set RS to command (RS=0)
        MSDelay(1);
        LCD_CTRL = LCD_CTRL | EN;          //rais enable
        MSDelay(5);
        LCD_CTRL = LCD_CTRL & ~EN;         //Drop enable to capture command
        MSDelay(15);                       //wait
        x = (command & 0x0F)<< 2;          // shift low nibble to center of byte for Pk5-Pk2
        LCD_DATA =LCD_DATA & ~0x3C;         //clear bits Pk5-Pk2
        LCD_DATA =LCD_DATA | x;             //send low nibble to PORTK
        LCD_CTRL = LCD_CTRL | EN;          //rais enable
        MSDelay(5);
        LCD_CTRL = LCD_CTRL & ~EN;         //drop enable to capture command
        MSDelay(15);
  }

         void DATWRT4(unsigned char data)
  {
  unsigned char x;
       
        
        
        x = (data & 0xF0) >> 2;
        LCD_DATA =LCD_DATA & ~0x3C;                     
        LCD_DATA = LCD_DATA | x;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL | RS;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL | EN;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL & ~EN;
        MSDelay(5);
       
        x = (data & 0x0F)<< 2;
        LCD_DATA =LCD_DATA & ~0x3C;                     
        LCD_DATA = LCD_DATA | x;
        LCD_CTRL = LCD_CTRL | EN;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL & ~EN;
        MSDelay(15);
  }


 void MSDelay(unsigned int itime)
  {
    unsigned int i; unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);
 }