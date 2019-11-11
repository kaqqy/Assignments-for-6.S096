#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct List_node_s {
  List_node *next;
  int value;
};

List empty_list( void ) {
  return (List) { .length = 0, .front = NULL };
}

// Allocate memory for a single List_node
List_node* create_node( int value ) {
  List_node *new_node = malloc( sizeof( List_node ) );
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

// Append a new node containing 'value' to the end of the list
void list_append( List *list, int value ) {
  List_node **back = &list->front;
  while (*back) {
    back = &(*back)->next;
  }
  *back = create_node(value);
  list->length++;
}

// Insert a new node with value 'insert' before the node with value 'before'
// Does not do anything if no node contains the value 'before'
void list_insert_before( List *list, int insert, int before ) {
  List_node **cur = &list->front;
  while (*cur && (*cur)->value != before) {
    cur = &(*cur)->next;
  }
  if (*cur) {
    List_node *to_insert = create_node(insert);
    to_insert->next = *cur;
    *cur = to_insert;
    list->length++;
  }
}

// Delete all occurrences of the value 'value' in the list
void list_delete( List *list, int value ) {
  List_node **cur = &list->front;
  while (*cur) {
    if ((*cur)->value == value) {
      List_node *to_delete = *cur;
      *cur = (*cur)->next;
      free(to_delete);
      list->length--;
    }
    else {
      cur = &(*cur)->next;
    }
  }
}

// Apply the function to every value in the list
void list_apply( List *list, int (*function_ptr)(int) ) {
  List_node *cur = list->front;
  while (cur) {
    cur->value = function_ptr(cur->value);
    cur = cur->next;
  }
}

// Accumulates the values in the list with the function
int list_reduce( List *list, int (*function_ptr)(int, int) ) {
  if (!list->front) {
    return 0;
  }
  List_node *cur = list->front->next;
  int result = list->front->value;
  while (cur) {
    result = function_ptr(result, cur->value);
    cur = cur->next;
  }
  return result;
}

// Print out a linked list in human-readable form
void list_print( List list ) {
  if( list.front == NULL ) {
    printf( "{}\n" );
  } else {
    printf( "{ " );

    List_node *p = list.front;
    size_t length = list.length;

    while( p->next != NULL && length > 0 ) {
      printf( "%d -> ", p->value );
      p = p->next; --length;
    }
    printf( "%d }\n", p->value );

    if( length != 1 ) {
      printf( "Error: badly formed list.\n" );
      exit( EXIT_FAILURE );
    }
  }
}

// Frees the memory in List *list
void list_clear( List *list ) {
  List_node *front = list->front;
  size_t length = list->length;

  while( front != NULL && length > 0 ) {
    List_node *next = front->next;
    free( front );
    front = next;
    --length;
  }

  if( length != 0 ) {
    printf( "Error: failed to clean up list properly.\n" );
    exit( EXIT_FAILURE );
  }
}
