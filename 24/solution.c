#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define UPPER_LIMIT 10 
#define TARGET 1000000

char** anagram(char* s);
char** anagram_r(char* s, char** buffer, int offset, int size, int length, int *count);
int factorial(int x);
void string_printArray(char** s);
char* string_new(const char* s);
int cmpfunc(const void *a, const void *b);
int main() {
   char* buffer = calloc(UPPER_LIMIT+1,sizeof(char));
   char i;
   for(i = 0; i < UPPER_LIMIT; i++) {
      buffer[(int)i] = '0' + i;
   }
   char** result = anagram(buffer);
   qsort(result, factorial(UPPER_LIMIT),sizeof(char*),cmpfunc);
   printf("Solution : %s\n",result[TARGET-1]);
   return EXIT_SUCCESS;
}

int factorial(int x) {
   if(x==1) return 1;
   return x*factorial(x-1);
}
char** anagram(char* s) {
  int length = strlen(s);
  int size = factorial(length);
  char **retVal = calloc(size + 1,sizeof(char**));
  int count = 0;
  anagram_r(s, retVal, 0, size,length, &count);
  return retVal; 
} 

char* string_new(const char* s) {
    char* retVal = calloc(strlen(s) + 1,sizeof(char));
    strcpy(retVal,s);
    return retVal; 
}

void string_printArray(char** s) {
   while(*s!=0) {
      printf("%s\n",*s);
      s++;
   }
}


char** anagram_r(char* s, char** buffer, int offset, int size,int length,int *count) {
   if(offset >= length - 1)  {
      buffer[*count] = string_new(s);
      *count=*count+1;
   } else {
      int i;
      char tmp;
      for(i = offset; i < length; i++) {
        tmp = s[offset];
        s[offset] = s[i]; 
        s[i] = tmp;
        anagram_r(s,buffer,offset +1, size, length, count);
        s[i] = s[offset];
        s[offset] = tmp;
      }
   }
   return buffer;
}


int cmpfunc(const void *a, const void*b) {
   return strcmp(*(const char**)a,*(const char**)b);
   return  *(char*)a - *(char*)b;
}
