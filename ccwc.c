#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

int indexOf(char *array[], int length, char value[]) {
  for (int i = 1; i < length; i++) {
    if (strcmp(array[i], value) == 0) {
      return i;
    }
  }
  return -1;
}

int getFile(char *array[], int length) {
  for (int i = 1; i < length; i++) {
    if (strchr(array[i], '.') != NULL) {
      return i;
    }
  }
  return -1;
}

int countBytes(FILE *file_pointer) {
  int count = 0;
  while (fgetc(file_pointer) != EOF) {
    count++;
  }
  return count;
}

int countLines(FILE *file_pointer) {
  int count = 0;
  char ch;
  while ((ch = fgetc(file_pointer)) != EOF) {
    if (ch == 0xA) {
      count++;
    }
  }
  return count;
}

int countWords(FILE *file_pointer) {
  int count = 0;
  char word[1024];
  while (fscanf(file_pointer, "%s", word) == 1) {
    count++;
  }

  return count;
}

int countChars(FILE *file_pointer) {
  int count = 0;
  wint_t wc;
  while ((wc = fgetwc(file_pointer)) != WEOF) {
    count++;
  }
  return count;
}

void printOptions(char *array[], int array_length, FILE *f_ptr) {
  printf("%c", 0x20);
  if (indexOf(array, array_length, "-l") != -1) {
    printf("%d ", countLines(f_ptr));
    fseek(f_ptr, 0, SEEK_SET);
  }
  if (indexOf(array, array_length, "-w") != -1) {
    printf("%d ", countWords(f_ptr));
    fseek(f_ptr, 0, SEEK_SET);
  }
  if (indexOf(array, array_length, "-c") != -1) {
    printf("%d ", countBytes(f_ptr));
    fseek(f_ptr, 0, SEEK_SET);
  }
  if (indexOf(array, array_length, "-m") != -1) {
    fclose(f_ptr);
    f_ptr = fopen(array[getFile(array, array_length)], "rb");
    printf("%d ", countChars(f_ptr));
    fseek(f_ptr, 0, SEEK_SET);
  }
}

int main(int argv_length, char *argv[]) {
  setlocale(LC_CTYPE, "");
  FILE *file_pointer;
  file_pointer = fopen(argv[getFile(argv, argv_length)], "rb");

  if (file_pointer == NULL) {
    return 6;
  }

  if (argv_length > 2) {
    printOptions(argv, argv_length, file_pointer);
    printf("%s\n", argv[getFile(argv, argv_length)]);
  }

  fclose(file_pointer);
  return 0;
}
