/** 
 *  @file 		policies.h
 *  @brief 		header file for API functions for manging policies in insurance company
 * 
 *  @details 	The API stores functions to operate and manage policies of 
 *				clients in insurance company.
 *				Implemented with two separate hash maps.
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
 
#ifndef __POLICIES_H__
#define __POLICIES_H__


#include <stdlib.h>     /* for size_t */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct PolicyDB PolicyDB;
/*----------------------------------------------------------------------------*/




/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       Create new data base to store records
 * @details     The function create data base of type PolicyDB that unique for each user
 *
 *
 * @return		Return NULL OR data base pointer myDB
 * @retval		NULL		= 	On error when the process of make the data base
 * @retval 		_myDB	    =	Data base pointer that return on success
 */
PolicyDB* CreateDB();
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Create a new record
 * @details     Create a new record from the user input variables 
 *
 *
 * @return		Return 0 OR -1 
 * @retval		-1		    = 	On error when initialize OR when error on insert
 * @retval 		0   	    =	On success
 */
int NewPolicy(PolicyDB* _myDB, size_t _licenseNo, size_t _year);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Show the user the record data  
 * @details     The function get from the user the record license number, found
 * it and display it to the user
 *
 *
 * @return		Return 0 OR -1 
 * @retval		-1		    = 	On error when initialize OR when not found
 * @retval 		0   	    =	On success
 */
int ShowPolicyByLicenseNo(PolicyDB* _myDB, size_t _licenseNo);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Show the user the record data  
 * @details     The function get from the user the record policy number, found
 * it and display it to the user
 *
 *
 * @return		Return 0 OR -1 
 * @retval		-1		    = 	On error when initialize
 * @retval 		0   	    =	On success
 */
int ShowPolicyByPolicyNo(PolicyDB* _myDB, size_t _policyNo);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Show the user the all record data for the given year  
 * @details     The function get from the user the year as param, found all records
 * that match this year, and display it to the user
 *
 *
 * @return		Return 0 OR -1 
 * @retval		-1		    = 	On error when initialize OR when noting has found
 * @retval 		0   	    =	On success
 */
int ListPoliciesByYear(PolicyDB* _myDB, size_t _year);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Destroy the data base
 * @details     The function destroy each record on the data base, and the DB it self
 *
 *
 * @return		void
 */
void Destroy(PolicyDB* _myDB);
/*----------------------------------------------------------------------------*/

#endif /* __POLICIES_H__ */
