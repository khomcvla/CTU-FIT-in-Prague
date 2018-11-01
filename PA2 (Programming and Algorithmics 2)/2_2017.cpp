#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */
//=====================================================================================================================
class CPersona
{
public:

              CPersona                      ( const string          & name,
                                              const string          & surname,
                                              const string          & email,
                                              const unsigned int    & salary )
  {
    name.empty()    ? m_name    = "" : m_name = name;
    surname.empty() ? m_surname = "" : m_surname = surname;
    email.empty()   ? m_email   = "" : m_email = email;
    salary == 0     ? m_salary  = 0  : m_salary = salary;
  }
  //---------------------------------------------------------------
  void            setName                   ( const string & name )
  {
    m_name = name;
  }
  //---------------------------------------------------------------
  void            setSurname                ( const string & surname )
  {
    m_surname = surname;
  }
  //---------------------------------------------------------------
  void            setEmail                  ( const string & email )
  {
    m_email = email;
  }
  //---------------------------------------------------------------
  void            setSalary                 ( unsigned int salary )
  {
    m_salary = salary;
  }
  //---------------------------------------------------------------
  string          getName                   ( void ) const
  {
    return m_name;
  }
  //---------------------------------------------------------------
  string          getSurname                ( void ) const
  {
    return m_surname;
  }
  //---------------------------------------------------------------
  string          getEmail                  ( void ) const
  {
    return m_email;
  }
  //---------------------------------------------------------------
  unsigned int    getSalary                 ( void ) const
  {
    return m_salary;
  }
  //---------------------------------------------------------------
  bool            greaterSurnameName        ( const CPersona & object) const 
  {
    if (m_surname == object.m_surname) {
      if (m_name < object.m_name)
        return true;
      else
        return false;
    }
    if (m_surname < object.m_surname)
      return true;
    return false;
  }
  //---------------------------------------------------------------
  bool            greaterEmail              ( const CPersona & object) const 
  {
    if (m_email < object.m_email)
      return true;
    else
      return false;
  }
private:

  string          m_name;
  string          m_surname;
  string          m_email;
  unsigned int    m_salary;
};
//=====================================================================================================================
class CPersonalAgenda
{
  public:
                  CPersonalAgenda  ( void ){};
                  ~CPersonalAgenda ( void ){};
    bool          Add              ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary );
    bool          Del              ( const string    & name,
                                     const string    & surname );
    bool          Del              ( const string    & email );
    bool          ChangeName       ( const string    & email,
                                     const string    & newName,
                                     const string    & newSurname );
    bool          ChangeEmail      ( const string    & name,
                                     const string    & surname,
                                     const string    & newEmail );
    bool          SetSalary        ( const string    & name,
                                     const string    & surname,
                                     unsigned int      salary );
    bool          SetSalary        ( const string    & email,
                                     unsigned int      salary );
    unsigned int  GetSalary        ( const string    & name,
                                     const string    & surname ) const;
    unsigned int  GetSalary        ( const string    & email ) const;
    bool          GetRank          ( const string    & name,
                                     const string    & surname,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetRank          ( const string    & email,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetFirst         ( string          & outName,
                                     string          & outSurname ) const;
    bool          GetNext          ( const string    & name,
                                     const string    & surname,
                                     string          & outName,
                                     string          & outSurname ) const;
    auto          GetIterator      ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary,
                                     unsigned int      choice ) const;

  private:

    // Make mutable by reason of GetIterator and const functions
    mutable vector<CPersona>::iterator  itEmail;
    mutable vector<CPersona>::iterator  itSurnameName;
    mutable vector<CPersona>            m_VectorSurnameName;
    mutable vector<CPersona>            m_VectorEmail;
};
//---------------------------------------------------------------------------------------------------------------------
auto          CPersonalAgenda::GetIterator      ( const string    & name,
                                                  const string    & surname,
                                                  const string    & email,
                                                  unsigned int      salary,
                                                  unsigned int      choice ) const
{
  if (choice == 1) {
    // Find a place for SurnameName
    itSurnameName = lower_bound(m_VectorSurnameName.begin(), m_VectorSurnameName.end(), CPersona(name, surname, email, salary),
        [&](const CPersona& lhs, const CPersona& rhs) {
          return lhs.greaterSurnameName(rhs);
        });
    return itSurnameName;
  } else {
    // Find a place for Email
    itEmail = lower_bound(m_VectorEmail.begin(), m_VectorEmail.end(), CPersona(name, surname, email, salary),
        [&](const CPersona& lhs, const CPersona& rhs) {
          return lhs.greaterEmail(rhs);
        });
    return itEmail;
  }
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::Add              ( const string    & name,
                                                  const string    & surname,
                                                  const string    & email,
                                                  unsigned int      salary )
{
  // Find a place for SurnameName
  itSurnameName = GetIterator(name, surname, email, salary, 1);

  // Find a place for Email
  itEmail = GetIterator(name, surname, email, salary, 2);

  // Check if Name and Surname already exist
  if (itSurnameName != m_VectorSurnameName.end() && itSurnameName->getName() == name && itSurnameName->getSurname() == surname)
    return false;

  // Check if Email already exist
  if (itEmail != m_VectorEmail.end() && itEmail->getEmail() == email)
    return false;

  // Insert into "m_VectorSurnameName" a new CPersona
  if (itSurnameName == m_VectorSurnameName.end())
    m_VectorSurnameName.push_back(CPersona(name, surname, email, salary));
  else
    m_VectorSurnameName.insert(itSurnameName, CPersona(name, surname, email, salary));

  // Insert into "m_VectorEmail" a new CPersona
  if (itEmail == m_VectorEmail.end())
    m_VectorEmail.push_back(CPersona(name, surname, email, salary));
  else
    m_VectorEmail.insert(itEmail, CPersona(name, surname, email, salary));

  return true;
}
//---------------------------------------------------------------------------------------------------------------------[TODO]
bool          CPersonalAgenda::Del              ( const string    & name,
                                                  const string    & surname )
{
  // Find a place for SurnameName
  itSurnameName = GetIterator(name, surname, "", 0, 1);

  // Check if person with this @name and @surname exists
  if (itSurnameName == m_VectorSurnameName.end() || itSurnameName->getName() != name || itSurnameName->getSurname() != surname)
    return false;

  // Find a place for Email
  itEmail = GetIterator("", "", itSurnameName->getEmail(), 0, 2);

  // Delete from m_VectorEmail our finded CPersona
  m_VectorEmail.erase(itEmail);

  // Delete from m_VectorSurnameName our finded CPersona
  m_VectorSurnameName.erase(itSurnameName);

  return true;
}
//---------------------------------------------------------------------------------------------------------------------[TODO]
bool          CPersonalAgenda::Del              ( const string    & email )
{
  // Find a place for Email
  itEmail = GetIterator("", "", email, 0, 2);

  // Check if person with this @email exists
  if (itEmail == m_VectorEmail.end() || itEmail->getEmail() != email)
    return false;

  // Find a place for SurnameName
  itSurnameName = GetIterator(itEmail->getName(), itEmail->getSurname(), "", 0, 1);

  // Delete from m_VectorSurnameName our finded CPersona
  m_VectorSurnameName.erase(itSurnameName);

  // Delete from m_VectorEmail our finded CPersona
  m_VectorEmail.erase(itEmail);

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::ChangeName       ( const string    & email,
                                                  const string    & newName,
                                                  const string    & newSurname )
{
  // Find an appropriate place for person with @email
  itEmail = GetIterator("", "", email, 0, 2);

  // Check if person with this @email exists
  if (itEmail == m_VectorEmail.end() || itEmail->getEmail() != email || (itEmail->getName() == newName && itEmail->getSurname() == newSurname))
    return false;

  // Find an appropriate place for person with @name and @surname
  itSurnameName = GetIterator(itEmail->getName(), itEmail->getSurname(), "", 0, 1);

  // Delete from m_VectorSurnameName our finded CPersona
  m_VectorSurnameName.erase(itSurnameName);

  // Find a new place for new CPersona into m_VectorSurnameName
  itSurnameName = GetIterator(newName, newSurname, "", 0, 1);

  if (itSurnameName->getName() == newName || itSurnameName->getSurname() == newSurname)
    return false;

  // Insert a new CPersona into m_VectorSurnameName
  if (itSurnameName == m_VectorSurnameName.end())
    m_VectorSurnameName.push_back(CPersona(newName, newSurname, email, itEmail->getSalary()));
  else
    m_VectorSurnameName.insert(itSurnameName, CPersona(newName, newSurname, email, itEmail->getSalary()));

  itEmail->setName(newName);
  itEmail->setSurname(newSurname);

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::ChangeEmail      ( const string    & name,
                                                  const string    & surname,
                                                  const string    & newEmail )
{
  // Find an appropriate place for person with @name and @surname
  itSurnameName = GetIterator(name, surname, "", 0, 1);

  // Check if person with this @name and @surname exists
  if (itSurnameName == m_VectorSurnameName.end() || itSurnameName->getName() != name || 
       itSurnameName->getSurname() != surname || itSurnameName->getEmail() == newEmail)
    return false;

  // Find an appropriate place for person with @email
  itEmail = GetIterator("", "", itSurnameName->getEmail(), 0, 2);

  // Delete from m_VectorEmail our finded CPersona
  m_VectorEmail.erase(itEmail);

  // Find a new place for new CPersona into m_VectorEmail
  itEmail = GetIterator("", "", newEmail, 0, 2);

  // If this @email already exists
  if (itEmail != m_VectorEmail.end() && itEmail->getEmail() == newEmail)
    return false;

  // Insert a new CPersona into m_VectorEmail
  if (itEmail == m_VectorEmail.end())
    m_VectorEmail.push_back(CPersona(name, surname, newEmail, itSurnameName->getSalary()));
  else
    m_VectorEmail.insert(itEmail, CPersona(name, surname, newEmail, itSurnameName->getSalary()));

  itSurnameName->setEmail(newEmail);

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::SetSalary        ( const string    & name,
                                                  const string    & surname,
                                                  unsigned int      salary )
{
  // Find a place for SurnameName
  itSurnameName = GetIterator(name, surname, "", 0, 1);

  // If the person doesn't exist
  if (itSurnameName == m_VectorSurnameName.end() || itSurnameName->getName() != name || itSurnameName->getSurname() != surname)
    return false;

  // Find a place for Email
  itEmail = GetIterator("", "", itSurnameName->getEmail(), 0, 2);

  itSurnameName->setSalary(salary);
  itEmail->setSalary(salary);

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::SetSalary        ( const string    & email,
                                                  unsigned int      salary )
{
  // Find a place for Email
  itEmail = GetIterator("", "", email, 0, 2);

  // If the person doesn't exist
  if (itEmail == m_VectorEmail.end() || itEmail->getEmail() != email)
    return false;

  // Find a place for SurnameName
  itSurnameName = GetIterator(itEmail->getName(), itEmail->getSurname(), "", 0, 1);

  itEmail->setSalary(salary);
  itSurnameName->setSalary(salary);

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
unsigned int  CPersonalAgenda::GetSalary        ( const string    & name,
                                                  const string    & surname ) const
{
  // Find a place for SurnameName
  itSurnameName = GetIterator(name, surname, "", 0, 1);

  // If the person doesn't exist
  if (itSurnameName == m_VectorSurnameName.end() || itSurnameName->getName() != name || itSurnameName->getSurname() != surname)
    return 0;

  return itSurnameName->getSalary();
}
//---------------------------------------------------------------------------------------------------------------------
unsigned int  CPersonalAgenda::GetSalary        ( const string    & email ) const
{
  // Find a place for Email
  itEmail = GetIterator("", "", email, 0, 2);

  // If the person doesn't exist
  if (itEmail == m_VectorEmail.end() || itEmail->getEmail() != email)
    return 0;

  return itEmail->getSalary();
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::GetRank          ( const string    & name,
                                                  const string    & surname,
                                                  int             & rankMin,
                                                  int             & rankMax ) const
{
  // Try to copy our original vector of employees
  // A terrible decision, but we will learn effective algorithms later 
  vector<CPersona> tmpVectorSurnameName = m_VectorSurnameName;

  // Sort the copy of our original vector
  sort(tmpVectorSurnameName.begin(), tmpVectorSurnameName.end(), [&](const CPersona & lhs, const CPersona & rhs) {
    return lhs.getSalary() < rhs.getSalary();
  });

  // Find a place for SurnameName
  itSurnameName = GetIterator(name, surname, "", 0, 1);

  // If the person doesn't exist
  if (itSurnameName == m_VectorSurnameName.end() || itSurnameName->getName() != name || itSurnameName->getSurname() != surname)
    return false;

  // Find "bottom" line
  for (rankMin = 0; rankMin < (int)tmpVectorSurnameName.size(); rankMin++)
    if (tmpVectorSurnameName[rankMin].getSalary() == itSurnameName->getSalary())
      break;

  // Find "upper" line
  for (rankMax = rankMin; rankMax < (int)tmpVectorSurnameName.size(); rankMax++)
    if (tmpVectorSurnameName[rankMax].getSalary() != itSurnameName->getSalary())
      break;

  rankMax--;

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::GetRank          ( const string    & email,
                                                  int             & rankMin,
                                                  int             & rankMax ) const
{
  // Try to copy our original vector of employees
  // A terrible decision, but we will learn effective algorithms later 
  vector<CPersona> tmpVectorEmail = m_VectorEmail;

  // Sort the copy of our original vector
  sort(tmpVectorEmail.begin(), tmpVectorEmail.end(), [&](const CPersona & lhs, const CPersona & rhs) {
    return lhs.getSalary() < rhs.getSalary();
  });

  // Find a place for Email
  itEmail = GetIterator("", "", email, 0, 2);

  // If the person doesn't exist
  if (itEmail == m_VectorEmail.end() || itEmail->getEmail() != email)
    return false;

  // Find "bottom" line
  for (rankMin = 0; rankMin < (int)tmpVectorEmail.size(); rankMin++)
    if (tmpVectorEmail[rankMin].getSalary() == itEmail->getSalary())
      break;

  // Find "upper" line
  for (rankMax = rankMin; rankMax < (int)tmpVectorEmail.size(); rankMax++)
    if (tmpVectorEmail[rankMax].getSalary() != itEmail->getSalary())
      break;

  rankMax--;

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::GetFirst         ( string          & outName,
                                                  string          & outSurname ) const
{
  if (m_VectorSurnameName.empty())
    return false;

  outName = m_VectorSurnameName.front().getName();
  outSurname = m_VectorSurnameName.front().getSurname();

  return true;
}
//---------------------------------------------------------------------------------------------------------------------
bool          CPersonalAgenda::GetNext          ( const string    & name,
                                                  const string    & surname,
                                                  string          & outName,
                                                  string          & outSurname ) const
{
  // Find a place for SurnameName
  itSurnameName = GetIterator(name, surname, "", 0, 1);

  // If the person doesn't exist
  if (itSurnameName == m_VectorSurnameName.end() ||
      next(itSurnameName) == m_VectorSurnameName.end() ||
      itSurnameName->getName() != name ||
      itSurnameName->getSurname() != surname)
    return false;

  outName = next(itSurnameName)->getName();
  outSurname = next(itSurnameName)->getSurname();

  return true;
}
//=====================================================================================================================
#ifndef __PROGTEST__
int main ( void )
{
  string outName, outSurname;
  int lo, hi;

  CPersonalAgenda b1;
  assert ( b1 . Add ( "John", "Smith", "john", 30000 ) );
  assert ( b1 . Add ( "John", "Miller", "johnm", 35000 ) );
  assert ( b1 . Add ( "Peter", "Smith", "peter", 23000 ) );
  assert ( b1 . GetFirst ( outName, outSurname )
           && outName == "John"
           && outSurname == "Miller" );
  assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( b1 . GetNext ( "John", "Smith", outName, outSurname )
           && outName == "Peter"
           && outSurname == "Smith" );
  assert ( ! b1 . GetNext ( "Peter", "Smith", outName, outSurname ) );
  assert ( b1 . SetSalary ( "john", 32000 ) );
  assert ( b1 . GetSalary ( "john" ) ==  32000 );
  assert ( b1 . GetSalary ( "John", "Smith" ) ==  32000 );
  assert ( b1 . GetRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . GetRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . GetRank ( "johnm", lo, hi )
           && lo == 2
           && hi == 2 );
  assert ( b1 . SetSalary ( "John", "Smith", 35000 ) );
  assert ( b1 . GetSalary ( "John", "Smith" ) ==  35000 );
  assert ( b1 . GetSalary ( "john" ) ==  35000 );
  assert ( b1 . GetRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . GetRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . GetRank ( "johnm", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . ChangeName ( "peter", "James", "Bond" ) );
  assert ( b1 . GetSalary ( "peter" ) ==  23000 );
  assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . GetSalary ( "Peter", "Smith" ) ==  0 );
  assert ( b1 . GetFirst ( outName, outSurname )
           && outName == "James"
           && outSurname == "Bond" );
  assert ( b1 . GetNext ( "James", "Bond", outName, outSurname )
           && outName == "John"
           && outSurname == "Miller" );
  assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . ChangeEmail ( "James", "Bond", "james" ) );
  assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . GetSalary ( "james" ) ==  23000 );
  assert ( b1 . GetSalary ( "peter" ) ==  0 );
  assert ( b1 . Del ( "james" ) );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 0
           && hi == 1 );
  assert ( b1 . Del ( "John", "Miller" ) );
  assert ( b1 . GetRank ( "john", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . GetFirst ( outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . Del ( "john" ) );
  assert ( ! b1 . GetFirst ( outName, outSurname ) );
  assert ( b1 . Add ( "John", "Smith", "john", 31000 ) );
  assert ( b1 . Add ( "john", "Smith", "joHn", 31000 ) );
  assert ( b1 . Add ( "John", "smith", "jOhn", 31000 ) );

  CPersonalAgenda b2;
  assert ( ! b2 . GetFirst ( outName, outSurname ) );
  assert ( b2 . Add ( "James", "Bond", "james", 70000 ) );
  assert ( b2 . Add ( "James", "Smith", "james2", 30000 ) );
  assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( ! b2 . Add ( "James", "Bond", "james3", 60000 ) );
  assert ( ! b2 . Add ( "Peter", "Bond", "peter", 50000 ) );
  assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . SetSalary ( "Joe", "Black", 90000 ) );
  assert ( ! b2 . SetSalary ( "joe", 90000 ) );
  assert ( b2 . GetSalary ( "Joe", "Black" ) ==  0 );
  assert ( b2 . GetSalary ( "joe" ) ==  0 );
  assert ( ! b2 . GetRank ( "Joe", "Black", lo, hi ) );
  assert ( ! b2 . GetRank ( "joe", lo, hi ) );
  assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . Del ( "Joe", "Black" ) );
  assert ( ! b2 . Del ( "joe" ) );
  assert ( ! b2 . ChangeName ( "james2", "James", "Bond" ) );
  assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "james" ) );
  assert ( ! b2 . ChangeName ( "peter", "Peter", "Smith" ) );
  assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter" ) );
  assert ( b2 . Del ( "Peter", "Smith" ) );
  assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter2" ) );
  assert ( ! b2 . SetSalary ( "Peter", "Smith", 35000 ) );
  assert ( b2 . GetSalary ( "Peter", "Smith" ) ==  0 );
  assert ( ! b2 . GetRank ( "Peter", "Smith", lo, hi ) );
  assert ( ! b2 . ChangeName ( "peter", "Peter", "Falcon" ) );
  assert ( ! b2 . SetSalary ( "peter", 37000 ) );
  assert ( b2 . GetSalary ( "peter" ) ==  0 );
  assert ( ! b2 . GetRank ( "peter", lo, hi ) );
  assert ( ! b2 . Del ( "Peter", "Smith" ) );
  assert ( ! b2 . Del ( "peter" ) );
  assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( b2 . GetSalary ( "peter" ) ==  40000 );

  return 0;
}
#endif /* __PROGTEST__ */