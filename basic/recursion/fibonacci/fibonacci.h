/** 
 *  @file fibonacci.h
 *  @brief header file for fibonacci src file
 * 
 *  @details This function calculate fibonacci problem with and without recursion.
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

#ifndef __FIBONACCI_H__
#define __FIBONACCI_H__

#include <stddef.h> 	/* for size_t  */



/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function calculate Fibonacci problem without recursion.
 *
 * Time Complexity: N.
 *
 * @param       index		=	the given number to calculate
 *
 * @return		The result for that index
 */
size_t Fibonacci(size_t _index);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function calculate Fibonacci problem with recursion.
 *
 * Time Complexity: N.
 *
 * @param       index		=	the given number to calculate
 *
 * @return		The result for that index
 */
size_t FibonacciRec(size_t _index);
/*----------------------------------------------------------------------------*/


#endif /* __FIBONACCI_H__ */
