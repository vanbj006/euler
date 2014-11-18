#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR_BUFFER_SIZE 100

char* intToText(int x,char *buffer, int len);
int letterCount(char* buffer, int len);

int main() {
    
  char* buffer;
  int i = 1;
  int total = 0;
  buffer = calloc(CHAR_BUFFER_SIZE, sizeof(char));
  for(i = 1; i <= 1000; i++) {
     buffer[0] = 0;
     intToText(i,buffer,CHAR_BUFFER_SIZE);
     total += letterCount(buffer,(CHAR_BUFFER_SIZE));
     printf("%5d - %s\n",letterCount(buffer,CHAR_BUFFER_SIZE),buffer);
  }
  free(buffer);
  printf("Solution : %d\n",total);
  return EXIT_SUCCESS; 
}

int letterCount(char* buffer, int len) {
   int i,count;
   i = 0;
   count = 0;
   while(( i < len) && (buffer[i] != 0)) {
      if((buffer[i] >= 'A') && (buffer[i] <= 'Z')) count++;
      i++;
   }
   return count;
}

char* intToText(int x,char *buffer, int len) {
    if(( x >= 1000 ) && ( x < 1000000 )) {
        intToText(x/1000,buffer,len);
        strncat(buffer," THOUSAND", len - strlen(buffer) - 1);
        int y = x % 1000;
        if(y > 0) {
           strncat(buffer," ", len - strlen(buffer) - 1);
           if(y < 100) {
              strncat(buffer,"AND ", len - strlen(buffer) - 1);
           }
           intToText(y,buffer,len);
	
        }
    }
    if((x >=100) && ( x < 1000)) {
             intToText(x/100,buffer,len);
             strncat(buffer," HUNDRED", len - strlen(buffer) - 1);
             if(x % 100 != 0) {
                strncat(buffer," AND ", len - strlen(buffer) - 1);
                intToText(x % 100,buffer,len);
             }
    } 
    if((x >=20) && (x <100)) {
          switch(x/10) {
             case 2 : strncat(buffer,"TWENTY", len - strlen(buffer) - 1);break; 
             case 3 : strncat(buffer,"THIRTY", len - strlen(buffer) - 1);break; 
             case 4 : strncat(buffer,"FORTY", len - strlen(buffer) - 1);break; 
             case 5 : strncat(buffer,"FIFTY", len - strlen(buffer) - 1);break; 
             case 6 : strncat(buffer,"SIXTY", len - strlen(buffer) - 1);break; 
             case 7 : strncat(buffer,"SEVENTY", len - strlen(buffer) - 1);break; 
             case 8 : strncat(buffer,"EIGHTY", len - strlen(buffer) - 1);break; 
             case 9 : strncat(buffer,"NINETY", len - strlen(buffer) - 1);break; 
          }
          intToText(x%10,buffer,len);
    }
    else if((x >0 ) && (x < 20)) {
        switch(x) {
           case 1 : strncat(buffer,"ONE",len - strlen(buffer) - 1);break;
	   case 2 : strncat(buffer,"TWO",len - strlen(buffer) - 1);break;
	   case 3 : strncat(buffer,"THREE",len - strlen(buffer) - 1);break;
	   case 4 : strncat(buffer, "FOUR",len - strlen(buffer) - 1);break;
           case 5 : strncat(buffer, "FIVE",len - strlen(buffer) - 1);break;
           case 6 : strncat(buffer, "SIX",len - strlen(buffer) - 1);break;
           case 7 : strncat(buffer, "SEVEN",len - strlen(buffer) - 1);break;
           case 8 : strncat(buffer, "EIGHT",len - strlen(buffer) - 1);break;
           case 9 : strncat(buffer, "NINE",len - strlen(buffer) - 1);break;
           case 10 : strncat(buffer, "TEN",len - strlen(buffer) - 1);break;
           case 11 : strncat(buffer, "ELEVEN",len - strlen(buffer) - 1);break;
           case 12 : strncat(buffer, "TWELVE",len - strlen(buffer) - 1);break;
           case 13 : strncat(buffer, "THIRTEEN",len - strlen(buffer) - 1);break;
           case 14 : strncat(buffer, "FOURTEEN",len - strlen(buffer) - 1);break;
           case 15 : strncat(buffer, "FIFTEEN",len - strlen(buffer) - 1);break;
           case 16 : strncat(buffer, "SIXTEEN",len - strlen(buffer) - 1);break;
           case 17 : strncat(buffer, "SEVENTEEN",len - strlen(buffer) - 1);break;
           case 18 : strncat(buffer, "EIGHTEEN",len - strlen(buffer) - 1);break;
           case 19 : strncat(buffer, "NINETEEN",len - strlen(buffer) - 1);break;
        }
    }
    return buffer;
}
