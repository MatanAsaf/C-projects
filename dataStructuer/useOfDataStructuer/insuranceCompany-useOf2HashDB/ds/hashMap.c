/** 
 *  @file 		HashMap.c
 *  @brief 		src file for Generic Hash map of key-value pairs data type
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

#include "hashMap.h" 		/* header file */
#include "list.h" 			/* for listCreate and destroy functions */
#include "listItr.h" 		/* for listItr API functions */
#include "listFunctions.h" 	/* for listItr_ForEach function */
#include "vector.h" 		/* for VectorCreate and destroy functions */
#include <stdlib.h> 		/* for size_t, NULL, malloc, free */
#include <math.h>			/* for sqrt in FindIfPrime function- Needed to add -lm when compile */
#include <stdio.h> 			/* for perror on DEBUG mode */

#define DEBUG		(1)
#define PRIME 		(0)
#define NOT_PRIME 	(1)
#define REMOVE 		(1)
#define CHECK_NULL(param)	do{ if(NULL == (param) ) { return NULL;}  } while(0)
#define CHECK_MAP(param)	do{ if(NULL == (param) ) { return MAP_UNINITIALIZED_ERROR;}  } while(0)
#define CHECK_KEY(param)	do{ if(NULL == (param) ) { return MAP_KEY_NULL_ERROR;}  } while(0)
#define CHECK_ITEM(param)	do{ if(NULL == (param) ) { return MAP_ITEM_NULL_ERROR;}  } while(0)
#define CHECK_ALLOC(param)	do{ if(NULL == (param) ) { return MAP_ALLOCATION_ERROR;}  } while(0)

          
            
/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/                                            
struct HashMap
{
    Vector* m_buckets;               /* The pointer to the Vector data structure */
    size_t m_numOfElements;          /* The total number of elements currently in the hash structure */
    HashFunction m_hashFunc;         /* Function to the key generator to get the index key */     
    EqualityFunction m_keysEqualFunc;/* Function the compare two keys */
};
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/                                            
typedef struct HashElement
{
    void* m_key;	/* The pointer to the key unique identifier of the struct */
    void* m_data;   /* The pointer to the data of the user */
} HashElement;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/                                            
typedef struct ContextBox
{
    void* m_key;	/* The pointer to the key to compare each element to */
    EqualityFunction m_keysEqualFunc;	/* Function the compare two keys */
} ContextBox;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef void (*keyDestroy)(void* _key);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef void (*valDestroy)(void* _value);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/                                            
typedef struct ContextDestroy
{
    keyDestroy m_keyDestroyFunc;	/* Function the destroy keys */
    valDestroy m_valDestroyFunc;	/* Function the destroy values */
} ContextDestroy;
/*----------------------------------------------------------------------------*/





/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function find the first prime number that is >= num  
 *
 * @param[in] 	_num					= 	First number to start from
 *
 * @return 		The first prime number that is >= num  
 */
static size_t FindNearstPrime(size_t _num);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function find the if the number is a prime number 
 *
 * @param[in] 	_num					= 	Number to test
 *
 * @return 		The status PRIME or NOT_PRIME
 */
static size_t FindIfPrime(size_t _num);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function Initialize all buckets in the vector with List*
 *
 * @param[in] 	_newHash				= 	Pointer to existing hash map after it created
 *
 * @return 		The hash map pointer 
 *
 * @retval 		On success    			=   The same pointer to the created hash map.
 * @retval  	NULL          			=   On failure due to unsuccessful initialize buckets
 */
static HashMap* InitBuckets(HashMap* _newHash);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Action function to destroy on each element in the list
 *
 * @param[in] 	element					= 	Element to test
 * @param[in]	context					= 	Context to be used
 *
 * @return 		-1
 */
static int DestroyElementAction(void* _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function find the right bucket to insert key in to it, according to hashFunc
 *
 * @param[in] 	_map					= 	Pointer to existing hash map after it created
 * @param[in] 	_key					= 	Pointer to key hash to calculate index
 *
 * @return 		The bucket index (unique list) to insert the element 
 */
static size_t FindBucket(const HashMap* _map,  void* _key);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Action function to operate on an element in the list
 *
 * @param[in] 	element					= 	Element to test
 * @param[in]	context					= 	Context to be used
 *
 * @return 		Zero if both element are equals, Otherwise 1
 */
static int CompareKeysAction(void* _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function search all elements in the right bucket to find key duplicate
 *
 * @param[in] 	_map					= 	Pointer to existing hash map after it created
 * @param[in] 	_index					= 	The bucket index on the vector that store the unique list
 * @param[in] 	_key					= 	Pointer to unique key to compare with each element
 * @param[in] 	_decision				= 	Status that indicate if to remove the founded element (if found)
 * @param[out] 	_pItr					= 	Pointer to return the element founded in the list (if found)
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_KEY_DUPLICATE_ERROR	=	When key already present in the map
 * @retval  	MAP_KEY_NOT_FOUND_ERROR	=	When key not found in the map
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to internal errors- only on DEBUG mode
 * @retval  	MAP_ALLOCATION_ERROR    =   Allocation error when creating structure for searching the key 
 */
static MapResult SearchKey(const HashMap* _map, size_t _index, void* _key, int _decision, void** _pItr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function insert new element in to the right list at the end of the list
 *
 * @param[in] 	_map					= 	Pointer to existing hash map after it created
 * @param[in] 	_index					= 	The bucket index on the vector that store the unique list
 * @param[in] 	_key					= 	Pointer to unique key in the element structure
 * @param[in] 	_value					= 	Pointer to date in the element structure
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_SUCCESS    			=   On success
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to internal errors- only on DEBUG mode
 * @retval  	MAP_ALLOCATION_ERROR    =   Allocation error when creating new element 
 */
static MapResult InsertValue(const HashMap* _map, size_t _index, void* _key, void* _value);
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       Create a new hash map with given capacity and key characteristics.
 *
 * @param[in]   _capacity       		=   Expected max capacity 
 * 						            		Will be rounded to nearest larger prime number.
 * @param[in]   _hashFunc       		=   Hashing function for keys
 * @param[in]   _keysEqualFunc  		=   Equality check function for keys. 
 *
 * @return 		The hash map pointer 
 *
 * @retval 		On success    			=   A pointer to the created hash map.
 * @retval  	NULL          			=   On failure due to allocation failure OR uninitialized pointers
 *
 * @warning 	Capacity must be > 0
 */
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap* newHash;
    
    CHECK_NULL(_hashFunc);
    CHECK_NULL(_keysEqualFunc);
    if( 0 == _capacity )
    {
        return NULL;
    }
    
    /* rounded to nearest larger prime number */
    _capacity = FindNearstPrime(_capacity);
    
    newHash = (HashMap*)malloc( sizeof(HashMap) ); 
    CHECK_NULL(newHash);
    
    newHash->m_buckets = VectorCreate(_capacity, 0); 
    if( NULL == (newHash->m_buckets) )
    {
        free(newHash);
        return NULL;
    }
    
    newHash->m_numOfElements = 0;
    newHash->m_hashFunc = _hashFunc;
    newHash->m_keysEqualFunc = _keysEqualFunc;
    
    /* Initialize all buckets and return the pointer if successful */
    return InitBuckets(newHash);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**
 * @brief 		Destroy hash map and set *_map to null
 * @details 	Has the option to destroy all keys and values using user provided functions
 *
 * @param[in] 	_map					= 	Map to be destroyed
 * @param[in] 	_keyDestroy				= 	Pointer to function to destroy keys
 * @param[in] 	_valDestroy				= 	Pointer to function to destroy values 
 *
 * @return 		void
 */
void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value) )
{	
	List* currentList;
	ContextDestroy* newContext;
	ListItr beginItr;
	ListItr endItr;
	size_t capacity;
	size_t i;
	
	if( NULL == _map || NULL == *_map )
    {
        return;
    }

	capacity = VectorCapacity( ( *(_map) )->m_buckets );
	
	if( NULL != _keyDestroy || NULL != *_valDestroy )
    {
    	/* create struct to send to function: */
		newContext = (ContextDestroy*)malloc( sizeof(ContextDestroy) ); 
		if(NULL == newContext)
		{
			return;
		}
	
		newContext->m_keyDestroyFunc = _keyDestroy;	
		newContext->m_valDestroyFunc = _valDestroy;
		
		for( i = 0; i < capacity; ++i)
		{
			VectorRemove( ( *(_map) )->m_buckets, (void*)&currentList );
			beginItr = ListItrBegin(currentList);
			endItr = ListItrEnd(currentList);
			ListItr_ForEach(beginItr, endItr, DestroyElementAction, newContext);
			ListDestroy(&currentList, NULL);
		}
		
		free(newContext);
    }
    else
    {
    	for( i = 0; i < capacity; ++i)
		{
			VectorRemove( ( *(_map) )->m_buckets, (void*)&currentList );
			ListDestroy(&currentList, NULL);
		}
    }
	
	VectorDestroy( &( ( *(_map) )->m_buckets), NULL);
	
	free(*_map);
    *_map = NULL;
    
	return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Adjust map capacity and rehash all key/value pairs
 * @details		Adjust map capacity so it can now have different size of buckets to stored key/value pairs
 *
 * @param[in] 	_map					= 	Existing map
 * @param[in] 	_newCapacity			= 	New capacity size
 * 						          			Will be rounded to nearest larger prime number.
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_SUCCESS    			=   On success
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to uninitialized map pointer OR newCapacity
 * @retval  	MAP_ALLOCATION_ERROR    =   On failure due to allocation failure 
 *
 * @warning 	newCapacity must be > 0
 */
MapResult HashMap_Rehash(HashMap *_map, size_t newCapacity)
{
	return MAP_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Insert a key-value pair into the hash map.
 *
 * @param[in] 	_map					=	Hash map to insert to, must be initialized
 * @param[in] 	_key					=	Key to serve as distinct element 
 * @param[in] 	_value					=	The value to associate with the key
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_SUCCESS    			=   On success
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to uninitialized map pointer
 * @retval  	MAP_KEY_NULL_ERROR		=	On failure due to uninitialized key pointer
 * @retval  	MAP_ALLOCATION_ERROR    =   On failure due to allocation key-value pair failure 
 * @retval  	MAP_KEY_DUPLICATE_ERROR	=	On failure due to key already present in the map
 * 
 * @warning 	Key must be unique and distinct
 */
MapResult HashMap_Insert(HashMap* _map,  void* _key,  void* _value)
{
	size_t bucketIndex;
	MapResult status;
	
	CHECK_MAP(_map);
	CHECK_KEY(_key);

	bucketIndex = FindBucket(_map, _key);
	
	/* find the position of this _key on the list if it found */
	status = SearchKey(_map, bucketIndex, _key, 0, NULL);
	if( MAP_KEY_NOT_FOUND_ERROR != status )
	{
		return status;
	}
	
	status = InsertValue(_map, bucketIndex, _key, _value); 
	if( MAP_SUCCESS == status )
	{
		++(_map->m_numOfElements);
	}
	
	return status;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove a key-value pair from the hash map.
 *
 * @param[in]   _map					=	Hash map to remove pair from, must be initialized
 * @param[in]   _searchKey				=	Key to to search for in the map
 * @param[out]  _pKey					=	Pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out]  _pValue					=	Pointer to variable that will get the value stored in the map corresponding to foind key
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_SUCCESS    			=   On success
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to uninitialized map pointer
 * @retval  	MAP_KEY_NULL_ERROR		=	On failure due to uninitialized key pointer
 * @retval  	MAP_ITEM_NULL_ERROR		=	On failure due to uninitialized pValue OR pKey pointer
 * @retval  	MAP_KEY_NOT_FOUND_ERROR	=	On failure due to key not found in the map
 * @retval  	MAP_ALLOCATION_ERROR    =   On failure due to allocation error when searching the key 
 * 
 * @warning 	Key must be unique and distinct
 */
MapResult HashMap_Remove(HashMap* _map,  void* _searchKey, void** _pKey, void** _pValue)
{
    size_t bucketIndex;
    MapResult status;
    HashElement* pBox; 

    CHECK_MAP(_map);
	CHECK_KEY(_searchKey);
	CHECK_ITEM(_pKey);
	CHECK_ITEM(*_pKey);
	CHECK_ITEM(_pValue);
	CHECK_ITEM(*_pValue);
	
    bucketIndex = FindBucket(_map, _searchKey);

    /* find the position of this _key on the list if it found */
    status = SearchKey(_map, bucketIndex, _searchKey, REMOVE, (void*)&pBox);
    if( MAP_KEY_DUPLICATE_ERROR != status )
    {
	    return status;
    }
   
    *_pKey = pBox->m_key;
    *_pValue = pBox->m_data;
    
    --(_map->m_numOfElements);
    
    return MAP_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Find a value by key
 *
 * @param[in] 	_map					=	Hash map to use, must be initialized
 * @param[in] 	_searchKey				=	Key to serve as distinct element to search according to it
 * @param[out] 	_pValue					=	Pointer to variable that will get the value associated with the search key.
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_SUCCESS    			=   On success
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to uninitialized map pointer
 * @retval  	MAP_KEY_NULL_ERROR		=	On failure due to uninitialized key pointer
 * @retval  	MAP_ITEM_NULL_ERROR		=	On failure due to uninitialized pValue OR pKey pointer
 * @retval  	MAP_KEY_NOT_FOUND_ERROR	=	On failure due to key not found in the map
 * @retval  	MAP_ALLOCATION_ERROR    =   On failure due to allocation error when searching the key
 * 
 * @warning 	Key must be unique and distinct
 */
MapResult HashMap_Find(const HashMap* _map, void* _searchKey, void** _pValue)
{
	size_t bucketIndex;
    MapResult status;
    HashElement* pBox; 

    CHECK_MAP(_map);
	CHECK_KEY(_searchKey);
	CHECK_ITEM(_pValue);
	CHECK_ITEM(*_pValue);
	
    bucketIndex = FindBucket(_map, _searchKey);

    /* find the position of this _key on the list if it found */
    status = SearchKey(_map, bucketIndex, _searchKey, 0, (void*)&pBox);
    if( MAP_KEY_DUPLICATE_ERROR != status )
    {
	    return status;
    }

    *_pValue = pBox->m_data;
    
    return MAP_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**
 * @brief 		Get number of key-value pairs inserted into the hash map
 * @Complexity	O(1)
 *
 * @param[in] 	_map					=	Hash map to use, must be initialized
 *
 * @return		Amount of elements in the hash map:
 *
 * @retval  	0    					=   On failure due to uninitialized map pointer OR 
 *											On success with empty hash
 * @retval  	Number    				=   On success without empty hash
 */
size_t HashMap_Size(const HashMap* _map)
{
	if( NULL == _map)
	{
		return 0;
	}
	
	return (_map->m_numOfElements);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Iterate over all key-value pairs in the map and call a function for each pair
 * @details 	The user provided KeyValueActionFunction will be called for each element.  
 * 				Iteration will stop if the called function returns a zero for a given pair
 * 
 * @param[in]	_map					=	Hash map to iterate over.
 * @param[in] 	_action					=	User provided function pointer to be invoked for each element
 * @param[in] 	_context				=	User provided element pointer to be invoked for each element
 *
 * @returns 	Number of times the user functions was invoked:
 *
 * @retval  	0    					=   On failure due to uninitialized one of the pointers OR 
 *											On success with empty hash
 * @retval  	Number    				=   On success without empty hash
 */
size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	List* currentList = (List*)10;
	ListItr currentItr;
	ListItr endItr;
	HashElement* currentElement;
	size_t nBuckets;
	size_t counter = 0;
	
	if( NULL == _map || NULL == _action )
	{
		return 0;
	}
	
	nBuckets = VectorCapacity(_map->m_buckets);
	
	while( 0 < nBuckets-- )
	{
		VectorGet(_map->m_buckets, nBuckets, (void*)&currentList);
		currentItr = ListItrBegin(currentList);
		endItr = ListItrEnd(currentList);
		
		while( endItr != currentItr )
		{
			++counter;
			currentElement = ListItrGet(currentItr);
			if( 0 == _action(currentElement->m_key, currentElement->m_data, _context) )
			{
				return counter;
			}
			
			currentItr = ListItrNext(currentItr);
		}
	}
	
	return counter;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Get Information on the current status of the hash map 
 * @details 	This Function provide MapStats structure (that mention under Define Declaration section above)
 *				with members that gather information on the current status of the hash map.
 * 
 * @param[in]	_map					=	Hash map to iterate over.
 *
 * @returns 	Number of times the user functions was invoked:
 *
 * @retval 		On success    			=   A pointer to the created MapStats structure.
 * @retval  	NULL          			=   On failure due to allocation failure OR uninitialized pointer
 *
 * @warning 	The function do not free created MapStats structure- It's the user responsibility to free it. 
 * @warning 	Each time the user call this Function it create a new MapStats structure
 */
MapStats* HashMap_GetStatistics(const HashMap* _map)
{
	MapStats* newStats;
	List* currentList = (List*)10;
	size_t nBuckets;
	size_t nElements;
	
	CHECK_NULL(_map);
	
	newStats = (MapStats*)calloc( 1, sizeof(MapStats) ); 
	CHECK_NULL(newStats);
	
	nBuckets = VectorCapacity(_map->m_buckets);
	
	newStats->m_numberOfBuckets = nBuckets;
	newStats->m_averageChainLength = ( (_map->m_numOfElements) / nBuckets );
	
	while( 0 < nBuckets-- )
	{
		VectorGet(_map->m_buckets, nBuckets, (void*)&currentList);
		nElements = ListSize(currentList);
		if( 0 == nElements )
		{
			continue;
		}
		
		if( (newStats->m_maxChainLength) < nElements )
		{
			newStats->m_maxChainLength = nElements;
			newStats->m_maxChainLengthIndex = nBuckets;
		}
		
		++( newStats->m_numberOfChains );
	}
	
	return newStats;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Iterate over all key-value pairs in the map and call a print function for each pair
 * @details 	The user provided KeyValueActionFunction for print the elements, 
 *				the function will print the bucket itself.  
 * 				Iteration will stop if the called function returns a zero for a given pair
 * 
 * @param[in]	_map					=	Hash map to iterate over.
 * @param[in] 	_action					=	User provided print function pointer to be invoked for each element
 * @param[in] 	_context				=	User provided element pointer to be invoked for each element
 *
 * @returns 	Number of times the user functions was invoked:
 *
 * @retval  	0    					=   On failure due to uninitialized one of the pointers OR 
 *											On success with empty hash
 * @retval  	Number    				=   On success without empty hash
 */
size_t HashMap_Print(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	List* currentList = (List*)10;
	ListItr currentItr;
	ListItr endItr;
	HashElement* currentElement;
	size_t nBuckets;
	size_t counter = 0;
	
	if( NULL == _map || NULL == _action )
	{
		return 0;
	}
	
	nBuckets = VectorCapacity(_map->m_buckets);
	
	while( 0 < nBuckets-- )
	{
		printf("\nBucket[%u] = { ", nBuckets);
		VectorGet(_map->m_buckets, nBuckets, (void*)&currentList);
		currentItr = ListItrBegin(currentList);
		endItr = ListItrEnd(currentList);
		
		while( endItr != currentItr )
		{
			++counter;
			currentElement = ListItrGet(currentItr);
			if( 0 == _action(currentElement->m_key, currentElement->m_data, _context) )
			{
				return counter;
			}
			
			currentItr = ListItrNext(currentItr);
		}
		printf(" }\n");
	}
	
	return counter;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function find the first prime number that is >= num  
 *
 * @param[in] 	_num					= 	First number to start from
 *
 * @return 		The first prime number that is >= num  
 */
static size_t FindNearstPrime(size_t _num)
{
    while(NOT_PRIME == FindIfPrime(_num))
    {
        ++_num;
    }
    
    return _num;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function find the if the number is a prime number 
 *
 * @param[in] 	_num					= 	Number to test
 *
 * @return 		The status PRIME or NOT_PRIME
 */
static size_t FindIfPrime(size_t _num)
{
	size_t i = 2;
	size_t root = (size_t)sqrt( (float)_num );
	
	while(i <= root) 
	{
		if( 0 == ( _num % i++ )  ) 
		{
			return NOT_PRIME;
		}
	}
	
	return PRIME;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function Initialize all buckets in the vector with List*
 *
 * @param[in] 	_newHash				= 	Pointer to existing hash map after it created
 *
 * @return 		The hash map pointer 
 *
 * @retval 		On success    			=   The same pointer to the created hash map.
 * @retval  	NULL          			=   On failure due to unsuccessful initialize buckets
 */
static HashMap* InitBuckets(HashMap* _newHash)
{
	List* newList;
	size_t capacity = VectorCapacity(_newHash->m_buckets);
	size_t i;
	
	for(i = 0; i < capacity; ++i)
	{
		newList = ListCreate();
		if( NULL == newList )
		{
			break;
		}
		
		if( VECTOR_SUCCESS != VectorAppend(_newHash->m_buckets, newList) )
		{
			ListDestroy(&newList, NULL);
			break;
		}
	}
	
	if( i == capacity )
	{
		return _newHash;	
	} 
	
	/* If Allocation failure then needed to do cleanup and free all */
	for( ; i > 0; --i)
	{
		VectorRemove( _newHash->m_buckets, (void*)&newList );
		ListDestroy(&newList, NULL);
	}
	
	VectorDestroy( &(_newHash->m_buckets), NULL);
	free(_newHash);
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Action function to destroy on each element in the list
 *
 * @param[in] 	element					= 	Element to test
 * @param[in]	context					= 	Context to be used
 *
 * @return 		-1
 */
static int DestroyElementAction(void* _element, void* _context)
{
	HashElement* dataBox = (HashElement*)ListItrGet( (ListItr)(_element) );
	ContextDestroy* destroyBox = (ContextDestroy*)(_context);
	
	if( NULL != (destroyBox->m_keyDestroyFunc) )
	{
		(destroyBox->m_keyDestroyFunc)(dataBox->m_key);
	} 
	
	if( NULL != (destroyBox->m_valDestroyFunc) )
	{
		(destroyBox->m_valDestroyFunc)(dataBox->m_data);
	}
	
	return -1;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function find the right bucket to insert key in to it, according to hashFunc
 *
 * @param[in] 	_map					= 	Pointer to existing hash map after it created
 * @param[in] 	_key					= 	Pointer to key hash to calculate index
 *
 * @return 		The bucket index (unique list) to insert the element 
 */
static size_t FindBucket(const HashMap* _map,  void* _key)
{
	size_t userBucketIndex = _map->m_hashFunc(_key);
	size_t capacity = VectorCapacity(_map->m_buckets );
	
	return (userBucketIndex % capacity);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Action function to operate on an element in the list
 *
 * @param[in] 	element					= 	Element to test
 * @param[in]	context					= 	Context to be used
 *
 * @return 		Zero if both element are equals, Otherwise 1
 */
static int CompareKeysAction(void* _element, void* _context)
{
	HashElement* dataBox = (HashElement*)ListItrGet( (ListItr)(_element) );
	ContextBox* contextBox = (ContextBox*)(_context);
	int decision;
	
	decision = (contextBox->m_keysEqualFunc)( contextBox->m_key, dataBox->m_key );
	
	/* If both keys are equals (equals == 1) stop the loop: */
	if( 0 != decision)
	{
		return 0;
	}
	
	return 1;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function search all elements in the right bucket to find key duplicate
 *
 * @param[in] 	_map					= 	Pointer to existing hash map after it created
 * @param[in] 	_index					= 	The bucket index on the vector that store the unique list
 * @param[in] 	_key					= 	Pointer to unique key to compare with each element
 * @param[in] 	_decision				= 	Status that indicate if to remove the founded element (if found)
 * @param[out] 	_pItr					= 	Pointer to return the element founded in the list (if found)
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_KEY_DUPLICATE_ERROR	=	When key already present in the map
 * @retval  	MAP_KEY_NOT_FOUND_ERROR	=	When key not found in the map
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to internal errors- only on DEBUG mode
 * @retval  	MAP_ALLOCATION_ERROR    =   Allocation error when creating structure for searching the key 
 */
static MapResult SearchKey(const HashMap* _map, size_t _index, void* _key, int _decision, void** _pItr)
{
	List* myList;
	ListItr beginItr;
	ListItr endItr;
	ListItr foundItr;
	ContextBox* newContext;
	
	if( VECTOR_SUCCESS != VectorGet(_map->m_buckets, _index, (void*)&myList) )
	{
		#if DEBUG
			perror("SearchKey function Error: On VectorGet\n");
		#endif
		return MAP_UNINITIALIZED_ERROR;
	}
	
	/* create struct to send to function: */
	newContext = (ContextBox*)malloc( sizeof(ContextBox) ); 
	CHECK_ALLOC(newContext);
	
	newContext->m_key = _key;
	newContext->m_keysEqualFunc = _map->m_keysEqualFunc;
	
	beginItr = ListItrBegin(myList);
	endItr = ListItrEnd(myList);

	foundItr = ListItr_ForEach(beginItr, endItr, CompareKeysAction, newContext);
	
	free(newContext);
	
	if( NULL == foundItr )
	{
		#if DEBUG
			perror("SearchKey function Error: On ListItr_ForEach.\nUninitialized\n");
		#endif
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(endItr == foundItr)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	if(NULL != _pItr)
	{
		*_pItr = ListItrGet(foundItr);
	}
	
	if(REMOVE == _decision)
	{
		ListItrRemove(foundItr);
	}
	
	return MAP_KEY_DUPLICATE_ERROR;
	
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Function insert new element in to the right list at the end of the list
 *
 * @param[in] 	_map					= 	Pointer to existing hash map after it created
 * @param[in] 	_index					= 	The bucket index on the vector that store the unique list
 * @param[in] 	_key					= 	Pointer to unique key in the element structure
 * @param[in] 	_value					= 	Pointer to date in the element structure
 *
 * @return		Status MapResult that indicate in which state the function ended:
 *
 * @retval  	MAP_SUCCESS    			=   On success
 * @retval  	MAP_UNINITIALIZED_ERROR =   On failure due to internal errors- only on DEBUG mode
 * @retval  	MAP_ALLOCATION_ERROR    =   Allocation error when creating new element 
 */
static MapResult InsertValue(const HashMap* _map, size_t _index, void* _key, void* _value)
{
	List* myList;
	ListItr endItr;
	ListItr newItr;
	HashElement* dataBox;
	
	if( VECTOR_SUCCESS != VectorGet(_map->m_buckets, _index, (void*)&myList) )
	{
		#if DEBUG
			perror("InsertValue function Error: On VectorGet\n");
		#endif
		return MAP_UNINITIALIZED_ERROR;
	}
	
	endItr = ListItrEnd(myList);
	if( NULL == endItr )
	{
		#if DEBUG
			perror("InsertValue function Error: On ListItrEnd.\nUninitialized\n");
		#endif
		return MAP_UNINITIALIZED_ERROR;
	}
	
	dataBox = (HashElement*)malloc( sizeof(HashElement) );	
	CHECK_ALLOC(dataBox);
	
	dataBox->m_data = _value;
	dataBox->m_key = _key;
	
	newItr = ListItrInsertBefore(endItr, dataBox);
	if(NULL == newItr)
	{
		#if DEBUG
			perror("InsertValue function Error: On ListItrInsertBefore.\nAllocation error when insert to list\n");
		#endif
		free(dataBox);
		return MAP_ALLOCATION_ERROR;	
	}
	
	return MAP_SUCCESS;
}
/*----------------------------------------------------------------------------*/
