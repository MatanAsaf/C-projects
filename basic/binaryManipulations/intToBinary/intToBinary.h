/** 
 *  @file 		intToBinary.h
 *  @brief 		header file for intToBinary function
 * 
 *  @details 	The function convert a number to it's representation in Binary.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 		2016-12-25    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __INT_TO_BINARY_H__
#define __INT_TO_BINARY_H__

#include <stddef.h>	/* for size_t */



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum 
{
    SUCCESS,				/* If the return was as expected */
    ERROR_NOT_INITIALIZE 	/* If one of the pointers point to null */
} ERRORS;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function convert a number to it's representation in Binary.
 *
 * Time Complexity: O(n) n = number of digits in the number.
 *
 *
 * @param       _number		=   The number to convert
 * @param       _string     =   Pointer to a string to hold the result
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 */
ERRORS intToBinary(int _number, char* _string);
/*----------------------------------------------------------------------------*/

#endif /* __INT_TO_BINARY_H__ */
