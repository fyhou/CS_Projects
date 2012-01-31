
#if !defined RESIZABLE_ARRAY_H
#define RESIZABLE_ARRAY_H

#define INITIAL_SIZE_RESIZABLE_TABLE 10

typedef struct RESIZABLE_TABLE_ENTRY {
	char * name;
	char * value;
} RESIZABLE_TABLE_ENTRY;

typedef struct RESIZABLE_TABLE {
	int maxElements;                       // Max number of elements in the array
	int currentElements;                   // Number of elements used in the array
	struct RESIZABLE_TABLE_ENTRY * array;  // Array that stores the entries.
} RESIZABLE_TABLE;  

RESIZABLE_TABLE * rtable_create();
void rtable_print(RESIZABLE_TABLE * table);
int rtable_add(RESIZABLE_TABLE * table, char * name, char * value);
char * rtable_lookup(RESIZABLE_TABLE * table, char * name);
int rtable_remove(RESIZABLE_TABLE * table, char * name);
int rtable_get_ith(RESIZABLE_TABLE * table, int ith, char ** name, char ** value);
int rtable_remove_ith(RESIZABLE_TABLE * table, int ith);
int rtable_number_elements(RESIZABLE_TABLE * table);
int rtable_max_elements(RESIZABLE_TABLE * table);
int rtable_save(RESIZABLE_TABLE * table, char * file_name);
int rtable_read(RESIZABLE_TABLE * table, char * file_name);
void rtable_sort(RESIZABLE_TABLE * table, int ascending);

int rtable_remove_first(RESIZABLE_TABLE * table);
int rtable_remove_last(RESIZABLE_TABLE * table);
int rtable_insert_first(RESIZABLE_TABLE * table, char *name, char * value);
int rtable_insert_last(RESIZABLE_TABLE * table, char *name, char * value);

#endif

