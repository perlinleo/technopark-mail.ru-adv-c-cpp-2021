// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#ifndef INCLUDE_DATA_HASHTABLE_H_
#define INCLUDE_DATA_HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hash_item_t {
  
  char* key;
  float counter;
} hash_item_t;

typedef struct hashtable_t {
  char* document;
  hash_item_t** hash_items;
} hashtable_t;

unsigned int create_hash(const char* key);
hash_item_t* new_hash_item(const char* key);

hashtable_t* create_hash_table();

void add_value(hashtable_t* hashtable, const char* key);
void print_hash_table(hashtable_t* hashtable);
unsigned int counter_for_word_ex_ht(hashtable_t* hashtable, const char* word);

#endif  // INCLUDE_DATA_MYSUBSTRING_H_