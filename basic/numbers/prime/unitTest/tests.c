/** 
 *  @file tests.c
 *  @brief tests file for prime API
 * 
 *  @details This API present different approaches to find out if the given number
 *			 is a prime number or not.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "prime.h"		/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */






/*************************** Tests for API functions **************************/
/*---------------------------- PrimeTrialDivision ----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(PrimeTrialDivision_CheckLimit)
	ASSERT_THAT( NOT_A_PRIME == PrimeTrialDivision(1) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrimeTrialDivision_CheckConstant2)
	ASSERT_THAT( PRIME == PrimeTrialDivision(2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrimeTrialDivision_CheckConstant17)
	ASSERT_THAT( PRIME == PrimeTrialDivision(17) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrimeTrialDivision_CheckConstant49)
	ASSERT_THAT( NOT_A_PRIME == PrimeTrialDivision(49) );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Prime API)
	PRINT(PrimeTrialDivision_CheckLimit)
	PRINT(PrimeTrialDivision_CheckConstant2)
	PRINT(PrimeTrialDivision_CheckConstant17)
	PRINT(PrimeTrialDivision_CheckConstant49)
END_SET
/*----------------------------------------------------------------------------*/


