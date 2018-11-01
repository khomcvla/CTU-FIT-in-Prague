#include <stdio.h>
#include <stdlib.h>

//Potrebujeme pro porovnani mezi hodnotami, vetsinou pro porovnani s NULOU
#define COMPARATOR 1e-8

//=================================================================================================
void Counter(double *material, double *sail, int *answer)
{
  while (*material > COMPARATOR && *sail > 0)
  {
    *material = *material - *sail;
    (*answer)++;
  }
}

//=================================================================================================
int main(int argc, char *argv[])
{
  double latka_v, latka_s;
  double plachta_v, plachta_s;
  double prekryv;

  double vertikal, vertikal_L, vertikal_R;
  double horizontal, horizontal_L, horizontal_R;

  double answer;

  int vertikal_L_answer = 0;
  int vertikal_R_answer = 0;
  int horizontal_L_answer = 0;
  int horizontal_R_answer = 0;

  //------------------------------------------------
  //Latka
  printf("Velikost latky:\n");
  if (scanf("%lf %lf", &latka_s, &latka_v) != 2 || (latka_v <= 0 || latka_s <= 0))
  {
    printf("Nespravny vstup.\n");
    return 1;
  }

  //------------------------------------------------
  //Plachta
  printf("Velikost plachty:\n");
  if (scanf("%lf %lf", &plachta_v, &plachta_s) != 2 || (plachta_v <= 0 || plachta_s <= 0))
  {
    printf("Nespravny vstup.\n");
    return 1;
  }
  else if ((latka_s >= plachta_s && latka_v >= plachta_v) || (latka_s >= plachta_v && latka_v >= plachta_s))
  {
    printf("Pocet kusu latky: 1\n");
    return 1;
  }

  //------------------------------------------------
  //Prekryv
  printf("Prekryv:\n");
  if (scanf("%lf", &prekryv) != 1 || prekryv < 0)
  {
    printf("Nespravny vstup.\n");
    return 1;
  }
  else if (latka_s <= prekryv && latka_v <= prekryv)
  {
    printf("Nelze vyrobit.\n");
    return 1;
  }

  //------------------------------------------------
  //Pokud vsechno je spravne, pak odcitame prvni celou latku bez prekryvu
  horizontal_L = (plachta_s - latka_s);
  horizontal_L_answer++;

  horizontal_R = (plachta_v - latka_v);
  horizontal_R_answer++;

  vertikal_L = (plachta_v - latka_s);
  vertikal_L_answer++;

  vertikal_R = (plachta_s - latka_v);
  vertikal_R_answer++;

  //------------------------------------------------
  //Dal budeme pocitat celkovy pocet latek vcetne prekryvu
  latka_s -= prekryv;
  latka_v -= prekryv;

  //------------------------------------------------
  //Celkovy pocet latek
  Counter(&horizontal_L, &latka_s, &horizontal_L_answer);
  Counter(&horizontal_R, &latka_v, &horizontal_R_answer);
  Counter(&vertikal_L, &latka_s, &vertikal_L_answer);
  Counter(&vertikal_R, &latka_v, &vertikal_R_answer);

  //------------------------------------------------
  //Odpoved
  if (horizontal_L > COMPARATOR || horizontal_R > COMPARATOR)
  {
    if (vertikal_L <= COMPARATOR && vertikal_R <= COMPARATOR)
      answer = vertikal_L_answer * vertikal_R_answer;
    else
      answer = vertikal_L_answer * vertikal_R_answer - 1;
  }
  else if (vertikal_L > COMPARATOR || vertikal_R > COMPARATOR)
  {
    if (horizontal_L <= COMPARATOR && horizontal_R <= COMPARATOR)
      answer = horizontal_L * horizontal_R;
    else
      answer = horizontal_L_answer * horizontal_R_answer - 1;
  }
  else
  {
    horizontal = horizontal_L_answer * horizontal_R_answer;
    vertikal = vertikal_L_answer * vertikal_R_answer;
    answer = horizontal < vertikal ? horizontal : vertikal;
  }

  printf("Pocet kusu latky: %d\n", (int)answer);

  return 0;
}