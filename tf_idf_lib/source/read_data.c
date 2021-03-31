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

size_t fill_hashtable_from_dir(const char* path, hashtable_t* hashtable_t){
    DIR *directory;
    struct dirent *dir;
    char buff[BUF_SIZE];
    directory = opendir(path);
    if(directory)
    {
        while ((dir = readdir(directory))!=0){
            if(strstr(dir->d_name,".txt")){
                printf("\nFilling from %s\n",dir->d_name);
                sprintf(buff, "%s%s",path, dir->d_name);
                printf(buff);
                fill_hashtable_from_file(buff,hashtable_t);
            }
        }
    }
    return 0;
}




