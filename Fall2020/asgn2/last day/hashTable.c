#include <stdio.h>
#include <string.h>
#include "hashTable.h"
#include <stdlib.h>

#define LOADFACTOR 0.8

/*makes hashTable and initializes*/
HashTable *createHashTable(int arraySize){
    HashTable *Table;
    
    Table = (HashTable *)malloc(sizeof(HashTable));
    Table->HashArray = (Node **)calloc(arraySize, sizeof(Node *));
    Table->arraySize = arraySize;    
 
    return Table;
}

/* hashes word into hash key */
unsigned hash( char *word, int arraySize)
{
   unsigned hashval;

   for(hashval = 0; *word != '\0'; word++)
      hashval = *word + 31 * hashval;
   return hashval % arraySize;

}


Node* createNode(char *word)
{
   Node *newNode;
   newNode = (Node *)calloc(1, sizeof(Node));
   if(newNode == NULL)
   {   
      perror("Memory Allocated: ");
      exit(EXIT_FAILURE);

   }
   
   newNode->word = word;
   newNode->freq = 1;
   newNode->next = NULL;

   return newNode;
}

void resizeArray(HashTable *hashTable)
{
    int i;
    Node **linearArrayCpy;
 
    i = hashTable->numEntries;
    
    /*creates a 1D linear Array of Node pointers */
    linearArrayCpy = linearArray(hashTable);

    free(hashTable->HashArray);

    hashTable->numEntries = 0;    

    hashTable->arraySize *= 2;
    hashTable->HashArray = (Node **)calloc(hashTable->arraySize,
                                       sizeof(Node *));
  

    while(i>0 ){ /*reinserts node into  hashTable */
        resizeInsertion(linearArrayCpy[i - 1], hashTable);
        hashTable->numEntries++;
        i--;
    }

    free(linearArrayCpy);

    hashTable->loadFactor = (float) hashTable->numEntries /
        (float) hashTable->arraySize;
    return;
}

void resizeInsertion(Node *node, HashTable *hashTable){
    
    int hashIndex;
    Node *currentNode;

    hashIndex = hash(node->word, hashTable->arraySize);
    currentNode = hashTable->HashArray[hashIndex];
    
    if(currentNode == NULL){
        hashTable->HashArray[hashIndex] = node;
        return;
    }

    while(currentNode->next)
        currentNode = currentNode->next;
 
    currentNode->next = node;

    return;
}

Node **linearArray(HashTable *hashTable)
{
   Node **linearArrayC;
   int bucketsLeft, i, j;
   Node *curNode, *nextNode;

   bucketsLeft = hashTable->arraySize;

   linearArrayC = (Node **)calloc(hashTable->numEntries, sizeof(Node *));
   
   if(linearArrayC == NULL){   
      perror("Memory Allocated: ");
      exit(EXIT_FAILURE);
   }
  

   j = 0;

   /* goes through hashArray and chains and converts to linear array of single
    * nodes */

   for(i = 0; i < bucketsLeft; i++) 
   {
     curNode = hashTable->HashArray[i];
     while(curNode) 
      {
         linearArrayC[j] = curNode;
         nextNode = curNode->next;
         curNode->next = NULL;
         j++;
         curNode = nextNode;
      }

   }
   
   return linearArrayC;

}

void addData( char *word, HashTable *hashTable) /* attempts to add word */
{
    unsigned hashIndex;
    Node *curNode;

    hashIndex = hash(word, hashTable->arraySize);

    /*sees if bucket is empty */
    if(hashTable->HashArray[hashIndex] == NULL){
        hashTable->HashArray[hashIndex] = createNode(word);
        hashTable->numEntries++;
      
    hashTable->loadFactor = (float) hashTable->numEntries /
        (float) hashTable->arraySize; 
      
        if(hashTable->loadFactor >= LOADFACTOR)
            resizeArray(hashTable);
        return; 
    }

    /*goes though linked list */
    else{
        curNode = hashTable->HashArray[hashIndex];    

        
        while(curNode->next != NULL){
            if(strcmp(curNode->word, word) == 0){ /*if word already exists */
                curNode->freq++;
                free(word);
                return;
            }
            curNode = curNode->next;
        }
        if(strcmp(curNode->word, word) == 0){ /* fence posting */
            curNode->freq++;
            free(word);
            return;
        }
        else{ /* append to linked list */
            curNode->next = createNode(word);
            hashTable->numEntries++;
            hashTable->loadFactor = (float) hashTable->numEntries /
                (float) hashTable->arraySize;
            if(hashTable->loadFactor >= LOADFACTOR)
                resizeArray(hashTable);
            return;
        }
    }  
       
} 

   




