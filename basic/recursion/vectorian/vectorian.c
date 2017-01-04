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



#include "vectorian.h"	/* header file */
#include <stddef.h> /* for size_t  */




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
size_t Vectorian(size_t _index)
{
	if( 1 >= _index )
    {
        return _index;
    }
    
    return Vectorian(_index - 1) * _index;
}
/*----------------------------------------------------------------------------*/

