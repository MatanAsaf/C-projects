/** 
 *  @file tests.c
 *  @brief tests file for fibonacci
 * 
 *  @details This function caculate fibonacci problam with and without recurssion.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-21    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "fibonacci.h"		/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <stddef.h> 		/* for size_t */

#define DEBUG (0)



/*************************** Tests for API functions **************************/
/*--------------------------------- Fibonacci --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(Fibonacci_CheckCase_0)
	size_t value = 0;
	size_t result = Fibonacci(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Fibonacci_CheckCase_1)
	size_t value = 1;
	size_t result = Fibonacci(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 1 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Fibonacci_CheckCase_5)
	size_t value = 5;
	size_t result = Fibonacci(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 5 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Fibonacci_CheckCase_15)
	size_t value = 15;
	size_t result = Fibonacci(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 610 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Fibonacci_CheckCase_30)
	size_t value = 30;
	size_t result = Fibonacci(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 832040 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Fibonacci_CheckCase_40)
	size_t value = 40;
	size_t result = Fibonacci(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 102334155 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- FibonacciRec -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(FibonacciRec_CheckCase_0)
	size_t value = 0;
	size_t result = FibonacciRec(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FibonacciRec_CheckCase_1)
	size_t value = 1;
	size_t result = FibonacciRec(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 1 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FibonacciRec_CheckCase_5)
	size_t value = 5;
	size_t result = FibonacciRec(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 5 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FibonacciRec_CheckCase_15)
	size_t value = 15;
	size_t result = FibonacciRec(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 610 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FibonacciRec_CheckCase_30)
	size_t value = 30;
	size_t result = FibonacciRec(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 832040 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FibonacciRec_CheckCase_40)
	size_t value = 40;
	size_t result = FibonacciRec(value);
	
	#if DEBUG
		printf("The result for value:%u is: %u\n",value, result );
	#endif
	
	ASSERT_THAT( 102334155 == result );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(fibonacci)
	PRINT(Fibonacci_CheckCase_0)
	PRINT(Fibonacci_CheckCase_1)
	PRINT(Fibonacci_CheckCase_5)
	PRINT(Fibonacci_CheckCase_15)
	PRINT(Fibonacci_CheckCase_30)
	PRINT(Fibonacci_CheckCase_40)
	
	PRINT(FibonacciRec_CheckCase_0)
	PRINT(FibonacciRec_CheckCase_1)
	PRINT(FibonacciRec_CheckCase_5)
	PRINT(FibonacciRec_CheckCase_15)
	PRINT(FibonacciRec_CheckCase_30)
	PRINT(FibonacciRec_CheckCase_40)
END_SET
/*----------------------------------------------------------------------------*/






