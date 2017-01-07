/** 
 *  @file 		barrier.c
 *  @brief 		Practice the right use of pthread barrier API functions
 * 
 *  @details 	Use of the folowing functions:
 *	1.pthread_barrier_init
 *	1.pthread_barrier_destroy
 *	3.pthread_barrier_wait  
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

#include <stddef.h> 	/* for size_t */
#include "matan_test.h" /* define test macros file */
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
	pthread_barrier_t m_barrier;
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
	
	pthread_barrier_init(&(newData.m_barrier), NULL, BARRIER_LIMIT);
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

	pthread_barrier_destroy(&(newData.m_barrier));
END_TEST
/*----------------------------------------------------------------------------*/



/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Use of Pthread Barrier)
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
		pthread_barrier_wait ( &( ( (Data*)_newData )->m_barrier ) );
		pthread_barrier_wait ( &( ( (Data*)_newData )->m_barrier ) );
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
		pthread_barrier_wait ( &(( (Data*)_newData )->m_barrier));
		
		for(j = 0; j < AMOUNT_OF_STORE; ++j)
		{
			totalSale += ( ((Data*)_newData)->m_totalSale[j] );
		}
		
		printf("Total revenue for round %u: %u\n",i ,totalSale);
		totalSale = 0;
		pthread_barrier_wait (&( ( (Data*)_newData )->m_barrier ));
	}
	
	return NULL;
}
/*----------------------------------------------------------------------------*/
