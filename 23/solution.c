#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UPPER_LIMIT 28123

//we found this experimentally
#define ABUNDANT_NUMBER_COUNT 6965


int isAbundant(int x);

int main() {

  int aNumbers[ABUNDANT_NUMBER_COUNT];
  int* sieve = calloc(UPPER_LIMIT + 1,sizeof(int));
  sieve[0] = 1;
  int i = 1;
  int count = 0;
  for(i = 1; i <= UPPER_LIMIT; i++) {
     if(isAbundant(i)) {
       aNumbers[count++] = i; 
     }
  }
  int j, sum, solution;
  for(i = 0; i < count; i++) {
     for(j = 0; j < count; j++) {
        sum = aNumbers[i] + aNumbers[j];
        if(sum <= UPPER_LIMIT) sieve[sum] = 1; 
     }
  }  
  solution = 0;
  for(i = 0; i <= UPPER_LIMIT; i++) {
     if(sieve[i] == 0) solution+=i; 
  }

  printf("Solution : %d",solution);
  return EXIT_SUCCESS;
}


int isAbundant(int x) {
    int sum = 1;
    int limit = (int)sqrt((double)x);
    int i;
    for(i = 2; i <= limit; i++) {
        if(x % i == 0) {
           sum += i;
           if(i * i != x) sum += x/i;
        }
       //printf("%d : %d\n",x,sum);
       if(sum > x) return 1;
    }
    return 0;
}
