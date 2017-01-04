/** 
 *  @file reverseString.c
 *  @brief src file for reverseString
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
#include <string.h>			/* for strlen */



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function swap between 2 numbers of type char.
 *
 * @param       _ptr1		=	Pointer to the first number
 * @param       _ptr2   	=	Pointer to the second number
 *
 * @return		void
 */
static void swapValues(char* ptr1, char* ptr2);
/*----------------------------------------------------------------------------*/



/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function get a string and rewrite it in backwords.
 *
 * Time Complexity: N.
 *
 *
 * @param       _array		=	Pointer to the array of numbers
 * @param       _arrSize   	=	The number of elements in the array
 *
 * @return		void
 */
void Reverse(char* _string)
{
	unsigned int i = 0;
	unsigned int arrSize = strlen(_string);
	unsigned int j = arrSize -1; 
	
	while ( i < (arrSize/2) )
	{
		swapValues( &_string[i], &_string[j] );
		++i;
		--j;	
	}
	
	return;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function swap between 2 numbers of type char.
 *
 * @param       _ptr1		=	Pointer to the first number
 * @param       _ptr2   	=	Pointer to the second number
 *
 * @return		void
 */
static void swapValues(char* ptr1, char* ptr2)
{
	char temp = *ptr1;
	
	*ptr1 = *ptr2;
	*ptr2 = temp;
	
	return;
}

/*----------------------------------------------------------------------------*/
