/** 
 *  @file 		tests.c
 *  @brief 		Create a set of test for Generic Double Linked List Iterator data structure
 * 
 *  @details 	Implemented as list of action that can be done on double linked list
 *  			without need to know how the double linked list data structure work.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2016-12-28    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "listItr.h"	/* header file */
#include "list.h"		/* list header */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h> 		/* for printf */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <time.h> 		/* for time_t */

#define SIZE (10) 		/* SIZE = The size of the vector (num of element) in each test */
#define MAX_RAND_VALUE (50) /* MAX_RAND_VALUE = The max value the function rand() can produce */
#define DEBUG (0)



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to List values in sort order 
 *
 * @param   list       	= The address of the the source List
 * @param   array		= Pointer to  the elements neeeded to insert to List 
 * @param   nElements  	= The number of elements to insert
 * @param   step       	= The range value between each element 
 * @param   minValue   	= The value of the first element
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list is not initialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If _item is NULL
 * @retval  LIST_ALLOCATION_ERROR       =   On memory allocation failure
*/
ListResult InsertSortedValues(List* _list, int* _array ,size_t _nElements, int _step, int _minValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to List random values 
 *
 * @param   list       	= The address of the the source List
 * @param   array		= Pointer to  the elements neeeded to insert to List 
 * @param   nElements  	= The number of elements to insert
 * @param   maxValue   	= The max value the rand() function can prduce, the max value in the List
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list is not initialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If _item is NULL
 * @retval  LIST_ALLOCATION_ERROR       =   On memory allocation failure
*/
ListResult InsertRandValues(List* _list, int* _array, size_t _nElements, int _maxValue);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*------------------------------- ListItrBegin -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrBegin_CheckNull)
    ASSERT_THAT( NULL == ListItrBegin(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrBegin_CheckAll)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr result[SIZE];
	size_t i;
	
	for(i = 0; i < SIZE; ++i)
	{
		var[i] = rand() % MAX_RAND_VALUE;
		ListPushTail(ip, (void*)&var[i]);
		result[i] = ListItrBegin(ip);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
    	ASSERT_THAT( result[i] == result[i + 1] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- ListItrEnd --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrEnd_CheckNull)
    ASSERT_THAT( NULL == ListItrEnd(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrEnd_CheckAll)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr result[SIZE];
	size_t i;
	
	for(i = 0; i < SIZE; ++i)
	{
		var[i] = rand() % MAX_RAND_VALUE;
		ListPushHead(ip, (void*)&var[i]);
		result[i] = ListItrEnd(ip);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
    	ASSERT_THAT( result[i] == result[i + 1] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItrEquals ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrEquals_CheckNull_Param1)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr itr;
	int result;
	
	InsertRandValues(ip, var, SIZE, SIZE);
	itr = ListItrBegin(ip);
	
	result = ListItrEquals(NULL, itr);
	
	ListDestroy(&ip, NULL);
	
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrEquals_CheckNull_Param2)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr itr;
	int result;
	
	InsertRandValues(ip, var, SIZE, SIZE);
	itr = ListItrBegin(ip);
	
	result = ListItrEquals(itr, NULL);
	
	ListDestroy(&ip, NULL);
	
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrEquals_CheckNull_TwoParam)
    ASSERT_THAT( 1 == ListItrEquals(NULL, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrEquals_CheckBeginIsEnd_EmptyList)
	List* ip = ListCreate();
	ListItr result[2];

	result[0] = ListItrBegin(ip);
	result[1] = ListItrEnd(ip);
	
	ListDestroy(&ip, NULL);
	
	ASSERT_THAT( result[0] == result[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrEquals_CheckBeginIsEnd_FullList)
	List* ip = ListCreate();
	ListItr result[2];
	int var[SIZE];

	InsertRandValues(ip, var, SIZE, SIZE);
	result[0] = ListItrBegin(ip);
	result[1] = ListItrEnd(ip);
	
	ListDestroy(&ip, NULL);
	
	ASSERT_THAT( result[0] != result[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItrNext --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrNext_CheckNull)
    ASSERT_THAT( NULL == ListItrNext(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrNext_CheckNextIsEnd)
	List* ip = ListCreate();
	ListItr nextItr;
	ListItr endItr;
	int var;

	var = rand() % MAX_RAND_VALUE;
	ListPushHead(ip, (void*)&var);
	nextItr = ListItrBegin(ip);
	endItr = ListItrEnd(ip);
	
	nextItr = ListItrNext(nextItr);
	
	ListDestroy(&ip, NULL);
	
	ASSERT_THAT( nextItr == endItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItrPrev --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrPrev_CheckNull)
    ASSERT_THAT( NULL == ListItrPrev(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrPrev_CheckPrevIsBegin)
	List* ip = ListCreate();
	ListItr prevItr;
	ListItr beginItr;
	int var;

	var = rand() % MAX_RAND_VALUE;
	ListPushHead(ip, (void*)&var);
	beginItr = ListItrBegin(ip);
	prevItr = ListItrEnd(ip);
	
	prevItr = ListItrPrev(prevItr);
	
	ListDestroy(&ip, NULL);
	
	ASSERT_THAT( prevItr == beginItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- ListItrGet --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrGet_CheckNull)
    ASSERT_THAT( NULL == ListItrGet(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrGet_CheckAll)
	List* ip = ListCreate();
	int var[SIZE];
	int* result[SIZE];
	ListItr currentItr;
	size_t i;
	
	InsertSortedValues(ip, var ,SIZE, -1, SIZE - 1);
	currentItr = ListItrBegin(ip);
	
	for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListItrGet(currentItr);
		currentItr = ListItrNext(currentItr);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( i == *(int*)result[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- ListItrSet --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrSet_CheckNull)
	int retData = 5;
	
    ASSERT_THAT( NULL == ListItrSet(NULL, (void*)retData) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrSet_CheckNull_Item)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr itr;
	ListItr result;
	
	InsertRandValues(ip, var, SIZE, SIZE);
	itr = ListItrBegin(ip);
	
	result = ListItrSet(itr, NULL);
	
	ListDestroy(&ip, NULL);
	
    ASSERT_THAT( NULL == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrSet_CheckAll)
	List* ip = ListCreate();
	int var[SIZE];
	int newValue = 999;
	int* orignalValue[SIZE];
	int* changeValue[SIZE];
	ListItr currentItr;
	size_t i;
	
	InsertSortedValues(ip, var ,SIZE, -1, SIZE - 1);
	currentItr = ListItrBegin(ip);
	
	for(i = 0; i < SIZE; ++i)
	{
		orignalValue[i] = ListItrSet(currentItr, (void*)&newValue);
		changeValue[i] = ListItrGet(currentItr);
		currentItr = ListItrNext(currentItr);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( i == *(int*)orignalValue[i] && newValue == *(int*)changeValue[i]);
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------- ListItrInsertBefore ---------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrInsertBefore_CheckNull)
	int retData = 5;
	
    ASSERT_THAT( NULL == ListItrInsertBefore(NULL, (void*)retData) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrInsertBefore_CheckNull_Item)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr itr;
	ListItr result;
	
	InsertRandValues(ip, var, SIZE, SIZE);
	itr = ListItrBegin(ip);
	
	result = ListItrInsertBefore(itr, NULL);
	
	ListDestroy(&ip, NULL);
	
    ASSERT_THAT( NULL == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrInsertBefore_Check_InsertBeforeBegin)
	List* ip = ListCreate();
	int arr[SIZE];
	int newValue[SIZE];
	int* allValue[SIZE * 2];
	ListItr currentItr;
	ListItr orignalItrStart;
	size_t i;
	size_t endLoop;
	
	InsertSortedValues(ip, arr ,SIZE, -1, SIZE * 2 );
	currentItr = ListItrBegin(ip);
	orignalItrStart = currentItr;
	
	for(i = SIZE; i > 0; --i)
	{
		newValue[i] = (int)i;
		currentItr = ListItrInsertBefore(currentItr, (void*)&newValue[i]);
		allValue[i] = ListItrGet(currentItr);
	}
	
	endLoop = (SIZE * 2) + 1;
	for(i = (SIZE + 1); i < endLoop; ++i)
	{
		allValue[i] = ListItrGet(orignalItrStart);
		orignalItrStart = ListItrNext(orignalItrStart);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 1; i < endLoop; ++i)
	{
    	ASSERT_THAT( i == *(int*)allValue[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItrRemove ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItrRemove_CheckNull)
    ASSERT_THAT( NULL == ListItrRemove(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrRemove_Check_Data)
	List* ip = ListCreate();
	int arr[SIZE];
	int* value[SIZE];
	ListItr currentItr;
	size_t i;
	
	InsertSortedValues(ip, arr ,SIZE, -1, SIZE - 1 );
	currentItr = ListItrBegin(ip);
	
	for(i = 0; i < SIZE; ++i)
	{
		value[i] = ListItrRemove(currentItr);
		currentItr = ListItrBegin(ip);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( i == *(int*)value[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItrRemove_Check_ItrPointers)
	List* ip = ListCreate();
	int arr[SIZE];
	ListItr cmpItr[SIZE];
	ListItr currentItr[SIZE];
	size_t i;
	
	InsertSortedValues(ip, arr ,SIZE, -1, SIZE - 1 );
	currentItr[0] = ListItrBegin(ip);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		cmpItr[i + 1] = ListItrNext(currentItr[i]);
		ListItrRemove(currentItr[i]);
		currentItr[i + 1] = ListItrBegin(ip);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 1; i < SIZE; ++i)
	{
    	ASSERT_THAT( cmpItr[i] == currentItr[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/********************************** Tests SET *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Generic Double Linked List Iterator)
	PRINT(ListItrBegin_CheckNull)
	PRINT(ListItrBegin_CheckAll)
	
	PRINT(ListItrEnd_CheckNull)
	PRINT(ListItrEnd_CheckAll)
	
	PRINT(ListItrEquals_CheckNull_Param1)
	PRINT(ListItrEquals_CheckNull_Param2)
	PRINT(ListItrEquals_CheckNull_TwoParam)
	PRINT(ListItrEquals_CheckBeginIsEnd_EmptyList)
	PRINT(ListItrEquals_CheckBeginIsEnd_FullList)
	
	PRINT(ListItrNext_CheckNull)
	PRINT(ListItrNext_CheckNextIsEnd)
	
	PRINT(ListItrPrev_CheckNull)
	PRINT(ListItrPrev_CheckPrevIsBegin)
	
	PRINT(ListItrGet_CheckNull)
	PRINT(ListItrGet_CheckAll)
	
	PRINT(ListItrSet_CheckNull)
	PRINT(ListItrSet_CheckNull_Item)
	PRINT(ListItrSet_CheckAll)
	
	PRINT(ListItrInsertBefore_CheckNull)
	PRINT(ListItrInsertBefore_CheckNull_Item)
	PRINT(ListItrInsertBefore_Check_InsertBeforeBegin)
	
	PRINT(ListItrRemove_CheckNull)
	PRINT(ListItrRemove_Check_Data)
	PRINT(ListItrRemove_Check_ItrPointers)
END_SET
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to List values in sort order 
 *
 * @param   list       	= The address of the the source List
 * @param   array		= Pointer to  the elements neeeded to insert to List 
 * @param   nElements  	= The number of elements to insert
 * @param   step       	= The range value between each element 
 * @param   minValue   	= The value of the first element
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list is not initialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If _item is NULL
 * @retval  LIST_ALLOCATION_ERROR       =   On memory allocation failure
*/
ListResult InsertSortedValues(List* _list, int* _array ,size_t _nElements, int _step, int _minValue)
{
    ListResult status;
    size_t i;
    int value = _minValue;
    
    for( i = 0;  i < _nElements; ++i )
    {
    	_array[i] = value;
        status = ListPushHead(_list, &_array[i]);
        if(LIST_SUCCESS != status)
        {
        	return status;
        }
        value += _step;
    }
    
    return LIST_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to List random values 
 *
 * @param   list       	= The address of the the source List
 * @param   array		= Pointer to  the elements neeeded to insert to List 
 * @param   nElements  	= The number of elements to insert
 * @param   maxValue   	= The max value the rand() function can prduce, the max value in the List
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list is not initialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If _item is NULL
 * @retval  LIST_ALLOCATION_ERROR       =   On memory allocation failure
*/
ListResult InsertRandValues(List* _list, int* _array, size_t _nElements, int _maxValue)
{
    ListResult status;
    size_t i;
    time_t t;
    
    srand((unsigned) time(&t)); 
     
    for(i = 0; i < _nElements; i++)
    {
    	_array[i] = rand() % _maxValue;
        status = ListPushHead(_list, &_array[i]);
        if(LIST_SUCCESS != status)
        {
        	return status;
        }
    }
    
    return LIST_SUCCESS;   
}
/*----------------------------------------------------------------------------*/
