#ifndef __STRUCT_H__
#define __STRUCT_H__

/****************************** Define Declaration ****************************/
/*----------------------------------------------------------------------------*/
typedef struct Node Node;
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
struct Node
{
    void* m_data;
    Node* m_next;
    Node* m_prev;
};
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
struct List
{
    Node m_head;
    Node m_tail;
};
/*----------------------------------------------------------------------------*/

#endif /* __STRUCT_H__ */
