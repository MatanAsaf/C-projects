/** 
 *  @file 		vector.h
 *  @brief 		header file for Generic Vector data type
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

#ifndef __VECTOR_H__
#define __VECTOR_H__
 
#include <stddef.h>  /* size_t */



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct Vector Vector;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef int	(*VectorElementAction)(void* _element, size_t _index, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef enum Vector_Result {
	VECTOR_SUCCESS,
	VECTOR_UNINITIALIZED_ERROR,	/* Uninitialized vector error */
	ITEM_UNINITIALIZED_ERROR,	/* Uninitialized item error */
	VECTOR_ALLOCATION_ERROR,	/* Realloc error on grow/shrink (on shrink this error == VECTOR_SUCCESS) */
	VECTOR_OVERFLOW_ERROR,		/* When needed to do realloc and _blockSize is 0 */
	VECTOR_UNDERFLOW_ERROR,		/* When numOfItems == 0 and trying to remove an element  */
	INDEX_OUT_OF_BOUNDS_ERROR	/* Vector index is out of bounds of the vector 
								(bigger then numOfElement or smaller then 0*/
} VectorResult;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Dynamically create a new vector object of given capacity
 * 
 * @param 	initialCapacity			= Initial capacity, number of elements that can be stored initially
 * @param 	blockSize				= The vector will grow or shrink on demand by this size 
 *
 * @return 	The vector pointer
 * @retval	Vector*					= On success 
 * @retval	NULL 					= On fail 
 *
 * @warning If _blockSize is 0 the vector will be of fixed size. 
 * @warning If both _initialCapacity and _blockSize are zero function will return NULL.
 */
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Dynamically deallocate a previously allocated vector 
 * 
 * @param	vector					= Vector to be deallocated.
 * @params	elementDestroy			= A function pointer to be used to destroy all 
 *								  elements in the vector or a null if no such destroy is required
 *
 * @return void
 */
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item) );
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Add an Item element to the end of the Vector.
 * 
 * @param	vector						= Vector to append integer to.
 * @param	item						= Item element to add.
 *
 * @return	Status VectorResult that indicate in which state the function ended:
 *
 * @retval 	VECTOR_SUCCESS				= On success 
 * @retval 	VECTOR_UNINITIALIZED_ERROR 	= When pointer is uninitialized- *_vector == NULL 
 * @retval 	ITEM_UNINITIALIZED_ERROR 	= When item is uninitialized- 	*_item == NULL
 * @retval 	VECTOR_ALLOCATION_ERROR 	= On allocation error- when realloc function failed 
 * @retval 	VECTOR_OVERFLOW_ERROR 		= When needed to do realloc and _blockSize is 0 
 */
VectorResult VectorAppend(Vector* _vector, void* _item);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Delete an Element from the end of the Vector. 
 * 
 * @param	vector						= Vector to delete integer from.
 * @param	pValue						= Pointer to variable that will receive deleted item value
 *
 * @return	Status VectorResult that indicate in which state the function ended:
 *
 * @retval 	VECTOR_SUCCESS				= On success 
 * @retval 	VECTOR_UNINITIALIZED_ERROR 	= When pointer is uninitialized- *_vector == NULL 
 * @retval 	ITEM_UNINITIALIZED_ERROR 	= When item is uninitialized- 	*_item == NULL
 * @retval 	VECTOR_ALLOCATION_ERROR 	= On allocation error- when realloc function failed 
 * @retval 	VECTOR_UNDERFLOW_ERROR 		= When numOfItems == 0 and trying to remove an element 
 *
 * @warning _item can't be null. this will be assertion violation
 */
VectorResult VectorRemove(Vector* _vector, void** _pValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Get value of item at specific index from the the Vector 
 *
 * @param	vector						= Vector to use.
 * @param	index						= Index of item to get value from. The index of first element is 0.
 * @param	pValue						= pointer to variable that will recieve the item's value.
 *
 * @return	Status VectorResult that indicate in which state the function ended:
 *
 * @retval 	VECTOR_SUCCESS				= On success 
 * @retval 	VECTOR_UNINITIALIZED_ERROR 	= When pointer is uninitialized- *_vector == NULL  
 * @retval 	INDEX_OUT_OF_BOUNDS_ERROR 	= When numOfItems < _index  
 *
 * @warning Index starts from 0.
 */
VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Set an item at specific index to a new value.
 *
 * @param	vector						= Vector to use.
 * @param	index						= Index of an existing item. The index of first element is 0.
 * @param	value						= New value to set.
 *
 * @return	Status VectorResult that indicate in which state the function ended:
 *
 * @retval 	VECTOR_SUCCESS				= On success 
 * @retval 	VECTOR_UNINITIALIZED_ERROR 	= When pointer is uninitialized- *_vector == NULL  
 * @retval 	INDEX_OUT_OF_BOUNDS_ERROR 	= When numOfItems < _index  
 *
 * @warning Index starts from 0.
 */
VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Get the number of actual items currently in the vector.
 *
 * @param	vector			= Vector to use.
 *
 * @return  Number of items 
 *
 * @retval	number			= On success 
 * @retval	0 				= If vector is empty OR pointer is uninitialized- 
 *							*_vector == NULL			
 */
size_t VectorSize(const Vector* _vector);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Get the current capacity of the vector.
 *
 * @param	vector			= Vector to use.
 *
 * @return  Capacity of vector
 *
 * @retval	number			= On success 
 * @retval	0 				= If vector current capacity is 0 OR pointer 
 *							is uninitialized- *_vector == NULL		
 */
size_t VectorCapacity(const Vector* _vector);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Iterate over all elements in the vector.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop. 
 * 
 * @param	vector			= Vector to iterate over.
 * @param	action			= User provided function pointer to be invoked for each element
 * @param	context			= User provided context, will be sent to _action
 *
 * @returns Number of times the user functions was invoked
 */
size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context);
/*----------------------------------------------------------------------------*/

#endif /* __VECTOR_H__ */
