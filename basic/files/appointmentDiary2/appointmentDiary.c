/** 
 *  @file 		appointmentDiary.c
 *  @brief 		src file for appointmentDiary2 API
 * 
 *  @details 	This API is the new version for the my implication of Appointment Diary.
 *				In this version the user now can save and load his latest version of the diary.
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

#include "appointmentDiary.h"	/* header file */
#include <stdlib.h>				/* for size_t && malloc && free */
#include <stdio.h>				/* for printf */

#define MAGIC_NUMBER (1234567890)
#define FILE_NAME "diary.txt"




/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
struct meetingType
{
    double m_beginHour; 	/* When the meeting begin */
    double m_endHour;		/* The end hour of the meeting */
    size_t m_roomNum; 		/* Which room is the meeting */
};
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
struct ManagerType
{
    Meeting** m_buffer; 	/* Hold the address of all meetings */ 
    size_t m_size; 			/* Hold the size of day in elements (array) */
    size_t m_incSize; 		/* if the structcher needed to grow, in how much to do so */
    size_t m_numOfElement;  /* Index number of meeting in that day */
    size_t m_magicNumber; 	/* If the user ask to destroy the structuer, a value that verified that he can do it only once */
};
/*----------------------------------------------------------------------------*/





/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 *	CheckRealloc function check to see if it needed to do realloc, if needed it do it
 */
static ERRORS CheckRealloc(DayPtr* _infoPtr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * SearchMeeting find the meeting with the _stHour and return the index in the 
 * array or -1 for not found
 */
static int SearchMeeting(DayPtr* _infoPtr, double _stHour);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * CheckInputMeeting check to see if the input of a meeting is legal: 
 * _stHour < _finHour /  _stHour &&  _finHour >= 0 _stHour &&  _finHour <= 23.99
 */
static ERRORS CheckInputMeeting(double _stHour, double  _finHour);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * ShiftMeeting function copy the data from array index to the next one (forward or backwards).
 * It's dependent on the condition: 1 for forward, else backwards.
 */
static void ShiftMeeting(DayPtr* _infoPtr, size_t _index, int _condition);
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/**						This is a new function in this update 
 * @brief       The function save all meetings created for that calendar into a file.
 * @details     Function that save all meeting info into a file name "diary.txt".
 *
 * Time Complexity: O(n).
 *
 *
 * @param       *_infoPtr 			= The address of the structurer
 *
 * @return		Status ERRORS that indicate in which state the function ended:
 *
 * @retval 		OK					= If the return was as expected
 * @retval      ERROR_NULL 			= If the pointer point to null
 * @retval      CREATE_FILE_FAILED 	= If there was an error when saving the diary into a file 
 */
ERRORS SaveDiary(DayPtr* _infoPtr)
{
    FILE* fp;
    size_t i = 0;
    
    if( NULL ==  _infoPtr )
    {
        return ERROR_NULL;
    } 
    
    fp = fopen(FILE_NAME, "w");
    if( NULL == fp  )
    {
        return CREATE_FILE_FAILED;
    }

    fprintf(fp, "%u %u %u\n", _infoPtr->m_numOfElement, _infoPtr->m_size, _infoPtr->m_incSize);
    
    while( i < (_infoPtr->m_numOfElement) )
    {
        fprintf(fp, "%f %f %u\n", _infoPtr->m_buffer[i]->m_beginHour, _infoPtr->m_buffer[i]->m_endHour, _infoPtr->m_buffer[i]->m_roomNum);
        ++i;
    }  
     
    fclose(fp);
    
    return OK;  
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**						This is a new function in this update 
 * @brief       The function load all meetings stored in a file and upload the user progress.
 * @details     Function that load all data from a file name "diary.txt" and return a pointer to the diary.
 *
 * Time Complexity: O(n).
 *
* @return		Return address of the structure DayPtr or NULL  
 */
DayPtr* LoadDiary(void)
{
    FILE* fp;
    size_t i = 0;
    size_t size;
    size_t incSize; 
    size_t numOfElement; 
    size_t roomNumber;
    double beginHour;
    double endHour; 
    Meeting *addMeeting;
    DayPtr* ip;
    
    fp = fopen(FILE_NAME, "r");
    if( fp == NULL )
    {
        return NULL;
    }
    
    fscanf(fp, "%u %u %u", &numOfElement, &size, &incSize);
    
    ip = CreateDay(size, incSize);
    if( NULL == ip )
    {
        return NULL;
    }
    
    while( i < numOfElement )
    {
        fscanf(fp, "%lf %lf %u" ,&beginHour, &endHour, &roomNumber);
        addMeeting = CreateMeeting(beginHour, endHour, roomNumber);
        InsertMeeting(ip, addMeeting);
        ++i;
    }  
    
    fclose(fp); 
    
    return ip; 
}
/*----------------------------------------------------------------------------*/


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
DayPtr* CreateDay(size_t _numOfApp, size_t _addSize)
{
    DayPtr* infoPtr;
    
    if( ( 0 == _numOfApp) && ( 0 == _addSize ) )
    {
        return NULL;
    }
    
    infoPtr = (DayPtr*)malloc( sizeof(DayPtr) );
    if( NULL == infoPtr )
    {
        return NULL;
    }
    
    infoPtr->m_buffer = (Meeting**)malloc( sizeof(Meeting) * _numOfApp );
    if( NULL == infoPtr->m_buffer)
    {
        free(infoPtr);
        return NULL;
    }
    
    infoPtr->m_size = _numOfApp; 
    infoPtr->m_incSize = _addSize;
    infoPtr->m_numOfElement = 0;
    infoPtr->m_magicNumber = MAGIC_NUMBER;
    
    return infoPtr;
}
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
Meeting* CreateMeeting(double _stHour, double _finHour, size_t _room)
{
    Meeting* appPtr;
    
    if( ILLEGAL_HOUR == CheckInputMeeting(_stHour, _finHour) )
    {
        return NULL;
    }
    
    appPtr = (Meeting*)malloc( sizeof(Meeting) );
    if( NULL == appPtr )
    {
        return NULL;
    }
    
    appPtr->m_beginHour = _stHour; 
    appPtr->m_endHour = _finHour;
    appPtr->m_roomNum = _room;
    
    return appPtr;
}
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
 * @retval      REALLOC_FAILED 	= If there is no more space available and increse has failed 
 */
ERRORS InsertMeeting(DayPtr* _infoPtr, Meeting* _meetingPtr)
{
    size_t index = 0;
    size_t nItems;
    ERRORS status;
    
    if( ( NULL == _infoPtr ) || ( NULL == _meetingPtr ) )
    {
        return ERROR_NULL;
    }
    
    nItems = _infoPtr->m_numOfElement;
    
    /* Find the index where the meeting needed to be position at the array */
    while( ( index < nItems ) && ( _meetingPtr->m_beginHour >= (_infoPtr->m_buffer[index])->m_endHour ) )
    {
        ++index;   
    }
    
    /* if this new meeting end after the current meeting start then overflow */
    if( index < nItems && _meetingPtr->m_endHour > (_infoPtr->m_buffer[index])->m_beginHour)
    {
    	return OVERBOOK;	
    }
    
    /* Call to CheckRealloc function to check if there is at least 1 more space in the array for this meeting */ 
    status = CheckRealloc(_infoPtr);
    if( OK != status)
    {
    	if( status == OVERFLOW)
		{
		    return OVERFLOW;
		}
		
		return REALLOC_FAILED;
    }
    
    /* Update numOfElement after before placement (and before shifting) */
    ++(_infoPtr->m_numOfElement);
    
    /* check to see if needed to Shift all meeting in the array by 1 place forward */
    if( index < nItems )
    {
        ShiftMeeting(_infoPtr, index, 1);
    }
    
    /* Place the meeting in the original index and update numOfElement*/
    _infoPtr->m_buffer[index] = _meetingPtr;
    
        
    return OK;   
}
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
ERRORS RemoveMeeting(DayPtr* _infoPtr, double _stHour)
{
    int index;
    
    if( NULL == _infoPtr )
    {
        return ERROR_NULL;
    }
    
    /* Find the index of that meeting */
    index = SearchMeeting(_infoPtr, _stHour);
    if( -1 == index )
    {
        return FIND_FAILED;
    }
    
    /*Remove this meeting from the diary day array */
    free(  _infoPtr->m_buffer[index] );
    
    /* Shift all meeting in the array by 1 place back */
    ShiftMeeting(_infoPtr, (size_t)index, 0);
    
    /* Update numOfElement*/
    --(_infoPtr->m_numOfElement);
    
    return OK;
}
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
Meeting* FindMeeting(DayPtr* _infoPtr, double _stHour)
{
    int index;
    
    if( NULL == _infoPtr )
    {
        return NULL;
    }
    
    index = SearchMeeting(_infoPtr, _stHour);
    if( -1 == index )
    {
        return NULL;
    }
    
    return (_infoPtr->m_buffer[index]);
}
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
void DestroyDiary(DayPtr* _infoPtr)
{
    size_t index = 0;
    
    if( NULL == _infoPtr || MAGIC_NUMBER != _infoPtr->m_magicNumber )
    {
    	return;
    }
        
    while( index < (_infoPtr->m_numOfElement) )
    {
        free(_infoPtr->m_buffer[index]);
        ++index;
    }

    _infoPtr->m_magicNumber = 987654321;
    free(_infoPtr->m_buffer);
    free(_infoPtr);
    
    return;
}
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
ERRORS PrintDay(DayPtr *_infoPtr)
{
    size_t index = 0;
    
    if( NULL == _infoPtr )
    {
        return ERROR_NULL;
    }
    
    while( index < (_infoPtr->m_numOfElement) )
    {
        printf("Meeting number: %u\n",index);
        printf("Begin Hour-%4.2f\n", _infoPtr->m_buffer[index]->m_beginHour);
        printf("Begin Hour-%4.2f\n", _infoPtr->m_buffer[index]->m_endHour);
        printf("Room Number-%d\n\n\n", _infoPtr->m_buffer[index]->m_roomNum);
        ++index;
    } 
    
    return OK;   
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 *	CheckRealloc function check to see if it needed to do realloc, if needed it do it
 */
static ERRORS CheckRealloc(DayPtr* _infoPtr)
{
    Meeting** tempAddress;
    
    if( _infoPtr->m_numOfElement  < _infoPtr->m_size )
    {
    	return OK;
    }
    
    if( 0 == _infoPtr->m_incSize )
    {
        return OVERFLOW;
    }
        
    tempAddress = (Meeting**)realloc ( _infoPtr->m_buffer , sizeof(Meeting*) * (_infoPtr->m_size + _infoPtr->m_incSize) );
    if( NULL == tempAddress)
    {
        return REALLOC_FAILED;
    }
    
    _infoPtr->m_buffer = tempAddress;
    _infoPtr->m_size += _infoPtr->m_incSize;
    
    return OK;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * SearchMeeting find the meeting with the _stHour and return the index in the 
 * array or -1 for not found
 */
static int SearchMeeting(DayPtr* _infoPtr, double _stHour)
{
    int index = 0;
    
    while( index < (_infoPtr->m_numOfElement) )
    {
        if( (_infoPtr->m_buffer[index])->m_beginHour == _stHour )
        {
            return (index);
        }
        
        ++index;
    }
    
    return -1;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * CheckInputMeeting check to see if the input of a meeting is legal: 
 * _stHour < _finHour /  _stHour &&  _finHour >= 0 _stHour &&  _finHour <= 23.99
 */
static ERRORS CheckInputMeeting( double _stHour, double  _finHour)
{
    if( ( _stHour >= _finHour) || ( 0 > _stHour ) || ( 23.99 <_finHour ) )
    {
        return ILLEGAL_HOUR;
    }
    
    return OK;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * ShiftMeeting function copy the data from array index to the next one (forward or backwards).
 * It's dependent on the condition: 1 for forward, else backwards.
 */
static void ShiftMeeting(DayPtr* _infoPtr, size_t _index, int _condition)
{
    size_t originalIndex = _index;
    
    if( 1 == _condition )
    {
        _index = _infoPtr->m_numOfElement;
        
        while( _index > originalIndex)
        {
            _infoPtr->m_buffer[_index] = _infoPtr->m_buffer[_index - 1];
            --_index;
        }
        
        return;
    }
    
    while( _index < (_infoPtr->m_numOfElement - 1 ) )
    {
         _infoPtr->m_buffer[_index] = _infoPtr->m_buffer[_index + 1];
        ++_index;
    }
    
    return;
}
/*----------------------------------------------------------------------------*/
