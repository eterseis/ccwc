#include <stdio.h>
#include <string.h>

int indexOf(char *array[], int length, char value[]){
  for (int i = 1; i < length; i++){
    if (strcmp(array[i], value) == 0){
      return i;
    }
  }
  return -1;
}

int getFile(char *array[], int length){
  for (int i = 1; i < length; i++){
    if (strchr(array[i], '.') != NULL){
      return i;
    }
  }
  return -1;
}

int countBytes(FILE *file_pointer){
  int count = -1;
  do{
    count++;
  }while (fgetc(file_pointer) != EOF);
  return count;
}

int main(int argc, char *argv[]){
  FILE *file_pointer;
  file_pointer = fopen(argv[getFile(argv, argc)], "r");

  if (file_pointer == NULL){
    return 6;
  }
  
  if (argc > 1){
    if(indexOf(argv, argc, "-c") != -1){
      printf("%d %s\n", countBytes(file_pointer), argv[getFile(argv, argc)]);
    }
  }
  return 0;
}
