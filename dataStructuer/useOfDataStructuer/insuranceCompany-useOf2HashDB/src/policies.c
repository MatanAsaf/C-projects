/** 
 *  @file 		policies.c
 *  @brief 		src file for API functions for manging policies in insurance company
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

#include "policies.h"	/* header file */
#include "hashMap.h"	/* header file for HashMap */
#include <string.h>     /* for memcpy */
#include <stddef.h>     /* for size_t */
#include <stdio.h>      /* for perror */
#include <errno.h>      /* for errno */

#define NUMBER_OF_BUCKETS 	(100)
#define CHECK_NULL(param)	do{ if(NULL == (param) ) { return NULL;}  } while(0)




/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct Record
{
    size_t m_policyNo; 	/* Policy number */
    size_t m_licenseNo; /* License number */
    size_t m_year; 		/* The year the car has been made */
} Record;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
struct PolicyDB
{
    HashMap* m_policyBuffer; 	    /* Pointer to hashmap1 that the key is by policyNo */
    HashMap* m_licenseBuffer; 	    /* Pointer to hashmap2 that the key is by licenseNo */
    size_t m_policyCounter; /* The year the car has been made */
};
/*----------------------------------------------------------------------------*/





/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
static size_t GenerateKey(void* _key);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static int CheckEquality(void* _firstKey, void* _secondKey);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void DestroyRecords(void* _record);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static size_t GeneratePolicyNo(PolicyDB* _myDB);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static int PrintRecordByYear(void* _key, void* _value, void* _context);
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
PolicyDB* CreateDB()
{
    PolicyDB* myDB = (PolicyDB*)malloc(sizeof(PolicyDB));
    HashMap* hash1;
    HashMap* hash2;
    
    CHECK_NULL(myDB);
    
    hash1 = HashMap_Create(NUMBER_OF_BUCKETS, GenerateKey, CheckEquality);
    if(NULL == hash1)
    {
        free(myDB);
        return NULL;
    }
    
    hash2 = HashMap_Create(NUMBER_OF_BUCKETS, GenerateKey, CheckEquality);
    if(NULL == hash2)
    {
        HashMap_Destroy(&hash1, NULL, DestroyRecords);
        free(myDB);
        return NULL;
    }
    
    myDB->m_policyCounter = 0;
    myDB->m_policyBuffer = hash1;
    myDB->m_licenseBuffer = hash2;
    
    return myDB;
}
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
int NewPolicy(PolicyDB* _myDB, size_t _licenseNo, size_t _year)
{
    Record* newRecord;
    size_t policyNumber;
    
    if(NULL == _myDB || 0 == _licenseNo || 1950 > _year)
    {
        return -1;
    }
    
    newRecord = (Record*)malloc(sizeof(Record));
    if(NULL == newRecord)
    {
        return -1;
    }
    
    policyNumber = GeneratePolicyNo(_myDB);
    newRecord->m_policyNo = policyNumber;
    newRecord->m_licenseNo = _licenseNo;
    newRecord->m_year = _year;
    
    if(MAP_SUCCESS != HashMap_Insert(_myDB->m_policyBuffer, (void*)policyNumber, (void*)newRecord) )
    {
        free(newRecord);
        return -1;
    }
    
    if(MAP_SUCCESS != HashMap_Insert(_myDB->m_licenseBuffer, (void*)_licenseNo, (void*)newRecord) )
    {
        HashMap_Remove(_myDB->m_policyBuffer, (void*)policyNumber, NULL, NULL);
        free(newRecord);
        return -1;
    }
    
    return 0;
}
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
int ShowPolicyByLicenseNo(PolicyDB* _myDB, size_t _licenseNo)
{
    Record* foundRecord;
    
    if(NULL == _myDB || 0 == _licenseNo)
    {
        return -1;
    }
    
    if(MAP_SUCCESS != HashMap_Find(_myDB->m_licenseBuffer, (void*)_licenseNo, (void**)&foundRecord) )
    {
        return -1;
    }
    
    printf("Found record by license Number: Policy %u, License %u, Year %u\n", foundRecord->m_policyNo, foundRecord->m_licenseNo, foundRecord->m_year);
    
    return 0;
}
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
int ShowPolicyByPolicyNo(PolicyDB* _myDB, size_t _policyNo)
{
    Record* foundRecord;
    
    if(NULL == _myDB || 0 == _policyNo)
    {
        return -1;
    }
    
    if(MAP_SUCCESS != HashMap_Find(_myDB->m_policyBuffer, (void*)_policyNo, (void**)&foundRecord) )
    {
        return -1;
    }
    
    printf("Found record by license Number: Policy %u, License %u, Year %u\n", foundRecord->m_policyNo, foundRecord->m_licenseNo, foundRecord->m_year);
    
    return 0;
}
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
int ListPoliciesByYear(PolicyDB* _myDB, size_t _year)
{
	if(NULL == _myDB)
    {
        return -1;
    }
    
    HashMap_ForEach(_myDB->m_policyBuffer,PrintRecordByYear,(void*)_year);
    
	return 0;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Destroy the data base
 * @details     The function destroy each record on the data base, and the DB it self
 *
 *
 * @return		void
 */
void Destroy(PolicyDB* _myDB)
{
    if(NULL == _myDB)
    {
        return;
    }
    
    HashMap_Destroy( &(_myDB->m_policyBuffer), NULL, NULL );
    HashMap_Destroy( &(_myDB->m_licenseBuffer), NULL, DestroyRecords );
    
    free(_myDB);
    
    return;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
static size_t GenerateKey(void* _key)
{
    return ( (size_t)_key % NUMBER_OF_BUCKETS);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static int CheckEquality(void* _firstKey, void* _secondKey)
{
    if( _firstKey == _secondKey )
    {
        return 1;
    }
    
    return 0;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static void DestroyRecords(void* _record)
{
    free(_record);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static size_t GeneratePolicyNo(PolicyDB* _myDB)
{
    return ++(_myDB->m_policyCounter);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
static int PrintRecordByYear(void* _key, void* _value, void* _context)
{
	size_t year = (size_t)_context;
	Record* record = (Record*)_value;
	
	if( year == (record->m_year) )
	{
	    printf("Found record by by year: Policy %u, License %u, year %u\n", record->m_policyNo, record->m_licenseNo, record->m_year);	
	}
	return 0; 
}
/*----------------------------------------------------------------------------*/
