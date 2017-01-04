/** 
 *  @file tests.c
 *  @brief tests file for divideOddEven
 * 
 *  @details This function divide numbers to odd group and even group.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *  @date 2016-12-13    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 
#include "divideOddEven.h"	/* header file */
#include <stdio.h>  		/* for printf */
#include <stddef.h>			/* for size_t */






/*************************** Tests for API functions **************************/
/*----------------------------------------------------------------------------*/
int main() 
{
	int arr[] = {4, 2, 9, 7, 6, 5, 2, 3};
	size_t arrSize = sizeof(arr) / sizeof(int);
	size_t i;
	
	printf("Befor\n");
	for(i = 0; i < arrSize; ++i)
	{
		printf("arr[%u] : %d\n",i, arr[i]);
	}
	
	Divide(arr, arrSize);
	
	printf("\nAfter\n");
	for(i = 0; i < arrSize; ++i)
	{
		printf("arr[%u] : %d\n",i, arr[i]);
	}
	
	return 0;
}
/*----------------------------------------------------------------------------*/

