/** 
 *  @file 		listItr.c
 *  @brief 		src file for Generic Double Linked List Iterator data type
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
 


#include "listItr.h" 			/* header file */ 
#include "privateListStruct.h" 	/* for struct Node, struct List */
#include <stdlib.h> 			/* for NULL, malloc, free */

#define AS_NODE(parameter)		( (Node*)(parameter) )
#define CHECK_NULL(param)		do{ if(NULL == (param) ) { return NULL;}  } while(0)
                                                

/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief  Connect to a new ListItr it's previous and next nods
 *
 * @params  _current	=   The current ListItr the function need to point at
 * @params  _previous   =   The ListItr that need to be before the current ListItr
 * @params  _next       =   The ListItr that need to be after the current ListItr
 *
 * @returns void
 */ 
static void PushConnect(Node* _current, Node* _previous, Node* _next);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Create new ListItr and insert it's value
 *
 * @params  list       =   A pointer to previously created List returned via ListCreate
 * @params  item       =   An item to add to the list
 *
 * @returns void
 */
static ListItr* CreateNewListItr(void* _item);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Find and connect 2 ListItr that came before and after the currentListItr to each outer
 *
 * @params  current		=   The current ListItr that the 2 ListItr point at
 *
 * @returns void
 */
static void PopConnect(Node* _current);
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
ListItr ListItrBegin(const List* _list)
{
    CHECK_NULL(_list);
    
    return (ListItr)(_list->m_head.m_next);
}
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
ListItr ListItrEnd(const List* _list)
{
    CHECK_NULL(_list);
    
    return (ListItr)(&(_list->m_tail));
}
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
int ListItrEquals(const ListItr _a, const ListItr _b)
{
    return (_a == _b);
}
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
ListItr ListItrNext(ListItr _itr)
{
    CHECK_NULL(_itr);
    
    return (ListItr)( AS_NODE(_itr)->m_next );
}
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
ListItr ListItrPrev(ListItr _itr)
{
    CHECK_NULL(_itr);
    
    if( ( AS_NODE(_itr)->m_prev ) ==  ( AS_NODE(_itr)->m_prev->m_prev )  )
    {
        return _itr;
    }
    
    return (ListItr)( AS_NODE(_itr)->m_prev );
}
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
void* ListItrGet(ListItr _itr)
{
    CHECK_NULL(_itr);
    
    if( _itr  ==  ( AS_NODE(_itr)->m_next )  )
    {
        return NULL;
    }
    
    return AS_NODE(_itr)->m_data;
}
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
void* ListItrSet(ListItr _itr, void* _element)
{
    void* tempData;
    
    CHECK_NULL(_itr);
    CHECK_NULL(_element);
    
    if( _itr  ==  ( AS_NODE(_itr)->m_next )  )
    {
        return NULL;
    }
    
    tempData = AS_NODE(_itr)->m_data;
    AS_NODE(_itr)->m_data = _element;
    
    return tempData;
}
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
ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
    ListItr* newListItr;
    
    CHECK_NULL(_itr);
    CHECK_NULL(_element);
    
    newListItr = CreateNewListItr(_element);
    CHECK_NULL(_itr);
    
    PushConnect((Node*)newListItr, AS_NODE(_itr)->m_prev, (Node*)_itr);
    
    return newListItr;
}
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
void* ListItrRemove(ListItr _itr)
{
    void* tempData;
    
    CHECK_NULL(_itr);
    
    if( _itr  ==  ( AS_NODE(_itr)->m_next )  )
    {
        return NULL;
    }
    
    tempData = AS_NODE(_itr)->m_data;
    PopConnect(_itr);
    free(_itr);
    
    return tempData;
    
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief  Connect to a new ListItr it's previous and next nods
 *
 * @params  _current	=   The current ListItr the function need to point at
 * @params  _previous   =   The ListItr that need to be before the current ListItr
 * @params  _next       =   The ListItr that need to be after the current ListItr
 *
 * @returns void
 */ 
static void PushConnect(Node* _current, Node* _previous, Node* _next)
{
    _current->m_prev = _previous;
    _current->m_next = _next;
    
    _previous->m_next = _current;
    _next->m_prev = _current;    
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Create new ListItr and insert it's value
 *
 * @params  list       =   A pointer to previously created List returned via ListCreate
 * @params  item       =   An item to add to the list
 *
 * @returns void
 */
static ListItr* CreateNewListItr(void* _item)
{
    Node* new;
    
    new = (Node*)malloc(  sizeof(Node) );
    CHECK_NULL(new);
    
    new->m_data = _item;
    return (ListItr*)new;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Find and connect 2 ListItr that came before and after the currentListItr to each outer
 *
 * @params  current		=   The current ListItr that the 2 ListItr point at
 *
 * @returns void
 */
static void PopConnect(Node* _current)
{
    Node* previous =_current->m_prev;
    Node* next =_current->m_next;
    
    previous->m_next = next;
    next->m_prev = previous;
}
/*----------------------------------------------------------------------------*/
