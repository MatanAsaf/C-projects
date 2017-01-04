/** 
 *  @file 		tests.c
 *  @brief 		Create a set of test for Generic Double Linked List data structure
 * 
 *  @details 	The API stores pointer to user provided elements of generic type.
 * 				The List is heap allocated and can grow and shrink on demand.
 *				Implemented as double linked list using head and tail sentinels.
 *  			Nodes are allocated from heap an store pointer to user proveded element.
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

#include "list.h"		/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h> 		/* for printf */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <time.h> 		/* for time_t */

#define SIZE (10) 		/* SIZE = The size of the vector (num of element) in each test */
#define MAX_RAND_VALUE (50) /* MAX_RAND_VALUE = The max value the function rand() can produce */
#define DEBUG (0)



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
void ElementDestroy(void* _item);
/*----------------------------------------------------------------------------*/





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


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that change all variables under index 100 to value of context 
 * 
 * @param   element    	= Pointer to  the element
 * @param   index		= The index of that element in the vector 
 * @param   context  	= The new value of the element
 *
 * @return  -1 			= Countinue loop for all elements
*/
int	ChangeValueAction(void* _element, size_t _index, void* _context);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*------------------------------- ListPushHead -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListPushHead_CheckNull) 
    ListResult result;
    int item = 2;

    result = ListPushHead(NULL, (void*)&item);
    ASSERT_THAT( LIST_UNINITIALIZED_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPushHead_CheckItemNull) 
    ListResult result;
    List* ip;
	
	ip = ListCreate();
    result = ListPushHead(ip, NULL);
    
    ListDestroy(&ip, NULL);
    ASSERT_THAT( LIST_NULL_ELEMENT_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListPushTail -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListPushTail_CheckNull) 
    ListResult result;
    int item = 2;

    result = ListPushTail(NULL, (void*)&item);
    ASSERT_THAT( LIST_UNINITIALIZED_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPushTail_CheckItemNull) 
    ListResult result;
    List* ip;
	
	ip = ListCreate();
    result = ListPushTail(ip, NULL);
    
    ListDestroy(&ip, NULL);
    ASSERT_THAT( LIST_NULL_ELEMENT_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListPopHead --------------------------------*/
/*----------------------------------------------------------------------------*/

TEST(ListPopHead_CheckNull) 
    ListResult result;
    int* item;

    result = ListPopHead(NULL, (void**)&item);
    ASSERT_THAT( LIST_UNINITIALIZED_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

TEST(ListPopHead_CheckItemNull) 
    ListResult result;
    List* ip;
	
	ip = ListCreate();
    result = ListPopHead(ip, NULL);
    
    ListDestroy(&ip, NULL);
    ASSERT_THAT( LIST_NULL_ELEMENT_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPopHead_CheckPopHead_1Item) 
    ListResult result[2];
    List* ip;
    int item = 2;
    int* retVal;
	
	ip = ListCreate();
	result[0] = ListPushHead(ip, (void*)&item);
    result[1] = ListPopHead(ip, (void**)&retVal);
    
    ListDestroy(&ip, NULL);
    ASSERT_THAT( LIST_SUCCESS == result[0] && LIST_SUCCESS == result[1] && *retVal == item );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPopHead_CheckPopHead_AllItems) 
    ListResult result[SIZE];
    List* ip;
    int item[SIZE];
    int* retVal[SIZE];
    size_t i;
	
	ip = ListCreate();
	InsertSortedValues(ip, item ,SIZE, 1, 0);
	for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListPopHead(ip, (void**)&retVal[i]);
	}
    
    ListDestroy(&ip, NULL);
    for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( LIST_SUCCESS == result[i] && *retVal[i] == item[SIZE - i - 1] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListPopTail --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListPopTail_CheckNull) 
    ListResult result;
    int item = 2;

    result = ListPopTail(NULL, (void**)&item);
    ASSERT_THAT( LIST_UNINITIALIZED_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPopTail_CheckItemNull) 
    ListResult result;
    List* ip;
	
	ip = ListCreate();
    result = ListPopTail(ip, NULL);
    
    ListDestroy(&ip, NULL);
    ASSERT_THAT( LIST_NULL_ELEMENT_ERROR == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPopTail_CheckPopHead_1Item) 
    ListResult result[2];
    List* ip;
    int item = 2;
    int* retVal;
	
	ip = ListCreate();
	result[0] = ListPushTail(ip, (void*)&item);
    result[1] = ListPopTail(ip, (void**)&retVal);
    
    ListDestroy(&ip, NULL);
    ASSERT_THAT( LIST_SUCCESS == result[0] && LIST_SUCCESS == result[1] && *retVal == item );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPopTail_CheckPopHead_AllItems) 
    ListResult result[SIZE];
    List* ip;
    int item[SIZE];
    int* retVal[SIZE];
    size_t i;
	
	ip = ListCreate();
	InsertSortedValues(ip, item ,SIZE, 1, 0);
	for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListPopTail(ip, (void**)&retVal[i]);
	}
    
    ListDestroy(&ip, NULL);
    for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( LIST_SUCCESS == result[i] && *retVal[i] == item[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPopTail_CheckPopHead_AllItemsCombined) 
    ListResult result[SIZE];
    List* ip;
    int item[SIZE];
    int* retVal[SIZE];
    size_t i;
	
	ip = ListCreate();
	InsertSortedValues(ip, item ,SIZE, 1, 0);
	for(i = 0; i < (SIZE/2); ++i)
	{
		result[i] = ListPopHead(ip, (void**)&retVal[i]);
		result[SIZE -i -1] = ListPopTail(ip, (void**)&retVal[SIZE -i -1]);
	}
    
    ListDestroy(&ip, NULL);
    for(i = 1; i < SIZE; ++i)
	{
		ASSERT_THAT( LIST_SUCCESS == result[i] && *retVal[i-1] > *retVal[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPopTail_CheckPopHead_AllItemsCombinedReverse) 
    ListResult result[SIZE];
    List* ip;
    int item[SIZE];
    int* retVal[SIZE];
    size_t i;
	
	ip = ListCreate();
	InsertSortedValues(ip, item ,SIZE, 1, 0);
	for(i = 0; i < (SIZE/2); ++i)
	{
		result[i] = ListPopTail(ip, (void**)&retVal[i]);
		result[SIZE -i -1] = ListPopHead(ip, (void**)&retVal[SIZE -i -1]);
	}
    
    ListDestroy(&ip, NULL);
    for(i = 1; i < SIZE; ++i)
	{
		ASSERT_THAT( LIST_SUCCESS == result[i] && *retVal[i-1] < *retVal[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- ListSize ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListSize_CheckNull) 
    size_t result;

    result = ListSize(NULL);
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListSize_CheckCorrectReturn) 
    size_t result;
    List* ip;
    int item[SIZE];
    
    ip = ListCreate();
	InsertSortedValues(ip, item ,SIZE, 1, 0);
    result = ListSize(ip);
    
    ListDestroy(&ip, NULL);
    ASSERT_THAT( SIZE == result );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests SET ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Test Generic List Module)
	PRINT(ListPushHead_CheckNull)
	PRINT(ListPushHead_CheckItemNull)
	
	PRINT(ListPushTail_CheckNull)
	PRINT(ListPushTail_CheckItemNull)
	
	PRINT(ListPopHead_CheckNull) 
	PRINT(ListPopHead_CheckItemNull)
	PRINT(ListPopHead_CheckPopHead_1Item) 
	PRINT(ListPopHead_CheckPopHead_AllItems) 
	
	PRINT(ListPopTail_CheckNull)
	PRINT(ListPopTail_CheckItemNull)
	PRINT(ListPopTail_CheckPopHead_1Item) 
	PRINT(ListPopTail_CheckPopHead_AllItems) 
	PRINT(ListPopTail_CheckPopHead_AllItemsCombined)
	PRINT(ListPopTail_CheckPopHead_AllItemsCombinedReverse) 
	
	PRINT(ListSize_CheckNull)
	PRINT(ListSize_CheckCorrectReturn) 
END_SET
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
void ElementDestroy(void* _item)
{
	if( NULL != _item )
	{
		free(_item);
	}
	else
	{
		#if DEBUG
		printf("Element Destroy failed.");
		#endif
	}
}
/*----------------------------------------------------------------------------*/


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


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that change all variables under index 100 to value of context 
 * 
 * @param   element    	= Pointer to  the element
 * @param   index		= The index of that element in the vector 
 * @param   context  	= The new value of the element
 *
 * @return  -1 			= Countinue loop for all elements
*/
int	ChangeValueAction(void* _element, size_t _index, void* _context)
{
	if(100 > _index)
	{
		*(int*)_element = *(int*)_context;
	}
	
	return -1;
}
/*----------------------------------------------------------------------------*/
