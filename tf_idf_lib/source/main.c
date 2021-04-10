// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <hashtable.h>
#include <read_data.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define ERROR -1

typedef size_t (*func_tf_idf)(const char *path, hashtable_t *hashtable_t);

int64_t test(const char *path_to_files, func_tf_idf func) {
  hashtable_t *TF_ALL_DOCS = create_hash_table();
  struct timespec start, end;
  if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &start) == -1) {
    fprintf(stderr, "clock_gettime error");
    return ERROR;
  }
  func(path_to_files, TF_ALL_DOCS);
  if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &end) == -1) {
    fprintf(stderr, "clock_gettime error");
    return ERROR;
  }
  int64_t result = end.tv_nsec - start.tv_nsec;
  return result;
}

int main(int argc, char **argv) {
  // загружаю so библиотеку с потоками

  void *libhandle = dlopen("libtf_idf_threads.so", RTLD_LAZY);
  if (libhandle == NULL) {
    fprintf(stderr, "dlopen error");
    return ERROR;
  }

  fprintf(stderr, "dlopen Error");

  void *tf_idf = dlsym(libhandle, "get_tf_idf_from_dir");
  if (tf_idf == NULL) {
    fprintf(stderr, "couldn`t get function from lib");
    return ERROR;
  }

  printf("\t Time spent parralel: %li \n", test("../data/test-1/", tf_idf));
  printf("\t Time spent cons: %li \n",
         test("../data/test-1/", get_tf_idf_from_dir));

  dlclose(libhandle);
  return 0;
}
