/** 
 *  @file 		countOnBits.h
 *  @brief 		header file for countOnBits src file
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
 
#ifndef __COUNT_ON_BITS_H__
#define __COUNT_ON_BITS_H__

#include <stddef.h> 		/* for size_t */

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
size_t CountOnBits(int _num);
/*----------------------------------------------------------------------------*/



#endif /* __COUNT_ON_BITS_H__ */
