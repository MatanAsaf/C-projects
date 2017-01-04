/** 
 *  @file tests.c
 *  @brief tests file for calculateSum
 * 
 *  @details This function sum all numbers of the given array.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-21    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "calculateSum.h"	/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */




/*************************** Tests for API functions **************************/
/*-------------------------------- CalculateSum ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CalculateSum_CheckNULL_Array)
	int retVal;
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == CalculateSum(NULL, 5, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateSum_CheckNULL_Size)
	int arr[] = {5,5,6,5,5};
	int retVal;
	
	ASSERT_THAT( ERROR_NO_SIZE == CalculateSum(arr, 0, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateSum_CheckNULL_Value)
	int arr[] = {5,5,6,5,5};
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == CalculateSum(arr, 5, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateSum_CheckCase_Posotive)
	int arr[] = {6,5,5,5,5};
	int retVal;
	ERRORS status;
	
	status = CalculateSum(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && 26 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateSum_CheckCase_Negetive)
	int arr[] = {-1, -2, -2, -2, -2};
	int retVal;
	ERRORS status;
	
	status = CalculateSum(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && -9 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CalculateSum_CheckCase_Mix)
	int arr[] = {5, -5, -5, 5, 5};
	int retVal;
	ERRORS status;
	
	status = CalculateSum(arr, 5, &retVal);
	
	ASSERT_THAT( SUCCESS == status && 5 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/

/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(CalculateSum)
	PRINT(CalculateSum_CheckNULL_Array)
	PRINT(CalculateSum_CheckNULL_Size)
	PRINT(CalculateSum_CheckNULL_Value)
	PRINT(CalculateSum_CheckCase_Posotive)
	PRINT(CalculateSum_CheckCase_Negetive)
	PRINT(CalculateSum_CheckCase_Mix)
END_SET
/*----------------------------------------------------------------------------*/






