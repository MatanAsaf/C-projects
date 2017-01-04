/** 
 *  @file power.h
 *  @brief header file for power src file
 * 
 *  @details The function return the value of n raised to the power of k.
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

#ifndef __POWER_H__
#define __POWER_H__

#include <stddef.h> 	/* for size_t  */



/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return the value of n raised to the power of k.
 *
 * Time Complexity: N.
 *
 * @param       n		=	The number to calculate
 * @param       k		=	The value of the power
 *
 * @return		The function return the value of n raised to the power of k.
 */
size_t Power(size_t _n, size_t _k);
/*----------------------------------------------------------------------------*/


#endif /* __POWER_H__ */
