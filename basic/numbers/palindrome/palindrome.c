/** 
 *  @file palindrome.c
 *  @brief src file for palindrome API
 * 
 *  @details This API present different approaches to find out if the given number
 *			 is a palindrome number or not.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "palindrome.h"	/* header file */
#include <stddef.h>	/* for size_t */
#include <math.h>	/* for sqrt- Needed to add -lm when compile */





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function found if the number is palindrome torught Trial division.
 * @details     The function check all numbers from 2 to square root of the number,
 				to see if there is at least 1 number that return remainder of 0, if
 				the function found it- then the orignal number is not a palindrome.
 *
 * Time Complexity: N(1.5N).
 *
 *
 * @param       _number        			=   The number to check
 *
 * @return		The status for the given number
 *
 * @retval		PALINDROME (0)			= 	When the number is a palindrome
 * @retval		NOT_A_PALINDROME (-1)	= 	When the number is a not a palindrome, there is
 *											at least 1 number that return remainder of 0.
 */
int PalindromeTrialDivision(size_t _number)
{
	unsigned int r[10];		/* The max digits that size_t type can holds */
  	unsigned int i = 0;
  	unsigned int counter = 0;
  
  	while ( _number > 0 ) 
	{
		++counter;
		r[i] = _number % 10;
		_number /= 10;
		++i;
	}
	for(i = 0; i < (counter/2); ++i)
	{
		if( r[i] != r[counter - i -1 ] )
		{
			return(NOT_A_PALINDROME);
		}
	}
	
	return PALINDROME;
}
/*----------------------------------------------------------------------------*/


