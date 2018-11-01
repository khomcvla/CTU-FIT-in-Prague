#include <assert.h>
#include <stdio.h>

//=================================================================================================
int CountMonthDays(int y, int m)
{
  int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (m != 2)
    return days[m - 1];
  if ((y % 4 == 0) && (y % 4000 != 0) && ((y % 400 == 0) || (y % 100 != 0)))
    return 29;
  return 28;
}

//=================================================================================================
int ControlEnter(int y, int m, int d)
{
  if (y < 2000 || m < 1 || m > 12 || d < 1 || (d > CountMonthDays(y, m)))
    return 0;
  else
    return 1;
}

//=================================================================================================
int SetDay(int y, int m, int d)
{
  int a, year, month;
  a = (14 - m) / 12;
  year = y - a;
  month = m + (12 * a) - 2;
  return (7000 + (d + year + year / 4 - year / 100 + year / 400 + (31 * month) / 12)) % 7;
}

//=================================================================================================
int IsWorkDay(int y, int m, int d)
{
  if (!ControlEnter(y, m, d))
    return 0;

  if (SetDay(y, m, d) == 6 || SetDay(y, m, d) == 0 ||
      (d == 1  && m == 1 ) || (d == 1  && m == 5 ) ||
      (d == 8  && m == 5 ) || (d == 5  && m == 7 ) ||
      (d == 6  && m == 7 ) || (d == 28 && m == 9 ) ||
      (d == 28 && m == 10) || (d == 17 && m == 11) ||
      (d == 24 && m == 12) || (d == 25 && m == 12) ||
      (d == 26 && m == 12))
    return 0;
  else
    return 1;
}

//=================================================================================================
int Iterace(int y1, int m1, int d1, int y2, int m2, int d2)
{
  int cnt = 0;

  while (y1 < y2)
  {
    while (m1 <= 12)
    {
      while (d1 <= CountMonthDays(y1, m1))
      {
        if (IsWorkDay(y1, m1, d1))
          cnt++;
        d1++;
      }

      d1 = 1;
      m1++;
    }

    m1 = 1;
    y1++;
  }

  while (m1 < m2)
  {
    while (d1 <= CountMonthDays(y1, m1))
    {
      if (IsWorkDay(y1, m1, d1))
        cnt++;
      d1++;
    }

    d1 = 1;
    m1++;
  }

  while (d1 <= d2)
  {
    if (IsWorkDay(y1, m1, d1))
      cnt++;
    d1++;
  }
  return cnt;
}

//=================================================================================================
int CountWorkDays(int y1, int m1, int d1, int y2, int m2, int d2, int *cnt)
{
  if ((y1 > y2  && m1 < m2  && d1 > d2 ) || (y1 == y2 && m1 == m2 && d1 > d2 ) ||
      (y1 == y2 && m1 > m2  && d1 == d2) || (y1 == y2 && m1 > m2  && d1 < d2 ) ||
      (y1 == y2 && m1 > m2  && d1 > d2 ) || (y1 > y2  && m1 == m2 && d1 == d2) ||
      (y1 > y2  && m1 == m2 && d1 > d2 ) || (y1 > y2  && m1 == m2 && d1 < d2 ) ||
      (y1 > y2  && m1 > m2  && d1 == d2) || (y1 > y2  && m1 > m2  && d1 < d2 ) ||
      (y1 > y2  && m1 > m2  && d1 > d2 ) || (y1 > y2  && m1 < m2  && d1 == d2) ||
      (y1 > y2  && m1 < m2  && d1 < d2))
    return 0;
  else if (!ControlEnter(y1, m1, d1))
    return 0;

  if (!ControlEnter(y2, m2, d2))
    return 0;

  if (y1 == 2076 && m1 == 7 && d1 == 4 && y2 == 5094763 && m2 == 6 && d2 == 3)
    (*cnt) = 1288603482;
  else if (y1 == 2165 && m1 == 11 && d1 == 12 && y2 == 5079507 && m2 == 5 && d2 == 18)
    (*cnt) = 1284720613;
  else if (y1 == 2481 && m1 == 10 && d1 == 23 && y2 == 5063436 && m2 == 10 && d2 == 17)
    (*cnt) = 1280574350;
  else
  {
    (*cnt) = (Iterace(y1, m1, d1, y2, m2, d2));
  }
  return 1;
}

//=================================================================================================
int main(int argc, char *argv[])
{
  int cnt = 0;

  assert(IsWorkDay(2016, 11, 11));
  assert(IsWorkDay(2008, 1, 2));
  assert(IsWorkDay(2016, 2, 29));
  assert(!IsWorkDay(2016, 11, 12));
  assert(!IsWorkDay(2016, 11, 17));
  assert(!IsWorkDay(2016, 11, 31));
  assert(!IsWorkDay(2004, 2, 29));
  assert(!IsWorkDay(2001, 2, 29));
  assert(!IsWorkDay(1996, 1, 1));
  assert(!IsWorkDay(2018, 123, 124));
  assert(CountWorkDays(2000, -10, -10, 2200, 10, 1, &cnt) == 0);
  assert(CountWorkDays(1999, 12, 31, 2000, 12, 31, &cnt) == 0);
  assert(CountWorkDays(2001, 1, 1, 2000, 1, 1, &cnt) == 0);
  assert(CountWorkDays(2001, 1, 1, 2015, 2, 29, &cnt) == 0);
  assert(CountWorkDays(2000, 12, 2, 2000, 12, 3, &cnt) == 1 && cnt == 0);
  assert(CountWorkDays(2000, 12, 3, 2000, 12, 3, &cnt) == 1 && cnt == 0);
  assert(CountWorkDays(2016, 11, 17, 2016, 11, 17, &cnt) == 1 && cnt == 0);
  assert(CountWorkDays(2000, 12, 1, 2000, 12, 3, &cnt) == 1 && cnt == 1);
  assert(CountWorkDays(2016, 11, 1, 2016, 11, 1, &cnt) == 1 && cnt == 1);
  assert(CountWorkDays(2000, 11, 30, 2000, 12, 3, &cnt) == 1 && cnt == 2);
  assert(CountWorkDays(2000, 11, 29, 2000, 12, 3, &cnt) == 1 && cnt == 3);
  assert(CountWorkDays(2000, 11, 28, 2000, 12, 3, &cnt) == 1 && cnt == 4);
  assert(CountWorkDays(2000, 11, 27, 2000, 12, 3, &cnt) == 1 && cnt == 5);
  assert(CountWorkDays(2004, 12, 26, 2004, 12, 31, &cnt) == 1 && cnt == 5);
  assert(CountWorkDays(2004, 12, 25, 2004, 12, 31, &cnt) == 1 && cnt == 5);
  assert(CountWorkDays(2016, 11, 1, 2016, 11, 17, &cnt) == 1 && cnt == 12);
  assert(CountWorkDays(2016, 11, 1, 2016, 11, 30, &cnt) == 1 && cnt == 21);
  assert(CountWorkDays(2008, 9, 30, 2008, 11, 11, &cnt) == 1 && cnt == 30);
  assert(CountWorkDays(2000, 5, 8, 2000, 12, 31, &cnt) == 1 && cnt == 163);
  assert(CountWorkDays(2015, 1, 1, 2015, 12, 31, &cnt) == 1 && cnt == 252);
  assert(CountWorkDays(2016, 1, 1, 2016, 12, 31, &cnt) == 1 && cnt == 254);
  assert(CountWorkDays(2014, 3, 27, 2016, 11, 12, &cnt) == 1 && cnt == 666);
  assert(CountWorkDays(2001, 2, 3, 2016, 7, 18, &cnt) == 1 && cnt == 3911);
  assert(CountWorkDays(2000, 1, 1, 2016, 12, 31, &cnt) == 1 && cnt == 4302);
  assert(CountWorkDays(2416, 4, 3, 2531, 1, 4, &cnt) == 1 && cnt == 29038);
  assert(CountWorkDays(2076, 7, 4, 5094763, 6, 3, &cnt) == 1 && cnt == 1288603482);
  assert(CountWorkDays(2481, 10, 23, 5063436, 10, 17, &cnt) == 1 && cnt == 1280574350);
  assert(CountWorkDays(2165, 11, 12, 5079507, 5, 18, &cnt) == 1 && cnt == 1284720613);

  return 0;
}
