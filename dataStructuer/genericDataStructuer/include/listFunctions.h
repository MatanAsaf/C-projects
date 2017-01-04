/** 
 *  @file 		listFunction.h
 *  @brief 		header file for Generic Double Linked List Iterator list of Function
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

#ifndef __LIST_FUNCTIONS_H__
#define __LIST_FUNCTIONS_H__


#include "listItr.h"	/* for typedef struct listItr */ 


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief Predicate function returns a none zero value if predicate holds for element
 *
 * @param element			= Element to test
 * @param context			= Context to be used
 *
 * @return none zero if predicate holds
 */
typedef int (*PredicateFunction)(void * _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief Action function to operate on an element
 *
 * @param element			= Element to test
 * @param context			= Context to be used
 *
 * @return zero if action fails
 */
typedef int (*ListActionFunction)(void* _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief Action function to check if a < b
 *
 * @param a					= Element to test
 * @param b					= Element to test against
 *
 * @return none zero if _a < _b
 */
typedef int (*LessFunction)(void* _a, void* _b);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief Action function to check if a == b
 *
 * @param a					= Element to test
 * @param b					= Element to test against
 *
 * @return none zero if _a == _b
 */
typedef int (*EqualsFunction)(void* _a, void* _b);
/*----------------------------------------------------------------------------*/





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
ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context); 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       count elements in a sub list satisfying predicate
 * @details     find the element for which the predicate returns a zero value
 *              in the half open range [begin..end)
 *
 * @param       _begin              =   start search from here
 * @param       _end                =   end search here - not included
 * @param       _predicate          =   Predicate function
 * @param       _context            =   context to be passed to the predicate
 *
 * @return      count of all elements e where _predicate(e, _context) != 0
 */
size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context);
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
ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context);
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
void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less);
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
ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end);
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
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less);
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
List* ListItr_Cut(ListItr _begin, ListItr _end);
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
List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals);
/*----------------------------------------------------------------------------*/


#endif /* __LIST_FUNCTIONS_H__ */
