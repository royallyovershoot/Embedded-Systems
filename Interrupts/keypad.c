#include "keypad.h"

// States (0 or 1) of the keys.
static char scan1[16];
static char scan2[16];


//busy delay of 1ms based on the default clock ///////////////////
void mSDelay(unsigned int itime)
{
   unsigned int i; unsigned int j;
   for(i=0;i<itime;i++)
   {    
      for(j=0;j<4000;j++) 
      {
        ;
      }
   }
}       
//////////////////////////////////////////////////////////////////


void keypad_init(void)
{
	/*** Configure matrix keypad input. ***/
	// PA0-3 are the column lines, and they are used as outputs.
	// PA4-7 are the row lines, and they are used as inputs.
	DDRA = 0x0F;   // Set columns for output, rows for input.
}

static void scan(char *scanbuf)
{
   char col = 0;
   char row = 0;
	/* Scan columns by sequentially raising each one. */
	for (col = 0; col < 4; col++)
	{
		PORTA = 1 << col;   /* Select column. */
		mSDelay(1);

		/* Scan all keys in the row. */
		for (row = 0; row < 4; row++)
		{
			char key = row * 4 + col;
			if (PORTA & ((1 << row) << 4))
				scanbuf[key] = 1;
			else
				scanbuf[key] = 0;
		}
	}
}


char keypad_read_scancode(void)
{
  char i = 0;
  
	// Debounce key presses by scanning the keys twice.
	scan(scan1);
	mSDelay(20);
	scan(scan2);
	
	for (i = 0; i < 16; i++)
	{
		if (scan1[i] && scan2[i])
			return i;
	}
	return -1;
}



char getchar(void)
{
  volatile char c = 0;
	for(;;) //scan forever
	{
		c = keypad_read_scancode();		
		
		//show the scanned result on 7-segment display
		if (!(c < 0)) 
		{
		  mSDelay(200);
		  return c;
		}		
	}	
}

//input_from_switches = PTH; //for DIP and De-bounce Switches:
#define DIPSW8 0x80
#define DIPSW7 0x40
#define DIPSW6 0x20
#define DIPSW5 0x10
#define DIPSW4 0x8
#define DIPSW3 0x4
#define DIPSW2 0x2
#define DIPSW1 0x1

