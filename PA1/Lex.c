// Rukmini Bose 
// rubose 
// PA1

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

#define MAX_LEN 161
#define MAX_LINES 5000

int strcmp(const char* str1, const char* str2);
char* strcpy(char * dst, const char * src);
unsigned long strlen(const char* str);

void insert(List L, int data, char** lines) {
    moveFront(L);
    while (index(L) != -1) {
        if (strcmp(lines[data], lines[get(L)]) <= 0) {
            insertBefore(L, data);
            return;
        }
        moveNext(L);
    }
    append(L, data);
}

int main(int argc, char* argv[]) {

   if (argc != 3) {
      fprintf(stderr, "Usage: Lex <input file> <output file>\n");
      exit(1);
   }

   FILE* in, *out;
   int n = 0; // number of lines in input file
   char line[MAX_LEN]; // buffer storing current line of input file

   // Open input and output files
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if (in == NULL) {
      fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if (out == NULL) {
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // Preallocate blank array to hold all strings
   char** arr = malloc(sizeof(char*) * MAX_LINES);
   
   // Create empty List
   List list = newList();

   // Read in each line, add it to arr, and insert each index correctly in list
   while (fgets(line, MAX_LEN, in) != NULL) {
      arr[n] = calloc(strlen(line) + 1, sizeof(char));
      strcpy(arr[n], line);
      insert(list, n, arr); // see the insert implementation in beginning of file
      n++;
   }

   // Iterate through list, and write each line to out
   moveFront(list);
   for ( ; index(list) >= 0 ; moveNext(list)) {
      fputs(arr[get(list)], out);
   }

   // Free list when finished
   freeList(&list);

   // Free arr when finished
   for (int i = 0; i < n; i++) {
      free(arr[i]);
   }
   free(arr);
   
   // Close files
   fclose(in);
   fclose(out);
}
