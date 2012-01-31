
#include <stdlib.h>
#include "linked_list.h"

void test1() {
	LINKED_LIST *ll;
	char * address;
	int result;

	ll = llist_create();

	llist_print(ll);

	printf("Add George\n");
	result = llist_add(ll, "George", "23 Oak St, West Lafayette, 47906");

	llist_print(ll);

	printf("Add Peter\n");
	result = llist_add(ll, "Peter", "27 Oak St, West Lafayette, 47906");

	llist_print(ll);

	//address = llist_lookup(ll, "Peter");
	//printf("Peter's address is: %s\n", address);

	//address = llist_lookup(ll, "George");
	//printf("George's address is: %s\n", address);
}

void test2() {
	LINKED_LIST *ll;
	char * address;
	int result;

	ll = llist_create();

	llist_print(ll);

	printf("Add George\n");
	result = llist_add(ll, "George", "23 Oak St, West Lafayette, 47906");

	llist_print(ll);

	printf("Add Peter\n");
	result = llist_add(ll, "Peter", "27 Oak St, West Lafayette, 47906");

	llist_print(ll);

	printf("Add George again\n");
	result = llist_add(ll, "George", "289 Pine St, West Lafayette, 47906");

	llist_print(ll);

	address = llist_lookup(ll, "Peter");
	printf("Peter's address is: %s\n", address);

	address = llist_lookup(ll, "George");
	printf("George's address is: %s\n", address);
}

void test3() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

}

void test4() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

	printf("remove name5\n");
	result = llist_remove(ll, "name5");
	printf("result1=%d\n", result);

	llist_print(ll);

	printf("remove name18\n");
	result = llist_remove(ll, "name18");
	printf("result2=%d\n", result);

	llist_print(ll);

	printf("remove name64\n");
	result = llist_remove(ll, "name64");
	printf("result3=%d\n", result);

	llist_print(ll);
}

void test5() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;
	char * name2, * value2;

	ll = llist_create();
	llist_print(ll);

	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

	// Get 11th value
	printf("Lookup 11th entry\n");
	result = llist_get_ith(ll, 11, &name2, &value2);
	printf("For 11th value name=%s value=%s\n", name2, value2);
	printf("result1=%d\n", result);

	// Get 23th value
	printf("Lookup 23th entry\n");
	result = llist_get_ith(ll, 23, &name2, &value2);
	printf("For 23th value name=%s value=%s\n", name2, value2);
	printf("result2=%d\n", result);

	// Get 64th value
	printf("Lookup 64th entry\n");
	result = llist_get_ith(ll, 64, &name2, &value2);
	printf("result3=%d\n", result);
}

void test6() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

	printf("remove name in position 5\n");
	result = llist_remove_ith(ll, 5);
	printf("result1=%d\n", result);

	llist_print(ll);

	printf("remove name in position 23\n");
	result = llist_remove_ith(ll, 23);
	printf("result2=%d\n", result);

	llist_print(ll);

	printf("remove name in position 67\n");
	result = llist_remove_ith(ll, 67);
	printf("result3=%d\n", result);

	llist_print(ll);
}


void test7() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

	printf("number in table: %d\n", llist_number_elements(ll));
}

void test8() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

	printf("Saving table /notallowed\n");
	result = llist_save(ll, "/notallowed");
	printf("result1=%d\n", result);

	printf("Saving table mytable1.ll\n");
	result = llist_save(ll, "mytable.ll");
	printf("result2=%d\n", result);

	printf("----- cat mytable.ll -----\n");
	system("cat mytable.ll");
}

void test9() {
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	printf("Read non existing table\n");
	result = llist_read(ll, "nonexsting.rt");
	printf("result1=%d\n", result);

	printf("Read friends.ll\n");
	result = llist_read(ll, "friends.rt");
	printf("result2=%d\n", result);

	llist_print(ll);
}

void test10() {
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	printf("Read friends.ll\n");
	result = llist_read(ll, "friends.rt");
	printf("result2=%d\n", result);

	llist_print(ll);

	printf("\nSort ascending\n");
	llist_sort(ll,1);
	llist_print(ll);

	printf("\nSort descending\n");
	llist_sort(ll,0);
	llist_print(ll);
}

void test11() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	result = llist_remove_first(ll);
	printf("llist_remove_first result=%d\n", result);

	result = llist_remove_last(ll);
	printf("llist_remove_last result=%d\n", result);
	
	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

	// Remove from one side or the other
	for (i=0; i < 10; i++) {
		result = llist_remove_first(ll);
		printf("llist_remove_first result=%d\n", result);
	}

	llist_print(ll);

	for (i=0; i < 10; i++) {
		result = llist_remove_last(ll);
		printf("llist_remove_last result=%d\n", result);
	}

	llist_print(ll);
	
}

void test12() {
	char name[20];
	char address[20];
	int i = 0;
	int result;
	LINKED_LIST *ll;

	ll = llist_create();
	llist_print(ll);

	for (i=0; i < 30; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_add(ll, name, address);
	}
	llist_print(ll);

	for (i=40; i < 50; i++) {
		printf("Adding first %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_insert_first(ll, name, address);
	}
	llist_print(ll);

	for (i=50; i < 60; i++) {
		printf("Adding %d\n", i);
		sprintf(name,"name%d", i);
		sprintf(address, "address%d", i);
		result = llist_insert_last(ll, name, address);
	}
	llist_print(ll);

}



int main(int argc, char ** argv) {

	char * test;
	
	if (argc <2) {
		printf("Usage: test_linked_list test1|test2|...test12\n");
		exit(1);
	}

	test = argv[1];
	printf("Running %s\n", test);
	if (strcmp(test, "test1")==0) {
		test1();
	}
	else if (strcmp(test, "test2")==0) {
		test2();
	}
	else if (strcmp(test, "test3")==0) {
		test3();
	}
	else if (strcmp(test, "test4")==0) {
		test4();
	}
	else if (strcmp(test, "test5")==0) {
		test5();
	}
	else if (strcmp(test, "test6")==0) {
		test6();
	}
	else if (strcmp(test, "test7")==0) {
		test7();
	}
	else if (strcmp(test, "test8")==0) {
		test8();
	}
	else if (strcmp(test, "test9")==0) {
		test9();
	}
	else if (strcmp(test, "test10")==0) {
		test10();
	}
	else if (strcmp(test, "test11")==0) {
		test11();
	}
	else if (strcmp(test, "test12")==0) {
		test12();
	}
	else {
		printf("Test not found!!n");
		exit(1);
	}

	return 0;
}

