/** 
 *  @file tests.c
 *  @brief tests file for removeSpaces
 * 
 *  @details This function that create new file with the same content but without space between words.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-21    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "removeSpaces.h"	/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stdlib.h> 		/* for size_t & srand */

#define MAX_RAND_VALUE (257) /* The max value the function rand() can produce */
#define FILE_NAME "temp.txt"
#define FILE_NAME2 "temp2.txt"



/*************************** Tests for API functions **************************/
/*-------------------------------- RemoveSpace -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(RemoveSpace_CheckNull)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == RemoveSpace(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveSpace_CheckEmptyFile)
	FILE* fp;
	
	fp = fopen( FILE_NAME ,"w");
	fclose(fp);
	
	ASSERT_THAT( SUCCESS == RemoveSpace(FILE_NAME) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveSpace_CheckCase_Rand)
	FILE* fp;
	size_t i;
	size_t temp;
	ERRORS status;
	
	fp = fopen(FILE_NAME ,"w");
	
	for(i = 0; i < 1000; ++i)
	{
		temp = (size_t)(rand() % MAX_RAND_VALUE);
		fputc((char)temp, fp);
	}
	
	fclose(fp);
	
	status = RemoveSpace(FILE_NAME);
    
	ASSERT_THAT( SUCCESS ==  status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveSpace_CheckCase_Full)
	FILE* fp;
	size_t i;
	ERRORS status;
	
	fp = fopen(FILE_NAME ,"w");
	
	for(i = 0; i < 100; ++i)
	{
		fprintf(fp, "mb vc xsdf gmmer ewtutvd fhmhgdj gmh j gf jgdj agmmmm bfhd gjhg fd");
	}
	
	fclose(fp);
	
	status = RemoveSpace(FILE_NAME);
    
	ASSERT_THAT( SUCCESS ==  status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------- RemoveSpaceInSrc -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(RemoveSpaceInSrc_CheckNull)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == RemoveSpaceInSrc(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveSpaceInSrc_CheckEmptyFile)
	FILE* fp;
	
	fp = fopen( FILE_NAME2 ,"w");
	fclose(fp);
	
	ASSERT_THAT( SUCCESS == RemoveSpaceInSrc(FILE_NAME2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveSpaceInSrc_CheckCase_Rand)
	FILE* fp;
	size_t i;
	size_t temp;
	ERRORS status;
	
	fp = fopen(FILE_NAME2 ,"w");
	
	for(i = 0; i < 1000; ++i)
	{
		temp = (size_t)(rand() % MAX_RAND_VALUE);
		fputc((char)temp, fp);
	}
	
	fclose(fp);
	
	status = RemoveSpaceInSrc(FILE_NAME2);
    
	ASSERT_THAT( SUCCESS ==  status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveSpaceInSrc_CheckCase_Full)
	FILE* fp;
	size_t i;
	ERRORS status;
	
	fp = fopen("before.txt" ,"w");
	
	for(i = 0; i < 100; ++i)
	{
		fprintf(fp, "mb vc xsdf gmmer ewtutvd fhmhgdj gmh j gf jgdj agmmmm bfhd gjhg hkgfjfj");
	}
	
	fprintf(fp, "END_OF_FILE");
	
	fclose(fp);
	
	fp = fopen("after.txt" ,"w");
	
	for(i = 0; i < 100; ++i)
	{
		fprintf(fp, "mb vc xsdf gmmer ewtutvd fhmhgdj gmh j gf jgdj agmmmm bfhd gjhg hkgfjfj");
	}
	
	fprintf(fp, "END_OF_FILE");
	
	fclose(fp);
	
	status = RemoveSpaceInSrc("after.txt");
    
	ASSERT_THAT( SUCCESS ==  status);
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(removeSpaces)
	PRINT(RemoveSpace_CheckNull)
	PRINT(RemoveSpace_CheckEmptyFile)
	PRINT(RemoveSpace_CheckCase_Rand)
	PRINT(RemoveSpace_CheckCase_Full)
	
	PRINT(RemoveSpaceInSrc_CheckNull)
	PRINT(RemoveSpaceInSrc_CheckEmptyFile)
	PRINT(RemoveSpaceInSrc_CheckCase_Rand)
	PRINT(RemoveSpaceInSrc_CheckCase_Full)
END_SET
/*----------------------------------------------------------------------------*/






