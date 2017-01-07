/** 
 *  @file 		cyclieBuf.c
 *  @brief 		src file for API functions for manging use buffer as cyclieBuf
 * 
 *  @details 	The API stores functions to operate and manage the user memory
 *				space (can be a pipe ).
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
 
#include "cyclieBuf.h"	/* header file */
#include <string.h>     /* for memcpy */
#include <stdlib.h>     /* for size_t */
#include <stdio.h>      /* for perror */
#include <errno.h>      /* for errno */

#define CHECK_NULL(param)	do{ if(NULL == (param) ) { return NULL;}  } while(0)



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
struct Queue
{
    size_t m_size; 		/* The size of the structuer */
    size_t m_head; 		/* Index to the first message to remove from the structuer */
    size_t m_tail; 		/* Index to the last message that insert to the structuer */
    size_t m_maxItems; 	/* The max number of message in the structuer */
    size_t m_nItems; 	/* The current number of message in the structuer */
    size_t m_msgSize; 	/* The size of each message in the structuer */
};
/*----------------------------------------------------------------------------*/




/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function initalize the user memory buffer
 * @details     The function get from the user pointer to memory, and it's size.
 *				If the given memory is not too small, the function initalize it.
 *
 * @param       _mem        =   Pointer to memory
 * @param       _memSize    =   The memory size (needed to be at least 
 * 				_numOfMsg * _maxMsgSize + (6* sizeof(size_t)) )
 * @param       _numOfMsg   =   The amount of msg the user want to have in the queue
 * @param       _maxMsgSize =   The max size for each msg
 *
 * @return		The orignal memory buffer OR NULL at error
 *
 * @retval		NULL		= 	On error when initalize
 * @retval 		_myQueue	=	On success
 */
Queue* CyclieBufCreate(void* _mem, size_t _memSize, size_t _numOfMsg, size_t _maxMsgSize)
{
	Queue* myQueue;
	
	CHECK_NULL(_mem);
	if( 0 == _memSize || 0 == _numOfMsg || 0 == _maxMsgSize)
	{
		return NULL;
	}
	
	if(  _memSize < ( sizeof(Queue) + (_numOfMsg * _maxMsgSize) )  )
	{
		return NULL;
	}
	
	myQueue = (Queue*)_mem;
	
	myQueue->m_size = _memSize;
	myQueue->m_maxItems = _numOfMsg;
	myQueue->m_nItems = 0;
	myQueue->m_head = 0;
	myQueue->m_tail = 0;
	myQueue->m_msgSize = _maxMsgSize;
	
	return myQueue;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function put a new msg into the user memory queue
 *
 * @param       _myQueue    =   Pointer to memory
 * @param       _msgData    =   Pointer to memory message
 *
 * @return		The status as 0 OR -1
 *
 * @retval		-1			= 	On error when initalize OR there is no room left 
 *								in the queue for this msg
 * @retval 		0			=	On success
 */
int CyclieBufPut(Queue* const _myQueue, void* _msgData)
{
	size_t* msgPtr;
	size_t msgLength;
	size_t currentIndexMsg;
	
	if(NULL == _myQueue || NULL == _msgData)
	{
		perror("Initalize error");
		return (-1);
	}
	
	currentIndexMsg = (_myQueue->m_tail);
	
	if(_myQueue->m_nItems == _myQueue->m_maxItems)
	{
		perror("Overflow error");
		return (-1);
	}
	
	msgLength = _myQueue->m_msgSize;

	msgPtr = (size_t*)(_myQueue + 1) + (msgLength * currentIndexMsg);
	memcpy((void*)msgPtr, _msgData, msgLength);
	
	(_myQueue->m_tail) = ( (currentIndexMsg + 1 ) % (_myQueue->m_maxItems)  ) ;
	++(_myQueue->m_nItems);
	
	return 0;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function get the msg from the user memory queue
 *
 * @param       _myQueue    =   Pointer to memory
 * @param       _msgData    =   Pointer to get message from memory
 *
 * @return		The status as 0 OR -1
 *
 * @retval		-1			= 	On error when initalize OR there is no room left 
 *								in the queue for this msg
 * @retval 		0			=	On success
 */
int CyclieBufGet(Queue* const _myQueue, void* _msgData)
{
	size_t* msgPtr;
	size_t msgLength;
	size_t currentIndexMsg;
	
	if(NULL == _myQueue)
	{
		perror("Initalize error");
		return (-1);
	}
	
	currentIndexMsg = (_myQueue->m_head);
	
	if(0 == _myQueue->m_nItems)
	{
		perror("Underflow error");
		return (-1);
	}
	
	msgLength = _myQueue->m_msgSize;

	msgPtr = (size_t*)(_myQueue + 1) + (msgLength * currentIndexMsg);
	memcpy(_msgData, (void*)msgPtr, msgLength);
	
	(_myQueue->m_head) = ( (currentIndexMsg + 1 ) % (_myQueue->m_maxItems)  ) ;
	--(_myQueue->m_nItems);
	
	return 0;
}
/*----------------------------------------------------------------------------*/


