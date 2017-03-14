#include "c_utils.h"


void strcat(char *dest, const char *src)
{

    while (*dest!= '\0')
        *dest++ ;
    do
    {
        *dest++ = *src++;
    }
    while (*src != '\0') ;
}

void strcat_char(char *dest, const char src)
{

    while (*dest!= '\0')
        *dest++ ;
    
    *dest++ = src;        
    *dest++ = '\0';        
}



// A utility function to check whether x is numeric
char isNumericChar(char x)
{
    return (x >= '0' && x <= '9')? 1: -1;
}


  
//convert string to int
int atoi(char *str)
{ 
    int res = 0;  // Initialize result
    int sign = 1;  // Initialize sign as positive
    int i = 0;  // Initialize index of first digit
  
    // If number is negative, then update sign
    if (str[0] == '-')
    {
        sign = -1;
        i++;  // Also update index of first digit
    }
  
    // Iterate through all digits of input string and update result
    for (; str[i] != '\0'; ++i)
    {
        if (isNumericChar(str[i]) < 0)
            return 0; // You may add some lines to write error message
                      
        res = res*10 + str[i] - '0';
    }
  
    // Return result with sign
    return sign*res;
}


//Reverse a string
void str_reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        //swap(*(str+start), *(str+end));        
        (*(str+start) ^= *(str+end)), (*(str+end) ^= *(str+start)), (*(str+start) ^= *(str+end));         
                
        start++;
        end--;
    }
}

//convert int to string
char* itoa(int num, char* str, int base)
{
    int i = 0;
    char isNegative = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    str_reverse(str, i);
 
    return str;
}
