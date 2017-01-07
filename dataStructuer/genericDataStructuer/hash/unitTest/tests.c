/** 
 *  @file 		tests.c
 *  @brief 		Test file for Generic Hash map of key-value pairs data type
 * 
 *  @details 	The API stores pointer to user provided elements of generic type.
 * 				The hash map (sometimes called dictionary or associative array)
 *  			is a set of distinct keys (or indexes) mapped (or associated) to values.
 *
 *				Implemented with separate chaining using linked lists.
 *  			Nodes are allocated from heap and store pointer to user proveded element.
 *				Size of allocated table will be the nearest prime number greater than requested capacity.
 *  			Lists used for chaining will be allocated eagerly.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2017-01-04    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 

 
#include "hashMap.h"	/* header file */
#include "matan_test.h"	/* def of unit test */
#include <stdio.h>  	/* for printf */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <time.h> 		/* for time_t */

#define DEBUG (0)
#define BUCKETS_SIZE (10) /*Number of buckets in each test */
#define NUMBER_OF_ELEMENTS (100) /* Number of elements to insert to hashMap in each test */
#define MAX_RAND_VALUE (500) /* MAX_RAND_VALUE = The max value the function rand() can produce */   



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/* 
 * @brief	Function that generate the key 
 * @params  _key	=   The pointer to key varibale
 *				
 * @returns index in which bucket to insert key  	
 */
static size_t GenerateKey(void* _key);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a key ==  iterator b key
 *
 * @param 	_a		= 	Element to test
 * @param 	_b		= 	Element to test against
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1		=	if _a == _b
 * @retval	0		=	if _a != _b
 */
static int CompareKey(void* _a, void* _b);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that change all variables to value of context
 *  
 * @param   _key    	= Pointer to key
 * @param   _value    	= Pointer to value
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Countinue loop for all elements
*/
int	ChangeValueAction(void* _key, void* _value, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that print all all key-value pairs in the map
 *  
 * @param   _key    	= Pointer to key
 * @param   _value    	= Pointer to value
 * @param   _context  	= The new value of the element
 *
 * @return   -1 		= Continue loop for all elements
*/
int	PrintAction(void* _key, void* _value, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to array values in sort order 
 *
 * @param   _array		= Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _lastValue  = The value of the last element
 *
 * @return   void
*/
static void InsertSortedValues(int* _array ,size_t _nElements, int _step, int _lastValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to array random values 
 *
 * @param   _array		= Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = The number of elements to insert
 * @param   _maxValue   = The max value the rand() function can prduce, the max value in the treetor
 *
 * @return   void
*/
static void InsertRandValues(int* _array, size_t _nElements, int _maxValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to hashMap all key-value pairs 
 *
 * @param 	_map		=	Hash map to insert to, must be initialized
 * @param 	_key		=	Key to serve as distinct element 
 * @param 	_value		=	The value to associate with the key
 * @param   _nElements  = 	The number of elements to insert
 *
 * @return	Amount of elements inserted in to the hash map:
 *
 * @retval  Number    	=   On success
 * @retval  0    		=   On failure
*/
static size_t InsertToHash(HashMap* _map, size_t* _key, int* _value, size_t _nElements);
/*----------------------------------------------------------------------------*/





/*************************** Tests for API functions **************************/
/*------------------------------- HashMap_Create -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_Create_CheckNull_NoCapacity) 
    ASSERT_THAT( NULL == HashMap_Create(0, GenerateKey, CompareKey) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Create_CheckNull_NoHashFunc) 
    ASSERT_THAT( NULL == HashMap_Create(BUCKETS_SIZE, NULL, CompareKey) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Create_CheckNull_NoEqualityFunc) 
    ASSERT_THAT( NULL == HashMap_Create(BUCKETS_SIZE, GenerateKey, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Create_CheckNotNull)
	HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	HashMap* retval = hash;
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( NULL != retval );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- HashMap_Insert -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_Insert_CheckNull_NoMap)
	size_t key = 0;
	int value = 555;
	
    ASSERT_THAT( MAP_UNINITIALIZED_ERROR == HashMap_Insert(NULL, &key, &value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Insert_CheckNull_NoKey)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	int value = 555;
	
	status = HashMap_Insert(hash, NULL, &value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_KEY_NULL_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Insert_CheckCase_NoValue)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t key = 0;
	
	status = HashMap_Insert(hash, &key, NULL);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Insert_CheckCase_Regular)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status[NUMBER_OF_ELEMENTS];
	size_t key[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	size_t i;
	
	for(i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		key[i] = i;
		value[i] = (rand() % MAX_RAND_VALUE) - (MAX_RAND_VALUE / 2);
		status[i] = HashMap_Insert(hash, &key[i], &value[i]);
	}
	
	HashMap_Destroy(&hash, NULL, NULL);
	
	for(i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
    	ASSERT_THAT( MAP_SUCCESS == status[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Insert_CheckCase_Duplicate)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status[NUMBER_OF_ELEMENTS];
	size_t key[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	size_t i;
	
	for(i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		key[i] = 0;
		value[i] = (rand() % MAX_RAND_VALUE) - (MAX_RAND_VALUE / 2);
		status[i] = HashMap_Insert(hash, &key[i], &value[i]);
	}
	
	HashMap_Destroy(&hash, NULL, NULL);
	
	ASSERT_THAT( MAP_SUCCESS == status[0] );
	for(i = 1; i < NUMBER_OF_ELEMENTS; ++i)
	{
    	ASSERT_THAT( MAP_KEY_DUPLICATE_ERROR == status[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- HashMap_Remove -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_CheckNull_NoMap)
	size_t searchKey = 0;
	size_t* key;
	int* value;
	
    ASSERT_THAT( MAP_UNINITIALIZED_ERROR == HashMap_Remove(NULL, &searchKey, (void**)&key, (void**)&value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_CheckNull_NoSearchKey)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t* key;
	int* value;
	
	status = HashMap_Remove(hash, NULL, (void**)&key, (void**)&value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_KEY_NULL_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_CheckNull_NoKey)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t searchKey = 0;
	int* value;
	
	status = HashMap_Remove(hash, &searchKey, NULL, (void**)&value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_ITEM_NULL_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_CheckNull_NoValue)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t searchKey = 0;
	size_t* key;
	
	status = HashMap_Remove(hash, &searchKey, (void**)&key, NULL);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_ITEM_NULL_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_CheckNotFound)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t searchKey = 0;
	size_t* key;
	int* value;
	
	status = HashMap_Remove(hash, &searchKey, (void**)&key, (void**)&value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_KEY_NOT_FOUND_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_CheckNotNull)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t searchKey = 0;
	size_t* key;
	int* value;
	
	HashMap_Insert(hash, &searchKey, NULL);
	status = HashMap_Remove(hash, &searchKey, (void**)&key, (void**)&value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_Check_OutOfTheMap)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status1[NUMBER_OF_ELEMENTS];
	MapResult status2[NUMBER_OF_ELEMENTS];
	size_t searchKey[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	size_t* retKey;
	int* retValue;
	size_t i;
	
	retKey = &i; 	/* just for retKey will not point to NULL */
	
	InsertSortedValues((int*)searchKey, NUMBER_OF_ELEMENTS, -1, NUMBER_OF_ELEMENTS - 1);
	InsertRandValues(value, NUMBER_OF_ELEMENTS, MAX_RAND_VALUE);
	InsertToHash(hash, searchKey, value, NUMBER_OF_ELEMENTS);
	
	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		status1[i] = HashMap_Remove(hash, &searchKey[i], (void**)&retKey, (void**)&retValue);
		status2[i] = HashMap_Remove(hash, &searchKey[i], (void**)&retKey, (void**)&retValue);
	}
	
	HashMap_Destroy(&hash, NULL, NULL);

	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		ASSERT_THAT( MAP_SUCCESS == status1[i] );
		ASSERT_THAT( MAP_KEY_NOT_FOUND_ERROR == status2[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Remove_Check_CorrectData)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status[NUMBER_OF_ELEMENTS];
	size_t searchKey[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	size_t* retKey[NUMBER_OF_ELEMENTS];
	int* retValue[NUMBER_OF_ELEMENTS];
	size_t i;
	
	
	InsertSortedValues((int*)searchKey, NUMBER_OF_ELEMENTS, -1, NUMBER_OF_ELEMENTS - 1);
	InsertRandValues(value, NUMBER_OF_ELEMENTS, MAX_RAND_VALUE);
	InsertToHash(hash, searchKey, value, NUMBER_OF_ELEMENTS);
	
	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		retKey[i] = &i; 	/* just for retKey will not point to NULL */
		status[i] = HashMap_Remove(hash, &searchKey[i], (void**)&retKey[i], (void**)&retValue[i]);
	}
	
	HashMap_Destroy(&hash, NULL, NULL);

	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		ASSERT_THAT( MAP_SUCCESS == status[i] );
		ASSERT_THAT( searchKey[i] == *retKey[i] );
		ASSERT_THAT( value[i] == *retValue[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- HashMap_Find -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_Find_CheckNull_NoMap)
	size_t key = 0;
	int* value;
	
    ASSERT_THAT( MAP_UNINITIALIZED_ERROR == HashMap_Find(NULL, &key, (void**)&value) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Find_CheckNull_NoKey)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	int* value;
	
	status = HashMap_Find(hash, NULL, (void**)&value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_KEY_NULL_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Find_CheckNull_NoValue)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t key = 0;
	
	status = HashMap_Find(hash, &key, NULL);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_ITEM_NULL_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Find_CheckNotFound)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t searchKey = 0;
	int* value;
	
	status = HashMap_Find(hash, &searchKey, (void**)&value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_KEY_NOT_FOUND_ERROR == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Find_CheckNotNull)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status;
	size_t searchKey = 0;
	int* value;
	
	HashMap_Insert(hash, &searchKey, NULL);
	status = HashMap_Find(hash, &searchKey, (void**)&value);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( MAP_SUCCESS == status );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Find_Check_NotOutOfTheMap)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status1[NUMBER_OF_ELEMENTS];
	MapResult status2[NUMBER_OF_ELEMENTS];
	size_t searchKey[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	int* retValue;
	size_t i;
	
	retValue = &value[0];/* just for retValue will not point to NULL */
	
	InsertSortedValues((int*)searchKey, NUMBER_OF_ELEMENTS, -1, NUMBER_OF_ELEMENTS - 1);
	InsertRandValues(value, NUMBER_OF_ELEMENTS, MAX_RAND_VALUE);
	InsertToHash(hash, searchKey, value, NUMBER_OF_ELEMENTS);
	
	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		status1[i] = HashMap_Find(hash, &searchKey[i], (void**)&retValue);
		status2[i] = HashMap_Find(hash, &searchKey[i], (void**)&retValue);
	}
	
	HashMap_Destroy(&hash, NULL, NULL);

	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		ASSERT_THAT( MAP_SUCCESS == status1[i] );
		ASSERT_THAT( MAP_SUCCESS == status2[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Find_Check_CorrectData)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	MapResult status[NUMBER_OF_ELEMENTS];
	size_t searchKey[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	int* retValue[NUMBER_OF_ELEMENTS];
	size_t i;
	
	InsertSortedValues((int*)searchKey, NUMBER_OF_ELEMENTS, -1, NUMBER_OF_ELEMENTS - 1);
	InsertRandValues(value, NUMBER_OF_ELEMENTS, MAX_RAND_VALUE);
	InsertToHash(hash, searchKey, value, NUMBER_OF_ELEMENTS);
	
	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		status[i] = HashMap_Find(hash, &searchKey[i], (void**)&retValue[i]);
	}
	
	HashMap_Destroy(&hash, NULL, NULL);

	for( i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		ASSERT_THAT( MAP_SUCCESS == status[i] );
		ASSERT_THAT( value[i] == *retValue[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- HashMap_Size -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_Size_CheckNull_NoMap)
    ASSERT_THAT( 0 == HashMap_Size(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Size_Check_CorrectData)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	size_t result;
	size_t searchKey[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	
	InsertSortedValues((int*)searchKey, NUMBER_OF_ELEMENTS, -1, NUMBER_OF_ELEMENTS - 1);
	InsertRandValues(value, NUMBER_OF_ELEMENTS, MAX_RAND_VALUE);
	InsertToHash(hash, searchKey, value, NUMBER_OF_ELEMENTS);
	
	result = HashMap_Size(hash);
	
	HashMap_Destroy(&hash, NULL, NULL);

	ASSERT_THAT( NUMBER_OF_ELEMENTS == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Size_CheckCase_Duplicate)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	size_t key[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	size_t i;
	size_t result;
	
	for(i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		key[i] = 0;
		value[i] = (rand() % MAX_RAND_VALUE) - (MAX_RAND_VALUE / 2);
		HashMap_Insert(hash, &key[i], &value[i]);
	}
	
	result = HashMap_Size(hash);
	
	HashMap_Destroy(&hash, NULL, NULL);

    ASSERT_THAT( 1 == result );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- HashMap_Print ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_Print_CheckNull_NoMap)
	int newValue = 999;
	
    ASSERT_THAT( 0 == HashMap_Print(NULL, PrintAction, &newValue) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_Print_CheckNull_NoFunction)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	int newValue = 999;
	size_t counter;
	
	counter = HashMap_Print(hash, NULL, &newValue);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( 0 == counter );
END_TEST
/*----------------------------------------------------------------------------*/


#if DEBUG
/*----------------------------------------------------------------------------*/
TEST(HashMap_Print_CheckCase_All)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	size_t counter[2];
	size_t key[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	
	InsertSortedValues((int*)key, NUMBER_OF_ELEMENTS, -1, NUMBER_OF_ELEMENTS - 1);
	InsertRandValues(value, NUMBER_OF_ELEMENTS, MAX_RAND_VALUE);
	counter[0] = InsertToHash(hash, key, value, NUMBER_OF_ELEMENTS);
	
	counter[1] = HashMap_Print(hash, PrintAction, NULL);
	
	HashMap_Destroy(&hash, NULL, NULL);

    ASSERT_THAT( NUMBER_OF_ELEMENTS == counter[0] && NUMBER_OF_ELEMENTS == counter[1] );
END_TEST
/*----------------------------------------------------------------------------*/
#endif


/*------------------------------- HashMap_ForEach ----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_ForEach_CheckNull_NoMap)
	int newValue = 999;
	
    ASSERT_THAT( 0 == HashMap_ForEach(NULL, ChangeValueAction, &newValue) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_ForEach_CheckNull_NoFunction)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	int newValue = 999;
	size_t counter;
	
	counter = HashMap_ForEach(hash, NULL, &newValue);
	
	HashMap_Destroy(&hash, NULL, NULL);
	
    ASSERT_THAT( 0 == counter );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_ForEach_CheckCase_All)
    HashMap* hash = HashMap_Create(BUCKETS_SIZE, GenerateKey, CompareKey);
	size_t counter;
	size_t key[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	int newValue = MAX_RAND_VALUE * 10;
	size_t i;
	
	InsertSortedValues((int*)key, NUMBER_OF_ELEMENTS, -1, NUMBER_OF_ELEMENTS - 1);
	InsertRandValues(value, NUMBER_OF_ELEMENTS, MAX_RAND_VALUE);
	InsertToHash(hash, key, value, NUMBER_OF_ELEMENTS);
	
	counter = HashMap_ForEach(hash, ChangeValueAction, &newValue);
	
	HashMap_Destroy(&hash, NULL, NULL);

    ASSERT_THAT( NUMBER_OF_ELEMENTS == counter );
    for(i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		ASSERT_THAT( newValue == value[i] );
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- HashMap_GetStatistics ----------------------*/
/*----------------------------------------------------------------------------*/
TEST(HashMap_GetStatistics_CheckNull_NoMap)
    ASSERT_THAT( NULL == HashMap_GetStatistics(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(HashMap_GetStatistics_Check_CorrectData)
    HashMap* hash = HashMap_Create(5, GenerateKey, CompareKey);
	MapStats* retPtr;
	MapResult status[NUMBER_OF_ELEMENTS];
	size_t key[NUMBER_OF_ELEMENTS];
	int value[NUMBER_OF_ELEMENTS];
	size_t result[5];
	size_t i;
	
	for(i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		key[i] = 5 * i;
		value[i] = (rand() % MAX_RAND_VALUE) - (MAX_RAND_VALUE / 2);
		status[i] = HashMap_Insert(hash, &key[i], &value[i]);
	}
	
	#if DEBUG
		HashMap_Print(hash, PrintAction, NULL);
	#endif
	
	retPtr = HashMap_GetStatistics(hash);
	result[0] = retPtr->m_numberOfBuckets;
	result[1] = retPtr->m_numberOfChains;
	result[2] = retPtr->m_maxChainLength;
	result[3] = retPtr->m_maxChainLengthIndex;
	result[4] = retPtr->m_averageChainLength;
	
	free(retPtr);
	HashMap_Destroy(&hash, NULL, NULL);

	for(i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		ASSERT_THAT( MAP_SUCCESS == status[i] );
	}
	
	ASSERT_THAT( 5 == result[0] );
	ASSERT_THAT( 1 == result[1] );
	ASSERT_THAT( 100 == result[2] );
	ASSERT_THAT( 0 == result[3] );
	ASSERT_THAT( (NUMBER_OF_ELEMENTS / 5) == result[4] );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Generic HashMap)
	PRINT(HashMap_Create_CheckNull_NoCapacity)
	PRINT(HashMap_Create_CheckNull_NoHashFunc)
	PRINT(HashMap_Create_CheckNull_NoEqualityFunc)
	PRINT(HashMap_Create_CheckNotNull)
	
	PRINT(HashMap_Insert_CheckNull_NoMap)
	PRINT(HashMap_Insert_CheckNull_NoKey)
	PRINT(HashMap_Insert_CheckCase_NoValue)
	PRINT(HashMap_Insert_CheckCase_Regular)
	PRINT(HashMap_Insert_CheckCase_Duplicate)
	
	PRINT(HashMap_Remove_CheckNull_NoMap)
	PRINT(HashMap_Remove_CheckNull_NoSearchKey)
	PRINT(HashMap_Remove_CheckNull_NoKey)
	PRINT(HashMap_Remove_CheckNull_NoValue)
	PRINT(HashMap_Remove_CheckNotFound)
	PRINT(HashMap_Remove_CheckNotNull)
	PRINT(HashMap_Remove_Check_OutOfTheMap)
	PRINT(HashMap_Remove_Check_CorrectData)
	
	PRINT(HashMap_Find_CheckNull_NoMap)
	PRINT(HashMap_Find_CheckNull_NoKey)
	PRINT(HashMap_Find_CheckNull_NoValue)
	PRINT(HashMap_Find_CheckNotFound)
	PRINT(HashMap_Find_CheckNotNull)
	PRINT(HashMap_Find_Check_NotOutOfTheMap)
	PRINT(HashMap_Find_Check_CorrectData)
	
	PRINT(HashMap_Size_CheckNull_NoMap)
	PRINT(HashMap_Size_Check_CorrectData)
	PRINT(HashMap_Size_CheckCase_Duplicate)
	
	PRINT(HashMap_Print_CheckNull_NoMap)
	PRINT(HashMap_Print_CheckNull_NoFunction)
	#if DEBUG
	PRINT(HashMap_Print_CheckCase_All)
	#endif
	
	PRINT(HashMap_ForEach_CheckNull_NoMap)
	PRINT(HashMap_ForEach_CheckNull_NoFunction)
	PRINT(HashMap_ForEach_CheckCase_All)
	
	PRINT(HashMap_GetStatistics_CheckNull_NoMap)
	PRINT(HashMap_GetStatistics_Check_CorrectData)
END_SET
/*----------------------------------------------------------------------------*/




/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/* 
 * @brief	Function that generate the key 
 * @params  _key		=   The pointer to key varibale
 *				
 * @returns index in which bucket to insert key  	
 */
size_t GenerateKey(void* _key)
{
    return *(size_t*)_key;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Function that check if iterator a key ==  iterator b key
 *
 * @param 	_a			= 	Element to test
 * @param 	_b			= 	Element to test against
 *
 * @return zero OR none zero (1) 
 *
 * @retval	1			=	if _a == _b
 * @retval	0			=	if _a != _b
 */
static int CompareKey(void* _a, void* _b)
{
	return ( *(size_t*)_a  == *(size_t*)_b );
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that change all variables to value of context
 *  
 * @param   _key    	= 	Pointer to key
 * @param   _value    	= 	Pointer to value
 * @param   _context  	= 	The new value of the element
 *
 * @return   -1 		= 	Continue loop for all elements
*/
int	ChangeValueAction(void* _key, void* _value, void* _context)
{
	*(int*)_value = *(int*)_context;
	
	return -1;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function for API: that print all all key-value pairs in the map
 *  
 * @param   _key    	= 	Pointer to key
 * @param   _value    	= 	Pointer to value
 * @param   _context  	= 	The new value of the element
 *
 * @return   -1 		= 	Continue loop for all elements
*/
int	PrintAction(void* _key, void* _value, void* _context)
{
	printf(" (Key: %u, Value: %d),", *(size_t*)_key, *(int*)_value);
	
	return -1;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to array values in sort order 
 *
 * @param   _array		= 	Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = 	The number of elements to insert
 * @param   _step       = 	The range value between each element 
 * @param   _lastValue  = 	The value of the last element
 *
 * @return   void
*/
static void InsertSortedValues(int* _array ,size_t _nElements, int _step, int _lastValue)
{
    while( 0 < _nElements-- )
    {
    	_array[_nElements] = _lastValue;
        _lastValue += _step;
    }
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief	Function that insert to array random values 
 *
 * @param   _array		= 	Pointer to  the elements neeeded to insert to treetor 
 * @param   _nElements  = 	The number of elements to insert
 * @param   _maxValue   = 	The max value the rand() function can prduce, the max value in the treetor
 *
 * @return   void
*/
static void InsertRandValues(int* _array, size_t _nElements, int _maxValue)
{
    while( 0 < _nElements--)
    {
    	_array[_nElements] =  (rand() % _maxValue) - (_maxValue / 2);
    }
    
    return;   
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to hashMap all key-value pairs 
 *
 * @param 	_map		=	Hash map to insert to, must be initialized
 * @param 	_key		=	Key to serve as distinct element 
 * @param 	_value		=	The value to associate with the key
 * @param   _nElements  = 	The number of elements to insert
 *
 * @return	Amount of elements inserted in to the hash map:
 *
 * @retval  Number    	=   On success
 * @retval  0    		=   On failure
*/
static size_t InsertToHash(HashMap* _map, size_t* _key, int* _value, size_t _nElements)
{
    MapResult status;
    size_t counter = 0;
    
    while( 0 < _nElements-- )
    {
    	++counter;
		status = HashMap_Insert(_map, &_key[_nElements], &_value[_nElements]);
		if( MAP_SUCCESS != status )
		{
			return counter;
		}
    }
    
    return counter;
}
/*----------------------------------------------------------------------------*/
