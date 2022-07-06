#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct node {
   char  *word;
   int freq;
   struct node *next;

} Node;


typedef struct {

  /* probably make a constructor */
  unsigned arraySize;
  Node **HashArray;
  double loadFactor;
  int numEntries;

} HashTable;

HashTable *createHashTable(int arraySize);

unsigned hash( char *word, int arraySize);

Node* createNode(char *word);

void addData( char *word, HashTable *hashTable); /* attempts to add word */

void resizeInsertion(Node *node, HashTable *hashTable);

Node **linearArray(HashTable *hashTable);

void resizeArray(HashTable *hashTable);

#endif




