/** 
 *  @file tests.c
 *  @brief tests file for writeInBin
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
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */
#include <stddef.h> 	/* for size_t  */
#include <string.h> 	/* for memcmp  */

#define DEBUG (1)
#define FILE_NAME "temp.txt"
#define AMOUNT_OF_ELEMENTS (10)



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct Person
{
    char name[30];
    int id;
    size_t age;
} Person;
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*-------------------------------- WriteToFile -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(WriteToFile_CheckNull_PathName)
	size_t arr[AMOUNT_OF_ELEMENTS];
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == WriteToFile(NULL, (void*)arr , sizeof( size_t), AMOUNT_OF_ELEMENTS ) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(WriteToFile_CheckNull_Value)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == WriteToFile(FILE_NAME, NULL , sizeof( size_t), AMOUNT_OF_ELEMENTS ) );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- ReadFromFile ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ReadFromFile_CheckNull_PathName)
	size_t arr[AMOUNT_OF_ELEMENTS];
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == ReadFromFile(NULL, (void**)&arr , sizeof( size_t), AMOUNT_OF_ELEMENTS ) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ReadFromFile_CheckNull_Value)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == ReadFromFile(FILE_NAME, NULL , sizeof( size_t), AMOUNT_OF_ELEMENTS ) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ReadFromFile_CheckCase_Size_t)
	size_t arr[AMOUNT_OF_ELEMENTS];
	size_t retVal[AMOUNT_OF_ELEMENTS];
    ERRORS status[2];
    int result;
    size_t i;
    
    for(i = 0; i < AMOUNT_OF_ELEMENTS; ++i)
    {
    	arr[i] = i;
    }
    
    status[0] = WriteToFile(FILE_NAME, (void*)arr ,sizeof(int) , AMOUNT_OF_ELEMENTS  );
    status[1] = ReadFromFile(FILE_NAME, (void**)&retVal ,sizeof(int) , AMOUNT_OF_ELEMENTS );
    result = memcmp(arr, retVal, sizeof(retVal) );
    
	ASSERT_THAT( SUCCESS == status[0] && SUCCESS == status[1] && 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ReadFromFile_CheckCase_Struct)
	Person arr[5] = { {"avraham",1, 99} ,{"itzhak", 3, 37}, {"jakob",5, 74}, {"yosef", 11, 17}, {"david", 4512, 70} };
	Person retVal[5];
    ERRORS status[2];
    int result;
    
    status[0] = WriteToFile(FILE_NAME, (void*)arr ,5 , sizeof(Person) );
    status[1] = ReadFromFile(FILE_NAME, (void**)&retVal ,5 , sizeof(Person) );
    result = memcmp(arr, retVal, sizeof(retVal) );
    
	ASSERT_THAT( SUCCESS == status[0] && SUCCESS == status[1] && 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(writeInBin)
	PRINT(WriteToFile_CheckNull_PathName)
	PRINT(WriteToFile_CheckNull_Value)
	
	PRINT(ReadFromFile_CheckNull_PathName)
	PRINT(ReadFromFile_CheckNull_Value)
	PRINT(ReadFromFile_CheckCase_Size_t)
	PRINT(ReadFromFile_CheckCase_Struct)
END_SET
/*----------------------------------------------------------------------------*/

