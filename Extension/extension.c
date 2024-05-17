#include "specific.h"

void test(void)
{}

// Create an empty BSA
bsa* bsa_init(void)
{
   static bsa start;
   bsa* b;

   b = &start;
   head = &start;
   start.indx = -1;
   start.n = UNSET;
   start.prev = NULL;
   start.next = NULL;

   return b;
}

// Create a new node
bsa* create_new(void)
{
   bsa* new = (bsa*)malloc(sizeof(bsa));
   if (new == NULL) {
      printf("malloc fail\n");
      return NULL;
   }
   else {
      return new;
   }
}

// Set element at index indx with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d)
{
   while (b->indx != indx) {
      if (b->next != NULL) {
         b = b->next;
      }
      else {
         bsa* new = create_new();
         new->prev = b;
         b->next = new;
         new->n = UNSET;
         new->next = NULL;
         new->indx = b->indx + 1;
         b = b->next;
      }
   }  
   b->n = d;

   return true;
}

// Return pointer to data at element b[i]
// or NULL if element is unset, or part of a row that hasn't been allocated.
int* bsa_get(bsa* b, int indx)
{
   b = head;
   while (b->indx != indx) {
      if (b->next == NULL) {
         return NULL;
      }
      else {
         b = b->next;
      }
   }   

   if (b->n == UNSET) {
      return NULL;      
   }
   else {
      return &(b->n);
   }
}

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
bool bsa_delete(bsa* b, int indx)
{
   b = head;
   while (b->indx != indx) {
      if (b->next != NULL) {
         b = b->next;
      }
      else {
         return false;
      }
   }

   if (b->n == UNSET) {
      return false;
   }    
   else {    
      b->n = UNSET;
      return true;
   }
}

// Clears up all space used
bool bsa_free(bsa* b)
{
   b = head->next;

   while (b->next != NULL) {
      bsa* temp = b;
      b = b->next;
      free(temp);
   }
   free(b);    

   return true;
}

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc)
{
   b = head;
   while (b->next != NULL) {
      if (b->n != UNSET) {
         (*func)(&(b->n), acc);
      }
      b = b->next;
   }
   if (b->n != UNSET) {
      (*func)(&(b->n), acc);
   }
}
