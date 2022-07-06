#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct node 
{
   char data;
   unsigned int freq;
   struct node *left;
   struct node *right;

}HuffNode;

typedef struct 
{
   unsigned int size, capacity;
   HuffNode **array;

}HuffArray;

HuffNode *createHuffNode(char data, unsigned int freq)
{
   HuffNode *newNode;
   newNode = malloc(sizeof(HuffNode));
   if(newNode == NULL)
   {   
      perror("Memory Allocated: ");
      exit(EXIT_FAILURE);
   }

   newNode->data = data;
   newNode->freq = freq;
   newNode->left = NULL;
   newNode->right = NULL;

   return newNode;
 
}

HuffArray* createHuffArray(unsigned capacity) 
{ 
   HuffArray  *hArray  = (HuffArray*)malloc(sizeof(HuffArray)); 
                          
                              
   hArray->size = 0; 
                                     
   hArray->capacity = capacity; 
                                           
   hArray->array  = ( HuffNode**)malloc(hArray->capacity * sizeof(struct MinHeapNode*)); 
  
  return hArray; 
                                                           
                                                           
} 

void deleteHuffNode(HuffNode *huffnode)
{
   if(huffnode != NULL)
   {
      deleteHuffNode(huffnode->left);
      deleteHuffNode(huffnode->right);
      free(huffnode);
   }

}

/* fix this  */ 
void encode(HuffNode *node, unsigned int *array, unsigned int pos)
{
   if(node->left){
      /* shift left? bit  probably that method */ 
      array[pos] = 0;
      encode(node->left, array, pos + 1);
   }

   if(node->right) {
      /* shift bits */
      array[pos] = 1;
      encode(node->right, array, pos + 1);
   
   }

   if (!(node->left || node->right)) {
         fun(node->data, arr, pos);
   }

}

/* possible to change later */

char * decode(HuffNode *root, char *encoded)
{
   int i, len;
   char *decoded;
   HuffNode *current;
   current = root;
   len = strlen(encoded);

   for(i = 0; i < len; i++)/*loops through encoded string */
   {

      if(encoded[i] == '0')
         current = current->left;
      else 
         current = current->right;

     /* reached leaf node */
     if(current->left == NULL && current->right)
     {
        /* add the letter to the decoded string */
        decoded += current->data; 
        current = root;
     }

   }

     return decoded + '\0';
}
