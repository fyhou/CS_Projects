/**
 * CS 251 - Project 4 - HashTableTemplate
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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////
//
// Class that defines a template for a hash table
// The keys are of type const char* and the data
// can be any type.
//
// Use like this:
//  HashTable hashTableInt<int>;
//  
//
///////////////////////////////////////////

// Each hash entry stores a key, object pair
template <typename Data>
struct HashTableTemplateEntry {
  const char* _key;
  Data _data;
  HashTableTemplateEntry* _next;
};


// This is a Hash table that maps string keys to objects of type Data
template <typename Data>
class HashTableTemplate {
 public:
  // Number of buckets
  enum {TableSize = 2039};
  
  // Array of the hash buckets.
  HashTableTemplateEntry<Data>** _buckets;
  
  // Obtain the hash code of a key
  int hash(const char* key);
  
 public:
  HashTableTemplate();
  
  // Add a record to the hash table. Returns true if key already exists.
  // Substitute content if key already exists.
  bool insertItem(const char* key, Data data);

  // Find a key in the dictionary and place in "data" the corresponding record
  // Returns false if key is does not exist
  bool find( const char* key, Data* data);

  // Removes an element in the hash table. Return false if key does not exist.
  bool removeElement(const char* key);
};


template <typename Data>
int HashTableTemplate<Data>::hash(const char* key) {
  int h=0;
  const char* p = key;
  while (*p) {
    h = (31 * h + (*p)) % TableSize;
    p++;
  }

  return h;
}

/**
 * method to initialize the hash table; after the object
 * is created, it is iterated over to place NULL values 
 * in the buckets
 */
template <typename Data>
HashTableTemplate<Data>::HashTableTemplate() {
  // TODO: Initialize the hash table
  	_buckets = new HashTableTemplateEntry<Data> * [TableSize];
	for (int i = 0 ; i < TableSize ; i++) { 
		_buckets[i] = NULL;
	}
  	
}

/*
 * insertion method
 * 
 * @param key The key to represent the data
 * @param data The data to be stored in the hash table
 * @return bool True if entry already exists, false if it doesn't
 */
template <typename Data>
bool HashTableTemplate<Data>::insertItem(const char* key, Data data) {
  // TODO: Insert a key,data pair inside the hash table.
  // Return true if the entry already exists or false if
  // it does not exist.
	int hashedKey = hash(key);				
	HashTableTemplateEntry<Data>* current = _buckets[hashedKey];

        // iterate to find entry 
        while (current != NULL) {
       		if (!strcmp(key, current->_key)){
       	     // entry is found, overwrite data
        	    current->_data = data;
        	    return true;
        	}
        	current = current->_next; // go to next element
    	}	
        
    	// entry not found in table, so create new entry
    	current = new HashTableTemplateEntry<Data>();
    	current->_key = strdup(key);
    	current->_data = data;
    	current->_next = _buckets[hashedKey];
    	_buckets[hashedKey] = current;
    	return false;
}

/**
 * find data associated to key
 * 
 * @param key Key to be searched for
 * @param data Where to store the data if found
 * @return bool Return true if entry is found, false if not
 */
template <typename Data>
bool HashTableTemplate<Data>::find(const char* key, Data* data) {
  // TODO: Find the data associated to a key. The data is
  // stored in the *data passed as parameter.
  // Return true if the entry is found or false otherwise.
	int hashedKey = hash(key);
	HashTableTemplateEntry<Data>* temp = _buckets[hashedKey];
	
	if (temp != NULL) {
		while (temp != NULL) {
			// key is found
			if (!(strcmp(temp->_key,key))) {
				// data is written to paramter value
				*data = temp->_data;
				return true;	
			}
			// iterates to next bucket
			temp = temp->_next;
		}	
	}
	// key not found in hash table
	return false;
}

/**
 * remove element method
 * 
 * @param key Key/data pair to remove
 * @return bool Return true if found, false if not
 */
template <typename Data>
bool HashTableTemplate<Data>::removeElement(const char* key) {
  // TODO: Remove the element that has this key from the hash table.
  // Return true if the entry is found or false otherwise.
	int hashedKey = hash(key);
	HashTableTemplateEntry<Data>* temp = _buckets[hashedKey];
	
	if (temp != NULL) {
		while (temp != NULL) {
			// key found
			if (!(strcmp(temp->_key, key))) {
				if (temp->_next != NULL) 
					_buckets[hashedKey] = temp->_next;
				else 
					_buckets[hashedKey] = NULL;
				delete temp;
				return true;
			}
			// iterates to next bucket
			temp = temp->_next;
		}
	}
	// key not found
  	return false;
}


template <typename Data>
class HashTableTemplateIterator {
  int _currentBucket;
  HashTableTemplateEntry<Data>*_currentEntry;
  HashTableTemplate<Data>* _hashTable;
 public:
  HashTableTemplateIterator(HashTableTemplate<Data>* hashTable);
  bool next(const char*& key, Data& data);
};

/**
 * makes the iterator 
 * 
 * @param HashTableTemplate The hash table to be iterated over
 */
template <typename Data>
HashTableTemplateIterator<Data>::HashTableTemplateIterator(HashTableTemplate<Data>* hashTable) {
  // TODO: Initialize iterator. "hashTable" is the table to be iterated.
	_hashTable = hashTable;
	_currentBucket = 0;
	_currentEntry = NULL;
}

/**
 * iterates to next item in table
 * 
 * @param key Next key
 * @param data Next data
 * @return bool Returns true if there are more entries or false otherwise
 */
template <typename Data>
bool HashTableTemplateIterator<Data>::next(const char*& key, Data& data) {
  // TODO: Returns the next element in the hash table.
  // The key and data values are stored in the references passed
  // as argument. It returns true if there are more entries or
  // false otherwise.
	
	if (_currentEntry != NULL) {
		_currentEntry = _currentEntry->_next;
		if (_currentEntry != NULL) {
			key = _currentEntry->_key;
			data = _currentEntry->_data;
			return true;
		}
	}
	_currentBucket++;
	while (_currentBucket < (_hashTable->TableSize)) {
		if (_hashTable->_buckets[_currentBucket] != NULL) {
			_currentEntry = _hashTable->_buckets[_currentBucket];
			key = _currentEntry->_key;
			data = _currentEntry->_data;
			return true;
		}
		_currentBucket++;
	}
	return false;
}
