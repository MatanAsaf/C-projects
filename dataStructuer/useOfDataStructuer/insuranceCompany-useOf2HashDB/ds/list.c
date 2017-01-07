/** 
 *  @file 		list.c
 *  @brief 		src file for Generic Double Linked List data type
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

#include "list.h" 
#include "privateListStruct.h" /* for struct Node, struct List */
#include <stdlib.h> 			/* for size_t, malloc */

#define CHECK_NULL(param)			do{ if(NULL == (param) ) { return NULL;}  } while(0)
#define CHECK_LIST_NULL(param)		do{ if(NULL == (param) ) { return LIST_UNINITIALIZED_ERROR;}  } while(0)
#define CHECK_ELEMENT_NULL(param)	do{ if(NULL == (param) ) { return LIST_NULL_ELEMENT_ERROR;}  } while(0)
#define CHECK_ALLOCATION_ERROR(err)	do{ if(NULL == (err) ) { return LIST_ALLOCATION_ERROR;}  } while(0)



/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief  Connect to a new node it's previous and next nods
 *
 * @params  _current        =   The current Node the function need to point at
 * @params  _previous       =   The Node that need to be before the current Node
 * @params  _next			=   The Node that need to be after the current Node
 *
 * @returns void
 */
static void ConnectPushNode(Node* _current, Node* _previous, Node* _next);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Find and connect 2 node that came before and after the current node to each outher
 *
 * @params  _current		=   The current Node that the 2 Nods point at
 *
 * @returns void
 */
static void PopConnectNode(Node* _current);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Create new node and insert it's value
 *
 * @params  _item           =   An item to add to the list
 *
 * @returns void
 */
static Node* CreateNewNode(void* _item);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Create new node and insert it's value
 *
 * @params  _curNode       =   A pointer to the node needed to remove
 * @params  _pItem         =   To store a pointer to the removed item in
 *
 * @returns void
 */
static void Pop(Node* _curNode, void** _pItem); 
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
List* ListCreate(void)
{
    List* ptr;

    ptr = (List*)malloc( sizeof(List) );  
    CHECK_NULL(ptr); 
    
    ptr->m_head.m_next = &(ptr->m_tail);
    ptr->m_head.m_prev = &(ptr->m_head);
    ptr->m_tail.m_prev = &(ptr->m_head);
    ptr->m_tail.m_next = &(ptr->m_tail);
    ptr->m_tail.m_data = NULL;
    
    return ptr; 
}
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
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
    Node* nodeAddress;
           
    if(NULL == _pList || NULL == *_pList)  
    {
        return;
    }
    
    nodeAddress = (*_pList)->m_head.m_next;
            
    while( &(*_pList)->m_tail != nodeAddress->m_next)
    {
        if( NULL != (*_elementDestroy) )
        {
            (*_elementDestroy)(nodeAddress->m_data);
        }
        
        nodeAddress = nodeAddress->m_next;
        free(nodeAddress->m_prev);
    }
    
    free(*_pList);
    *_pList = NULL;
    
    return;
}
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
ListResult ListPushHead(List* _list, void* _item)
{
    Node* newNode;
    
    CHECK_LIST_NULL( _list);
    CHECK_ELEMENT_NULL(_item);
    
    newNode = CreateNewNode(_item);
    CHECK_ALLOCATION_ERROR(newNode);
    
    ConnectPushNode(newNode, &_list->m_head, _list->m_head.m_next);
    
    return LIST_SUCCESS;
}
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
ListResult ListPushTail(List* _list, void* _item)
{
    Node* newNode;
    
    CHECK_LIST_NULL( _list);
    CHECK_ELEMENT_NULL(_item);
    
    newNode = CreateNewNode(_item);
    CHECK_ALLOCATION_ERROR(newNode);
    
    ConnectPushNode(newNode, _list->m_tail.m_prev, &_list->m_tail);
    
    return LIST_SUCCESS;
}
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
ListResult ListPopHead(List* _list, void** _pItem)
{
    Node* tempNode;
                              
    CHECK_LIST_NULL( _list);
    CHECK_ELEMENT_NULL(_pItem);
    CHECK_ELEMENT_NULL(*_pItem);
    
    if( &(_list->m_tail) == _list->m_head.m_next)
    {
    	return EMPTY_LIST_ERROR;
    }
    
    tempNode = _list->m_head.m_next;
    
    Pop(tempNode, _pItem);
    PopConnectNode(_list->m_head.m_next);

    return LIST_SUCCESS;
}
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
ListResult ListPopTail(List* _list, void** _pItem)
{
    Node* tempNode;
    
    CHECK_LIST_NULL( _list);
    CHECK_ELEMENT_NULL(_pItem);
    CHECK_ELEMENT_NULL(*_pItem);
    
    if( &(_list->m_tail) == _list->m_head.m_next)
    {
    	return EMPTY_LIST_ERROR;
    }
    
    tempNode = _list->m_tail.m_prev;
    
    Pop(tempNode, _pItem);
    PopConnectNode(_list->m_tail.m_prev);
    
    return LIST_SUCCESS;
}
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
size_t ListSize(const List* _list)
{
    Node* nodeAddress;
    size_t counter = 0;
    
    if( NULL == _list )
    {
    	return 0;
    }
    
    nodeAddress = _list->m_head.m_next;
    
    while(&(_list->m_tail) != nodeAddress)
    {
        ++counter;
        nodeAddress = nodeAddress->m_next;
    }
    
    return counter;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief  Connect to a new node it's previous and next nods
 *
 * @params  _current        =   The current Node the function need to point at
 * @params  _previous       =   The Node that need to be before the current Node
 * @params  _next			=   The Node that need to be after the current Node
 *
 * @returns void
 */
static void ConnectPushNode(Node* _current, Node* _previous, Node* _next)
{
    _current->m_prev = _previous;
    _current->m_next = _next;
    
    _previous->m_next = _current;
    _next->m_prev = _current;  
    
    return;  
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Find and connect 2 node that came before and after the current node to each outher
 *
 * @params  _current		=   The current Node that the 2 Nods point at
 *
 * @returns void
 */
static void PopConnectNode(Node* _current)
{
    Node* previous =_current->m_prev;
    Node* next =_current->m_next;
    
    previous->m_next = next;
    next->m_prev = previous;
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Create new node and insert it's value
 *
 * @params  _item           =   An item to add to the list
 *
 * @returns void
 */
static Node* CreateNewNode(void* _item)
{
    Node* newNode;
    
    newNode = (Node*)malloc( sizeof(Node) );
    CHECK_NULL(newNode);
    
    newNode->m_data = _item;
    
    return newNode;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief  Create new node and insert it's value
 *
 * @params  _curNode       =   A pointer to the node needed to remove
 * @params  _pItem         =   To store a pointer to the removed item in
 *
 * @returns void
 */
static void Pop(Node* _curNode, void** _pItem)
{
    *_pItem = _curNode->m_data;
    free(_curNode);
    
    return;
}
/*----------------------------------------------------------------------------*/

