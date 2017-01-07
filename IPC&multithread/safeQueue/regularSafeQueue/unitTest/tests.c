/** 
 *  @file 		tests.c
 *  @brief 		Set of tests for src safeQueue API functions
 * 
 *  @details 	The API stores functions to operate and manage the same memory
 *				space while a reader thread and a writer thread operate on it.
 *				The memory space implemented as a generic queue..
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
 

#include "safeQueue.h"  /* header file */  
#include "matan_test.h" 	/* define test macros file */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <stdio.h>      /* for printf & perror */
#include <pthread.h> 	/* for pthread API */
#include <string.h> 	/* for memset */
#include <sys/types.h>	/* for gettid */

#define MSG_SIZE (10)
#define AMOUNT_OF_MSG (20)
#define QUEUE_SIZE (10) 		/* SIZE = The size of the Queue (num of element) */  
#define DEBUG1	(0)
#define DEBUG2	(1)


/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
static void* Producer(void* _queue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Consumer(void* _queue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* GenerateString();
/*----------------------------------------------------------------------------*/


/******************************* Tests functions ******************************/
/*----------------------------------------------------------------------------*/
TEST(FullTest)
	Queue* ip;
	pthread_t producerID;
	pthread_t consumerID;
	size_t queueSize;
	
	ip = QueueCreate(QUEUE_SIZE);
	if(NULL == ip)
	{
		printf("Allocation Error on QueueCreate\n");
	}
	
	#if DEBUG1
	printf("QueueCreate Success\n");
	#endif
	
	if( -1 == pthread_create(&producerID, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	
	if( -1 == pthread_create(&consumerID, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	
	if( -1 == pthread_join(producerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }

	if( -1 == pthread_join(consumerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
	
	queueSize = QueueSize(ip);
	
	QueueDestroy(&ip, NULL);
	ASSERT_THAT ( 0 == queueSize );
END_TEST
/*----------------------------------------------------------------------------*/




/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(safeQueue)
	PRINT(FullTest)
END_SET
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
static void* Producer(void* _queue)
{
	void* ptr;
	size_t i;
	
	for(i = 0; i < AMOUNT_OF_MSG; ++i)
	{
		ptr = GenerateString();
		
		#if DEBUG2
		printf("Producer: Msg number %u- %s\n",i, (char*)ptr);
		#endif
		
		if(QUEUE_SUCCESS != QueueInsert( _queue,  ptr))
		{
			printf("Error on QueueInsert\n");
		}
	}
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Consumer(void* _queue)
{
	char* ptr;
	size_t i;
	
	for(i = 0; i < AMOUNT_OF_MSG; ++i)
	{
		if(QUEUE_SUCCESS != QueueRemove(_queue,  (void**)&ptr) )
		{
			printf("Error on QueueInsert\n");
		}
		
		#if DEBUG2
		printf("Consumer: Msg number %u- %s\n",i, ptr);
		#endif
		
		free(ptr);
	}
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* GenerateString()
{
	char* ptr;
	char msg[MSG_SIZE];
	char tav;

	tav = (char)(65 + (rand() % 26) ); /* rand number from A-Z */
	
	#if DEBUG1
	printf("Char: %c\n", tav);
	#endif
	
	memset(msg, tav, MSG_SIZE);
	
	#if DEBUG1
	printf("Msg: %s\n", msg);
	#endif
	
	ptr = (char*)malloc( sizeof(MSG_SIZE) );
	memcpy(ptr, msg, MSG_SIZE);
	
	return ptr;
}
/*----------------------------------------------------------------------------*/
