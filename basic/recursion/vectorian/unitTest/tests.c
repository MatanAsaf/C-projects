/** 
 *  @file tests.c
 *  @brief tests file for vectorian
 *
 *  @details The function return the value of index multiply all the numbers before him
 *			 starting from 1.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-21    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "vectorian.h"			/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */




/*************************** Tests for API functions **************************/
/*--------------------------------- vectorian --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(Vectorian_CheckCase_0)
	ASSERT_THAT( 0 == Vectorian(0) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Vectorian_CheckCase_1)
	ASSERT_THAT( 1 == Vectorian(1) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Vectorian_CheckCase_2)
	ASSERT_THAT( 2 == Vectorian(2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Vectorian_CheckCase_3)
	ASSERT_THAT( 6 == Vectorian(3) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Vectorian_CheckCase_4)
	ASSERT_THAT( 24 == Vectorian(4) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Vectorian_CheckCase_5)
	ASSERT_THAT( 120 == Vectorian(5) );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Vectorian)
	PRINT(Vectorian_CheckCase_0)
	PRINT(Vectorian_CheckCase_1)
	PRINT(Vectorian_CheckCase_2)
	PRINT(Vectorian_CheckCase_3)
	PRINT(Vectorian_CheckCase_4)
	PRINT(Vectorian_CheckCase_5)

END_SET
/*----------------------------------------------------------------------------*/






