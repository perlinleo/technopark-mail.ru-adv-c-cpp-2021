#include <read_data.h>


#include <stdio.h>
#include <stdlib.h>

size_t fill_hashtable_from_file(const char* path,hashtable_t* hashtable, char* doc_verbose){
    if(hashtable==NULL){
        fprintf(stderr, "can`t access given hashtable");
        return NULL;
    }
    int counter = count_words_from_file(path, hashtable, doc_verbose);
    if(counter>0){
        if(tf_metrics_from_file(path,hashtable,doc_verbose,counter)){
            printf("Succesefully calculated TF metrics\n");
        }
    }
    else{
        printf("No words found!\n");
    }

    return counter;
}

size_t count_words_from_file(const char* path,hashtable_t* hashtable,char* doc_verbose){
    // Подсчёт количества слов в файле. 
    // Количество повторений для каждого слова-> хэш-таблица
    
    if(hashtable==NULL){
        fprintf(stderr, "can`t access given hashtable");
        return NULL;
    }
    size_t counter=0;
    FILE *current_file= fopen(path, "r");

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
    return counter;
}

size_t tf_metrics_from_file(const char* path,hashtable_t* hashtable,char* doc_verbose, float counter){
    // изменение значений в существующей таблице. теперь counter  
    // для каждого элемента ---->>> TF метрика
    
    if(hashtable==NULL){
        fprintf(stderr, "can`t access given hashtable");
        return NULL;
    }
    char *buff = malloc(sizeof(char)*BUF_SIZE);
    FILE *current_file= fopen(path, "r");

    while(fscanf(current_file,"%49s",buff)!=EOF)
    {
        if(doc_verbose!=NULL){
            printf("\n%s_DOC_%s\n",buff,doc_verbose);
            strcat(buff, "_DOC_");
            strcat(buff, doc_verbose);
            hashtable->hash_items[create_hash(buff)]->counter/=counter;
        }
    }
    fclose(current_file);
    return 0;
}

size_t tf_idf_metrics_from_file(const char* path,hashtable_t* hashtable,char* doc_verbose,size_t doc_amount){
    // изменение значений в существующей таблице. теперь counter  
    // для каждого элемента ---->>> TF_IDF метрика
    
    if(hashtable==NULL){
        fprintf(stderr, "can`t access given hashtable");
        return NULL;
    }
    char *buff = malloc(sizeof(char)*BUF_SIZE);
    float idf_val=0;

    FILE *current_file= fopen(path, "r");
    while(fscanf(current_file,"%49s",buff)!=EOF)
    {
        if(doc_verbose!=NULL){
            idf_val=count_idf(hashtable,buff,doc_amount);
            strcat(buff, "_DOC_");
            strcat(buff, doc_verbose);
            hashtable->hash_items[create_hash(buff)]->counter*=idf_val;
        }
    }
    fclose(current_file);

    return 0;
}


float count_idf(hashtable_t* hashtable, const char* word,size_t dir_size){
    char *buff = malloc(sizeof(char)*BUF_SIZE);
    strcpy(buff,word);
    strcat(buff, "_DOC_1.txt");
    float idf_val=0;
    unsigned int hash = create_hash(buff);
    hash_item_t *item = hashtable->hash_items[hash];
    if(item==NULL){
        printf("There is no %s in a given hashtable!\n",word);
    }
    else{
        for(int i=1;i<=dir_size;++i){
            snprintf(buff, BUF_SIZE*sizeof(char),"%s_DOC_%i.txt",word,i);
            hash=create_hash(buff);
            item = hashtable->hash_items[hash];
            if(item==NULL){
                // printf("There is no %s in a given hashtable!\n",word);
            }
            else{
                idf_val+=1.0;
            }
        }
    }
    return idf_val;
}

size_t fill_hashtable_from_dir(const char* path, hashtable_t* hashtable_t){
    DIR *directory;
    size_t files_amount=0;
    struct dirent *dir;
    char buff[BUF_SIZE_PATH];

    directory = opendir(path);
    
    char** queries= malloc(sizeof(char*)*MAX_FILES_AMOUNT);
    if(queries==NULL){
        printf("Can`t alloc space for files array");
    }

    // получаю пути к файлам
    
    if(directory)
    {
        while ((dir = readdir(directory))!=0){
            if(strstr(dir->d_name,".txt")){
                /*
                files_amount++;
                printf("\nFilling from %s\n",dir->d_name);
                sprintf(buff, "%s%s",path, dir->d_name);
                printf(buff);
                fill_hashtable_from_file(buff,hashtable_t, dir->d_name);
                */
                queries[files_amount]=malloc(sizeof(char)*MAX_FILENAME);
                sprintf(buff, "%s%s",path, dir->d_name);
                strcpy(queries[files_amount],buff);
                files_amount++;
            }
            else{
                printf("\n%s isn`t .txt\n",dir->d_name);
            }
        }
        char doc_name[3];
        for(int i=0;i<files_amount;++i){
            sprintf(doc_name, "%i.txt", i+1);
            fill_hashtable_from_file(queries[i],hashtable_t, doc_name);
        }
        for(int i=0;i<files_amount;++i){
            sprintf(doc_name, "%i.txt", i+1);
            tf_idf_metrics_from_file(queries[i],hashtable_t,doc_name,files_amount+1);
        }

    }
    return files_amount;
}

/*
size_t fill_hashtables_from_dir_1(const char* path){
    DIR *directory;
    size_t files_amount=0;
    struct dirent *dir;

    hashtable_t* WORD_COUNT_HASHTABLE=create_hash_table();
    
    char buff[BUF_SIZE_PATH];
    directory = opendir(path);
    if(directory)
    {
        while ((dir = readdir(directory))!=0){
            if(strstr(dir->d_name,".txt")){
                files_amount++;
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
*/





