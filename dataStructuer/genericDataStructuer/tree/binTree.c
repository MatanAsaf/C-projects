/** 
 *  @file 		binTree.c
 *  @brief 		src file for Generic Binary Tree data type
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

#include "binTree.h" 	/* header file */
#include <stdlib.h> 	/* for size_t, NULL, malloc, free */

#define CHECK_NULL(param)	do{ if(NULL == (param) ) { return NULL;}  } while(0)
#define MAGIC_NUMBER (123456789)                                               
#define ROOT_FATHER (-1)
#define RIGHT_SON  	(0)
#define LEFT_SON  	(1)



                               
/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct Node Node;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
struct Node
{
    void* m_data;	 /* Pointer to node element data */
    Node* m_father;  /* Pointer to previous node parent */
    Node* m_leftSon; /* Pointer to node with data that smaller then the current node data */
    Node* m_rightSon;/* Pointer to node with data that bigger then the current node data */
};
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
struct BSTree
{
    Node* m_root; 
    LessComparator m_compare;
    size_t m_magicNumber;
}; 
/*----------------------------------------------------------------------------*/




/*************************** Declaration of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       Add an element to tree if it's not already there
 *              Insert element to binary tree, using the tree's comparison function
 * Average time complexity O(log n).
 * Worst: O(n)
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate 
 * @param       _father         = A element root
 * @param       _sonDirection   = An index of the position of the son according to his father: 
 *									RIGHT_SON 	= new son is the right son 
 *									LEFT_SON    = new son is the left son
 *									ROOT_FATHER	= new son is the root
 * @param       _item   		= Pointer to data
 *
 * @return      return the new iterator that pointing to the item added 
 */
static BSTreeItr CreateNewNode(BSTree* _tree, Node* _father, int _sonDirection, void* _item);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove an element (that have NO children) from tree and return it's data
 * @details     Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(1).
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate 
 * @param       _chosenNode		= A tree iterator as Node typedef
 * @param       _ptr			= The pointer to modify for the parent
 *
 * @return      removed the node data
 */
static void* RemoveNodeWithNoChild(BSTree* _tree, Node* _chosenNode, Node* _ptr);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove an element (that have 1 children) from tree and return it's data
 * @details     Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(1).
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate 
 * @param       _chosenNode     = A tree iterator as Node typedef
 *
 * @return      removed the node data
 */
static void* RemoveNodeWithOneChild(BSTree* _tree, Node* _chosenNode);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove an element (that have 2 children) from tree and return it's data
 * @details     Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(n).
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate
 * @param       _chosenNode     =       A tree iterator as Node typedef
 *
 * @return      removed the node data
 */
static void* RemoveNodeWithTwoChild(BSTree* _tree, Node* _chosenNode);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       call the right function to remove all link of a Node according to it's number of children
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate
 * @param       _chosenNode     = A tree iterator as Node typedef
 *
 * @return      removed the node data
 */
static void* OptNodeChild(BSTree* _tree, Node* _chosenNode);
/*----------------------------------------------------------------------------*/                                                    


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by PreOrder mode
 * @details Iteration will stop on the first element for which action returns a zero
 *          or on reaching end of the container.
 *			PreOrder:
 *			1. Check current node and preform an action
 *			2. Traverse the left subtree
 *			3. Traverse the right subtree
 * @Complexity  O(n)
 *
 * @param   itr        		=   First iterate to start with
 * @param   action         	=   Action function to call for each element
 * @param   context        	=   Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned zero value
 */
static BSTreeItr ForEachPreOrder(BSTreeItr _itr, ActionFunction _action, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by InOrder mode
 * @details Iteration will stop on the first element for which action returns a zero
 *          or on reaching end of the container.
 *			InOrder:
 *			1. Traverse the left subtree
 *			2. Check current node and preform an action
 *			3. Traverse the right subtree
 * @Complexity  O(n)
 *
 * @param   itr        		=   First iterate to start with
 * @param   action         	=   Action function to call for each element
 * @param   context        	=   Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned zero value
 */
static BSTreeItr ForEachInOrder(BSTreeItr _itr, ActionFunction _action, void* _context);
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by PostOrder mode
 * @details Iteration will stop on the first element for which action returns a zero
 *          or on reaching end of the container.
 *			PostOrder:
 *			1. Traverse the left subtree
 *			2. Traverse the right subtree
 *			3. Check current node and preform an action
 * @Complexity  O(n)
 *
 * @param   itr        		=   First iterate to start with
 * @param   action         	=   Action function to call for each element
 * @param   context        	=   Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned zero value
 */
static BSTreeItr ForEachPostOrder(BSTreeItr _itr, ActionFunction _action, void* _context);
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
BSTree* BSTree_Create(LessComparator _less)
{
    BSTree* newTree;
    
    CHECK_NULL(_less);

    newTree = (BSTree*)calloc( 1, sizeof (BSTree) );
    CHECK_NULL(newTree);
    
    newTree->m_compare = _less;
    newTree->m_magicNumber = MAGIC_NUMBER;
    
    return newTree;
}
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
void BSTree_Destroy(BSTree* _tree, void (*_destroyer)(void *) )
{
	Node* current = BSTreeItr_Begin(_tree);
	Node* endItr = BSTreeItr_End(_tree);
	Node* tempItr;
	
    if(NULL == _tree || _tree->m_magicNumber != MAGIC_NUMBER)
    {
    	return;
    }
    
	while( endItr != current)  
	{
		if( NULL != _destroyer )
		{
			_destroyer(current->m_data);
		}
		
		tempItr = BSTreeItr_Next(current);
		free(current);
		current = tempItr;
	}
	
	_tree->m_magicNumber = 987654321;
    free(_tree);
    
    return;
}
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
BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	Node* current;
	Node* lastFather = NULL;
	int status = ROOT_FATHER;
	
	CHECK_NULL(_tree);
	CHECK_NULL(_item);

	current = _tree->m_root;
	
	/* Found the position on the tree for the item: */
	while( NULL != current )
	{
		lastFather = current;
		
		if( 1 == _tree->m_compare(_item, current->m_data) )
		{
			current = current->m_leftSon;
			status = LEFT_SON;
			continue;
		}
		
		if( 1 == _tree->m_compare(current->m_data, _item) )
		{
			current = current->m_rightSon;
			status = RIGHT_SON;
			continue;
		}
		
		return NULL; /* Can't insert duplicates */	
	}
		
	return CreateNewNode(_tree, lastFather, status, _item);
}
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
BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
	Node* current;
	Node* lastItr;
	
	CHECK_NULL(_tree);
	CHECK_NULL(_predicate);
	
	current = BSTreeItr_Begin(_tree);
	CHECK_NULL(current);
	
	lastItr = BSTreeItr_End(_tree); 
	CHECK_NULL(lastItr);
	
	while( lastItr != current )
	{
		if( 1 == _predicate(current->m_data, _context) )
		{
			return (BSTreeItr)current;
		}
		
		current = BSTreeItr_Next(current);	
	}
	
	/* Check the lastItr also: */
	if( 1 == _predicate(current->m_data, _context) )
	{
		return (BSTreeItr)current;
	}
	
	return NULL;
	
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get an in-order itertator to the tree's begin 
 * @Complexity O(log n)
 *
 * @param   tree           	= A previously created Tree ADT returned via BSTreeCreate
 *
 * @return  An iterator pointing at the tree's begin: 
 *
 * @retval  NULL            = On NULL input
 * @retval  Iterator begin  = On success
 * @retval  Iterator end  	= If tree is empty
 */
BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	Node* current;
	
	CHECK_NULL(_tree);
	
	current = _tree->m_root;
	CHECK_NULL(current);
	
	while( NULL != current->m_leftSon )
	{
		current = current->m_leftSon;
	}
	
	return (BSTreeItr)current;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Get itertator to the tree's end (in order)
 * @Complexity  O(log n)
 *
 * @param   tree           	= A previously created Tree ADT returned via BSTreeCreate
 *
 * @return  An iterator pointing at the tree's end: 
 *
 * @retval  NULL            = On NULL input
 * @retval  Iterator end   	= On success
 */
BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	Node* current;
	
	CHECK_NULL(_tree);
	
	current = _tree->m_root;
	CHECK_NULL(current);
	
	while( NULL != current->m_rightSon )
	{
		current = current->m_rightSon;
	}
	
	return (BSTreeItr)current;
}
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
int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	return ( _a == _b );
}
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
BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	Node* currentNode = (Node*)_it;
	
	CHECK_NULL(_it);
	
	/* If there is no RIGHT son: then find the first father that the currentNode is his LEFT son */
	if( NULL == currentNode->m_rightSon )
	{
		while( NULL != currentNode  && (currentNode->m_father->m_leftSon != currentNode) )
		{
			currentNode = currentNode->m_father; 	
		}
		
		if(NULL == currentNode) /* _it == the end */
		{
			return _it;
		}
		
		return (BSTreeItr)(currentNode->m_father);
	}
	/* If there is a RIGHT son: then find the last LEFT son of the currentNode RIGHT son */
	currentNode = currentNode->m_rightSon;
	 
	while( NULL != currentNode->m_leftSon )
	{
		currentNode = currentNode->m_leftSon; 	
	}
	
	return (BSTreeItr)currentNode;
}
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
BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	Node* currentNode = (Node*)_it;
	
	CHECK_NULL(_it);
	
	/* If there is no LEFT son: then find the first father that the currentNode is his RIGHT son */
	if( NULL == currentNode->m_leftSon )
	{
		while( NULL != currentNode  && (currentNode->m_father->m_rightSon != currentNode) )
		{
			currentNode = currentNode->m_father; 	
		}
		
		if(NULL == currentNode) /* _it == the beginning */
		{
			return _it;
		}
		
		return (BSTreeItr)(currentNode->m_father);
	}
	/* If there is a LEFT son: then find the last RIGHT son of the currentNode LEFT son */
	currentNode = currentNode->m_leftSon;
	 
	while( NULL != currentNode->m_rightSon )
	{
		currentNode = currentNode->m_rightSon; 	
	}
	
	return (BSTreeItr)currentNode;
}
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
void* BSTreeItr_Remove(BSTree* _tree, BSTreeItr _it)
{
	Node* current = (Node*)(_it);
	
	CHECK_NULL(_tree);
	CHECK_NULL(_it);
	
	return OptNodeChild(_tree, current);
}
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
void* BSTreeItr_Get(BSTreeItr _it)
{
	CHECK_NULL(_it);
	
	return ( (Node*)(_it) )->m_data;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by given traversal mode
 * @details Iteration will on the first element for which action returns a zero
 *          or on reaching end of the container
 * @Complexity  O(n)
 *
 * @param   tree           	=       Tree to iterate over
 * @param   mode           	=       Traversal mode - TREE_TRAVERSAL_PREORDER, TREE_TRAVERSAL_INORDER or TREE_TRAVERSAL_POSTORDER
 * @param   action         	=       Action function to call for each element
 * @param   context        	=       Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned none zero value
 *
 * @retval  iterator        =   Where the loop has stopped
 * @retval  NULL         	=   If pointer is uninitialized OR ilegal TraversalMode
 */
BSTreeItr BSTree_ForEach(const BSTree* _tree, BSTreeTraversalMode _mode,
                 ActionFunction _action, void* _context)
{
	BSTreeItr result;
	BSTreeItr startItr;
	
	CHECK_NULL(_tree);
	
	startItr = _tree->m_root;
	
	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER:
			result = ForEachPreOrder(startItr, _action, _context);
			break;
		case BSTREE_TRAVERSAL_INORDER:
			result = ForEachInOrder(startItr, _action, _context);
			break;
		case BSTREE_TRAVERSAL_POSTORDER:
			result = ForEachPostOrder(startItr, _action, _context);
			break;
		default:
			return NULL;
			break;
	}
	
	if( NULL == result )
	{
		result = BSTreeItr_End(_tree);
	}
	
	return result;
}
/*----------------------------------------------------------------------------*/





/*************************** Implication of functions *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       Add an element to tree if it's not already there
 *              Insert element to binary tree, using the tree's comparison function
 * Average time complexity O(log n).
 * Worst: O(n)
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate 
 * @param       _father         = A element root
 * @param       _sonDirection   = An index of the position of the son according to his father: 
 *									RIGHT_SON 	= new son is the right son 
 *									LEFT_SON    = new son is the left son
 *									ROOT_FATHER	= new son is the root
 * @param       _item   		= Pointer to data
 *
 * @return      return the new iterator that pointing to the item added 
 */
static BSTreeItr CreateNewNode(BSTree* _tree, Node* _father, int _sonDirection, void* _item)
{
	Node* newNode;
	
	newNode = (Node*)calloc( 1, sizeof (Node) );
	CHECK_NULL(newNode);
	
	newNode->m_data = _item;
	newNode->m_father = _father;
	
	if( ROOT_FATHER == _sonDirection )
	{
		_tree->m_root = newNode;
		return (BSTreeItr)newNode;
	}
	
	if( RIGHT_SON == _sonDirection )
	{
		_father->m_rightSon = newNode;
	}
	else
	{
		_father->m_leftSon = newNode;
	}
	
	return (BSTreeItr)newNode;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove an element (that have NO children) from tree and return it's data
 * @details     Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(1).
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate 
 * @param       _chosenNode		= A tree iterator as Node typedef
 * @param       _ptr			= The pointer to modify for the parent
 *
 * @return      removed the node data
 */
static void* RemoveNodeWithNoChild(BSTree* _tree, Node* _chosenNode, Node* _ptr)
{
	void* tempData = _chosenNode->m_data;
	
	/* If this node is the root: */
	if( NULL == _chosenNode->m_father )
	{
		_tree->m_root = _ptr;
		free(_chosenNode);
		return tempData;
	}
	
	if( _chosenNode->m_father->m_rightSon == _chosenNode )
	{
		_chosenNode->m_father->m_rightSon = _ptr;
	}
	else
	{
		_chosenNode->m_father->m_leftSon = _ptr;
	}
	
	free(_chosenNode);
	
	return tempData;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove an element (that have 1 children) from tree and return it's data
 * @details     Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(1).
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate 
 * @param       _chosenNode     = A tree iterator as Node typedef
 *
 * @return      removed the node data
 */
static void* RemoveNodeWithOneChild(BSTree* _tree, Node* _chosenNode)
{
	Node* child;
	
	/* Connect pointers in the child node: */
	if( NULL == _chosenNode->m_rightSon )
	{
		_chosenNode->m_leftSon->m_father = _chosenNode->m_father;
		child = _chosenNode->m_leftSon;
	}
	else
	{
		_chosenNode->m_rightSon->m_father = _chosenNode->m_father;
		child = _chosenNode->m_rightSon;
	}
	
	return RemoveNodeWithNoChild(_tree, _chosenNode, child); /* Connect pointers in the parent node */
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       Remove an element (that have 2 children) from tree and return it's data
 * @details     Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(n).
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate
 * @param       _chosenNode     =       A tree iterator as Node typedef
 *
 * @return      removed the node data
 */
static void* RemoveNodeWithTwoChild(BSTree* _tree, Node* _chosenNode)
{
	Node* nextNode;
	void* tempData = _chosenNode->m_data; 
	
	/* found the the next element after the chosen node */
	nextNode = (Node*)BSTreeItr_Next( (BSTreeItr)_chosenNode ); 
	
	/* copy the data to the current node */
	_chosenNode->m_data = nextNode->m_data;

	OptNodeChild(_tree, nextNode); /* Eventually the next node untill the endItr will not have 2 children */
	
	return tempData;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief       call the right function to remove all link of a Node according to it's number of children
 *
 * @param       _tree         	= A previously created Tree ADT returned via BSTreeCreate
 * @param       _chosenNode     = A tree iterator as Node typedef
 *
 * @return      removed the node data
 */
static void* OptNodeChild(BSTree* _tree, Node* _chosenNode)
{
	/* Option 1: the itr have NO children */
	if( NULL == _chosenNode->m_rightSon && NULL == _chosenNode->m_leftSon )
	{
		return RemoveNodeWithNoChild(_tree, _chosenNode, NULL);
	}
	/* Option 2: the itr have 1 child */
	if( NULL == _chosenNode->m_rightSon || NULL == _chosenNode->m_leftSon )
	{
		return RemoveNodeWithOneChild(_tree, _chosenNode);	
	}
	/* Option 3: the itr have 2 children */
	return RemoveNodeWithTwoChild(_tree, _chosenNode);
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by PreOrder mode.
 * @details Iteration will stop on the first element for which action returns a zero
 *          or on reaching end of the container.
 *			PreOrder:
 *			1. Check current node and preform an action
 *			2. Traverse the left subtree
 *			3. Traverse the right subtree
 * @Complexity  O(n)
 *
 * @param   itr        		=   First iterate to start with
 * @param   action         	=   Action function to call for each element
 * @param   context        	=   Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned zero value
 */
static BSTreeItr ForEachPreOrder(BSTreeItr _itr, ActionFunction _action, void* _context)
{
	if( NULL == _itr )
	{
		return _itr;
	}
	
	if( 0 == _action( ( (Node*)_itr )->m_data, _context) )
	{
		return _itr;
	}
	
	if( NULL != ForEachPreOrder( ( (Node*)_itr )->m_leftSon, _action, _context) )
	{
		return _itr;
	}
	
	if( NULL != ForEachPreOrder( ( (Node*)_itr )->m_rightSon, _action, _context) )
	{
		return _itr;
	}
	
	return NULL;

}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by InOrder mode
 * @details Iteration will stop on the first element for which action returns a zero
 *          or on reaching end of the container.
 *			InOrder:
 *			1. Traverse the left subtree
 *			2. Check current node and preform an action
 *			3. Traverse the right subtree
 * @Complexity  O(n)
 *
 * @param   itr        		=   First iterate to start with
 * @param   action         	=   Action function to call for each element
 * @param   context        	=   Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned zero value
 */
static BSTreeItr ForEachInOrder(BSTreeItr _itr, ActionFunction _action, void* _context)
{
	if( NULL == _itr )
	{
		return _itr;
	}
	
	if( NULL != ForEachPreOrder( ( (Node*)_itr )->m_leftSon, _action, _context) )
	{
		return _itr;
	}
	
	if( 0 == _action( ( (Node*)_itr )->m_data, _context) )
	{
		return _itr;
	}
	
	
	if( NULL != ForEachPreOrder( ( (Node*)_itr )->m_rightSon, _action, _context) )
	{
		return _itr;
	}
	
	return NULL;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/** 
 * @brief   Performs an action function on every element in tree, by PostOrder mode
 * @details Iteration will stop on the first element for which action returns a zero
 *          or on reaching end of the container.
 *			PostOrder:
 *			1. Traverse the left subtree
 *			2. Traverse the right subtree
 *			3. Check current node and preform an action
 * @Complexity  O(n)
 *
 * @param   itr        		=   First iterate to start with
 * @param   action         	=   Action function to call for each element
 * @param   context        	=   Parameters for the function
 *
 * @return  Iterator to end or an iterator to the specific element where action returned zero value
 */
static BSTreeItr ForEachPostOrder(BSTreeItr _itr, ActionFunction _action, void* _context)
{
	if( NULL == _itr )
	{
		return _itr;
	}
	
	if( NULL != ForEachPreOrder( ( (Node*)_itr )->m_leftSon, _action, _context) )
	{
		return _itr;
	}
	
	if( NULL != ForEachPreOrder( ( (Node*)_itr )->m_rightSon, _action, _context) )
	{
		return _itr;
	}
	
	if( 0 == _action( ( (Node*)_itr )->m_data, _context) )
	{
		return _itr;
	}
	
	return NULL;
}
/*----------------------------------------------------------------------------*/
