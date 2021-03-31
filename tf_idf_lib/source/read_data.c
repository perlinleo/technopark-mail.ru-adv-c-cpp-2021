#include <read_data.h>




size_t fill_hashtable_from_file(const char* path,hashtable_t* hashtable, char* doc_verbose){
    if(hashtable==NULL){
        fprintf(stderr, "can`t access given hashtable");
        return NULL;
    }
    size_t counter=0;
    FILE *current_file= fopen(path, "r");
    float idf_val=0;

    char *buff = malloc(sizeof(char)*BUF_SIZE);
    while(fscanf(current_file,"%49s",buff)!=EOF)
    {
        if(doc_verbose!=NULL){
            printf("\n%s_%s\n",buff,doc_verbose);
            strcat(buff, "_DOC_");
            strcat(buff, doc_verbose);
        }
        add_value(hashtable, buff);
        ++counter;
    }
    fclose(current_file);
    current_file= fopen(path, "r");
    while(fscanf(current_file,"%49s",buff)!=EOF)
    {
        if(doc_verbose!=NULL){
            printf("\n%s_%s\n",buff,doc_verbose);
            strcat(buff, "_DOC_");
            strcat(buff, doc_verbose);
            hashtable->hash_items[create_hash(buff)]->counter/=counter;
        }
    }
    fclose(current_file);
    current_file= fopen(path, "r");
    while(fscanf(current_file,"%49s",buff)!=EOF)
    {
        if(doc_verbose!=NULL){
            idf_val=count_idf(hashtable,buff,3);
            strcat(buff, "_DOC_");
            strcat(buff, doc_verbose);
            hashtable->hash_items[create_hash(buff)]->counter*=idf_val;
        }
    }
    fclose(current_file);
    return counter;
}




float count_idf(hashtable_t* hashtable, const char* word,size_t dir_size){
    char *buff = malloc(sizeof(char)*BUF_SIZE);
    strcpy(buff,word);
    strcat(buff, "_DOC_1.txt");
    printf(buff);
    float idf_val=0;
    unsigned int hash = create_hash(buff);
    hash_item_t *item = hashtable->hash_items[hash];
    if(item==NULL){
        printf("There is no %s in a given hashtable!\n",word);
    }
    else{
        for(int i=1;i<=dir_size;++i){
            snprintf(buff, BUF_SIZE*sizeof(char),"%s_DOC_%i.txt",word,i);
            printf(buff);
            hash=create_hash(buff);
            item = hashtable->hash_items[hash];
            if(item==NULL){
                printf("There is no %s in a given hashtable!\n",word);
            }
            else{
                idf_val+=1.0;
            }
        }
    }
    printf("\n\n%f",idf_val);
    return idf_val;
}

size_t fill_hashtable_from_dir(const char* path, hashtable_t* hashtable_t, short unique){
    DIR *directory;
    size_t files_amount=0;
    struct dirent *dir;
    char buff[BUF_SIZE_PATH];
    directory = opendir(path);
    if(directory)
    {
        while ((dir = readdir(directory))!=0){
            if(strstr(dir->d_name,".txt")){
                files_amount++;
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
            else{
                printf("%s isn`t .txt\n",dir->d_name);
            }
        }
    }
    return files_amount;
}






