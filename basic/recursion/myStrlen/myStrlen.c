/** 
 *  @file 		myStrlen.h
 *  @brief 		header file for myStrlen src file
 * 
 *  @details 	This function return the number of characters there are in the 
 *				string  using recursion..
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
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
 * @brief       This function return the number of characters there are in the 
 *				string  using recursion.
 *
 * Time Complexity: N.
 *
 * @param       ptrString	=	Pointer to the string.
 *
 * @return		The number of characters there are in the string
 */
size_t MyStrlenRec(char* _ptrString);
/*----------------------------------------------------------------------------*/




/************************************ MAIN ************************************/
/*----------------------------------------------------------------------------*/
int main()
{
	char str[100];
	
	printf("Please insert any string up to 100 bytes:\n");
	scanf("%s", str);
    printf("The number of characters in your string: %u\n", MyStrlenRec(str) );
    
    return 0;
}
/*----------------------------------------------------------------------------*/





/************************** API functions Implication *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function return the number of characters there are in the 
 *				string  using recursion.
 *
 * Time Complexity: N.
 *
 * @param       ptrString	=	Pointer to the string.
 *
 * @return		The number of characters there are in the string
 */
size_t MyStrlenRec(char* _ptrString)
{
    if( NULL == _ptrString || '\0' == _ptrString[0])
    {
        return 0;    
    }
    
    return (MyStrlenRec(_ptrString + 1) +1);
}
/*----------------------------------------------------------------------------*/



