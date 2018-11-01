#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=================================================================================================
typedef struct
{
  int* massiv;
  int number;
  int length;
  int max_length;
  int bylo;
} STRUCT;

//=================================================================================================
int main(int argc, char* argv[])
{
  STRUCT* array = NULL;

  int N = 0, buffer_int = -1, control;
  char L_Z, R_Z, DVT, flag;

  //------------------------------------------------
  printf("Zpravy:\n");
  while (1) {

    control = (scanf(" %d", &buffer_int));

    if (control == EOF)
      break;

    //Wrong input #1
    if (control != 1 || buffer_int < 0) {
      printf("Nespravny vstup.\n");
      for (int i = 0; i < N; i++)
        free(array[i].massiv);
      free(array);
      return 0;
    }
    //Wrong input #2
    if (scanf(" %c", &DVT) != 1 || DVT != ':') {
      printf("Nespravny vstup.\n");
      for (int i = 0; i < N; i++)
        free(array[i].massiv);
      free(array);
      return 0;
    }
    //Wrong input #3
    if (scanf(" %c", &L_Z) != 1 || L_Z != '[') {
      printf("Nespravny vstup.\n");
      for (int i = 0; i < N; i++)
        free(array[i].massiv);
      free(array);
      return 0;
    }

    flag = 0;
    for (int i = 0; i < N; i++) {
      if (buffer_int == array[i].number) {
        do {
          if (scanf(" %d %c", &array[i].massiv[array[i].length], &R_Z) != 2 || (R_Z != ',' && R_Z != ']')) {
            printf("Nespravny vstup.\n");
            for (int j = 0; j < N; j++)
              free(array[j].massiv);
            free(array);
            return 0;
          }

          array[i].length++;
          if (array[i].length > array[i].max_length) {
            array[i].max_length *= 2;
            array[i].massiv = (int*)realloc(array[i].massiv, array[i].max_length * sizeof(int));
          }

        } while (R_Z != ']');

        flag = 1;
        break;
      }
    }

    if (flag == 0) {

      N++;
      // +1 STRUCT
      array = (STRUCT*)realloc(array, N * sizeof(STRUCT));

      // malloc first 20 elements
      array[N - 1].max_length = 20;
      array[N - 1].length = 0;
      array[N - 1].massiv = (int*)malloc(array[N - 1].max_length * sizeof(int));
      array[N - 1].number = buffer_int;
      array[N - 1].bylo = 0;

      do {
        if (scanf(" %d %c", &array[N - 1].massiv[array[N - 1].length], &R_Z) != 2 || (R_Z != ',' && R_Z != ']')) {
          printf("Nespravny vstup.\n");

          for (int i = 0; i < N; i++)
            free(array[i].massiv);
          free(array);

          return 0;
        }

        array[N - 1].length++;

        if (array[N - 1].length > array[N - 1].max_length) {
          array[N - 1].max_length *= 2;
          array[N - 1].massiv = (int*)realloc(array[N - 1].massiv, array[N - 1].max_length * sizeof(int));
        }
      } while (R_Z != ']');
    }
  }

  //------------------------------------------------
  printf("Unikatni zpravy:\n");
  for (int c = 0; c < N; c++) {

    if (array[c].bylo == 0) {
      int buffer = array[c].length;

      while (buffer) {
        for (int k = c; k < N; k++) {

          int test = 0;

          if (array[k].length == array[c].length) {
            for (int p = 0; p < array[k].length; p++)
              if (array[c].massiv[p] != array[k].massiv[p])
                test++;

            if (test == 0 && array[k].bylo == 0) {
              if (k != c)
                printf(", %d", array[k].number);
              else
                printf("%d", array[k].number);

              array[k].bylo = 1;
            }
          }
        }

        int tmp = array[c].massiv[array[c].length - 1];
        for (int i = array[c].length - 1; i > 0; i--)
          array[c].massiv[i] = array[c].massiv[i - 1];
        array[c].massiv[0] = tmp;
        buffer--;
      }
      printf("\n");
      free(array[c].massiv);
    } else
      free(array[c].massiv);
  }

  free(array);
  return 0;
}