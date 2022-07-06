#include <stdio.h>
#include <stdlib.h>



/* Write a C function, merge lists(), that takes pointers to two NULL-terminated linked lists made up
of these structures, sorted in ascending numerical order (1, 2, 3 ,4 ,5 ,6), and merges them together into one sorted list.
Return a pointer to the head of the merged list.*/

/* approach 

    combine lists then sort 
*/
typedef struct node_st 
{
    int data;
    struct node_st *next;
}Node;

int getListSize(Node *list)
{   
    int length; 
    Node *temp;
    length = 0;
    for ( temp = list; temp->next != NULL; temp = temp -> next)
        length++;
    
    return length;

}

int comparator(const void *node1p, const void *node2p)
{
    Node *node1, *node2;
    node1 = *(Node **)node1p;
    node2 = *(Node **)node2p;

    return (node1->data - node2->data);
    
}



Node *append_list(Node *list, Node *rest)
{
    Node *t;
    if(list){
        for (t= list; t->next != NULL; t = t->next);
        t->next = rest;
    }
    else
        list = rest;

    return list;
}


Node *merge_lists(Node *a, Node *b)
{
    int length; 
    Node *list;
    list = append_list(a, b);
    length = getListSize(list);

    qsort(list, length, sizeof(Node *), comparator);

    return list;
    
}


