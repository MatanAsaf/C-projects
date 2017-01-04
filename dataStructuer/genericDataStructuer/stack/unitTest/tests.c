/** 
 *  @file 		tests.c
 *  @brief 		Create a set of test for Generic Stack data structure
 * 
 *  @details 	The API stores pointer to user provided elements of generic type.
 * 				The stack is heap allocated and can grow and shrink on demand.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2016-12-27    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

 
#include "stack.h"		/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <time.h> 		/* for time_t */

#define SIZE (10) /* SIZE = The size of the stack (num of element) in each test */
#define MAX_RAND_VALUE (50) /* MAX_RAND_VALUE = The max value the function rand() can produce */   



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to stack values in sort order 
 *
 * @param   _stk        = The pushress of the the source stack
 * @param   _array		= Pointer to  the elements neeeded to insert to stack 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 *
 * @return   void
*/
static StackResult InsertSortedValues(Stack* _stk, int* _array ,size_t _nElements, int _step, int _minValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to stack random values 
 *
 * @param   _stk        = The pushress of the the source stack
 * @param   _array		= Pointer to  the elements neeeded to insert to stack 
 * @param   _nElements  = The number of elements to insert
 * @param   _maxValue   = The max value the rand() function can prduce, the max value in the stack
 *
 * @return   void
*/
static StackResult InsertRandValues(Stack* _stk, int* _array, size_t _nElements, int _maxValue);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*------------------------------- StackCreate -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(StackCreate_CheckNoSize)
	Stack* ip;
	Stack* retVal;
    
    ip = StackCreate(0, 1);
	retVal = ip;
	
    StackDestroy(&ip, NULL);
    
    ASSERT_THAT( NULL != retVal );
END_TEST
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
TEST(StackCreate_CheckNoIncSize)
    Stack* ip;
	Stack* retVal;
    
    ip = StackCreate(1, 0);
	retVal = ip;
	
    StackDestroy(&ip, NULL);
    
    ASSERT_THAT( NULL != retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackCreate_CheckRegular)
    Stack* ip;
	Stack* retVal;
    
    ip = StackCreate(5, 5);
	retVal = ip;
	
    StackDestroy(&ip, NULL);
    
    ASSERT_THAT( NULL != retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackCreate_NoElements)
    Stack* ip;
    
    ip = StackCreate(0, 0);
    
    ASSERT_THAT( NULL == ip );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- StackDestroy ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(StackDestroy_DoubleFree)
    Stack* ip; 
    
    ip = StackCreate(5, 5);

    StackDestroy( &ip, NULL);
    
    ASSERT_THAT( NULL == ip );
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------------- StackPush -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(StackPush_CheckNull)
	int item = 555;
    StackResult status;

    status = StackPush(NULL, &item); 
    ASSERT_THAT( STACK_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPush_CheckItemNull) 
    Stack* ip;
    StackResult status;
    
    ip = StackCreate(1, 0);
    
    status = StackPush(ip, NULL);
    StackDestroy( &ip, NULL); 
    ASSERT_THAT( DATA_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPush_Overflow) 
    Stack* ip;
    int item[] = {555, 444};
    StackResult status;
    
    ip = StackCreate(1, 0);
    
    status = StackPush(ip, &item[0]);
    status = StackPush(ip, &item[1]);

    StackDestroy( &ip, NULL); 
    ASSERT_THAT( STACK_OVERFLOW_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPush_Realloc) 
    Stack* ip;
    int item[] = {555, 444};
    StackResult status;
    
    ip = StackCreate(1, 1);
    
    status = StackPush(ip, &item[0]);
    status = StackPush(ip, &item[1]);

    StackDestroy( &ip, NULL);
    ASSERT_THAT( STACK_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPush_ReallocFailed) 
    Stack* ip;
    int item = 555;
    StackResult status;
    
    ip = StackCreate(0, 2000000000);
    
    status = StackPush(ip, &item);

    StackDestroy( &ip, NULL);
    ASSERT_THAT( STACK_ALLOCATION_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPush_Regular) 
    Stack* ip;
    int item[] = {555, 444};
    StackResult status;
    
    ip = StackCreate(2, 0);
    
    status = StackPush(ip, &item[0]);
    status = StackPush(ip, &item[1]);
    
    StackDestroy( &ip, NULL); 
    ASSERT_THAT( STACK_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------------- StackPop --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(StackPop_CheckNull) 
	int item = 555;
    StackResult status;

    status = StackPop(NULL, (void**)&item);
    ASSERT_THAT( STACK_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPop_CheckItemNull) 
    Stack* ip;
    StackResult status;
    
    ip = StackCreate(1, 0);
    
    status = StackPop(ip, NULL);
    StackDestroy( &ip, NULL); 
    ASSERT_THAT( DATA_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPop_CheckUnderflow) 
    Stack* ip;
    int* testVar;
    StackResult status;
    
    ip = StackCreate(1, 0);

    status = StackPop(ip, (void**)&testVar);
    StackDestroy( &ip, NULL); 
    
    ASSERT_THAT( STACK_UNDERFLOW_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPop_DicreseRealloc)
    Stack* ip;
    int item[] = {555, 444, 333};
    StackResult status[5];
    int* testVar;
    size_t i;
    
    ip = StackCreate(1, 1);
    
    status[0] = StackPush(ip, &item[0]);
    status[1] = StackPush(ip, &item[1]);
    status[2] = StackPush(ip, &item[2]);
    
    status[3] = StackPop(ip, (void**)&testVar);
    status[4] = StackPop(ip, (void**)&testVar);
    
    StackDestroy( &ip, NULL);
    
    for(i = 0; i < 5; ++i)
    {
    	ASSERT_THAT( STACK_SUCCESS == status[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPop_IntRegular)
    Stack* ip;
    int item[] = {555, 444};
    int* testVar;
    int temp = 0;
    
    testVar = &temp;
    
    ip = StackCreate(2, 0);
    
    StackPush(ip, &item[0]);
    StackPush(ip, &item[1]);
    StackPop(ip, (void**)&testVar);
    
    StackDestroy( &ip, NULL);  
    ASSERT_THAT( *testVar == item[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPop_CharRegular)
    Stack* ip;
    char item[] = {'z', 'g'};
    char* testVar;
    char temp = 'A';
    
    testVar = &temp;
    
    ip = StackCreate(2, 0);
    
    StackPush(ip, &item[0]);
    StackPush(ip, &item[1]);
    StackPop(ip, (void**)&testVar);
    
    StackDestroy( &ip, NULL);
    ASSERT_THAT( *testVar == item[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPop_DoubleRegular)
    Stack* ip;
    double item[] = {555.25, 444.33};
    double* testVar;
    double temp = 0.3;
    
    testVar = &temp;
    
    ip = StackCreate(2, 0);
    
    StackPush(ip, &item[0]);
    StackPush(ip, &item[1]);
    StackPop(ip, (void**)&testVar);
    
    StackDestroy( &ip, NULL);
    ASSERT_THAT( *testVar == item[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(StackPop_CheckFull)
    Stack* ip;
    int item[SIZE];
    int* testVar[SIZE];
    StackResult status;
    size_t i;
    
    ip = StackCreate(SIZE, 0);
    
    status = InsertSortedValues(ip, item ,SIZE, 1, 0);
    
    for( i = 0; i < SIZE; ++i)
    {
    	StackPop(ip, (void**)&testVar[i]);
    }
    
    StackDestroy( &ip, NULL);  
    
    ASSERT_THAT( STACK_SUCCESS == status );
    
    for( i = 0; i < SIZE; ++i)
    {
    	ASSERT_THAT( item[SIZE -1 -i] == *testVar[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- StackSize --------------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on stack in StackSize
 * Input 	size(ptr = NULL) --> Output 0
 */
TEST(StackSize_CheckNull) 
    size_t result;

    result = StackSize(NULL);
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function StackSize
 * Input 	size(vec with SIZE elements) --> Output SIZE
 */
TEST(StackSize_CheckRegular) 
    size_t result;
    Stack* ip;
    int item[SIZE];
    
    ip = StackCreate(SIZE, 0);
    InsertRandValues(ip, item, SIZE, MAX_RAND_VALUE);

    result = StackSize(ip);
    
    StackDestroy( &ip, NULL);
    ASSERT_THAT( SIZE == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function StackSize
 * Input 	size(size, element) --> Output element
 */
TEST(StackSize_CheckCorrectElement)
    size_t result;
    Stack* ip;
    int item[SIZE - 1];
    
    ip = StackCreate(SIZE, 0);
    InsertRandValues(ip, item, SIZE - 1, MAX_RAND_VALUE);

    result = StackSize(ip);
    
    StackDestroy( &ip, NULL);
    ASSERT_THAT( (SIZE - 1) == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- StackCapacity ------------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on stack in StackCapacity
 * Input 	Capacity(ptr = NULL) --> Output 0
 */
TEST(StackCapacity_CheckNull) 
    size_t result;

    result = StackCapacity(NULL);
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function StackCapacity
 * Input 	Capacity(vec at the size of SIZE) --> Output SIZE
 */
TEST(StackCapacity_CheckBase) 
    size_t result;
    Stack* ip;
    int item[SIZE];
    
    ip = StackCreate(SIZE, 0);
    InsertRandValues(ip, item, SIZE, MAX_RAND_VALUE);

    result = StackCapacity(ip);
    
    StackDestroy( &ip, NULL);
    ASSERT_THAT( SIZE == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function StackCapacity with realloc
 * Input 	Capacity(size, element) --> Output element
 */
TEST(StackCapacity_CheckAfterRealloc) 
    size_t result;
    Stack* ip;
    int item[SIZE + 5];
    
    ip = StackCreate(SIZE, 5);
    InsertRandValues(ip, item, SIZE + 5, MAX_RAND_VALUE);

    result = StackCapacity(ip);
    
    StackDestroy( &ip, NULL);
    ASSERT_THAT( (SIZE + 5) == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function StackCapacity with realloc
 * Input 	Capacity(size, element) --> Output element
 */
TEST(StackCapacity_CheckAfterRealloc2) 
    size_t result;
    Stack* ip;
    int item[SIZE + 5];
    
    ip = StackCreate(SIZE, 7);
    InsertRandValues(ip, item, SIZE + 5, MAX_RAND_VALUE);

    result = StackCapacity(ip);
    
    StackDestroy( &ip, NULL);
    ASSERT_THAT( (SIZE + 7) == result );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************** Tests SET *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Test Generic stack Module)
	PRINT(StackCreate_CheckNoSize)
	PRINT(StackCreate_CheckNoIncSize)
	PRINT(StackCreate_CheckRegular)  
	PRINT(StackCreate_NoElements)

	PRINT(StackDestroy_DoubleFree)

	PRINT(StackPush_CheckNull)
	PRINT(StackPush_CheckItemNull)
	PRINT(StackPush_Overflow)
	PRINT(StackPush_Realloc)
	PRINT(StackPush_ReallocFailed)
	PRINT(StackPush_Regular)

	PRINT(StackPop_CheckNull) 
	PRINT(StackPop_CheckItemNull)
	PRINT(StackPop_CheckUnderflow)
	PRINT(StackPop_DicreseRealloc)
	PRINT(StackPop_IntRegular)
	PRINT(StackPop_CharRegular)
	PRINT(StackPop_DoubleRegular)
	PRINT(StackPop_CheckFull)
	
	PRINT(StackSize_CheckNull) 
	PRINT(StackSize_CheckRegular) 
	PRINT(StackSize_CheckCorrectElement)
	
	PRINT(StackCapacity_CheckNull) 
	PRINT(StackCapacity_CheckBase)
	PRINT(StackCapacity_CheckAfterRealloc)
	PRINT(StackCapacity_CheckAfterRealloc2)
END_SET
/*----------------------------------------------------------------------------*/




/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to stack values in sort order 
 *
 * @param   _stk        = The pushress of the the source stack
 * @param   _array		= Pointer to  the elements neeeded to insert to stack 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 *
 * @return   void
*/
static StackResult InsertSortedValues(Stack* _stk, int* _array ,size_t _nElements, int _step, int _minValue)
{
    StackResult status;
    size_t i;
    int value = _minValue;
    
    for( i = 0;  i < _nElements; ++i )
    {
    	_array[i] = value;
        status = StackPush(_stk, &_array[i]);
        if(STACK_SUCCESS != status)
        {
        	return status;
        }
        value += _step;
    }
    
    return STACK_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to stack random values 
 *
 * @param   _stk        = The pushress of the the source stack
 * @param   _array		= Pointer to  the elements neeeded to insert to stack 
 * @param   _nElements  = The number of elements to insert
 * @param   _maxValue   = The max value the rand() function can prduce, the max value in the stack
 *
 * @return   void
*/
static StackResult InsertRandValues(Stack* _stk, int* _array, size_t _nElements, int _maxValue)
{
    StackResult status;
    size_t i;
    time_t t;
    int value;
    
    srand((unsigned) time(&t)); 
    value = rand() % _maxValue;
     
    for(i = 0; i < _nElements; i++)
    {
    	_array[i] = value;
        status = StackPush(_stk, &_array[i]);
        if(STACK_SUCCESS != status)
        {
        	return status;
        }
        value = rand() % _maxValue;
    }
    
    return STACK_SUCCESS;   
}
/*----------------------------------------------------------------------------*/
