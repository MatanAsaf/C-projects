/** 
 *  @file matan_test.h
 *  @brief src file for matan_test macro structuer
 * 
 *  @details This macro structuer define a set of defenition to build a unit test.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */


#ifndef MATAN_TEST_H_
#define MATAN_TEST_H_

#include <stdio.h>	/* for printf */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
#define PASS                	(0)
#define FAILED              	(-1)
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
#define TEST(name)          	int name(void){
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
#define END_TEST            	return PASS; \
                            	}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
#define ASSERT_THAT(statment)   do{ if(!(statment)) return FAILED;} while(0)
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
#define TEST_SET(moduleName)    int main()\
								{\
								int result;\
								unsigned int amountOfTests = 0;\
								unsigned int testsSucceed = 0;\
								unsigned int testsFailed = 0;\
								printf(YEL "\nSet of Tests for Moudle %s, %s %s:\n\n",#moduleName, __DATE__, __TIME__);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
#define PRINT(testName)			result = testName();\
								++amountOfTests;\
								result == PASS ? ++testsSucceed : ++testsFailed;\
								printf("Test Number %u: %s. Result: ",amountOfTests, #testName);\
								printf("%s\n", result == PASS ? GRN "PASS"  YEL: RED "FAILED");
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/							
#define END_SET                 printf(BLU "\nTotal Tests: %u\n", amountOfTests);\
								printf(GRN "Tests Succeed: %u\n", testsSucceed);\
								printf(RED "Tests Failed: %u\n", testsFailed);\
								printf(MAG "\nUnit Tests design by Matan Asaf (Matan.Asaf@gmail.com)\n\n");\
								return 0;\
								}
/*----------------------------------------------------------------------------*/



#endif /* MATAN_TEST_H_ */

