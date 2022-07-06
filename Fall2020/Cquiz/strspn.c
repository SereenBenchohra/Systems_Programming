#include <stdio.h>

size_t strspn(const char*s, const char *accepted){

   int numAccepted;
   numAccepted = 0;  /*start with 0 characters accepted */
   int i, j;
   i = 0;
   while(accepted[i] != '\0' ) { 

       for(j = 0; s[j] != '\0'; j ++) {
         if(s[j] == accepted[i]){
            numAccepted++;
            i++;
         }

       }
       i++;
   }


   return numAccepted;
}

int main()
{
   const char *s = "ASDHDJSKLJ";
   const char *accepted = "1";
   size_t numAcc;
   numAcc = strspn(s, accepted);
   printf("%zu", numAcc);

   return 0;

}
