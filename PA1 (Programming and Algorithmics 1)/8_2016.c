#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//=================================================================================================
typedef struct TSoldier
{
    struct TSoldier   * m_Next;
    int                 m_PersonalID;
    char                m_SecretRecord[64];
} TSOLDIER;

#endif /* __PROGTEST__ */

//=================================================================================================
void error() {
    printf("Nespravny vstup/vystup.\n");
    exit(0);
}

//=================================================================================================
TSOLDIER         * mergePlatoons                           ( TSOLDIER        * p1,
                                                             TSOLDIER        * p2 )
{

  TSOLDIER* tmp = NULL;
  TSOLDIER* head = p1;

  if (p1 == NULL && p2 == NULL)
    return NULL;
  else if (p1 == NULL)
    return p2;
  else if (p2 == NULL)
    return p1;

  int cnt;
  cnt = 0;

  for (;;) {

    if (p1->m_Next == NULL) {
      if (cnt == 0) {
        p1->m_Next = p2;
        break;
      }
      tmp = p2->m_Next;
      p2->m_Next = p1;
      p1->m_Next = tmp;
      break;
    }

    if (p2->m_Next == NULL) {
      tmp = p1->m_Next;
      p1->m_Next = p2;
      p2->m_Next = tmp;
      break;
    }

    switch (cnt) {
    case 0: {
      tmp = p1->m_Next;
      p1->m_Next = p2;
      p1 = tmp;
      cnt = 1;
    }
    case 1: {
      tmp = p2->m_Next;
      p2->m_Next = p1;
      p2 = tmp;
      cnt = 0;
    }
    }
  }

  return head;
}

//=================================================================================================
void               splitPlatoon                            ( TSOLDIER        * src, 
                                                             TSOLDIER       ** p1,
                                                             TSOLDIER       ** p2 )
{
  TSOLDIER* tmp = src;
  TSOLDIER* cur;

  int length;
  length = 0;

  for (;;) {
    if (tmp == NULL)
      break;
    length++;
    tmp = tmp->m_Next;
  }

  if (length % 2 == 1 && floor(length / 2) > 1) {
    tmp = src;
    cur = NULL;

    for (;;) {
      if (tmp->m_Next == NULL)
        break;
      cur = tmp;
      tmp = tmp->m_Next;
    }

    free(cur->m_Next);
    cur->m_Next = NULL;
  }

  //-----------------------------------
  int cntA = 0;
  TSOLDIER A;
  TSOLDIER* endA = &A;
  cur = src;
  A.m_Next = NULL;

  for (;;) {
    if (cntA == floor(length / 2))
      break;
    tmp = cur;
    cur = tmp->m_Next;
    tmp->m_Next = endA->m_Next;
    endA->m_Next = tmp;
    endA = endA->m_Next;
    cntA++;
  }
  *p1 = A.m_Next;

  //-----------------------------------
  int cntB = 0;
  TSOLDIER B;
  TSOLDIER* endB = &B;
  B.m_Next = NULL;

  for (;;) {
    if (cntB == floor(length / 2))
      break;
    tmp = cur;
    cur = tmp->m_Next;
    tmp->m_Next = endB->m_Next;
    endB->m_Next = tmp;
    endB = endB->m_Next;
    cntB++;
  }
  *p2 = B.m_Next;
}

//=================================================================================================
void               destroyPlatoon                          ( TSOLDIER        * src )
{
  TSOLDIER* tmp = src;
  TSOLDIER* tmp_next;
  int cnt;
  cnt = 0;
  for (;;) {
    if (tmp == NULL)
      break;
    tmp_next = tmp->m_Next;
    free(tmp);
    tmp = tmp_next;
  }
}

//=================================================================================================
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{

}
#endif /* __PROGTEST__ */
