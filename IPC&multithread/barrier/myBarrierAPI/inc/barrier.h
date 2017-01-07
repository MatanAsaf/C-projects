/** 
 *  @file 		barrier.h
 *  @brief 		header file for my version of pthread barrier API functions
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

#ifndef __BARRIER_H__
#define __BARRIER_H__

#include <stddef.h>		/* for size_t */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum Barrier_Result {
	BARRIER_SUCCESS,
	BARRIER_INITIALIZE_FAILED,		/* Error on unitialize parameter*/
	BARRIER_CREATE_FAILED,			/* Error on create barrier */
	BARRIER_DESTROY_FAILED,			/* Error on destroy barrier */
	BARRIER_WAIT_FAILED				/* Error on wait barrier */
} BarrierResult;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef struct BarrierData BarrierData;
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
 * @retval		BARRIER_INITIALIZE_FAILED	= 	On error when initalize
 * @retval		BARRIER_CREATE_FAILED		= 	On error when create
 * @retval 		BARRIER_SUCCESS				=	On success
 */
BarrierResult BarrierCreate(BarrierData** _myBarrier, size_t _limitCondition);
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
 * @retval		BARRIER_INITIALIZE_FAILED	= 	On error when initalize
 * @retval		BARRIER_DESTROY_FAILED		= 	On error when destroy
 * @retval 		BARRIER_SUCCESS				=	On success
 */
BarrierResult BarrierDestroy(BarrierData** _myBarrier);
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
 * @retval		BARRIER_INITIALIZE_FAILED	= 	On error when initalize
 * @retval		BARRIER_WAIT_FAILED			= 	On error when wait
 * @retval 		BARRIER_SUCCESS				=	On success
 */
BarrierResult BarrierWait(BarrierData* _myBarrier);
/*----------------------------------------------------------------------------*/


#endif /* __BARRIER_H__ */
