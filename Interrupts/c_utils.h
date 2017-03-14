#include <hidef.h>            /* common defines and macros */
#include <mc9s12dp256.h>      /* MicroController derivative information */

//add src to the end of dest string
void strcat(char *dest, const char *src);
void strcat_char(char *dest, const char src);

// A utility function to check whether x is numeric
char isNumericChar(char x);

//convert string to int
int atoi(char *str);

//Reverse a string
void str_reverse(char str[], int length);

//convert int to string
char* itoa(int num, char* str, int base);

