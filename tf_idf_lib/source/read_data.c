#include <read_data.h>


#define BUF_SIZE 50

size_t fill_hashtable_from_file(const char* path,hashtable_t* hashtable){
    if(hashtable==NULL){
        fprintf(stderr, "can`t access given hashtable");
        return NULL;
    }

    size_t counter=0;
    FILE *current_file= fopen(path, "r");
    
    char *buff = malloc(sizeof(char)*BUF_SIZE);
    while(fscanf(current_file,"%49s",buff)!=EOF){
        printf("%s ",buff);
        add_value(hashtable, buff);
        ++counter;
    }

    fclose(current_file);
    return counter;
}




