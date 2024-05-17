#pragma once
/* Binary Sparse Arrays */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define UNSET -2147483648

struct bsa {
   int indx, n;
   struct bsa* prev;
   struct bsa* next;
};
typedef struct bsa bsa;
bsa* head;

// Create an empty BSA
bsa* bsa_init(void);

// Create a new node
bsa* create_new(void);

// Set element at index indx with value d i.e. b[i] = d;
bool bsa_set(bsa* b, int indx, int d);

// Return pointer to data at element b[i]
// or NULL if element is unset
int* bsa_get(bsa* b, int indx);

// Delete element at index indx by set it to UNSET
bool bsa_delete(bsa* b, int indx);

// Clears up all space used
bool bsa_free(bsa* b);

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc);

// You'll this to test the other functions you write
void test(void);
