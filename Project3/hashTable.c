#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include "hashTable.h"

typedef struct node
{
HTEntry entry;
struct node *next;
}HashNode ;



/* The hash table metric structure returned by htMetrics.*/


typedef struct
{
   HTFunctions *htFunctions;
   unsigned *Sizes;
   int NumSizes;
   int curSize, curSizeIndex, numElements;
   int uniqueEntries, totalEntries;
   float reHashLoadFactor;
   HashNode **theArray;
   HashNode **arrayOfChains;
   HTMetrics metrics;
}HashTable;

void assertCheck(unsigned sizes[], int numSizes, float rehashLoadFactor)
{
   int i;
   assert(numSizes >= 1);
   assert(sizes[0] != 0); /*ask about this */

   for (i = 1; i < numSizes; ++i)
      assert(sizes[i-1] < sizes[i]); /*Make this a  loop */

   assert(rehashLoadFactor > 0.0 && rehashLoadFactor<= 1 );
}

void* htCreate( HTFunctions *functions, unsigned sizes[],
   int numSizes, float rehashLoadFactor)
{
   HashTable *hashTable; /*Dynamically allocate memory */
   assertCheck(sizes, numSizes, rehashLoadFactor);
   hashTable = (HashTable *)malloc(sizeof(HashTable));
   hashTable-> htFunctions = functions;
   /*hashTable -> Sizes = (unsigned *)malloc(sizeof(unsigned)* numSizes);*/
   hashTable -> Sizes = sizes;
   hashTable ->curSize = sizes[0];
   hashTable -> NumSizes = numSizes;
   hashTable -> uniqueEntries = 0;
   hashTable -> totalEntries = 0;
   hashTable ->numElements = 0;
   hashTable -> reHashLoadFactor = rehashLoadFactor;
   hashTable -> curSizeIndex = 0;

   hashTable ->theArray = (HashNode **)calloc(sizes[0], sizeof(HashNode *));

   return (void*)hashTable;
}

void freeNodes(int i, HashTable *ht)
{
   HashNode *temp, *head;
   head = ht->theArray[i];
   while (head->next != NULL) /*keeps track of chains */
   {
      temp = head;
      head = head->next;
      free(temp->entry.data);
      free((temp));
   }
   //free(ht->theArray[i]);
}

void freeArray(void *hashTable)
{
   int i;
   HashTable *ht;
   ht = (HashTable*)hashTable;
   /*ht->theArray[i] != NULL) */
   for(i = 0; i < ht->curSize; i++)
      if (ht->theArray[i] != NULL)
         freeNodes(i, ht);
   free(ht->theArray);
   /*free(ht -> Sizes); */
}

void htDestroy(void *hashTable)
{
   freeArray(hashTable);
   free(hashTable);
}

void emptyHTError(void *hashTable)
{
   HashTable *hashtable = (HashTable*)hashTable;
   if( hashtable == NULL) {
      perror("");
      fprintf(stderr, "malloc failure attempting to add \n");
      exit(EXIT_FAILURE);
   }
}

unsigned HashIndex(void *data, HashTable *hashtable)
{
   int hash, hashIndex;
   hash = hashtable->htFunctions->hash(data);
   hashIndex = hash % htCapacity(hashtable);
   return hashIndex;
}

void ifNodeNotNull(HashNode **temp, HashNode *curNode, HashNode *tempCurNode)
{
   while (tempCurNode->next != NULL)
      tempCurNode = tempCurNode->next;
   tempCurNode->next = curNode;

}
void addElementsToArray(HashNode **temp, int hashIndex, HashNode *curNode)
{
   HashNode *tempCurNode;
   tempCurNode = temp[hashIndex];
   if(temp[hashIndex] == NULL)
      temp[hashIndex] = curNode;
   else
      ifNodeNotNull(temp, curNode, tempCurNode);

}

void CurNodeIsNULL(HashNode *curNode, HashNode **temp, HashTable *hashtable,
   int i)
{
   int hashIndex = 0;
   curNode = hashtable->theArray[i];
   while (curNode->next != NULL) {/*keeps track of chains */
      hashIndex = HashIndex(curNode->entry.data, hashtable);
      addElementsToArray(temp, hashIndex, curNode);
      curNode = curNode->next;
   }

}
void reSizeArray(HashNode *curNode, HashNode  **temp, HashTable *hashtable,
   int oldSize)
{
   int i, hashIndex;
   hashIndex = 0;
   for(i = 0; i < oldSize; i++)
      if(hashtable->theArray[i] != NULL)
         CurNodeIsNULL(curNode, temp, hashtable, i);
}
void LoadFactorExceedsLimit(HashTable *hashtable, HashNode *curNode)
{
   int oldSize, nSize;
   HashNode **temp;
   oldSize = hashtable->Sizes[hashtable->curSizeIndex];
   hashtable->curSizeIndex+=1;
   nSize = hashtable->Sizes[hashtable->curSizeIndex];

   temp = (HashNode **)calloc(nSize, sizeof(HashNode *));
   hashtable->curSize = nSize;

   reSizeArray(curNode, temp, hashtable, oldSize);

   hashtable->theArray = temp;
   freeArray(hashtable->theArray);
}

void checkLoadFactor(void *hashTable, void *data1, HashNode *curNode)
{
   int index;
   HashTable *hashtable;
   float loadFactor;

   hashtable = (HashTable *)hashTable;

   loadFactor = (float )hashtable->numElements / (float )hashtable->curSize;
   index = hashtable->curSizeIndex;

   /* if the load factor exceeds the limits and index does not = to numSizes */
   if(loadFactor > hashtable->reHashLoadFactor && index !=hashtable->NumSizes){
      LoadFactorExceedsLimit(hashtable, curNode);
   }

}

void checkForDuplicate(HashNode *curNode, HashNode *new_node, int *addedFlag,
   int *freq)
{
   printf("freq before %d\n", curNode->entry.frequency);
   curNode->entry.frequency += 1;
   *addedFlag = 1;
   printf("freq after %d\n", curNode->entry.frequency);
   *freq = curNode->entry.frequency;
   free(new_node);
}
unsigned IfHashNotEmpty(HashNode *curNode, HashTable *hashtable,
   HashNode *new_node, void *data)
{
   int freq;
   int addedFlag = 0;
   while (curNode->next != NULL)
   {
      if (hashtable->htFunctions->compare(curNode->entry.data,
         new_node->entry.data) == 0) {
         checkForDuplicate(curNode, new_node, &addedFlag, &freq);
         break;
      }
      else
         curNode = curNode->next;
   }

   if(addedFlag == 0) { /* could put into function */
      curNode->next = new_node;
      new_node->entry.frequency = 1;
      hashtable->uniqueEntries+= 1;
      hashtable->numElements+= 1;
      freq = new_node->entry.frequency = 1;
   }

   return freq;
}

unsigned checkNodeIsNULL(HashTable *hashtable, HashNode *curNode, unsigned
   hashIndex, HashNode *new_node)
{

   //curNode = new_node; /* check with this */
   // hashtable->theArray[hashIndex] = new_node;
   new_node->entry.frequency += 1;
   hashtable->uniqueEntries+= 1;
   hashtable->numElements+= 1;
   curNode = new_node;  /*check with this */

   return curNode->entry.frequency;  /* new_node was here */
}
unsigned htAdd(void *hashTable, void *data)
{
   int hashIndex;
   int frequency;
   unsigned hash;
   HashNode *new_node;
   HashTable *hashtable;
   HashNode *curNode;
   emptyHTError(hashTable);

   frequency = 0; /*always going to give me zero */
   assert(data != NULL);
   hashtable = (HashTable*)hashTable;

   hash = hashtable->htFunctions->hash(data);
   hashIndex = hash % htCapacity(hashtable);

   curNode = hashtable->theArray[hashIndex];


   new_node = (HashNode*)malloc(sizeof(HashNode));

   if(new_node == NULL)
   {
      perror("attempting to malloc");
      exit(EXIT_FAILURE);
   }


   new_node-> next = NULL;
   new_node->entry.data = data;
   new_node->entry.frequency = 0;

   hashtable->totalEntries+= 1;
   checkLoadFactor(hashTable, data, curNode);
   if(curNode == NULL)
      frequency = checkNodeIsNULL(hashtable, curNode, hashIndex,
         new_node);
   else
      frequency = IfHashNotEmpty(curNode, hashtable, new_node,
         data);

   checkLoadFactor(hashTable, data, curNode);
   return  frequency;
}

HTEntry checkInChain(HashTable *hashtable, void *data, HashNode *curNode)
{
   /* if it isn't NULL then sees checks the Array for it the name is a misnom */
   HTEntry entry;
   while(curNode->next != NULL)
   {
      if(hashtable->htFunctions->compare(curNode->entry.data, data) == 0)
      {
         entry.frequency = curNode->entry.frequency;
         entry.data = curNode->entry.data;
         break;
      }
      else
         curNode = curNode ->next;

   }
   return entry;
}

HTEntry htLookUp(void *hashTable, void *data)
{
   /* Lookups if data is in hashTable if not then return a freq of 0 */
   HTEntry entry;
   unsigned hashIndex,hash;
   HashTable *hashtable;
   HashNode *curNode;
   assert(data != NULL);
   hashtable = (HashTable *)hashTable;
   hash = hashtable->htFunctions->hash(data);
   hashIndex = hash % htCapacity(hashTable);
   /* printf("hash index %d: ", hashIndex); */
   curNode = hashtable->theArray[hashIndex];

   if(curNode == NULL)
   {
      entry.frequency = 0;
      entry.data = NULL;
   }
   else
      entry = checkInChain(hashtable, data, curNode);

   return entry;
}

HTEntry* htToArray(void *hashTable, unsigned *size)
{
   HTEntry* entries;
   int i;

   HashTable *hashTable1;
   HashNode *curNode; /* curNode is a local variable */
   *size = htUniqueEntries(hashTable);
   /* free this array as well ? */
   entries = (HTEntry *)calloc(*size, sizeof(HTEntry));

   hashTable1 = (HashTable *)hashTable;

   i = 0;
   while (hashTable1->theArray[i] != NULL)
   {

      entries[i] = hashTable1->theArray[i]->entry;
      curNode = hashTable1->theArray[i];

      while (curNode->next != NULL) /*keeps track of chains */
      {
         curNode = curNode->next;
         i++;
         entries[i] = curNode->entry;
      }
      i++;
   }

   return entries;

}

unsigned htCapacity(void *hashTable)
{
   HashTable *hashTable1 = (HashTable *)hashTable;
   return hashTable1->curSize;
}

unsigned htUniqueEntries(void *hashTable)
{
   HashTable *hashT;
   hashT = (HashTable *)hashTable;
   return hashT->uniqueEntries;

}

unsigned htTotalEntries(void *hashTable)
{
   HashTable *hashT;
   hashT = (HashTable *)hashTable;
   return hashT->totalEntries;
}

/*
float getAverageChainLength(HashTable *hashTable)
{
   float avg;
   avg = hashTable->metrics.avgChainLength/ hashTable->metrics.numberOfChains;
   return avg;
}
*/

/*   records metrics for Hashtable
 *    hashtable->metrics.avgChainLength+= *chainLength;
 *    if(hashtable->metrics.maxChainLength < *chainLength)
 *  hashtable->metrics.maxChainLength = *chainLength;
 */

/* Use function CHECKNODE is NULL to help with metrics
 */

/* chainLength =  (unsigned *)malloc(sizeof(unsigned));
 * chainLength = 0;
 */

HTMetrics htMetrics(void *hashTable)
{

   HashTable *hashT;
   HTMetrics metrics;
   hashT = (HashTable *)hashTable;

   return metrics;
}

