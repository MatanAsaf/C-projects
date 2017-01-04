/** 
 *  @file fileDetails.c
 *  @brief src file for fileDetails
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

#include "fileDetails.h"	/* header file */
#include <stdio.h>			/* for printf & perror */
#include <stddef.h> 		/* for size_t  */
#include <stdlib.h> 		/* for calloc  */

#define BYTES_TO_READ (100)
#define FOUND_MIN(value1, value2) ( value1 > value2 ? value2 : value1  )



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function print each characters in the file from specific index.
 *
 * @param       fileName		=	Pointer to the name path of the file to open
 * @param       index			=	The index in the file, from where to start printing
 * @param       mode			=	In which mode the index is given:
 *									0 : From the start
 *									2 : From the end
 *
 * @return		void
 */
static void PrintFile(const char* _fileName, int _index, int _mode);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function read each character in the given block searching for 
 *				param c for number of times, every time it found it, the function update counter.
 *
 * @param       buffer			=	Pointer to the buffer to read from
 * @param       blockSize		=	The size of the buffer
 * @param       c				=	Which character to search
 * @param       counter			=	How many times to search for it
 *
 * @return		Amount of bytes has been read
 */
static size_t ReadBlock(const char* _buffer, size_t _blockSize, char _c, size_t* _counter);
/*----------------------------------------------------------------------------*/




/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function count words, new lines, and characters from a given file.
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
ERRORS CountTotalValues(const char* _fileName, size_t* _nChar, size_t* _nWord, size_t* _nLine)
{
	FILE* fp;
    char current;
    char lastChar = ' ';
    size_t charCounter = 0;
    size_t wordCounter = 0;
    size_t lineCounter = 0; 
    
    if(NULL ==  _fileName)
    {
    	return ERROR_NOT_INITIALIZE;
    }
    
	fp = fopen(_fileName ,"r");
	if(NULL == fp)
	{
		return FILE_ERROR;
	}
    
	current = (char)fgetc(fp);
    while( !(feof(fp) ) )
    {
    	++charCounter;
        
        switch(current)
        {
        	case '\n':
        		++lineCounter;
        	case ' ':
        		if( lastChar != ' ' && lastChar != '\n' )
		    	{
		    		++wordCounter;
		            lastChar = ' ';
		    	}
        		break;
        	default:
        		lastChar = current;
        }
        
        current = (char)fgetc(fp);       
    }
    
    if( 0 != fclose(fp) )
    {
    	return FILE_ERROR;
    }
    
    *_nChar = charCounter;
    *_nWord = wordCounter; 
    *_nLine = lineCounter;
    
    return SUCCESS;
}
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
ERRORS PrintLastLines(char *_fileName, size_t _numOfLines)
{
    FILE *fp;
    char buffer[BYTES_TO_READ];
    size_t printIndex = 0;
    size_t currentBytesRead;
    long int readIndex;
    long int pos = 0;
    
    if( NULL == _fileName )
    {
        return ERROR_NOT_INITIALIZE;
    }
    
    fp = fopen(_fileName ,"r");
	if(NULL == fp)
	{
		return FILE_ERROR;
	}
	
	/* Start from the end of the file */
	if( 0 != fseek(fp, 0 , SEEK_END) )
	{
		return FILE_ERROR;
	}
	
    pos = ftell(fp);
    readIndex = FOUND_MIN(pos, BYTES_TO_READ);
    if( 0 != fseek(fp, -1 * readIndex , SEEK_END) )
    {
		return FILE_ERROR;
	}
	
    while( 0 != pos && 0 != _numOfLines)
    {
    	pos = ftell(fp);
    	currentBytesRead = fread(&buffer, 1, (size_t)readIndex, fp);
    	
    	printIndex += ReadBlock(buffer, currentBytesRead, '\n', &_numOfLines);
		
		readIndex = FOUND_MIN(pos, BYTES_TO_READ);
    	fseek(fp, -1 * ( (long int)currentBytesRead + readIndex) , SEEK_CUR);
    }

	if( 0 != fclose(fp) )
    {
    	return FILE_ERROR;
    }
	
	PrintFile(_fileName, -1 * (int)(printIndex), SEEK_END);
    
    return SUCCESS;
}
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
ERRORS CountEachChar(char *_fileName, size_t** _pValue)
{
	FILE *fp;
	size_t* ptr;
	int lastChar;
    
    if( NULL == _fileName || NULL == _pValue )
    {
        return ERROR_NOT_INITIALIZE;
    }
    
    fp = fopen(_fileName ,"r");
	if(NULL == fp)
	{
		return FILE_ERROR;
	}
	
	ptr = (size_t*)calloc(256, sizeof(size_t) );
	if( NULL == ptr )
    {
        return ALLOCATION_ERROR;
    }
    
    lastChar = fgetc(fp);
     while( !(feof(fp) ) )
    {
        ++( ptr[ lastChar ]);  
        lastChar = fgetc(fp);
    }
    
    if( 0 != fclose(fp) )
    {
    	return FILE_ERROR;
    }
    
    *_pValue = (size_t*)ptr;
    
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function print each characters in the file from specific index.
 *
 * @param       fileName		=	Pointer to the name path of the file to open
 * @param       index			=	The index in the file, from where to start printing
 * @param       mode			=	In which mode the index is given:
 *									0 : From the start
 *									2 : From the end
 *
 * @return		void
 */
static void PrintFile(const char* _fileName, int _index, int _mode)
{
	FILE *fp;
    char current;
    
	fp = fopen(_fileName ,"r");
    
    fseek(fp, _index , _mode);

    current = (char)fgetc(fp);
    while( !(feof(fp) ) )
    {
    	printf("%c", current);
    	current = (char)fgetc(fp);
    }
    
    printf("\n");
    
    fclose(fp);
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function read each character in the given block searching for 
 *				param c for number of times, every time it found it, the function update counter.
 *
 * @param       buffer			=	Pointer to the buffer to read from
 * @param       blockSize		=	The size of the buffer
 * @param       c				=	Which character to search
 * @param       counter			=	How many times to search for it
 *
 * @return		Amount of bytes has been read
 */
static size_t ReadBlock(const char* _buffer, size_t _blockSize, char _c, size_t* _counter)
{
	size_t i;
	
	if(0 == _blockSize || 0 == *_counter)
	{
		return 0;
	}
	
	for( i = _blockSize; i > 0; --i )
	{
		if( _c != _buffer[i - 1] )
    	{
    		continue;
    	}
    	
    	--(*_counter);
    		
    	if( 0 == *_counter )
		{
			break;
		}
	}
	
	return (_blockSize - i);
}
/*----------------------------------------------------------------------------*/
