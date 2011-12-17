
#include <stdio.h>
#include "HashTableTemplate.h"


struct Student {
  const char * name;
  int grade;
};


Student students[] = {
  {"Rachael", 8},
  {"Monica", 9},
  {"Phoebe", 10},
  {"Joey", 6},
  {"Ross", 8},
  {"Chandler", 7}
};


struct Vars {
  const char * varName;
  const char * value;
};


Vars vars[] = {
  {"a", "abcd"},
  {"b", "efgh"},
  {"c", "defg"}
};


void test1() {
  HashTableTemplate<int> h;

  bool e;
  e = h.insertItem("Rachael", 8);
  assert(!e);
  
  e = h.insertItem("Monica", 9);
  assert(!e);
  
  e = h.insertItem("Monica", 10);
  assert(e);

  printf("Test1 passed\n");
}


void test2() {
  HashTableTemplate<int> h;

  bool e;
  e = h.insertItem("Rachael", 8);
  assert(!e);
  
  e = h.insertItem("Monica", 9);
  assert(!e);
  
  e = h.insertItem("Monica", 10);
  assert(e);

  int grade;
  e = h.find("Rachael", &grade);
  assert(e);
  assert(grade==8);

  e = h.find("Monica", &grade);
  assert(e);
  assert(grade==10);

  printf("Test2 passed\n");
}


void test3() {
  HashTableTemplate<int> h;

  for (int i=0; i < sizeof(students)/sizeof(Student); i++) {
    bool e = h.insertItem(students[i].name, students[i].grade);
    assert(!e);
  }

  for (int i=0; i<sizeof(students)/sizeof(Student);i++) {
    int grade;
    bool e = h.find(students[i].name, &grade);
    assert(e);
    assert(grade==students[i].grade);
  }

  int grade;
  bool e = h.find("John", &grade);
  assert(!e);

  e = h.removeElement("John");
  assert(!e);

  e = h.removeElement("Rachael");
  assert(e);

  e = h.find("Rachael", &grade);
  assert(!e);

  printf("Test3 passed\n");
}


void test4() {
  HashTableTemplate<int> h;

  bool e = h.insertItem("Rachael", 8);
  assert(!e);
  
  e = h.insertItem("Monica", 9);
  assert(!e);
  
  e = h.insertItem("Monica", 10);
  assert(e);

  HashTableTemplateIterator<int> iterator(&h);

  int sum = 0;
  const char * key;
  int grade;
  while (iterator.next(key, grade)) {
    sum += grade;
    //printf("%s %d\n", key, grade);
  }

  assert(sum==18);

  printf("Test4 passed\n");
}


void test5() {
  HashTableTemplate<int> h;

  int sum = 0;
  for (int i = 0; i < sizeof(students)/sizeof(Student); i++) {
    bool e = h.insertItem(students[i].name, students[i].grade);
    assert(!e);
    sum += students[i].grade;
  }

  HashTableTemplateIterator<int> iterator(&h);

  int sum2 = 0;
  const char * key;
  int grade;
  while (iterator.next(key, grade)) {
    sum2+=grade;
    //printf("%s %d\n", key, grade);
  }

  assert(sum2 == sum);
  printf("Test5 passed\n");
}


void test6() {
  HashTableTemplate<const char *> h;

  for (int i = 0; i < sizeof(vars)/sizeof(Vars); i++) {
    bool e = h.insertItem(vars[i].varName, vars[i].value);
    assert(!e);
  }

  for (int i = 0; i < sizeof(vars)/sizeof(Vars); i++) {
    const char * value;
    bool e = h.find(vars[i].varName, &value);
    assert(e);
    assert(!strcmp(value, vars[i].value));
  }

  const char *value;
  bool e = h.find("John", &value);
  assert(!e);

  e = h.removeElement("John");
  assert(!e);

  e = h.removeElement("a");
  assert(e);

  e = h.find("a", &value);
  assert(!e);

  printf("Test6 passed\n");
}


void usage() {
  // Print usage
  fprintf(stderr, "HashTableTemplateTest test1|test2|test3|test4|test5|test6\n");
}


int main(int argc, char **argv) {
  if (argc == 1) {
    usage();
    exit(1);
  }

  if (!strcmp(argv[1], "test1")) {
    test1();
  } else if (!strcmp(argv[1], "test2")) {
    test2();
  } else if (!strcmp(argv[1], "test3")) {
    test3();
  } else if (!strcmp(argv[1], "test4")) {
    test4();
  } else if (!strcmp(argv[1], "test5")) {
    test5();
  } else if (!strcmp(argv[1], "test6")) {
    test6();
  } else {
    usage();
    exit(1);
  }

  exit(0);
}
