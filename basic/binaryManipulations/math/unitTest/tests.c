/** 
 *  @file 		tests.c
 *  @brief 		tests file for math API
 * 
 *  @details 	The math API do a different math calculations using bit manipulations
 * 
 *  @warning 	This bit manipulations work only on 32 bit system
 *
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		2016-12-25    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "math.h"		/* header file */
#include "matan_test.h"	/* def of TEST test */
#include <stdio.h>  	/* for printf */
#include <stdlib.h> 	/* for size_t & rand */

#define DEBUG (0)
#define MAX_RAND_VALUE (1000000) /* The max value the function rand() can produce */  
#define MAX_INT (2147483647)
#define INT_BITS 	(32)

/***************************** Functions Declaration **************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return the value of n raised to the power of k.
 *
 * Time Complexity: N.
 *
 * @param       n		=	The number to calculate
 * @param       k		=	The value of the power
 *
 * @return		The function return the value of n raised to the power of k.
 */
size_t Power(size_t _n, size_t _k);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*-------------------------------- CheckSign ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CheckSign_CheckZero)
	ASSERT_THAT( 1 == CheckSign(0) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CheckSign_CheckNegetive)
	int value = (rand() % MAX_RAND_VALUE) * -1;
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( -1 == CheckSign(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CheckSign_CheckPositive)
	int value = (rand() % MAX_RAND_VALUE);
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( 1 == CheckSign(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------- ChangeToAbsolute1 -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ChangeToAbsolute1_CheckPositive)
	int value = (rand() % MAX_RAND_VALUE);
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( value == ChangeToAbsolute1(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ChangeToAbsolute1_CheckNegetive)
	int value = (rand() % MAX_RAND_VALUE) * -1;
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( (-1 * value) == ChangeToAbsolute1(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------- ChangeToAbsolute2 -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ChangeToAbsolute2_CheckPositive)
	int value = (rand() % MAX_RAND_VALUE);
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( value == ChangeToAbsolute2(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ChangeToAbsolute2_CheckNegetive)
	int value = (rand() % MAX_RAND_VALUE) * -1;
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( (-1 * value) == ChangeToAbsolute2(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------- ChangeToAbsolute3 -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ChangeToAbsolute3_CheckPositive)
	int value = (rand() % MAX_RAND_VALUE);
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( value == ChangeToAbsolute3(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ChangeToAbsolute3_CheckNegetive)
	int value = (rand() % MAX_RAND_VALUE) * -1;
	
	#if DEBUG
		printf("%d\n", value);
	#endif
	
	ASSERT_THAT( (-1 * value) == ChangeToAbsolute3(value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------- CheckPowerOfTwo ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CheckPowerOfTwo_CheckCase_PowerOfTwo)
	size_t i;
	unsigned int value;
	
	for(i = 0; i < INT_BITS; ++i)
	{
		value = (unsigned int)Power(2, i);
		
		#if DEBUG
		printf("%u\n", value);
		#endif
	
		ASSERT_THAT( 1 == CheckPowerOfTwo(value) );	
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------------- Sum -------------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(Sum_CheckWithoutR)
	int value1 = 1;
	int value2 = 2;
	int sum = value1 + value2;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
		printf("Result: %d\n", sum);
	#endif
	
	ASSERT_THAT( sum == Sum(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Sum_CheckWithR_Case1)
	int value1 = 1;
	int value2 = 1;
	int sum = value1 + value2;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
		printf("Result: %d\n", sum);
	#endif
	
	ASSERT_THAT( sum == Sum(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Sum_CheckWithR_Case2)
	int value1 = 7;
	int value2 = 7;
	int sum = value1 + value2;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
		printf("Result: %d\n", sum);
	#endif
	
	ASSERT_THAT( sum == Sum(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Sum_CheckWithR_Case3)
	int value1 = 7;
	int value2 = 15;
	int sum = value1 + value2;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
		printf("Result: %d\n", sum);
	#endif
	
	ASSERT_THAT( sum == Sum(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Sum_CheckRandPositive)
	int value1 = (rand() % MAX_RAND_VALUE);
	int value2 = (rand() % MAX_RAND_VALUE);
	int sum = value1 + value2;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
		printf("Result: %d\n", sum);
	#endif
	
	ASSERT_THAT( sum == Sum(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Sum_CheckRandNegetive)
	int value1 = (rand() % MAX_RAND_VALUE) * -1;
	int value2 = (rand() % MAX_RAND_VALUE) * -1;
	int sum = value1 + value2;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
		printf("Result: %d\n", sum);
	#endif
	
	ASSERT_THAT( sum == Sum(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/



/*------------------------------- Multiply ----------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(Multiply_CheckZero1)
	size_t  value1 = 0;
	size_t  value2 = (size_t)(rand() % MAX_RAND_VALUE);
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
	#endif
	
	ASSERT_THAT( 0 == Multiply(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Multiply_CheckZero2)
	size_t  value1 = (size_t)(rand() % MAX_RAND_VALUE);
	size_t  value2 = 0;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
	#endif
	
	ASSERT_THAT( 0 == Multiply(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Multiply_CheckRand)
	size_t  value1 = (size_t)(rand() % MAX_RAND_VALUE);
	size_t  value2 = (size_t)(rand() % MAX_RAND_VALUE);
	size_t result = value1 * value2;
	
	#if DEBUG
		printf("%d\n", value1);
		printf("%d\n", value2);
		printf("Result: %d\n", result);
	#endif
	
	ASSERT_THAT( result == Multiply(value1, value2) );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Math API)
	PRINT(CheckSign_CheckZero)
	PRINT(CheckSign_CheckNegetive)
	PRINT(CheckSign_CheckPositive)
	
	PRINT(ChangeToAbsolute1_CheckPositive)
	PRINT(ChangeToAbsolute1_CheckNegetive)
	
	PRINT(ChangeToAbsolute2_CheckPositive)
	PRINT(ChangeToAbsolute2_CheckNegetive)
	
	PRINT(ChangeToAbsolute3_CheckPositive)
	PRINT(ChangeToAbsolute3_CheckNegetive)
	
	PRINT(CheckPowerOfTwo_CheckCase_PowerOfTwo)
	
	PRINT(Sum_CheckWithoutR)
	PRINT(Sum_CheckWithR_Case1)
	PRINT(Sum_CheckWithR_Case2)
	PRINT(Sum_CheckWithR_Case3)
	PRINT(Sum_CheckRandPositive)
	PRINT(Sum_CheckRandNegetive)
	
	PRINT(Multiply_CheckZero1)
	PRINT(Multiply_CheckZero2)
	PRINT(Multiply_CheckRand)
END_SET
/*----------------------------------------------------------------------------*/




/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return the value of n raised to the power of k.
 *
 * Time Complexity: N.
 *
 * @param       n		=	The number to calculate
 * @param       k		=	The value of the power
 *
 * @return		The function return the value of n raised to the power of k.
 */
size_t Power(size_t _n, size_t _k)
{
	if( 0 == _k )
    {
        return 1;
    }
    
    return (Power(_n, _k-1) * _n);
}
/*----------------------------------------------------------------------------*/
