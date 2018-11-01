#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=================================================================================================
int main(int argv, char* argc[])
{
  static int array[2000][2000];
  int sirka, vyska, count, count_test = 0, celkem = 0;
  char string[9];

  //------------------------------------------------
  printf("Velikost mapy:\n");
  if (scanf("%d %d", &sirka, &vyska) != 2 || !(sirka > 0 && sirka <= 2000) || !(vyska > 0 && vyska <= 2000)) {
    printf("Nespravny vstup.\n");
    return 0;
  }

  //------------------------------------------------
  printf("Cenova mapa:\n");
  for (int i = 0; i < vyska; i++)
    for (int j = 0; j < sirka; j++)
      if (scanf("%d", &array[i][j]) != 1) {
        printf("Nespravny vstup.\n");
        return 0;
      }

  //------------------------------------------------
  printf("Dotazy:\n");
  while (1) {
    int control = (scanf("%10s %d", string, &count));

    if (control == EOF)
      return 0;

    if (control != 2) {
      printf("Nespravny vstup.\n");
      return 0;
    }

    if ((strcmp(string, "count") != 0) && (strcmp(string, "list") != 0)) {
      printf("Nespravny vstup.\n");
      return 0;
    }

    celkem = 0;

    for (int i = 0; i < vyska; i++)
      for (int j = 0; j < sirka; j++) {
        for (int DOWN = 0; DOWN < vyska - i; DOWN++)
          for (int RIGHT = 0; RIGHT < sirka - j; RIGHT++) {
            count_test = 0;

            for (int k = i; k <= i + DOWN; k++)
              for (int l = j; l <= j + RIGHT; l++)
                count_test += array[k][l];

            if (count_test == count && (strcmp(string, "list") == 0)) {
              printf("%d @ (%d,%d) - (%d,%d)\n", count, j, i, j + RIGHT, i + DOWN);
              celkem++;
            } else if (count_test == count && (strcmp(string, "count") == 0))
              celkem++;
          }
      }
    printf("Celkem: %d\n", celkem);
  }

  return 0;
}