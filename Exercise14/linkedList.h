/*
 * Provided source - DO NOT MODIFY !!!
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node
{
   int value;
   struct node *next;
} ListNode;

/*
 * Adds the value to the front of the list. Has O(1) performance.
 * 
 * Parameter list: The head of the list, NULL if empty.
 * Parameter value: The value to add to the beginning of the list.
 *
 * Return: The head of the list.
 */ 
ListNode* addHead(ListNode *list, int value);

/*
 * Adds the value to the end of the list. Has O(N) performance.
 * 
 * Parameter list: The head of the list, NULL if empty.
 * Parameter value: The value to add to the end of the list.
 *
 * Return: The head of the list.
 */ 
ListNode* addTail(ListNode *list, int value);

/*
 * Deletes the node at the specified index. Indexes are zero-base. Reports
 * an error in the index is out-out-bounds (see reference solution behavior
 * for specific text you must match). Has O(N) performance.
 * 
 * Parameter list: The head of the list, NULL if empty.
 * Parameter index: The zero-based index of the value to remove from the list.
 *
 * Return: The head of the list.
 */ 
ListNode* deleteNode(ListNode *list, int index);

/*
 * Prints the values, if any, in the list from beginning to end. Has O(N)
 * performance.
 * 
 * Parameter list: The head of the list, NULL if empty.
 *
 * Return: Nothing. 
 */
void printList(ListNode *list);

#endif
