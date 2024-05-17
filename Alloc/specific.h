#pragma once
/* Binary Sparse Arrays */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define BSA_ROWS 30
#define UNSET -2147483648

struct bsa {
   bool empty;
   int* rpt[BSA_ROWS];
};
typedef struct bsa bsa;

// Create an empty BSA
bsa* bsa_init(void);

// Set element at index indx with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d);

// Return pointer to data at element b[i]
// or NULL if element is unset, or part of a row that hasn't been allocated.
int* bsa_get(bsa* b, int indx);

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
bool bsa_delete(bsa* b, int indx);

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b);

// Returns stringified version of structure
// Each row has its elements printed between {}, up to the maximum index.
// Rows after the maximum index are ignored.
bool bsa_tostring(bsa* b, char* str);

// Clears up all space used
bool bsa_free(bsa* b);

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc);

// You'll this to test the other functions you write
void test(void);

// Get the row of the input index
int get_row(int indx);

// Calculate the ilog2 using bit manipulation
int ilog2(int i);

// Get the position of the input index in its row
int get_pos(int indx, int row);

// Check whether the row is empty
bool check_row(bsa* b, int row);

// Check whether the whole bsa is empty
void check_bsa(bsa* b);

// Change a row to string and add it to str
void row_to_string(bsa* b, int row, char* str);

// Change the variable n from int to char 
void int_to_char(int n, char* s);
