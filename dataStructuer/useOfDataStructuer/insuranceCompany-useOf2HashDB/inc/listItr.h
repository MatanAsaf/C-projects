/** 
 *  @file 		listItr.h
 *  @brief 		header file for Generic Double Linked List Iterator data type
 * 
 *  @details 	Implemented as list of action that can be done on double linked list
 *  			without need to know how the double linked list data structure work.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2016-12-28    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */
 

#ifndef __LIST_ITR_H__
#define __LIST_ITR_H__
 
 
#include "list.h" /* for typedef struct List */ 


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef void* ListItr;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the list's beginning
 *
 * @params  list       	=   list to return begin iterator, pointing at first element
 *                          or at the end if list is empty
 *
 * @return  ListItr pointer:
 *
 * @retval 	On success  =   A iterator pointing at the list's beginning. 
 * @retval  NULL        =   If pointer is uninitialized
 */
ListItr ListItrBegin(const List* _list);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the list end
 *
 * @params  list       	=   list to return end iterator
 *
 * @return  ListItr pointer:
 *
 * @retval 	On success  =   A iterator pointing at the list's end. 
 * @retval  NULL        =   If pointer is uninitialized
 */
ListItr ListItrEnd(const List* _list);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Function that compare between two iterators
 *
 * @params  a          	=   Pointer to iterator a
 * @params  b          	=   Pointer to iterator b
 *
 * @return  Retruns none zero if _a and _b iterators refer to same ListItr:
 *
 * @retval  1           =   If iterator _a and iterator _b equals
 * @retval  0           =   If iterator _a and iterator _b NOT equals OR 
 *							iterator _a is uninitialized OR 
 *							iterator _b is uninitialized
 *
 * @warning if both ListItr are uninitialized the result will be 1
 */
int ListItrEquals(const ListItr _a, const ListItr _b);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 *
 * @params  itr                            	=   pointer to current iterator 
 *
 * @return  ListItr pointer:
 *
 * @retval  All iterator exclude the end    =   Iterator pointing at the next list's iterator
 * @retval  At end of the list              =   Iterator pointing at itself 
 * @retval  NULL              				=   If pointer is uninitialized     
 */
ListItr ListItrNext(ListItr _itr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the previous element
 * @warning if _itr is begin iterator it will be returned
 *
 * @params  itr                            	=   pointer to iterator 
 *
 * @return  ListItr pointer:
 *
 * @retval  All iterator exclude the begin  =   Iterator pointing at the prev list's iterator
 * @retval  In begin of the list            =   Iterator pointing at itself 
 * @retval  NULL              				=   If pointer is uninitialized 
 */
ListItr ListItrPrev(ListItr _itr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get data from the list ListItr the current iterator is pointing to
 *
 * @params  itr         	=   A list iterator
 *
 * @return  Element data pointer:
 *
 * @retval  Data         	=   If the iterator is pointing at data
 * @retval  NULL         	=   If iterator pointing to the end OR pointer is uninitialized
 */
void* ListItrGet(ListItr _itr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Set data at the ListItr where the current iterator is pointing at
 *
 * @params  itr         	=   A list iterator
 * @params  element     	=   A iterator data
 *
 * @return  The orignal data from the current ListItr before the change:
 * 
 * @retval  Data         	=   If the iterator is pointing at data
 * @retval  NULL         	=   If iterator pointing to the end OR pointer is uninitialized
 */
void* ListItrSet(ListItr _itr, void* _element);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Inserts a new ListItr before current iterator ListItr is pointing at
 *
 * @params  itr         	=   A list iterator
 * @params  element     	=   A iterator data
 *
 * @return  An iterator pointer at the element inserted:
 *
 * @retval  Iterator ptr 	=   If the iterator is valid
 * @retval  NULL         	=   If there was an allocation error OR 
 *								one of the pointers is uninitialized
 */
ListItr ListItrInsertBefore(ListItr _itr, void* _element);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Removes the ListItr the current iterator is pointing at
 *
 * @params  itr         	=   A list iterator
 *
 * @return  Element data pointer:
 * 
 * @retval  Data         	=   The removed data
 * @retval  NULL         	=   If iterator pointing to the end OR pointer is uninitialized
 */
void* ListItrRemove(ListItr _itr);
/*----------------------------------------------------------------------------*/


#endif /* __LIST_ITR_H__ */
