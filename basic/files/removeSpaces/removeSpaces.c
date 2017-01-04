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



#include "removeSpaces.h"	/* header file */
#include <stdio.h>			/* for fread & fwrite & fileno */
#include <stddef.h> 		/* for size_t */
#include <unistd.h> 		/* for ftruncate */
#include <sys/types.h> 		/* for ftruncate */
#include <errno.h> 			/* for errno */

#define CH 		(' ')
#define BYTES_TO_READ (100)
#define CHECK_OPEN_FILE_ERROR(ptr)	do { if( NULL == (ptr) ) { return FILE_ERROR;} } while(0)
#define CHECK_FILE_ERROR(ptr)		do { if( 0 != (ptr) ) { perror("Error: "); return FILE_ERROR;} } while(0)

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
ERRORS RemoveSpace(char *_fileName)
{
    FILE* fpR;
    FILE* fpW;
    char block[BYTES_TO_READ];
    size_t currentBytesRead;
    size_t indexR = 0;
    
    if( NULL == _fileName )
    {
        return ERROR_NOT_INITIALIZE;
    }
    
    fpR = fopen( _fileName ,"r");
    CHECK_OPEN_FILE_ERROR(fpR);
	
    fpW = fopen( "resultFile.txt" ,"w");
    CHECK_OPEN_FILE_ERROR(fpW);
	
    while( !(feof(fpR) ) )
    {
        currentBytesRead = fread(&block , sizeof(char), BYTES_TO_READ , fpR ); 
        while( indexR < currentBytesRead )
        {
            
            if( CH != block[indexR] )
            {
                fputc(block[indexR], fpW);
            }
            
            ++indexR;    
        }
        
        indexR = 0;
    }
    
    CHECK_FILE_ERROR(fclose(fpW));
    
    CHECK_FILE_ERROR(fclose(fpR));
    
    return SUCCESS;
}
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
ERRORS RemoveSpaceInSrc(char *_fileName)
{
    FILE* fp;
    char block[BYTES_TO_READ];
    size_t currentBytesRead = 0;
    size_t totalBytesRead = 0;
    size_t totalBytesWrite = 0;
    size_t indexR = 0;
    size_t bytesToWrite = 0;
    
    if( NULL == _fileName )
    {
        return ERROR_NOT_INITIALIZE;
    }
    
    fp = fopen( _fileName ,"r+");
    CHECK_OPEN_FILE_ERROR(fp);
	
    while( !(feof(fp) ) )
    {
        currentBytesRead = fread(&block , sizeof(char), BYTES_TO_READ , fp ); 
        while( indexR++ < currentBytesRead )
        {
            if( CH == block[indexR - 1] )
            {
            	continue;
            }
            
            if( bytesToWrite != (indexR -1) )
            {
            	block[bytesToWrite] = block[indexR -1];
            }
            
            ++bytesToWrite;
        }
        
        totalBytesRead += currentBytesRead;
        
        if( 0 < bytesToWrite )
        {
			CHECK_FILE_ERROR(fseek(fp, (long int)totalBytesWrite , SEEK_SET));
			
			totalBytesWrite += fwrite( &block, sizeof(char), bytesToWrite, fp );
		
			CHECK_FILE_ERROR(fseek(fp, (long int)totalBytesRead , SEEK_SET));
			
			bytesToWrite = 0;
        }
        
        indexR = 0;
    }
    
    CHECK_FILE_ERROR(fclose(fp));
    
	CHECK_FILE_ERROR(truncate(_fileName, (off_t)totalBytesWrite));
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/



