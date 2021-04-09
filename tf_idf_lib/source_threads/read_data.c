// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <pthread.h>
#include <read_data.h>

#define STAGECOUNT 1
#define STAGETF 2
#define STAGETF_IDF 3

typedef struct ht_mutex_t {
  hashtable_t* hashtable;  // protected hashtable
  pthread_mutex_t mutex;
} ht_mutex_t;

ht_mutex_t data = {PTHREAD_MUTEX_INITIALIZER, 0};
int counterGlobal = 0, threadAmount = 12, threadsFinished = 0,
    files_amount_glob = 0;

typedef struct fhtff {
  char* path[MAX_FILENAME];
  char* doc_verbose[MAXNAMLEN];
} fhtff;

void* fill_hashtable_tf_from_file_thread(void* arg) {
  printf("started !\n");
  fhtff* fhtff_arg = (fhtff*)arg;
  const char* path = fhtff_arg->path;
  const char* doc_verbose = fhtff_arg->doc_verbose;
  pthread_mutex_t* mutex = &data.mutex;
  if (data.hashtable == NULL) {
    printf("Can`t access given hashtable\n");
    return NULL;
  }
  float counter =
      count_words_multythread(path, data.hashtable, doc_verbose, mutex);
  printf(" %i |COUNTER VAL|", counter);
  counterGlobal += counter;
  if (counter > 0) {
    if (tf_metrics_multythread(path, data.hashtable, doc_verbose, counter,
                               mutex) > 0) {
      // print_hash_table(hashtable);
      printf("Succesefully calculated TF metrics\n");
    }
  } else {
    printf("No words found!\n");
  }
  threadsFinished++;
  printf("finished!\n");
  return 0;
}

void* fill_hashtable_tf_idf_from_file_thread(void* arg) {
  printf("started !\n");
  fhtff* fhtff_arg = (fhtff*)arg;
  const char* path = fhtff_arg->path;
  const char* doc_verbose = fhtff_arg->doc_verbose;
  tf_idf_metrics(path, data.hashtable, doc_verbose, files_amount_glob);
  threadsFinished++;
  printf("finished!\n");
  return 0;
}

/*
void *fill_hashtable_tf_idf_from_file_thread(void* arg){
  fhtff *fhtff_arg = (fhtff*)arg;
  const char* path = fhtff_arg->path;
  const char* doc_verbose = fhtff_arg->doc_verbose;
  pthread_mutex_t *mutex= &data.mutex;
  if (data.hashtable == NULL) {
    printf("Can`t access given hashtable\n");
    return NULL;
  }
  pthread_mutex_lock(mutex);
  if (counterGlobal > 0) {
    if (tf_metrics(path, data.hashtable, doc_verbose, counterGlobal) > 0) {
      printf("Succesefully calculated TF metrics\n");
    }
  } else {
    printf("No words found!\n");
  }
  threadsFinished++;

}
*/
size_t fill_hashtable_from_file(const char* path, hashtable_t* hashtable,
                                char* doc_verbose) {
  if (hashtable == NULL) {
    printf("Can`t access given hashtable\n");
    return NULL;
  }
  // int counter = count_words(path, hashtable, doc_verbose);
  int counter = 0;
  /*
   __  _     _                                 _  __
  / / | |_  | |__    _ __    ___    __ _    __| | \ \
 | |  | __| | '_ \  | '__|  / _ \  / _` |  / _` |  | |
 | |  | |_  | | | | | |    |  __/ | (_| | | (_| |  | |
 | |   \__| |_| |_| |_|     \___|  \__,_|  \__,_|  | |
  \_\                                             /_/
  */
  /*print_hash_table(hashtable);
  if (counter > 0) {
    if (tf_metrics(path, hashtable, doc_verbose, counter) > 0) {
      print_hash_table(hashtable);
      printf("Succesefully calculated TF metrics\n");
    }
  } else {
    printf("No words found!\n");
  }
  */
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

    fhtff* jobs = malloc(sizeof(fhtff) * 100);
    data.hashtable = hashtable_t;
    for (int i = 0; i < files_amount; ++i) {
      snprintf(jobs[i].doc_verbose, MAX_FILENAME, "%i.txt", i + 1);
      // printf("%s\n", doc_name);
      snprintf(jobs[i].path, MAXNAMLEN, "%s", queries[i]);
      // fill_hashtable_from_file(queries[i], hashtable_t, doc_name);
      // pthread_create(&threadsIds[threadCounter],NULL,fill_hashtable_tf_from_file_thread,threadInfo);
    }  // получаю threadInfo для следующих потоков.
    for (int i = 0; i < files_amount; ++i) {
      printf("%s %s THREADINFO\n", jobs[i].doc_verbose, jobs[i].path);
    }

    pthread_t threadsIds[files_amount];

    for (int i = 0; i < files_amount; ++i) {
      if (pthread_create(&threadsIds[i], NULL,
                         fill_hashtable_tf_from_file_thread, &jobs[i]) == 0) {
        printf("THREAD NUM #%i CREATED \n", i);
      }
    }
    while (threadsFinished < files_amount) {
      // printf("FINISHED %i FILES AMOUNT %i \n",threadsFinished,files_amount);
    }
    print_hash_table(data.hashtable);
    files_amount_glob = files_amount;
    threadsFinished = 0;
    for (int i = 0; i < files_amount; ++i) {
      /*
      snprintf(doc_name, MAX_FILENAME, "%i.txt", i + 1);
      tf_idf_metrics(queries[i], hashtable_t, doc_name, files_amount);
      */
      if (pthread_create(&threadsIds[i], NULL,
                         fill_hashtable_tf_idf_from_file_thread,
                         &jobs[i]) == 0) {
        printf("THREAD NUM #%i CREATED \n", i);
      }
    }
    while (threadsFinished < files_amount) {
      // printf("FINISHED %i FILES AMOUNT %i \n",threadsFinished,files_amount);
    }
    printf("done!\n");
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
