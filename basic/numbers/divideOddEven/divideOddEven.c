/** 
 *  @file divideOddEven.c
 *  @brief src file for divideOddEven
 * 
 *  @details This function divide numbers to odd group and even group.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "divideOddEven.h"	/* header file */
#include <stddef.h>		/* for size_t */



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function swap between 2 numbers of type int.
 *
 * @param       _ptr1		=	Pointer to the first number
 * @param       _ptr2   	=	Pointer to the second number
 *
 * @return		void
 */
static void swapNumbers(int* _ptr1, int* _ptr2);
/*----------------------------------------------------------------------------*/



/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function divide all the numbers in the array to 2 groups.
 * @details     The function divide all the numbers in the array to 2 groups: 
 *				Odd numbers and Even numbers. So 1 group will be on the right 
 *				side of the array, and the secend group on the left.
 *
 * Time Complexity: N.
 *
 *
 * @param       _array		=	Pointer to the array of numbers
 * @param       _arrSize   	=	The number of elements in the array
 *
 * @return		void
 */
void Divide(int* _array, size_t _arrSize)
{
	unsigned int i = 0;
	unsigned int j = _arrSize -1;
	
	if(NULL == _array)
	{
		return;
	}
	
	while( i < j )
	{ 
		while( (_array[i] % 2 == 1) )
		{
			++i;
		}
		
		while((_array[j] % 2 == 0) )
		{
			--j;
		}
		
		if( i < j )
		{
			swapNumbers(&_array[i], &_array[j]);
		}
	}
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function swap between 2 numbers of type int.
 *
 * @param       _ptr1		=	Pointer to the first number
 * @param       _ptr2   	=	Pointer to the second number
 *
 * @return		void
 */
static void swapNumbers(int* _ptr1, int* _ptr2) 
{
	int temp = *_ptr1;
	*_ptr1 = *_ptr2;
	*_ptr2 = temp;
	
}
/*----------------------------------------------------------------------------*/
