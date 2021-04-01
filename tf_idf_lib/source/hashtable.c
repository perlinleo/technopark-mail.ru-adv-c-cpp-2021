// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <hashtable.h>

unsigned int create_hash(const char *str) {
  __int64_t hash = RAND_VALUE;
  int c;

  while (c = *str++) {
    hash = ((hash << 5) + hash) + c;
  }
  if (hash < 0) {
    hash *= -1;
  }
  hash = hash % DEFAULT_TABLE_SIZE;
  
  return (hash);
}

hash_item_t *new_hash_item(const char *key) {
  hash_item_t *item = malloc(sizeof(hash_item_t));
  if (item == NULL) {
    printf("insufficient memory available/new_hash_item");
    return NULL;
  }
  item->key = malloc(strlen(key) * sizeof(char) + 1);
  if (item->key == NULL) {
    printf("insufficient memory available/new_hash_item");
    free(item);
    return NULL;
  }
  item->counter = 1.0;
  snprintf(item->key, strlen(key) * sizeof(char) + 1, "%s", key);
  

  return item;
}

hashtable_t *create_hash_table() {
  system("pwd");
  hashtable_t *new_hashtable = (hashtable_t *)malloc(sizeof(hashtable_t));
  system("pwd");
  if (new_hashtable == NULL) {
    fprintf(stderr, "hashtable allocation error!\n");
    return;
  }
  system("pwd");
  new_hashtable->hash_items =
      (hash_item_t **)calloc(sizeof(hash_item_t *), DEFAULT_TABLE_SIZE);
  if (new_hashtable->hash_items == NULL) {
    fprintf(stderr, "hashtable->hast_items allocation error!\n");
    free(new_hashtable);
    return;
  }
  system("pwd");

  return new_hashtable;
}

void add_value(hashtable_t *hashtable, const char *key) {
  if (hashtable == NULL) {
    fprintf(stderr, "Can`t access hashtable");
  } else {
    unsigned int slot = create_hash(key);

    hash_item_t *item = hashtable->hash_items[slot];

    if (item == NULL) {
      hashtable->hash_items[slot] = new_hash_item(key);
    } else {
      hashtable->hash_items[slot]->counter += 1.0;
    }
  }
}

void print_hash_table(hashtable_t *hashtable) {
  if (hashtable == NULL) {
    fprintf(stderr, "Can`t access hashtable");
  } else {
    for (int i = 0; i < DEFAULT_TABLE_SIZE; i++) {
      if (hashtable->hash_items[i] != NULL) {
        printf("%s has value of %f (hash: 0x%x )\n",
               hashtable->hash_items[i]->key, hashtable->hash_items[i]->counter,
               i);
      }
    }
  }
}


