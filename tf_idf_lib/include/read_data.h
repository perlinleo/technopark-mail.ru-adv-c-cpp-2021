// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#ifndef INCLUDE_DATA_READ_DATA_H_
#define INCLUDE_DATA_READ_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hashtable.h>
#include <dirent.h>

size_t fill_hashtable_from_file(const char* path,hashtable_t* hashtable);

size_t fill_hashtable_from_dir(const char* path, hashtable_t* hashtable_t);

#endif  // INCLUDE_DATA_READ_DATA_H_