
#include <hidef.h>
  /* common defines and macros */
#include <mc9s12dp256.h> /* MicroController derivative information */

  #pragma LINK_INFO DERIVATIVE "mc9s12dp256b"
  //*********************************************************
  //Title:    Keypad input to PORTB LED 
  //          Based on Example 12.4C                        *
  //          HCS12 Microcontroller And Embedded Systems    *
  //          Using Assembly and C with CodeWarrior         *
  //          1st Edition                                   *
  //          by Hussam Eid     
  //Platform: Wytec Dragon12 plus Dev board                 *
  //Compiler: Feescale CodeWarrior IDE v5.9.0               *

//*********************************************************
//On Dragon12+ board, the rows and columns of 4x4 keypad are connected to PORTA. 
//See page 26 of Dragon12+ User's Manual
//As you press any key the ASCII value for the key is placed on the LEDs of PORTB

/*
  Notes for Continuation:
  Already all the values are stored in the arrays . All you have to do is get the values from array content from 8 to 11 and display them
*/
#define CONTLEN 16
# define MAXNUM 2
void mSDelay(unsigned int); //delay function
void WhichSegement(int c); //determines which of the 4 segements to display the number
void OperationAct(int Operation); //performs the addition, sub,div,mult.
void putInArray(int location, char value);
void ClearPad(void);
void dp(void);
void r1(void);
void r2(void);
void r3(void);
void r4(void);
void InitializeArray(void);
int fromBunchOfNumbersToOneInteger(int from,int to,int[] a);
void subMain(void);
void EqualsButtonPressed(void);
int hextoInt(char convertIT);
int next = -1;
int equals = 0;
int clearAll = 0;
int count = -1;
int loc = 0; //location
int arithmeticOP = 0; //verifies if an arithmetic operation button is pressed
int operation = 0; //determines what type of arithmetic operation is pressed
int content[CONTLEN];
unsigned char ENTRIES[CONTLEN];

unsigned char PPS[] = {
  0x0E,
  0x0D,
  0x0B,
  0x07
};
const unsigned char keypad[4][4] = {
  '1',
  '2',
  '3',
  'A',
  '4',
  '5',
  '6',
  'B',
  '7',
  '8',
  '9',
  'C',
  '*',
  '0',
  '#',
  'D'
};
unsigned char column, row;

/**************MAIN*******************************/
void main(void) { //OPEN MAIN
InitializeArray();//set all memory array to zeros
  subMain();//go to initializing the buttons and display.
  
}
/*
Populating the array with zeross, like Amigos
*/
void InitializeArray(void)
{
	int n=0;
	while(n!=CONTLEN)
	{
		content[n]=0 ;
		n++;
	}
}
void dp(void) //Displays numbers based on keypad
  {
    PTP = PPS[0];
    r1();
    r2();
    r3();
    r4();

    if (count < 4 && arithmeticOP == 0) {
      WhichSegement(count);
    } else if (count >= 4) {
      count = 0;
    }

  }
void EqualsButtonPressed(void) {
  OperationAct(operation);

}

/*
Performs the addition , subtraction , multiplication and division act based on the Alpha buttons pressed on the board
*/
void OperationAct(int Operation) {
	switch(Operation)
	{
		case 1: fromContentToDsiplay(8,11, fromBunchOfNumbersToOneInteger(0,3,content[]) + fromBunchOfNumbersToOneInteger(4,7,content[]));break;//save the sum of the two numbers into the array position 8 to 11.
		case 2: fromContentToDsiplay(8,11, fromBunchOfNumbersToOneInteger(0,3,content[]) + fromBunchOfNumbersToOneInteger(4,7,content[]));break;//save the sum of the two numbers into the array position 8 to 11.
		case 3: fromContentToDsiplay(8,11, fromBunchOfNumbersToOneInteger(0,3,content[]) * fromBunchOfNumbersToOneInteger(4,7,content[]));break;//save the sum of the two numbers into the array position 8 to 11.
		case 4: fromContentToDsiplay(8,11, fromBunchOfNumbersToOneInteger(0,3,content[]) / fromBunchOfNumbersToOneInteger(4,7,content[]));break;//save the sum of the two numbers into the array position 8 to 11.
	}
  next = 0;
}
void fromContentToDsiplay(int from,int  to, int num)
{
	/*Converts a given number to array*/
	int j;
	for(j=from;j=<to;j++)
		content[j]=
	
	for (int i = from; i <=to; ++i, num /= 10)
        content[i] = num % 10;
}
/*
Converts the arrays of Numbers to actual integer , for instance on 7 seg disp: 1 | 2 | 4| ---> return 124
*/
int fromBunchOfNumbersToOneInteger(int from,int to,int[] a)
{	int* n=length;
	int i=from, k = 0;
for (i = 0; i =< to; i++)
   return k = 10 * k + a[i];
}
void ClearPad(void) {
    //clears the pad from all values entered and clears the memory array conentLen
	InitializeArray();
	next=0;
  }
/*
Converts given hex values of the 7-segment display into integers 
*/
int hextoInt(char convertIT) {
    switch (convertIT) {
    case 0x3F:
      return 0;
      break;
    case 0x06:
      return 1;
      break;
    case 0x5B:
      return 2;
      break;
    case 0x4F:
      return 3;
      break;
    case 0x66:
      return 4;
      break;
    case 0x6D:
      return 5;
      break;
    case 0x7D:
      return 6;
      break;
    case 0x07:
      return 7;
      break;
    case 0x7F:
      return 8;
      break;
    case 0x67:
      return 9;
      break;
    }
  }
  /**
  Decides which of the 4 segments to display
  */
void WhichSegement(int c) {
  switch (c) {
  case 0:
    PTP = PPS[0];
    break;
  case 1:
    PTP = PPS[1];
    break;
  case 2:
    PTP = PPS[2];
    break;
  case 3:
    PTP = PPS[3];
    break;
  case 20:
    PTP = 0;

  }
}

  /*
  Puts the user input into an array
  */
void putInArray(int location, char value) {

  if (location > 15) {
    loc = 0;
  } else {
    ENTRIES[location] = value;
  }

  /**********************SUBROUTINES***********/
  /**
  Does the arithmetic if 
  operation=1 add
  operation=2 sub
  operation=3 divide
  operation=4 multiply
  */
}

void r1(void) {
  if (row == 0x10 && column == 0) {
    // PORTB=keypad[0][column];         //OUTPUT TO PORTB LED
    PORTB = 0x06;

    ++count;
  } else if (row == 0x10 && column == 1) {
    PORTB = 0x5B;
    ++count;
  } else if (row == 0x10 && column == 2) {
    PORTB = 0x4F;
    ++count;
  } else if (row == 0x10 && column == 3) {
    arithmeticOP = 1;
    operation = 1;
  }
  ++next;
  content[next] = convertIT(PORTB);
}
void r2(void) {
  if (row == 0x20 && column == 0) {
    // PORTB=keypad[0][column];         //OUTPUT TO PORTB LED
    PORTB = 0x66;
    ++count;
  } else if (row == 0x20 && column == 1) {
    PORTB = 0x6D;
    ++count;
  } else if (row == 0x20 && column == 2) {
    PORTB = 0x7D;
    ++count;
  } else if (row == 0x20 && column == 3) {
    arithmeticOP = 1;
    operation = 2;
  }
  ++next;
  content[next] = convertIT(PORTB);
}
void r3(void) {
  if (row == 0x40 && column == 0) {
    // PORTB=keypad[0][column];         //OUTPUT TO PORTB LED
    PORTB = 0x07;
    ++count;
  } else if (row == 0x40 && column == 1) {
    PORTB = 0x7F;
    ++count;
  } else if (row == 0x40 && column == 2) {
    PORTB = 0x67;
    ++count;
  } else if (row == 0x40 && column == 3) {
    arithmeticOP = 1;
    operation = 3;
  }
  ++next;
  content[next] = convertIT(PORTB);
}

void r4(void) {
  if (clearAll == 1) // if the clear all button is pressed.
  {
    ClearPad();
  }

  if (row == 0x80 && column == 1) {
    PORTB = 0x3F;
    ++count;
    ++next;
    content[next] = convertIT(PORTB); //putting the content into the next portB
  } else if (row == 0x80 && column == 3) {
    //CONVERT TO DIVISION
    arithmeticOP = 1;
    operation = 4;
  } else if (row == 0x80 && column == 2) {
    //clear all signal
    EqualsButtonPressed();
  } else if (row == 0x80 && column == 0) {
    //clear all signal
    clearAll = 1;
  }

}
void subMain(void) {
  DDRB = 0xFF; //MAKE PORTB OUTPUT
  DDRP |= 0xFF;
  PTP &= ~0x02; //ACTIVATE LED ARRAY ON PORT B
  DDRJ |= 0x0F; //
  PTJ |= 0x0F; //TURN OFF 7SEG LED
  DDRA = 0x0F; //MAKE ROWS INPUT AND COLUMNS OUTPUT
  while (1) { //OPEN WHILE(1)
    do { //OPEN do1
      PORTA = PORTA | 0x0F; //COLUMNS SET HIGH
      row = PORTA & 0xF0; //READ ROWS
    } while (row == 0x00); //WAIT UNTIL KEY PRESSED //CLOSE do1

    do { //OPEN do2
      do { //OPEN do3
        mSDelay(1); //WAIT
        row = PORTA & 0xF0; //READ ROWS
      } while (row == 0x00); //CHECK FOR KEY PRESS //CLOSE do3

      mSDelay(15); //WAIT FOR DEBOUNCE
      row = PORTA & 0xF0;
    } while (row == 0x00); //FALSE KEY PRESS //CLOSE do2

    while (1) { //OPEN while(1)
      PORTA &= 0xF0; //CLEAR COLUMN
      PORTA |= 0x01; //COLUMN 0 SET HIGH
      row = PORTA & 0xF0; //READ ROWS
      if (row != 0x00) { //KEY IS IN COLUMN 0
        column = 0;
        break; //BREAK OUT OF while(1)
      }
      PORTA &= 0xF0; //CLEAR COLUMN
      PORTA |= 0x02; //COLUMN 1 SET HIGH
      row = PORTA & 0xF0; //READ ROWS
      if (row != 0x00) { //KEY IS IN COLUMN 1
        column = 1;
        break; //BREAK OUT OF while(1)
      }

      PORTA &= 0xF0; //CLEAR COLUMN
      PORTA |= 0x04; //COLUMN 2 SET HIGH
      row = PORTA & 0xF0; //READ ROWS
      if (row != 0x00) { //KEY IS IN COLUMN 2
        column = 2;
        break; //BREAK OUT OF while(1)
      }
      PORTA &= 0xF0; //CLEAR COLUMN
      PORTA |= 0x08; //COLUMN 3 SET HIGH
      row = PORTA & 0xF0; //READ ROWS
      if (row != 0x00) { //KEY IS IN COLUMN 3
        column = 3;
        break; //BREAK OUT OF while(1)
      }
      row = 0; //KEY NOT FOUND
      break; //step out of while(1) loop to not get stuck
    }
    dp(); //go to display function

    do {
      mSDelay(15);
      PORTA = PORTA | 0x0F; //COLUMNS SET HIGH
      row = PORTA & 0xF0; //READ ROWS
    } while (row != 0x00); //MAKE SURE BUTTON IS NOT STILL HELD
  } //CLOSE WHILE(1)
}
void mSDelay(unsigned int itime) {
  unsigned int i;
  unsigned int j;
  for (i = 0; i < itime; i++)
    for (j = 0; j < 4000; j++);
}