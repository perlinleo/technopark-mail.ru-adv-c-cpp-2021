// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <read_data.h>

size_t fill_hashtable_from_file(const char* path, hashtable_t* hashtable,
                                char* doc_verbose) {
  if (hashtable == NULL) {
    printf("Can`t access given hashtable\n");
    return NULL;
  }
  int counter = count_words(path, hashtable, doc_verbose);
  print_hash_table(hashtable);
  if (counter > 0) {
    if (tf_metrics(path, hashtable, doc_verbose, counter) > 0) {
      print_hash_table(hashtable);
      printf("Succesefully calculated TF metrics\n");
    }
  } else {
    printf("No words found!\n");
  }

  return counter;
}

size_t get_tf_idf_from_dir(const char* path, hashtable_t* hashtable_t) {
  DIR* directory;
  size_t files_amount = 0;
  directory = opendir(path);
  char** queries = malloc(sizeof(char*) * MAX_FILES_AMOUNT);
  if (queries == NULL) {
    printf("Can`t alloc space for files array\n");
  }

  // получаю пути к файлам

  if (directory) {
    struct dirent* dir;
    while ((dir = readdir(directory)) != 0) {
      if (strstr(dir->d_name, ".txt")) {
        queries[files_amount] = malloc(sizeof(char) * MAX_FILENAME);
        snprintf(queries[files_amount], MAX_FILENAME, "%s%s", path,
                 dir->d_name);
        files_amount++;
      } else {
        printf("\n%s isn`t .txt\n", dir->d_name);
      }
    }
    char doc_name[MAX_FILENAME];
    for (int i = 0; i < files_amount; ++i) {
      snprintf(doc_name, MAX_FILENAME, "%i.txt", i + 1);
      printf("%s\n", doc_name);
      fill_hashtable_from_file(queries[i], hashtable_t, doc_name);
    }
    for (int i = 0; i < files_amount; ++i) {
      snprintf(doc_name, MAX_FILENAME, "%i.txt", i + 1);
      tf_idf_metrics(queries[i], hashtable_t, doc_name, files_amount);
    }
    for (int i = 0; i < files_amount; ++i) {
      free(queries[i]);
    }
  }

  free(queries);
  return files_amount;
}

size_t get_top_5_for_doc(hashtable_t* hashtable, const char* doc_verbose) {
  char doc[MAX_FILENAME];
  string_val** strings_from_doc = malloc(sizeof(string_val*) * MAX_WORD_COUNT);
  int counter = 0;

  snprintf(doc, MAX_FILENAME, "%s.txt", doc_verbose);
  for (int i = 0; i < DEFAULT_TABLE_SIZE; i++) {
    if (hashtable->hash_items[i] != NULL) {
      if (strstr(hashtable->hash_items[i]->key, doc)) {
        strings_from_doc[counter] = malloc(sizeof(string_val));
        strings_from_doc[counter]->key = malloc(sizeof(char) * MAX_WORD_LENGTH);
        snprintf(strings_from_doc[counter]->key, MAX_WORD_LENGTH, "%s",
                 hashtable->hash_items[i]->key);
        strings_from_doc[counter]->val = hashtable->hash_items[i]->counter;
        counter++;
      }
    }
  }
  sort_string_val_array(strings_from_doc, counter);
  print_top_5(strings_from_doc, counter);
}
