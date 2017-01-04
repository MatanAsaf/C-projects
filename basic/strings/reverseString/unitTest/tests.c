/** 
 *  @file tests.c
 *  @brief tests file for reverseString
 * 
 *  @details This function print any string in reverse.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "reverseString.h"	/* header file */
#include <stdio.h>  		/* for printf */






/*----------------------------------------------------------------------------*/
int main() 
{
	char string[30];
	
	printf("Please insert a string: \n");	
	
	scanf("%s",string);
	printf("Before: %s \n",string);
	Reverse(string);
	printf("After: %s \n",string);
	
	return 0;
}
/*----------------------------------------------------------------------------*/

