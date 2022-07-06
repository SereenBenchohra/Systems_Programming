#include <limits.h>
#include "hashTable.h"

void* htCreate(
   HTFunctions *functions,
   unsigned sizes[],
   int numSizes,
   float rehashLoadFactor)
{
   /* Excellent, an always wrong result! */
   return NULL;
}

void htDestroy(void *hashTable)
{
   /* A void function, can't return a wrong answer but can do nothing! */
}

unsigned htAdd(void *hashTable, void *data)
{
   /* Excellent, an always wrong result! */
   return 0;
}

HTEntry htLookUp(void *hashTable, void *data)
{
   HTEntry entry;

   /* A decent "wrong" answer - combination should never happen! */
   entry.data = "This is a test";
   entry.frequency = 0;
   
   return entry;
}

HTEntry* htToArray(void *hashTable, unsigned *size)
{
   /* All values possible but UINT_MAX is unlikely and recognizable! */
   *size = UINT_MAX;

   /* NULL is a possible correct result, but only when size is zero */
   return NULL;
}

unsigned htCapacity(void *hashTable)
{
   /* Always incorrect - htCreate does does not allow a size of zero. */
   return 0;
}

unsigned htUniqueEntries(void *hashTable)
{
   /* All values possible but UNIT_MAX is unlikely and recognizable! */
   return UINT_MAX;
}

unsigned htTotalEntries(void *hashTable)
{
   /* All values possible but UNIT_MAX is unlikely and recognizable! */
   return UINT_MAX;
}

HTMetrics htMetrics(void *hashTable)
{
   HTMetrics metrics;

   /* All values possible but UNIT_MAX is unlikely and recognizable! */
   metrics.numberOfChains = UINT_MAX;
   
   /* All values possible but UNIT_MAX is unlikely and recognizable! */
   metrics.maxChainLength = UINT_MAX;

   /* Always incorrect, avgChainLength will always be zero or positive. */
   metrics.avgChainLength = -1.0;

   return metrics;
}
