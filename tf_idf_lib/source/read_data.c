#include <read_data.h>




size_t fill_hashtable_from_file(const char* path,hashtable_t* hashtable, char* doc_verbose){
    if(hashtable==NULL){
        fprintf(stderr, "can`t access given hashtable");
        return NULL;
    }
    size_t counter=0;
    FILE *current_file= fopen(path, "r");
    
    char *buff = malloc(sizeof(char)*BUF_SIZE);
    while(fscanf(current_file,"%49s",buff)!=EOF){
        if(doc_verbose!=NULL){
            printf("\n%s_%s\n",buff,doc_verbose);
            strcat(buff, "_DOC_");
            strcat(buff, doc_verbose);
        }
        add_value(hashtable, buff);
        ++counter;
    }

    fclose(current_file);
    return counter;
}

size_t fill_hashtable_from_dir(const char* path, hashtable_t* hashtable_t, short unique){
    DIR *directory;
    struct dirent *dir;
    char buff[BUF_SIZE_PATH];
    directory = opendir(path);
    if(directory)
    {
        while ((dir = readdir(directory))!=0){
            if(strstr(dir->d_name,".txt")){
                printf("\nFilling from %s\n",dir->d_name);
                sprintf(buff, "%s%s",path, dir->d_name);
                printf(buff);
                if(unique==UNIQUE){
                    printf("unique chheck\n");
                    fill_hashtable_from_file(buff,hashtable_t, dir->d_name);
                }
                else if(unique==NOT_UNIQUE)
                {
                    fill_hashtable_from_file(buff,hashtable_t, NULL);
                }
            }
        }
    }
    return 0;
}






