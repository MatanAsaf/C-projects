/** 
 *  @file myString.h
 *  @brief heade file for myString API
 * 
 *  @details This API present my implication of different function from string.h.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-14    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <stddef.h>	/* for size_t */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum Result {
	SUCCESS,
	UNINITIALIZED_ERROR,			/* Uninitialized error on param pointer */
	UNINITIALIZED_RETURN,			/* Uninitialized error on return value pointer */
	NOT_FOUND,						/* There are no numbers in that string */
	NOT_EQUAL,						/* Both string NOT equal */
	FIRST_PARAM_LONGER,				/* The first string have more characters then the second string	*/
	SECOND_PARAM_LONGER				/* The second string have more characters then the first string	*/
} STATUS;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function get a string and convert it to integer.
 * @details     The function work under this condetion:
 *				1. 	Any character that separate 2 digits will end the loop, and 
 *					the return number will be only the first digits in a row.
 *				2.	Spaces are ignored
 *				3.	After the signes: +/- the function look for digits, if there 
 *					is none, the return value will be 0.
 *
 * Time Complexity: N.
 *
 *
 * @param       _string        		=   The string to convert
 * @param       _retNumber        	=   Pointer to store the integer result
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS					=	The function successes converting
 * @retval		UNINITIALIZED_ERROR		=	Uninitialized error on string pointer
 * @retval		UNINITIALIZED_RETURN	=	Uninitialized error on retNumber pointer
 * @retval		NOT_FOUND				=	There are no numbers in that string
 */
STATUS myAToI(const char* _string, int* _retNumber);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function get a number and convert it to a string.
 * @details     The function get a number and convert it to a string.			
 *
 * Time Complexity: N.
 *
 *
 * @param       _number        		=   The number to convert
 * @param       _retString        	=   Pointer to store the string result
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS					=	The function successes converting
 * @retval		UNINITIALIZED_RETURN	=	Uninitialized error on retString pointer
 */
STATUS myIToA(int _number, char* _retString);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function search for the first occurrence of the character c
 *				in the first n bytes of the string.		
 *
 * Time Complexity: O(n).
 *
 * @param       _str        		=   The string to search in it
 * @param       _c        			=   The value character to place in each of the characters 
 * @param       _n        			=   Max index of characters to search
 * @param       _index        		=   Pointer to store the index result
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS					=	The function succeeded
 * @retval		UNINITIALIZED_ERROR		=	Uninitialized error on str pointer
 * @retval		UNINITIALIZED_RETURN	=	Uninitialized error on index pointer
 * @retval		NOT_FOUND				=	The character has not found
 */
STATUS myMemChar(const char* _str, char _c, size_t _n, size_t* _index);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Compares the first n bytes of str1 and str 2.		
 *
 * Time Complexity: O(n).
 *
 * @param       _str1        		=   The first string
 * @param       _str2        		=   The second string to compare to
 * @param       _n        			=   Max index of characters to search
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS				=	The function succeeded and both string equal up to n characters
 * @retval		UNINITIALIZED_ERROR	=	Uninitialized error on one of the pointer
 * @retval		NOT_EQUAL			=	Both string NOT equal
 * @retval		FIRST_PARAM_LONGER	=	The first string have more characters then the second string
 * @retval		SECOND_PARAM_LONGER	=	The second string have more characters then the first string
 */
STATUS myMemCmp(const char* _str1, const char* _str2, size_t _n);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Copies n characters from src to des.		
 *
 * Time Complexity: O(n).
 *
 * @param       _des        		=   The destination string to place the 2 strings
 * @param       _src        		=   The src string to copy to des string
 * @param       _n        			=   Numbers of characters to append
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS				=	The function succeeded
 * @retval		UNINITIALIZED_ERROR	=	Uninitialized error on one of the pointer
 */
STATUS myMemCpy(char* _des, const char* _src, size_t _n);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Set each character in the str string with the value c, up to n characters long.		
 *
 * Time Complexity: O(n).
 *
 * @param       _str        		=   The string to place the characters
 * @param       _c        			=   The value character to place in each of the characters 
 * @param       _n        			=   Numbers of characters to set
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS				=	The function succeeded
 * @retval		UNINITIALIZED_ERROR	=	Uninitialized error on _src pointer
 */
STATUS myMemSet(char* _str, char _c, size_t _n);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Appends the string src to the string des, up to n characters long.		
 *
 * Time Complexity: O(n).
 *
 * @param       _des        		=   The destination string to place the 2 strings
 * @param       _src        		=   The src string to copy to des string
 * @param       _n        			=   Numbers of characters to append
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS				=	The function succeeded
 * @retval		UNINITIALIZED_ERROR	=	Uninitialized error on one of the pointers
 */
STATUS myStrNCat(char* _des, const char* _src, size_t _n);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Calculate how many characters in the string.		
 * @details     The function calculate how many characters in the string.			
 *
 * Time Complexity: O(n).
 *
 *
 * @param       _src        		=   The src string  
 * @param       _n        			=   Pointer to store the result
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS					=	The function succeeded
 * @retval		UNINITIALIZED_ERROR		=	Uninitialized error on _src pointer
 * @retval		UNINITIALIZED_RETURN	=	Uninitialized error on _n pointer
 */
STATUS myStrLen(const char* _src, size_t* _n);
/*----------------------------------------------------------------------------*/


#endif /* __MY_STRING_H__ */
