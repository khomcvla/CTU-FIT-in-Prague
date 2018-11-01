
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;
//==================================================================================================
class Graph
{
public:
  //------------------------------------------------
  void create_graph();
  //------------------------------------------------
  void read_numbers();
  //------------------------------------------------
  void read_commodities();
  //------------------------------------------------
  void read_connections();
  //------------------------------------------------
  void find_graph_result();
  //------------------------------------------------

private:
  //------------------------------------------------
  class Vertex
  {
  public:
    //----------------------------
    void add_neighbour(Vertex *neighbour);
    //----------------------------
    void find_vertex_result();
    //----------------------------

    unsigned long long _productType;

    bool _isVisited;
    unsigned long long _distance;

    vector<Vertex *> _vectorNeigbours;
    map<unsigned long long, unsigned long long> _mapAllProductsAtThisPoint;
  };

  //------------------------------------------------

  unsigned long long _N, _M;
  unsigned long long _P, _Q;

  vector<Vertex> _vectorVerticies;
};
//--------------------------------------------------------------------------------------------------
void Graph::create_graph()
{
  read_numbers();
  read_commodities();
  read_connections();

  find_graph_result();
}
//--------------------------------------------------------------------------------------------------
void Graph::read_numbers()
{
  cin >> _N >> _M >> _P >> _Q;
  _vectorVerticies.resize(_N);
}
//--------------------------------------------------------------------------------------------------
void Graph::read_commodities()
{
  for (unsigned long long i = 0; i < _N; i++)
  {
    cin >> _vectorVerticies[i]._productType;
    _vectorVerticies[i]._mapAllProductsAtThisPoint.emplace(_vectorVerticies[i]._productType, 0);
  }
}
//--------------------------------------------------------------------------------------------------
void Graph::read_connections()
{
  unsigned long long vertex;
  unsigned long long neighbour;

  for (unsigned long long i = 0; i < _M; i++)
  {
    cin >> vertex >> neighbour;
    _vectorVerticies[vertex].add_neighbour(&_vectorVerticies[neighbour]);
    _vectorVerticies[neighbour].add_neighbour(&_vectorVerticies[vertex]);
  }
}
//--------------------------------------------------------------------------------------------------
void Graph::find_graph_result()
{
  unsigned long long max = 0;
  unsigned long long allMax = 0;
  ostringstream oneStr;
  ostringstream allStr;

  for (unsigned long long i = 0; i < _N; i++)
  {
    //------------------------------------------------
    for (unsigned long long j = 0; j < _N; j++)
      _vectorVerticies[j]._isVisited = false;

    //------------------------------------------------
    // start BFS on this vertex
    _vectorVerticies[i].find_vertex_result();

    //------------------------------------------------
    //create sorted result vector
    vector<pair<unsigned long long, unsigned long long>> vectorTmp;
    for (auto &x : _vectorVerticies[i]._mapAllProductsAtThisPoint)
      vectorTmp.push_back(make_pair(x.first, x.second));

    sort(vectorTmp.begin(), vectorTmp.end(), [](auto &a, auto &b) { return a.second < b.second; });

    //------------------------------------------------
    // construct an output string
    max = 0;
    oneStr.clear();
    oneStr.str("");
    for (unsigned long long i = 0; i < _Q; i++)
    {
      max += vectorTmp[i].second;
      oneStr << ' ' << vectorTmp[i].first;
    }

    allMax += max;
    allStr << to_string(max) << oneStr.str() << '\n';
  }

  cout << allMax << '\n'
       << allStr.str();
}
//--------------------------------------------------------------------------------------------------
void Graph::Vertex::add_neighbour(Vertex *neighbour)
{
  _vectorNeigbours.push_back(neighbour);
}
//--------------------------------------------------------------------------------------------------
void Graph::Vertex::find_vertex_result()
{
  _isVisited = true;
  _distance = 0;

  queue<Vertex *> queue;
  queue.push(this);

  while (!queue.empty())
  {
    auto *ptr = queue.front();
    queue.pop();

    for (auto &x : ptr->_vectorNeigbours)
    {
      if (x->_isVisited == false)
      {
        x->_isVisited = true;
        x->_distance = ptr->_distance + 1;

        auto iter = this->_mapAllProductsAtThisPoint.find(x->_productType);

        if (iter == this->_mapAllProductsAtThisPoint.end())
        {
          this->_mapAllProductsAtThisPoint.emplace(x->_productType, x->_distance);
        }
        else
        {
          if (iter->second > x->_distance)
            iter->second = x->_distance;
        }

        queue.push(x);
      }
    }
  }
}
//==================================================================================================
int main(void)
{
  Graph g;
  g.create_graph();

  return 0;
}