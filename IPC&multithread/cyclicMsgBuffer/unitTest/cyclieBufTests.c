/** 
 *  @file 		cyclieBufTest.c
 *  @brief 		Set of tests for cyclieBuf API functions
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

#include "cyclieBuf.h" 	/* header file */  
#include "matan_test.h" /* tests macros file */
#include <stdlib.h>     /* for size_t */
#include <stdio.h>      /* for perror */
#include <string.h>     /* for perror */
#include <errno.h>      /* for errno */

#define MEM_SIZE (1024)
#define MSG_SIZE (10)
#define AMOUNT_OF_MSG (10)


/******************************* Tests functions ******************************/
/*------------------------------ CyclieBufCreate -----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CyclieBufCreate_CheckNULL_Memory)
	void* retVal;
	
	retVal = CyclieBufCreate(NULL, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufCreate_CheckNULL_MemSize)
	void* buffer = malloc(MEM_SIZE);
	void* retVal;
	
	retVal = CyclieBufCreate(buffer, 0, AMOUNT_OF_MSG, MSG_SIZE);
	free(buffer);
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufCreate_CheckNULL_AmountOfSize)
	void* buffer = malloc(MEM_SIZE);
	void* retVal;
	
	retVal = CyclieBufCreate(buffer, MEM_SIZE, 0, MSG_SIZE);
	free(buffer);
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufCreate_CheckNULL_MsgSize)
	void* buffer = malloc(MEM_SIZE);
	void* retVal;
	
	retVal = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, 0);
	free(buffer);
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufCreate_CheckMemTooSmall)
	void* buffer = malloc(MEM_SIZE);
	size_t memSize = sizeof(size_t) + (AMOUNT_OF_MSG * MSG_SIZE);
	void* retVal;
	
	retVal = CyclieBufCreate(buffer, memSize -1 , AMOUNT_OF_MSG, MSG_SIZE);
	free(buffer);
    ASSERT_THAT( NULL == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufCreate_CheckNotNull)
	void* buffer = malloc(MEM_SIZE);
	void* retVal;
	
	retVal = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	free(buffer);
    ASSERT_THAT( NULL != retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- CyclieBufPut -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CyclieBufPut_CheckNULL_Memory)
	int retVal;
	char msg[] = "AAAAAA";
	
	retVal = CyclieBufPut(NULL, (void*)&msg );
    ASSERT_THAT( -1 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufPut_CheckNULL_Data)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal;
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	retVal = CyclieBufPut(mem, NULL );
	free(buffer);
    ASSERT_THAT( -1 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufPut_CheckNotNULL)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal;
	char msg[] = "AAAAAA";
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	retVal = CyclieBufPut(mem, msg );
	free(buffer);
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufPut_CheckOverflow)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal[AMOUNT_OF_MSG + 1];
	char msg[] = "AAAAAA";
	size_t i;
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	for(i = 0; i <= AMOUNT_OF_MSG; ++i)
	{
		retVal[i] = CyclieBufPut(mem, msg );
	}
	
	free(buffer);
	for(i = 0; i < AMOUNT_OF_MSG; ++i)
	{
    	ASSERT_THAT( 0 == retVal[i] );
    }
    ASSERT_THAT( -1 == retVal[i] );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- CyclieBufGet -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CyclieBufGet_CheckNULL_Memory)
	int retVal;
	char msg[] = "AAAAAA";
	
	retVal = CyclieBufGet(NULL, (void*)msg );
    ASSERT_THAT( -1 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufGet_CheckRegular)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal[2];
	char msg[] = "AAAAAA";
	char msg1[MSG_SIZE];
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	retVal[0] = CyclieBufPut(mem, msg );
	retVal[1] = CyclieBufGet(mem, msg1 );
	free(buffer);
    ASSERT_THAT( 0 == retVal[0] );
    ASSERT_THAT( 0 == retVal[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufGet_CheckUnderflow)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal;
	char msg[MSG_SIZE];
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	retVal = CyclieBufGet(mem, (void*)&msg );
    ASSERT_THAT( -1 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufGet_CheckEqualMsg)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal;
	char msg[] = "AAAAAA";
	char msg1[MSG_SIZE];
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	CyclieBufPut(mem, msg);
	CyclieBufGet(mem, msg1);
	free(buffer);
	retVal = strcmp(msg, msg1);
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufGet_CheckEqualMsgByOrder)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal[AMOUNT_OF_MSG];
	char msg[] = "AAAAAA";
	char msg1[AMOUNT_OF_MSG][MSG_SIZE];
	size_t i;
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, AMOUNT_OF_MSG, MSG_SIZE);
	for(i = 0; i < AMOUNT_OF_MSG; ++i)
	{
	    CyclieBufPut(mem, msg);
	}
	for(i = 0; i < AMOUNT_OF_MSG; ++i)
	{
	    CyclieBufGet(mem, msg1[i]);
	}
	free(buffer);
	for(i = 0; i < AMOUNT_OF_MSG; ++i)
	{
	    retVal[i] = strcmp(msg, msg1[i]);
	    ASSERT_THAT( 0 == retVal[i]);
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CyclieBufGet_CheckAllMsg)
	void* buffer = malloc(MEM_SIZE);
	void* mem;
	int retVal[5];
	char wMsg1[] = "AAAAAA";
	char wMsg2[] = "BBBBBB";
	char wMsg3[] = "CCCCCC";
	char wMsg4[] = "DDDDDD";
	char wMsg5[] = "EEEEEE";
	char msg1[5][MSG_SIZE];
	size_t i;
	
	mem = CyclieBufCreate(buffer, MEM_SIZE, 5, MSG_SIZE);
	CyclieBufPut(mem, wMsg1);
	CyclieBufPut(mem, wMsg2);
	CyclieBufPut(mem, wMsg3);
	CyclieBufPut(mem, wMsg4);
	CyclieBufPut(mem, wMsg5);
	for(i = 0; i < 5; ++i)
	{
	    CyclieBufGet(mem, msg1[i]);
	}
	free(buffer);
    retVal[0] = strcmp(wMsg1, msg1[0]);
    retVal[1] = strcmp(wMsg2, msg1[1]);
    retVal[2] = strcmp(wMsg3, msg1[2]);
    retVal[3] = strcmp(wMsg4, msg1[3]);
    retVal[4] = strcmp(wMsg5, msg1[4]);
    for(i = 0; i < 5; ++i)
	{
        ASSERT_THAT( 0 == retVal[i]);
    }
END_TEST
/*----------------------------------------------------------------------------*/









/********************************* Test Suite *********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(CyclieBuf)
	PRINT(CyclieBufCreate_CheckNULL_Memory)
	PRINT(CyclieBufCreate_CheckNULL_MemSize)
	PRINT(CyclieBufCreate_CheckNULL_AmountOfSize)
	PRINT(CyclieBufCreate_CheckNULL_MsgSize)
	PRINT(CyclieBufCreate_CheckMemTooSmall)
	PRINT(CyclieBufCreate_CheckNotNull)
	
	PRINT(CyclieBufPut_CheckNULL_Memory)
	PRINT(CyclieBufPut_CheckNULL_Data)
	PRINT(CyclieBufPut_CheckNotNULL)
	PRINT(CyclieBufPut_CheckOverflow)
	
	PRINT(CyclieBufGet_CheckNULL_Memory)
	PRINT(CyclieBufGet_CheckRegular)
	PRINT(CyclieBufGet_CheckUnderflow)
	PRINT(CyclieBufGet_CheckEqualMsg)
	PRINT(CyclieBufGet_CheckEqualMsgByOrder)
	PRINT(CyclieBufGet_CheckAllMsg)
END_SET
/*----------------------------------------------------------------------------*/

