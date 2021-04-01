#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hashtable.h>

#define BUF_SIZE 50

float count_idf(hashtable_t* hashtable, const char* word,size_t dir_size,char* doc_verbose);

size_t tf_metrics(const char* path,hashtable_t* hashtable,char* doc_verbose, float counter);

size_t tf_idf_metrics(const char* path,hashtable_t* hashtable,char* doc_verbose,size_t doc_amount);

size_t count_words(const char* path,hashtable_t* hashtable,char* doc_verbose);
