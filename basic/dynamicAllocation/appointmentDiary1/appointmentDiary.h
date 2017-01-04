/** 
 *  @file 		appointmentDiary.h
 *  @brief 		header file for appointmentDiary API
 * 
 *  @details 	This API present my implication of Appointment Diary.
 *			 	The implication is for one day that the user can create as many as he wants.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 		2016-12-15    
 *
 *  @bug 		No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __APPOINTMENT_DIARY_H__
#define __APPOINTMENT_DIARY_H__

#include <stddef.h>	/* for size_t */





/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef enum 
{
    OK,				/* If the return was as expected */
    ERROR_NULL,		/* If a pointer point to null  */
    ILLEGAL_HOUR, 	/* If the endHour <= beginHour of the meeting or 1 of the parmeters is overlap the next day  */
    REALLOC_FAIL,	/* If there is no more space available and the increse prossess has failed  */
    OVERBOOK, 		/* If there is no room for this meeting in the calendar */
    OVERFLOW,		/* If there is no more space available and incSize value is 0  */
    FIND_FAILED,		/* If it can't find an appointment of this hour  */
    MEETING_INSERT 	/* If meeting has been created  */
} ERRORS;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef struct meetingType Meeting;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef struct ManagerType DayPtr;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function open a new diary for one day calendar.
 * @details     Function that create 2 dynamic allocation: 
 *				1. for the day info 
 *				2. for the array of meetings
 *
 * Time Complexity: O(1).
 *
 *
 * @param       _numOfApp 		= The total capacity for amount of appointment for that specific day 
 * @param       _addSize 		= In how much to increase the size when the space is run out
 *
 * @return		Return address of the structure DayPtr or NULL 
 */
DayPtr* CreateDay(size_t _numOfApp, size_t _addSize);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function open a new meeting in the calendar.
 * @details     Function that creat 1 dynamic allocation, with all the data of the meeting.
 *
 * Time Complexity: O(1).
 *
 *
 * @param       _stHour 		= The hour when the meeting is start
 * @param       _finHour 		= The hour when the meeting is end
 * @param       _room 			= In which room the meeting take place
 *
 * @return		Return address of the structure Meeting or NULL 
 */
Meeting* CreateMeeting(double _stHour, double _finHour, size_t _room);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function add the new meeting already created to the calendar.
 * @details     Function that add the meeting structure in the right index of the
 * 				day array, that sorted by the start hour of each meeting.
 *
 * Time Complexity: O(n).
 *
 *
 * @param       *_infoPtr 		= The address of the structurer
 * @param       _meetingPtr 	= The address of the meeting
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		OK				= If the return was as expected
 * @retval      ERROR_NULL 		= If the pointer point to null
 * @retval      ERR_OVERFLOW 	= If the function reach it max space in DA and inc_size == 0
 * @retval      REALLOC_FAIL 	= If there is no more space available and increse has failed 
 */
ERRORS InsertMeeting(DayPtr* _infoPtr, Meeting* _meetingPtr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function remove a meeting already created from the calendar.
 * @details     Function that remove meeting from the array dynamic allocation and
 *				delete all of it's data.
 *
 * Time Complexity: O(n).
 *
 *
 * @param       *_infoPtr 		= The address of the structuer
 * @param       _stHour 		= search the meeting by the start hour of the meeting
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		OK				= If the return was as expected
 * @retval      ERROR_NULL 		= If the pointer point to null
 * @retval      FIND_FAILED		= If the function tries to remove index that is not yet exist  
 */
ERRORS RemoveMeeting(DayPtr* _infoPtr, double _stHour);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function find a meeting already created from the calendar.
 * @details     Function that find meeting from a given day, and return it to the user.
 *
 * Time Complexity: O(n).
 *
 *
 * @param       *_infoPtr 		= The address of the structurer
 * @param       _stHour 		= search the meeting by the start hour of the meeting
 *
 * @return		Return address of the structure or NULL 
 */
Meeting* FindMeeting(DayPtr* _infoPtr, double _stHour);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function destroy all meetings created for a given day calendar.
 * @details     Function that free all data that created, include the user info for that
 *				specific day. The user can't destroy the same day twice.
 *
 * Time Complexity: O(n).
 *
 *
 * @param       *_infoPtr 		= The address of the structurer
 *
 * @return		void 
 */
void DestroyDiary(DayPtr* _infoPtr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       The function print all meetings created for that day in the calendar.
 * @details     Function that search and print all meetings for that day in the calendar
 *				sorted by the start hour of the meetings.
 *
 * Time Complexity: O(n).
 *
 *
 * @param       *_infoPtr 		= The address of the structurer
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		OK				= If the return was as expected
 * @retval      ERROR_NULL 		= If the pointer point to null 
 */
ERRORS PrintDay(DayPtr *_InfoPtr);
/*----------------------------------------------------------------------------*/





#endif /* __APPOINTMENT_DIARY_H__ */
