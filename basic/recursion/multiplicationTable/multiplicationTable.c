/** 
 *  @file multiplicationTable.h
 *  @brief header file for multiplicationTable src file
 * 
 *  @details This function print the multiplicationTable to the screen using recursion.
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

#include <stddef.h> /* for size_t  */
#include <stdio.h>	/* for printf  */


/************************** API functions Declaration *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function print the multiplicationTable to the screen using recursion.
 *
 * Time Complexity: N.
 *
 * @param       line	=	The total of lines to print in the multiplicationTable.
 * @param       row		=	The current row to start printing in the multiplicationTable.
 * @param       index	=	The current position to start printing in the multiplicationTable.
 *
 * @return		void
 */
void multiplicationTable(int _line, int _row, int _index);
/*----------------------------------------------------------------------------*/




/************************************ MAIN ************************************/
/*----------------------------------------------------------------------------*/
int main()
{
    multiplicationTable(10, 1 ,1);
    
    return 0;
}
/*----------------------------------------------------------------------------*/





/************************** API functions Implication *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function print the multiplicationTable to the screen using recursion.
 *
 * Time Complexity: N.
 *
 * @param       line	=	The total of lines to print in the multiplicationTable.
 * @param       row		=	The current row to start printing in the multiplicationTable.
 * @param       index	=	The current position to start printing in the multiplicationTable.
 *
 * @return		void
 */
void multiplicationTable(int _line, int _row, int _index)
{
    if( _index > _line )
    {
        if(_row >= _line) 
        {
            printf("\n");
            return;
        }
        
        ++_row;
        _index = 1;
        printf("\n");
    }
    
    printf("%5d", _index * _row );
    
    ++_index;
    multiplicationTable(_line, _row , _index);
    
    return;  
}
/*----------------------------------------------------------------------------*/



