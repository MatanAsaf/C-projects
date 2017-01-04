/** 
 *  @file 		tests.c
 *  @brief 		Test file for Generic Binary Tree data type
 * 
 *  @details 	Implement a binary search tree ADT.
 *  			The tree is implemented using a sentinel. 
 *  			The first node in the tree is the sentinel left subtree.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2017-01-01     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

 
#include "binTree.h"	/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <time.h> 		/* for time_t */

#define SIZE (10) /* SIZE = The size of the treetor (num of element) in each test */
#define MAX_RAND_VALUE (500) /* MAX_RAND_VALUE = The max value the function rand() can produce */   



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to treet values in sort order 
 *
 * @param   _tree       = The address of the the source tree
 * @param   _array		= Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 *
 * @return   void
 */
static void InsertSortedValues(BSTree* _tree, int* _array ,size_t _nElements, int _step, int _minValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**
 * @brief	Function that insert to tree random values 
 *
 * @param   _tree       = The address of the the source tree
 * @param   _array		= Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = The number of elements to insert
 * @param   _maxValue   = The max value the rand() function can prduce, the max value in the treetor
 *
 * @return   Amount of elements insert to tree
 */
static size_t InsertRandValues(BSTree* _tree, int* _array, size_t _nElements, int _maxValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**
 * @brief	Function for API: that change all variables to value of context 
 * 
 * @param   _element    = Pointer to  the element 
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Countinue loop for all elements
 */
static int	ChangeValueAction(void* _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a data <  iterator b data
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1		=	if _a < _b
 * @retval	0		=	if _a >= _b
 */
static int CompareData(void* _a, void* _b);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Predicate function returns a none zero value if predicate holds for element
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1		=	if _a == _b
 * @retval	0		=	if _a != _b
 */
static int HoldsDataPredicate(void* _a, void* _b);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Predicate function returns a none zero value if predicate holds for element
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against 
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1		=	if _a == _b
 * @retval	0		=	if _a != _b
 */
static int CompareToValuePredicate(void* _a, void* _b);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*------------------------------- BSTree_Create ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTree_Create_CheckNull)
    ASSERT_THAT( NULL == BSTree_Create(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Create_CheckNotNull)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTree* status = myTree;
	
	BSTree_Destroy(myTree, NULL);
	
    ASSERT_THAT( NULL != status);
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTreeItr_Get ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Get_CheckNull_Tree)
	ASSERT_THAT( NULL == BSTreeItr_Get(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTree_Insert ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTree_Insert_CheckNull_Tree)
	int var = 555;
	
    ASSERT_THAT( NULL == BSTree_Insert(NULL, &var) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Insert_CheckNull_Item)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr retVal = BSTree_Insert(myTree, NULL);
	
	BSTree_Destroy(myTree, NULL);
	
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Insert_CheckCase_CorrectValue)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr itr;
	int var = 555;
	int* retVal;
	
	itr = BSTree_Insert(myTree, &var);
	retVal = BSTreeItr_Get(itr);
	
	BSTree_Destroy(myTree, NULL);
	
    ASSERT_THAT( 555 == *retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Insert_CheckCase_All)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr itr;
	int arr[SIZE];
	int* retVal[SIZE];
	size_t i;
	
	for(i = 0; i < SIZE; ++i)
	{
		arr[i] =  (int)i;
		itr = BSTree_Insert(myTree, &arr[i]);
		retVal[i] = BSTreeItr_Get(itr);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < SIZE; ++i)
	{
		ASSERT_THAT( (int)i == *retVal[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Insert_CheckCase_NoDuplicate)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr itr[SIZE];
	int arr[SIZE];
	int* retVal;
	size_t i;
	
	arr[0] =  888;
	itr[0] = BSTree_Insert(myTree, &arr[0]);
	retVal = BSTreeItr_Get(itr[0]);
	
	for(i = 1; i < SIZE; ++i)
	{
		arr[i] =  888;
		itr[i] = BSTree_Insert(myTree, &arr[i]);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( 888 == *retVal );
	for(i = 1; i < SIZE; ++i)
	{
		ASSERT_THAT( NULL == itr[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTreeItr_Begin ----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Begin_CheckNull_Tree)
	ASSERT_THAT( NULL == BSTreeItr_Begin(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Begin_CheckCase_BeginStayTheSame)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr beginItr[SIZE];
	int arr[SIZE];
	int* retVal[SIZE];
	size_t i;
	
	for(i = 0; i < SIZE; ++i)
	{
		arr[i] =  (int)i;
		BSTree_Insert(myTree, &arr[i]);
		beginItr[i] = BSTreeItr_Begin(myTree);
		retVal[i] = BSTreeItr_Get(beginItr[i]);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		ASSERT_THAT( 0 == *retVal[i] && beginItr[i] == beginItr[i + 1]);
	}
	ASSERT_THAT( 0 == *retVal[i] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Begin_CheckCase_BeginIsTheSmallest)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr itr;
	BSTreeItr beginItr;
	int arr[SIZE];
	int* retVal;
	size_t i;
	
	for(i = SIZE; i > 0; --i)
	{
		arr[SIZE - i] =  (int)i;
		itr = BSTree_Insert(myTree, &arr[SIZE - i]);
		beginItr = BSTreeItr_Begin(myTree);
		retVal = BSTreeItr_Get(beginItr);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( 1 == *retVal && beginItr == itr );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_Begin_CheckCase_RandValues)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr beginItr;
	int arr[SIZE];
	int* retVal;
	size_t i;
	size_t endOfLoop;
	
	endOfLoop = InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	
	beginItr = BSTreeItr_Begin(myTree);
	retVal = BSTreeItr_Get(beginItr);
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < endOfLoop; ++i)
	{
		ASSERT_THAT( arr[i] >= *retVal );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTreeItr_End ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_End_CheckNull_Tree)
	ASSERT_THAT( NULL == BSTreeItr_End(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_End_CheckCase_EndStayTheSame)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr endItr[SIZE];
	int arr[SIZE];
	int* retVal[SIZE];
	size_t i;
	
	for(i = SIZE; i > 0; --i)
	{
		arr[SIZE - i] =  (int)i;
		BSTree_Insert(myTree, &arr[SIZE - i]);
		endItr[SIZE - i] = BSTreeItr_End(myTree);
		retVal[SIZE - i] = BSTreeItr_Get(endItr[SIZE - i]);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		ASSERT_THAT( SIZE == *retVal[i] && endItr[i] == endItr[i + 1]);
	}
	ASSERT_THAT( SIZE == *retVal[i] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_End_CheckCase_EndIsTheLargest)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr itr;
	BSTreeItr endItr;
	int arr[SIZE];
	int* retVal;
	size_t i;
	
	for(i = 0; i < SIZE; ++i)
	{
		arr[i] =  (int)i;
		itr = BSTree_Insert(myTree, &arr[i]);
		endItr = BSTreeItr_End(myTree);
		retVal = BSTreeItr_Get(endItr);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( (SIZE - 1) == *retVal && endItr == itr );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_End_CheckCase_RandValues)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr endItr;
	int arr[SIZE];
	int* retVal;
	size_t i;
	size_t endOfLoop;
	
	endOfLoop = InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	
	endItr = BSTreeItr_End(myTree);
	retVal = BSTreeItr_Get(endItr);
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < endOfLoop; ++i)
	{
		ASSERT_THAT( arr[i] <= *retVal );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTreeItr_Equals ---------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Equals_CheckNull_OnlyFirst)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr endItr;
	int result;
	int var;
	
	var =  888;
	BSTree_Insert(myTree, &var);
	endItr = BSTreeItr_End(myTree);
	result = BSTreeItr_Equals(NULL, endItr);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Equals_CheckNull_OnlySecond)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr beginItr;
	int result;
	int var;
	
	var =  888;
	BSTree_Insert(myTree, &var);
	beginItr = BSTreeItr_Begin(myTree);
	result = BSTreeItr_Equals(beginItr, NULL);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Equals_CheckNull_Both)
	BSTree* myTree = BSTree_Create(CompareData);
	int result;
	
	result = BSTreeItr_Equals(NULL, NULL);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( 1 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Equals_CheckCase_BeginIsEnd)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr beginItr;
	BSTreeItr endItr;
	int result;
	int var;
	
	var =  888;
	BSTree_Insert(myTree, &var);
	beginItr = BSTreeItr_Begin(myTree);
	endItr = BSTreeItr_End(myTree);
	result = BSTreeItr_Equals(beginItr, endItr);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( 1 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Equals_CheckCase_BeginIsNotEnd)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr beginItr;
	BSTreeItr endItr;
	int result;
	int arr[SIZE];
	
	InsertSortedValues(myTree, arr ,SIZE, 1, 56);
	
	beginItr = BSTreeItr_Begin(myTree);
	endItr = BSTreeItr_End(myTree);
	result = BSTreeItr_Equals(beginItr, endItr);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( 0 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTreeItr_Next -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Next_CheckNull_Tree)
	ASSERT_THAT( NULL == BSTreeItr_Next(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Next_CheckCase_SortedValues)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr resultItr[SIZE];
	int* resultData[SIZE];
	int arr[SIZE];
	size_t i;
	
	InsertSortedValues(myTree, arr ,SIZE, 1, 0);
	
	resultItr[0] = BSTreeItr_Begin(myTree);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		resultData[i] = BSTreeItr_Get(resultItr[i]);
		resultItr[i + 1] = BSTreeItr_Next(resultItr[i]);
	}
	
	resultData[i] = BSTreeItr_Get(resultItr[i]);
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		ASSERT_THAT( *resultData[i] < *resultData[i + 1] && (int)i == *resultData[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Next_CheckCase_RandValues)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr resultItr[SIZE];
	BSTreeItr endItr;
	int* resultData[SIZE];
	int arr[SIZE];
	size_t i = 0;
	
	InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	
	resultItr[i] = BSTreeItr_Begin(myTree);
	endItr = BSTreeItr_End(myTree);
	
	while( endItr != resultItr[i] )
	{
		resultData[i] = BSTreeItr_Get(resultItr[i]);
		resultItr[i + 1] = BSTreeItr_Next(resultItr[i]);
		++i;
	}
	
	resultData[i] = BSTreeItr_Get(resultItr[i]);
	
	BSTree_Destroy(myTree, NULL);
	
	i = 0;
	
	while( endItr != resultItr[i] )
	{
		ASSERT_THAT( *resultData[i] < *resultData[i + 1] );
		++i;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTreeItr_Prev -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Prev_CheckNull_Tree)
	ASSERT_THAT( NULL == BSTreeItr_Prev(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Prev_CheckCase_SortedValues)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr resultItr[SIZE];
	int* resultData[SIZE];
	int arr[SIZE];
	size_t i;
	
	InsertSortedValues(myTree, arr ,SIZE, 1, 0);
	
	resultItr[0] = BSTreeItr_End(myTree);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		resultData[i] = BSTreeItr_Get(resultItr[i]);
		resultItr[i + 1] = BSTreeItr_Prev(resultItr[i]);
	}
	
	resultData[i] = BSTreeItr_Get(resultItr[i]);
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < (SIZE - 1); ++i)
	{
		ASSERT_THAT( *resultData[i] > *resultData[i + 1] && (int)(SIZE - 1 -i) == *resultData[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Prev_CheckCase_RandValues)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr resultItr[SIZE];
	BSTreeItr beginItr;
	int* resultData[SIZE];
	int arr[SIZE];
	size_t i = 0;
	
	InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	
	resultItr[i] = BSTreeItr_End(myTree);
	beginItr = BSTreeItr_Begin(myTree);
	
	while( beginItr != resultItr[i] )
	{
		resultData[i] = BSTreeItr_Get(resultItr[i]);
		resultItr[i + 1] = BSTreeItr_Prev(resultItr[i]);
		++i;
	}
	
	resultData[i] = BSTreeItr_Get(resultItr[i]);
	
	BSTree_Destroy(myTree, NULL);
	
	i = 0;
	
	while( beginItr != resultItr[i] )
	{
		ASSERT_THAT( *resultData[i] > *resultData[i + 1] );
		++i;
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTree_FindFirst ---------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTree_FindFirst_CheckNull_Tree)
	ASSERT_THAT( NULL == BSTree_FindFirst(NULL, HoldsDataPredicate, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_FindFirst_CheckNull_Function)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr retVal;
	
	retVal = BSTree_FindFirst(myTree, NULL, NULL);
	
	BSTree_Destroy (myTree, NULL);
	
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_FindFirst_CheckCase_EmptyTree)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr resultItr;
	int cmpValue = MAX_RAND_VALUE + 1;
	
	resultItr = BSTree_FindFirst(myTree, CompareToValuePredicate, &cmpValue);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( NULL == resultItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_FindFirst_CheckCase_NotFound)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr resultItr;
	int arr[SIZE];
	int cmpValue = MAX_RAND_VALUE + 1;
	
	InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	
	resultItr = BSTree_FindFirst(myTree, CompareToValuePredicate, &cmpValue);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( NULL == resultItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_FindFirst_CheckCase_FoundRoot)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr rootItr;
	BSTreeItr resultItr;
	int arr[SIZE];
	int rootData;
	
	rootData =  rand() % MAX_RAND_VALUE;
	rootItr = BSTree_Insert(myTree, &rootData);
	
	InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	
	resultItr = BSTree_FindFirst(myTree, HoldsDataPredicate, &rootData);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( resultItr == rootItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTreeItr_Remove ---------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Remove_CheckNull_Tree)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr itr;
	int* retVal;
	int data =  rand() % MAX_RAND_VALUE;
	
	itr = BSTree_Insert(myTree, &data);
	
	retVal = BSTreeItr_Remove(NULL, itr);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Remove_CheckNull_Itr)
	BSTree* myTree = BSTree_Create(CompareData);
	int* retVal;
	
	retVal = BSTreeItr_Remove(myTree, NULL);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Remove_CheckCase_NoChild)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr resultItr;
	BSTreeItr foundItr;
	int* retVal;
	int data;
	
	data =  rand() % MAX_RAND_VALUE;
	resultItr = BSTree_Insert(myTree, &data);
	
	retVal = BSTreeItr_Remove(myTree, resultItr);
	
	foundItr = BSTree_FindFirst(myTree, HoldsDataPredicate, &retVal);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( data == *retVal && NULL == foundItr );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Remove_CheckCase_1Child)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr foundItr[SIZE];
	BSTreeItr endItr[SIZE];
	int arr[SIZE];
	int* retVal[SIZE];
	size_t i;
	
	InsertSortedValues(myTree, arr, SIZE, 1, 0);
	
	for(i = 0; i < SIZE; ++i)
	{
		endItr[i] = BSTreeItr_End(myTree);
		retVal[i] = BSTreeItr_Remove(myTree, endItr[i]);
		foundItr[i] = BSTree_FindFirst(myTree, HoldsDataPredicate, &retVal[i]);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	for(i = 0; i < SIZE; ++i)
	{
		ASSERT_THAT( (SIZE -1 -i) == *retVal[i] && NULL == foundItr[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTreeItr_Remove_CheckCase_2Child)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr foundItr;
	BSTreeItr endItr[SIZE];
	BSTreeItr rootItr;
	int arr[SIZE];
	int* retVal[SIZE];
	size_t i;
	size_t endOfLoop;
	int rootData;
	int* rootRetVal;
	
	rootData =  rand() % MAX_RAND_VALUE;
	rootItr = BSTree_Insert(myTree, &rootData);
	
	endOfLoop = InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	
	rootRetVal = BSTreeItr_Remove(myTree, rootItr);
	foundItr = BSTree_FindFirst(myTree, HoldsDataPredicate, &rootRetVal);
	
	for(i = 0; i < endOfLoop; ++i)
	{
		endItr[i] = BSTreeItr_End(myTree);
		retVal[i] = BSTreeItr_Remove(myTree, endItr[i]);
	}
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( rootData == *rootRetVal && NULL == foundItr );
	
	for(i = 0; i < (endOfLoop - 1); ++i)
	{
		ASSERT_THAT( *retVal[i] > *retVal[i + 1] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- BSTree_ForEach -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(BSTree_ForEach_CheckNull_Tree)
	BSTree* myTree = BSTree_Create(CompareData);
	int changeValue = 9;
	BSTreeItr retVal;
	
	retVal = BSTree_ForEach(NULL, 0, ChangeValueAction, &changeValue);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_ForEach_CheckNull_IlegalMode)
	BSTree* myTree = BSTree_Create(CompareData);
	int changeValue = 9;
	BSTreeItr retVal;
	
	retVal = BSTree_ForEach(myTree, 3, ChangeValueAction, &changeValue);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_ForEach_CheckCase_PreOrderMode)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr endItr;
	int changeValue = 0;
	BSTreeItr retVal;
	int arr[SIZE];
	size_t endOfLoop;
	size_t i;
	
	endOfLoop = InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	endItr = BSTreeItr_End(myTree);
	
	retVal = BSTree_ForEach(myTree, 0, ChangeValueAction, &changeValue);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( endItr == retVal );
	for(i = 0; i < endOfLoop; ++i)
	{
		ASSERT_THAT( changeValue == arr[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_ForEach_CheckCase_InOrderMode)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr endItr;
	int changeValue = 1;
	BSTreeItr retVal;
	int arr[SIZE];
	size_t endOfLoop;
	size_t i;
	
	endOfLoop = InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	endItr = BSTreeItr_End(myTree);
	
	retVal = BSTree_ForEach(myTree, 1, ChangeValueAction, &changeValue);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( endItr == retVal );
	for(i = 0; i < endOfLoop; ++i)
	{
		ASSERT_THAT( changeValue == arr[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(BSTree_ForEach_CheckCase_PostOrderMode)
	BSTree* myTree = BSTree_Create(CompareData);
	BSTreeItr endItr;
	int changeValue = 2;
	BSTreeItr retVal;
	int arr[SIZE];
	size_t endOfLoop;
	size_t i;
	
	endOfLoop = InsertRandValues(myTree, arr, SIZE, MAX_RAND_VALUE);
	endItr = BSTreeItr_End(myTree);
	
	retVal = BSTree_ForEach(myTree, 2, ChangeValueAction, &changeValue);
	
	BSTree_Destroy(myTree, NULL);
	
	ASSERT_THAT( endItr == retVal );
	for(i = 0; i < endOfLoop; ++i)
	{
		ASSERT_THAT( changeValue == arr[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Test Generic Binary Tree)
	PRINT(BSTree_Create_CheckNull)
	PRINT(BSTree_Create_CheckNotNull)
	
	PRINT(BSTreeItr_Get_CheckNull_Tree)
	
	PRINT(BSTree_Insert_CheckNull_Tree)
	PRINT(BSTree_Insert_CheckNull_Item)
	PRINT(BSTree_Insert_CheckCase_CorrectValue)
	PRINT(BSTree_Insert_CheckCase_All)
	PRINT(BSTree_Insert_CheckCase_NoDuplicate)
	
	PRINT(BSTreeItr_Begin_CheckNull_Tree)
	PRINT(BSTree_Begin_CheckCase_BeginStayTheSame)
	PRINT(BSTree_Begin_CheckCase_BeginIsTheSmallest)
	PRINT(BSTree_Begin_CheckCase_RandValues)
	
	PRINT(BSTreeItr_End_CheckNull_Tree)
	PRINT(BSTree_End_CheckCase_EndStayTheSame)
	PRINT(BSTree_End_CheckCase_EndIsTheLargest)
	PRINT(BSTree_End_CheckCase_RandValues)
	
	PRINT(BSTreeItr_Equals_CheckNull_OnlyFirst)
	PRINT(BSTreeItr_Equals_CheckNull_OnlySecond)
	PRINT(BSTreeItr_Equals_CheckNull_Both)
	PRINT(BSTreeItr_Equals_CheckCase_BeginIsEnd)
	PRINT(BSTreeItr_Equals_CheckCase_BeginIsNotEnd)

	PRINT(BSTreeItr_Next_CheckNull_Tree)
	PRINT(BSTreeItr_Next_CheckCase_SortedValues)
	PRINT(BSTreeItr_Next_CheckCase_RandValues)
	
	PRINT(BSTreeItr_Prev_CheckNull_Tree)
	PRINT(BSTreeItr_Prev_CheckCase_SortedValues)
	PRINT(BSTreeItr_Prev_CheckCase_RandValues)
	
	PRINT(BSTree_FindFirst_CheckNull_Tree)
	PRINT(BSTree_FindFirst_CheckNull_Function)
	PRINT(BSTree_FindFirst_CheckCase_EmptyTree)
	PRINT(BSTree_FindFirst_CheckCase_NotFound)
	PRINT(BSTree_FindFirst_CheckCase_FoundRoot)
	
	PRINT(BSTreeItr_Remove_CheckNull_Tree)
	PRINT(BSTreeItr_Remove_CheckNull_Itr)
	PRINT(BSTreeItr_Remove_CheckCase_NoChild)
	PRINT(BSTreeItr_Remove_CheckCase_1Child)
	PRINT(BSTreeItr_Remove_CheckCase_2Child)
	
	PRINT(BSTree_ForEach_CheckNull_Tree)
	PRINT(BSTree_ForEach_CheckNull_IlegalMode)
	PRINT(BSTree_ForEach_CheckCase_PreOrderMode)
	PRINT(BSTree_ForEach_CheckCase_InOrderMode)
	PRINT(BSTree_ForEach_CheckCase_PostOrderMode)
END_SET
/*----------------------------------------------------------------------------*/




/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to tree values in sort order 
 *
 * @param   _tree       = The address of the the source tree
 * @param   _array		= Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 *
 * @return   void
*/
static void InsertSortedValues(BSTree* _tree, int* _array ,size_t _nElements, int _step, int _minValue)
{
    size_t i;
    int value = _minValue;
    
    for( i = 0;  i < _nElements; ++i )
    {
    	_array[i] = value;
        if(NULL == BSTree_Insert(_tree, &_array[i]) )
        {
        	return;
        }
        value += _step;
    }
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to tree random values 
 *
 * @param   _tree       = The address of the the source tree
 * @param   _array		= Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = The number of elements to insert
 * @param   _maxValue   = The max value the rand() function can prduce, the max value in the treetor
 *
 * @return   Amount of elements insert to tree
*/
static size_t InsertRandValues(BSTree* _tree, int* _array, size_t _nElements, int _maxValue)
{
    size_t i;
    size_t counter = 0;
    time_t t;
    
    srand((unsigned) time(&t)); 
     
    for(i = 0; i < _nElements; i++)
    {
    	_array[i] =  rand() % _maxValue;
        if(NULL == BSTree_Insert(_tree, &_array[i]) )
        {
        	return counter;
        }
        
        ++counter;
    }
    
    return counter;   
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**
 * @brief	Function for API: that change all variables to value of context 
 * 
 * @param   _element    = Pointer to  the element 
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Countinue loop for all elements
 */
static int	ChangeValueAction(void* _element, void* _context)
{
	*(int*)_element = *(int*)_context;
	
	return -1;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a data <  iterator b data
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1		=	if _a < _b
 * @retval	0		=	if _a >= _b
 */
static int CompareData(void* _a, void* _b)
{
	return ( *(int*)_a  < *(int*)_b );
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Predicate function returns a none zero value if predicate holds for element
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against 
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1		=	if _a == _b
 * @retval	0		=	if _a != _b
 */
static int HoldsDataPredicate(void* _a, void* _b)
{
	return ( _a == _b );
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Predicate function returns a none zero value if predicate holds for element
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against 
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1		=	if _a == _b
 * @retval	0		=	if _a != _b
 */
static int CompareToValuePredicate(void* _a, void* _b)
{
	return ( *(int*)_a == *(int*)_b );
}
/*----------------------------------------------------------------------------*/
