/** 
 *  @file 		flipBits.h
 *  @brief 		header file for flipBits src file
 * 
 *  @details 	The API do a bit manipulation such a flip or shift bits.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 2016-12-26     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#ifndef __FLIP_BITS_H__
#define __FLIP_BITS_H__

#include <stddef.h>		/* for size_t */



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum 
{
    SUCCESS,				/* If the return was as expected */
    ERROR_NOT_INITIALIZE, 	/* If one of the pointers point to null */
    ERROR_OUT_OF_RANGE,		/* If one of the indexes values is not between 0-31 */
    ERROR_ILLEGAL_RANGE,		/* If indexEnd value is smaller then indexBegin value */
    ERROR_THE_SAME_BIT		/* If 2 indexes values have the same value */
} ERRORS;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       Flips all bits in a given number, from given start bit to given end bit.
 *
 * Time Complexity: O(n).
 *
 * @param       num			=	The number to test, and the return value
 * @param       indexBegin	=	The index where to start flip. 
 * @param       indexEnd	=	The index where to end flip, this index will still flip. 
 *								index range: 0-31 (31 the most significant bit)
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If the pointer point to null
 * @retval      ERROR_OUT_OF_RANGE 		= If one of the indexes values is not between 0-31
 * @retval      ERROR_ILLEGAL_RANGE 	= If indexEnd value is smaller then indexBegin value
 */
ERRORS RangeFlipBits(int* _num, size_t _indexBegin, size_t _indexEnd);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Flips a single bit.
 *
 * Time Complexity: O(1).
 *
 * @param       num			=	The number to test, and the return value
 * @param       index		=	The index where to flip. 
 *								index range: 0-31 (31 the most significant bit)
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If the pointer point to null
 * @retval      ERROR_OUT_OF_RANGE 		= If the index values is not between 0-31
 */
ERRORS FlipSingleBits(int* _num, size_t _index);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Flips a two bits.
 *
 * Time Complexity: O(1).
 *
 * @param       num			=	The number to test, and the return value
 * @param       index1		=	The index where to flip. 
 *								index range: 0-31 (31 the most significant bit)
 * @param       index2		=	The index where to flip. 
 *								index range: 0-31 (31 the most significant bit)
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If the pointer point to null
 * @retval      ERROR_OUT_OF_RANGE 		= If the index values is not between 0-31
 * @retval      ERROR_THE_SAME_BIT 		= If index1 value is the same as index2 value,
 *										  it's mean the result will be the number will 
 *										  stay the same, because the 2 index contradict each outer.
 */
ERRORS FlipTwoBits(int* _num, size_t _index1, size_t _index2);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Shift a given number to the right/left n times in a circular way.
 *
 * Time Complexity: O(1).
 *
 * @param       num			=	The number to shift
 * @param       direction	=	In which direction to shift: 
 *								right: < 0
 *								left:  >= 0
 * @param       n			=	How many times to shift
 *
 * @return		The new value of the number
 */
int ShiftNum(int _num, size_t _direction, size_t _n);
/*----------------------------------------------------------------------------*/


#endif /* __FLIP_BITS_H__ */
