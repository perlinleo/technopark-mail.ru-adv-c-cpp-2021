// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <hashtable.h>

#define DEFAULT_TABLE_SIZE 150000000
                           
// размер файла-> 1мб -> 1млн символов , при средней длинне слова в 4.5 буквы
// максимальное количество разных слов в одном файле=222222 222222

#define RAND_VALUE 40

#define MAX_WORD_LENGTH 50
/*
typedef struct word{

}
*/

unsigned int create_hash(const char *str)
{
    unsigned long hash = RAND_VALUE;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%150000000;
}

hash_item_t *new_hash_item(const char *key) {
  hash_item_t *item = malloc(sizeof(hash_item_t*));
  if (item == NULL) {
    fprintf(stderr, "insufficient memory available/new_hash_item");
    return NULL;
  }
  item->key = malloc(strlen(key) * sizeof(char) + 1);
  if (item->key == NULL) {
    fprintf(stderr, "insufficient memory available/new_hash_item");
    free(item);
    return NULL;
  }
  item->counter = 1;
  snprintf(item->key, strlen(key) * sizeof(char) + 1, "%s", key);
  // strcpy(item->key, key);

  return item;
}

hashtable_t *create_hash_table() {
  hashtable_t *new_hashtable = malloc(sizeof(hashtable_t));
  if (new_hashtable == NULL) {
    fprintf(stderr, "hashtable allocation error!\n");
    return NULL;
  }
  new_hashtable->document = malloc(255* sizeof(char));
  if (new_hashtable->document == NULL) {
    fprintf(stderr, "insufficient memory new_hashtable->document");
    free(new_hashtable);
    return NULL;
  }
  new_hashtable->hash_items = calloc(sizeof(hash_item_t *), DEFAULT_TABLE_SIZE);
  if (new_hashtable->hash_items == NULL) {
    fprintf(stderr, "hashtable->hast_items allocation error!\n");
    free(new_hashtable);
    return NULL;
  }

  return new_hashtable;
}

void add_value(hashtable_t *hashtable, const char *key) {
  if (hashtable == NULL) {
    fprintf(stderr, "Can`t access hashtable");
  } else {
    size_t slot = create_hash(key);

    hash_item_t *item = hashtable->hash_items[slot];

    if (item == NULL) {
      hashtable->hash_items[slot] = new_hash_item(key);
    } else {
      hashtable->hash_items[slot]->counter++;
    }
  }
}

void print_hash_table(hashtable_t *hashtable) {
  if (hashtable == NULL) {
    fprintf(stderr, "Can`t access hashtable");
  } else {
    for (int i = 0; i < DEFAULT_TABLE_SIZE; i++) {
      if (hashtable->hash_items[i] != NULL) {
        printf("%s found %u times (hash:0x%x)\n", hashtable->hash_items[i]->key,
               hashtable->hash_items[i]->counter, i);
      }
    }
  }
}

unsigned int counter_for_word_ex_ht(hashtable_t *hashtable, const char *word) {
  if (hashtable == NULL) {
    fprintf(stderr, "Can`t access hashtable!");
  } else if (word == NULL) {
    fprintf(stderr, "Can`t access given word");
  } else {
    unsigned int hash = create_hash(word);
    if (hashtable->hash_items[hash] != NULL) {
      return hashtable->hash_items[hash]->counter;
    }
  }
}
