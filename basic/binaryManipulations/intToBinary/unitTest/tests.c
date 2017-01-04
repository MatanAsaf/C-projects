/** 
 *  @file 		tests.c
 *  @brief 		tests file for intToBinary function
 * 
 *  @details 	The function convert a number to it's representation in Binary.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 		2016-12-25    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "intToBinary.h"	/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */

#define DEBUG (0)
#define N_BYTES (100)
#define RANGE (100)
#define MAX_UNSIGNED_INT (2147483647)


/*************************** Tests for API functions **************************/
/*-------------------------------- intToBinary -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(intToBinary_CheckNull)
	ASSERT_THAT( ERROR_NOT_INITIALIZE  == intToBinary(1, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(intToBinary_CheckCase_AllPositive)
	char retVal[N_BYTES];
	int value = 0;
	size_t i;
	ERRORS status;
	
	for(i = 0; i < RANGE; ++i)
	{
		status = intToBinary(value, retVal);
	
		#if DEBUG
		printf("\nValue %d in Binary is: %s\n", value, retVal);
		#endif
		
		ASSERT_THAT( SUCCESS  == status );
		
		++value;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(intToBinary_CheckCase_AllNegative)
	char retVal[N_BYTES];
	int value = 0;
	size_t i;
	ERRORS status;
	
	for(i = 0; i < RANGE; ++i)
	{
		status = intToBinary(value, retVal);
	
		#if DEBUG
		printf("\nValue %d in Binary is: %s\n", value, retVal);
		#endif
		
		ASSERT_THAT( SUCCESS  == status );
		
		--value;
	}
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(IntToBinary Function)
	PRINT(intToBinary_CheckNull)
	PRINT(intToBinary_CheckCase_AllPositive)
	PRINT(intToBinary_CheckCase_AllNegative)
END_SET
/*----------------------------------------------------------------------------*/


