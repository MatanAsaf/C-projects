/** 
 *  @file 		tests.c
 *  @brief 		Set of tests for src multithreads safeQueue API functions
 * 
 *  @details 	The API stores functions to operate and manage the same memory
 *				space while multithreads operate on it as reader threads and/or as writer threads.
 *				The memory space implemented as a generic queue.
 *				The multithreads implemented as a condition mutex.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2017-01-06    
 *
 *  @bug No known bugs.
 *
 *  @warning QueueDestroy: The safe queue can't protect destroy thread from consumer/producer thread
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
 

#include "safeQueue.h"  /* header file */  
#include "matan_test.h" /* define test macros file */
#include <stdlib.h> 	/* for size_t & srand & malloc */
#include <stdio.h>      /* for printf & perror */
#include <pthread.h> 	/* for pthread API */
#include <string.h> 	/* for memset */
#include <sys/types.h>	/* for gettid */
#include <unistd.h>		/* for sleep */

#define MSG_SIZE (10)
#define AMOUNT_OF_MSG (20)
#define QUEUE_SIZE (10) 		/* SIZE = The size of the Queue (num of element) */  
#define DEBUG_ERRORS	(0)
#define DEBUG_PRINT_MSG	(0)


/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
static void GenericProduce(Queue* _queue, size_t nItems);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void GenericConsume(Queue* _queue, size_t nItems);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Producer(void* _queue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Consumer(void* _queue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* ProducerHalf(void* _queue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* ConsumerHalf(void* _queue);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* GenerateString();
/*----------------------------------------------------------------------------*/


/******************************* Tests functions ******************************/
/*----------------------------------------------------------------------------*/
TEST(Test001_1Consumer_1Producer_EvenAction)
	Queue* ip;
	pthread_t producerID;
	pthread_t consumerID;
	size_t queueSize;
	
	ip = QueueCreate(QUEUE_SIZE);
	if(NULL == ip)
	{
		printf("Allocation Error on QueueCreate\n");
	}
	
	#if DEBUG_ERRORS
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


/*----------------------------------------------------------------------------*/
TEST(Test002_1Consumer_1Producer_MoreActionForProducer)
	Queue* ip;
	pthread_t producerID;
	pthread_t consumerID;
	size_t queueSize;
	
	ip = QueueCreate(QUEUE_SIZE);
	if(NULL == ip)
	{
		printf("Allocation Error on QueueCreate\n");
	}
	
	#if DEBUG_ERRORS
	printf("QueueCreate Success\n");
	#endif
	
	if( -1 == pthread_create(&producerID, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	
	if( -1 == pthread_create(&consumerID, NULL, ConsumerHalf, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }

	if( -1 == pthread_join(consumerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
	
	sleep(1);
	
	queueSize = QueueSize(ip);
	
	if( -1 == pthread_create(&consumerID, NULL, ConsumerHalf, ip) )
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
    
	QueueDestroy(&ip, NULL);
	ASSERT_THAT ( QUEUE_SIZE == queueSize );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Test003_1Consumer_1Producer_MoreActionForConsumer)
	Queue* ip;
	pthread_t producerID;
	pthread_t consumerID;
	size_t queueSize;
	
	ip = QueueCreate(QUEUE_SIZE);
	if(NULL == ip)
	{
		printf("Allocation Error on QueueCreate\n");
	}
	
	#if DEBUG_ERRORS
	printf("QueueCreate Success\n");
	#endif
	
	if( -1 == pthread_create(&producerID, NULL, ProducerHalf, ip) )
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
	
	sleep(1);
	
	queueSize = QueueSize(ip);
	
	if( -1 == pthread_create(&producerID, NULL, ProducerHalf, ip) )
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
    
	QueueDestroy(&ip, NULL);
	ASSERT_THAT ( 0 == queueSize );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Test004_5Consumers_5Producers_EvenAction)
	Queue* ip;
	pthread_t producerID1;
	pthread_t producerID2;
	pthread_t producerID3;
	pthread_t producerID4;
	pthread_t producerID5;
	
	pthread_t consumerID1;
	pthread_t consumerID2;
	pthread_t consumerID3;
	pthread_t consumerID4;
	pthread_t consumerID5;
	size_t queueSize;
	
	ip = QueueCreate(QUEUE_SIZE);
	if(NULL == ip)
	{
		printf("Allocation Error on QueueCreate\n");
	}
	
	#if DEBUG_ERRORS
	printf("QueueCreate Success\n");
	#endif
	
	if( -1 == pthread_create(&producerID1, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_create(&producerID2, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&producerID3, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&producerID4, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&producerID5, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	if( -1 == pthread_create(&consumerID1, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_create(&consumerID2, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&consumerID3, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&consumerID4, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&consumerID5, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	if( -1 == pthread_join(producerID1, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_join(producerID2, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(producerID3, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(producerID4, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(producerID5, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	if( -1 == pthread_join(consumerID1, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_join(consumerID2, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID3, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID4, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID5, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	queueSize = QueueSize(ip);
	
	QueueDestroy(&ip, NULL);
	ASSERT_THAT ( 0 == queueSize );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Test005_5Consumers_1Producers_EvenAction)
	Queue* ip;
	pthread_t producerID;
	
	pthread_t consumerID1;
	pthread_t consumerID2;
	pthread_t consumerID3;
	pthread_t consumerID4;
	pthread_t consumerID5;
	size_t queueSize;
	
	ip = QueueCreate(QUEUE_SIZE);
	if(NULL == ip)
	{
		printf("Allocation Error on QueueCreate\n");
	}
	
	#if DEBUG_ERRORS
	printf("QueueCreate Success\n");
	#endif
	
	if( -1 == pthread_create(&producerID, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	
    
    
	if( -1 == pthread_create(&consumerID1, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_create(&consumerID2, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&consumerID3, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&consumerID4, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&consumerID5, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	if( -1 == pthread_join(producerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	queueSize = QueueSize(ip);
	
	if( -1 == pthread_create(&producerID, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_join(producerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_create(&producerID, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_join(producerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_create(&producerID, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_join(producerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_create(&producerID, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_join(producerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_join(consumerID1, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_join(consumerID2, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID3, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID4, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID5, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
	QueueDestroy(&ip, NULL);
	ASSERT_THAT ( 0 == queueSize );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(Test006_1Consumers_5Producers_EvenAction)
	Queue* ip;
	pthread_t producerID1;
	pthread_t producerID2;
	pthread_t producerID3;
	pthread_t producerID4;
	pthread_t producerID5;
	
	pthread_t consumerID;
	size_t queueSize;
	
	ip = QueueCreate(QUEUE_SIZE);
	if(NULL == ip)
	{
		printf("Allocation Error on QueueCreate\n");
	}
	
	#if DEBUG_ERRORS
	printf("QueueCreate Success\n");
	#endif
	
	if( -1 == pthread_create(&producerID1, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_create(&producerID2, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&producerID3, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&producerID4, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_create(&producerID5, NULL, Producer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	if( -1 == pthread_create(&consumerID, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
	if( -1 == pthread_join(consumerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
	queueSize = QueueSize(ip);
	
	
    if( -1 == pthread_create(&consumerID, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_create(&consumerID, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_create(&consumerID, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
    
    if( -1 == pthread_create(&consumerID, NULL, Consumer, ip) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(consumerID, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
	
	
	if( -1 == pthread_join(producerID1, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
	if( -1 == pthread_join(producerID2, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(producerID3, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(producerID4, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    if( -1 == pthread_join(producerID5, NULL) )
    {
    	QueueDestroy(&ip, NULL);
    }
    
	QueueDestroy(&ip, NULL);
	ASSERT_THAT ( QUEUE_SIZE == queueSize );
END_TEST
/*----------------------------------------------------------------------------*/


/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(Test safeQueue Module)
	PRINT(Test001_1Consumer_1Producer_EvenAction)
	PRINT(Test002_1Consumer_1Producer_MoreActionForProducer)
	PRINT(Test003_1Consumer_1Producer_MoreActionForConsumer)
	PRINT(Test004_5Consumers_5Producers_EvenAction)
	PRINT(Test005_5Consumers_1Producers_EvenAction)
	PRINT(Test006_1Consumers_5Producers_EvenAction)
END_SET
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
static void GenericProduce(Queue* _queue, size_t nItems)
{
	void* ptr;
	size_t i;
	
	for(i = 0; i < nItems; ++i)
	{
		ptr = GenerateString();
		
		#if DEBUG_PRINT_MSG
		printf("Producer: Msg number %u- %s\n",i, (char*)ptr);
		#endif
		
		if(QUEUE_SUCCESS != QueueInsert( _queue,  ptr))
		{
			#if DEBUG_ERRORS
			printf("Error on QueueInsert\n");
			#endif
		}
	}
	
	return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void GenericConsume(Queue* _queue, size_t nItems)
{
	char* ptr;
	size_t i;
	
	for(i = 0; i < nItems; ++i)
	{
		if(QUEUE_SUCCESS != QueueRemove(_queue,  (void**)&ptr) )
		{
			#if DEBUG_ERRORS
			printf("Error on QueueInsert\n");
			#endif
		}
		
		#if DEBUG_PRINT_MSG
		printf("Consumer: Msg number %u- %s\n",i, ptr);
		#endif
		
		free(ptr);
	}
	
	return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Producer(void* _queue)
{
	GenericProduce(_queue, AMOUNT_OF_MSG);
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* Consumer(void* _queue)
{
	GenericConsume(_queue, AMOUNT_OF_MSG);
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* ProducerHalf(void* _queue)
{
	GenericProduce(_queue, AMOUNT_OF_MSG/2);
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void* ConsumerHalf(void* _queue)
{
	GenericConsume(_queue, AMOUNT_OF_MSG/2);
	
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
	
	#if DEBUG_ERRORS
	printf("Char: %c\n", tav);
	#endif
	
	memset(msg, tav, MSG_SIZE);
	
	#if DEBUG_ERRORS
	printf("Msg: %s\n", msg);
	#endif
	
	ptr = (char*)malloc( sizeof(MSG_SIZE) );
	memcpy(ptr, msg, MSG_SIZE);
	
	return ptr;
}
/*----------------------------------------------------------------------------*/
