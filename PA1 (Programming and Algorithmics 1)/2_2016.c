#include <stdio.h>
#include <stdlib.h>

//=================================================================================================
typedef struct
{
  long long int count_sum;
} STRUCT;
STRUCT *array = NULL;

//=================================================================================================
void ZERO(int N)
{
  array[N].count_sum = 0;
}

//=================================================================================================
int gcd(int a, int b)
{
  int c;
  while (b)
  {
    c = a % b;
    a = b;
    b = c;
  }
  return abs(a);
}

//=================================================================================================
int main()
{
  long long int N = 0;
  long long int all_is_zero = 0, all_is_flag = 0, all_is_simmilar = 0, vert_slesh = 0;
  long long int count_L = 0, count_R = 0, count_L_before = 0, count_R_before = 0;
  char c;

  array = (STRUCT *)realloc(array, (N + 1) * sizeof(STRUCT));
  ZERO(N);

  printf("Zpravy:\n");
  while (scanf("%c", &c) != EOF)
  {
    if ((c > 96 && c < 123) || c == '\n' || c == '|')
    {
      if (!vert_slesh)
      {
        //If we have 'ENTER' but we have no 'SLESH'
        if (c == '\n' && vert_slesh == 0)
        {
          printf("Nespravny vstup.\n");
          return 0;
        }
        else if (c == '|')
        {
          vert_slesh++;
        }
        else
        {
          if (c != '\n')
          {
            int ARC = (1 << ((int)(c)-97));
            count_L += ARC;
          }
          if (all_is_zero == 0 && (count_L == 0 || count_R == 0))
            all_is_zero++;
          else if (all_is_flag == 0 && count_L != 0 && count_R != 0)
            all_is_flag++;
        }
      }
      else
      {
        if (c == '|')
        {
          printf("Nespravny vstup.\n");
          return 0;
        }

        if (c != '\n')
        {
          int ARC = (1 << ((int)(c)-97));
          count_R += ARC;
        }

        if (N > 0 && count_L != count_L_before)
          all_is_simmilar = 1;

        if (all_is_zero == 0 && (count_L == 0 || count_R == 0))
          all_is_zero++;
        else if (all_is_flag == 0 && count_L != 0 && count_R != 0)
          all_is_flag++;

        if (c == '\n')
        {
          //If we have only slesh(|)
          if (count_L == 0 && count_R == 0)
          {
            printf("Nespravny vstup.\n");
            return 0;
          }

          array[N].count_sum = count_L + count_R;

          N++;
          array = (STRUCT *)realloc(array, (N + 1) * sizeof(STRUCT));

          ZERO(N);

          if (N > 1)
          {
            if (all_is_zero != 0 && all_is_flag == 0)
            {
              array[N - 1].count_sum = 0;
            }
            else if (all_is_simmilar == 0)
            {
              array[N - 1].count_sum = count_L;
            }
            else
            {
              //Looking for gcd
              int GCD, rozdil;
              GCD = gcd(array[N - 2].count_sum, array[N - 1].count_sum);
              rozdil = abs(count_L_before - count_L);
              if (rozdil % GCD != 0)
              {
                printf("Nelze dosahnout.\n");
                return 0;
              }

              if (N == 2)
              {
                array[N - 2].count_sum += count_L_before;
                array[N - 1].count_sum += count_L;

                //Until are not simmilar
                while (array[N - 2].count_sum != array[N - 1].count_sum)
                {
                  while (array[N - 2].count_sum < array[N - 1].count_sum)
                    array[N - 2].count_sum += (count_L_before + count_R_before);
                  while (array[N - 1].count_sum < array[N - 2].count_sum)
                    array[N - 1].count_sum += (count_L + count_R);
                }
              }
              else
              {
                array[N - 1].count_sum += count_L;

                while (array[N - 2].count_sum != array[N - 1].count_sum)
                {
                  while (array[N - 2].count_sum < array[N - 1].count_sum)
                    array[N - 2].count_sum += array[N - 2].count_sum;

                  while (array[N - 1].count_sum < array[N - 2].count_sum)
                    array[N - 1].count_sum += (count_L + count_R);
                }
              }
            }
          }

          count_L_before = count_L;
          count_R_before = count_R;
          count_L = 0;
          count_R = 0;
          vert_slesh = 0;
        }
      }
    }
    else
    {
      printf("Nespravny vstup.\n");
      return 0;
    }
  }

  if (N < 2)
  {
    printf("Nespravny vstup.\n");
    return 0;
  }

  printf("Synchronizace za: %lld\n", array[N - 1].count_sum);

  free(array);

  return 0;
}
