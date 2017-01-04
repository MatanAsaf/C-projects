/** 
 *  @file triangle.h
 *  @brief header file for triangle src file
 * 
 *  @details This functions print triangle to the screen using recursion.
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
 * @brief       This function print regular triangle to the screen using recursion.
 *
 * Time Complexity: N.
 *
 * @param       col		=	The number of coll the triangle will have.
 * @param       line	=	The number of lines the triangle will have.
 * @param       index	=	In which Index to start.
 *
 * @return		void
 */
void Triangle(int _col, int _line, int _index);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function print reverse triangle to the screen using recursion.
 *
 * Time Complexity: N.
 *
 * @param       col		=	The number of coll the triangle will have.
 * @param       line	=	The number of lines the triangle will have.
 * @param       index	=	In which Index to start.
 *
 * @return		void
 */
void ReverseTriangle(int _col, int _line, int _index);
/*----------------------------------------------------------------------------*/





/************************************ MAIN ************************************/
/*----------------------------------------------------------------------------*/
int main()
{
    Triangle(5, 1 ,1);
    ReverseTriangle(5, 1 ,1);
    
    return 0;
}
/*----------------------------------------------------------------------------*/





/************************** API functions Implication *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function print regular triangle to the screen using recursion.
 *
 * Time Complexity: N.
 *
 * @param       col		=	The number of coll the triangle will have.
 * @param       line	=	The number of lines the triangle will have.
 * @param       index	=	In which Index to start.
 *
 * @return		void
 */
void Triangle(int _col, int _line, int _index)
{
    if( _index > _col )
    {
        if(_line >= _col) 
        {
            printf("\n\n\n");
            return;
        }
        
        printf("\n");
        ++_line;
        _index = _line;
    }
    
    printf("*");
    
    ++_index;
    Triangle(_col, _line , _index);
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function print reverse triangle to the screen using recursion.
 *
 * Time Complexity: N.
 *
 * @param       col		=	The number of coll the triangle will have.
 * @param       line	=	The number of lines the triangle will have.
 * @param       index	=	In which Index to start.
 *
 * @return		void
 */
void ReverseTriangle(int _col, int _line, int _index)
{
    if( _index <= 0 )
    {
        if(_line >= _col) 
        {
            printf("\n\n\n");
            return;
        }
        
        printf("\n");
        ++_line;
        _index = _line;
    }
    
    printf("*");
    
    --_index;
    ReverseTriangle(_col, _line , _index);
    
    return;
}
/*----------------------------------------------------------------------------*/
