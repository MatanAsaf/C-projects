/** 
 *  @file calculateSum.h
 *  @brief header file for calculateSum src file
 * 
 *  @details This function sum all numbers of the given array.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 2016-12-21     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __CALCULATE_SUM_H__
#define __CALCULATE_SUM_H__

#include <stddef.h> 	/* for size_t  */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum 
{
    SUCCESS,				/* If the return was as expected */
    ERROR_NOT_INITIALIZE, 	/* If one of the pointers point to null */
    ERROR_NO_SIZE 			/* If size of the array is zero */
} ERRORS;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function sum all numbers of the given array.
 *
 * Time Complexity: N.
 *
 * @param       _arr		=	Pointer to the start of the array
 * @param       _size		=	The size of the array
 * @param       _pValue		=	The return value of the numbers sum value
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      ERROR_NO_SIZE 			= If size of the array is zero
 */
ERRORS CalculateSum(int* _arr, size_t _size, int* _pValue);
/*----------------------------------------------------------------------------*/


#endif /* __CALCULATE_SUM_H__ */
