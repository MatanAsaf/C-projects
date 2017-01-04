/** 
 *  @file 		tests.c
 *  @brief 		Create a set of test for Generic Double Linked List Functions data structure
 * 
 *  @details 	Implemented as list of functions that can be done on double linked list iterator
 *  			without need to know how the double linked list data structure work.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2016-12-29    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "listFunctions.h" 	/* header file */ 
#include "list.h"			/* list header file */
#include "listItr.h"		/* listItr header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h> 			/* for printf */
#include <stdlib.h> 		/* for size_t & srand & malloc */
#include <time.h> 			/* for time_t */

#define SIZE (100) /* SIZE = The size of the vector (num of element) in each test */
#define MAX_RAND_VALUE (50) /* MAX_RAND_VALUE = The max value the function rand() can produce */
#define DEBUG 0



/*************************** Declaration of function **************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a data ==  iterator b data
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (-1) 
 *
 * @retval	0		=	if _a == _b
 * @retval	-1		=	if _a != _b
 */
static int FoundData(void* _a, void* _b);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to List values in sort order 
 *
 * @param   list       	= The address of the the source List
 * @param   array		= Pointer to  the elements needed to insert to List 
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
 * @param   array		= Pointer to  the elements needed to insert to List 
 * @param   nElements  	= The number of elements to insert
 * @param   maxValue   	= The max value the rand() function can produce, the max value in the List
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
 * @param   _element    = Pointer to  the element 
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Continue loop for all elements
*/
int	ChangeValueAction(void* _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a data <  iterator b data
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (-1) 
 *
 * @retval	0		=	if _a < _b
 * @retval	-1		=	if _a >= _b
 */
static int CompareData(void* _a, void* _b);
/*----------------------------------------------------------------------------*/





/******************************* Tests functions ******************************/
/*----------------------------- ListItr_FindFirst ----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_FindFirst_CheckNull_Begin)
    List* myList = ListCreate();
    ListItr endItr = ListItrEnd(myList);
    int item = 555;
    ListItr retVal = ListItr_FindFirst(NULL, endItr, FoundData, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_FindFirst_CheckNull_End)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    int item = 555;
    ListItr retVal = ListItr_FindFirst(beginItr, NULL, FoundData, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_FindFirst_CheckNull_Function)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    ListItr endItr = ListItrEnd(myList);
    int item = 555;
    ListItr retVal = ListItr_FindFirst(beginItr, endItr, NULL, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_FindFirst_CheckCase_BeginIsFirst)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr beginItr[SIZE];
	ListItr currentFirstItr[SIZE];
	ListItr endItr;
	size_t i;
	
	endItr = ListItrEnd(ip);
	
	for(i = 0; i < SIZE; ++i)
	{
		var[i] = rand() % MAX_RAND_VALUE;
		ListPushHead(ip, (void*)&var[i]);
		beginItr[i] = ListItrBegin(ip);
		currentFirstItr[i] = ListItr_FindFirst(beginItr[i], endItr, FoundData, beginItr[i]);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( beginItr[i] == currentFirstItr[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_FindFirst_CheckCase_FirstDoesNotChange)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr beginItr[SIZE];
	ListItr currentFirstItr[SIZE];
	ListItr endItr;
	size_t i;
	
	endItr = ListItrEnd(ip);
	
	for(i = 0; i < SIZE; ++i)
	{
		var[i] = rand() % MAX_RAND_VALUE;
		ListPushTail(ip, (void*)&var[i]);
		beginItr[i] = ListItrBegin(ip);
		currentFirstItr[i] = ListItr_FindFirst(beginItr[i], endItr, FoundData, beginItr[i]);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
    	ASSERT_THAT( beginItr[i] == beginItr[i + 1] && currentFirstItr[i] == currentFirstItr[i + 1] && beginItr[i] == currentFirstItr[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_FindFirst_CheckCase_FoundCorrectFirst)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr beginItr;
	ListItr endItr;
	ListItr searchItr[SIZE];
	ListItr currentFirstItr[SIZE];
	size_t i;
	
	InsertSortedValues(ip, var ,SIZE, 1, 0);
	
	beginItr = ListItrBegin(ip);
	endItr = ListItrEnd(ip);
	searchItr[0] = endItr;
	
	for(i = 1; i < SIZE; ++i)
	{
		searchItr[i] = ListItrPrev(searchItr[i - 1]);
		currentFirstItr[i] = ListItr_FindFirst(beginItr, endItr, FoundData, searchItr[i]);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 1; i < SIZE; ++i)
	{
    	ASSERT_THAT( searchItr[i] == currentFirstItr[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------ ListItr_CountIf -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_CountIf_CheckNull_Begin)
    List* myList = ListCreate();
    ListItr endItr = ListItrEnd(myList);
    int item = 555;
    size_t retVal = ListItr_CountIf(NULL, endItr, FoundData, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_CountIf_CheckNull_End)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    int item = 555;
    size_t retVal = ListItr_CountIf(beginItr, NULL, FoundData, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_CountIf_CheckNull_Function)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    ListItr endItr = ListItrEnd(myList);
    int item = 555;
    size_t retVal = ListItr_CountIf(beginItr, endItr, NULL, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_CountIf_CheckCase_CountToBegin)
	List* ip = ListCreate();
	int arr[SIZE];
	ListItr beginItr;
	size_t result;
	ListItr endItr;
	
	InsertRandValues(ip, arr, SIZE, MAX_RAND_VALUE);
	beginItr = ListItrBegin(ip);
	endItr = ListItrEnd(ip);
		
	result = ListItr_CountIf(beginItr, endItr, FoundData, beginItr);
	
	ListDestroy(&ip, NULL);
	
    ASSERT_THAT( 1 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_CountIf_CheckCase_CountToEnd)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr beginItr;
	size_t result[SIZE];
	ListItr endItr;
	ListItr lastItr;
	size_t i;
	
	var[0] = 0;
	ListPushHead(ip, (void*)&var[0]);
	endItr = ListItrEnd(ip);
	lastItr = ListItrPrev(endItr);
	
	for(i = 1; i < SIZE; ++i)
	{
		beginItr = ListItrBegin(ip);
		result[i - 1] = ListItr_CountIf(beginItr, endItr, FoundData, lastItr);
		var[i] = (int)i;
		ListPushHead(ip, (void*)&var[i]);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
    	ASSERT_THAT( (i + 1) == result[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_CountIf_CheckCase_OutOfRange)
	List* ip = ListCreate();
	int arr[SIZE];
	ListItr beginItr;
	size_t result;
	ListItr endItr;
	
	InsertSortedValues(ip, arr, SIZE, 1, 0);
	beginItr = ListItrBegin(ip);
	endItr = ListItrEnd(ip);
		
	result = ListItr_CountIf(ListItrNext(beginItr), endItr, FoundData, beginItr);
	
	ListDestroy(&ip, NULL);
	
    ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------ ListItr_ForEach -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_ForEach_CheckNull_Begin)
    List* myList = ListCreate();
    ListItr endItr = ListItrEnd(myList);
    int item = 555;
    ListItr retVal = ListItr_ForEach(NULL, endItr, ChangeValueAction, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_ForEach_CheckNull_End)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    int item = 555;
    ListItr retVal = ListItr_ForEach(beginItr, NULL, ChangeValueAction, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_ForEach_CheckNull_Function)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    ListItr endItr = ListItrEnd(myList);
    int item = 555;
    ListItr retVal = ListItr_ForEach(beginItr, endItr, NULL, &item);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_ForEach_CheckCase_ChangeEachValue)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr beginItr;
	ListItr stopedItr;
	ListItr endItr;
	int newValue = 999;
	int* result[SIZE];
	size_t i;
	
	InsertRandValues(ip, var, SIZE, MAX_RAND_VALUE);
	endItr = ListItrEnd(ip);
	beginItr = ListItrBegin(ip);
	stopedItr = ListItr_ForEach(beginItr, endItr, ChangeValueAction, (void*)&newValue);
	
	for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListItrGet(beginItr);
		beginItr = ListItrNext(beginItr);
	}
	
	ListDestroy(&ip, NULL);
	
	ASSERT_THAT( stopedItr == endItr );
	
	for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( 999 == *result[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItr_Sort -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_Sort_CheckAllSorted)
	List* ip = ListCreate();
	int var[SIZE];
	ListItr beginItr;
	ListItr endItr;
	int* result[SIZE];
	size_t i;
	
	InsertRandValues(ip, var, SIZE, MAX_RAND_VALUE);
	endItr = ListItrEnd(ip);
	beginItr = ListItrBegin(ip);
	ListItr_Sort(beginItr, endItr, CompareData);
	
	for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListItrGet(beginItr);
		beginItr = ListItrNext(beginItr);
	}
	
	ListDestroy(&ip, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
    	ASSERT_THAT( *result[i] <= *result[i + 1] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItr_Splice -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_Splice_CheckNull_Des)
    List* myList = ListCreate();
	ListItr beginItr = ListItrBegin(myList);
    ListItr endItr = ListItrEnd(myList);
    ListItr retVal = ListItr_Splice(NULL, beginItr, endItr);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Splice_CheckNull_Begin)
    List* myList = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
    ListItr endItr = ListItrEnd(myList);
    ListItr retVal = ListItr_Splice(desItr, NULL, endItr);
    
    ListDestroy(&myList, NULL);
    ListDestroy(&desList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Splice_CheckNull_End)
    List* myList = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
    ListItr beginItr = ListItrBegin(myList);
    ListItr retVal = ListItr_Splice(desItr, beginItr, NULL);
    
    ListDestroy(&myList, NULL);
    ListDestroy(&desList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Splice_Check_InsertToDes)
    List* ip = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrEnd(desList);
    ListItr beginItr;
    ListItr endItr;
    int* result[SIZE];
    int arr[SIZE];
    size_t i;
    
    InsertSortedValues(ip, arr, SIZE, -1, SIZE);
    beginItr = ListItrBegin(ip);
    endItr = ListItrEnd(ip);
    
    desItr = ListItr_Splice(desItr, beginItr, endItr);
    
    for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListItrGet(desItr);
		desItr = ListItrNext(desItr);
	}
	
	beginItr = ListItrBegin(ip);
    endItr = ListItrEnd(ip);
    
    ListDestroy(&ip, NULL);
    ListDestroy(&desList, NULL);
    
    for(i = 0; i < (SIZE - 1); ++i)
	{
    	ASSERT_THAT( (i + 1) == *result[i] );
    }
    
    ASSERT_THAT( beginItr == endItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItr_Merge ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_Merge_CheckNull_Des)
    List* myList1 = ListCreate();
    List* myList2 = ListCreate();
	ListItr beginItr1 = ListItrBegin(myList1);
    ListItr endItr1 = ListItrEnd(myList1);
    ListItr beginItr2 = ListItrBegin(myList2);
    ListItr endItr2 = ListItrEnd(myList2);
    ListItr retVal = ListItr_Merge(NULL, beginItr1, endItr1, beginItr2, endItr2, CompareData);
    
    ListDestroy(&myList1, NULL);
    ListDestroy(&myList2, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Merge_CheckNull_FirstBegin)
    List* myList1 = ListCreate();
    List* myList2 = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
    ListItr endItr1 = ListItrEnd(myList1);
    ListItr beginItr2 = ListItrBegin(myList2);
    ListItr endItr2 = ListItrEnd(myList2);
    ListItr retVal = ListItr_Merge(desItr, NULL, endItr1, beginItr2, endItr2, CompareData);
    
    ListDestroy(&myList1, NULL);
    ListDestroy(&myList2, NULL);
    ListDestroy(&desList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Merge_CheckNull_FirstEnd)
    List* myList1 = ListCreate();
    List* myList2 = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
	ListItr beginItr1 = ListItrBegin(myList1);
    ListItr beginItr2 = ListItrBegin(myList2);
    ListItr endItr2 = ListItrEnd(myList2);
    ListItr retVal = ListItr_Merge(desItr, beginItr1, NULL, beginItr2, endItr2, CompareData);
    
    ListDestroy(&myList1, NULL);
    ListDestroy(&myList2, NULL);
    ListDestroy(&desList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Merge_CheckNull_SecondBegin)
    List* myList1 = ListCreate();
    List* myList2 = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
	ListItr beginItr1 = ListItrBegin(myList1);
    ListItr endItr1 = ListItrEnd(myList1);
    ListItr endItr2 = ListItrEnd(myList2);
    ListItr retVal = ListItr_Merge(desItr, beginItr1, endItr1, NULL, endItr2, CompareData);
    
    ListDestroy(&myList1, NULL);
    ListDestroy(&myList2, NULL);
    ListDestroy(&desList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Merge_CheckNull_SecondEnd)
    List* myList1 = ListCreate();
    List* myList2 = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
	ListItr beginItr1 = ListItrBegin(myList1);
    ListItr endItr1 = ListItrEnd(myList1);
    ListItr beginItr2 = ListItrBegin(myList2);
    ListItr retVal = ListItr_Merge(desItr, beginItr1, endItr1, beginItr2, NULL, CompareData);
    
    ListDestroy(&myList1, NULL);
    ListDestroy(&myList2, NULL);
    ListDestroy(&desList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Merge_CheckNewList_NoSort)
    List* ip1 = ListCreate();
    List* ip2 = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
	ListItr beginItr1;
    ListItr endItr1;
    ListItr beginItr2;
    ListItr endItr2;
    int* result[SIZE * 2];
    int arr1[SIZE];
    int arr2[SIZE];
    size_t i;
    size_t endOfLoop = SIZE * 2;
    
    InsertSortedValues(ip1, arr1, SIZE, -1, SIZE - 1);
    beginItr1 = ListItrBegin(ip1);
    endItr1 = ListItrEnd(ip1);
    
    InsertSortedValues(ip2, arr2, SIZE, -1, (SIZE * 2) - 1);
    beginItr2 = ListItrBegin(ip2);
    endItr2 = ListItrEnd(ip2);
    
    desItr = ListItr_Merge(desItr, beginItr1, endItr1, beginItr2, endItr2, NULL);
    
    for(i = 0; i < endOfLoop; ++i)
	{
		result[i] = ListItrGet(desItr);
		desItr = ListItrNext(desItr);
	}
	
	beginItr1 = ListItrBegin(ip1);
    endItr1 = ListItrEnd(ip1);
	beginItr2 = ListItrBegin(ip2);
    endItr2 = ListItrEnd(ip2);
    
    ListDestroy(&ip1, NULL);
    ListDestroy(&ip2, NULL);
    ListDestroy(&desList, NULL);
    
    for(i = 0; i < endOfLoop; ++i)
	{
    	ASSERT_THAT( i == *result[i] );
    }
    
    ASSERT_THAT( beginItr1 == endItr1 && beginItr2 == endItr2 );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Merge_CheckNewList_WithSort)
    List* ip1 = ListCreate();
    List* ip2 = ListCreate();
    List* desList = ListCreate();
    ListItr desItr = ListItrBegin(desList);
	ListItr beginItr1;
    ListItr endItr1;
    ListItr beginItr2;
    ListItr endItr2;
    int* result[SIZE * 2];
    int arr1[SIZE];
    int arr2[SIZE];
    size_t i;
    size_t endOfLoop = SIZE * 2;
    
    InsertRandValues(ip1, arr1, SIZE, MAX_RAND_VALUE);
    beginItr1 = ListItrBegin(ip1);
    endItr1 = ListItrEnd(ip1);
    
    InsertRandValues(ip2, arr2, SIZE, MAX_RAND_VALUE);
    beginItr2 = ListItrBegin(ip2);
    endItr2 = ListItrEnd(ip2);
    
    desItr = ListItr_Merge(desItr, beginItr1, endItr1, beginItr2, endItr2, CompareData);
    
    for(i = 0; i < endOfLoop; ++i)
	{
		result[i] = ListItrGet(desItr);
		desItr = ListItrNext(desItr);
	}
	
	beginItr1 = ListItrBegin(ip1);
    endItr1 = ListItrEnd(ip1);
	beginItr2 = ListItrBegin(ip2);
    endItr2 = ListItrEnd(ip2);
    
    ListDestroy(&ip1, NULL);
    ListDestroy(&ip2, NULL);
    ListDestroy(&desList, NULL);
    
    for(i = 0; i < (endOfLoop - 1); ++i)
	{
    	ASSERT_THAT( *result[i] <= *result[i + 1] );
    }
    
    ASSERT_THAT( beginItr1 == endItr1 && beginItr2 == endItr2 );
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- ListItr_Cut -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_Cut_CheckNull_Begin)
    List* myList = ListCreate();
    ListItr endItr = ListItrEnd(myList);
    List* retVal = ListItr_Cut(NULL, endItr);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Cut_CheckNull_End)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    List* retVal = ListItr_Cut(beginItr, NULL);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Cut_CheckNewList)
    List* ip = ListCreate();
    ListItr beginItr;
    ListItr endItr;
    List* newList;
    ListItr newListBeginItr;
    int* result[SIZE];
    int arr[SIZE];
    size_t i;
    
    InsertSortedValues(ip, arr, SIZE, -1, SIZE - 1);
    beginItr = ListItrBegin(ip);
    endItr = ListItrEnd(ip);
    
    newList = ListItr_Cut(beginItr, endItr);
    newListBeginItr = ListItrBegin(newList);
    
    for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListItrGet(newListBeginItr);
		newListBeginItr = ListItrNext(newListBeginItr);
	}
	
	beginItr = ListItrBegin(ip);
    endItr = ListItrEnd(ip);
    
	ListDestroy(&ip, NULL);
    ListDestroy(&newList, NULL);
    
    for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( i == *result[i] );
    }
    
    ASSERT_THAT( beginItr == endItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- ListItr_Unique -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListItr_Unique_CheckNull_Begin)
    List* myList = ListCreate();
    ListItr endItr = ListItrEnd(myList);
    List* retVal = ListItr_Unique(NULL, endItr, FoundData);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Unique_CheckNull_End)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    List* retVal = ListItr_Unique(beginItr, NULL, FoundData);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Unique_CheckNull_Function)
    List* myList = ListCreate();
    ListItr beginItr = ListItrBegin(myList);
    ListItr endItr = ListItrEnd(myList);
    List* retVal = ListItr_Unique(beginItr, endItr, NULL);
    
    ListDestroy(&myList, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Unique_CheckEmptyList)
    List* ip = ListCreate();
    ListItr beginItr = ListItrBegin(ip);
    ListItr endItr = ListItrEnd(ip);
    List* newList;
    ListItr newListBeginItr;
    ListItr newListEndItr;

    
    newList = ListItr_Unique(beginItr, endItr, FoundData);
    newListBeginItr = ListItrBegin(newList);
    newListEndItr = ListItrEnd(newList);
	
	beginItr = ListItrNext( ListItrBegin(ip) );
    
	ListDestroy(&ip, NULL);
    ListDestroy(&newList, NULL);
    
    ASSERT_THAT( newListBeginItr == newListEndItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Unique_CheckNoDuplicate)
    List* ip = ListCreate();
    ListItr beginItr;
    ListItr endItr;
    List* newList;
    ListItr newListBeginItr;
    ListItr newListEndItr;
    int* result[SIZE];
    int arr[SIZE];
    size_t i;
    
    InsertSortedValues(ip, arr, SIZE, -1, SIZE - 1);
    beginItr = ListItrBegin(ip);
    endItr = ListItrEnd(ip);
    
    newList = ListItr_Unique(beginItr, endItr, FoundData);
    newListBeginItr = ListItrBegin(newList);
    newListEndItr = ListItrEnd(newList);
    
    for(i = 0; i < SIZE; ++i)
	{
		result[i] = ListItrGet(beginItr);
		beginItr = ListItrNext(beginItr);
	}
	
	beginItr = ListItrNext( ListItrBegin(ip) );
    endItr = ListItrEnd(ip);
    
	ListDestroy(&ip, NULL);
    ListDestroy(&newList, NULL);
    
    /* All element in the new list needed to be equal to value 5, there need to be SIZE -1 elements */
    for(i = 0; i < SIZE; ++i)
	{
    	ASSERT_THAT( i == *result[i] );
    }
    
    /* There need to be only 1 element in the src list */
    ASSERT_THAT( newListBeginItr == newListEndItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListItr_Unique_CheckDuplicateList)
    List* ip = ListCreate();
    ListItr beginItr;
    ListItr endItr;
    List* newList;
    ListItr newListBeginItr;
    int* result[SIZE];
    int arr[SIZE];
    size_t i;
    
    InsertSortedValues(ip, arr, SIZE, 0, 5);
    beginItr = ListItrBegin(ip);
    endItr = ListItrEnd(ip);
    
    newList = ListItr_Unique(beginItr, endItr, FoundData);
    newListBeginItr = ListItrBegin(newList);
    
    for(i = 0; i < (SIZE - 1); ++i)
	{
		result[i] = ListItrGet(newListBeginItr);
		newListBeginItr = ListItrNext(newListBeginItr);
	}
	
	beginItr = ListItrNext( ListItrBegin(ip) );
    endItr = ListItrEnd(ip);
    
	ListDestroy(&ip, NULL);
    ListDestroy(&newList, NULL);
    
    /* All element in the new list needed to be equal to value 5, there need to be SIZE -1 elements */
    for(i = 0; i < (SIZE - 1); ++i)
	{
    	ASSERT_THAT( 5 == *result[i] );
    }
    
    /* There need to be only 1 element in the src list */
    ASSERT_THAT( beginItr == endItr );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(ListFunctions)
	PRINT(ListItr_FindFirst_CheckNull_Begin)
	PRINT(ListItr_FindFirst_CheckNull_End)
	PRINT(ListItr_FindFirst_CheckNull_Function)
	PRINT(ListItr_FindFirst_CheckCase_BeginIsFirst)
	PRINT(ListItr_FindFirst_CheckCase_FirstDoesNotChange)
	PRINT(ListItr_FindFirst_CheckCase_FoundCorrectFirst)
	
	PRINT(ListItr_CountIf_CheckNull_Begin)
	PRINT(ListItr_CountIf_CheckNull_End)
	PRINT(ListItr_CountIf_CheckNull_Function)
	PRINT(ListItr_CountIf_CheckCase_CountToBegin)
	PRINT(ListItr_CountIf_CheckCase_CountToEnd)
	PRINT(ListItr_CountIf_CheckCase_OutOfRange)
	
	PRINT(ListItr_ForEach_CheckNull_Begin)
	PRINT(ListItr_ForEach_CheckNull_End)
	PRINT(ListItr_ForEach_CheckNull_Function)
	PRINT(ListItr_ForEach_CheckCase_ChangeEachValue)
	
	PRINT(ListItr_Sort_CheckAllSorted)
	
	PRINT(ListItr_Splice_CheckNull_Des)
	PRINT(ListItr_Splice_CheckNull_Begin)
	PRINT(ListItr_Splice_CheckNull_End)
	PRINT(ListItr_Splice_Check_InsertToDes)
	
	PRINT(ListItr_Merge_CheckNull_Des)
	PRINT(ListItr_Merge_CheckNull_FirstBegin)
	PRINT(ListItr_Merge_CheckNull_FirstEnd)
	PRINT(ListItr_Merge_CheckNull_SecondBegin)
	PRINT(ListItr_Merge_CheckNull_SecondEnd)
	PRINT(ListItr_Merge_CheckNewList_NoSort)
	PRINT(ListItr_Merge_CheckNewList_WithSort)
	
	PRINT(ListItr_Cut_CheckNull_Begin)
	PRINT(ListItr_Cut_CheckNull_End)
	PRINT(ListItr_Cut_CheckNewList)
	
	PRINT(ListItr_Unique_CheckNull_Begin)
	PRINT(ListItr_Unique_CheckNull_End)
	PRINT(ListItr_Unique_CheckNull_Function)
	PRINT(ListItr_Unique_CheckEmptyList)
	PRINT(ListItr_Unique_CheckNoDuplicate)
	PRINT(ListItr_Unique_CheckDuplicateList)
END_SET
/*----------------------------------------------------------------------------*/





/*************************** Implication of function **************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a data ==  iterator b data
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (-1) 
 *
 * @retval	0		=	if _a == _b
 * @retval	-1		=	if _a != _b
 */
static int FoundData(void* _a, void* _b)
{
	int result = ( *(int*)ListItrGet( (ListItr)_a ) == *(int*)ListItrGet( (ListItr)_b ) );
	
	return --result;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to List values in sort order 
 *
 * @param   list       	= The address of the the source List
 * @param   array		= Pointer to  the elements needed to insert to List 
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
 * @param   array		= Pointer to  the elements needed to insert to List 
 * @param   nElements  	= The number of elements to insert
 * @param   maxValue   	= The max value the rand() function can produce, the max value in the List
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
    int value;
    
    srand((unsigned) time(&t)); 
    value = rand() % _maxValue;
     
    for(i = 0; i < _nElements; i++)
    {
    	_array[i] = value;
        status = ListPushHead(_list, &_array[i]);
        if(LIST_SUCCESS != status)
        {
        	return status;
        }
        value = rand() % _maxValue;
    }
    
    return LIST_SUCCESS;   
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that change all variables to value of context
 *  
 * @param   _element    = Pointer to  the element 
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Countinue loop for all elements
*/
int	ChangeValueAction(void* _element, void* _context)
{
	ListItrSet((ListItr)_element, _context);
	
	return -1;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a data <=  iterator b data
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (-1) 
 *
 * @retval	0		=	if _a <= _b
 * @retval	-1		=	if _a > _b
 */
static int CompareData(void* _a, void* _b)
{
	int result = ( *(int*)ListItrGet( (ListItr)_a ) <= *(int*)ListItrGet( (ListItr)_b ) );
	
	return --result;
}
/*----------------------------------------------------------------------------*/
