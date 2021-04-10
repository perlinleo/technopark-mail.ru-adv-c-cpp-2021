  
#include "gtest/gtest.h"

extern "C"{
    #include "read_data.h"
    #include "hashtable.h"
    #include <stdio.h>
}

TEST(getdocs, correct){
    hashtable_t *TF_ALL_DOCS = create_hash_table();
    int a = get_tf_idf_from_dir("../../data/test-1/",TF_ALL_DOCS);
    ASSERT_EQ(a,5);
}

TEST(decodeAndPrint, correct){
    hashtable_t *TF_ALL_DOCS = create_hash_table();
    int a = get_tf_idf_from_dir("../../data/test-1/",TF_ALL_DOCS);
    ASSERT_EQ(a,5);
}


TEST(top5, correctdata1){
  hashtable_t *TF_ALL_DOCS = create_hash_table();
  int a = get_tf_idf_from_dir("../../data/test-1/",TF_ALL_DOCS);
   ASSERT_EQ(a,5);
   int b = get_top_5_for_doc(TF_ALL_DOCS,"1");
   ASSERT_EQ(b,6);
}