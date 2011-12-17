/**
 * CS 251 - Project 4 - HashTableVoid
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

#include "HashTableVoid.h"

using namespace std;
int HashTableVoid::hash(const char* key) {
	int h=0;
  	const char* p = key;
	while (*p) {
    		h = (31 * h + (*p)) % TableSize;
    		p++;
	}
  	return h;	
}

/**
 * method to initialize the hash table; after the space
 * is allocated, it is iterated over to place NULL values 
 * in the buckets
 */
HashTableVoid::HashTableVoid() {
 	 // TODO: Initialize the hash table
	_buckets = (HashTableVoidEntry**) malloc (TableSize * sizeof (HashTableVoidEntry*));
	for (int i = 0 ; i < TableSize ; i++) {
		_buckets[i] = NULL;
	}
}


bool HashTableVoid::insertItem(const char* key, void* data) {
  	// TODO: Insert a key,data pair inside the hash table.
 	// Return true if the entry already exists or false if
  	// it does not exist.
  	int hashedKey = hash(key);
  	
  	// check if there is already an element at that particular location of buckets array
  	HashTableVoidEntry* current = _buckets[hashedKey];

  		// iterate to find entry 
        while(current != NULL) {
       		if(!strcmp(key, current->_key)){
       			// entry is found, overwrite data
        	    current->_data = data;
        	    return true;
        	}
        	current = current->_next;
    	}	
        
        // entry not found in table, so create new entry
    	current = new HashTableVoidEntry();
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
bool HashTableVoid::find(const char* key, void** data) {
  // TODO: Find the data associated to a key. The data is
  // stored in the *data passed as parameter.
  // Return true if the entry is found or false otherwise.
	int hashedKey = hash(key);
	HashTableVoidEntry* temp = _buckets[hashedKey];
	
	if (temp != NULL) {
		while (temp != NULL) {
			// key is found
			if (!(strcmp(temp->_key, key))) {
				// data is written to paramter value
				*data = (void *)(temp->_data);
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
bool HashTableVoid::removeElement(const char* key) {
  // TODO: Remove the element that has this key from the hash table.
  // Return true if the entry is found or false otherwise.
  	int hashed = hash(key);
  	HashTableVoidEntry* temp = _buckets[hashed];
  	
  	if (temp != NULL) {
  		while (temp != NULL) {
  			// key found
  			if (!(strcmp(temp->_key, key))) {
  				if (temp->_next != NULL) 
  					_buckets[hashed] = temp->_next;
  				else
  					_buckets[hashed] = NULL;
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

/**
 * makes the iterator 
 * 
 * @param HashTableTemplate The hash table to be iterated over
 */
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid* hashTable) {
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
bool HashTableVoidIterator::next(const char*& key, void*& data) {
  // TODO: Returns the next element in the hash table.
  // The key and data values are stored in the references passed
  // as argument. It returns true if there are more entries or
  // false otherwise.
	
	while(_currentEntry == NULL && _currentBucket < _hashTable->TableSize) {
		_currentEntry = _hashTable->_buckets[_currentBucket++];
	}
	
	if(_currentBucket == _hashTable->TableSize) {
		return false;
	}
	
	key = _currentEntry->_key;
	data = _currentEntry-> _data;
	
	_currentEntry = _currentEntry -> _next;
	return true;
}
