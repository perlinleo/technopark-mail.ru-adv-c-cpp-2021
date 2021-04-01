  
#include "gtest/gtest.h"

extern "C"{
    #include "read_data.h"
    #include "hashtable.h"
    #include <stdio.h>
}

int compareFile(FILE* file_compared, FILE* file_checked)
{
    bool diff = 0;
    int N = 65536;
    char* b1 = (char*) calloc (1, N+1);
    char* b2 = (char*) calloc (1, N+1);
    size_t s1, s2;

    do {
        s1 = fread(b1, 1, N, file_compared);
        s2 = fread(b2, 1, N, file_checked);

        if (s1 != s2 || memcmp(b1, b2, s1)) {
            diff = 1;
            break;
        }
      } while (!feof(file_compared) || !feof(file_checked));

    free(b1);
    free(b2);

    if (diff) return 0;
    else return 1;
}

TEST(dataset_TF_IDF, small){
  // FILE* stream = freopen( "../prog.log", "w", stdout );
  
  hashtable_t *TF_ALL_DOCS = create_hash_table();
  int a = get_tf_idf_from_dir("../../data/", TF_ALL_DOCS);
  ASSERT_EQ(a,3);

  // fclose( stream );
}