/*implement qsort that returns a sorted array */

#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include <string.h>
#include "qsort.h"

int comparator(const void *node1p, const void *node2p){

    Node *node1, *node2;

    node1 = *(Node **)node1p;
    node2 = *(Node **)node2p;   

    if(node1->freq == node2->freq){
        return strcmp(node2->word, node1->word);
    }
    return (node2->freq - node1->freq);
}

