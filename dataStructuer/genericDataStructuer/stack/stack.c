/** 
 *  @file 		stack.c
 *  @brief 		src file for Generic Stack data type
 * 
 *  @details 	The API stores pointer to user provided elements of generic type.
 * 				The stack is heap allocated and can grow and shrink on demand.
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

 
#include "stack.h"			/* header file */
#include "vector.h"			/* vector header */
#include <stdio.h>			/* for perror */
#include <stdlib.h>  		/* size_t &malloc */

#define DEBUG (1)



/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
struct Stack
{
    Vector* m_vec; /* Pointer to the Vector data structuer */
};
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Dynamically create a new stack object of given capacity
 * 
 * @param 	initialCapacity			= Initial capacity, number of elements that can be stored initially
 * @param 	blockSize				= The stack will grow or shrink on demand by this size 
 *
 * @return 	The stack pointer
 * @retval	stack*					= On success 
 * @retval	NULL 					= On fail 
 *
 * @warning If _blockSize is 0 the stack will be of fixed size. 
 * @warning If both _initialCapacity and _blockSize are zero function will return NULL.
 */
Stack* StackCreate(size_t _initialCapacity, size_t _blockSize)
{
	Stack* newStack;
	
	if( 0 == _initialCapacity && 0 == _blockSize )
	{
        return NULL;
    }
    
    newStack = (Stack*)malloc( sizeof(Stack) );
    if( NULL == newStack )
    {
    	return NULL;
    }
    
    newStack->m_vec = VectorCreate(_initialCapacity, _blockSize);
    if( NULL == newStack->m_vec )
    {
    	free(newStack);
    	return NULL;
    }
    
    return newStack;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Dynamically deallocate a previously allocated stack 
 * 
 * @param	stack					= Stack to be deallocated.
 * @params	elementDestroy			= A function pointer to be used to destroy all 
 *								  elements in the stack or a null if no such destroy is required
 *
 * @return void
 */
void StackDestroy(Stack** _stack, void (*_elementDestroy)(void* _item) )
{
	if( NULL == _stack || NULL == *_stack)  
    {
        return;
    }
    
	VectorDestroy( &((*_stack)->m_vec), (*_elementDestroy) );
	
	free(*_stack);
    *_stack = NULL;
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Add an Item element to the top of the stack.
 * 
 * @param	stack						= Stack to append integer to.
 * @param	item						= Item element to add.
 *
 * @return	Status stackResult that indicate in which state the function ended:
 *
 * @retval 	STACK_SUCCESS				= On success 
 * @retval 	STACK_UNINITIALIZED_ERROR 	= When pointer is uninitialized- *_stack == NULL 
 * @retval 	DATA_UNINITIALIZED_ERROR 	= When item is uninitialized- 	*_item == NULL
 * @retval 	STACK_ALLOCATION_ERROR 		= On allocation error- when realloc function failed 
 * @retval 	STACK_OVERFLOW_ERROR 		= When needed to do realloc and _blockSize is 0 
 */
StackResult StackPush(Stack* _stack, void* _item)
{
	VectorResult status;
	
	if( NULL == _stack )
    {
    	return STACK_UNINITIALIZED_ERROR;
    }
    
	status = VectorAppend( _stack->m_vec, _item);
	
	switch(status)
	{
		case VECTOR_SUCCESS:
			return STACK_SUCCESS;
		case ITEM_UNINITIALIZED_ERROR:
			return DATA_UNINITIALIZED_ERROR;
		case VECTOR_ALLOCATION_ERROR:
			return STACK_ALLOCATION_ERROR;
		case VECTOR_OVERFLOW_ERROR:
			return STACK_OVERFLOW_ERROR;
		default:
			#if DEBUG
				perror("Bug in StackPush function! status return not illegal\n");
			#endif
			return VECTOR_SUCCESS;
	}	
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Remove an Element from the top of the stack. 
 * 
 * @param	stack						= Stack to delete integer from.
 * @param	pValue						= Pointer to variable that will receive deleted item value
 *
 * @return	Status stackResult that indicate in which state the function ended:
 *
 * @retval 	STACK_SUCCESS				= On success 
 * @retval 	STACK_UNINITIALIZED_ERROR 	= When pointer is uninitialized- *_stack == NULL 
 * @retval 	DATA_UNINITIALIZED_ERROR 	= When item is uninitialized- 	*_item == NULL
 * @retval 	STACK_ALLOCATION_ERROR 		= On allocation error- when realloc function failed 
 * @retval 	STACK_UNDERFLOW_ERROR 		= When numOfItems == 0 and trying to remove an element 
 *
 * @warning _item can't be null. this will be assertion violation
 */
StackResult StackPop(Stack* _stack, void** _pValue)
{
	VectorResult status;
	
	if( NULL == _stack )
    {
    	return STACK_UNINITIALIZED_ERROR;
    }
    
	status = VectorRemove( _stack->m_vec, _pValue);
	
	switch(status)
	{
		case VECTOR_SUCCESS:
			return STACK_SUCCESS;
		case ITEM_UNINITIALIZED_ERROR:
			return DATA_UNINITIALIZED_ERROR;
		case VECTOR_ALLOCATION_ERROR:
			return STACK_ALLOCATION_ERROR;
		case VECTOR_UNDERFLOW_ERROR:
			return STACK_UNDERFLOW_ERROR;
		default:
			#if DEBUG
				perror("Bug in StackPop function! status return not illegal\n");
			#endif
			return VECTOR_SUCCESS;
	}	
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Get the number of actual items currently in the stack.
 *
 * @param	stack			= Stack to use.
 *
 * @return  Number of items 
 *
 * @retval	number			= On success 
 * @retval	0 				= If stack is empty OR pointer is uninitialized- 
 *							*_stack == NULL			
 */
size_t StackSize(const Stack* _stack)
{
	if( NULL == _stack )
    {
    	return 0;
    }
    
    return VectorSize(_stack->m_vec);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/**  
 * @brief 	Get the current capacity of the stack.
 *
 * @param	stack			= Stack to use.
 *
 * @return  Capacity of stack
 *
 * @retval	number			= On success 
 * @retval	0 				= If stack current capacity is 0 OR pointer 
 *							is uninitialized- *_stack == NULL		
 */
size_t StackCapacity(const Stack* _stack)
{
	if( NULL == _stack )
    {
    	return 0;
    }
    
    return VectorCapacity(_stack->m_vec);
}
/*----------------------------------------------------------------------------*/
