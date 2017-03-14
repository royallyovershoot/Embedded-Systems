#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */


void mSDelay(unsigned int itime);
void keypad_init(void);
char keypad_read_scancode(void);
char getchar(void);
