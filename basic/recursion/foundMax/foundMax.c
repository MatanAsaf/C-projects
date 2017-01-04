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



#include "foundMax.h"		/* header file */
#include <stddef.h> 	/* for size_t  */



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function c search in a given array of numbers which one is
 * 				with the maximum value.
 *
 * Time Complexity: N.
 *
 * @param       _arr		=	Pointer to the start of the array
 * @param       _size		=	The size of the array
 *
 * @return		The value of one of the numbers in the array with the max value
 */
static int FoundMaxValue(int* _arr, size_t _size);
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
ERRORS FoundMax(int* _arr, size_t _size, int* _pValue)
{
	if( NULL ==  _arr || NULL ==  _pValue )
    {
    	return ERROR_NOT_INITIALIZE;
    }
    
    if( 0 ==  _size )
    {
    	return ERROR_NO_SIZE;
    }
    
    *_pValue = FoundMaxValue(_arr, _size);
    
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function c search in a given array of numbers which one is
 * 				with the maximum value.
 *
 * Time Complexity: N.
 *
 * @param       _arr		=	Pointer to the start of the array
 * @param       _size		=	The size of the array
 *
 * @return		The value of one of the numbers in the array with the max value
 */
static int FoundMaxValue(int* _arr, size_t _size)
{
    int tempMax;
    
    if(1 == _size )
    {
        return _arr[0];
    }
    
    tempMax = FoundMaxValue( _arr, _size-1);
    
    if(_arr[_size-1] > tempMax)
    {
        return _arr[_size-1];
    }
    
    return tempMax;
}
/*----------------------------------------------------------------------------*/



