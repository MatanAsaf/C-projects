/** 
 *  @file cyclieBufTest.c for cyclieBuf API
 *  @brief unit test for file for API function for cyclieBuf
 * 
 *  @details ...
 * 
 *  @author Author Matan Asaf
 *  @date 2016-12-01    
 *
 *  @bug No known bugs.
 */ 
 

#include "policies.h"   /* header file */  
#include "matan_test.h" /* tests macros file */
#include <stddef.h>       /* for size_t */
#include <stdio.h>       /* for perror */
#include <string.h>       /* for perror */
#include <errno.h>       /* for errno */




/******************************* Tests functions ******************************/
/*--------------------------------- NewPolicy --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(NewPolicy_CheckNULL_Pointer)
	int retVal;
	
	retVal = NewPolicy(NULL, 0, 1960);
    ASSERT_THAT( -1 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(NewPolicy_CheckNULL_License)
	int retVal;
	PolicyDB* buffer = CreateDB();
	PolicyDB* db = buffer;
	
	retVal = NewPolicy(buffer, 0, 1960);
	Destroy(buffer);
    ASSERT_THAT( -1 == retVal && NULL != db);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(NewPolicy_CheckNULL_YearTooSmall)
	int retVal;
	PolicyDB* buffer = CreateDB();
	PolicyDB* db = buffer;
	
	retVal = NewPolicy(buffer, 555, 1949);
	Destroy(buffer);
    ASSERT_THAT( -1 == retVal && NULL != db);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(NewPolicy_CheckNotNULL)
	int retVal;
	PolicyDB* buffer = CreateDB();
	
	retVal = NewPolicy(buffer, 555, 1960);
	Destroy(buffer);
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------- ShowPolicyByLicenseNo --------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByLicenseNo_CheckNULL_Pointer)
	int retVal;
	
	retVal = ShowPolicyByLicenseNo(NULL, 55555);
    ASSERT_THAT( -1 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByLicenseNo_CheckNULL_License)
	int retVal;
	PolicyDB* buffer = CreateDB();
	PolicyDB* db = buffer;
	
	retVal = ShowPolicyByLicenseNo(buffer, 0);
    ASSERT_THAT( -1 == retVal && NULL != db);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByLicenseNo_CheckNotFound)
	int retVal;
	PolicyDB* buffer = CreateDB();
	
	retVal = ShowPolicyByLicenseNo(buffer, 1234567);
	Destroy(buffer);
    ASSERT_THAT( -1 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByLicenseNo_CheckFirstFound)
	int retVal[2];
	PolicyDB* buffer = CreateDB();
	
	retVal[0] = NewPolicy(buffer, 1234567, 1960);
	retVal[1] = ShowPolicyByLicenseNo(buffer, 1234567);
	Destroy(buffer);
    ASSERT_THAT( 0 == retVal[0] && 0 == retVal[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByLicenseNo_CheckFound)
	int retVal;
	PolicyDB* buffer = CreateDB();
	
	NewPolicy(buffer, 111, 1960);
	NewPolicy(buffer, 222, 1985);
	NewPolicy(buffer, 333, 2010);
	NewPolicy(buffer, 444, 2015);
	NewPolicy(buffer, 555, 2012);
	retVal = ShowPolicyByLicenseNo(buffer, 333);
	Destroy(buffer);
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------- ShowPolicyByPolicyNo ---------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByPolicyNo_CheckNULL_Pointer)
	int retVal;
	
	retVal = ShowPolicyByPolicyNo(NULL, 55555);
    ASSERT_THAT( -1 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByPolicyNo_CheckNULL_License)
	int retVal;
	PolicyDB* buffer = CreateDB();
	PolicyDB* db = buffer;
	
	retVal = ShowPolicyByPolicyNo(buffer, 0);
    ASSERT_THAT( -1 == retVal && NULL != db);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByPolicyNo_CheckNotFound)
	int retVal;
	PolicyDB* buffer = CreateDB();
	
	retVal = ShowPolicyByPolicyNo(buffer, 1);
	Destroy(buffer);
    ASSERT_THAT( -1 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByPolicyNo_CheckFirstFound)
	int retVal[2];
	PolicyDB* buffer = CreateDB();
	
	retVal[0] = NewPolicy(buffer, 1234567, 1960);
	retVal[1] = ShowPolicyByPolicyNo(buffer, 1);
	Destroy(buffer);
    ASSERT_THAT( 0 == retVal[0] && 0 == retVal[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ShowPolicyByPolicyNo_CheckFound)
	int retVal;
	PolicyDB* buffer = CreateDB();
	
	NewPolicy(buffer, 111, 1960);
	NewPolicy(buffer, 222, 1985);
	NewPolicy(buffer, 333, 2010);
	NewPolicy(buffer, 444, 2015);
	NewPolicy(buffer, 555, 2012);
	retVal = ShowPolicyByPolicyNo(buffer, 4);
	Destroy(buffer);
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------- ListPoliciesByYear ----------------------------*/
/*----------------------------------------------------------------------------*/
TEST(ListPoliciesByYear_CheckNULL_Pointer)
	int retVal;
	
	retVal = ListPoliciesByYear(NULL, 2000);
    ASSERT_THAT( -1 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(ListPoliciesByYear_CheckFound)
	int retVal;
	PolicyDB* buffer = CreateDB();
	
	NewPolicy(buffer, 111, 1960);
	NewPolicy(buffer, 222, 2010);
	NewPolicy(buffer, 333, 2010);
	NewPolicy(buffer, 444, 2015);
	NewPolicy(buffer, 555, 2012);
	retVal = ListPoliciesByYear(buffer, 2010);
	Destroy(buffer);
    ASSERT_THAT( 0 == retVal );
END_TEST
/*----------------------------------------------------------------------------*/





/********************************* Test Suite *********************************/
TEST_SET(Test SysV Module)
	PRINT(NewPolicy_CheckNULL_Pointer)
	PRINT(NewPolicy_CheckNULL_License)
	PRINT(NewPolicy_CheckNULL_YearTooSmall)
	PRINT(NewPolicy_CheckNotNULL)
	
	PRINT(ShowPolicyByLicenseNo_CheckNULL_Pointer)
	PRINT(ShowPolicyByLicenseNo_CheckNULL_License)
	PRINT(ShowPolicyByLicenseNo_CheckNotFound)
	PRINT(ShowPolicyByLicenseNo_CheckFirstFound)
	PRINT(ShowPolicyByLicenseNo_CheckFound)
	
	PRINT(ShowPolicyByPolicyNo_CheckNULL_Pointer)
	PRINT(ShowPolicyByPolicyNo_CheckNULL_License)
	PRINT(ShowPolicyByPolicyNo_CheckNotFound)
	PRINT(ShowPolicyByPolicyNo_CheckFirstFound)
	PRINT(ShowPolicyByPolicyNo_CheckFound)
	
	PRINT(ListPoliciesByYear_CheckNULL_Pointer)
	PRINT(ListPoliciesByYear_CheckFound)
	
END_SET


