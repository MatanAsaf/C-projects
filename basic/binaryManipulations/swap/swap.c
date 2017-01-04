/** 
 *  @file 		swap.c
 *  @brief 		src file for swap API
 * 
 *  @details 	The API swap between 2 numbers without using any temporary space to do so.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		2016-12-22     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "swap.h"		/* header file */
#include <stddef.h>		/* for NULL */



/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function Swap between A and B without using any temporary.
 *
 * @warning		This method can only work if the total sum is still in the integer range.
 *
 * Time Complexity: O(1).
 *
 * @param       a		=	The first number
 * @param       b		=	The second number to swap with
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 */
ERRORS MathSwap1(int* _a, int* _b)
{
	if(NULL == _a || NULL == _b)
	{
		return ERROR_NOT_INITIALIZE;
	}
	
	*_a = *_a + *_b;
	*_b = *_a - *_b;
	*_a = *_a - *_b;
	
	return SUCCESS;
}
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function Swap between A and B without using any temporary.
 *
 * @warning		This method can only work if the total sum is still in the integer range.
 *
 * Time Complexity: O(1).
 *
 * @param       a		=	The first number
 * @param       b		=	The second number to swap with
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 */
ERRORS MathSwap2(int* _a, int* _b)
{
	if(NULL == _a || NULL == _b)
	{
		return ERROR_NOT_INITIALIZE;
	}
	
	*_a = *_a - *_b;
	*_b = *_a + *_b;
	*_a = *_b - *_a;
	
	return SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function Swap between A and B without using any temporary.
 *				
 * @warning		This method can only work if both numbers are not zero, otherwise 
 *				return ERROR_NOT_VALID .
 * @warning		This method can only work if the total multiply is still in the integer range.
 *
 * Time Complexity: O(1).
 *
 * @param       a		=	The first number
 * @param       b		=	The second number to swap with
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      ERROR_NOT_VALID 		= If one of the pointers point to value 0
 */
ERRORS MathSwap3(int* _a, int* _b)
{
	if(NULL == _a || NULL == _b)
	{
		return ERROR_NOT_INITIALIZE;
	}
	
	if(0 == *_a || 0 == *_b)
	{
		return ERROR_NOT_VALID;
	}
	
	*_a = *_a * *_b;
	*_b = *_a / *_b;
	*_a = *_a / *_b;
	
	return SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function Swap between A and B without using any temporary.
 *
 * Time Complexity: O(1).
 *
 * @param       a		=	The first number
 * @param       b		=	The second number to swap with
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 */
ERRORS BitSwap(int* _a, int* _b)
{
	if(NULL == _a || NULL == _b)
	{
		return ERROR_NOT_INITIALIZE;
	}
	
	*_a = *_a ^ *_b;
	*_b = *_a ^ *_b;
	*_a = *_a ^ *_b;
	
	return SUCCESS;
}
/*----------------------------------------------------------------------------*/


