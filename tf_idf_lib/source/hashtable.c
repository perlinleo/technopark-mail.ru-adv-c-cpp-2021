#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define DEFAULT_TABLE_SIZE 150000
//размер файла-> 1мб -> 1млн символов , при средней длинне слова в 4.5 буквы максимальное количество разных слов в одном файле=222222
//222222 

#define RAND_VALUE 40

/*
typedef struct word{
    
}
*/

typedef struct hash_item_t {
    char *key;
    uint counter;
    struct hash_item_t *next;
} hash_item_t;

typedef struct hashtable_t { 
    hash_item_t **hash_items;
} hashtable_t;


uint create_hash (const char* key){
    uint hash = 0;

    //printf("\n%zu\n", strlen(key));
    //strlen check works fine but max_length must be enough
    
    for(int i = 0;i < strlen(key); ++i){
        hash = hash * RAND_VALUE + key[i];
    }
    
    hash = hash % DEFAULT_TABLE_SIZE;
    
    return hash;
}



hash_item_t* new_hash_item(const uint *counter,const char* key){
    hash_item_t *item = malloc(sizeof(hash_item_t));
    item->key = malloc(sizeof(uint));
    counter=0;
    strcpy(item->key, key);
}



hashtable_t *create_hash_table()
{
    hashtable_t *new_hashtable= malloc(sizeof(hashtable_t));
    if (new_hashtable==NULL){
        fprintf(stderr, "hashtable allocation error!\n");
        return NULL;
    }

    new_hashtable->hash_items = calloc(sizeof(hash_item_t*) , DEFAULT_TABLE_SIZE);
    

    /*
    for(int i = 0; i<DEFAULT_TABLE_SIZE; ++i) {
        printf("i was: %p\n" ,new_hashtable->hash_items[i]);
        new_hashtable->hash_items[i] = NULL;
        printf("i am: %p\n" ,new_hashtable->hash_items[i]);
    }

    */

    return new_hashtable;
}

void add_value(hashtable_t* hashtable,const char*key){
    size_t slot = create_hash(key);

    hash_item_t *item = hashtable->hash_items[slot];

    if (item==NULL) {
        hashtable->hash_items[slot] = new_hash_item(0,key);
    }
    else {
        printf("item found!");
        hashtable->hash_items[slot]->counter++;
        printf("\nfound %i times\n", hashtable->hash_items[slot]->counter);
    }


}

void delete_hash_table() {
}


int main(int argc, char**argv){
    char string[5];
    hashtable_t *ht = create_hash_table();
    while (1==1)
    {
        scanf("%5s",string);
        printf("%d\n", create_hash(string));
        add_value(ht,string);    
    }
    
    printf("%d\n", create_hash("hello"));
    return 0;
}