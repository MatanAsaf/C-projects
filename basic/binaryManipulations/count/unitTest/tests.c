/** 
 *  @file tests.c
 *  @brief tests file for countOnBits
 * 
 *  @details 	The API countOnBits count the number of ones in a binary representation.
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
 
#include "countOnBits.h"	/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */

#define INT_BITS 	(32)


/*************************** Tests for API functions **************************/
/*-------------------------------- CountOnBits -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CountOnBits_CheckCase_1Bit)
	size_t i;
	int value = 1;
	
	for(i = 0; i < INT_BITS; ++i)
	{
		ASSERT_THAT( 1 == CountOnBits(value) );
		value <<= 1;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CountOnBits_CheckCase_AllBit)
	size_t i;
	int value = 1;
	
	value <<= (INT_BITS -1);
	
	for(i = 0; i < INT_BITS; ++i)
	{
		ASSERT_THAT( (i + 1) == CountOnBits(value) );
		value >>= 1;
	}
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(countOnBits)
	PRINT(CountOnBits_CheckCase_1Bit)
	PRINT(CountOnBits_CheckCase_AllBit)
END_SET
/*----------------------------------------------------------------------------*/






