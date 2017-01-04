/** 
 *  @file tests.c
 *  @brief tests file for flipBits
 * 
 *  @details 	The API do a bit manipulation such a flip or shift bits.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 2016-12-26    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "flipBits.h"		/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */

#define INT_BITS 	(32)


/*************************** Tests for API functions **************************/
/*------------------------------- RangeFlipBits ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckNULL)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == RangeFlipBits(NULL, 5, 8) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckOutOfRange1)
	int value = 5;
	int* ptr = &value;
	
	ASSERT_THAT( ERROR_OUT_OF_RANGE == RangeFlipBits(ptr, 32, 8) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckOutOfRange2)
	int value = 5;
	int* ptr = &value;
	
	ASSERT_THAT( ERROR_OUT_OF_RANGE == RangeFlipBits(ptr, 3, 32) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckIllegalRange)
	int value = 5;
	int* ptr = &value;
	
	ASSERT_THAT( ERROR_ILLEGAL_RANGE == RangeFlipBits(ptr, 12, 11) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckCase_1Bit)
	int value = 1;
	int* ptr = &value;
	
	ASSERT_THAT( SUCCESS == RangeFlipBits(ptr, 0, 0) && 0 == value );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckCase_1Bit_MostSignificant)
	int value = 1;
	int* ptr = &value;
	
	value <<= (INT_BITS - 1);
	ASSERT_THAT( SUCCESS == RangeFlipBits(ptr, (INT_BITS - 1), (INT_BITS - 1)) && 0 == value );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckCase_All1Bit)
	int value = 1;
	int beforeValue;
	int* ptr = &value;
	size_t i;
	
	for(i = 0; i < INT_BITS; ++i)
	{
		beforeValue = value;
		ASSERT_THAT( SUCCESS == RangeFlipBits(ptr, i, i) && 0 == value );
		value = beforeValue;
		value *= 2;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RangeFlipBits_CheckCase_AllBits)
	int value = 1;
	int beforeValue;
	int step = 1;
	int* ptr = &value;
	size_t i;
	
	for(i = 0; i < INT_BITS; ++i)
	{
		beforeValue = value;
		step *= 2;
		ASSERT_THAT( SUCCESS == RangeFlipBits(ptr, 0, i) && 0 == value );
		value = beforeValue;
		value += step;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- FlipSingleBits -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(FlipSingleBits_CheckNULL)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == FlipSingleBits(NULL, 5) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FlipSingleBits_CheckOutOfRange)
	int value = 5;
	int* ptr = &value;
	
	ASSERT_THAT( ERROR_OUT_OF_RANGE == FlipSingleBits(ptr, 32) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FlipSingleBits_CheckCase_All1Bit)
	int value = 1;
	int beforeValue;
	int* ptr = &value;
	size_t i;
	
	for(i = 0; i < INT_BITS; ++i)
	{
		beforeValue = value;
		ASSERT_THAT( SUCCESS == FlipSingleBits(ptr, i) && 0 == value );
		value = beforeValue;
		value *= 2;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FlipSingleBits_CheckCase_AllBits)
	int value = 1;
	int beforeValue;
	int resulteValue = 0;
	int step = 1;
	int* ptr = &value;
	size_t i;
	
	for(i = 0; i < INT_BITS; ++i)
	{
		beforeValue = value;
		step *= 2;
		ASSERT_THAT( SUCCESS == FlipSingleBits(ptr, i) && resulteValue == value );
		value = beforeValue;
		value += step;
		resulteValue = beforeValue;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- FlipTwoBits -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(FlipTwoBits_CheckNULL)
	ASSERT_THAT( ERROR_NOT_INITIALIZE == FlipTwoBits(NULL, 5, 8) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FlipTwoBits_CheckOutOfRange1)
	int value = 5;
	int* ptr = &value;
	
	ASSERT_THAT( ERROR_OUT_OF_RANGE == FlipTwoBits(ptr, 32, 8) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FlipTwoBits_CheckOutOfRange2)
	int value = 5;
	int* ptr = &value;
	
	ASSERT_THAT( ERROR_OUT_OF_RANGE == FlipTwoBits(ptr, 3, 32) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FlipTwoBits_CheckTheSameValue)
	int value = 5;
	int* ptr = &value;
	
	ASSERT_THAT( ERROR_THE_SAME_BIT == FlipTwoBits(ptr, 11, 11) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FlipTwoBits_CheckCase_All2Bit)
	int value = 1;
	int result = value << (INT_BITS - 1);
	int beforeValue;
	int* ptr = &value;
	size_t i;
	
	for(i = 0; i < (INT_BITS - 1); ++i)
	{
		beforeValue = value;
		ASSERT_THAT( SUCCESS == FlipTwoBits(ptr, (INT_BITS - 1), i) && result == value );
		value = beforeValue;
		value *= 2;
	}
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(flipBits API)
	PRINT(RangeFlipBits_CheckNULL)
	PRINT(RangeFlipBits_CheckOutOfRange1)
	PRINT(RangeFlipBits_CheckOutOfRange2)
	PRINT(RangeFlipBits_CheckIllegalRange)
	PRINT(RangeFlipBits_CheckCase_1Bit)
	PRINT(RangeFlipBits_CheckCase_1Bit_MostSignificant)
	PRINT(RangeFlipBits_CheckCase_All1Bit)
	PRINT(RangeFlipBits_CheckCase_AllBits)
	
	PRINT(FlipSingleBits_CheckNULL)
	PRINT(FlipSingleBits_CheckOutOfRange)
	PRINT(FlipSingleBits_CheckCase_All1Bit)
	PRINT(FlipSingleBits_CheckCase_AllBits)
	
	PRINT(FlipTwoBits_CheckNULL)
	PRINT(FlipTwoBits_CheckOutOfRange1)
	PRINT(FlipTwoBits_CheckOutOfRange2)
	PRINT(FlipTwoBits_CheckTheSameValue)
	PRINT(FlipTwoBits_CheckCase_All2Bit)
END_SET
/*----------------------------------------------------------------------------*/






