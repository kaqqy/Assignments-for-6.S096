#include "list.h"
#include <stdio.h>

int sq( int x ) {
  return x * x;
}

int plus( int x, int y ) {
  return x + y;
}

int main(void) {
  int N = 5;
  List list = empty_list();

  for( int i = 0; i < N; ++i ) {
    list_append( &list, i );
  }

  list_print( list );
  list_apply( &list, sq );
  list_print( list );
  list_append( &list, list_reduce( &list, plus ) );
  list_print( list );
  for (int i = 0; i < 100; i++) {
    list_insert_before( &list, i - 1, i );
  }
  list_print( list );
  for (int i = 2; i < 20; i++) {
    list_delete( &list, i );
  }
  list_print( list );
  list_delete( &list, 0 );
  list_delete( &list, -1 );
  list_print( list );
  list_clear( &list );
  return 0;
}
