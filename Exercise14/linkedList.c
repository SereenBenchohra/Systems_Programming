#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include "memmon.h"

/*
 * Adds the value to the front of the list. Has O(1) performance.
 * 
 * Parameter list: The head of the list, NULL if empty.
 * Parameter value: The value to add to the beginning of the list.
 *
 * Return: The head of the list.
 */ 
ListNode* addHead(ListNode *list, int value)
{

   ListNode *new_node; 
   if(list == NULL)
   {
      fprintf(stderr, "malloc failure attempting to add %d\n" , value);
      exit(EXIT_FAILURE);
   }

   new_node = (ListNode*)malloc(sizeof(ListNode));
   new_node->value = value;
   new_node->next = list;
   list  = new_node;
   
   if(list == NULL )
   {
      fprintf(stderr, "No MEMORY");
      exit(EXIT_FAILURE);
   }

   return list;

}

/*
 * Adds the value to the end of the list. Has O(N) performance.
 * 
 * Parameter list: The head of the list, NULL if empty.
 * Parameter value: The value to add to the end of the list.
 *
 * Return: The head of the list.
 */ 

ListNode* addTail(ListNode *list, int value)
{
   ListNode *new_node;
   ListNode *lastNode;
   if(list == NULL) {
      fprintf(stderr, "malloc failure attempting to add %d\n", value);
      exit(EXIT_FAILURE);
   }

   new_node = (ListNode*)malloc(sizeof(ListNode));
   new_node->value = value;
   lastNode = list;
   new_node->next = NULL;
   
   if(list == NULL)
      list = new_node; 

   while(lastNode->next != NULL)
      lastNode = lastNode->next;

   lastNode->next = new_node;

   if(list == NULL )
   {
      fprintf(stderr, "No MEMORY");
      exit(EXIT_FAILURE);
   }

   return list;
}

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

void checkAndDelete(ListNode *list, int index)
{

   ListNode *tempNode, *prev;
   tempNode = list;
   prev = list;

   if((tempNode != NULL) && (tempNode->value == index))
   {
      list = tempNode ->next;
      free(tempNode);
   }

   while( (tempNode != NULL) & (tempNode->value != index))
   {
      prev = tempNode;
      tempNode = tempNode->next;
   }

   if(tempNode == NULL );

   if(tempNode ->value !=index)
      fprintf(stderr, "Index %d is out of bounds\n", index);
   else{
      prev->next = tempNode->next;
      free(tempNode);
   }

}

ListNode* deleteNode(ListNode *list, int index)
{
   
   if(list == NULL)
      fprintf(stderr, "Index %d is out of bounds\n", index);
   
   else
      checkAndDelete(list, index);
      
   return list;

}
/*
 * Prints the values, if any, in the list from beginning to end. Has O(N)
 * performance.
 * 
 * Parameter list: The head of the list, NULL if empty.
 *
 * Return: Nothing. 
 */
void printList(ListNode *list)
{
   if(list == NULL)
      printf("List: Empty\n");
   while(list != NULL)
   {
      printf(" %d", list->value);
      list = list->next;
   }

}
