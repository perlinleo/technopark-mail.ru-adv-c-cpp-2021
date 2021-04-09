// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#ifndef INCLUDE_TERM_FREQ_H_
#define INCLUDE_TERM_FREQ_H_

#include <hashtable.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 50

float count_idf(hashtable_t* hashtable, const char* word, size_t dir_size,
                char* doc_verbose);

size_t tf_metrics(const char* path, hashtable_t* hashtable, char* doc_verbose,
                  float counter);

size_t tf_metrics_multythread(const char* path, hashtable_t* hashtable,
                              char* doc_verbose, float counter,
                              pthread_mutex_t* mutex_lock);

size_t tf_idf_metrics(const char* path, hashtable_t* hashtable,
                      char* doc_verbose, size_t doc_amount);

size_t count_words_multythread(const char* path, hashtable_t* hashtable,
                               char* doc_verbose, pthread_mutex_t* mutex_lock);

size_t count_words(const char* path, hashtable_t* hashtable, char* doc_verbose);

#endif  // INCLUDE_TERM_FREQ_H_