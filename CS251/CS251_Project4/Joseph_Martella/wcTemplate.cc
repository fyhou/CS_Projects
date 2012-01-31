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
#include "HashTableTemplate.h"

#define MAXWORD 1024

struct WordCount {
  const char * word;
  int count;
};

/*
 * prints out correct usage of program 
 */
void correctUsage() {
  fprintf(stderr, "Usage: wcTemplate file\n");
}


int main(int argc, char **argv) {
  // if not enough arguments are passed
  if (argc < 2) {
    correctUsage();
    exit(1);
  }
  
  // attempts to open file
  FILE * f = fopen(argv[1], "r");
  // if file doesn't exist, error is outputted 
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s\n", argv[1]);
    perror("fopen");
    exit(1);
  }

  // make a hash table of ints
  HashTableTemplate<int> intTable;

  int c;
  char word[MAXWORD];
  int count = 0;
  printf("Reading file %s...\n\n", argv[1]);
  printf("WORDS\n", argv[1]);
  printf("-----------------------\n", argv[1]);
  while (1) {
    // skips over white space
    c = fgetc(f);    
    while (c > 0 && (c ==' '|| c =='\t' || c == '\n')) {
      // Skip spaces
      c = fgetc(f);
    }

    if (c <= 0) {
      break;
    }
    
    // we encountered a word; read until word ends
    int i = 0;
    while (c > 0 && (c !=' ' && c != '\t' && c != '\n')) {
      word[i++] = c;
      c = fgetc(f);
    }

    // print word
    word[i] = 0;
    printf("%d:%s\n", count, word);

    // add word to table
    WordCount * wc;

    //
    // ADD YOUR CODE HERE TO LOOKUP THE WORD AND INCREMENT THE COUNT
    // OR TO ADD A NEW WordCountRecord IF THE WORD DOES NOT EXIST
    //
    int vCount;
    
    if (!intTable.find (word, &vCount)) {
    	intTable.insertItem(word,1);
    }
    else {
    	int tempCount = vCount;
    	intTable.insertItem(word, (++tempCount));
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
  HashTableTemplateIterator<int> iterator (&intTable);
  const char * tWord;
  int tempCount;
  
  while (iterator.next (tWord, tempCount)) {
  	printf("%-20s %d\n", tWord, (int)(tempCount));
  }
  
  fclose(f);
}
