/** 
 *  @file 		barrier.c
 *  @brief 		src file for my version of pthread barrier API functions
 * 
 *  @details 	The API stores functions to operate and manage pthread barrier
 *				so multi-threads can operate on the same src object.
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

#include "barrier.h"	/* header file */
#include <stdlib.h>		/* for malloc & free */
#include <stddef.h>		/* for size_t */
#include <pthread.h>	/* for mutex API */
#include <stdio.h>      /* for perror */
#include <errno.h>      /* for errno */



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
struct BarrierData
{
	pthread_mutex_t m_mutex;
	pthread_cond_t m_condMutex;
	size_t m_counter;
	size_t m_barrierLimit;
};
/*----------------------------------------------------------------------------*/




/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function create a new barrier struct.
 * @details     The function shall allocated any resources required to use the barrier.
 *				It will create a new barrier structure and return BarrierResult 
 *				status and when successful return the barrier pointer through pValue.
 *
 * @param       _myBarrier        			=   Pointer to the return value at the function success
 * @param       _limitCondition        		=   Indicate how many threads can operate untill block by barrier
 *
 * @return		Status BarrierResult that indicate in which state the function ended:
 *
 * @retval		BARRIER_INITIALIZE_FAILED	= 	On error when initialize
 * @retval		BARRIER_CREATE_FAILED		= 	On error when create
 * @retval 		BARRIER_SUCCESS				=	On success
 */
BarrierResult BarrierCreate(BarrierData** _myBarrier, size_t _limitCondition)
{
	BarrierData* myBarrier;
	
	if(NULL == *_myBarrier)
	{
		return BARRIER_INITIALIZE_FAILED;	
	}
	
	myBarrier = (BarrierData*)malloc( sizeof(BarrierData) );
	
	if(NULL == myBarrier)
	{
		return BARRIER_CREATE_FAILED;	
	}
	
	if(0 != pthread_mutex_init( &(myBarrier->m_mutex), NULL) )
	{
		free(myBarrier);
		return BARRIER_CREATE_FAILED;
	}
	
	if(0 != pthread_cond_init( &(myBarrier->m_condMutex), NULL) )
	{
		free(myBarrier);
		return BARRIER_CREATE_FAILED;
	}
	
	myBarrier->m_counter = 0;
	myBarrier->m_barrierLimit = _limitCondition;
	
	*_myBarrier = myBarrier;
	
	return BARRIER_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function destroy the new barrier struct.
 * @details     The function shall destroy the barrier referenced by barrier and
 * 				release any resources used by the barrier. The function return BarrierResult 
 *				status and when successful return the barrier pointer uninitialize through pValue.
 *
 * @param       _myBarrier        			=   Pointer to the return value (NULL) at the function success
 *
 * @return		Status BarrierResult that indicate in which state the function ended:
 *
 * @retval		BARRIER_INITIALIZE_FAILED	= 	On error when initialize
 * @retval		BARRIER_DESTROY_FAILED		= 	On error when destroy
 * @retval 		BARRIER_SUCCESS				=	On success
 */
BarrierResult BarrierDestroy(BarrierData** _myBarrier)
{
	if(NULL == _myBarrier || NULL == *_myBarrier)
	{
		return BARRIER_INITIALIZE_FAILED;	
	}
	
	if(0 != pthread_cond_destroy( &((*_myBarrier)->m_condMutex) ) )
	{
		return BARRIER_DESTROY_FAILED;
	}
	
	if(0 != pthread_mutex_destroy( &((*_myBarrier)->m_mutex) ) )
	{
		return BARRIER_DESTROY_FAILED;
	}
	
	free(*_myBarrier);
	*_myBarrier = NULL;
	
	return BARRIER_SUCCESS;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function stop the barrier when number of threads reach the limit.
 * @details     The function specifies the number of threads that can be call before 
 *				any of them successfully return from the call, according to limitCondition
 *				parameter from BarrierCreate function.
 *
 * @param       _myBarrier        			=   Pointer to the barrier struct
 *
 * @return		Status BarrierResult that indicate in which state the function ended:
 *
 * @retval		BARRIER_INITIALIZE_FAILED	= 	On error when initialize
 * @retval		BARRIER_WAIT_FAILED			= 	On error when wait
 * @retval 		BARRIER_SUCCESS				=	On success
 */
BarrierResult BarrierWait(BarrierData* _myBarrier)
{
	if(NULL == _myBarrier)
	{
		return BARRIER_INITIALIZE_FAILED;	
	}
	
	if(0 != pthread_mutex_lock( &(_myBarrier->m_mutex) ) )
	{
		return BARRIER_WAIT_FAILED;
	}
		
	++(_myBarrier->m_counter);
	
	if(_myBarrier->m_counter < _myBarrier->m_barrierLimit)
	{
		if(0 != pthread_cond_wait( &(_myBarrier->m_condMutex),  &(_myBarrier->m_mutex) ) )
		{
			return BARRIER_WAIT_FAILED;
		}
	}
	
	if(_myBarrier->m_counter >= _myBarrier->m_barrierLimit)
	{
		_myBarrier->m_counter = 0;
	}
	
	if(0 != pthread_cond_broadcast( &(_myBarrier->m_condMutex) ) )
	{
		return BARRIER_WAIT_FAILED;
	}
	
	if(0 != pthread_mutex_unlock( &(_myBarrier->m_mutex) ) )
	{
		return BARRIER_WAIT_FAILED;
	}
	
	return BARRIER_SUCCESS;
}
/*----------------------------------------------------------------------------*/


