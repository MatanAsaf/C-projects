/** 
 *  @file 		swap.h
 *  @brief 		header file for swap src file
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
 
#ifndef __BIT_SWAP_H__
#define __BIT_SWAP_H__


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum 
{
    SUCCESS,				/* If the return was as expected */
    ERROR_NOT_INITIALIZE, 	/* If one of the pointers point to null */
    ERROR_NOT_VALID 		/* If one of the pointers point to value 0 */
} ERRORS;
/*----------------------------------------------------------------------------*/





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
ERRORS MathSwap1(int* _a, int* _b);
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
ERRORS MathSwap2(int* _a, int* _b);
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
ERRORS MathSwap3(int* _a, int* _b);
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
ERRORS BitSwap(int* _a, int* _b);
/*----------------------------------------------------------------------------*/



#endif /* __BIT_SWAP_H__ */
