/** 
 *  @file 		math.h
 *  @brief 		header file for math src file
 * 
 *  @details 	The math API do a different math calculations using bit manipulations
 * 
 *  @warning 	This bit manipulations work only on 32 bit system
 *
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		2016-12-25     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#ifndef __BIT_MATH_H__
#define __BIT_MATH_H__

#include <stddef.h>		/* for size_t */


/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function compute the sign of integer value without branching.
 *
 * Time Complexity: O(1).
 *
 * @param       num		=	The number to test
 *
 * @return		Value that indicate in which state the value number is:
 *
 * @retval 		1		= If the number is positive
 * @retval      -1 		= If the number is negative
 */
int CheckSign(int _num);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function compute the integer absolute value without branching.
 *
 * Time Complexity: O(1).
 *
 * @param       num		=	The number to test
 *
 * @return		The new value that represent the original number in absolute value.
 */
int ChangeToAbsolute1(int _num);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function compute the integer absolute value without branching.
 *
 * Time Complexity: O(1).
 *
 * @param       num		=	The number to test
 *
 * @return		The new value that represent the original number in absolute value.
 */
int ChangeToAbsolute2(int _num);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function compute the integer absolute value without branching.
 *
 * Time Complexity: O(1).
 *
 * @param       num		=	The number to test
 *
 * @return		The new value that represent the original number in absolute value.
 */
int ChangeToAbsolute3(int _num);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function check if a given integer value is power of two.
 *
 * Time Complexity: O(n). n == Number of bits in integer.
 *
 * @param       num		=	The number to test
 *
 * @return		Value that indicate in which state the value number is:
 *
 * @retval 		1		= If the number value is power of two.
 * @retval      0 		= If the number value is NOT power of two.
 */
unsigned int CheckPowerOfTwo(unsigned int _num);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function add two numbers using bitwise operations only
 *
 * @warning		This method can only work if the total sum is still in the integer range.
 *
 * Time Complexity: O(n). n == Number of bits in integer.
 *
 * @param       num1	=	The first number
 * @param       num1	=	The second number to add to the first one
 *
 * @return		The total sum value.
 */
int Sum(int _num1, int _num2);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function multiply two numbers using bitwise operations only
 *
 * @warning		This method can only work if the result is still in the size_t range.
 *
 * Time Complexity: O(N).
 *
 * @param       num1	=	The first number
 * @param       num1	=	The second number to multiply with the first one
 *
 * @return		The total multiply result value.
 */
size_t Multiply(size_t _num1, size_t _num2);
/*----------------------------------------------------------------------------*/


#endif /* __BIT_MATH_H__ */
