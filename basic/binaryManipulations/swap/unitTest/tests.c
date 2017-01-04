/** 
 *  @file 		tests.c
 *  @brief 		tests file for swap API
 * 
 *  @details 	The API swap between 2 numbers without using any temporary space to do so.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		2016-12-22    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "swap.h"		/* header file */
#include "matan_test.h"	/* def of TEST test */
#include <stdio.h>  	/* for printf */
#include <stddef.h> 	/* for size_t */




/*************************** Tests for API functions **************************/
/*-------------------------------- MathSwap1 ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(MathSwap1_CheckFirstNull)
	int b = 50;
	ERRORS status;
	
	status = MathSwap1(NULL, &b);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap1_CheckSecendNull)
	int a = 50;
	ERRORS status;
	
	status = MathSwap1(&a, NULL);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap1_CheckRegularSwap)
	int a = 50;
	int b = 99;
	ERRORS status;
	
	status = MathSwap1(&a, &b);
	
	ASSERT_THAT( SUCCESS == status && a == 99 && b == 50 );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- MathSwap2 ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(MathSwap2_CheckFirstNull)
	int b = 50;
	ERRORS status;
	
	status = MathSwap2(NULL, &b);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap2_CheckSecendNull)
	int a = 50;
	ERRORS status;
	
	status = MathSwap2(&a, NULL);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap2_CheckRegularSwap)
	int a = 50;
	int b = 99;
	ERRORS status;
	
	status = MathSwap2(&a, &b);
	
	ASSERT_THAT( SUCCESS == status && a == 99 && b == 50 );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- MathSwap3 ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(MathSwap3_CheckFirstNull)
	int b = 50;
	ERRORS status;
	
	status = MathSwap3(NULL, &b);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap3_CheckSecendNull)
	int a = 50;
	ERRORS status;
	
	status = MathSwap3(&a, NULL);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap3_CheckFirstNotValid)
	int a = 0;
	int b = 99;
	ERRORS status;
	
	status = MathSwap3(&a, &b);
	
	ASSERT_THAT( ERROR_NOT_VALID == status && a == 0 && b == 99 );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap3_CheckSecondNotValid)
	int a = 50;
	int b = 0;
	ERRORS status;
	
	status = MathSwap3(&a, &b);
	
	ASSERT_THAT( ERROR_NOT_VALID == status && a == 50 && b == 0 );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(MathSwap3_CheckRegularSwap)
	int a = 50;
	int b = 99;
	ERRORS status;
	
	status = MathSwap3(&a, &b);
	
	ASSERT_THAT( SUCCESS == status && a == 99 && b == 50 );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- BitSwap ----------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BitSwap_CheckFirstNull)
	int b = 50;
	ERRORS status;
	
	status = BitSwap(NULL, &b);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BitSwap_CheckSecendNull)
	int a = 50;
	ERRORS status;
	
	status = BitSwap(&a, NULL);
	
	ASSERT_THAT( ERROR_NOT_INITIALIZE == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BitSwap_CheckRegularSwap)
	int a = 50;
	int b = 99;
	ERRORS status;
	
	status = BitSwap(&a, &b);
	
	ASSERT_THAT( SUCCESS == status && a == 99 && b == 50 );
END_TEST
/*----------------------------------------------------------------------------*/




/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(foundMax)
	PRINT(MathSwap1_CheckFirstNull) 
	PRINT(MathSwap1_CheckSecendNull)
	PRINT(MathSwap1_CheckRegularSwap)
	
	PRINT(MathSwap2_CheckFirstNull) 
	PRINT(MathSwap2_CheckSecendNull)
	PRINT(MathSwap2_CheckRegularSwap)
	
	PRINT(MathSwap3_CheckFirstNull) 
	PRINT(MathSwap3_CheckSecendNull)
	PRINT(MathSwap3_CheckFirstNotValid)
	PRINT(MathSwap3_CheckSecondNotValid)
	PRINT(MathSwap3_CheckRegularSwap)
	
	PRINT(BitSwap_CheckFirstNull) 
	PRINT(BitSwap_CheckSecendNull)
	PRINT(BitSwap_CheckRegularSwap)
END_SET
/*----------------------------------------------------------------------------*/






