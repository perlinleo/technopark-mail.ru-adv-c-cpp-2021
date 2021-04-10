  
#include "gtest/gtest.h"

extern "C"{
    #include "read_data.h"
    #include "hashtable.h"
    #include <stdio.h>
}

TEST(hashfunc, small){
  // FILE* stream = freopen( "../prog.log", "w", stdout );
  EXPECT_EQ(719432, create_hash("test"));
  
  // fclose( stream );
}

TEST(newha, correct){
  const char* key= "hello";
  hash_item_t *test = new_hash_item(key);
  EXPECT_EQ(key[0], test->key[0]);
}

