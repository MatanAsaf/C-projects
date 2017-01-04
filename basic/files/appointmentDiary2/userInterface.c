/** 
 *  @file 		userInterface.c
 *  @brief 		src file userInterface.c for appointmentDiary API
 * 
 *  @details 	This file present a menu commands for the user to mange his appointment diary.
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
#include <stdio.h>
#include <stdlib.h> 			/* for size_t & exit() */


/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 *	This function present to the user the the message dialog to create new diary,
 *	and return the diary pointer. 
 */
static DayPtr* UserFirstMenu(void);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	This function present to the user the the message dialog to create new Meeting,
 *	and return the meeting pointer. 
 */
static Meeting* UserSecondMenu(int *statusMeeting);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	This function check which status has return from each of the API function, 
 *  and present the user the right message. 
 */
static ERRORS CheckStatus(ERRORS status);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	This function present to the user the the message dialog to insert meeting data. 
 */
static Meeting* CreateMeetingMenu(int *statusMeeting, Meeting* _orignalApp);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	Present full menu. 
 */
static void PresentMenu(void);
/*----------------------------------------------------------------------------*/





/********************************** USER MENU *********************************/
/*----------------------------------------------------------------------------*/
int main ()
{ 
    int statusMeeting = 0; /* to check if the user already create a meeting: 0 = false, 1 = true  */
    double beginHour;
    ERRORS status = OK;
    DayPtr* ip;
    Meeting* addMeeting = NULL;
    int command = 8;
    
    /* Loop 1 - Create Diary */
    ip = UserFirstMenu();
    
    /* Loop 2 - Main Menu */
    while( command != 0 )
    {
        switch (command)
        {
            case 1:
                addMeeting = CreateMeetingMenu(&statusMeeting, addMeeting);
                if(addMeeting == NULL)
                {
                    printf("ERROR: Meeting has NOT been created.\n");
                    printf("Please check your input and try again, if this message repeat itself-try again later\n");
                    command = 8;
                    break;    
                }
                command = 2;
                break;
            case 2:
                status = InsertMeeting(ip, addMeeting);
                status = CheckStatus(status);
                if(status == OK)
                {
                    printf("Meeting has been insert\n\n");    
                }
                command = 8;
                break;
            case 3:
                printf("Please insert you meeting begin hour to remove:\n");
                scanf("%lf",&beginHour);
                status = RemoveMeeting(ip, beginHour);
                status = CheckStatus(status);
                if(status == OK)
                {
                    printf("Meeting has been remove\n\n");    
                }
                command = 8;
                break;
            case 4:
                printf("Please insert you meeting begin hour to search:\n");
                scanf("%lf",&beginHour);
                status = RemoveMeeting(ip, beginHour);
                status = CheckStatus(status);
                if(status == OK)
                {
                    printf("Meeting has been found\n\n");  
                    break;  
                }
                command = 8;
                break;
            case 5:
                DestroyDiary(ip);
                printf("Diary has been remove\n\n");
                ip = UserFirstMenu();
                addMeeting = UserSecondMenu(&statusMeeting);
				if(NULL == addMeeting)
				{
					return 0;
				}
                command = 8;
                break;
            case 6:
                printf("Your schedule meeting for the day is:\n\n");
                status = PrintDay(ip);
                CheckStatus(status);
                command = 8;
                break;
            case 7:
                status = SaveDiary(ip);
                CheckStatus(status);
                if(OK == status)
                {
                	printf("Your diary has been save!\n");
                	printf("Now you can use this latest version the next time you log in\n\n");
                }
                command = 8;
                break;
            case 8:
                PresentMenu();
                scanf("%d",&command);
                break;
            case 9:
                exit(0);
                break;
            default:
                printf("Wrong command, please check again\n\n");
                command = 8;
                break;
        }
    }
    
    DestroyDiary(ip);
    return 0;
}





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 *	This function present to the user the the message dialog to create new diary,
 *	and return the diary pointer. 
 */
static DayPtr* UserFirstMenu(void)
{
    int command = 0;
    size_t size; 
    size_t inc_size;
	DayPtr *ip;
    
    /* Loop 1*/
    printf("MENU: \n 1 = Create new appointment diary\n 2 = Load your previous diary\n 9 = Exit this app\n");
    scanf("%d",&command);
    
	while( command != -1 )
    {
        switch (command)
        {
            case 1:
                printf("Please insert you diary details\n");
                printf("Please insert your start amount of meeting:\n");
                scanf("%u",&size);
                printf("Please insert your add amount of meeting, for cases you will want to add more then the original size:\n");
                scanf("%u",&inc_size);
                
                ip = CreateDay(size, inc_size);
                if(ip == NULL)
                {
                    printf("\nERROR: diary has NOT been created.\n"); 
                    printf("Please check your input and try again, if this message repeat itself-try again later\n\n");
                    command = 1; 
                    break;  
                }
                
                printf("\nDiary has been created\n\n");
                command = -1;
                break;
            
            case 2:
            	ip = LoadDiary();
            	if(ip == NULL)
                {
                	printf("\nERROR: diary has NOT been load.\n"); 
                	printf("you can only load your previous version of your diary if you save it before exit the last time you use it\n\n");
                	command = 1; 
                	break;
                }
                
                printf("\nDiary has been load succesfuly\n\n");
                command = -1; 
                break;
               
            case 9:
                exit(0);
                break;
                
            default:
                printf("Wrong command, please check again\n\n");
                printf("MENU: \n 1 = Create new appointment diary\n 9 = Exit this app\n");
                scanf("%d",&command);
                break;
        }
        
    }
    
    return ip;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	This function present to the user the the message dialog to create new Meeting,
 *	and return the meeting pointer. 
 */
static Meeting* UserSecondMenu(int *statusMeeting)
{
    int command = 0;
    Meeting* addMeeting = NULL;
    
	/* Loop 2 - Create First Appointment */
    while( 9 != command )
    {
    	addMeeting = CreateMeetingMenu(statusMeeting, addMeeting);
		if(NULL == addMeeting)
		{
		    printf("\nERROR: Meeting has NOT been created.\n");
		    printf("Please check your input and try again, if this message repeat itself-try again later\n");
		    printf("Press 9 for exit this app or any number for create new appointment\n\n");
		    scanf("%d",&command);
		    continue;   
		}
		
		return addMeeting;
    }
    
    return NULL; 
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	This function check which status has return from each of the API function, 
 *  and present the user the right message. 
 */
static ERRORS CheckStatus(ERRORS status)
{
    switch(status)
    {
        case ERROR_NULL:
            printf("ERROR_NULL: Please check if you created a meeting first\n\n");
            return ERROR_NULL;
        case ILLEGAL_HOUR:
            printf("ILLEGAL_HOUR: Please make sure that in your input the end Hour is after the begin Hour of the meeting"); 
            printf(" and bote of your parameters are less then 23.99 and bigger then 0\n\n");
            return ILLEGAL_HOUR;
        case REALLOC_FAILED:
            printf("REALLOC_FAIL: Your diary reach it's max size, and there are no more room in the pc memory to increase it, close some open programs and try agin \n\n");
            return REALLOC_FAILED;
        case OVERBOOK:
            printf("OVERBOOK: Your meeting hours overlap existents meeting\n\n");
            return OVERBOOK;
        case OVERFLOW:
            printf("OVERFLOW: Your diary reach it's max size, no room for any more meetings try remove some before insert new one\n\n");
            return OVERFLOW;
        case FIND_FAILED:
            printf("FIND_FAIL: There are no meetings that start in that begin hour\n\n");
            return FIND_FAILED;
        case CREATE_FILE_FAILED:
            printf("CREATE_FILE_FAILED: There was a technical problem when saving your diary\n\n");
            return CREATE_FILE_FAILED;
        default:
            return OK;
    }
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	This function present to the user the the message dialog to insert meeting data. 
 */
static Meeting* CreateMeetingMenu(int *statusMeeting, Meeting* _orignalApp)
{
    double beginHour;
    double endHour;
    size_t roomNumber;
    char answer;
    Meeting* addMeeting;
    
    if(1 == *statusMeeting )
    {
        printf("\nWarning!\nYou have created meeting already and still didn't insert it to your diary\n"); 
        printf("If you continue all your data will be lost, continue (Y/N)?\n");
        scanf("%c",&answer);
        scanf("%c",&answer);
        if(answer == 'N' || answer == 'n')
        {
            return _orignalApp;
        }
    }
    
    printf("Please insert you meeting details\n");
    printf("Please insert you meeting begin hour:\n");
    scanf("%lf",&beginHour);
    printf("Please insert you meeting end hour:\n");
    scanf("%lf",&endHour);
    printf("Please insert you meeting room number:\n");
    scanf("%u",&roomNumber);
    addMeeting = CreateMeeting(beginHour, endHour, roomNumber);
    if(addMeeting != NULL)
    {
        printf("Meeting has been created, but still not in your diary\n");
        *statusMeeting = 1;
        
        return addMeeting;    
    }
    
    return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 *	Present full menu. 
 */
static void PresentMenu(void)
{
	printf("MENU: \n1 = Create appointment\n");
    printf("2 = Insert appointment to diary\n");
    printf("3 = Remove Appointment\n");
    printf("4 = Search Appointment\n"); 
    printf("5 = Destroy all meeting and Diary\n"); 
    printf("6 = Print all your meeting\n");
    printf("7 = Save all your meeting\n");
    printf("8 = Print the menu\n"); 
    printf("9 = Exit this app\n");
    printf("Please insert your command according to the menu\n");
    
    return;
}
/*----------------------------------------------------------------------------*/
