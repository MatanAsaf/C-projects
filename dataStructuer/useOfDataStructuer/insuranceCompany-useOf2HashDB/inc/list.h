/** 
 *  @file 		list.h
 *  @brief 		header file for Generic Double Linked List data type
 * 
 *  @details 	The API stores pointer to user provided elements of generic type.
 * 				The List is heap allocated and can grow and shrink on demand.
 *				Implemented as double linked list using head and tail sentinels.
 *  			Nodes are allocated from heap an store pointer to user proveded element.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2016-12-27    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __LIST_H__
#define __LIST_H__


#include <stdlib.h> /* for size_t */



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct List List;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
typedef enum List_Result {
	LIST_SUCCESS,
	LIST_UNINITIALIZED_ERROR,	/* Uninitialized list */
	LIST_ALLOCATION_ERROR,		/* Node allocation failed due to heap error */
	LIST_NULL_ELEMENT_ERROR,    /* Uninitialized element */
	EMPTY_LIST_ERROR         	/* No element in the list to pop */
} ListResult;
/*----------------------------------------------------------------------------*/






/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Create a list
 * 
 * @return 	The List pointer 
 *
 * @retval 	On success    =   A pointer to the created list.
 * @retval  NULL          =   On failure due to allocation failure
 */
List* ListCreate(void);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Destroy list
 * @details Destroys the list completely optionally destroys elements using user provided function
 *
 * @params	pList       	=   A pointer to previously created List returned via 
 *							ListCreate on completion *_pList will be null
 * @params	elementDestroy  =   A function pointer to be used to destroy elements 
 *							inserted into the list or a null if no such destroy is required
 * @returns void
 */
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item));
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Add element to head of list
 * @details Time complexity: O(1).
 *
 * @params  list                       =   A previously created List ADT returned via ListCreate
 * @params  item                       =   An item to add to the list
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list ptr is uninitialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If item element is uninitialized
 * @retval  LIST_ALLOCATION_ERROR       =   On memory allocation failure
 */
ListResult ListPushHead(List* _list, void* _item);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Add element to tail of list
 * @details Time complexity: O(1).
 *
 * @params  list                       =   A previously created List ADT returned via ListCreate
 * @params  item                       =   An item to add to the list
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list ptr is uninitialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If item element is uninitialized
 * @retval  LIST_ALLOCATION_ERROR       =   On memory allocation failure
 */
ListResult ListPushTail(List* _list, void* _item);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Remove element from list's head
 * @details If successfull, stores a pointer to the removed item in _item
 *  		Time complexity O(1).
 *
 * @params  list                       	=   A previously created List ADT returned via ListCreate
 * @params  pItem                      	=   Pointer to variable that will receive deleted item value
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list ptr is uninitialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If item element is uninitialized
 * @retval  EMPTY_LIST_ERROR         	=   No element in the list to pop 	
 */
ListResult ListPopHead(List* _list, void** _pItem);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  	Remove element from list's tail
 * @details If successfull, stores a pointer to the removed item in _item
 *  		Time complexity O(1).
 *
 * @params  list                       	=   A previously created List ADT returned via ListCreate
 * @params  pItem                      	=   Pointer to variable that will receive deleted item value
 *
 * @return	Status ListResult that indicate in which state the function ended:
 *
 * @retval  LIST_SUCCESS                =   On success
 * @retval  LIST_UNINITIALIZED_ERROR    =   If the list ptr is uninitialized
 * @retval  LIST_NULL_ELEMENT_ERROR     =   If item element is uninitialized
 * @retval  EMPTY_LIST_ERROR         	=   No element in the list to pop 	
 */
ListResult ListPopTail(List* _list, void** _pItem);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Get number of elements in the list
 * @details Time complexity: O(n).
 *
 * @params  list              			= A previously created List ADT returned via ListCreate
 *
 * @returns Number of elements:
 *
 * @retval  number                  	= If there are more then 0
 * @retval  0                       	= If the list is uninitialized OR number 
 *										of elements is 0
 */
size_t ListSize(const List* _list);
/*----------------------------------------------------------------------------*/


#endif /* __LIST_H__ */
