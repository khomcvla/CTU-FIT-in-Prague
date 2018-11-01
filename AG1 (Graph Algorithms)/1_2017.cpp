#include <iostream>

using namespace std;

//=====================================================================================================================
class Graph {

  public:

                                Graph                            (const unsigned long int cnt);
                               ~Graph                            ();

    void                        fillTime                         ();
    void                        fillHeir                         ();
    void                        findLeastTime                    ();

  private:

    struct TNode {

                                TNode                            ();

      void                      findVertexTime                   (unsigned long int *max, Graph *G);
      void                      checkCycle                       (Graph *G);

      TNode                  ** m_THeir = 0;
      unsigned long int         m_Time = 0;
      unsigned long int         m_Start = 0;

      bool                      m_Visited = 0;
      unsigned long int         m_NumberVertex = 0;
      unsigned long int         m_CntHeirs = 0; 

      bool                      m_WHITE = 0; // for checking cycle 1
      bool                      m_GRAY = 0;  // for checking cycle 2
      bool                      m_BLACK = 0; // for checking cycle 3
    };

    TNode                     * m_TArray = 0;
    unsigned long int           m_CntElements = 0;
    unsigned long int           m_Max = 0;
};
//---------------------------------------------------------------------------------------------------------------------
                                Graph::Graph                     (const unsigned long int cnt)
                              : m_TArray(NULL),
                                m_CntElements (cnt),
                                m_Max(0)
{

  m_TArray = new TNode[m_CntElements];
}
//---------------------------------------------------------------------------------------------------------------------
                                Graph::~Graph                    ()
{
  for (unsigned long int i = 0; i < m_CntElements; i++) {
    delete[] m_TArray[i].m_THeir;
  }
  delete [] m_TArray;
}
//---------------------------------------------------------------------------------------------------------------------
                                Graph::TNode::TNode              ()
                              : m_THeir(NULL),
                                m_Start(0),
                                m_WHITE(true)
{
}
//---------------------------------------------------------------------------------------------------------------------
void                            Graph::fillTime                  ()
{
  for (unsigned long int i = 0; i < m_CntElements; i++) {
    cin >> m_TArray[i].m_Time;

    if (m_TArray[i].m_Time <= 0) {
      printf("No solution.\n");
      this->~Graph();
      exit(0);
    }

    m_TArray[i].m_NumberVertex = i;
  }
}
//---------------------------------------------------------------------------------------------------------------------
void                            Graph::fillHeir                  ()
{
  unsigned long int cntHeirs;
  unsigned long int heir;

  for (unsigned long int i = 0; i < m_CntElements; i++) {

    cin >> cntHeirs;

    if (cntHeirs != 0) {

      m_TArray[i].m_THeir = new TNode*[cntHeirs];
      m_TArray[i].m_CntHeirs = cntHeirs;

      for (unsigned long int j = 0; j < cntHeirs; j++) {
        cin >> heir;
        m_TArray[i].m_THeir[j] = &(m_TArray[heir]);
      }
    }
  }
}
//---------------------------------------------------------------------------------------------------------------------
void                            Graph::TNode::findVertexTime     (unsigned long int *max, Graph *G)
{
  m_Visited = true;

  for (unsigned long int i = 0; i < m_CntHeirs; i++) {

    if (m_THeir[i]->m_Visited == false)
      m_THeir[i]->findVertexTime(max, G);

    if (m_Start < (m_THeir[i]->m_Start + m_THeir[i]->m_Time)) // выбираем самую "дорогую" грань
      m_Start = m_THeir[i]->m_Start + m_THeir[i]->m_Time;

  }

  if ((*max) < m_Start + m_Time) // попутно собираем информацию о самой поздней детали
    (*max) = m_Start + m_Time;
}
//---------------------------------------------------------------------------------------------------------------------
void                            Graph::TNode::checkCycle         (Graph *G)
{
  if (m_BLACK == false) {
    if (m_GRAY == true) {
      printf("No solution.\n");
      G->~Graph();
      exit(0);

    } else if (m_WHITE == true) {
      m_GRAY = true;
      for (unsigned long int i = 0; i < m_CntHeirs; i++)
        m_THeir[i]->checkCycle(G);

    }

    m_BLACK = true;
  }
}
//---------------------------------------------------------------------------------------------------------------------
void                            Graph::findLeastTime             ()
{
  for (unsigned long int i = 0; i < m_CntElements; i++)
    m_TArray[i].checkCycle(this);

  for (unsigned long int i = 0; i < m_CntElements; i++)
    m_TArray[i].findVertexTime(&m_Max, this);

  printf("%lu\n", m_Max);
  for (unsigned long int i = 0; i < m_CntElements; i++)
    printf("%lu ", m_TArray[i].m_Start);
  printf("\n");
}
//=====================================================================================================================
int main (void) {

  unsigned long int V;
  cin >> V;

  Graph G(V);
  G.fillTime();
  G.fillHeir();
  G.findLeastTime();

  return 0;
}
