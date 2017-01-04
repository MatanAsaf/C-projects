/** 
 *  @file vectorian.h
 *  @brief header file for vectorian src file
 * 
 *  @details The function return the value of index multiply all the numbers before him
 *			 starting from 1.
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

#ifndef __VECTORIAN_H__
#define __VECTORIAN_H__

#include <stddef.h> 	/* for size_t  */



/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return the value of index multiply all the numbers before him
 *				starting from 1.
 *
 * Time Complexity: N.
 *
 * @param       index		=	The number to calculate
 *
 * @return		The function return the value of index multiply all the numbers before him
 *				starting from 1.
 */
size_t Vectorian(size_t _index);
/*----------------------------------------------------------------------------*/


#endif /* __VECTORIAN_H__ */
