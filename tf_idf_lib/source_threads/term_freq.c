// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <pthread.h>
#include <term_freq.h>

size_t count_words_multythread(const char* path, hashtable_t* hashtable,
                               char* doc_verbose, pthread_mutex_t* mutex_lock) {
  // Подсчёт количества слов в файле.
  // Количество повторений для каждого слова-> хэш-таблица

  if (hashtable == NULL) {
    fprintf(stderr, "can`t access given hashtable");
    return NULL_HASHTABLE;
  }
  size_t counter = 0;
  FILE* current_file = fopen(path, "r");

  char* buff = malloc(sizeof(char) * BUF_SIZE);
  while (fscanf(current_file, "%49s", buff) != EOF) {
    // printf("WORKING WITH DOC %s\n", doc_verbose);
    if (doc_verbose != NULL) {
      strcat(buff, "_DOC_");
      strcat(buff, doc_verbose);
      pthread_mutex_lock(mutex_lock);
      add_value(hashtable, buff);
      pthread_mutex_unlock(mutex_lock);
    } else {
      fprintf(stderr, "empty doc_verb\n");
      return NULL_DOC_VERB;
    }

    ++counter;
  }
  fclose(current_file);
  return counter;
}

size_t tf_metrics_multythread(const char* path, hashtable_t* hashtable,
                              char* doc_verbose, float counter,
                              pthread_mutex_t* mutex_lock) {
  // изменение значений в существующей таблице. теперь counter
  // для каждого элемента ---->>> TF метрика

  if (hashtable == NULL) {
    fprintf(stderr, "can`t access given hashtable");
    return NULL_HASHTABLE;
  }
  if (doc_verbose != NULL) {
    if (hashtable == NULL) {
      fprintf(stderr, "Can`t access hashtable");
    } else {
      for (int i = 0; i < DEFAULT_TABLE_SIZE; i++) {
        if (hashtable->hash_items[i] != NULL) {
          if (strstr(hashtable->hash_items[i]->key, doc_verbose) != NULL) {
            pthread_mutex_lock(mutex_lock);
            hashtable->hash_items[i]->counter /= counter;
            pthread_mutex_unlock(mutex_lock);
          }
        }
      }
    }
  }
  return 1;
}

size_t tf_idf_metrics(const char* path, hashtable_t* hashtable,
                      char* doc_verbose, size_t doc_amount) {
  // изменение значений в существующей таблице. теперь counter
  // для каждого элемента ---->>> TF_IDF метрика

  if (hashtable == NULL) {
    fprintf(stderr, "can`t access given hashtable");
    return NULL_HASHTABLE;
  }

  if (doc_verbose != NULL) {
    if (hashtable == NULL) {
      fprintf(stderr, "Can`t access hashtable");
    } else {
      float idf_val;
      for (int i = 0; i < DEFAULT_TABLE_SIZE; i++) {
        if (hashtable->hash_items[i] != NULL) {
          idf_val = count_idf(hashtable, hashtable->hash_items[i]->key,
                              doc_amount, doc_verbose);
          hashtable->hash_items[i]->counter *= idf_val;
        }
      }
    }
  }
  return 0;
}

float count_idf(hashtable_t* hashtable, const char* word, size_t dir_size,
                char* doc_verbose) {
  char* buff = malloc(sizeof(char) * BUF_SIZE);
  char* wordCopy = malloc(sizeof(char) * BUF_SIZE);

  snprintf(wordCopy, MAX_WORD_LENGTH, "%s", word);
  int len = strlen(word);
  wordCopy[len - 10] = '\0';
  float idf_val = 0;

  for (int i = 1; i <= dir_size; ++i) {
    snprintf(buff, BUF_SIZE * sizeof(char), "%s_DOC_%i.txt", wordCopy, i);
    unsigned int hash = create_hash(buff);
    hash_item_t* item = hashtable->hash_items[hash];
    if (item == NULL) {
      // нет
    } else {
      idf_val += 1.0;
    }
  }
  return (dir_size / idf_val);
}
