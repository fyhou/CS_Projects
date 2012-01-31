
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"

int a[] = {45, 23, 78, 12, 100, 1, 100, 34, 90, 78};

int
main( int argc, char ** argv )
{
  List l;
  int i;

  int nelements = sizeof( a )/ sizeof( int );
  for ( i = 0; i < nelements; i++ ) {
    l.insertSorted( a[ i ] );
  }

  /* Additional test: inserting negative number */
  l.insertSorted(-1);

  /* Additional test: inserting 0 */
  l.insertSorted(0);

  /* Additional test: insert a character */
  l.insertSorted('A');
  /** ASCII value is added and sorted correctly **/

  /* Additional test: insert a double */
  l.insertSorted(1.1);
  /** Since argument is an int, function truncates, than adds **/

  /* Additional test: insert a double */
  // l.insertSorted("test");
  /** test fails; cannot convert char * into int **/ 

  /* Additional test: insert NULL */
  l.insertSorted(NULL);
  /** converted to a 0, then inserted correctly **/ 

  printf("List after sorting...\n");

  l.print();

  // Make sure that list is sorted
  ListNode *n = l._head;
  while ( n && n->_next ) {
    assert( n->_value <= n->_next->_value );
    n = n->_next;
  }

  // remove elements from the list
  assert( l.remove( 34 ) == 0 );
  assert( l.remove( 34 ) == -1 );
  assert( l.remove( 95 ) == -1 );
  assert( l.remove( 100 ) == 0 );
  assert( l.remove( 100 ) == 0 );
  assert( l.remove( 100 ) == -1 );

  /* Additional test: remove NULL */
  assert( l.remove( NULL ) == -1);
   

  // Make sure that the other elements are still there
  assert ( l.lookup( 45) == 0 );
  assert ( l.lookup( 23) == 0 );
  assert ( l.lookup( 78) == 0 );
  assert ( l.lookup( 1) == 0 );
  assert ( l.lookup( 90) == 0 );
  assert ( l.lookup( 34) == -1 );
  assert ( l.lookup( 100) == -1 );
  assert ( l.lookup( 95) == -1 );
  assert ( l.lookup( 2) == -1 );
  assert ( l.lookup( 12) == 0 );

  printf(">>> test_listd!\n");
  exit( 0 );
}
