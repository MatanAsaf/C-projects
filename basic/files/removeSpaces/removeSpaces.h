/** 
 *  @file removeSpaces.h
 *  @brief header file for removeSpaces src file
 * 
 *  @details This function that create new file with the same content but without space between words.
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

#ifndef __REMOVE_SPACES_H__
#define __REMOVE_SPACES_H__

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
 * @brief       Function that create new file with the same content but without space between words.
 *
 * Time Complexity: N.
 *
 * @param       fileName				=	Pointer to the name path of the file to open
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      FILE_ERROR 				= If there was an error when handling with the file
 */
ERRORS RemoveSpace(char *_fileName);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Function that remove from the file content all spacees between words.
 *
 * Time Complexity: N.
 *
 * @param       fileName				=	Pointer to the name path of the file to open
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      FILE_ERROR 				= If there was an error when handling with the file
 */
ERRORS RemoveSpaceInSrc(char *_fileName);
/*----------------------------------------------------------------------------*/


#endif /* __REMOVE_SPACES_H__ */
