/** 
 *  @file 		binTree.h
 *  @brief 		Header file for Generic Binary Tree data type
 * 
 *  @details 	Implement a binary search tree ADT.
 *  			The tree is implemented using a sentinel. 
 *  			The first node in the tree is the sentinel left subtree.
 * 
 *  @author 	Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 		last update: 2017-01-01    
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stddef.h>  /* for size_t */


/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct BSTree BSTree; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef void* BSTreeItr; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef int (*LessComparator)(void* _left, void* _right);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Predicate function returns a none zero value if predicate holds for element
 *
 * @param       _element        =       element to test
 * @param       _context        =       context to be used
 *
 * @return      none zero if predicate holds
 */
typedef int (*PredicateFunction)(void * _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Action function to operate on an element
 *
 * @param       _element        =        element to test
 * @param       _context        =        context to be used
 *
 * @return      zero if action fails
 */
typedef int (*ActionFunction)(void* _element, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef enum
{
    BSTREE_TRAVERSAL_PREORDER = 0, /* father, leftSon, rightSon  */
    BSTREE_TRAVERSAL_INORDER,      /* leftSon, father, rightSon  */
    BSTREE_TRAVERSAL_POSTORDER     /* leftSon, rightSon, father */
} BSTreeTraversalMode;
/*----------------------------------------------------------------------------*/





/******************************** API functions *******************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief   Create a binary search tree
 * @details Creates an empty binary search tree with sentinel
 * 
 * @param   less			= A comparison function that returns true (none zero value) 
 *							if x < y  and false (zero) otherwise.
 *
 * @return 	The Tree pointer:
 *
 * @retval 	On success    	= A pointer to the newly created tree.
 * @retval  NULL          	= On failure due to allocation failure OR due to uninitialized pointer given
 */
BSTree* BSTree_Create(LessComparator _less);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Destroy tree
 * @details Destroys the tree, If supplied with non-NULL destroyer function, 
 *			frees the items in the tree.
 * @Complexity	O(n)
 *
 * @param   tree           	= A previously created Tree ADT returned via BSTreeCreate
 * @param   destroyer      	= A function to destroy the data in the tree (may be NULL if unnecessary)
 *
 * @return  void
 */
void  BSTree_Destroy(BSTree* _tree, void (*_destroyer)(void *) );
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Add an element to tree if it's not already there
 * @details Insert element to binary tree, using the tree's comparison function
 * @Complexity 	Average O(log n).
 * 				Worst 	O(n)
 *
 * @param   tree           	= A previously created Tree ADT returned via BSTreeCreate
 * @param   item           	= An item to add to the tree
 *
 * @return  Iterator pointing to the item added OR iterator to the end on failure:
 *
 * @retval 	On success    	= A pointer to the newly created tree iterator element that hold the data.
 * @retval  NULL          	= On failure due to allocation failure OR due to uninitialized pointer given OR duplicates
 *
 * @warning Can't insert duplicates
 */
BSTreeItr BSTree_Insert(BSTree* _tree, void* _item);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Search the first element for which the given predicate returns 0
 * @details Iterating using in-order manner over elements
 * @Complexity  O(k * n) where k is the time complexity of the predicate
 *
 * @param   tree            = A previously created Tree ADT returned via BSTreeCreate
 * @param   predicate       = Predicate function
 * @param   context         = Predicate parameters
 *
 * @return  An iterator pointing to the first data found:
 *
 * @retval  NULL            = On NULL input OR when the itr NOT found OR when tree is empty
 * @retval  Iterator found  = When the itr found the element
 */
BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get an in-order itertator to the tree's begin 
 * @Complexity  O(1) 
 *
 * @param   tree           	= A previously created Tree ADT returned via BSTreeCreate
 *
 * @return  An iterator pointing at the tree's begin: 
 *
 * @retval  NULL            = On NULL input
 * @retval  Iterator begin  = On success
 * @retval  Iterator end  	= If tree is empty
 */
BSTreeItr BSTreeItr_Begin(const BSTree* _tree);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the tree's end (in order)
 * @Complexity  O(1)
 *
 * @param   tree           	= A previously created Tree ADT returned via BSTreeCreate
 *
 * @return  An iterator pointing at the tree's end: 
 *
 * @retval  NULL            = On NULL input
 * @retval  Iterator end   	= On success
 */
BSTreeItr BSTreeItr_End(const BSTree* _tree);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Compare two iterators
 *
 * @param   a          		= First iterator
 * @param   b          		= Iterator to compare to the first
 *
 * @return  Status of the compare result: 
 *  
 * @retval  0 				= If are not the same 
 * @retval  1 				= If iterators are the same
 *
 * @warning if both ListItr are uninitialized the result will be 1 
 */
int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 *
 * @param   it                            	=   Pointer to current iterator 
 *
 * @return  BSTreeItr pointer:
 *
 * @retval  All iterator exclude the end    =   Iterator pointing at the next tree's iterator
 * @retval  At end of the list              =   Iterator pointing at itself 
 * @retval  NULL              				=   If pointer is uninitialized     
 */
BSTreeItr BSTreeItr_Next(BSTreeItr _it);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the previous element from a given iterator
 * @warning if _itr is begin iterator it will be returned
 *
 * @param   it                            	=   Pointer to current iterator 
 *
 * @return  BSTreeItr pointer:
 *
 * @retval  All iterator exclude the begin  =   Iterator pointing at the previous tree's iterator
 * @retval  At begin of the list            =   Iterator pointing at itself 
 * @retval  NULL              				=   If pointer is uninitialized     
 */
BSTreeItr BSTreeItr_Prev(BSTreeItr _it);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief 	Removes the BSTreeItr the current iterator is pointing at
 * @details Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * @Complexity 	Best 	O(1) -	If the current iterator have no more the 1 child.
 * 				Worst 	O(n) -	If the current iterator and all the next have 2 children.
 *
 * @param   it         		=   Pointer to Tree itself- use in case of removing the root
 * @param   it         		=   Pointer to current iterator to remove
 *
 * @return  Element data pointer:
 * 
 * @retval  Data         	=   The removed data
 * @retval  NULL         	=   If iterator pointing to the end OR pointer is uninitialized
 */
void* BSTreeItr_Remove(BSTree* _tree, BSTreeItr _it);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get data from the tree BSTreeItr the current iterator is pointing to
 *
 * @param   it        		=   Pointer to current iterator to get data from
 *
 * @return  Element data pointer:
 *
 * @retval  Data         	=   If the iterator is pointing at data
 * @retval  NULL         	=   If iterator pointing to the end OR pointer is uninitialized
 */
void* BSTreeItr_Get(BSTreeItr _it);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by given traversal mode
 * @details Iteration will on the first element for which action returns a zero
 *          or on reaching end of the conrainer
 * @Complexity  O(n)
 *
 * @param   tree           	=       Tree to iterate over
 * @param   mode           	=       Traversal mode - TREE_TRAVERSAL_PREORDER, TREE_TRAVERSAL_INORDER or TREE_TRAVERSAL_POSTORDER
 * @param   action         	=       Action function to call for each element
 * @param   context        	=       Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned zero value
 *
 * @retval  iterator        =   Where the loop has stopped
 * @retval  NULL         	=   If pointer is uninitialized
 */
BSTreeItr BSTree_ForEach(const BSTree* _tree, BSTreeTraversalMode _mode,
                 ActionFunction _action, void* _context);
/*----------------------------------------------------------------------------*/


#endif /* __BINARY_TREE_H__ */
