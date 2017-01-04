#ifndef __HEAP_H__
#define __HEAP_H__

/** 
 *  @file heap.h
 *  @brief Create a Generic Heap dataBase type
 * 
 *  @details Implemented as heap using generic vector 
 *  Struct are allocated from heap and store pointers to user proveded element.
 * 
 *  @author Matan Asaf
 *  @date 08/11/2016 
 * 
 *  @bug No known bugs.
 */ 
 
 
#include "vector.h" 	/* vector header */
#include "privateHeapStruct.h" /* define heap struct */
#include <stdlib.h> 	/* for size_t */ 
                                               
                                                
                                                
                                                
                                                
/***************************************** Declaration of typedef *****************************************/
/*--------------------------------------------------------------------------------------------------------*/
typedef struct Heap Heap;
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
typedef int	(*VectorElementAction)(void* _element, size_t _index, void* _context);
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
typedef enum Heap_Result {
	HEAP_SUCCESS = 0,
	HEAP_UNINITIALIZED_ERROR,			/* Uninitialized list 					 	*/
	HEAP_ALLOCATION_ERROR,				/* Node allocation failed due to heap error */
	HEAP_NULL_ELEMENT_ERROR,            /* Uninitialized element 					*/
	HEAP_UNDERFLOW,                 	/* realloc failed 			                */
    HEAP_OVERFLOW,						/* realloc with _blockSize of 0				*/
    HEAP_WRONG_INDEX,					/* ... TODO				                    */
    HEAP_IS_EMPTY						/* when trying to get an element from empty heap */
} HeapResult;
/*--------------------------------------------------------------------------------------------------------*/



/********************************************* API functions **********************************************/
/*--------------------------------------------------------------------------------------------------------*/
/** @brief  Build new heap
 * Average time complexity O(n^2).
 * Worst: O(n^2)
 *
 * @params  	_vec                    	=   The pointer to generic vector
 * @param       _less           =       A comparison function 
 *				that returns true (none zero value) if x < y 
 *				and false (zero) otherwise.
 * @returns 	Pointer to the new Heap
 * @retval  	NULL 						=	If dynamic vector is NULL OR allocation failed
 */
Heap* HeapBuild(Vector* _vec, LessComparator _less);
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
/* Description : Destroy the heap but not the dynamic vector
 * 
 * Parameters  : ~ _heap - pointer to heap
 * 
 * Outputs 	   : ~ NONE
 *
 * Erros 	   : ~ NONE
 *
 * Limitations : ~ NONE 
 */
void HeapDestroy(Heap* _heap);
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
/* Description : Insert data to the heap
 * 
 * Parameters  : ~ _heap - pointer to heap
 *               ~ _data - data that need to insert
 * 
 * Outputs 	   : ~ NONE
 *
 * Erros 	   : ~ ERR_NOT_INITIALIZED
 *               ~ ERR_OK
 *               ~ ERR_OVERFLOW 
 *               ~ ERR_REALLOCATION_FIALED
 *
 * Limitations : ~ NONE 
 */
HeapResult HeapInsert(Heap* _heap, int _data);
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
 /** @brief  Return the max item
 * Average time complexity O(1).
 * Worst: O(1)
 *
 * @params  	_heap                    	=   The pointer to generic heap
 * @param       **_pValue					=	Pointer to get the element pointer
 * @returns 	The element in the Heap with the max value
 * @retval  	NULL 						=	If dynamic heap is NULL
 * @retval  	HEAP_IS_EMPTY 				=	If there is no elements in the heap
 * @retval  	max item 					=	When HEAP_SUCCESS
 */
HeapResult HeapMax(Heap* _heap, void** _pValue);
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
/* Description : Return the max item and delete it
 * 
 * Parameters  : ~ _heap - pointer to heap
 *               ~ _data - pointer to store the max item
 * 
 * Outputs 	   : ~ deleted max item in the heap
 *
 * Erros 	   : ~ ERR_NOT_INITIALIZED
 *               ~ ERR_OK
 *               ~ ERR_WRONG_INDEX if heap is empty
 *               ~ ERR_UNDERFLOW if heap is empty
 *               ~ ERR_REALLOCATION_FIALED
 *
 * Limitations : ~ NONE 
 */
HeapResult HeapExtractMax(Heap* _heap, int* _data);
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
 /** @brief  Return the numbers of elements in the item
 * Average time complexity O(1).
 * Worst: O(1)
 *
 * @params  	_heap                    	=   The pointer to generic heap
 * @returns 	The number of element in the Heap 
 * @retval  	0 							=	If dynamic heap is NULL Or if the heap is empty
 * @retval  	heapSize 					=	Otherwise
 */
size_t HeapItemsNum(Heap* _heap);
/*--------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------*/
/* Description : print all items in heap
 * 
 * Parameters  : ~ _heap - pointer to heap
 * 
 * Outputs 	   : ~ NONE
 *
 * Erros 	   : ~ NONE
 *
 * Limitations : ~ NONE 
 */
void HeapPrint(Heap* _heap);
/*--------------------------------------------------------------------------------------------------------*/
/* TODO heap search */


/*--------------------------------------------------------------------------------------------------------*/
/**  
 * @brief Iterate over all elements in the vector.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.  
 * @param[in] _heap - heap to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided context, will be sent to _action
 * @returns number of times the user functions was invoked
 * equevallent to:
 *      for(i = 1; i < Vector_Size(v); ++i){
 *             Vector_Get(v, i, &elem);
 *             if(_action(elem, i, _context) == 0)
 *					break;	
 *      }
 *		return i;
 */
size_t VectorForEach(const Heap* _heap, VectorElementAction _action, void* _context);
/*--------------------------------------------------------------------------------------------------------*/



#endif /* __HEAP_H__ */
