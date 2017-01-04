/** 
 *  @file 		tests.c
 *  @brief 		Create a set of test for Generic Vector data structure
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
 

#include "queue.h"  	/* header file */  
#include "matan_test.h"	/* def of TEST test */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <stdio.h>      /* for printf */
#include <time.h> 		/* for time_t */


#define QUEUE_SIZE (10) 		/* SIZE = The size of the Queue (num of element) in each PRINT */
#define MAX_RAND_VALUE (50) /* MAX_RAND_VALUE = The max value the function rand() can produce */   



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to Queue values in sort order 
 * @param   _queue      = The address of the the source Queue
 * @param   _array		= Pointer to  the elements neeeded to insert to Queue 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 * @return   void
*/
static QueueResult InsertSortedValues(Queue* _queue, int* _array ,size_t _nElements, int _step, int _minValue);
/*----------------------------------------------------------------------------*/



/*************************** Tests for API functions **************************/
/*-------------------------------- QueueCreate -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(QueueCreate_CheckNull)
    Queue* ip;
    Queue* retVal;
    
    ip = QueueCreate(0);
	retVal = ip;
    QueueDestroy( &ip, NULL);
    
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueCreate_CheckNotNull)
    Queue* ip;
    Queue* retVal;
    
    ip = QueueCreate(QUEUE_SIZE);
	retVal = ip;
    QueueDestroy( &ip, NULL);
    
    ASSERT_THAT( NULL != retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- QueueDestroy -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(QueueDestroy_DoubleFree)
    Queue* ip; 
    
    ip = QueueCreate(QUEUE_SIZE);

    QueueDestroy( &ip, NULL);
    
    ASSERT_THAT( NULL == ip );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- QueueInsert ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(QueueInsert_CheckNull_Queue)
    QueueResult retVal;
    int item = 5;
    
    retVal = QueueInsert(NULL, (void*)&item);
    
    ASSERT_THAT( QUEUE_UNINITIALIZED_ERROR == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueInsert_CheckNull_Item)
    QueueResult retVal;
    Queue* ip;
    
    ip = QueueCreate(QUEUE_SIZE);
    retVal = QueueInsert(ip, NULL);
    
    QueueDestroy( &ip, NULL);
    
    ASSERT_THAT( ITEM_UNINITIALIZED_ERROR == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueInsert_CheckOverflow)
    Queue* ip;
    QueueResult retVal[2];
    int item = 5;
    
    ip = QueueCreate(1);
	retVal[0] = QueueInsert(ip, (void*)&item );
	retVal[1] = QueueInsert(ip, (void*)&item );
	
    QueueDestroy( &ip, NULL);
    
    ASSERT_THAT( QUEUE_SUCCESS == retVal[0] && QUEUE_OVERFLOW == retVal[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- QueueRemove ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(QueueRemove_CheckNull_Queue)
    QueueResult retVal;
    int* item;
    
    retVal = QueueRemove(NULL, (void**)&item);
    
    ASSERT_THAT( QUEUE_UNINITIALIZED_ERROR == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueRemove_CheckUnderflow)
    Queue* ip;
    QueueResult retVal;
    int* item;
    
    ip = QueueCreate(1);
	retVal = QueueRemove(ip, (void**)&item );
	
    QueueDestroy( &ip, NULL);
    
    ASSERT_THAT( QUEUE_UNDERFLOW == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueRemove_CheckFirstValue)
    Queue* ip;
    QueueResult retVal[2];
    int item = 55;
    int* value;
    
    ip = QueueCreate(QUEUE_SIZE);
    
    retVal[0] = QueueInsert(ip, (void*)&item );
    retVal[1] = QueueRemove(ip, (void**)&value );
	
    QueueDestroy( &ip, NULL);
    
	ASSERT_THAT( QUEUE_SUCCESS == retVal[0] && QUEUE_SUCCESS == retVal[1] && item == *value );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueRemove_CheckAllValue)
    Queue* ip;
    QueueResult retVal[QUEUE_SIZE];
    int item[QUEUE_SIZE];
    int* value[QUEUE_SIZE];
    QueueResult status;
    size_t i;
    
    ip = QueueCreate(QUEUE_SIZE);
    status = InsertSortedValues(ip, item , QUEUE_SIZE, 1, 0);
    if(QUEUE_SUCCESS != status)
    {
    	printf("The error is in InsertSortedValues function\n");
    }
    
    for(i = 0; i < QUEUE_SIZE; ++i)
    {
    	retVal[i] = QueueRemove(ip, (void**)&value[i] );
    }
	
    QueueDestroy( &ip, NULL);
    
    for(i = 0; i < QUEUE_SIZE; ++i)
    {
    	ASSERT_THAT( QUEUE_SUCCESS == retVal[i] && item[i] == *value[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueRemove_CheckCyclie)
    Queue* ip;
    QueueResult retVal[5];
    int item = 55;
    int* value[7];
    size_t i;
    
    ip = QueueCreate(5);
    
    QueueInsert(ip, (void*)&item );
    QueueRemove(ip, (void**)&value[5] );
 	QueueInsert(ip, (void*)&item );
  	retVal[0] = QueueInsert(ip, (void*)&item );
   	retVal[1] = QueueInsert(ip, (void*)&item );
   	QueueRemove(ip, (void**)&value[6] );
    retVal[2] = QueueInsert(ip, (void*)&item );
    retVal[3] = QueueInsert(ip, (void*)&item );
    retVal[4] = QueueInsert(ip, (void*)&item );
	
	QueueRemove(ip, (void**)&value[0] );
	QueueRemove(ip, (void**)&value[1] );
	QueueRemove(ip, (void**)&value[2] );
	QueueRemove(ip, (void**)&value[3] );
	QueueRemove(ip, (void**)&value[4] );
	
    QueueDestroy( &ip, NULL);
    
	for(i = 0; i < 5; ++i)
    {
    	ASSERT_THAT( QUEUE_SUCCESS == retVal[i] && item == *value[i] );
    }
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- QueueCapacity -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(QueueCapacity_CheckNull_Queue)
    size_t retVal;
    
    retVal = QueueCapacity(NULL);
    
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueCapacity_CheckCorrectAnswer)
    Queue* ip;
    size_t retVal;
    int item[QUEUE_SIZE];
    
	ip = QueueCreate(QUEUE_SIZE);
    InsertSortedValues(ip, item , QUEUE_SIZE-1, 1, 0);
    retVal = QueueCapacity(ip);
    
    QueueDestroy( &ip, NULL);
    ASSERT_THAT( QUEUE_SIZE == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------------- QueueSize -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(QueueSize_CheckNull_Queue)
    size_t retVal;
    
    retVal = QueueSize(NULL);
    
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(QueueSize_CheckCorrectAnswer)
    Queue* ip;
    size_t retVal;
    int item[QUEUE_SIZE];
    
	ip = QueueCreate(QUEUE_SIZE);
    InsertSortedValues(ip, item , QUEUE_SIZE-1, 1, 0);
    retVal = QueueSize(ip);
    
    QueueDestroy( &ip, NULL);
    ASSERT_THAT( (QUEUE_SIZE-1) == retVal );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* PRINT SET *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(PRINT SysV Module)
	PRINT(QueueCreate_CheckNull)
	PRINT(QueueCreate_CheckNotNull)
	
	PRINT(QueueDestroy_DoubleFree)
	
	PRINT(QueueInsert_CheckNull_Queue)
	PRINT(QueueInsert_CheckNull_Item)
	PRINT(QueueInsert_CheckOverflow)
	
	PRINT(QueueRemove_CheckNull_Queue)
	PRINT(QueueRemove_CheckUnderflow)
	PRINT(QueueRemove_CheckFirstValue)
	PRINT(QueueRemove_CheckAllValue)
	PRINT(QueueRemove_CheckCyclie)
	
	PRINT(QueueCapacity_CheckNull_Queue)
	PRINT(QueueCapacity_CheckCorrectAnswer)
	
	PRINT(QueueSize_CheckNull_Queue)
	PRINT(QueueSize_CheckCorrectAnswer)
END_SET
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/*
 * @brief 	Function that insert to Queue values in sort order 
 * @param   _queue        = The address of the the source Queue
 * @param   _array		= Pointer to  the elements neeeded to insert to Queue 
 * @param   _nElements  = The number of elements to insert
 * @param   _step       = The range value between each element 
 * @param   _minValue   = The value of the first element
 * @return   void
*/
static QueueResult InsertSortedValues(Queue* _queue, int* _array ,size_t _nElements, int _step, int _minValue)
{
    QueueResult status;
    size_t i;
    int value = _minValue;
    
    for( i = 0;  i < _nElements; ++i )
    {
    	_array[i] = value;
        status = QueueInsert(_queue, &_array[i]);
        if(QUEUE_SUCCESS != status)
        {
        	return status;
        }
        value += _step;
    }
    
    return QUEUE_SUCCESS;
}
/*----------------------------------------------------------------------------*/



