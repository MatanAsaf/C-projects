/** 
 *  @file tests.c
 *  @brief tests file for appointmentDiary API
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-15    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "appointmentDiary.h"	/* header file */
#include "matan_test.h"			/* def of unit test */
#include <stdio.h>  			/* for printf */
#include <stdlib.h>				/* for size_t && malloc && free */

#define N_OF_APP (10)			/* Number of appointments to test */



/*************************** Tests for API functions **************************/
/*--------------------------------- CreateDay --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CreateDay_CheckNull)
	ASSERT_THAT( NULL == CreateDay(0, 0) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CreateDay_CheckNotNull_numOfApp)
	DayPtr* ip = CreateDay(10, 0);
	DayPtr* checkResult;
	
	checkResult = ip;
	
	DestroyDiary(ip);
	
	ASSERT_THAT( NULL != checkResult );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CreateDay_CheckNotNull_addSize)
	DayPtr* ip = CreateDay(0, 10);
	DayPtr* checkResult;
	
	checkResult = ip;
	
	DestroyDiary(ip);
	
	ASSERT_THAT( NULL != checkResult );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- CreateMeeting ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(CreateMeeting_CheckIllegalInput_StartHour)
	Meeting* app1 = CreateMeeting(-8, 10, 111);
	
	ASSERT_THAT( NULL == app1 );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CreateMeeting_CheckIllegalInput_EndHour)
	Meeting* app1 = CreateMeeting(10.33, 25, 111);
	
	ASSERT_THAT( NULL == app1 );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CreateMeeting_CheckIllegalInput_EndHourIsBeforeStartHour)
	Meeting* app1 = CreateMeeting(10, 9.5, 111);
	
	ASSERT_THAT( NULL == app1 );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(CreateMeeting_CheckNotNull)
	Meeting* app1 = CreateMeeting(10.3, 11.7, 100);
	Meeting* checkResult;
	
	checkResult = app1;
	
	free(app1);
	
	ASSERT_THAT( NULL != checkResult );
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- InsertMeeting ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckNull_Day)
	Meeting* app1 = CreateMeeting(10.3, 11.7, 100);
	ERRORS status;
	
	status = InsertMeeting(NULL, app1);
	
	free(app1);
	
	ASSERT_THAT( ERROR_NULL == status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckNull_App)
	DayPtr* ip = CreateDay(10, 10);
	ERRORS status;
	
	status = InsertMeeting(ip, NULL);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( ERROR_NULL == status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckNotNull)
	DayPtr* ip = CreateDay(1, 0);
	Meeting* app1 = CreateMeeting(10.5, 11.5, 50);
	ERRORS status;
	
	status = InsertMeeting(ip, app1);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckOverBook_Equal)
	DayPtr* ip = CreateDay(2, 0);
	Meeting* app1 = CreateMeeting(10.5, 11.5, 50);
	Meeting* app2 = CreateMeeting(10.5, 11.5, 55);
	ERRORS status[2];
	
	status[0] = InsertMeeting(ip, app1);
	status[1] = InsertMeeting(ip, app2);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status[0] && OVERBOOK == status[1]);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckOverBook_StartHourOverlap)
	DayPtr* ip = CreateDay(2, 0);
	Meeting* app1 = CreateMeeting(10.5, 11, 50);
	Meeting* app2 = CreateMeeting(10.5, 12, 55);
	ERRORS status[2];
	
	status[0] = InsertMeeting(ip, app1);
	status[1] = InsertMeeting(ip, app2);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status[0] && OVERBOOK == status[1]);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckOverBook_EndHourOverlap)
	DayPtr* ip = CreateDay(2, 0);
	Meeting* app1 = CreateMeeting(10.5, 12, 50);
	Meeting* app2 = CreateMeeting(11.5, 12, 55);
	ERRORS status[2];
	
	status[0] = InsertMeeting(ip, app1);
	status[1] = InsertMeeting(ip, app2);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status[0] && OVERBOOK == status[1]);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckRealloc_OK)
	DayPtr* ip = CreateDay(1, 1);
	Meeting* app1 = CreateMeeting(10.5, 11, 50);
	Meeting* app2 = CreateMeeting(11.5, 12, 55);
	ERRORS status[2];
	
	status[0] = InsertMeeting(ip, app1);
	status[1] = InsertMeeting(ip, app2);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status[0] && OK == status[1]);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckRealloc_Overflow)
	DayPtr* ip = CreateDay(1, 0);
	Meeting* app1 = CreateMeeting(10.5, 11, 50);
	Meeting* app2 = CreateMeeting(11.5, 12, 55);
	ERRORS status[2];
	
	status[0] = InsertMeeting(ip, app1);
	status[1] = InsertMeeting(ip, app2);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status[0] && OVERFLOW == status[1]);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(InsertMeeting_CheckShifting)
	DayPtr* ip = CreateDay(2, 0);
	Meeting* app1 = CreateMeeting(10.5, 11, 50);
	Meeting* app2 = CreateMeeting(9.5, 10.45, 55);
	ERRORS status[2];
	
	status[0] = InsertMeeting(ip, app1);
	status[1] = InsertMeeting(ip, app2);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status[0] && OK == status[1]);
END_TEST
/*----------------------------------------------------------------------------*/


/*------------------------------- RemoveMeeting ------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(RemoveMeeting_CheckNull_Day)
	ASSERT_THAT( ERROR_NULL == RemoveMeeting(NULL, 10.3) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveMeeting_CheckNotFound)
	DayPtr* ip = CreateDay(2, 0);
	Meeting* app = CreateMeeting(10.5, 11, 50);
	ERRORS status;
	
	InsertMeeting(ip, app);
	status = RemoveMeeting(ip, 12);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( FIND_FAILED == status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveMeeting_CheckFound)
	DayPtr* ip = CreateDay(N_OF_APP, 0);
	Meeting* app[N_OF_APP];
	ERRORS status[N_OF_APP];
	size_t i;
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		app[i] = CreateMeeting(i, i+1, 500);
		InsertMeeting(ip, app[i]);
	}
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		status[i] = RemoveMeeting(ip, N_OF_APP - 1 - i);
	}
	
	DestroyDiary(ip);
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		ASSERT_THAT( OK == status[i]);
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(RemoveMeeting_CheckShifting)
	DayPtr* ip = CreateDay(N_OF_APP, 0);
	Meeting* app[N_OF_APP];
	ERRORS status[N_OF_APP];
	size_t i;
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		app[i] = CreateMeeting(i, i+1, 500);
		InsertMeeting(ip, app[i]);
	}
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		status[i] = RemoveMeeting(ip, i);
	}
	
	DestroyDiary(ip);
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		ASSERT_THAT( OK == status[i]);
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*-------------------------------- FindMeeting -------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(FindMeeting_CheckNull_Day)
	ASSERT_THAT( NULL == FindMeeting(NULL, 10.3) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FindMeeting_CheckNotFound)
	DayPtr* ip = CreateDay(2, 0);
	Meeting* app = CreateMeeting(10.5, 11, 50);
	Meeting* status;
	
	InsertMeeting(ip, app);
	status = FindMeeting(ip, 12);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( NULL == status);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(FindMeeting_CheckFound)
	DayPtr* ip = CreateDay(N_OF_APP, 0);
	Meeting* app[N_OF_APP];
	Meeting* status[N_OF_APP];
	size_t i;
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		app[i] = CreateMeeting(i, i+1, 500);
		InsertMeeting(ip, app[i]);
	}
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		status[i] = FindMeeting(ip, i);
	}
	
	DestroyDiary(ip);
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		ASSERT_THAT( app[i] == status[i]);
	}
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- PrintDay ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(PrintDay_CheckNull_Day)
	ASSERT_THAT( ERROR_NULL == PrintDay(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(PrintDay_CheckOK)
	DayPtr* ip = CreateDay(N_OF_APP, 0);
	Meeting* app[N_OF_APP];
	ERRORS status;
	size_t i;
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		app[i] = CreateMeeting(i + 8, i + 9, 500);
		InsertMeeting(ip, app[i]);
	}
	
	status = PrintDay(ip);
	
	DestroyDiary(ip);
	
	ASSERT_THAT( OK == status);
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- SaveDiary --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(SaveDiary_CheckNull)
	ASSERT_THAT( ERROR_NULL == SaveDiary(NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(SaveDiary_CheckOneElement)
	DayPtr* ip = CreateDay(1, 0);
	Meeting* app = CreateMeeting(10.5, 11, 50);
	DayPtr* ipLoad;
	ERRORS status[2];
	
	InsertMeeting(ip, app);
	status[0] = SaveDiary(ip);
	ipLoad = LoadDiary();
	status[1] = RemoveMeeting(ipLoad, 10.5);
	
	DestroyDiary(ip);
	DestroyDiary(ipLoad);
	
	ASSERT_THAT( OK == status[0] && OK == status[1]);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(SaveDiary_CheckFullDiary)
	DayPtr* ip = CreateDay(N_OF_APP, 0);
	Meeting* app[N_OF_APP];
	DayPtr* ipLoad;
	ERRORS status[N_OF_APP];
	size_t i;
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		app[i] = CreateMeeting(i + 8, i + 9, 111);
		InsertMeeting(ip, app[i]);	
	}
	
	SaveDiary(ip);
	ipLoad = LoadDiary();
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		status[i] = RemoveMeeting(ipLoad, i + 8);
	}
	
	DestroyDiary(ip);
	DestroyDiary(ipLoad);
	
	for(i = 0; i < N_OF_APP; ++i)
	{
		ASSERT_THAT( OK == status[i]);
	}
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(appointmentDiary API)
	PRINT(CreateDay_CheckNull)
	PRINT(CreateDay_CheckNotNull_numOfApp)
	PRINT(CreateDay_CheckNotNull_addSize)
	
	PRINT(CreateMeeting_CheckIllegalInput_StartHour)
	PRINT(CreateMeeting_CheckIllegalInput_EndHour)
	PRINT(CreateMeeting_CheckIllegalInput_EndHourIsBeforeStartHour)
	PRINT(CreateMeeting_CheckNotNull)

	PRINT(InsertMeeting_CheckNull_Day)
	PRINT(InsertMeeting_CheckNull_App)
	PRINT(InsertMeeting_CheckNotNull)
	PRINT(InsertMeeting_CheckOverBook_Equal)
	PRINT(InsertMeeting_CheckOverBook_StartHourOverlap)
	PRINT(InsertMeeting_CheckOverBook_EndHourOverlap)
	PRINT(InsertMeeting_CheckRealloc_OK)
	PRINT(InsertMeeting_CheckRealloc_Overflow)
	PRINT(InsertMeeting_CheckShifting)
	
	PRINT(RemoveMeeting_CheckNull_Day)
	PRINT(RemoveMeeting_CheckNotFound)
	PRINT(RemoveMeeting_CheckFound)
	PRINT(RemoveMeeting_CheckShifting)
	
	PRINT(FindMeeting_CheckNull_Day)
	PRINT(FindMeeting_CheckNotFound)
	PRINT(FindMeeting_CheckFound)
	
	PRINT(PrintDay_CheckNull_Day)
	PRINT(PrintDay_CheckOK)
	
	PRINT(SaveDiary_CheckNull)
	PRINT(SaveDiary_CheckOneElement)
	PRINT(SaveDiary_CheckFullDiary)
END_SET
/*----------------------------------------------------------------------------*/

