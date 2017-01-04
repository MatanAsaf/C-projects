/** 
 *  @file tests.c
 *  @brief tests file for foundMax
 * 
 *  @details This function search in a given array of numbers which one is with the maximum value.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-21    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "foundMax.h"		/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */




/*************************** Tests for API functions **************************/
/*---------------------------------- FoundMax --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(FoundMax_CheckNULL_Array)
	int retVal;
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == FoundMax(NULL, 5, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FoundMax_CheckNULL_Size)
	int arr[] = {5,5,6,5,5};
	int retVal;
	
	ASSERT_THAT( ERROR_NO_SIZE == FoundMax(arr, 0, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FoundMax_CheckNULL_Value)
	int arr[] = {5,5,6,5,5};
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == FoundMax(arr, 5, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FoundMax_CheckCase_Begin)
	int arr[] = {6,5,5,5,5};
	int retVal;
	ERRORS status;
	
	status = FoundMax(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && 6 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FoundMax_CheckCase_Middle)
	int arr[] = {4,4,5,4,4};
	int retVal;
	ERRORS status;
	
	status = FoundMax(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && 5 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FoundMax_CheckCase_End)
	int arr[] = {8,8,8,8,9};
	int retVal;
	ERRORS status;
	
	status = FoundMax(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && 9 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/

/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(foundMax)
	PRINT(FoundMax_CheckNULL_Array)
	PRINT(FoundMax_CheckNULL_Size)
	PRINT(FoundMax_CheckNULL_Value)
	PRINT(FoundMax_CheckCase_Begin)
	PRINT(FoundMax_CheckCase_Middle)
	PRINT(FoundMax_CheckCase_End)
END_SET
/*----------------------------------------------------------------------------*/






