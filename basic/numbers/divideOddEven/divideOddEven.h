/** 
 *  @file divideOddEven.h
 *  @brief header file for divideOddEven src file
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

#ifndef DIVIDE_ODD_EVEN_H_
#define DIVIDE_ODD_EVEN_H_

#include <stddef.h>	/* for size_t */




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
void Divide(int* _array, size_t _arrSize);
/*----------------------------------------------------------------------------*/

#endif /* DIVIDE_ODD_EVEN_H_ */
