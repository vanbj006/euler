#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "p022_names.txt"
#define FOR_READING "r"
#define CHAR_BUFFER_SIZE 20 
#define HEAP_SIZE 6000 

struct Heap {
   int size;
   int count;
   char** data;
};

struct Heap *heap_new(int size);
int heap_leftIndex(int index);
int heap_rightIndex(int index);
int heap_parentIndex(int index);
int heap_minChildIndex(int index, struct Heap *heap);
int heap_add(char* x, struct Heap *heap);
char* heap_remove(struct Heap *heap);
void heap_swap(int x, int y, struct Heap *heap);
int heap_compare(int x, int y, struct Heap *heap);
void heap_print(struct Heap *heap);
int heap_dataCompare(char *x, char* y);
void ReadFile(struct Heap *heap);

ulong calcScore(char *s, int index) {
  ulong retVal = 0;
  while(*s != 0) {
     retVal += *s - 'A' + 1;
     s++;
  }
  return index * retVal;
}

int main() {
  struct Heap *names;
  names = heap_new(HEAP_SIZE);
  ReadFile(names);
  ulong total = 0;
  int i = 1;
  while(names->count > 0) {
     char* s = heap_remove(names);
     ulong score = calcScore(s,i);
     total+= score;
  }

  printf("Total : %u\n",total);
  return 0;
}


void heap_print(struct Heap *heap) {
  printf("size : %d\n",heap->size);
  printf("count : %d\n",heap->count);
  printf("data : ");
  int i; for (i = 0; i < heap->size; i++) printf("%s ",heap->data[i]);
  printf("\n"); 
}
struct Heap *heap_new(int size) {
   struct Heap *retVal = malloc(sizeof(struct Heap));
   retVal->count = 0;
   retVal->size = size;
   retVal->data = malloc(sizeof(char*) * size);
   return retVal;
}


int heap_add(char* x, struct Heap *heap) {
   if(heap->size <= heap->count) return -1; //Heap is full
   if(*x == 0) return -2; //Empty String
   int index, parentIndex;
   index = heap->count++;
   heap->data[index] = x;
   parentIndex = heap_parentIndex(index);
   
   while((index > 0) && (heap_compare(parentIndex,index,heap))) {
      heap_swap(parentIndex,index,heap);
      index = parentIndex;
      parentIndex = heap_parentIndex(index);
   }
   return index;
   
}

int heap_leftIndex(int index) {
  return (2 * index) + 1;
}

int heap_rightIndex(int index) {
  return (2 * index) + 2;
}

int heap_parentIndex(int index) {
  if( (index % 2) == 0 ) index-=2;
  return index/2;
}

void heap_swap(int x, int y, struct Heap *heap) {
   char* tmp = heap->data[x];
   heap->data[x] = heap->data[y];
   heap->data[y] = tmp;
   return;
}

int heap_compare(int x, int y, struct Heap *heap) {
 //if y is the parent, swap them. 
 if( x > y ) {
     int tmp = x;
     x = y;
     y = tmp;   
 }
 
 return heap_dataCompare(heap->data[x], heap->data[y]);

}

void ReadFile(struct Heap *heap) {
  FILE *fr; 
  fr = fopen(FILE_NAME, FOR_READING);
  if(fr == NULL) { printf("ERROR opening file FILE_NAME\n"); exit(1); }
  char *buffer, *ref;
  int error = 0;
  
  while(error >= 0) {
     buffer = calloc(CHAR_BUFFER_SIZE, sizeof(char));
     if(buffer == NULL) { printf("ERROR: Out of memory\n"); exit(1); }
     ref = buffer;
     *ref = (char)getc(fr); 
     while((*ref != ',') && (*ref != EOF))  { 
        if(((*ref >= 'A') && (*ref <='Z')) ||
	    (*ref == ',')) ref++;
        *ref = getc(fr);
     }
     *ref = 0;
     error = heap_add(buffer, heap);
        
  }
  /*int nameCount = 1;
  int nameMaxLength = 0;
  int i = 0;
  FILE *fr;
  fr = fopen(FILE_NAME, FOR_READING);
  char buffer;
  buffer = getc(fr);
  if( fr != NULL ) {
     while(buffer != EOF) {
        if(buffer == ',') {
	    nameCount++;
            if( i > nameMaxLength) nameMaxLength = i;
            i = 0;
            printf("\n");
        }
        if( ( ( buffer >= 'A' ) && ( buffer <= 'Z' ) ) ||
            ( ( buffer >= 'a' ) && ( buffer <= 'z' ) ) ) {
            i++;
            printf("%c",buffer);
        }
        buffer = getc(fr);

  }
  fclose(fr);  
  printf("\nnameCount : %d\nnameMaxLength : %d\n", nameCount, nameMaxLength);
  
  } else {
    printf("Error : Unable to open FILE %s\n",FILE_NAME);
    exit(1);
  } */
  return;
} 


char* heap_remove(struct Heap *heap) {
  char* retVal = heap->data[0];
  int childIndex = 0;
  int index = 0;
  heap->data[index] = heap->data[--heap->count];
  childIndex = heap_minChildIndex(index,heap);
  while(heap_compare(index,childIndex,heap)) {
     heap_swap(index,childIndex,heap);
     index = childIndex;
     childIndex = heap_minChildIndex(index,heap);
  }
  
  return retVal; 
}

int heap_minChildIndex(int index, struct Heap *heap) {
  int left, right;
  left = heap_leftIndex(index);
  right = heap_rightIndex(index);

  if(left >= heap->count) return index;
  if(right >= heap->count) return index;

  if(heap_dataCompare(heap->data[left],heap->data[right])) return right;
  return left;
}


int heap_dataCompare(char* x, char* y) {
  int i;
  while( *x != 0 ) {
    if( *x == *y ) { x++; y++; }
    else if ( *x > *y ) return 1;
    else return 0; 
  }   
  return 0;
}
