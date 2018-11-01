#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

//=================================================================================================
typedef struct {
  char* letter_R;
  char* letter_NO_R;
} STRUCT;
STRUCT* array = NULL;

//=================================================================================================
int cmp(const void* a, const void* b)
{
  return strcmp(((STRUCT*)a)->letter_NO_R, ((STRUCT*)b)->letter_NO_R);
}

//=================================================================================================
int main(int argc, char* argv[])
{
  int N = 0;

  while (true) {

    N++;

    char c = fgetc(stdin);
    if (c != EOF)
      ungetc(c, stdin);
    else
      break;

    array = (STRUCT*)realloc(array, N * sizeof(STRUCT));

    size_t len;
    getline(&array[N - 1].letter_R, &len, stdin);

    if ((int)(strlen(array[N - 1].letter_R)) == 1) {
      printf("Nespravny vstup.\n");

      for (int i = 0; i < N; i++) {
        free(array[i].letter_R);
        free(array[i].letter_NO_R);
      }
      free(array);

      return 0;
    }

    for (int i = 0; i < (int)(strlen(array[N - 1].letter_R)) - 1; i++)
      if (!((array[N - 1].letter_R[i] >= 'a' && array[N - 1].letter_R[i] <= 'z') || 
            (array[N - 1].letter_R[i] >= 'A' && array[N - 1].letter_R[i] <= 'Z') || (array[N - 1].letter_R[i] == ' '))) {
        printf("Nespravny vstup.\n");

        for (int i = 0; i < N; i++) {
          free(array[i].letter_R);
          free(array[i].letter_NO_R);
        }
        free(array);

        return 0;
      }

    array[N - 1].letter_NO_R = (char*)calloc((int)(strlen(array[N - 1].letter_R)) * 2, sizeof(char));
    strcpy(array[N - 1].letter_NO_R, array[N - 1].letter_R);

    //------------------------------------------------
    //Toupper letter #R
    for (int i = 0; i < (int)(strlen(array[N - 1].letter_NO_R)) - 1; i++)
      if ('a' <= array[N - 1].letter_NO_R[i] && array[N - 1].letter_NO_R[i] <= 'z')
        array[N - 1].letter_NO_R[i] += 'A' - 'a';

    //------------------------------------------------
    for (int i = 0; i < (int)(strlen(array[N - 1].letter_NO_R)); i++) {
      if (array[N - 1].letter_NO_R[i] == 'C' && array[N - 1].letter_NO_R[i + 1] == 'H') {
        for (int j = (int)(strlen(array[N - 1].letter_NO_R)); j > i; j--)
          array[N - 1].letter_NO_R[j] = array[N - 1].letter_NO_R[j - 1];

        array[N - 1].letter_NO_R[i] = '9';
        i += 2;

      } else if (array[N - 1].letter_NO_R[i] >= 'A' && array[N - 1].letter_NO_R[i] <= 'H') {
        for (int j = (int)(strlen(array[N - 1].letter_NO_R)); j > i; j--)
          array[N - 1].letter_NO_R[j] = array[N - 1].letter_NO_R[j - 1];

        array[N - 1].letter_NO_R[i] = (char)((int)array[N - 1].letter_NO_R[i + 1] - 16);
        i += 1;
      }
    }
  }

  qsort(array, N - 1, sizeof(STRUCT), cmp);

  for (int i = 0; i < N - 1; i++)
    printf("%s", array[i].letter_R);

  for (int i = 0; i < N - 1; i++) {
    free(array[i].letter_R);
    free(array[i].letter_NO_R);
  }
  free(array);

  return 0;
}