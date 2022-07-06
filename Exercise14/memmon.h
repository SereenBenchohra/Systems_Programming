/*
 * Memory Monitor
 *
 * Intended for use Kurt Mammen's CPE 357 Systems Programming course at
 * Cal Poly. If you use it anywhere please attribute authorship appropriately!
 * 
 * !!! DO NOT MODIFY !!!
 *
 * To use Memory Monitor:
 *
 *    1. Both memmon.h and memmon.c MUST be in your source directory.
 *    2. You MUST #include "memmon.h" in ALL source file where you are
 *       calling any of the Standard Library functions malloc, calloc,
 *       realloc, and free.
 *    3. You MUST #include <stdlib.h> BEFORE "memmon.h".
 */
#ifndef MEMMON_H
#define MEMMON_H

/* Slightly different guards on Macs and the CSL servers */
#if defined _STDLIB_H_ || defined _STDLIB_H

#ifdef NOMEMMON
   #define memAllocs() -1
   #define memCallocs() -1
   #define memMallocs() -1
   #define memReallocs() -1
   #define memFrees() -1
   #define memPeak() -1
   #define memCurrent() -1 
   #define memSetOutOfMemory(FLAG) 
#else
   #define free(PTR)           memFree((PTR))
   #define malloc(BYTES)       memMalloc((BYTES), __FILE__, __LINE__)
   #define calloc(COUNT,SIZE)  memCalloc((COUNT), (SIZE), __FILE__, __LINE__)
   #define realloc(PTR, BYTES) memRealloc((PTR), (BYTES), __FILE__, __LINE__)

   /* Don't call these directly - they get called by the macros above */
   void memFree(void *ptr);
   void* memMalloc(size_t bytes, const char *fname, int line);
   void* memCalloc(size_t count, size_t size, const char *fname, int line);
   void* memRealloc(void *ptr, size_t bytes, const char *fname, int line);

   /* You can call these if you want to see information about your memory use */
   int memAllocs();         /* signed so -1 shows up when not NOMEMMON */
   int memCallocs();        /* signed so -1 shows up when not NOMEMMON */
   int memMallocs();        /* signed so -1 shows up when not NOMEMMON */
   int memReallocs();       /* signed so -1 shows up when not NOMEMMON */
   int memFrees();          /* signed so -1 shows up when not NOMEMMON */
   unsigned memPeak();      /* Not size_t to be 32-64 bit compatible */
   unsigned memCurrent();   /* Not size_t to be 32-64 bit compatible */
   void memSetOutOfMemory(int flag); 
#endif
#endif
#endif
