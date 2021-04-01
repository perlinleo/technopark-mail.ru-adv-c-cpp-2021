// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#ifndef INCLUDE_DATA_READ_DATA_H_
#define INCLUDE_DATA_READ_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hashtable.h>
#include <dirent.h>


#define BUF_SIZE 50
#define BUF_SIZE_PATH 255
#define UNIQUE 1
#define NOT_UNIQUE 0
#define MAX_FILES_AMOUNT 500
#define MAX_FILENAME 100


float count_idf(hashtable_t* hashtable, const char* word,size_t dir_size,char* doc_verbose);

size_t fill_hashtable_from_file(const char* path,hashtable_t* hashtable, char* doc_verbose);

size_t tf_metrics_from_file(const char* path,hashtable_t* hashtable,char* doc_verbose, float counter);

size_t tf_idf_metrics_from_file(const char* path,hashtable_t* hashtable,char* doc_verbose,size_t doc_amount);

size_t count_words_from_file(const char* path,hashtable_t* hashtable,char* doc_verbose);

size_t fill_hashtable_from_dir(const char* path, hashtable_t* hashtable_t);

#endif  // INCLUDE_DATA_READ_DATA_H_