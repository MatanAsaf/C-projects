/** 
 *  @file tests.c
 *  @brief tests file for myString API
 * 
 *  @details This API present implication of different function from string.h.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-14    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "myString.h"		/* header file */
#include "matan_test.h"		/* def of unit test */
#include <stdio.h>  		/* for printf */
#include <string.h>  		/* for strcmp */




/*************************** Tests for API functions **************************/
/*---------------------------------- myAToI ----------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckNull_String)
	int retVal;
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myAToI(NULL, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckNull_Item)
	ASSERT_THAT( UNINITIALIZED_RETURN == myAToI("124", NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckNotFound)
	char string[] = "ABHGYTRDJK";
	int retVal;
	
	ASSERT_THAT( NOT_FOUND == myAToI(string, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckFoundOnlyPositiveSign)
	char string[] = "ABHGY+fTRDJK";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && 0 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckFoundOnlyNegetiveSign)
	char string[] = "ABHGYofTRD-JK";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && 0 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckCaseNegetiveWithoutSeperation)
	char string[] = "ABHGYofTRD-54K";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && -54 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckCaseNegetiveWithSeperation)
	char string[] = "ABHGYofTRD-54K98";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && -54 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckCasePositiveWithoutSeperation)
	char string[] = "ABHGYofTRD+36K";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && 36 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckCasePositiveWithSeperation)
	char string[] = "ABHGYofTRD+36K948";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && 36 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckCaseOnlyDigitsWithOutSeperation)
	char string[] = "ABHGYofTRD111K$#@";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && 111 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckCaseOnlyDigitsWithSeperation)
	char string[] = "ABHGYofTRD111K948";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && 111 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myAToI_CheckCaseOnlyDigitsWithSpaces)
	char string[] = "ABH 0 0 4 5   0 y jhg$";
	int retVal;
	
	ASSERT_THAT( SUCCESS == myAToI(string, &retVal) && 450 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*---------------------------------- myIToA ----------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myIToA_CheckNull_Item)
	ASSERT_THAT( UNINITIALIZED_RETURN == myIToA(0, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myIToA_CheckCase_0)
	char string[12];
	int status[2];
	
	status[0] =  myIToA(0, string);
	status[1] = strcmp(string, "0");
	
	ASSERT_THAT( SUCCESS ==  status[0]  && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myIToA_CheckCase_Negetive)
	char string[12];
	int status[2];
	
	status[0] =  myIToA(-540, string);
	status[1] = strcmp(string, "-540");
	
	ASSERT_THAT( SUCCESS ==  status[0]  && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myIToA_CheckCase_Positive)
	char string[12];
	int status[2];
	
	status[0] =  myIToA(9000000, string);
	status[1] = strcmp(string, "9000000");
	
	ASSERT_THAT( SUCCESS ==  status[0]  && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- myMemChar --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myMemChar_CheckNull_String)
	size_t retVal;
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myMemChar(NULL, '#', 50, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemChar_CheckNull_Item)
	char string[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( UNINITIALIZED_RETURN == myMemChar(string, '#', 50, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemChar_CheckCase_FoundFirst)
	char string[] = "ABHGYofTRD111K$#@";
	size_t retVal;
	
	ASSERT_THAT( SUCCESS == myMemChar(string, 'A', 50, &retVal) && 0 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemChar_CheckCase_FoundLast)
	char string[] = "ABHGYofTRD111K$#@";
	size_t retVal;
	
	ASSERT_THAT( SUCCESS == myMemChar(string, '@', 50, &retVal) && 16 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemChar_CheckCase_NotFound)
	char string[] = "ABHGYofTRD111K$#@";
	size_t retVal;
	
	ASSERT_THAT( NOT_FOUND == myMemChar(string, 'Z', 50, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemChar_CheckCase_NotFound_OutOfRange)
	char string[] = "ABHGYofTRD111K$#@";
	size_t retVal;
	
	ASSERT_THAT( NOT_FOUND == myMemChar(string, 'G', 2, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- myMemCmp ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myMemCmp_CheckNull_String1)
	char string2[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myMemCmp(NULL, string2, 15) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCmp_CheckNull_String2)
	char string1[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myMemCmp(string1, NULL, 15) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCmp_CheckCase_Equal)
	char string1[] = "ABHGYofTRD111K$#@";
	char string2[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( SUCCESS == myMemCmp(string1, string2, 25) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCmp_CheckCase_NotEqual)
	char string1[] = "ABHGYofTRD111K$#@";
	char string2[] = "ABHGYofTRD112K$#@";
	
	ASSERT_THAT( NOT_EQUAL == myMemCmp(string1, string2, 25) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCmp_CheckCase_NotEqual_ButOutOfRange)
	char string1[] = "ABHGYofTRD111K$#@";
	char string2[] = "ABHGYofTRD121K$#@";
	
	ASSERT_THAT( SUCCESS == myMemCmp(string1, string2, 9) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCmp_CheckCase_NotEqual_FirstLonger)
	char string1[] = "ABHGYofTRD111K$#@";
	char string2[] = "ABHGYofTRD111K$#";
	
	ASSERT_THAT( FIRST_PARAM_LONGER == myMemCmp(string1, string2, 25) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCmp_CheckCase_NotEqual_SecondLonger)
	char string1[] = "ABHGYofTRD111K$#";
	char string2[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( SECOND_PARAM_LONGER == myMemCmp(string1, string2, 25) );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- myMemCpy ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myMemCpy_CheckNull_Des)
	char string2[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myMemCpy(NULL, string2, 15) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCpy_CheckNull_Src)
	char string1[15];
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myMemCpy(string1, NULL, 15) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCpy_CheckCase_CutString)
	char string1[50];
	char string2[] = "ABHGYofTRD111K$#@";
	int status[2];
	
	status[0] =  myMemCpy(string1, string2, 5);
	status[1] = strcmp(string1, "ABHGYo");
	
	ASSERT_THAT( SUCCESS == status[0] && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemCpy_CheckCase_AllString)
	char string1[50];
	char string2[] = "ABHGYofTRD111K$#@";
	int status[2];
	
	status[0] =  myMemCpy(string1, string2, strlen(string2) );
	status[1] = strcmp(string1, string2);
	
	ASSERT_THAT( SUCCESS == status[0] && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- myMemSet ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myMemSet_CheckNull_String)
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myMemSet(NULL, '#', 10) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myMemSet_Check)
	char string[50];
	int status[2];
	
	status[0] =  myMemSet(string, '#', 10);
	status[1] = strcmp(string, "##########");
	
	ASSERT_THAT( SUCCESS == status[0] && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- myStrNCat --------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myStrNCat_CheckNull_Des)
	char string2[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myStrNCat(NULL, string2, 15) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myStrNCat_CheckNull_Src)
	char string1[15];
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myStrNCat(string1, NULL, 15) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myStrNCat_CheckCase_EmptyDes)
	char string1[50] = "\0";
	char string2[] = "BBB";
	int status[2];
	
	status[0] =  myStrNCat(string1, string2, 40);
	status[1] = strcmp(string1, string2);
	
	ASSERT_THAT( SUCCESS == status[0] && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myStrNCat_CheckCase_2Append)
	char string1[50] = "\0";
	char string2[] = "AAA";
	char string3[] = "BBB";
	int status[4];
	
	status[0] =  myStrNCat(string1, string2, 40);
	status[1] = strcmp(string1, string2);
	status[2] =  myStrNCat(string1, string3, 40);
	status[3] = strcmp(string1, "AAABBB");
	
	ASSERT_THAT( SUCCESS == status[0] && 0 == status[1] && SUCCESS == status[2] && 0 == status[3]);
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myStrNCat_CheckCase_CutString)
	char string1[50] = "\0";
	char string2[] = "BBB";
	int status[2];
	
	status[0] =  myStrNCat(string1, string2, 1);
	status[1] = strcmp(string1, "B");
	
	ASSERT_THAT( SUCCESS == status[0] && 0 == status[1] );
END_TEST
/*----------------------------------------------------------------------------*/


/*--------------------------------- myStrLen ---------------------------------*/
/*----------------------------------------------------------------------------*/
TEST(myStrLen_CheckNull_String)
	size_t retVal;
	
	ASSERT_THAT( UNINITIALIZED_ERROR == myStrLen(NULL, &retVal) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myStrLen_CheckNull_Item)
	char string[] = "ABHGYofTRD111K$#@";
	
	ASSERT_THAT( UNINITIALIZED_RETURN == myStrLen(string, NULL) );
END_TEST
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
TEST(myStrLen_Check)
	char string[] = "ABHGYofTRD111K$#@";
	size_t retVal;
	
	ASSERT_THAT( SUCCESS == myStrLen(string, &retVal) && 17 == retVal);
END_TEST
/*----------------------------------------------------------------------------*/


/********************************* Tests Suite ********************************/
/*----------------------------------------------------------------------------*/
TEST_SET(myString API)
	PRINT(myAToI_CheckNull_String)
	PRINT(myAToI_CheckNull_Item)
	PRINT(myAToI_CheckNotFound)
	PRINT(myAToI_CheckFoundOnlyPositiveSign)
	PRINT(myAToI_CheckFoundOnlyNegetiveSign)
	PRINT(myAToI_CheckCaseNegetiveWithoutSeperation)
	PRINT(myAToI_CheckCaseNegetiveWithSeperation)
	PRINT(myAToI_CheckCasePositiveWithoutSeperation)
	PRINT(myAToI_CheckCasePositiveWithSeperation)
	PRINT(myAToI_CheckCaseOnlyDigitsWithOutSeperation)
	PRINT(myAToI_CheckCaseOnlyDigitsWithSeperation)
	PRINT(myAToI_CheckCaseOnlyDigitsWithSpaces)
	
	PRINT(myIToA_CheckNull_Item)
	PRINT(myIToA_CheckCase_0)
	PRINT(myIToA_CheckCase_Negetive)
	PRINT(myIToA_CheckCase_Positive)
	
	PRINT(myMemChar_CheckNull_String)
	PRINT(myMemChar_CheckNull_Item)
	PRINT(myMemChar_CheckCase_FoundFirst)
	PRINT(myMemChar_CheckCase_FoundLast)
	PRINT(myMemChar_CheckCase_NotFound)
	PRINT(myMemChar_CheckCase_NotFound_OutOfRange)
	
	PRINT(myMemCmp_CheckNull_String1)
	PRINT(myMemCmp_CheckNull_String2)
	PRINT(myMemCmp_CheckCase_Equal)
	PRINT(myMemCmp_CheckCase_NotEqual)
	PRINT(myMemCmp_CheckCase_NotEqual_ButOutOfRange)
	PRINT(myMemCmp_CheckCase_NotEqual_FirstLonger)
	PRINT(myMemCmp_CheckCase_NotEqual_SecondLonger)

	PRINT(myMemCpy_CheckNull_Des)
	PRINT(myMemCpy_CheckNull_Src)
	PRINT(myMemCpy_CheckCase_CutString)
	PRINT(myMemCpy_CheckCase_AllString)

	PRINT(myMemSet_CheckNull_String)
	PRINT(myMemSet_Check)
	
	PRINT(myStrNCat_CheckNull_Des)
	PRINT(myStrNCat_CheckNull_Src)
	PRINT(myStrNCat_CheckCase_EmptyDes)
	PRINT(myStrNCat_CheckCase_2Append)
	PRINT(myStrNCat_CheckCase_CutString)
	
	PRINT(myStrLen_CheckNull_String)
	PRINT(myStrLen_CheckNull_Item)
	PRINT(myStrLen_Check)
END_SET
/*----------------------------------------------------------------------------*/

