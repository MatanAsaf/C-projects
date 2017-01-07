/** 
 *  @file 		safeQueue.c
 *  @brief 		src file for API functions for manging multithreads safeQueue
 * 
 *  @details 	The API stores functions to operate and manage the same memory
 *				space while multithreads operate on it as reader threads and/or as writer threads.
 *				The memory space implemented as a generic queue.
 *				The multithreads implemented as a semaphore.
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
 
#include "safeQueue.h"	/* header file */
#include <stdlib.h> 	/* for size_t  & malloc */
#include <fcntl.h> 		/* for semaphore o_flag define */
#include <sys/stat.h> 	/* for O_CREAT mode parameters in semaphore API */
#include <semaphore.h> 	/* for semaphore API */
#include <time.h> 		/* for mutex */
#include <stdio.h>      /* for perror */
#include <errno.h> 		/* for display errors on errno */
#include <pthread.h> 	/* for pthread API */
#include <errno.h> 		/* for display errors */

#define DEBUG	(1)
#define SEMAPHORE_INIT_FAILED (-1)
#define SEMAPHORE_INIT_SUCCESS (0)
#define CHECK_NULL(param)	do{ if(NULL == (param) ) { return NULL;}  } while(0)




/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
struct Queue
{
    void** m_items;				/* Pointer to the actual items */
    size_t m_capacity; 			/* The size of the structuer */
    size_t m_head; 				/* Index to the first message to remove from the structuer */
    size_t m_tail; 				/* Index to the last message that insert to the structuer */
    size_t m_numOfElements; 	/* The current number of message in the structuer */
    size_t m_numOfWaitOnEmpty; 	/* The number of times thread wait for remove on empty queue */
    size_t m_numOfWaitOnFull; 	/* The number of times thread wait for remove on full queue */
    sem_t m_semaphoreEmpty;		/* Pointer to semaphore for Empty condition */
    sem_t m_semaphoreFull;		/* Pointer to semaphore for full condition */
    pthread_mutex_t m_mutex;	/* Pointer to mutex */
};
/*----------------------------------------------------------------------------*/





/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
static int InitSemaphore(Queue* _myQueue);
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
Queue* QueueCreate(size_t _initialCapacity)
{
	Queue* myQueue;
	int status;
	int mutexStatus;
	
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
	status = InitSemaphore(myQueue);
	
	if(SEMAPHORE_INIT_FAILED == status)
	{
		free(myQueue->m_items);
		free(myQueue);
		return NULL;
	}
	
	mutexStatus = pthread_mutex_init( &(myQueue->m_mutex), NULL);
    if(0 != mutexStatus)
	{
		QueueDestroy(&myQueue, NULL);
		return NULL;
	}
	
	return myQueue;
}
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
            (*_elementDestroy)( (*_myQueue)->m_items[(*_myQueue)->m_head] );
            ((*_myQueue)->m_head) = ( ((*_myQueue)->m_head + 1 ) % ((*_myQueue)->m_capacity)  );
        }
    }
    
    sem_destroy( &((*_myQueue)->m_semaphoreFull) );
    sem_destroy( &((*_myQueue)->m_semaphoreEmpty) );
	pthread_mutex_destroy( &((*_myQueue)->m_mutex) );
	
    free((*_myQueue)->m_items);
    free(*_myQueue);
    *_myQueue = NULL;
    
    return;
}
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
QueueResult QueueInsert(Queue* const _myQueue, void* _data)
{
	if( NULL == _myQueue )
	{
		return QUEUE_UNITIALIZED_ERROR;
	}
	
	if( NULL == _data )
	{
		return ITEM_UNITIALIZED_ERROR;
	}
	
	if(_myQueue->m_numOfElements == _myQueue->m_capacity)
	{
		++(_myQueue->m_numOfWaitOnFull);
	}
	
	if(-1 == sem_wait( &(_myQueue->m_semaphoreEmpty) ))
	{
		#if DEBUG
		perror("SEM_FAILED on sem_wait: ");
		printf("errno Error: %u\n", errno);;
		#endif
		
		return SEMAPHORE_ERROR;
	}
		
	if(0 != pthread_mutex_lock( &(_myQueue->m_mutex) ) )
	{
		#if DEBUG
		perror("mutex_FAILED on mutex_lock: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return MUTEX_ERROR;
	}
	
	_myQueue->m_items[_myQueue->m_tail] = _data;
	(_myQueue->m_tail) = ( (_myQueue->m_tail + 1 ) % (_myQueue->m_capacity)  );
	++(_myQueue->m_numOfElements);
	
	if(0 != pthread_mutex_unlock( &(_myQueue->m_mutex) ) )
	{
		#if DEBUG
		perror("mutex_FAILED on mutex_unlock: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return MUTEX_ERROR;
	}
	
	if(-1 == sem_post( &(_myQueue->m_semaphoreFull) ) )
	{
		#if DEBUG
		perror("SEM_FAILED on sem_post: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return SEMAPHORE_ERROR;
	}
	
	return QUEUE_SUCCESS;
}
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
QueueResult QueueRemove(Queue* const _myQueue, void** _pValue)
{
	if( NULL == _myQueue )
	{
		return QUEUE_UNITIALIZED_ERROR;
	}
	
	if( NULL == _pValue )
	{
		return ITEM_UNITIALIZED_ERROR;
	}
	
	if(0 == _myQueue->m_numOfElements)
	{
		++(_myQueue->m_numOfWaitOnFull);
	}
	
	if(-1 == sem_wait( &(_myQueue->m_semaphoreFull) ) )
	{
		#if DEBUG
		perror("SEM_FAILED on sem_wait: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return SEMAPHORE_ERROR;
	}
	
	if(0 != pthread_mutex_lock( &(_myQueue->m_mutex) ) )
	{
		#if DEBUG
		perror("mutex_FAILED on mutex_lock: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return MUTEX_ERROR;
	}
	
	*_pValue = (_myQueue->m_items)[_myQueue->m_head];
	(_myQueue->m_head) = ( (_myQueue->m_head + 1 ) % (_myQueue->m_capacity)  ) ;
	--(_myQueue->m_numOfElements);
	
	if(0 != pthread_mutex_unlock( &(_myQueue->m_mutex) ) )
	{
		#if DEBUG
		perror("mutex_FAILED on mutex_unlock: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return MUTEX_ERROR;
	}
	
	if( -1 == sem_post( &(_myQueue->m_semaphoreEmpty) ) )
	{
		#if DEBUG
		perror("SEM_FAILED on sem_post: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return SEMAPHORE_ERROR;
	}
	
	return QUEUE_SUCCESS;
}
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
size_t QueueCapacity(Queue* const _myQueue)
{
	size_t  counter;
	
	if( NULL == _myQueue )
	{
		return 0;
	}
	
	pthread_mutex_lock( &(_myQueue->m_mutex) );
	
	counter = (_myQueue->m_capacity);
	
	pthread_mutex_unlock( &(_myQueue->m_mutex) );
	
	return counter;
}
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
size_t QueueSize(Queue* const _myQueue)
{
	size_t  counter;
	
	if( NULL == _myQueue )
	{
		return 0;
	}
	
	pthread_mutex_lock( &(_myQueue->m_mutex) );
	
	counter = (_myQueue->m_numOfElements);
	
	pthread_mutex_unlock( &(_myQueue->m_mutex) );
	
	return counter;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
static int InitSemaphore(Queue* _myQueue)
{
	if(-1 == sem_init(&(_myQueue->m_semaphoreFull), 0, 0) )
	{
		#if DEBUG
		perror("SEM_FAILED on semaphoreFull: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		return SEMAPHORE_INIT_FAILED;
	}
	
	if(-1 == sem_init(&(_myQueue->m_semaphoreEmpty), 0, (unsigned int)_myQueue->m_capacity) )
	{
		#if DEBUG
		perror("SEM_FAILED on semaphoreEmpty: ");
		printf("errno Error: %u\n", errno);
		#endif
		
		sem_destroy( &(_myQueue->m_semaphoreFull) );
		return SEMAPHORE_INIT_FAILED;
	}
	
	return SEMAPHORE_INIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
