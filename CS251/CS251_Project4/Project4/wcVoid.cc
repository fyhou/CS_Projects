/**
 * CS 251 - Project 4 - HashTableVoid
 * Program that prints the occurrences of the words of a file.
 * 
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date April 3, 2011
 *
 * @compile with make
 * @execute with make test
 */

#include <stdio.h>
#include "HashTableVoid.h"

#define MAXWORD 1024

struct WordCount {
  const char * word;
  int count;
};


void usage() {
  fprintf(stderr, "Usage: wcVoid file\n");
}


int main(int argc, char **argv) {
  if (argc <2) {
    usage();
    exit(1);
  }
  
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s\n", argv[1]);
    perror("fopen");
    exit(1);
  }

  HashTableVoid table;

  int ch;
  char word[MAXWORD];
  int count = 0;
  printf("Reading file %s...\n\n", argv[1]);
  printf("WORDS\n", argv[1]);
  printf("-----------------------\n", argv[1]);
  while (1) {

    // Keep reading to skip spaces
    ch = fgetc(f);    
    while (ch > 0 && (ch==' '|| ch=='\t' || ch== '\n')) {
      // Skip spaces
      ch = fgetc(f);
    }

    if (ch <=0) {
      break;
    }
    
    // Found a word. Keep reading to parse word
    int i = 0;
    while (ch > 0 && ch!=' '&& ch!='\t' && ch!= '\n') {
      word[i]=ch;
      i++;
      ch = fgetc(f);
    }

    // print word
    word[i]=0;
    printf("%d:%s\n", count, word);

    // Add word to table
    WordCount * wc;

    //
    // ADD YOUR CODE HERE TO LOOKUP THE WORD AND INCREMENT THE COUNT
    // OR TO ADD A NEW WordCountRecord IF THE WORD DOES NOT EXIST
    //
    void* vCount;
    const char * newWord = strdup(word);
    
    if (!table.find (newWord, &vCount) ) {
    	table.insertItem (newWord, (void*)1);
    }
    else {
    	int tempCount = (int)vCount;
    	table.insertItem(newWord, (void *)(++tempCount));
    }
    
    count++;
  }

  printf("\nHISTOGRAM\n", argv[1]);
  printf("-----------------------\n", argv[1]);
  WordCount * wc;

  //
  // ADD YOUR CODE HERE TO ITERATE OVER THE HASH TABLE AND
  // PRINT THE COUNT FOR EVERY WORD. USE THE FORMAT
  //
  // printf("%-20s %d\n", wc->word, wc->count);
  //
  HashTableVoidIterator iterator (&table);
  const char * tWord;
  void *tempCount;
  while (iterator.next(tWord, tempCount)) {
  	printf("%-20s %d\n", tWord, (int)(tempCount));
  }
  fclose(f);
}
