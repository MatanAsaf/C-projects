/** 
 *  @file 		HashMap.h
 *  @brief 		header file for Generic Hash map of key-value pairs data type
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

#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <stddef.h>  /* size_t */



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct HashMap HashMap;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef enum Map_Result 
{
	MAP_SUCCESS = 0,
	MAP_UNINITIALIZED_ERROR,	/* Uninitialized map error 	*/
	MAP_KEY_NULL_ERROR, 		/* Uninitialized key error  */
	MAP_ITEM_NULL_ERROR, 		/* Uninitialized item error  */
	MAP_KEY_DUPLICATE_ERROR, 	/* Duplicate key error 		*/
	MAP_KEY_NOT_FOUND_ERROR, 	/* Key not found 			*/
	MAP_ALLOCATION_ERROR 		/* Allocation error 	 	*/
} MapResult;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef struct Map_Stats {
	size_t m_numberOfBuckets;    	/* Empty + not empty buckets */
	size_t m_numberOfChains;     	/* None empty chains (With non zero elements) */
	size_t m_maxChainLength;     	/* Length of longest chain */
	size_t m_maxChainLengthIndex;	/* Index for longest chain */
	size_t m_averageChainLength; 	/* Average length of none empty chains */
} MapStats;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef size_t (*HashFunction)(const void* _key);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef int (*EqualityFunction)(const void* _firstKey, const void* _secondKey);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef int	(*KeyValueActionFunction)(const void* _key, void* _value, void* _context);
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
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);
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
void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
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
MapResult HashMap_Rehash(HashMap *_map, size_t newCapacity);
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
MapResult HashMap_Insert(HashMap* _map, const void* _key, const void* _value);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove a key-value pair from the hash map.
 *
 * @param[in]   _map					=	Hash map to remove pair from, must be initialized
 * @param[in]   _searchKey				=	Key to to search for in the map
 * @param[out]  _pKey					=	Pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out]  _pValue					=	Pointer to variable that will get the value stored in the map corresponding to found key
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
MapResult HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue);
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
MapResult HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue);
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
size_t HashMap_Size(const HashMap* _map);
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
size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context);
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
MapStats* HashMap_GetStatistics(const HashMap* _map);
/*----------------------------------------------------------------------------*/


#endif /* __HASH_MAP_H__ */

