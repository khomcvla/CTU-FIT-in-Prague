#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

// enable only if your implementation supports Add ( ) with more than three parameters
#define MULTIPLE_STOPS
template <typename _T, typename _E>
class CAccess;

//=================================================================================================
template <typename _T, typename _E>
class CRelation
{
  public:
    //---------------------------------------------------------------------------------------------
                              CRelation                             ( void ){};
    //---------------------------------------------------------------------------------------------
    CRelation<_T,_E>        & Add                                   ( const _E   type,
                                                                      const _T & station2 );
    //---------------------------------------------------------------------------------------------
    void                      AddType                               ( const _E type );
    //---------------------------------------------------------------------------------------------

  private:
    
    friend CAccess<_T, _E>;

    map<_T, vector<_E>>       m_map_station_type;  
};
//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
CRelation<_T, _E>           & CRelation<_T, _E>::Add                ( const _E   type,  
                                                                      const _T & station2 )
{
  // searching if @station2 already exists in relations
  auto iter_station = m_map_station_type.find(station2);
  if (iter_station == m_map_station_type.end()) { // if doesn't exist

    vector<_E> vector_type;
    vector_type.push_back(type);

    m_map_station_type.insert(make_pair(station2, vector_type));
  } else {

    iter_station->second.push_back(type);
  }

  return *this;
}
//=================================================================================================
template <typename _T, typename _E>
class CAccess
{
  public:
    //---------------------------------------------------------------------------------------------
                              CAccess                               ( void ){};
    //---------------------------------------------------------------------------------------------
                             ~CAccess                               ( void );
    //---------------------------------------------------------------------------------------------
    template <typename ... _Trest>
    CAccess<_T, _E>         & Add                                   ( const _E           type,
                                                                      const _Trest & ... stations ); 
    //---------------------------------------------------------------------------------------------
    map<_T, int>              Find                                  ( const _T & station1 ) const;
    //---------------------------------------------------------------------------------------------
    map<_T, int>              Find                                  ( const _T  & station1, 
                                                                      int         range ) const;
    //---------------------------------------------------------------------------------------------
    template <typename _F>
    map<_T, int>              Find                                  ( const _T  & station1, 
                                                                      int         range,
                                                                      const _F    filter ) const;
    //---------------------------------------------------------------------------------------------

  private:
    //---------------------------------------------------------------------------------------------
    void                      excepStation                          ( const _T & station ) const;
    //---------------------------------------------------------------------------------------------

    friend CRelation<_T, _E>;

    mutable map<_T, CRelation<_T, _E>* >      m_map_station_relation;

    mutable queue<_T>                         m_queue_station;
    mutable map<_T, int>                      m_map_station_range;
    mutable set<_T>                           m_map_station_visited;
};             
//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
                              CAccess<_T, _E>::~CAccess             ( void )
{
  for (auto i : m_map_station_relation)
    delete i.second;
}
//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
template <typename ... _Trest>
CAccess<_T, _E>             & CAccess<_T, _E>::Add                  ( const _E           type,
                                                                      const _Trest & ... stations)
{
  auto num_stations = sizeof...(stations);
  vector<_T> all_stations = { stations... };

  for (unsigned i = 0; i < num_stations; i++) {

    for (unsigned j = i + 1; j < num_stations; j++) {

      //--------------------------------------
      // searching for existing @station1
      auto iter_station1 = m_map_station_relation.find(all_stations[i]);
      if (iter_station1 == m_map_station_relation.end()) { // if @station1 doesn't exist

        // creating relation for @station1
        CRelation<_T, _E>* ptr_relation1 = new CRelation<_T, _E>();
        ptr_relation1->Add(type, all_stations[j]);
        // and add to the @station1 @station2 with connection @type
        m_map_station_relation.insert(make_pair(all_stations[i], ptr_relation1));

      } else {

        iter_station1->second->Add(type, all_stations[j]);
      }

      //--------------------------------------
      // searching for existing @station2
      auto iter_station2 = m_map_station_relation.find(all_stations[j]);
      if (iter_station2 == m_map_station_relation.end()) { // if @station2 doesn't exist

        // creating relation for @station2
        CRelation<_T, _E>* ptr_relation2 = new CRelation<_T, _E>();
        ptr_relation2->Add(type, all_stations[i]);
        // and add to the @station2 @station1 with connection @type
        m_map_station_relation.insert(make_pair(all_stations[j], ptr_relation2));

      } else {

        iter_station2->second->Add(type, all_stations[i]);
      }
    }
  }

  return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
map<_T, int>                  CAccess<_T, _E>::Find                 ( const _T & station ) const
{
  //--------------------------------------
  // if @station1 doesn't exist just throw exception
  auto iter_station = m_map_station_relation.find(station);
  // if @station1 doesn't exist just throw the exception
  if (iter_station == m_map_station_relation.end())
    excepStation(station);

  //--------------------------------------
  // BFS

  // preparing maps
  m_map_station_range.clear();
  m_map_station_visited.clear();

  // insert starting vertex to the queue
  m_queue_station.push(station);
  m_map_station_range.insert(make_pair(station, 0));

  while (m_queue_station.empty() != true) {

    auto iter_visited = m_map_station_visited.find(m_queue_station.front()); // check if @station is already closed

    if (iter_visited == m_map_station_visited.end()) { // if @station is not closed

      // find all @station neighbours and add their to the queue
      auto iter_station = m_map_station_relation.find(m_queue_station.front());
      for (auto& i : iter_station->second->m_map_station_type) {
        m_map_station_range.insert(make_pair(i.first, m_map_station_range[m_queue_station.front()] + 1));
        m_queue_station.push(i.first);
      }

      m_map_station_visited.insert(m_queue_station.front());
    }

    m_queue_station.pop();
  }

  return m_map_station_range;
}
//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
map<_T, int>                  CAccess<_T, _E>::Find                 ( const _T  & station, 
                                                                      int         range ) const
{
  //--------------------------------------
  // if @station1 doesn't exist just throw exception
  auto iter_station = m_map_station_relation.find(station);
  // if @station1 doesn't exist just throw the exception
  if (iter_station == m_map_station_relation.end())
    excepStation(station);

  //--------------------------------------
  // BFS

  // preparing maps
  m_map_station_range.clear();
  m_map_station_visited.clear();

  // insert starting vertex to the queue
  m_queue_station.push(station);
  m_map_station_range.insert(make_pair(station, 0));

  while (m_queue_station.empty() != true) {

    if (m_map_station_range[m_queue_station.front()] + 1 > range) {
      m_queue_station.pop();
      continue;
    }

    auto iter_visited = m_map_station_visited.find(m_queue_station.front()); // check if @station is already closed

    if (iter_visited == m_map_station_visited.end()) { // if @station is not closed

      // find all @station neighbours and add their to the queue
      auto iter_station = m_map_station_relation.find(m_queue_station.front());
      for (auto& i : iter_station->second->m_map_station_type) {
        m_map_station_range.insert(make_pair(i.first, m_map_station_range[m_queue_station.front()] + 1));
        m_queue_station.push(i.first);
      }

      m_map_station_visited.insert(m_queue_station.front());
    }

    m_queue_station.pop();
  }

  return m_map_station_range;
}
//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
template <typename _F>
map<_T, int>                  CAccess<_T, _E>::Find                 ( const _T  & station, 
                                                                      int         range,
                                                                      const _F    filter ) const
{
  map<_T, int> tmp_map_station_int;

  //--------------------------------------
  // if @station1 doesn't exist just throw exception
  auto iter_station = m_map_station_relation.find(station);
  // if @station1 doesn't exist just throw the exception
  if (iter_station == m_map_station_relation.end())
    excepStation(station);

  //--------------------------------------
  // BFS

  // preparing maps
  m_map_station_range.clear();
  m_map_station_visited.clear();

  // insert starting vertex to the queue
  m_queue_station.push(station);
  m_map_station_range.insert(make_pair(station, 0));

  while (m_queue_station.empty() != true) {

    if (m_map_station_range[m_queue_station.front()] + 1 > range) {
      m_queue_station.pop();
      continue;
    }

    auto iter_visited = m_map_station_visited.find(m_queue_station.front()); // check if @station is already closed

    if (iter_visited == m_map_station_visited.end()) { // if @station is not closed

      // find all @station neighbours and add their to the queue
      auto iter_station = m_map_station_relation.find(m_queue_station.front());
      for (auto& i : iter_station->second->m_map_station_type) {

        // checking filter
        bool filtred = false;
        for (auto& j : i.second) {
          if (filter(j) == true) {
            filtred = true;
            break;
          }
        }

        if (filtred == true) {
          m_map_station_range.insert(make_pair(i.first, m_map_station_range[m_queue_station.front()] + 1));
          m_queue_station.push(i.first);
        }
      }

      m_map_station_visited.insert(m_queue_station.front());
    }

    m_queue_station.pop();
  }

  return m_map_station_range;
}
//-------------------------------------------------------------------------------------------------
template <typename _T, typename _E>
void                          CAccess<_T, _E>::excepStation         ( const _T & station ) const
{
  ostringstream oss;
  oss << station;
  throw invalid_argument("unknown " + oss.str());
}
//=================================================================================================
#ifndef __PROGTEST__
class CTrain
{
  public:
                              CTrain                                ( const string & company, 
                                                                      int            speed )
                              : m_Company ( company ), 
                                m_Speed ( speed ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    string                    m_Company;
    int                       m_Speed; 
};
//=================================================================================================
class TrainFilterCompany
{
  public:
                              TrainFilterCompany                    ( const set<string> & companies ) 
                              : m_Companies ( companies ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                      operator ()                           ( const CTrain & train ) const
    { 
      return m_Companies . find ( train . m_Company ) != m_Companies . end (); 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    set <string>              m_Companies;    
};
//=================================================================================================
class TrainFilterSpeed
{
  public:
                              TrainFilterSpeed                      ( int min, 
                                                                      int max )
                              : m_Min ( min ), 
                                m_Max ( max ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                      operator ()                           ( const CTrain & train ) const
    {
      return train.m_Speed >= m_Min && train.m_Speed <= m_Max;
    }
    //---------------------------------------------------------------------------------------------
  private:  
    int                       m_Min;
    int                       m_Max; 
};
//=================================================================================================
bool                          NurSchnellzug                         ( const CTrain & zug )
{
  return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
int                           main                                  ( void )
{
  CAccess<string,CTrain> lines;
  lines . Add ( CTrain (   "DB", 120 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "CD",  80 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "DB", 160 ), "Berlin", "Dresden"  )
        . Add ( CTrain (   "DB", 160 ), "Dresden", "Munchen" )
        . Add ( CTrain (   "CD",  90 ), "Munchen", "Prague"  )
        . Add ( CTrain (   "DB", 200 ), "Munchen", "Linz"    )
        . Add ( CTrain (  "OBB",  90 ), "Munchen", "Linz"    )
        . Add ( CTrain (   "CD",  50 ), "Linz", "Prague"     )
        . Add ( CTrain (   "CD", 100 ), "Prague", "Wien"     )
        . Add ( CTrain (  "OBB", 160 ), "Linz", "Wien"       )
        . Add ( CTrain ( "SNCF", 300 ), "Paris", "Marseille" )
        . Add ( CTrain ( "SNCF", 250 ), "Paris", "Dresden"   )
        . Add ( CTrain ( "SNCF", 200 ), "London", "Calais"   );

  assert ( lines . Find ( "Berlin" ) == (map<string,int>
  {
    make_pair ( "Berlin", 0 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Marseille", 3 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "London" ) == (map<string,int>
  {
    make_pair ( "Calais", 1 ),
    make_pair ( "London", 0 )
  }) );
  assert ( lines . Find ( "Wien" ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Marseille", 5 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Wien", 3 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Wien", 5, NurSchnellzug ) == (map<string,int>
  {
    make_pair ( "Berlin", 4 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Prague", 3,  TrainFilterCompany ( { "CD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 1 ),
    make_pair ( "Dresden", 2 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 1 ),
    make_pair ( "Prague", 0 ),
    make_pair ( "Wien", 1 )
  }) );
  assert ( lines . Find ( "Munchen", 4, TrainFilterSpeed ( 160, 250 ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Munchen", 4, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "London", 20, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "London", 0 )
  }) );
  try
  {
     auto res = lines . Find ( "Salzburg" );
     assert ( "No exception thrown" == NULL );
  }
  catch ( const invalid_argument & e )
  {
    assert ( string ( e . what () ) == "unknown Salzburg" );
  }
#ifdef MULTIPLE_STOPS
  lines . Add ( CTrain ( "RZD",  80 ), "Prague", "Kiev", "Moscow", "Omsk", "Irkutsk", "Vladivostok" );
  lines . Add ( CTrain ( "LAV", 160 ), "Malaga", "Cordoba", "Toledo", "Madrid", "Zaragoza", "Tarragona", "Barcelona", "Montpellier", "Marseille" );
  assert ( lines . Find ( "Madrid" ) == (map<string,int>
  {
    make_pair ( "Barcelona", 1 ),
    make_pair ( "Berlin", 4 ),
    make_pair ( "Cordoba", 1 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 6 ),
    make_pair ( "Kiev", 6 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Madrid", 0 ),
    make_pair ( "Malaga", 1 ),
    make_pair ( "Marseille", 1 ),
    make_pair ( "Montpellier", 1 ),
    make_pair ( "Moscow", 6 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 6 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Tarragona", 1 ),
    make_pair ( "Toledo", 1 ),
    make_pair ( "Vladivostok", 6 ),
    make_pair ( "Wien", 6 ),
    make_pair ( "Zaragoza", 1 )
  }) );
  assert ( lines . Find ( "Omsk", 4 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Moscow", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Omsk", 0 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Moscow", 10, TrainFilterCompany ( { "RZD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Moscow", 0 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 1 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 )
  }) );
#endif /* MULTIPLE_STOPS */
  return 0;
}
#endif  /* __PROGTEST__ */