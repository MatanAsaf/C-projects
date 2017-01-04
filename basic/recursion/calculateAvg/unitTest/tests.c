/** 
 *  @file tests.c
 *  @brief tests file for calculateAvg
 * 
 *  @details This function sum all numbers of the given array and calculate their average.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-21    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "calculateAvg.h"	/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */




/*************************** Tests for API functions **************************/
/*-------------------------------- CalculateAvg -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CalculateAvg_CheckNULL_Array)
	float retVal;
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == CalculateAvg(NULL, 5, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateAvg_CheckNULL_Size)
	int arr[] = {5,5,6,5,5};
	float retVal;
	
	ASSERT_THAT( ERROR_NO_SIZE == CalculateAvg(arr, 0, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateAvg_CheckNULL_Value)
	int arr[] = {5,5,6,5,5};
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == CalculateAvg(arr, 5, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateAvg_CheckCase_AllTheSame)
	int arr[] = {5, 5, 5, 5, 5};
	float retVal;
	ERRORS status;
	
	status = CalculateAvg(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && 5 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateAvg_CheckCase_Sorted)
	int arr[] = {1, 2, 3, 4, 5};
	float retVal;
	ERRORS status;
	
	status = CalculateAvg(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && 3 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/




/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(CalculateAvg)
	PRINT(CalculateAvg_CheckNULL_Array)
	PRINT(CalculateAvg_CheckNULL_Size)
	PRINT(CalculateAvg_CheckNULL_Value)
	PRINT(CalculateAvg_CheckCase_AllTheSame)
	PRINT(CalculateAvg_CheckCase_Sorted)
END_SET
/*----------------------------------------------------------------------------*/






