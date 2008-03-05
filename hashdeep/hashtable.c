
#include "main.h"

/* $Id$ */

status_t file_data_compare(state *s, file_data_t *a, file_data_t *b)
{
  int partial_match = FALSE;
  hashname_t i;
  
  if (NULL == a || NULL == b || NULL == s)
    return status_unknown_error;  
  
  /* We first compare the hashes because they should tell us the fastest if we're
     looking at different files. Then the file size and finally the file name. */
  for (i = 0 ; i < NUM_ALGORITHMS ; ++i)
  {
    if (s->hashes[i]->inuse)
    {
      if (!(STRINGS_EQUAL(a->hash[i],b->hash[i])))
      {
	if (partial_match)
	  return status_partial_match;
	else
	  return status_no_match;
	
	partial_match = TRUE;
      }
    }
  }
  
  if (a->file_size != b->file_size)
    return status_file_size_mismatch;
  
  if (!(STRINGS_EQUAL(a->file_name,b->file_name)))
    return status_file_name_mismatch;
  
  return status_match;
}

/* These two functions are the "hash" functions for the hash table. 
   Because the original implementation of this code was for storing
   md5 hashes, I used the name "translate" to avoid confusion. */


/* Convert a single hexadecimal character to decimal. If c is not a valid
   hex character, returns 0. */
int translateChar(char c) 
{
  // If this is a digit
  if (c > 47 && c < 58) 
    return (c - 48);
  
  c = toupper(c);
  // If this is a letter... 'A' should be equal to 10
  if (c > 64 && c < 71) 
    return (c - 55);

  return 0;
}
    
/* Translates a hex value into it's appropriate index in the array.
   In reality, this just turns the first HASH_SIG_FIGS into decimal */
uint64_t translate(char *n) 
{ 
  int count;
  uint64_t total = 0, power = 1;
  for (count = HASH_TABLE_SIG_FIGS - 1 ; count >= 0 ; count--) {
    total += translateChar(n[count]) * power;
    power *= 16;
  }

  return total;
}



void hashtable_init(hashtable_t *t)
{
  uint64_t i;
  for (i = 0 ; i < HASH_TABLE_SIZE ; ++i)
    t->member[i] = NULL;
}


status_t hashtable_add(state *s, file_data_t *f)
{
  if (NULL == s || NULL == f)
    return status_unknown_error;

  

  return status_ok;
}


status_t hashtable_contains(state *s, file_data_t *f)
{
  hashname_t i, first_alg = alg_unknown;

  if (NULL == s || NULL == f)
    return status_unknown_error;
  
  i = 0;
  while (i < NUM_ALGORITHMS && alg_unknown == first_alg)
  {
    if (s->hashes[i]->inuse)
      first_alg = i;
    ++i;
  }

  return status_no_match;
}