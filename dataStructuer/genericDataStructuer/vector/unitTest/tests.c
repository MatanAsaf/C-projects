/** 
 *  @file 		tests.c
 *  @brief 		Create a set of test for Generic Vector data structure
 * 
 *  @details 	The API stores pointer to user provided elements of generic type.
 * 				The Vector is heap allocated and can grow and shrink on demand.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2016-12-26    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

 
#include "vector.h"		/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <time.h> 		/* for time_t */

#define SIZE (10) /* SIZE = The size of the vector (num of element) in each test */
#define MAX_RAND_VALUE (50) /* MAX_RAND_VALUE = The max value the function rand() can produce */   



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check cases for null for createVector function
 *
 * @param   _size       = Initial capacity
 * @param   _incSize	= Vector will grow or shrink on demand by this size 
 *
 * Input 	create(Y,X) --> Output is NOT NULL for all cases exspet X==Y==0
 */
static Vector* checkNull(size_t _size, size_t _incSize);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to vector values in sort order 
 *
 * @param   _vec        = The address of the the source vector
 * @param   _array		= Pointer to  the elements neeeded to insert to vector 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 *
 * @return   void
*/
static VectorResult InsertSortedValues(Vector* _vec, int* _array ,size_t _nElements, int _step, int _minValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to vector random values 
 *
 * @param   _vec        = The address of the the source vector
 * @param   _array		= Pointer to  the elements neeeded to insert to vector 
 * @param   _nElements  = The number of elements to insert
 * @param   _maxValue   = The max value the rand() function can prduce, the max value in the vector
 *
 * @return   void
*/
static VectorResult InsertRandValues(Vector* _vec, int* _array, size_t _nElements, int _maxValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that change all variables under index 100 to value of context 
 * 
 * @param   _element    = Pointer to  the element
 * @param   _index		= The index of that element in the vector 
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Countinue loop for all elements
*/
static int	ChangeValueAction(void* _element, size_t _index, void* _context);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*------------------------------- VectorCreate -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(VectorCreate_CheckNoSize)
    ASSERT_THAT( NULL != checkNull(0,1) );
END_TEST
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
TEST(VectorCreate_CheckNoIncSize)
    ASSERT_THAT( NULL != checkNull(1,0) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(VectorCreate_CheckRegular)
    ASSERT_THAT( NULL != checkNull(5,5) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(VectorCreate_NoElements)
    ASSERT_THAT( NULL == checkNull(0,0) );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- VectorDestroy ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(VectorDestroy_DoubleFree)
    Vector* ip; 
    
    ip = VectorCreate(5, 5);

    VectorDestroy( &ip, NULL);
    
    ASSERT_THAT( NULL == ip );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- VectorAppend ------------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL in VectorAppend function == 0
 * Input 	Append(ptr = NULL) --> Output VECTOR_UNINITIALIZED_ERROR
 */
TEST(VectorAppend_CheckNull)
	int item = 555;
    VectorResult status;

    status = VectorAppend(NULL, &item); 
    ASSERT_THAT( VECTOR_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on item in VectorAppend
 * Input 	Append(item = NULL) --> Output ITEM_UNINITIALIZED_ERROR
 */
TEST(VectorAppend_CheckItemNull) 
    Vector* ip;
    VectorResult status;
    
    ip = VectorCreate(1, 0);
    
    status = VectorAppend(ip, NULL);
    VectorDestroy( &ip, NULL); 
    ASSERT_THAT( ITEM_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check OVERFLOW
 * Input 	create(1,0) --> add()*2
 */
TEST(VectorAppend_Overflow) 
    Vector* ip;
    int item[] = {555, 444};
    VectorResult status;
    
    ip = VectorCreate(1, 0);
    
    status = VectorAppend(ip, &item[0]);
    status = VectorAppend(ip, &item[1]);

    VectorDestroy( &ip, NULL); 
    ASSERT_THAT( VECTOR_OVERFLOW_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Realloc
 * Input 	create(1,1) --> add()*2
 */
TEST(VectorAppend_Realloc) 
    Vector* ip;
    int item[] = {555, 444};
    VectorResult status;
    
    ip = VectorCreate(1, 1);
    
    status = VectorAppend(ip, &item[0]);
    status = VectorAppend(ip, &item[1]);

    VectorDestroy( &ip, NULL);
    ASSERT_THAT( VECTOR_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Realloc Failed on MAX SIZE increse
 * Input 	create(1,0) --> add()*2
 */
TEST(VectorAppend_ReallocFailed) 
    Vector* ip;
    int item = 555;
    VectorResult status;
    
    ip = VectorCreate(0, 2000000000);
    
    status = VectorAppend(ip, &item);

    VectorDestroy( &ip, NULL);
    ASSERT_THAT( VECTOR_ALLOCATION_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Append Function for int varibale
 * Input 	create(1,0) --> add()*2
 */
TEST(VectorAppend_Regular) 
    Vector* ip;
    int item[] = {555, 444};
    VectorResult status;
    
    ip = VectorCreate(2, 0);
    
    status = VectorAppend(ip, &item[0]);
    status = VectorAppend(ip, &item[1]);
    
    VectorDestroy( &ip, NULL); 
    ASSERT_THAT( VECTOR_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/



/*-------------------------------- VectorRemove ------------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorRemove
 * Input 	Remove(ptr = NULL) --> Output VECTOR_UNINITIALIZED_ERROR
 */
TEST(VectorRemove_CheckNull) 
	int item = 555;
    VectorResult status;

    status = VectorRemove(NULL, (void**)&item);
    ASSERT_THAT( VECTOR_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on item in VectorRemove
 * Input 	Remove(item = NULL) --> Output ITEM_UNINITIALIZED_ERROR
 */
TEST(VectorRemove_CheckItemNull) 
    Vector* ip;
    VectorResult status;
    
    ip = VectorCreate(1, 0);
    
    status = VectorRemove(ip, NULL);
    VectorDestroy( &ip, NULL); 
    ASSERT_THAT( ITEM_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on item in VectorRemove
 * Input 	Remove(item = NULL) --> Output ITEM_UNINITIALIZED_ERROR
 */
TEST(VectorRemove_CheckUnderflow) 
    Vector* ip;
    int* testVar;
    VectorResult status;
    
    ip = VectorCreate(1, 0);

    status = VectorRemove(ip, (void**)&testVar);
    VectorDestroy( &ip, NULL); 
    
    ASSERT_THAT( VECTOR_UNDERFLOW_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Realloc on discrese
 * Input 	create(1,0) --> add()*3 --> remove()*2 
 */
TEST(VectorRemove_DicreseRealloc)
    Vector* ip;
    int item[] = {555, 444, 333};
    VectorResult status[5];
    int* testVar;
    size_t i;
    
    ip = VectorCreate(1, 1);
    
    status[0] = VectorAppend(ip, &item[0]);
    status[1] = VectorAppend(ip, &item[1]);
    status[2] = VectorAppend(ip, &item[2]);
    
    status[3] = VectorRemove(ip, (void**)&testVar);
    status[4] = VectorRemove(ip, (void**)&testVar);
    
    VectorDestroy( &ip, NULL);
    
    for(i = 0; i < 5; ++i)
    {
    	ASSERT_THAT( VECTOR_SUCCESS == status[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Remove Function for int varibale
 * Input 	create(1,0) --> add()*2
 */
TEST(VectorRemove_IntRegular)
    Vector* ip;
    int item[] = {555, 444};
    int* testVar;
    int temp = 0;
    
    testVar = &temp;
    
    ip = VectorCreate(2, 0);
    
    VectorAppend(ip, &item[0]);
    VectorAppend(ip, &item[1]);
    VectorRemove(ip, (void**)&testVar);
    
    VectorDestroy( &ip, NULL);  
    ASSERT_THAT( *testVar == item[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Remove Function for char varibale
 * Input 	create(1,0) --> add()*2
 */
TEST(VectorRemove_CharRegular)
    Vector* ip;
    char item[] = {'z', 'g'};
    char* testVar;
    char temp = 'A';
    
    testVar = &temp;
    
    ip = VectorCreate(2, 0);
    
    VectorAppend(ip, &item[0]);
    VectorAppend(ip, &item[1]);
    VectorRemove(ip, (void**)&testVar);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( *testVar == item[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Remove Function for double varibale
 * Input 	create(1,0) --> add()*2
 */
TEST(VectorRemove_DoubleRegular)
    Vector* ip;
    double item[] = {555.25, 444.33};
    double* testVar;
    double temp = 0.3;
    
    testVar = &temp;
    
    ip = VectorCreate(2, 0);
    
    VectorAppend(ip, &item[0]);
    VectorAppend(ip, &item[1]);
    VectorRemove(ip, (void**)&testVar);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( *testVar == item[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(VectorRemove_CheckFull)
    Vector* ip;
    int item[SIZE];
    int* testVar[SIZE];
    VectorResult status;
    size_t i;
    
    ip = VectorCreate(SIZE, 0);
    
    status = InsertSortedValues(ip, item ,SIZE, 1, 0);
    
    for( i = 0; i < SIZE; ++i)
    {
    	VectorRemove(ip, (void**)&testVar[i]);
    }
    
    VectorDestroy( &ip, NULL);  
    
    ASSERT_THAT( VECTOR_SUCCESS == status );
    
    for( i = 0; i < SIZE; ++i)
    {
    	ASSERT_THAT( item[SIZE -1 -i] == *testVar[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- VectorGet --------------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorGet
 * Input 	Get(ptr = NULL) --> Output VECTOR_UNINITIALIZED_ERROR
 */
TEST(VectorGet_CheckNull) 
	int item;
    VectorResult status;

    status = VectorGet(NULL, 0, (void**)&item);
    ASSERT_THAT( VECTOR_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check VectorGet for the first index
 * Input 	create(1,0) --> add(1) --> get(index = 0)
 */
TEST(VectorGet_CheckGetFirst)
    Vector* ip;
    int item = 555;
    int* testVar;
    VectorResult status;
    
    ip = VectorCreate(1, 0);
    
    VectorAppend(ip, &item);
    status = VectorGet(ip, 0, (void**)&testVar);
    
    VectorDestroy( &ip, NULL);  
    ASSERT_THAT( *testVar == item && VECTOR_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Out of Bounds at the end of vector for VectorGet
 * Input 	create(1,0) --> add(1) --> get(index = 2)
 */
TEST(VectorGet_OutOfBounds)
    Vector* ip;
    int item = 555;
    int* testVar;
    VectorResult status;
    
    ip = VectorCreate(1, 0);
    
    VectorAppend(ip, &item);
    status = VectorGet(ip, 1, (void**)&testVar);
    
    VectorDestroy( &ip, NULL);  
    ASSERT_THAT( INDEX_OUT_OF_BOUNDS_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check VectorGet for the each index
 * Input 	create(SIZE,0) --> add(SIZE) --> get(index = i)
 */
TEST(VectorGet_CheckGetAll)
    Vector* ip;
    int item[SIZE];
    int* testVar[SIZE];
    VectorResult status[SIZE];
    size_t i;
    
    ip = VectorCreate(SIZE, 0);
    InsertSortedValues(ip, item, SIZE, 1, 0);
    
    for(i = 0; i < SIZE; ++i)
    {
    	status[i] = VectorGet(ip, i, (void**)&testVar[i]);
    }
    
    VectorDestroy( &ip, NULL);
    
    for(i = 0; i < SIZE; ++i)
    {
    	ASSERT_THAT( *testVar[i] == item[i] && VECTOR_SUCCESS == status[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- VectorSet --------------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorSet
 * Input 	Get(ptr = NULL) --> Output VECTOR_UNINITIALIZED_ERROR
 */
TEST(VectorSet_CheckNull) 
	int item = 555;
    VectorResult status;

    status = VectorSet(NULL, 0, (void*)&item);
    ASSERT_THAT( VECTOR_UNINITIALIZED_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check Out of Bounds at the end of vector for VectorSet
 * Input 	create(1,0) --> add(1) --> get(index = 2)
 */
TEST(VectorSet_OutOfBounds)
    Vector* ip;
    int item = 555;
    int item2 = 444;
    VectorResult status;
    
    ip = VectorCreate(1, 0);
    
    VectorAppend(ip, &item);
    status = VectorSet(ip, 1, (void*)&item2);
    
    VectorDestroy( &ip, NULL);  
    ASSERT_THAT( INDEX_OUT_OF_BOUNDS_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check regular case for VectorSet- insert then change and
 * 			check it was change
 * Input 	create(1,0) --> add(1) --> set(index = 0) --> get(index = 0)
 */
TEST(VectorSet_CheckRegular)
    Vector* ip;
    int item = 555;
    int item2 = 444;
    int* testVar;
    VectorResult status;
    
    ip = VectorCreate(1, 0);
    
    VectorAppend(ip, &item);
    status = VectorSet(ip, 0, (void*)&item2);
    status = VectorGet(ip, 0, (void**)&testVar);
    
    VectorDestroy( &ip, NULL);  
    ASSERT_THAT( VECTOR_SUCCESS == status && *testVar == item2);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check VectorSet for the each index
 * Input 	create(SIZE,0) --> add(SIZE) --> set(index = i) --> get(index = i)
 */
TEST(VectorSet_CheckSetAll)
    Vector* ip;
    int item[SIZE];
    int item2 = 50;
    int* testVar[SIZE];
    VectorResult status[SIZE];
    size_t i;
    
    ip = VectorCreate(SIZE, 0);
    InsertSortedValues(ip, item, SIZE, 1, 0);
    
    for(i = 0; i < SIZE; ++i)
    {
    	status[i] = VectorSet(ip, i, (void*)&item2);
    }
    
    for(i = 0; i < SIZE; ++i)
    {
    	VectorGet(ip, i, (void**)&testVar[i]);
    }
    
    VectorDestroy( &ip, NULL);
    
    for(i = 0; i < SIZE; ++i)
    {
    	ASSERT_THAT( *testVar[i] == item2 && VECTOR_SUCCESS == status[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- VectorSize -------------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorSize
 * Input 	size(ptr = NULL) --> Output 0
 */
TEST(VectorSize_CheckNull) 
    size_t result;

    result = VectorSize(NULL);
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function VectorSize
 * Input 	size(vec with SIZE elements) --> Output SIZE
 */
TEST(VectorSize_CheckRegular) 
    size_t result;
    Vector* ip;
    int item[SIZE];
    
    ip = VectorCreate(SIZE, 0);
    InsertRandValues(ip, item, SIZE, MAX_RAND_VALUE);

    result = VectorSize(ip);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( SIZE == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function VectorSize
 * Input 	size(size, element) --> Output element
 */
TEST(VectorSize_CheckCorrectElement)
    size_t result;
    Vector* ip;
    int item[SIZE - 1];
    
    ip = VectorCreate(SIZE, 0);
    InsertRandValues(ip, item, SIZE - 1, MAX_RAND_VALUE);

    result = VectorSize(ip);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( (SIZE - 1) == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- VectorCapacity -----------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorCapacity
 * Input 	Capacity(ptr = NULL) --> Output 0
 */
TEST(VectorCapacity_CheckNull) 
    size_t result;

    result = VectorCapacity(NULL);
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function VectorCapacity
 * Input 	Capacity(vec at the size of SIZE) --> Output SIZE
 */
TEST(VectorCapacity_CheckBase) 
    size_t result;
    Vector* ip;
    int item[SIZE];
    
    ip = VectorCreate(SIZE, 0);
    InsertRandValues(ip, item, SIZE, MAX_RAND_VALUE);

    result = VectorCapacity(ip);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( SIZE == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function VectorCapacity with realloc
 * Input 	Capacity(size, element) --> Output element
 */
TEST(VectorCapacity_CheckAfterRealloc) 
    size_t result;
    Vector* ip;
    int item[SIZE + 5];
    
    ip = VectorCreate(SIZE, 5);
    InsertRandValues(ip, item, SIZE + 5, MAX_RAND_VALUE);

    result = VectorCapacity(ip);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( (SIZE + 5) == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check the return value on function VectorCapacity with realloc
 * Input 	Capacity(size, element) --> Output element
 */
TEST(VectorCapacity_CheckAfterRealloc2) 
    size_t result;
    Vector* ip;
    int item[SIZE + 5];
    
    ip = VectorCreate(SIZE, 7);
    InsertRandValues(ip, item, SIZE + 5, MAX_RAND_VALUE);

    result = VectorCapacity(ip);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( (SIZE + 7) == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- VectorForEach -----------------------------*/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorForEach
 * Input 	ForEach(ptr = NULL) --> Output 0
 */
TEST(VectorForEach_CheckNull) 
    size_t result;
	int newValue = 50;
	
    result = VectorForEach(NULL , ChangeValueAction, &newValue);
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorForEach
 * Input 	ForEach(action = NULL) --> Output 0
 */
TEST(VectorForEach_CheckActionNull) 
    size_t result;
	int newValue = 50;
	Vector* ip;
	
	ip = VectorCreate(SIZE, 0);
    result = VectorForEach(ip , NULL, &newValue);
    
    VectorDestroy( &ip, NULL);
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check NULL on vector in VectorForEach
 * Input 	ForEach(action = NULL) --> Output result = SIZE && each value == 50
 */
TEST(VectorForEach_CheckRegular) 
    size_t result;
    int item[SIZE];
    int* retValue[SIZE];
	int newValue = 50;
	Vector* ip;
    size_t i;
	
	ip = VectorCreate(SIZE, 0);
	InsertSortedValues(ip, item, SIZE, 1, 0);
    result = VectorForEach(ip , ChangeValueAction, &newValue);
    
    for(i = 0; i < SIZE; ++i)
    {
    	VectorGet(ip, i, (void**)&retValue[i]);
    }
    
    VectorDestroy( &ip, NULL);
    
    for(i = 0; i < SIZE; ++i)
    {
    	ASSERT_THAT( *retValue[i] == newValue );
    }
    
    ASSERT_THAT( SIZE == result );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests SET ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Test Generic Vector Module)
	PRINT(VectorCreate_CheckNoSize)
	PRINT(VectorCreate_CheckNoIncSize)
	PRINT(VectorCreate_CheckRegular)  
	PRINT(VectorCreate_NoElements)

	PRINT(VectorDestroy_DoubleFree)

	PRINT(VectorAppend_CheckNull)
	PRINT(VectorAppend_CheckItemNull)
	PRINT(VectorAppend_Overflow)
	PRINT(VectorAppend_Realloc)
	PRINT(VectorAppend_ReallocFailed)
	PRINT(VectorAppend_Regular)

	PRINT(VectorRemove_CheckNull) 
	PRINT(VectorRemove_CheckItemNull)
	PRINT(VectorRemove_CheckUnderflow)
	PRINT(VectorRemove_DicreseRealloc)
	PRINT(VectorRemove_IntRegular)
	PRINT(VectorRemove_CharRegular)
	PRINT(VectorRemove_DoubleRegular)
	PRINT(VectorRemove_CheckFull)
	
	PRINT(VectorGet_CheckNull)
	PRINT(VectorGet_CheckGetFirst)
	PRINT(VectorGet_OutOfBounds)
	PRINT(VectorGet_CheckGetAll)
	
	PRINT(VectorSet_CheckNull)
	PRINT(VectorSet_OutOfBounds)
	PRINT(VectorSet_CheckRegular)
	PRINT(VectorSet_CheckSetAll)
	
	PRINT(VectorSize_CheckNull) 
	PRINT(VectorSize_CheckRegular) 
	PRINT(VectorSize_CheckCorrectElement)
	
	PRINT(VectorCapacity_CheckNull) 
	PRINT(VectorCapacity_CheckBase)
	PRINT(VectorCapacity_CheckAfterRealloc)
	PRINT(VectorCapacity_CheckAfterRealloc2)
	
	PRINT(VectorForEach_CheckNull)
	PRINT(VectorForEach_CheckActionNull)
	PRINT(VectorForEach_CheckRegular)
END_SET
/*----------------------------------------------------------------------------*/




/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/* 
 * @brief 	Function that check cases for null for createVector function
 *
 * @param   _size       = Initial capacity
 * @param   _incSize	= Vector will grow or shrink on demand by this size 
 *
 * Input 	create(Y,X) --> Output is NOT NULL for all cases exspet X==Y==0
 */
static Vector* checkNull(size_t _size, size_t _incSize)
{
    Vector* ip; 
    
    ip = VectorCreate(_size, _incSize);

    return ip;        
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to vector values in sort order 
 *
 * @param   _vec        = The address of the the source vector
 * @param   _array		= Pointer to  the elements neeeded to insert to vector 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 *
 * @return   void
*/
static VectorResult InsertSortedValues(Vector* _vec, int* _array ,size_t _nElements, int _step, int _minValue)
{
    VectorResult status;
    size_t i;
    int value = _minValue;
    
    for( i = 0;  i < _nElements; ++i )
    {
    	_array[i] = value;
        status = VectorAppend(_vec, &_array[i]);
        if(VECTOR_SUCCESS != status)
        {
        	return status;
        }
        value += _step;
    }
    
    return VECTOR_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to vector random values 
 *
 * @param   _vec        = The address of the the source vector
 * @param   _array		= Pointer to  the elements neeeded to insert to vector 
 * @param   _nElements  = The number of elements to insert
 * @param   _maxValue   = The max value the rand() function can prduce, the max value in the vector
 *
 * @return   void
*/
static VectorResult InsertRandValues(Vector* _vec, int* _array, size_t _nElements, int _maxValue)
{
    VectorResult status;
    size_t i;
    time_t t;
    int value;
    
    srand((unsigned) time(&t)); 
    value = rand() % _maxValue;
     
    for(i = 0; i < _nElements; i++)
    {
    	_array[i] = value;
        status = VectorAppend(_vec, &_array[i]);
        if(VECTOR_SUCCESS != status)
        {
        	return status;
        }
        value = rand() % _maxValue;
    }
    
    return VECTOR_SUCCESS;   
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that change all variables under index 100 to value of context 
 *
 * @param   _element    = Pointer to  the element
 * @param   _index		= The index of that element in the vector 
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Countinue loop for all elements
*/
static int ChangeValueAction(void* _element, size_t _index, void* _context)
{
	if(100 > _index)
	{
		*(int*)_element = *(int*)_context;
	}
	
	return -1;
}
/*----------------------------------------------------------------------------*/
