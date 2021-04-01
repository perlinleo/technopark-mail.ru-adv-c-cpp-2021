// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <hashtable.h>
#include <read_data.h>
#include <stdio.h>

int main(int argc, char **argv) {
  fprintf(stdout, "successfully reassigned\n");
  hashtable_t *TF_ALL_DOCS = create_hash_table();
  int a = get_tf_idf_from_dir("../data/", TF_ALL_DOCS);
  printf("%i\n\n", a);
  print_hash_table(TF_ALL_DOCS);
  a = get_top_5_for_doc(TF_ALL_DOCS, "1");
  printf("%i\n\n", a);

  return 0;
}
