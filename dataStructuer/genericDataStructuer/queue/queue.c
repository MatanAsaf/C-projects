/** 
 *  @file 		queue.c
 *  @brief 		src file for Generic Queue data type
 * 
 *  @details 	The API stores pointer to user provided elements of generic type.
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
 
#include "queue.h"		/* header file */
#include <stdlib.h> 	/* for size_t & calloc & malloc */

#define CHECK_NULL(var)				do{ if(NULL == (var) ) { return NULL;}  } while(0)
#define CHECK_QUEUE_NULL(param)		do{ if(NULL == (param) ) { return QUEUE_UNINITIALIZED_ERROR;}  } while(0)
#define CHECK_ITEM_NULL(param)		do{ if(NULL == (param) ) { return ITEM_UNINITIALIZED_ERROR;}  } while(0)




/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
struct Queue
{
    void** m_items;			/* Pointer to the actual items */
    size_t m_capacity; 		/* The size of the structuer */
    size_t m_head; 			/* Index to the first message to remove from the structuer */
    size_t m_tail; 			/* Index to the last message that insert to the structuer */
    size_t m_numOfElements; /* The current number of message in the structuer */
};
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function create a new queue and return the memory
 * @details     With the capacity the user sent as size the function create a new 
 *				queue and return the pointer to it.
 *
 * @param       _initialCapacity 	=   Number of elements that can be stored initially
 *
 * @return		The orignal memory buffer OR NULL at error
 *
 * @retval		NULL				= 	On error when initalize
 * @retval 		_myQueue			=	On success
 */
Queue* QueueCreate(size_t _initialCapacity)
{
	Queue* myQueue;
	
	if( 0 == _initialCapacity)
	{
		return NULL;
	}
	
	myQueue = (Queue*)calloc( 1, sizeof(Queue) );
	CHECK_NULL(myQueue);
	
	myQueue->m_items = malloc( _initialCapacity * sizeof(Queue*) );
	if( NULL == myQueue->m_items)
	{
		free(myQueue->m_items);
		return NULL;
	}
	
	myQueue->m_capacity = _initialCapacity;
	
	return myQueue;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 		Dynamically deallocate a previously allocated Queue 
 * 
 * @param	 	_Queue				= 	Queue to be deallocated.
 * @params	 	_elementDestroy		= 	A function pointer to be used to destroy 
 *										all elements in the vector or a null if no 
 *										such destroy is required
 * @return void
 */
void QueueDestroy(Queue** _myQueue, void (*_elementDestroy)(void* _item) )
{

	size_t i;
    size_t elementCounter;
    
    if(NULL == _myQueue || NULL == *_myQueue)  
    {
        return;
    }
    
    if( NULL != (*_elementDestroy) )
    {
        elementCounter = (*_myQueue)->m_numOfElements;
        
        for(i = 0; i < elementCounter; ++i)
        {
            (*_elementDestroy)( (*_myQueue)->m_items[i] );
        }
    }
    
    free((*_myQueue)->m_items);
    free(*_myQueue);
    *_myQueue = NULL;
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function put a new element into queue
 * @details     This function add another element to the queue at the end of the line
 *
 * @param       _myQueue					=   Pointer to queue
 * @param       _data    					=   Pointer to data element
 *
 * @return		Status VectorResult that indicate in which state the function ended:
 *
 * @retval 		QUEUE_SUCCESS				=	On success
 * @retval 		QUEUE_UNINITIALIZED_ERROR	=	Uninitialized Queue error
 * @retval 		ITEM_UNINITIALIZED_ERROR	=	Uninitialized item error
 * @retval 		QUEUE_OVERFLOW				=	When there is no room to add more elements
 */
QueueResult QueueInsert(Queue* const _myQueue, void* _data)
{
	CHECK_QUEUE_NULL(_myQueue);
	CHECK_ITEM_NULL(_data);
	
	if(_myQueue->m_numOfElements == _myQueue->m_capacity)
	{
		return QUEUE_OVERFLOW;
	}
	
	_myQueue->m_items[_myQueue->m_tail] = _data;
	(_myQueue->m_tail) = ( (_myQueue->m_tail + 1 ) % (_myQueue->m_capacity)  );
	++(_myQueue->m_numOfElements);
	
	return QUEUE_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function get the element from the queue
 * @details     This function remove the next element in the queue from the top of the line
 *
 * @param       _myQueue        			=   Pointer to queue
 * @param       _pValue    					=   Pointer to variable that will receive item data
 *
 * @return		Status VectorResult that indicate in which state the function ended:
 *
 * @retval 		QUEUE_SUCCESS				=	On success
 * @retval 		QUEUE_UNINITIALIZED_ERROR	=	Uninitialized Queue error
 * @retval 		QUEUE_ALLOCATION_ERROR		=	Allocation error 
 */
QueueResult QueueRemove(Queue* const _myQueue, void** _pValue)
{
	CHECK_QUEUE_NULL(_myQueue);
	CHECK_ITEM_NULL(_pValue);
	CHECK_ITEM_NULL(*_pValue);
	
	if(0 == _myQueue->m_numOfElements)
	{
		return QUEUE_UNDERFLOW;
	}
	
	*_pValue = (_myQueue->m_items)[_myQueue->m_head];
	(_myQueue->m_head) = ( (_myQueue->m_head + 1 ) % (_myQueue->m_capacity)  ) ;
	--(_myQueue->m_numOfElements);
	
	return QUEUE_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return the orignal memory buffer capacity of the queue
 * @details     The function return the orignal memory buffer capacity of the queue from a given queue.
 *
 * @param       _myQueue        		=   Pointer to queue
 *
 * @return		The orignal queue capacity OR 0
 *
 * @retval 		capacity				=	On success
 * @retval		0 						= 	If queue current capacity is 0 OR pointer
 *											is uninitialized- *_myQueue == NULL
 */
size_t QueueCapacity(Queue* const _myQueue)
{
	size_t  counter;
	
	if( NULL == _myQueue )
	{
		return 0;
	}

	counter = (_myQueue->m_capacity);
	
	return counter;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return The number of elements in the queue
 * @details     The function return the number of elements in the queue from a given queue.
 *
 * @param       _myQueue        		=   Pointer to queue
 *
 * @return		The number of elements in the queue OR 0
 *
 * @retval 		size					=	On success 
 * @retval		0 						= 	If queue is empty OR pointer is uninitialized- 
 *											*_myQueue == NULL
 */
size_t QueueSize(Queue* const _myQueue)
{
	size_t  counter;
	
	if( NULL == _myQueue )
	{
		return 0;
	}

	counter = (_myQueue->m_numOfElements);
	
	return counter;
}
/*----------------------------------------------------------------------------*/

