/** 
 *  @file tests.c
 *  @brief tests file for power
 * 
 *  @details The function return the value of n raised to the power of k.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-21    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "power.h"			/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */




/*************************** Tests for API functions **************************/
/*----------------------------------- Power ----------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(Power_CheckCase_0)
	ASSERT_THAT( 0 == Power(0, 5) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Power_CheckCase_1)
	ASSERT_THAT( 1 == Power(1, 5) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Power_CheckCase_2)
	ASSERT_THAT( 32 == Power(2, 5) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Power_CheckCase_3)
	ASSERT_THAT( 81 == Power(3, 4) );
END_TEST
/*----------------------------------------------------------------------------*/


/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Power)
	PRINT(Power_CheckCase_0)
	PRINT(Power_CheckCase_1)
	PRINT(Power_CheckCase_2)
	PRINT(Power_CheckCase_3)
END_SET
/*----------------------------------------------------------------------------*/






