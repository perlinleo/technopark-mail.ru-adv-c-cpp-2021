// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#ifndef INCLUDE_DATA_READ_DATA_H_
#define INCLUDE_DATA_READ_DATA_H_

#include <dirent.h>
#include <hashtable.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string_val.h>
#include <term_freq.h>
#include <dlfcn.h>
#include <time.h>

#define BUF_SIZE_PATH 255
#define MAX_WORD_LENGTH 50
#define MAX_FILES_AMOUNT 500
#define MAX_FILENAME 100
#define MAX_WORD_COUNT 100000

size_t fill_hashtable_from_file(const char* path, hashtable_t* hashtable,
                                char* doc_verbose);

size_t get_tf_idf_from_dir(const char* path, hashtable_t* hashtable_t);

size_t get_top_5_for_doc(hashtable_t* hashtable, const char* doc_verbose);

#endif  // INCLUDE_DATA_READ_DATA_H_