/** 
 *  @file prime.c
 *  @brief src file for prime API
 * 
 *  @details This API present different approaches to find out if the given number
 *			 is a prime number or not.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "prime.h"	/* header file */
#include <stddef.h>	/* for size_t */
#include <math.h>	/* for sqrt- Needed to add -lm when compile */





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function found if the number is prime torught Trial division.
 * @details     The function check all numbers from 2 to square root of the number,
 				to see if there is at least 1 number that return remainder of 0, if
 				the function found it- then the orignal number is not a prime.
 *
 * Time Complexity: N^(0.5).
 *
 *
 * @param       _number        		=   The number to check
 *
 * @return		The status for the given number
 *
 * @retval		PRIME (0)			= 	When the number is a prime
 * @retval		NOT_A_PRIME (-1)	= 	When the number is a not a prime, there is
 *										at least 1 number that return remainder of 0.
 */
int PrimeTrialDivision(size_t _number)
{
	size_t i = 2;
	size_t root = (size_t)sqrt( (float)_number );
	
	if(2 > _number)
	{
		return(NOT_A_PRIME);
	}
	
	while(i <= root) 
	{
		if( 0 == ( _number % i++ ) ) 
		{
			return NOT_A_PRIME;
		}
	}
	
	return PRIME;
}
/*----------------------------------------------------------------------------*/


