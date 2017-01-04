/** 
 *  @file 		listFunction.c
 *  @brief 		src file for Generic Double Linked List Iterator list of Function
 * 
 *  @details 	Implemented as list of functions that can be done on double linked list iterator
 *  			without need to know how the double linked list data structure work.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2016-12-29    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include "listItr.h"       	/* for typedef struct listItr */
#include "list.h"			/* list header file */
#include "listFunctions.h"  /* header file */ 
#include <stdlib.h>         /* for NULL, malloc, free */

#define CHECK_NULL(param)		do{ if(NULL == (param) ) { return NULL;}  } while(0)


/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       Finds the first element in a range satsifying a predicate
 * @details     find the element for which the predicate reuturns a non zero value
 *              in the half open range [begin..end)
 *
 * @param       _begin              =   start search from here
 * @param       _end                =   end search here - not included
 * @param       _predicate          =   Predicate function
 * @param       _context            =   context to be passed to the predicate
 *
 * @return      An iterator pointing to the first node with data found or to _end if not
 */
ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    CHECK_NULL(_begin);
    CHECK_NULL(_end);
    CHECK_NULL(_predicate);
    
	return ListItr_ForEach(_begin, _end, _predicate, _context);
} 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       count elements in a sub list satisfying predicate
 * @details     find the element for which the predicate returns a non zero value
 *              in the half open range [begin..end)
 *
 * @param       _begin              =   start search from here
 * @param       _end                =   end search here - not included
 * @param       _predicate          =   Predicate function
 * @param       _context            =   context to be passed to the predicate
 *
 * @return      count of all elements e where _predicate(e, _context) != 0
 */
size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    ListItr current = _begin;
    size_t counter = 0;
    int desicion;
    
	if(NULL == _begin || NULL == _end || NULL == _predicate)
	{
		return 0;
	}
    
    while(_end != current)
    {
    	++counter;
    	
        desicion = _predicate(current, _context);
        
        if(0 == desicion)
        {
            return counter;
        }
        
        current = ListItrNext(current);
    }
    
    return 0;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       execute an action for all elements in a half open range
 * @details     call -action for each element in the range [begin..end)
 *              iteration will stop if Action function returns 0 for an element
 *
 * @param       _begin              =   A list iterator to start operations from
 * @param       _end                =   A list iterator to end operations on
 * @param       _Action             =   user provided action function
 * @param       _context            =   Parameters for the function
 *
 * @return      ListItr to the element where the iteration stoped. this might be end iterator
 */
ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
    ListItr current = _begin;
    int desicion;
    
    CHECK_NULL(_begin);
    CHECK_NULL(_end);
    CHECK_NULL(_action);
    
    while(_end != current)
    {
        desicion = _action(current, _context);
        
        if(0 == desicion)
        {
            return current;
        }
        
        current = ListItrNext(current);
    }
    
    return _end;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Sorts a sublist in place using the bubble sort algorithm
 * @Complexity 	O(n^2)
 *
 * @params 		_begin				= Iterator to sublist start
 * @params 		_end				= Iterator to sublist end
 * @params 		_less				= Less compare function
 * 
 * @return void 
 */
void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less)
{
    ListItr currentItr =_begin;
    ListItr endOfLoop =_end;
    ListItr cmpItr;
    ListItr lastSwap;
    int decision;
    int swapFlag;
    void* data1;
    void* data2;
    
    if(NULL == _begin || NULL == _end || NULL == _less)
    {
        return;
    }
    
    while( 1 )
    {
    	cmpItr = ListItrNext(currentItr);
    	swapFlag = 0;
    	
        while( cmpItr != endOfLoop )
        {
            decision = _less(currentItr, cmpItr);
            if(0 != decision) /* 0 != SWAP */
            {
                lastSwap = cmpItr;
                swapFlag = 1; 
                data1 = ListItrGet(currentItr);
                data2 = ListItrSet(cmpItr, data1);
                ListItrSet(currentItr, data2);
            } 
            
            currentItr = ListItrNext(currentItr);
            cmpItr = ListItrNext(cmpItr);   
        }
        
        if( 0 == swapFlag )
        {
        	return;
        }
        
        endOfLoop = lastSwap;
        currentItr = _begin;
    }
    
    return;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Splice all element from [_begin.._end) into _dst
 * @details 	Remove all elements from the half open range [_begin.._end)
 * 				and insert them before _dest
 * @Complexity  O(n)
 *
 * @warning 	The function assumes that: 
 *  			_begin and _end are in the correct order and on the same list
 *  			_dset is not between them
 * 				Otherwise behavior is undefined
 * 				all three iterators can belong to same list
 *
 * @params 		_dest				= Iterator to new list
 * @params 		_begin				= Iterator to sublist start
 * @params 		_end				= Iterator to sublist end
 *
 * @return		The new start of the list OR NULL
 *
 * @retval		NULL				= On initalize error OR when _begin == _end
 * @retval		newBegin			= The new begin iterator of the list
 */
ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr current;
	ListItr removeItr;
	void* itrData;
	
    CHECK_NULL(_dest);
    CHECK_NULL(_begin);
    CHECK_NULL(_end);
    
    if(_begin == _end)
    {
    	return NULL;
    }
    
    current = ListItrPrev(_end);
    
    while(_begin != current)
    {
    	removeItr = current;
    	current = ListItrPrev(current);
    	itrData = ListItrRemove(removeItr);
    	_dest = ListItrInsertBefore(_dest, itrData);
    }
    
    itrData = ListItrRemove(current);
    _dest = ListItrInsertBefore(_dest, itrData);
		
	return _dest;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Merges two given sub lists into destination 
 * @details 	Merge elements from two sub lists defined by [_firstbegin.._firstEnd)
 * 				and [_secondBegin.._secondEnd) in optionaly sorted order using _less function.
 * 				merged elements will be inserted before _destBegin
 * 				if a _less function is provided then merge will be sorted
 * 
 * @warning 	This will removes all merged items from source ranges.
 * @Complexity  O(n^2)
 * 
 * @params 		_destBegin			= Iterator to new list
 * @params 		_firstBegin			= Iterator to sublist1 start
 * @params 		_firstEnd			= Iterator to sublist1 end
 * @params 		_secondBegin		= Iterator to sublist2 start
 * @params 		_secondEnd			= Iterator to sublist2 end
 * @params 		_less				= Less compare function
 *
 * @return		The new start of the list OR NULL
 *
 * @retval		NULL				= On initalize error OR when _begin == _end
 * @retval		_destBegin			= The new begin iterator of the list 
 */
ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd,
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
    ListItr endItr = _destBegin;
    
	_destBegin = ListItr_Splice(_destBegin, _secondBegin, _secondEnd);
	CHECK_NULL(_destBegin);
	
	_destBegin = ListItr_Splice(_destBegin, _firstBegin, _firstEnd);
	CHECK_NULL(_destBegin);
	
	if(NULL != _less)
	{
		ListItr_Sort(_destBegin, endItr, _less);
	}
	
	return _destBegin;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Removes a sublist [_begin.._end) from a list and creates a new list
 * 				with all removed items.
 * @Complexity	O(n)
 *
 * @params 		_begin				= Iterator to sublist start
 * @params 		_end				= Iterator to sublist end
 *
 * @return		The new list OR NULL
 *
 * @retval		NULL				= On initalize error OR when _begin == _end
 * @retval		newList				= The pointer for the new list
 */
List* ListItr_Cut(ListItr _begin, ListItr _end)
{
	List* newList;
	ListItr newDes;
	
	newList = ListCreate();
	CHECK_NULL(newList);
	
	newDes = ListItrEnd(newList);
	if(NULL == newDes)
	{
		ListDestroy(&newList, NULL);
		return NULL;
	}
	
	newDes = ListItr_Splice(newDes, _begin, _end);
	
	if(NULL == newDes)
	{
		ListDestroy(&newList, NULL);
		return NULL;
	}
	
	return newList;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 		Removes all duplicate elements from a sorted sublist [_begin.._end) 
 * 				and return a new list with all removed items.
 * @Complexity	O(N^2)
 * 
 *
 * @params 		_begin				= Iterator to sublist start
 * @params 		_end				= Iterator to sublist end
 * @params 		_equals				= Pointer to action function to check if a == b
 *
 * @returned	A new list with all removed items
 */
List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
	List* newList;
	ListItr newDes;
	ListItr current = _begin;
	ListItr removeItr;
	ListItr cmpItr;
	void* itrData;
	
	CHECK_NULL(_begin);
	CHECK_NULL(_end);
	CHECK_NULL(_equals);
	
	/* Create new list */
	newList = ListCreate();
	CHECK_NULL(newList);
	
	newDes = ListItrEnd(newList);
	if(NULL == newDes)
	{
		ListDestroy(&newList, NULL);
		return NULL;
	}
	
	cmpItr = ListItrNext(current);
	/* Loop over all original list itr */
	while(_end != cmpItr)
    {
    	/* use ForEach function to compare all Itr to the current iterator from original list*/
    	cmpItr = ListItr_ForEach(cmpItr, _end, _equals, current);
		CHECK_NULL(cmpItr);
		
		/* if something has found then: */
		if(_end != cmpItr)
		{
			/* remove it, save the data, and insert it to new list at the last position */
			removeItr = cmpItr;
			cmpItr = ListItrNext(cmpItr);
			itrData = ListItrRemove(removeItr);
			ListItrInsertBefore(newDes, itrData);
			continue;	
		}
		/* otherwise continue with the loop with the pre itr */
		current = ListItrNext(current);
		cmpItr = ListItrNext(current);
	}

	return newList;
}
/*----------------------------------------------------------------------------*/


