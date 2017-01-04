/** 
 *  @file fileDetails.h
 *  @brief header file for fileDetails src file
 * 
 *  @details This API present some functions that collect data from a given file.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 2016-12-20     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __FILE_DETAILS_H__
#define __FILE_DETAILS_H__

#include <stddef.h> 	/* for size_t  */





/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum 
{
    SUCCESS,				/* If the return was as expected */
    ERROR_NOT_INITIALIZE, 	/* If one of the pointers point to null */
    FILE_ERROR,				/* If there was an error when handling with the file */
    ALLOCATION_ERROR		/* Allocation failed due to heap error */
} ERRORS;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function count words, lines, and characters from a given file.
 *
 * Time Complexity: N.
 *
 * @param       fileName				=	Pointer to the name path of the file to open
 * @param       nChar   				=	The return value for number of characters in the file
 * @param       nWord   				=	The return value for number of words in the file
 * @param       nLine   				=	The return value for number of new lines in the file
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      FILE_ERROR 				= If there was an error when handling with the file
 */
ERRORS CountTotalValues(const char* _fileName, size_t* _nChar, size_t* _nWord, size_t* _nLine);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Function that print the last lines of a given file, depend on the parameter _numOfLines.
 *
 * Time Complexity: O(n) n == number of lines to print.
 *
 * @param       fileName 				= The address of an array with the path of the file
 * @param       numOfLines 				= The number of lines to print from this file, 
 *										if the number is bigger then the number of lines there 
 *										is in the file, print all file
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      FILE_ERROR 				= If there was an error when handling with the file
 */
ERRORS PrintLastLines(char *_fileName, size_t _numOfLines);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Function that return how many occurrences there is for each different 
 *				char in the file, only print if occurrences is bigger the zero.
 *
 * Time Complexity: O(n) n == number of characters in the file.
 *
 * @param       fileName 				= The address of an array with the path of the file
 * @param       pValue 					= Pointer to return data array that present each 
 *										char from 0 to 256 according to ASCII table
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      FILE_ERROR 				= If there was an error when handling with the file
 * @retval      ALLOCATION_ERROR		= Allocation failed due to heap error
 */
ERRORS CountEachChar(char *_fileName, size_t** _pValue);
/*----------------------------------------------------------------------------*/





#endif /* __FILE_DETAILS_H__ */
