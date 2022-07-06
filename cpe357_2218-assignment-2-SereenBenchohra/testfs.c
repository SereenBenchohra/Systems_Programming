#include "checkit.h"
#include "InodeHandle.h"

#define PATH "/home/sbenchoh/KeenCPE357/cpe357_2218-assignment-2-SereenBenchohra/fs_emulator.c"
#define PATH2 "/home/sbenchoh/KeenCPE357/cpe357_2218-assignment-2-SereenBenchohra/fs"

void test_integer() // test an outwrite string to see if error raised
{
   char *testNum;
   int num;
   testNum = "Hello";
   num = is_integer(testNum);
   
}
// test if regular number string is converted 
void test_integer1() 
{
   char *testNum;
   int num;
   testNum = "4567";
   num = is_integer(testNum);
   checkit_int(num, 4567);

}
// test if decimal is passed in 
void test_integer2() 
{
   char *testNum;
   int num;
   testNum = "45.67";
   num = is_integer(testNum);
   checkit_int(num, 45);

}

void test_File()
{
   isFile(PATH);

}

void test_File1()
{
   isFile(PATH2);

}

void test_print_Inodes()
{
   for(i = 0; i < ARRAYSIZE; i++ ) // verifies inode works (succesful)
   {
      printf("%c\n", inode_fs[i]);
   }
}



int main()
{
   test_integer1();
   test_integer2();
   // test_integer();
   test_File1();
   test_File();
   return 0;
}