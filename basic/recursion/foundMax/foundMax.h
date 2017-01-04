/** 
 *  @file foundMax.h
 *  @brief header file for foundMax src file
 * 
 *  @details This function search in a given array of numbers which one is with the maximum value.
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

#ifndef __FOUND_MAX_H__
#define __FOUND_MAX_H__

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
 * @brief       This function c search in a given array of numbers which one is
 * 				with the maximum value and return status.
 *
 * Time Complexity: N.
 *
 * @param       _arr		=	Pointer to the start of the array
 * @param       _size		=	The size of the array
 * @param       _pValue		=	The return value of one of the numbers in the 
 *								array with the max value
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      ERROR_NO_SIZE 			= If size of the array is zero
 */
ERRORS FoundMax(int* _arr, size_t _size, int* _pValue);
/*----------------------------------------------------------------------------*/


#endif /* __FOUND_MAX_H__ */
