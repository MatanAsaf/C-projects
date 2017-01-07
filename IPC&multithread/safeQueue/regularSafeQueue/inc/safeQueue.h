/** 
 *  @file 		safeQueue.h
 *  @brief 		header file for API functions for manging safeQueue
 * 
 *  @details 	The API stores functions to operate and manage the same memory
 *				space while a reader thread and a writer thread operate on it.
 *				The memory space implemented as a generic queue.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2017-01-06    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__

#include <stdlib.h>		/* for define size_t */


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
	ITEM_UNINITIALIZED_ERROR,		/* Uninitialized item error */
	SEMAPHORE_ERROR,			/* Error on the semaphore part of the code */
	MUTEX_ERROR					/* Error on the mutex part of the code */
} QueueResult;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function create a new queue and return the memory
 * @details     The function create a new queue in capacity the user sent as size and return the pointer to it.
 *
 * @param       _initialCapacity        =   Number of elements that can be stored initially
 *
 * @return		The orignal memory buffer OR NULL at error
 *
 * @retval		NULL					= 	On error when initalize
 * @retval 		_myQueue				=	On success
 */
Queue* QueueCreate(size_t _initialCapacity);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 		Dynamically deallocate a previously allocated safeQueue 
 * 
 * @param 		_Queue					= 	Queue to be deallocated.
 * @param 		_elementDestroy			= 	A function pointer to be used to destroy all elements in the vector
 *             or a null if no such destroy is required
 *
 * @return void
 */
void QueueDestroy(Queue** _myQueue, void (*_elementDestroy)(void* _item) );
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function put a new element into queue
 * @details     This function write a new msg (pointer) in the join queue when success, 
 *				and return to the user status that indicate in which state the function ended. 
 *
 * @param       _myQueue				=   Pointer to memory
 * @param       _data    				=   Pointer to memory message
 *
 * @return		Status QueueResult that indicate in which state the function ended:
 *
 * @retval 		QUEUE_SUCCESS			=	On success
 * @retval 		QUEUE_UNINITIALIZED_ERROR	=	Uninitialized Queue error
 * @retval 		ITEM_UNINITIALIZED_ERROR	=	Uninitialized item error
 * @retval 		QUEUE_OVERFLOW			=	When there is no room to add more elements
 */
QueueResult QueueInsert(Queue* const _myQueue, void* _data);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function get the element from the queue
 * @details     This function read from the join queue the pointer to the msg, 
 *				and return to the user the pointer when success, otherwise 
 *				return status error. 
 *
 * @param       _myQueue        		=   Pointer to memory
 * @param       _pValue    				=   Pointer to get message from memory
 *
 * @return		Status QueueResult that indicate in which state the function ended:
 *
 * @retval 		QUEUE_SUCCESS			=	On success
 * @retval 		QUEUE_UNINITIALIZED_ERROR	=	Uninitialized Queue error
 * @retval 		QUEUE_ALLOCATION_ERROR	=	Allocation error 
 */
QueueResult QueueRemove(Queue* const _myQueue, void** _pValue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return the orignal memory buffer capacity in the queue
 * @details     The function return the orignal memory buffer capacity in the queue from a given queue.
 *
 * @param       _myQueue        		=   Pointer to memory
 *
 * @return		The orignal memory buffer capacity OR error
 *
 * @retval		0						= 	On error when initalize OR when capacity is 0
 * @retval 		capacity				=	On success
 */
size_t QueueCapacity(Queue* const _myQueue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function return The number of elements in the queue
 * @details     The function return the number of elements in the queue from a given queue.
 *
 * @param       _myQueue        		=   Pointer to memory
 *
 * @return		The number of elements in the queue OR error
 *
 * @retval		0						= 	On error when initalize OR when size is 0
 * @retval 		size					=	On success
 */
size_t QueueSize(Queue* const _myQueue);
/*----------------------------------------------------------------------------*/


#endif /* __SAFE_QUEUE_H__ */
