// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <stdio.h>

#include <read_data.h>

#include <hashtable.h>

int main(int argc, char **argv) {
  system("pwd");
  hashtable_t *TF_ALL_DOCS = create_hash_table();
  get_tf_idf_from_dir("../data/", TF_ALL_DOCS);
  print_hash_table(TF_ALL_DOCS);
  return 0;
}
