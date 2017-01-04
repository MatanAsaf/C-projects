/** 
 *  @file palindrome.h
 *  @brief heade file for palindrome API
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

#ifndef PALINDROME_H_
#define PALINDROME_H_

#include <stddef.h>	/* for size_t */

#define PALINDROME 		(0)
#define NOT_A_PALINDROME (-1)



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
int PalindromeTrialDivision(size_t _number);
/*----------------------------------------------------------------------------*/

#endif /* PALINDROME_H_ */
