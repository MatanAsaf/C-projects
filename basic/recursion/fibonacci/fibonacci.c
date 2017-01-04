/** 
 *  @file fibonacci.h
 *  @brief header file for fibonacci src file
 * 
 *  @details This function caculate fibonacci problam with and without recurssion.
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



#include "fibonacci.h"		/* header file */
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
size_t Fibonacci(size_t _index)
{
    size_t x0 = 0;
    size_t x1 = 1;
    size_t temp;
    size_t i;
    
    if( 1 >= _index)
    {
        return _index;
    }
    
    for(i = 2; i <= _index; ++i)
    {
        temp = x0+ x1;
        x0 = x1;
        x1 = temp;
    }
    
    return x1; 
}
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
size_t FibonacciRec(size_t _index)
{
    if(_index == 0)
    {
        return 0;
    }
    
    if(_index == 1)
    {
        return 1;
    }
    
    return FibonacciRec(_index-1) + FibonacciRec(_index-2);  
}
/*----------------------------------------------------------------------------*/



