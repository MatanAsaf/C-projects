/** 
 *  @file 		cyclieBuf.h
 *  @brief 		header file for API functions for manging use buffer as cyclieBuf
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

#ifndef __CYCLIE_BUF_H__
#define __CYCLIE_BUF_H__

#include <stdlib.h>		/* for define size_t */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct Queue Queue;
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
Queue* CyclieBufCreate(void* _mem, size_t _memSize, size_t _numOfMsg, size_t _maxMsgSize);
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
int CyclieBufPut(Queue* const _myQueue, void* _msgData);
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
int CyclieBufGet(Queue* const _myQueue, void* _msgData);
/*----------------------------------------------------------------------------*/



#endif /* __CYCLIE_BUF_H__ */
