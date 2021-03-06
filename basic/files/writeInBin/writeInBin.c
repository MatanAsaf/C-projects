/** 
 *  @file writeInBin.c
 *  @brief src file for writeInBin
 * 
 *  @details This API allowed the user to read and write to a file in binary.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-18     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "writeInBin.h"	/* header file */
#include <stddef.h> 	/* for size_t  */
#include <stdio.h> 		/* for fread / fwrite  */




/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function read from a given file that is writting in binary and return the status and data.
 *
 * Time Complexity: N.
 *
 * @param       filePath				=	Pointer to the name path of the file to open
 * @param       pValue   				=	Pointer to store the data
 * @param       elementSize   			=	The size of 1 element
 * @param       nLine   				=	The total of elements
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      OPEN_ERROR 				= If there was an error when opening the file
 */
ERRORS ReadFromFile(const char* _filePath, void** _pValue, size_t _elementSize, size_t _nElement)
{
	FILE* fp;
    
    if(NULL ==  _filePath || NULL ==  _pValue || NULL ==  *_pValue)
    {
    	return ERROR_NOT_INITIALIZE;
    }
    
	fp = fopen(_filePath ,"rb");
	if(NULL == fp)
	{
		return OPEN_ERROR;
	}
    
	fread(_pValue, _elementSize, _nElement, fp);
    
    fclose(fp);
    
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function write from a given file that is writting in binary and return the status and data.
 *
 * Time Complexity: N.
 *
 * @param       filePath				=	Pointer to the name path of the file to open
 * @param       value   				=	Pointer to read the data
 * @param       elementSize   			=	The size of 1 element
 * @param       nLine   				=	The total of elements
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		SUCCESS					= If the return was as expected
 * @retval      ERROR_NOT_INITIALIZE 	= If one of the pointers point to null
 * @retval      OPEN_ERROR 				= If there was an error when opening the file
 */
ERRORS WriteToFile(const char* _filePath, const void* _value, size_t _elementSize, size_t _nElement)
{
	FILE* fp;
    
    if(NULL ==  _filePath || NULL ==  _value )
    {
    	return ERROR_NOT_INITIALIZE;
    }
    
	fp = fopen(_filePath ,"wb");
	if(NULL == fp)
	{
		return OPEN_ERROR;
	}
    
	fwrite(_value, _nElement, _elementSize, fp);
    
    fclose(fp);
    
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/
