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
    FILE *wf_ptr;
    wf_ptr = freopen(array[getFile(array, array_length)], "rb", f_ptr);
    printf("%d ", countChars(wf_ptr));
    fclose(wf_ptr);
  }
}

void PrintPipeOptions(char *argv[], int argv_length, FILE *f_ptr) {
  char *options[] = {"-l", "-w", "-c", "-m"};
  int options_length = sizeof(options) / 8;
  for (int i = 0; i < options_length; i++) {
    if (indexOf(argv, argv_length, options[i]) != -1) {
      switch (i) {
      case 0:
        printf("%d\t", countLines(f_ptr));
        rewind(f_ptr);
        break;
      case 1:
        printf("%d\t", countWords(f_ptr));
        rewind(f_ptr);
        break;
      case 2:
        printf("%d\t", countBytes(f_ptr));
        rewind(f_ptr);
        break;
      case 3:
        FILE *wf_ptr = freopen("/tmp/ccwctmp.txt", "rb", f_ptr);
        printf("%d\t", countChars(wf_ptr));
        fclose(wf_ptr);
        break;
      }
    }
  }
  printf("\n");
}

int main(int argv_length, char *argv[]) {
  setlocale(LC_CTYPE, "");
  int fileIndex = getFile(argv, argv_length);
  if (fileIndex != -1) {
    FILE *file_pointer;
    file_pointer = fopen(argv[fileIndex], "rb");

    if (file_pointer == NULL) {
      return 6;
    }

    if (argv_length > 2) {
      printOptions(argv, argv_length, file_pointer);
      printf("%s\n", argv[getFile(argv, argv_length)]);
    } else if (argv_length == 2) {
      argv[2] = "-c";
      argv[3] = "-l";
      argv[4] = "-w";
      printOptions(argv, argv_length + 3, file_pointer);
      printf("%s\n", argv[getFile(argv, argv_length)]);
    }

    if (indexOf(argv, argv_length, "-m") == -1) {
      fclose(file_pointer);
    }
  } else {
    FILE *ftmp;
    ftmp = fopen("/tmp/ccwctmp.txt", "w+");
    char ch;
    while ((ch = fgetc(stdin)) != EOF) {
      fputc(ch, ftmp);
    }
    rewind(ftmp);
    if (argv_length == 1) {
      int bytes = countBytes(ftmp);
      rewind(ftmp);
      int lines = countLines(ftmp);
      rewind(ftmp);
      int words = countWords(ftmp);

      printf("\t%d\t%d\t%d\n", bytes, lines, words);
      fclose(ftmp);
    } else if (argv_length > 1) {
      PrintPipeOptions(argv, argv_length, ftmp);
    }
  }
  return 0;
}
