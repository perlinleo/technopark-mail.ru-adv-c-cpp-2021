// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#ifndef INCLUDE_DATA_HASHTABLE_H_
#define INCLUDE_DATA_HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TABLE_SIZE 150000000

// размер файла-> 1мб -> 1млн символов , при средней длинне слова в 4.5 буквы
// максимальное количество разных слов в одном файле=222222 222222

#define RAND_VALUE 40

#define MAX_WORD_LENGTH 50

typedef struct hash_item_t {
  char* key;
  float counter;
} hash_item_t;

typedef struct hashtable_t {
  hash_item_t** hash_items;
} hashtable_t;

unsigned int create_hash(const char* key);
hash_item_t* new_hash_item(const char* key);

hashtable_t* create_hash_table();

void add_value(hashtable_t* hashtable, const char* key);
void print_hash_table(hashtable_t* hashtable);
unsigned int counter_for_word_ex_ht(hashtable_t* hashtable, const char* word);

#endif  // INCLUDE_DATA_MYSUBSTRING_H_