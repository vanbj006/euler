#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAYS_PER_WEEK 7
#define MONTHS_PER_YEAR 12
#define SUNDAY 0
#define MONDAY 1 
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6



struct Date {
   int Year;
   int Month;
   int Day;
   int DayOfWeek;
};

struct Date* date_new();
void date_print(struct Date *date);
int date_daysInMonth(struct Date *date);
char date_isLeap(struct Date *date);
char* string_new(const char* s);
char* date_dayOfWeek(struct Date *date);
struct Date* date_addMonth(struct Date* date);
int main() {
   struct Date *date = date_new();
   
   //Date is initialized to 1900/01/01,
   //so move forward 1 year to 1901/01/01
   int i;
   for(i = 0; i < MONTHS_PER_YEAR; i++) {
     //date_print(date);
     date_addMonth(date);
   }
   //Count 1st sundays until the end of 2000
   int count = 0;
   while(date->Year <= 2000) {
      if(date->DayOfWeek == SUNDAY) {
        //date_print(date);
        count++;
      }
      date_addMonth(date);
   }
   printf("Solution : %d\n",count);
   return EXIT_SUCCESS;
}


int date_daysInMonth(struct Date *date) {
    switch(date->Month) {
       case 1:  //Jan
       case 3:  //March
       case 5:  //May
       case 7:  //July
       case 8:  //August
       case 10: //October
       case 12: //December
           return 31;
       case 2: return date_isLeap(date) ? 29 : 28;
       case 4: //April
       case 6: //June 
       case 9: //September
       case 11: //November
          return 30;
    }
    return 0;
}
struct Date *date_new() {
   struct Date *retVal = malloc(sizeof(struct Date));
   retVal->Year = 1900;
   retVal->Month = 1;
   retVal->Day = 1;
   retVal->DayOfWeek = 1;
   return retVal;
}


void date_print(struct Date *date) {
   printf("%s %02d-%02d-%4d\n",date_dayOfWeek(date),date->Day,date->Month,date->Year);
}


char date_isLeap(struct Date *date) {
   if(date->Year % 100 == 0) {
      if(date->Year % 400 == 0 ) return 1;
   } else if(date->Year % 4 == 0) return 1;
   return 0;
}

char* date_dayOfWeek(struct Date *date) {
    switch(date->DayOfWeek) {
       case SUNDAY: return string_new("SUNDAY");
       case MONDAY: return string_new("MONDAY");
       case TUESDAY: return string_new("TUESDAY");
       case WEDNESDAY: return string_new("WEDNESDAY");
       case THURSDAY: return string_new("THURSDAY");
       case FRIDAY: return string_new("FRIDAY");
       case SATURDAY: return string_new("SATURDAY");
    }
    return string_new("");
}




char* string_new(const char* s) {
    size_t size = strlen(s);
    char* retVal = calloc(size + 1, sizeof(char));
    if(retVal == NULL) { printf("ERROR: Out of memeory!\n"); exit(1); }
    strncpy(retVal,s,size);
    return retVal;
}

char* string_cat(const char* s1, const char* s2) {
    size_t size = strlen(s1) + strlen(s2);
    char* retVal = calloc(size + 1, sizeof(char));
    if(retVal == NULL) { printf("ERROR: Out of memeory!\n"); exit(1); }
    strncpy(retVal,s1,size);
    strncat(retVal,s2,size - strlen(retVal));
    return retVal;
}

struct Date* date_addMonth(struct Date* date) {
    int daysInMonth = date_daysInMonth(date);
    //printf("Days In Month %d %d : %d\n",date->Month,date->Year,daysInMonth);
    if( date->Month == MONTHS_PER_YEAR ) {
        date->Year++;
        date->Month = 1;
    } else {
        date->Month++;
    }
    date->DayOfWeek = (date->DayOfWeek + daysInMonth) % DAYS_PER_WEEK; 
    return date;
}
