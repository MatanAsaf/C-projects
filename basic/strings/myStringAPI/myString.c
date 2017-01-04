/** 
 *  @file myString.c
 *  @brief src file for myString API
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

#include "myString.h"	/* header file */
#include <stddef.h>		/* for size_t */


#define YES	(1)
#define NO	(0)
#define CHECK_UNINITIALIZED(param)	do { if( NULL == (param) ) { return UNINITIALIZED_ERROR;} } while(0)
#define CHECK_UNINITIALIZED_RETURN(param)	do { if( NULL == (param) ) { return UNINITIALIZED_RETURN;} } while(0)
#define CHECK_NOT_FOUND(param)	do { if( '\0' == (param) ) { return NOT_FOUND;} } while(0)


/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
static int IsDigit(const char _sign);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void SwapChar(char* _string, size_t _index1, size_t _index2);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static size_t CheckNegetive(int* _number, char* _retString, size_t _index);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static size_t WriteStringInReverse(int _number, char* _retString, size_t _index);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void ReverseString(char* _retString, size_t _index);
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function get a string and convert it to integer.
 * @details     The function work under this condetion:
 *				1. 	Any charecter that seperate 2 digits will end the loop, and 
 *					the return number will be only the first digits in a row.
 *				2.	Spaces are ignored
 *				3.	After the signes: +/- the function look for digits, if there 
 *					is none, the return value will be 0.
 *					
 *
 * Time Complexity: N.
 *
 *
 * @param       _string        		=   The string to convert
 * @param       _retNumber        	=   Pointer to store the integer result
 *
 * @return		The status after the function has done it's action 
 *
 * @retval		SUCCESS					=	The function successed converting
 * @retval		UNINITIALIZED_ERROR		=	Uninitialized error on string pointer
 * @retval		UNINITIALIZED_RETURN	=	Uninitialized error on retNumber pointer
 * @retval		NOT_FOUND				=	There are no numbers in that string
 */
STATUS myAToI(const char* _string, int* _retNumber)
{
	int num = 0;
	int valueFlag = 1;
	
	CHECK_UNINITIALIZED(_string);
	CHECK_UNINITIALIZED_RETURN(_retNumber);
	
	/* found the start of the number in the string */
	while( NO == IsDigit(_string[0]) && '\0' != _string[0] &&  '+' != _string[0] && '-' != _string[0] )
	{
		++_string;	
	}
	
	CHECK_NOT_FOUND(_string[0]);
	
	if( '-' == _string[0] )
	{
		valueFlag = -1;
	}
	else
	{
		if( '+' != _string[0] )
		{
			num += (_string[0] - 48);
		}
	}
	
	++_string;
	
	while( '\0' != _string[0] )
	{
		if(' ' == _string[0] )
		{
			++_string;
			continue;
		}
		
		if( NO == IsDigit(_string[0]) )
		{
			break;
		}
		
		num *= 10;
		num += (_string[0] - 48);
		++_string;
	}
	
	*_retNumber = (valueFlag * num);
	
	return SUCCESS;
}
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
 * @retval		SUCCESS					=	The function succeeded converting
 * @retval		UNINITIALIZED_RETURN	=	Uninitialized error on retString pointer
 */
STATUS myIToA(int _number, char* _retString)
{
	size_t charIndex = 0;
	
	CHECK_UNINITIALIZED_RETURN(_retString);
	
	charIndex = CheckNegetive(&_number, _retString, charIndex);
	
	charIndex = WriteStringInReverse(_number, _retString, charIndex);
	
	ReverseString(_retString, charIndex);
	
	return SUCCESS;
}
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
STATUS myMemChar(const char* _str, char _c, size_t _n, size_t* _index)
{
	size_t counter = 0;
	
	CHECK_UNINITIALIZED(_str);
	CHECK_UNINITIALIZED_RETURN(_index);
	
	while( '\0' != _str[0] && counter <= _n )
	{
		if( _str[0] == _c )
		{
			*_index = counter;
			return SUCCESS;
		}
		
		++_str;
		++counter;
	}
	
	return NOT_FOUND;
}
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
STATUS myMemCmp(const char* _str1, const char* _str2, size_t _n)
{
	size_t counter = 0;
	
	CHECK_UNINITIALIZED(_str1);
	CHECK_UNINITIALIZED(_str2);
	
	while( '\0' != _str1[0] && '\0' != _str2[0] && counter <= _n)
	{
		if( _str1[0] != _str2[0] )
		{
			return NOT_EQUAL;
		}
		
		++_str1;
		++_str2;
		++counter;
	}
	
	if( '\0' != _str1[0] && '\0' == _str2[0] )
	{
		return FIRST_PARAM_LONGER;
	}
	
	if( '\0' != _str2[0] && '\0' == _str1[0])
	{
		return SECOND_PARAM_LONGER;
	}
	
	return SUCCESS;
}
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
STATUS myMemCpy(char* _des, const char* _src, size_t _n)
{
	size_t counter = 0;
	
	CHECK_UNINITIALIZED(_des);
	CHECK_UNINITIALIZED(_src);
	
	while( '\0' != _src[0] && _n >= counter)
	{
		_des[0] = _src[0];
		++_des;
		++_src;
		++counter;
	}
	
	_des[0] = '\0';
	
	return SUCCESS;
}
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
STATUS myMemSet(char* _str, char _c, size_t _n)
{
	size_t counter = 0;
	
	CHECK_UNINITIALIZED(_str);
	
	while( _n > counter)
	{
		_str[0] = _c;
		++_str;
		++counter;
	}
	
	_str[0] = '\0';
	
	return SUCCESS;
}
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
STATUS myStrNCat(char* _des, const char* _src, size_t _n)
{
	size_t counter = 0;
	
	CHECK_UNINITIALIZED(_des);
	CHECK_UNINITIALIZED(_src);
	
	while( '\0' != _des[0] )
	{
		++_des;
	}
	
	while( '\0' != _src[0] && _n > counter)
	{
		_des[0] = _src[0];
		++_des;
		++_src;
		++counter;
	}
	
	_des[0] = '\0';
	
	return SUCCESS;
}
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
STATUS myStrLen(const char* _src, size_t* _n)
{
	size_t counter = 0;
	
	CHECK_UNINITIALIZED(_src);
	CHECK_UNINITIALIZED_RETURN(_n);
	
	while( '\0' != _src[0] )
	{
		++_src;
		++counter;
	}
	
	*_n =  counter;
	
	return SUCCESS;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
static int IsDigit(const char _sign)
{
	if(47 < (int)_sign && 58 > (int)_sign)
	{
		return YES;
	}
	
	return NO;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void SwapChar(char* _string, size_t _index1, size_t _index2)
{
	char temp = _string[_index1];
	_string[_index1] = _string[_index2];
	_string[_index2] = temp;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static size_t CheckNegetive(int* _number, char* _retString, size_t _index)
{
	if(0 > *_number)
	{
		_retString[0] = '-';
		*_number *= -1;
		++_index;
	}
	
	return _index;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static size_t WriteStringInReverse(int _number, char* _retString, size_t _index)
{
	size_t tempDigit;
	
	while(10 < _number)
	{
		tempDigit = (size_t)( _number % 10);
		_retString[_index] = (char)(tempDigit + 48);
		_number /= 10;
		++_index;
	}
	
	_retString[_index] = (char)(_number + 48);
	++_index;
	
	_retString[_index] = '\0';
	
	return _index;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void ReverseString(char* _retString, size_t _index)
{
	size_t i = 0;
	
	if( '-' == _retString[0] )
	{
		++i;
	}
	
	while( i < (_index -1) )
	{
		SwapChar( _retString, i, _index - 1 );
		++i;
		--_index;
		
	}
	
	return;
}
/*----------------------------------------------------------------------------*/
