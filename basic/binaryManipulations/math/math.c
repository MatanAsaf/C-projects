/** 
 *  @file 		math.c
 *  @brief 		src file for math API
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

#include "math.h"		/* header file */
#include <stddef.h>		/* for size_t */
#include <stdio.h>		/* for printf */

#define INT_BITS 	(32)
#define MAX_INT 	(2147483647)


/***************************** Functions Declaration **************************/






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
int CheckSign(int _num)
{
	_num >>= (INT_BITS -1);
	
	return (_num | 1);
}
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
int ChangeToAbsolute1(int _num)
{
	return (_num * CheckSign(_num) );
}
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
int ChangeToAbsolute2(int _num)
{
	
	int signBit = _num >> (INT_BITS - 1);
	int opposite = ~(_num - 1);
	int result = (-1 * signBit * opposite) - (_num * ~(signBit) );
	
	return result;
}
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
int ChangeToAbsolute3(int _num)
{
	int signBit = _num >> (INT_BITS - 1);
	
	_num ^= signBit;
	_num -= signBit;
	
	return _num;
}
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
unsigned int CheckPowerOfTwo(unsigned int _num)
{
	size_t i = 0;
	size_t nOfOneBit = 0;
	
	while( i < INT_BITS)
	{
		if( 1 == (_num & 1) )
		{
			++nOfOneBit;
			
			if( 2 > nOfOneBit )
			{
				break;
			}
		}
		
		_num >>= 1;
	}
	
	return (1 == nOfOneBit);
}
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
int Sum(int _num1, int _num2)
{
	int r = 0;
	int valueBitNum1;
	int valueBitNum2;
	int result;
	int retValue = 0;
	int condition1;
	int condition2;
	int condition3;
	size_t i = 0;
	
	while( i < INT_BITS )
	{
		valueBitNum1 = _num1 & 1;
		valueBitNum2 = _num2 & 1;
		
		result = valueBitNum1 ^ valueBitNum2 ^ r;
		
		condition1 = ( 1 == valueBitNum1 && 1 == valueBitNum2 );
		condition2 = ( 1 == valueBitNum1 && 1 == r );
		condition3 = ( 1 == r && 1 == valueBitNum2 );
		
		if( 1 == condition1 || 1 == condition2 || 1 == condition3 )
		{
			r = 1;
		}
		else
		{
			r = 0;
		}
		
		result <<= i;
		retValue |= result;
		_num1 >>= 1;
		_num2 >>= 1;
		++i;
	}
	
	return retValue;
}
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
size_t Multiply(size_t _num1, size_t _num2)
{
	size_t retValue = _num1;
	size_t i;
	
	if(0 == _num1 || 0 == _num2 )
	{
	 	return 0;
	}
	
	for( i = 1; i < _num2; ++i)
	{
		retValue = (size_t)Sum((int)retValue, (int)_num1);
	}
	
	return retValue;
}
/*----------------------------------------------------------------------------*/


/*************************** Implication of functions *************************/

