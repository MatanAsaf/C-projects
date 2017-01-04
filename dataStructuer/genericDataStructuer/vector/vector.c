/** 
 *  @file 		vector.c
 *  @brief 		src file for Generic Vector data type
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

 
#include "vector.h"			/* header file */
#include <stdlib.h>  		/* size_t &malloc */

#define CHECK_NULL(param)			do{ if(NULL == (param) ) { return NULL;}  } while(0)
#define CHECK_VECTOR_NULL(param)	do{ if(NULL == (param) ) { return VECTOR_UNINITIALIZED_ERROR;}  } while(0)
#define CHECK_ITEM_NULL(param)		do{ if(NULL == (param) ) { return ITEM_UNINITIALIZED_ERROR;}  } while(0)
#define CHECK_ALLOCATION(error)		do{ if(NULL == (error) ) { return VECTOR_ALLOCATION_ERROR;}  } while(0)
#define CHECK_ERROR(error)			do{ if(VECTOR_SUCCESS != (error) ) { return (error);}  } while(0)
#define CHECK_UNDERFLOW(error)		do{ if(VECTOR_SUCCESS != (error) ) { return VECTOR_UNDERFLOW_ERROR;}  } while(0)
#define GAP_OF_DISCREASE_REALLOC (2)


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
struct Vector
{
    void** m_items;
    size_t m_originalCapacity; 	/* The original size that the user asked for  */
    size_t m_capacity; 			/* The current size of the structuer */
    size_t m_numOfItems; 		/* The current number of Items in the structuer */
    size_t m_blockSize; 		/* The size of block when we need increse the structuer  */
};
/*----------------------------------------------------------------------------*/





/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/* Check if needed to increse capacity of vector
 */
static VectorResult CheckIncRealloc(Vector* _vector);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Check if needed to discrese capacity of vector
 */
static VectorResult CheckDisRealloc(Vector* _vector);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Resize the capacity of vector
 */
static void** resizeVector(Vector* _vector, size_t _newSize);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Check if the index the user sent is in bound of current elements in the vector
 */
static VectorResult CheckIndex(const Vector* _vector, size_t _index);
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
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
    Vector* vec;
    /* If the user ask for vector of size 0 and doesn't want it the increse in the future- then there is no need in create a vector */
    if( 0 == _initialCapacity && 0 == _blockSize )
    {
        return NULL;  
    }
    
    vec = (Vector*) malloc( sizeof(Vector) );
    CHECK_NULL(vec);
    
    vec->m_items = (void**)malloc( _initialCapacity * sizeof(void*) );
    if( NULL == (vec->m_items) )
    {
        free((void*)vec);
        return NULL;
    }
    
    vec->m_originalCapacity = _initialCapacity;
    vec->m_capacity = _initialCapacity;
    vec->m_numOfItems = 0;
    vec->m_blockSize = _blockSize;

    return vec;
}
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
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item) )
{
    size_t i;
    size_t elementCounter;
    
    if(NULL == _vector || NULL == *_vector)  
    {
        return;
    }
    
    if( NULL != (*_elementDestroy) )
    {
        elementCounter = (*_vector)->m_numOfItems;
        
        for(i = 0; i < elementCounter; ++i)
        {
            (*_elementDestroy)( (*_vector)->m_items[i] );
        }
    }
    
    free((*_vector)->m_items);
    free(*_vector);
    *_vector = NULL;
    return;
}
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
VectorResult VectorAppend(Vector* _vector, void* _item)
{
    VectorResult error;
    
    CHECK_VECTOR_NULL(_vector);
    CHECK_ITEM_NULL(_item);
    
    error = CheckIncRealloc(_vector);
    CHECK_ERROR(error);
    
    _vector->m_items[_vector->m_numOfItems++] = _item;
    return VECTOR_SUCCESS;
}
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
VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
    VectorResult error;
    
    CHECK_VECTOR_NULL(_vector);
    CHECK_ITEM_NULL(_pValue);
    CHECK_ITEM_NULL(*_pValue);
    
    error = CheckIndex(_vector, _vector->m_numOfItems - 1);
    if(VECTOR_SUCCESS != error)
    {
    	return VECTOR_UNDERFLOW_ERROR;
    }
    
    *_pValue = (_vector->m_items)[--_vector->m_numOfItems];
    
    error = CheckDisRealloc(_vector);
    CHECK_ERROR(error);
    
    return VECTOR_SUCCESS;
}
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
VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
    VectorResult error;
    const Vector* vec2;
    
    CHECK_VECTOR_NULL(_vector);
    CHECK_ITEM_NULL(_pValue);
    CHECK_ITEM_NULL(*_pValue);
    
    vec2 = _vector;
    
    error = CheckIndex(vec2, _index);
    CHECK_ERROR(error);
     
    *_pValue = (_vector->m_items)[_index];
    
    return VECTOR_SUCCESS;
}
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
VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
    VectorResult error;
    
    CHECK_VECTOR_NULL(_vector);
    CHECK_ITEM_NULL(_value);
    
    error = CheckIndex(_vector, _index);
    CHECK_ERROR(error);
     
    (_vector->m_items)[_index] = _value;
    
    return VECTOR_SUCCESS;
}
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
size_t VectorSize(const Vector* _vector)
{
    if(NULL == _vector)
    {
    	return 0;
    } 
    
    return (_vector->m_numOfItems);
}
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
size_t VectorCapacity(const Vector* _vector)
{
    if(NULL == _vector)
    {
    	return 0;
    }
    
    return (_vector->m_capacity);
}
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
size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
    int desicion;
    size_t i;
    size_t elementCounter;
    
    if( NULL == _vector || NULL == _action)
    {
    	return 0;
    }
    
    elementCounter = _vector->m_numOfItems;
    
    for(i = 0; i < elementCounter; ++i)
    {
        desicion = _action((_vector->m_items)[i], i, _context);
        
        if(0 == desicion)
        {
            return i;
        }
    }
    
    return i;    
}
/*----------------------------------------------------------------------------*/






/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/* Check if needed to increse capacity of vector
 */
static VectorResult CheckIncRealloc(Vector* _vector)
{
    void** temp;
    size_t newCapacity;
    
    if( _vector->m_numOfItems == _vector->m_capacity )
    {
        if( 0 == _vector->m_blockSize )
        {
            return VECTOR_OVERFLOW_ERROR;
        }
        
        newCapacity = (_vector->m_capacity) + (_vector->m_blockSize);
        temp = resizeVector(_vector, newCapacity );
        CHECK_ALLOCATION(temp);
        
        _vector->m_items = temp;
        _vector->m_capacity += (_vector->m_blockSize);
    }
    
    return VECTOR_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Check if needed to discrese capacity of vector 
 */
static VectorResult CheckDisRealloc(Vector* _vector)
{   
    void** temp;
    size_t newCapacity;
     
    if( ( _vector->m_capacity > _vector->m_originalCapacity ) && ( ((_vector->m_capacity) - (_vector->m_numOfItems)) >= (GAP_OF_DISCREASE_REALLOC * _vector->m_blockSize) ) )
    {
        newCapacity = (_vector->m_capacity) - (_vector->m_blockSize);
        temp = resizeVector(_vector, newCapacity );
        CHECK_ALLOCATION(temp); /* Error, But still the remove has done */ 
        
        _vector->m_items = temp;
        _vector->m_capacity -= (_vector->m_blockSize); 
    }
    
    return VECTOR_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Resize the capacity of vector 
 */
static void** resizeVector(Vector* _vector, size_t _newSize)
{
    void** newPtr;
    
    newPtr = realloc( _vector->m_items, _newSize * sizeof(int) );
    
    return newPtr;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Check if the index the user sent is in bound of current elements in the vector  
 */
static VectorResult CheckIndex(const Vector* _vector, size_t _index)
{
    if( 0 == _vector->m_numOfItems || _index >= _vector->m_numOfItems)
    {
        return INDEX_OUT_OF_BOUNDS_ERROR;
    }
    
    return VECTOR_SUCCESS;
}
/*----------------------------------------------------------------------------*/
