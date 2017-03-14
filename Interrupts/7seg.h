#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */



void seven_seg_init(void);

//c should be from 0-17 and block_index from 0-3
void show_on_seven_seg(unsigned char c, unsigned char block_index);
