/** 
 *  @file tests.c
 *  @brief tests file for palindrome API
 * 
 *  @details This API present different approaches to find out if the given number
 *			 is a palindrome number or not.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "palindrome.h"	/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */






/*************************** Tests for API functions **************************/
/*------------------------- PalindromeTrialDivision --------------------------*/
/*----------------------------------------------------------------------------*/
TEST(PalindromeTrialDivision_CheckLimit)
	ASSERT_THAT( PALINDROME == PalindromeTrialDivision(9) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PalindromeTrialDivision_CheckConstant2234322)
	ASSERT_THAT( PALINDROME == PalindromeTrialDivision(2234322) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PalindromeTrialDivision_CheckConstant1234554321)
	ASSERT_THAT( PALINDROME == PalindromeTrialDivision(1234554321) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PalindromeTrialDivision_CheckNotOnFirstDigit)
	ASSERT_THAT( NOT_A_PALINDROME == PalindromeTrialDivision(123454320) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PalindromeTrialDivision_CheckNotOnSecendDigit)
	ASSERT_THAT( NOT_A_PALINDROME == PalindromeTrialDivision(123454301) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PalindromeTrialDivision_CheckNotOnThirdDigit)
	ASSERT_THAT( NOT_A_PALINDROME == PalindromeTrialDivision(123454021) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PalindromeTrialDivision_CheckNotOnFourthDigit)
	ASSERT_THAT( NOT_A_PALINDROME == PalindromeTrialDivision(123450321) );
END_TEST
/*----------------------------------------------------------------------------*/


/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Palindrome API)
	PRINT(PalindromeTrialDivision_CheckLimit)
	PRINT(PalindromeTrialDivision_CheckConstant2234322)
	PRINT(PalindromeTrialDivision_CheckConstant1234554321)
	PRINT(PalindromeTrialDivision_CheckNotOnFirstDigit)
	PRINT(PalindromeTrialDivision_CheckNotOnSecendDigit)
	PRINT(PalindromeTrialDivision_CheckNotOnThirdDigit)
	PRINT(PalindromeTrialDivision_CheckNotOnFourthDigit)
END_SET
/*----------------------------------------------------------------------------*/


