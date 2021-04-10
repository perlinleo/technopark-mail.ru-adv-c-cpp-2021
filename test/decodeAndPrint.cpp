#include "gtest/gtest.h"

extern "C"{
    #include "read_data.h"
    #include "hashtable.h"
    #include <stdio.h>
}


TEST(decodeAndPrint, correct){
    hashtable_t *TF_ALL_DOCS = create_hash_table();
    int a = get_tf_idf_from_dir("../../data/",TF_ALL_DOCS);
    ASSERT_EQ(a,5);
}
