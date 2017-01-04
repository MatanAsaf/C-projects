/** 
 *  @file 		queue.h
 *  @brief 		header file for Generic Queue data type
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

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>		/* for define size_t */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct Queue Queue;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef int	(*QueueElementAction)(void* _element, size_t _index, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef enum Queue_Result {
	QUEUE_SUCCESS,
	QUEUE_UNINITIALIZED_ERROR,	/* Uninitialized Queue error */
	ITEM_UNINITIALIZED_ERROR,	/* Uninitialized item error */
	QUEUE_OVERFLOW,				/* Overflow error, when there is no room to add more elements */
	QUEUE_UNDERFLOW				/* Underflow error, when there is no elements in the queue to get */
} QueueResult;
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
Queue* QueueCreate(size_t _initialCapacity);
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
void QueueDestroy(Queue** _myQueue, void (*_elementDestroy)(void* _item) );
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
QueueResult QueueInsert(Queue* const _myQueue, void* _data);
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
QueueResult QueueRemove(Queue* const _myQueue, void** _pValue);
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
size_t QueueCapacity(Queue* const _myQueue);
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
size_t QueueSize(Queue* const _myQueue);
/*----------------------------------------------------------------------------*/


#endif /* __QUEUE_H__ */
