#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

//
// It returns a new LINKED_LIST. It allocates it dynamically,
// and initializaes the values. The initial list is empty.
//
LINKED_LIST * llist_create() {

	LINKED_LIST * list = (LINKED_LIST *) malloc(sizeof(LINKED_LIST));
	if (list == NULL) {
		return NULL;
	}

	// Create Sentinel node. This node does not store any data
	// but simplifies the list implementation.
	list->head = (LINKED_LIST_ENTRY *) malloc(sizeof(LINKED_LIST_ENTRY));
	if (list->head == NULL) {
		return NULL;
	}
	
	
	list->nElements = 0;
	list->head->next = list->head;
	list->head->previous = list->head;
	
	return list;
}

//
// It prints the elements in the alist in the form:
//
// ===== List =====
// nElements=2
// name="George" value="289 Pine St, West Lafayette, 47906"
// name="Peter" value="27 Oak St, West Lafayette, 47906"
// ======== End List =======
void llist_print(LINKED_LIST * list) {
	
	LINKED_LIST_ENTRY * e;

//	printf("===== List =====\n");
//	printf("nElements=%d\n", list->nElements);

	e = list->head->next;
	while (e != list->head) {
		printf("%s\n", e->name);
		e = e->next;
	}
	// printf("======== End List =======\n");
}

//
// Adds one pair name/value to the list. If the name already exists it will
// Substitute its value. Otherwise, it will store name/value in a new entry.
// The name/vale strings are duplicated with strdup() before adding them to the
// list.
//
int llist_add(LINKED_LIST * list, char * name, char * value) {
	LINKED_LIST_ENTRY * e;

	// TODO: Check if the name is not in the list
	// if it is there substitute the value and return 1.
	int i = 0;
	
	e = list->head->next;
	while (e != list->head) {
		if (strcmp(e->name, name) == 0) {
			e->value = strdup(value);
			return 1;
		}
		else {
			e = e->next;
		}
	}

	// Entry not found. Add new entry at the end of the list
	e = (LINKED_LIST_ENTRY *)malloc(sizeof(LINKED_LIST_ENTRY));
	e->name = strdup(name);
	e->value = strdup(value);

	//Add at the beginning
	e->next = list->head;
	e->previous = list->head->previous;
	list->head->previous = e;
	e->previous->next = e;
	
	list->nElements++;
	return 0;
}

//
// Returns the value that correspond to the name or NULL if the
// name does not exist in the list.
//
char * llist_lookup(LINKED_LIST * list, char * name) {
	LINKED_LIST_ENTRY * e;

	e = list->head->next;
	while (e != list->head) {
		if (strcmp(e->name, name) == 0) {
			return (e->value);
		}
		else {
			e = e->next;
		}
	}
	
	return NULL;
}

//
// It removes the entry with that name from the list.
// Also the name and value strings will be freed.
//
int llist_remove(LINKED_LIST * list, char * name) {
	LINKED_LIST_ENTRY * e;

	e = list->head->next;
	while (e != list->head) {
		if (strcmp(e->name, name) == 0) {
			(e->previous)->next = e->next;
		 	(e->next)->previous = e->previous;
			list->nElements--;
			free (e->name);
			free (e->value);
			return 1;
		}
		else {
			e = e->next;
		}
	}
	return 0;
}

//
// It returns in *name and *value the name and value that correspond to
// the ith entry. It will return 1 if successful, or 0 otherwise.
//
int llist_get_ith(LINKED_LIST * list, int ith, char ** name, char ** value) {
	LINKED_LIST_ENTRY * e;
	int i = 0;

	if (ith >= list->nElements)
		return 0;
	else { 
		e = list->head->next;
		for (i = 0; i < ith; i++) {
			e = e->next;
		}

		*name = strdup(e->name);
		*value = strdup(e->value);
	}

	return 1;
}

//
// It removes the ith entry from the list.
// Also the name/value strings are freed.
//
int llist_remove_ith(LINKED_LIST * list, int ith) {
	LINKED_LIST_ENTRY * e;
	int i = 0;
	e = list->head->next;

	if (ith >= list->nElements)
		return 0;
	else {
		for (i = 0; i < ith; i++) {
			e = e->next;
		}
		
		(e->previous)->next = e->next;
		(e->next)->previous = e->previous;
		free(e->name);
		free(e->value);
		list->nElements--;
	}

	return 1;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LINKED_LIST * list) {
	return list->nElements;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// name1\n
// value1\n
// \n
// name2\n
// value2\n
// ...
//
// Notice that there is an empty line between each name/value pair.
//
int llist_save(LINKED_LIST * list, char * file_name) {
	int i = 0;
	FILE *file;
	LINKED_LIST_ENTRY * e;

	e = list->head->next;
	
	file = fopen(file_name, "wt");
	if (file == NULL) {
		return 0;
	}
	else {
		for (i = 0; i < list->nElements; i++) {
			fprintf(file, "%s\n%s\n\n", e->name, e->value);
			e = e->next;
		}
	}

	fclose(file);
	return 1;
}

//
// It reads the list from the file_name indicated. If the list already has entries, it will
// clear the entries.
//
int llist_read(LINKED_LIST * list, char * file_name) {
	FILE *file;
	LINKED_LIST_ENTRY * e;

	e = list->head->next;
	while (e != list->head) {
		memset(e->name, 0, 10);
		memset(e->value,0, 10);
		e = e->next;
	}

	file = fopen(file_name, "r");
	if (file == NULL) {
		return 0;
	}
	else {
		char c;
		int i = 0;
		int j = 0;
		int nl_count = 1;
		char name[100];
		char value[100];
		int decider = 1;

		while ((c=fgetc(file)) != EOF){
			if (c != '\n') {
				if (decider == 1) {
					name[i] = c;
					i++;
				}
				else {
					value[j] = c;
					j++;
				}
			}
			else {
				nl_count++;
				if ((nl_count % 3) == 0) {
					name[i] = '\0';
					value[j] = '\0';
					llist_add(list, name, value);
					i = 0;
					j = 0;
					nl_count = 0;
					memset(name, 0, 100);
					memset(value, 0, 100);
					decider = 1;
					continue;
				}
				else if ((nl_count % 2) == 0) {
					decider = 0;
					continue;	
				}
				else {
				}
			}
		}
	}	

	fclose(file);
	return 1;
}

//
// It sorts the list according to the name. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LINKED_LIST * list, int ascending) {
	int i = 0;
	int j = 0;
	char *temp;
	LINKED_LIST_ENTRY * e;
	e = list->head->next;
	if (ascending == 1) {
		for (i = 0; i < list->nElements-1; i++) {
			e = list->head->next;
			while ((e->next) != list->head) {
				if ((strcmp(e->name, (e->next)->name)) > 0) {
					temp = strdup((e->next)->name);
					(e->next)->name = strdup(e->name);
					e->name = strdup(temp);
				
					temp = strdup((e->next)->value);
					(e->next)->value = strdup(e->value);
					e->value = strdup(temp);
				}
				e = e->next;
			}
		}
	}
	else {
		for (i = 0; i < list->nElements-1; i++) {
			e = list->head->next;
			while ((e->next) != list->head) {
					if ((strcmp(e->name, (e->next)->name)) < 0) {
					temp = strdup((e->next)->name);
					(e->next)->name = strdup(e->name);
					e->name = strdup(temp);

					temp = strdup((e->next)->value);
					(e->next)->value = strdup(e->value);
					e->value = strdup(temp);
				}
				e = e->next;
			}
		}

	}
}

//
// It removes the first entry in the list.
// All entries are moved down one position.
// It also frees memory allocated for name and value.
//
int llist_remove_first(LINKED_LIST * list) {
	LINKED_LIST_ENTRY * e;
	if (list -> nElements == 0)
		return 0;
	else {
		e = list->head->next;
		(e->previous)->next = e->next;
		(e->next)->previous = e->previous;
		list->nElements--;
		free(e->name);
		free(e->value);
		return 1;
	}
}

//
// It removes the last entry in the list
// It also frees memory allocated for name and value.
//
int llist_remove_last(LINKED_LIST * list) {
	if (list->nElements == 0)
		return 0;
	else {
		llist_remove_ith(list, list->nElements-1);
		return 1;
	}
}

//
// Insert a name/value pair at the beginning of the list.
// There is no check if the name already exists. The entry is added
// at the beginning of the list.
//
int llist_insert_first(LINKED_LIST * list, char *name, char * value) {
	LINKED_LIST_ENTRY * e;
	e = (LINKED_LIST_ENTRY *) malloc (sizeof(LINKED_LIST_ENTRY));
	e->name = strdup(name);
	e->value = strdup(value);

	e->next = list->head->next;
	e->previous = list->head->next->previous;
	list->head->next->previous = e;
	(e->previous)->next = e;
	list->nElements++;
	return 1;
}

//
// Insert a name/value pair at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
int llist_insert_last(LINKED_LIST * list, char *name, char * value) {
	LINKED_LIST_ENTRY * e;
	e = (LINKED_LIST_ENTRY *) malloc (sizeof(LINKED_LIST_ENTRY));
	e->name = strdup(name);
	e->value = strdup(value);

	e->next = list->head;
	e->previous = list->head->previous;
	list->head->previous = e;
	e->previous->next = e;

	list->nElements++;
	return 1;
}

