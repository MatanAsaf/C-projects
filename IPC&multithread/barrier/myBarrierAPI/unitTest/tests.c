/** 
 *  @file 		tests.c
 *  @brief 		Set of tests for my version of pthread barrier API functions
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
#include "matan_test.h" /* define test macros file */
#include <stddef.h> 	/* for size_t */
#include <stdio.h>      /* for printf & perror */
#include <pthread.h> 	/* for pthread API */

#define AMOUNT_OF_STORE (5)   
#define BARRIER_LIMIT (6)
#define NUMBER_OF_ACTION (5)
#define ITEM_PRICE (100)

/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct data
{
	size_t m_totalSale[AMOUNT_OF_STORE];
	BarrierData* m_barrier1;
	BarrierData* m_barrier2;
	size_t m_storeIndex;
	pthread_mutex_t m_mutex;
} Data;
/*----------------------------------------------------------------------------*/





/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
static void* Producer(void* _void);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Consumer(void* _void);
/*----------------------------------------------------------------------------*/



/******************************** Tests function ******************************/
/*----------------------------------------------------------------------------*/
TEST(FullTest)
	pthread_t producerID1;
	pthread_t producerID2;
	pthread_t producerID3;
	pthread_t producerID4;
	pthread_t producerID5;
	pthread_t counterID;
	Data newData;
	size_t i;
	
	BarrierCreate(&newData.m_barrier1, BARRIER_LIMIT);
	BarrierCreate(&newData.m_barrier2, BARRIER_LIMIT);
	pthread_mutex_init( &(newData.m_mutex), NULL);
	
	newData.m_storeIndex = 0;
	
	for(i = 0; i < AMOUNT_OF_STORE; ++i)
	{
		newData.m_totalSale[i] = 0;
	}
	
	pthread_create(&producerID1, NULL, Producer, &newData);
	pthread_create(&producerID2, NULL, Producer, &newData);
	pthread_create(&producerID3, NULL, Producer, &newData);
	pthread_create(&producerID4, NULL, Producer, &newData);
	pthread_create(&producerID5, NULL, Producer, &newData);
    pthread_create(&counterID, NULL, Consumer, &newData);
	
	pthread_join(producerID1, NULL);
	pthread_join(producerID2, NULL);
	pthread_join(producerID3, NULL);
	pthread_join(producerID4, NULL);
	pthread_join(producerID5, NULL);
	pthread_join(counterID, NULL);

	BarrierDestroy(&(newData.m_barrier1));
	BarrierDestroy(&(newData.m_barrier2));	
END_TEST
/*----------------------------------------------------------------------------*/



/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Barrier)
	PRINT(FullTest)
END_SET
/*----------------------------------------------------------------------------*/



/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
static void* Producer(void* _newData)
{
	size_t index;
	size_t i;
	size_t salePrice = ITEM_PRICE;
	
	pthread_mutex_lock( &( ((Data*)_newData)->m_mutex) );
	
	index = ( ( (Data*)_newData )->m_storeIndex++ );
	
	pthread_mutex_unlock( &( ((Data*)_newData)->m_mutex) );
	
	for(i = 0; i < NUMBER_OF_ACTION; ++i)
	{
		printf("Producer number %u: Insert salePrice: %u\n",index, salePrice);
		((Data*)_newData)->m_totalSale[index] += ITEM_PRICE;
		BarrierWait(  ( (Data*)_newData )->m_barrier1 );
		BarrierWait(  ( (Data*)_newData )->m_barrier2 );
	}
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Consumer(void* _newData)
{
	size_t i;
	size_t j;
	size_t totalSale = 0;
	
	
	for(i = 0; i < NUMBER_OF_ACTION; ++i)
	{
		BarrierWait( ( (Data*)_newData )->m_barrier1);
		
		for(j = 0; j < AMOUNT_OF_STORE; ++j)
		{
			totalSale += ( ((Data*)_newData)->m_totalSale[j] );
		}
		
		printf("Total revenue for round %u: %u\n",i ,totalSale);
		totalSale = 0;
		BarrierWait( ( (Data*)_newData )->m_barrier2 );
	}
	
	return NULL;
}
/*----------------------------------------------------------------------------*/
