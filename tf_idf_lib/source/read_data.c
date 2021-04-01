#include <read_data.h>

size_t fill_hashtable_from_file(const char* path, hashtable_t* hashtable,
                                char* doc_verbose) {
  if (hashtable == NULL) {
    fprintf(stderr, "can`t access given hashtable");
    return NULL;
  }
  int counter = count_words(path, hashtable, doc_verbose);
  print_hash_table(hashtable);
  if (counter > 0) {
    if (tf_metrics(path, hashtable, doc_verbose, counter) > 0) {
      print_hash_table(hashtable);
      printf("Succesefully calculated TF metrics\n");
    }
  }

  else {
    printf("No words found!\n");
  }

  return counter;
}

size_t get_tf_idf_from_dir(const char* path, hashtable_t* hashtable_t) {
  DIR* directory;
  size_t files_amount = 0;

  directory = opendir(path);

  char** queries = malloc(sizeof(char*) * MAX_FILES_AMOUNT);
  if (queries == NULL) {
    printf("Can`t alloc space for files array");
  }

  // получаю пути к файлам

  if (directory) {
    struct dirent* dir;
    char buff[BUF_SIZE_PATH];
    while ((dir = readdir(directory)) != 0) {
      if (strstr(dir->d_name, ".txt")) {
        /*
        files_amount++;
        printf("\nFilling from %s\n",dir->d_name);
        sprintf(buff, "%s%s",path, dir->d_name);
        printf(buff);
        fill_hashtable_from_file(buff,hashtable_t, dir->d_name);
        */
        queries[files_amount] = malloc(sizeof(char) * MAX_FILENAME);
        sprintf(buff, "%s%s", path, dir->d_name);
        strcpy(queries[files_amount], buff);
        files_amount++;
      } else {
        printf("\n%s isn`t .txt\n", dir->d_name);
      }
    }
    char doc_name[7];
    for (int i = 0; i < files_amount; ++i) {
      sprintf(doc_name, "%i.txt", i + 1);
      printf("%s\n", doc_name);
      fill_hashtable_from_file(queries[i], hashtable_t, doc_name);
    }
    for (int i = 0; i < files_amount; ++i) {
      sprintf(doc_name, "%i.txt", i + 1);
      tf_idf_metrics(queries[i], hashtable_t, doc_name, files_amount);
    }
    for (int i = 0; i < files_amount; ++i) {
      free(queries[i]);
    }
  }
  free(queries);
  return files_amount;
}
