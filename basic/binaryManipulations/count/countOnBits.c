/** 
 *  @file 		countOnBits.c
 *  @brief 		src file for countOnBits API
 * 
 *  @details 	The API countOnBits count the number of ones in a binary representation.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 2016-12-26     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "countOnBits.h"	/* header file */
#include <stddef.h>			/* for NULL */

#define INT_BITS 	(32)

/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       Count the number of ones in a binary representation.
 *
 * Time Complexity: O(n).
 *
 * @param       num		=	The number to test
 *
 * @return		The number of ones
 */
size_t CountOnBits(int _num)
{
	size_t counter = 0;
	size_t i;
	
	for(i = 0; i < INT_BITS; ++i)
	{
		if( 1 == (_num & 1) )
		{
			++counter;
		}
		
		_num >>= 1;
	}

	return counter;
}
/*----------------------------------------------------------------------------*/


