/** 
 *  @file calculateAvg.h
 *  @brief header file for calculateAvg src file
 * 
 *  @details This function sum all numbers of the given array and calculate their average.
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

#ifndef __CALCULATE_AVG_H__
#define __CALCULATE_AVG_H__

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
 * @brief       This function sum all numbers of the given array and calculate their average.
 *
 * Time Complexity: N.
 *
 * @param       _arr		=	Pointer to the start of the array
 * @param       _size		=	The size of the array
 * @param       _pValue		=	The return value with the average of all the numbers in the array
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      ERROR_NO_SIZE 			= If size of the array is zero
 */
ERRORS CalculateAvg(int* _arr, size_t _size, float* _pValue);
/*----------------------------------------------------------------------------*/


#endif /* __CALCULATE_AVG_H__ */
