/** 
 *  @file tests.c
 *  @brief tests file for fileDetails
 * 
 *  @details This API present some functions that collect data from a given file.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-20    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "fileDetails.h"/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */
#include <stdlib.h> 	/* for size_t & srand */
#include <time.h> 		/* for time_t */

#define DEBUG (0)			
#define N_SPACES (10)		
#define N_LINES (10)
#define MAX_RAND_VALUE (257) /* The max value the function rand() can produce */
#define FILE_NAME "temp.txt"
#define FILE_NAME2 "temp2.txt"
#define FILE_NAME3 "temp3.txt"



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function print the all values of the result.
 *
 * @param       charCounter		=	Amount of characters
 * @param       wordCounter		=	Amount of words
 * @param       lineCounter		=	Amount of lines
 *
 * @return		void
 */
static void PrintValues(size_t _charCounter, size_t _wordCounter, size_t _lineCounter);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*----------------------------- CountTotalValues -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CountTotalValues_CheckNull)
	size_t nC;
	size_t nW;
	size_t nL;
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == CountTotalValues(NULL, &nC, &nW, &nL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountTotalValues_CheckEmptyFile)
	FILE* fp;
	size_t nC;
	size_t nW;
	size_t nL;
	ERRORS status;
	
	fp = fopen(FILE_NAME ,"w");
    fclose(fp);
    
	status = CountTotalValues(FILE_NAME, &nC, &nW, &nL);
	
	#if DEBUG
		PrintValues(nC, nW, nL);
	#endif
	
	ASSERT_THAT( SUCCESS == status && 0 == nC && 0 == nW && 0 == nL );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountTotalValues_CheckFileWithOnlySpaces)
	FILE* fp;
	size_t nC;
	size_t nW;
	size_t nL;
	ERRORS status;
	size_t i;
	
	fp = fopen(FILE_NAME ,"w");
	
	for(i = 0; i < N_SPACES; ++i)
	{
		fputc(' ', fp);
	}
	
    fclose(fp);
    
	status = CountTotalValues(FILE_NAME, &nC, &nW, &nL);
	
	#if DEBUG
		PrintValues(nC, nW, nL);
	#endif
	
	ASSERT_THAT( SUCCESS == status && N_SPACES == nC && 0 == nW && 0 == nL );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountTotalValues_CheckFileWithOnlyLineBreak)
	FILE* fp;
	size_t nC;
	size_t nW;
	size_t nL;
	ERRORS status;
	size_t i;
	
	fp = fopen(FILE_NAME ,"w");
	
	for(i = 0; i < N_LINES; ++i)
	{
		fputc('\n', fp);
	}
	
    fclose(fp);
    
	status = CountTotalValues(FILE_NAME, &nC, &nW, &nL);
	
	#if DEBUG
		PrintValues(nC, nW, nL);
	#endif
	
	ASSERT_THAT( SUCCESS == status && N_LINES == nC && 0 == nW && N_LINES == nL );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountTotalValues_CheckFileWords)
	FILE* fp;
	size_t nC;
	size_t nW;
	size_t nL;
	ERRORS status;
	size_t i;
	
	fp = fopen(FILE_NAME ,"w");
	
	for(i = 0; i < N_LINES; ++i)
	{
		fputc('g', fp);
		fputc(' ', fp);
		fputc('t', fp);
		fputc('\n', fp);
	}
	
    fclose(fp);
    
	status = CountTotalValues(FILE_NAME, &nC, &nW, &nL);
	
	#if DEBUG
		PrintValues(nC, nW, nL);
	#endif
	
	ASSERT_THAT( SUCCESS == status && (4 * N_LINES) == nC && (2 * N_LINES) == nW && N_LINES == nL );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountTotalValues_CheckFileWords2)
	FILE* fp;
	size_t nC;
	size_t nW;
	size_t nL;
	ERRORS status;
	size_t i;
	
	fp = fopen(FILE_NAME ,"w");
	
	for(i = 0; i < N_LINES; ++i)
	{
		fputc('g', fp);
		fputc(' ', fp);
		fputc('t', fp);
		fputc(' ', fp);
		fputc('\n', fp);
	}
	
    fclose(fp);
    
	status = CountTotalValues(FILE_NAME, &nC, &nW, &nL);
	
	#if DEBUG
		PrintValues(nC, nW, nL);
	#endif
	
	ASSERT_THAT( SUCCESS == status && (5 * N_LINES) == nC && (2 * N_LINES) == nW && N_LINES == nL );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------ PrintLastLines ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(PrintLastLines_CheckNull)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == PrintLastLines(NULL, N_LINES) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrintLastLines_CheckEmpty)
	FILE* fp;
	
	fp = fopen(FILE_NAME2 ,"w");
	fclose(fp);
	
	ASSERT_THAT( SUCCESS == PrintLastLines(FILE_NAME2, N_LINES) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrintLastLines_CheckZeroLines)
	FILE* fp;
	
	fp = fopen(FILE_NAME2 ,"w");
	fclose(fp);
	
	ASSERT_THAT( SUCCESS == PrintLastLines(FILE_NAME2, 0) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrintLastLines_CheckFileWithLessBytesThenReaderBlock)
	FILE* fp;
	size_t i = 1;
	
	fp = fopen(FILE_NAME2 ,"w");
	
	fprintf(fp, "\nLine %u", i);
	
	fclose(fp);
	
	ASSERT_THAT( SUCCESS == PrintLastLines(FILE_NAME2, 1) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrintLastLines_CheckLinesLessThenFile)
	FILE* fp;
	size_t i = 0;
	
	fp = fopen(FILE_NAME2 ,"w");
	
	fprintf(fp, "Line number %u Not to be read\n", i);
	fprintf(fp, "Line number %u Not to be read\n", i);
	fprintf(fp, "Line number %u Not to be read\n", i);
	
	for(i = 1; i < N_LINES; ++i)
	{
		fprintf(fp, "Line number %u needed to be read\n", i);
	}
	
	fprintf(fp, "Line number %u needed to be read", i);
	
	fclose(fp);
	
	ASSERT_THAT( SUCCESS == PrintLastLines(FILE_NAME2, N_LINES) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrintLastLines_CheckLinesMoreThenFile)
	FILE* fp;
	size_t i;
	
	fp = fopen(FILE_NAME2 ,"w");
	for(i = 0; i < (N_LINES - 1); ++i)
	{
		fprintf(fp, "Line number %u needed to be read\n", i);
	}
	
	fclose(fp);
	
	ASSERT_THAT( SUCCESS == PrintLastLines(FILE_NAME2, N_LINES) );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------ PrintLastLines ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CountEachChar_CheckNull_File)
	size_t* ptr;
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == CountEachChar(NULL, &ptr) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountEachChar_CheckNull_Value)
	FILE* fp;
	
	fp = fopen(FILE_NAME3 ,"w");
	fclose(fp);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == CountEachChar(FILE_NAME3, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountEachChar_CheckCase_Empty)
	FILE* fp;
	size_t* ptr;
	size_t i;
	ERRORS status;
	
	fp = fopen(FILE_NAME3 ,"w");
	fclose(fp);
	
	status = CountEachChar(FILE_NAME3, &ptr);
	
	for(i = 0; i < 256; ++i)
	{
		ASSERT_THAT( 0 == ptr[i] );
	}
	
	free(ptr);
	ASSERT_THAT( SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountEachChar_CheckCase_Full)
	FILE* fp;
	size_t* ptr;
	size_t i;
	size_t temp;
	ERRORS status;
	
	fp = fopen(FILE_NAME3 ,"w");
	
	for(i = 0; i < 1000; ++i)
	{
		temp = (size_t)(rand() % MAX_RAND_VALUE);
		fputc((char)temp, fp);
	}
	
	fclose(fp);
	
	status = CountEachChar(FILE_NAME3, &ptr);
	
	#if DEBUG
	for(i = 32; i < 126; ++i)
	{
	    if( ptr[i] > 0 )
	    {
	        printf("Char %c: %u times\n", i , ptr[i] );
	    }
	}
    #endif
    
    free(ptr);
	ASSERT_THAT( SUCCESS ==  status);
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(fileDetails API)
	PRINT(CountTotalValues_CheckNull)
	PRINT(CountTotalValues_CheckEmptyFile)
	PRINT(CountTotalValues_CheckFileWithOnlySpaces)
	PRINT(CountTotalValues_CheckFileWithOnlyLineBreak)
	PRINT(CountTotalValues_CheckFileWords)
	PRINT(CountTotalValues_CheckFileWords2)
	
	PRINT(PrintLastLines_CheckNull)
	PRINT(PrintLastLines_CheckEmpty)
	PRINT(PrintLastLines_CheckZeroLines)
	PRINT(PrintLastLines_CheckFileWithLessBytesThenReaderBlock)
	PRINT(PrintLastLines_CheckLinesLessThenFile)
	PRINT(PrintLastLines_CheckLinesMoreThenFile)
	
	PRINT(CountEachChar_CheckNull_File)
	PRINT(CountEachChar_CheckNull_Value)
	PRINT(CountEachChar_CheckCase_Empty)
	PRINT(CountEachChar_CheckCase_Full)
END_SET
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function print the all values of the result.
 *
 * @param       charCounter		=	Amount of characters
 * @param       wordCounter		=	Amount of words
 * @param       lineCounter		=	Amount of lines
 *
 * @return		void
 */
static void PrintValues(size_t _charCounter, size_t _wordCounter, size_t _lineCounter)
{
	printf("The number of charecter in a file is: %d\n", _charCounter);
    printf("The number of words in a file is: %d\n", _wordCounter);
    printf("The number of lines in a file is: %d\n", _lineCounter);
	
	return;
}
/*----------------------------------------------------------------------------*/
