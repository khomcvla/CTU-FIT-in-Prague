//=================================================================================================
class YMD
{
  public:
                        YMD                           ( int year, 
                                                        int month,
                                                        int day );

                        YMD                           ( void ){}

    YMD               & operator -                    ( void );
    YMD               & operator -                    ( const YMD & x);
    YMD               & operator +                    ( const YMD & x);

    void                setYear                       ( int year  )  { m_year  = year;  }
    void                setMonth                      ( int month )  { m_month = month; }
    void                setDay                        ( int day   )  { m_day   = day;   } 

    int                 getYear                       ( void ) const { return m_year;   }
    int                 getMonth                      ( void ) const { return m_month;  }
    int                 getDay                        ( void ) const { return m_day;    }

    auto                getVectorYMD                  ( void ) const { return m_vector_YMD; }

  protected:
  
    int                 m_year;
    int                 m_month;
    int                 m_day;
        
    vector<YMD>         m_vector_YMD;
    
};
//-------------------------------------------------------------------------------------------------
                        YMD::YMD                      ( int year, 
                                                        int month,
                                                        int day )
{
  m_year = year;
  m_month = month;
  m_day = day;
}
//-------------------------------------------------------------------------------------------------
YMD                   & YMD::operator -               ( void )
{
  setYear(-getYear());
  setMonth(-getMonth());
  setDay(-getDay());

  return *this;
}
//-------------------------------------------------------------------------------------------------
YMD                   & YMD::operator -               ( const YMD & x )
{
  m_year  -= x.m_year;
  m_month -= x.m_month;
  m_day   -= x.m_day;

  m_vector_YMD.push_back(YMD(x.getYear(), x.getMonth(), x.getDay()));

  return *this;
}
//-------------------------------------------------------------------------------------------------
YMD                   & YMD::operator +               ( const YMD & x )
{
  m_year  += x.m_year;
  m_month += x.m_month;
  m_day   += x.m_day;

  m_vector_YMD.push_back(YMD(x.getYear(), x.getMonth(), x.getDay()));

  return *this;
}
//=================================================================================================
class Year:  public YMD
{
  public:
                        Year                          ( int year )              
  {
    YMD::m_year   = year;
    YMD::m_month  = 0;
    YMD::m_day    = 0;

    YMD::m_vector_YMD.push_back(YMD(year, 0, 0));
  }                       
};
//=================================================================================================
class Month: public YMD
{
  public:
                        Month                         ( int month )
  {
    YMD::m_year   = 0;
    YMD::m_month  = month;
    YMD::m_day    = 0;

    YMD::m_vector_YMD.push_back(YMD(0, month, 0));
  }
};
//=================================================================================================
class Day:   public YMD
{
  public:
                        Day                           ( int day )
  {
    YMD::m_year   = 0;
    YMD::m_month  = 0;
    YMD::m_day    = day;

    YMD::m_vector_YMD.push_back(YMD(0,0,day));
  }
};
//=================================================================================================
class CDate
{
  public:
                        CDate                         ( int year, 
                                                        int month,
                                                        int day );

    CDate               operator -                    ( const   YMD & x ); 
    CDate               operator +                    ( const   YMD & x );
    CDate             & operator +=                   ( const   YMD & x );

    int                 operator -                    ( const CDate & x ); 
    CDate               operator +                    ( const CDate & x );

    bool                operator ==                   ( const CDate & x ) const;
    bool                operator !=                   ( const CDate & x ) const;
    bool                operator <                    ( const CDate & x ) const;

    friend ostream    & operator <<                   ( ostream & os, const CDate & x );

  private:

    int                 m_year;
    int                 m_month;
    int                 m_day;

    //---------------------------------------------------------------------------------------------
    int                 returnDayInMonth              ( int year, 
                                                        int month  ) 
    {
      // If month is February
      if (month == 2) {
        // Checking for Leap Year
        if ((year % 4 == 0) && (year % 4000 != 0) && ((year % 400 == 0) || (year % 100 != 0)))
          return 29;
        else
          return 28;
      } else if ((month % 2 == 0 && month >= 8) || (month % 2 != 0 && month < 9)) // Two groups of days 31:(1,3,5,7,8,10,12) && 31:(4,6,9,11)
        return 31;
      else
        return 30;
    }
    //---------------------------------------------------------------------------------------------
    bool                validateDate                  ( int year,
                                                        int month,
                                                        int day    )
    {
      if (year < 1600 || month < 1 || month > 12 || day < 1 || day > returnDayInMonth(year, month))
        return false;

      return true;
    }
    //---------------------------------------------------------------------------------------------
    int                 returnDifferenceDay           ( int first,
                                                        int second )
    {
      return abs(first - second);
    }
    //---------------------------------------------------------------------------------------------
    int                 returnDifferenceMonth         ( int year,
                                                        int first,
                                                        int second )
    {
      int days = 0;

      for (int i = first + 1; i < second; i++)
        days += returnDayInMonth(year, i);

      return days;
    }
    //---------------------------------------------------------------------------------------------
    int                 returnDifferenceYear          ( int first,
                                                        int second )
    {
      int days = 0;

      for (int i = first + 1; i < second; i++)
        for (int j = 1; j <= 12; j++)
          days += returnDayInMonth(i, j);

      return days;
    }
};
//-------------------------------------------------------------------------------------------------
                        CDate::CDate                  ( int year,
                                                        int month, 
                                                        int day )
{
  if (!validateDate(year, month, day))
    throw InvalidDateException();

  m_year  = year;
  m_month = month;
  m_day   = day;
}
//-------------------------------------------------------------------------------------------------
int                     CDate::operator -             ( const CDate & x )
{
  int days = 0;

  // Years
  if (m_year < x.m_year) {

    // Example 2016.4.1 - 2018.3.15

    // Firstly calculate days till lower year 2016.4.1 - 2016.12.31
    days += returnDayInMonth(m_year, m_month) - m_day;
    days += returnDifferenceMonth(m_year, m_month, 13); // 13 because included December. Check function "returnDifferenceMonth"

    // Secondly calculate all days in years between 2016 and 2018
    // This is (2018, 2017, 2016) -> 2017
    days += returnDifferenceYear(m_year, x.m_year);

    // Thirdly calculate remaining days from 2018.1.1 to 2018.3.15
    days += returnDifferenceMonth(x.m_year, 0, x.m_month); // 0 because included January. Check function "returnDifferenceMonth"
    days += x.m_day;

    days = -days;

  } else if (m_year > x.m_year) {

    // Example 2018.3.15 - 2016.4.1

    // Firstly calculate days till lower year 2016.4.1 - 2016.12.31
    days += returnDayInMonth(x.m_year, x.m_month) - x.m_day;
    days += returnDifferenceMonth(x.m_year, x.m_month, 13); // 13 because included December. Check function "returnDifferenceMonth"

    // Secondly calculate all days in years between 2018 and 2016
    // This is (2016, 2017, 2018) -> 2017
    days += returnDifferenceYear(x.m_year, m_year);

    // Thirdly calculate remaining days from 2018.1.1 to 2018.3.15
    days += returnDifferenceMonth(m_year, 0, m_month); // 0 because included January. Check function "returnDifferenceMonth"
    days += m_day;

  } else { // if (m_year == x.m_year)

    // Month
    if (m_month < x.m_month) {
      days += x.m_day;
      days += returnDayInMonth(m_year, m_month) - m_day;
      days += returnDifferenceMonth(m_year, m_month, x.m_month);

    } else if (m_month > x.m_month) {
      days += m_day;
      days += returnDayInMonth(x.m_year, x.m_month) - x.m_day;
      days += returnDifferenceMonth(m_year, x.m_month, m_month);

    } else { // if (m_month == x.m_month)
      // Days
      // If we have dates with the same year and month
      // just need to calculate days
      days += returnDifferenceDay(m_day, x.m_day);
    }
  }

  return days;
}
//-------------------------------------------------------------------------------------------------
CDate                   CDate::operator +             ( const YMD   & x )
{
  int year = m_year;
  int month = m_month;
  int day = m_day;

  // DAYS
  // Firstly try to add second date's @m_day
  if (x.getDay() > 0) {
    for (int i = 0; i < x.getDay(); i++) {

      // Plus 1 day
      day++;

      // If deductible days equivalent [max_day]
      if (day == returnDayInMonth(year, month) + 1) {

        // Change @month and if it's December then need to increment @year
        if (month == 12) {
          year++;
          month = 1;
          day = 1;

        } else {
          // Otherwise just need to increment @month and set @day
          month++;
          day = 1;
        }
      }
    }
  } else {
    for (int i = 0; i > x.getDay(); i--) {
      // Minus 1 day
      day--;

      // If deductible days equivalent 0
      if (day == 0) {

        // Change @month and if it's January then need to decrement @year
        if (month == 1) {
          year--;
          month = 12;
          day = 31;

        } else {
          // Otherwise just need to decrement @month and set @day
          month--;
          day = returnDayInMonth(year, month);
        }
      }
    }
  }

  // MONTH
  // Secondly try to add second date's @month
  if (x.getMonth() > 0) {
    for (int i = 0; i < x.getMonth(); i++) {

      // Increment @month
      month++;

      // Change @month and if it's January then need to increment @year
      if (month == 13) {
        year++;
        month = 1;
      }
    }
  } else {
    for (int i = 0; i > x.getMonth(); i--) {
      // Decrement @month
      month--;

      // Change @month and if it's January then need to decrement @year
      if (month == 0) {
        year--;
        month = 12;
      }
    }
  }

  // YEAR
  // Thirdly try to minus second date's @year
  if (x.getYear() > 0) {
    for (int i = 0; i < x.getYear(); i++) {
      year++;
    }
  } else {
    for (int i = 0; i > x.getYear(); i--) {
      year--;
    }
  }

  if (!validateDate(year, month, day))
    throw InvalidDateException();

  return CDate(year, month, day);
}
//-------------------------------------------------------------------------------------------------
CDate                   CDate::operator -             ( const YMD   & x )
{
  int year = m_year;
  int month = m_month;
  int day = m_day;

  // DAYS
  // Firstly try to add second date's @m_day
  if (x.getDay() < 0) {
    for (int i = x.getDay(); i < 0; i++) {

      // Plus 1 day
      day++;

      // If deductible days equivalent [max_day]
      if (day == returnDayInMonth(year, month) + 1) {

        // Change @month and if it's December then need to increment @year
        if (month == 12) {
          year++;
          month = 1;
          day = 1;

        } else {
          // Otherwise just need to increment @month and set @day
          month++;
          day = 1;
        }
      }
    }
  } else {
    for (int i = 0; i < x.getDay(); i++) {
      // Minus 1 day
      day--;

      // If deductible days equivalent 0
      if (day == 0) {

        // Change @month and if it's January then need to decrement @year
        if (month == 1) {
          year--;
          month = 12;
          day = 31;

        } else {
          // Otherwise just need to decrement @month and set @day
          month--;
          day = returnDayInMonth(year, month);
        }
      }
    }
  }

  // MONTH
  // Secondly try to add second date's @month
  if (x.getMonth() < 0) {
    for (int i = x.getMonth(); i < 0; i++) {

      // Increment @month
      month++;

      // Change @month and if it's January then need to increment @year
      if (month == 13) {
        year++;
        month = 1;
      }
    }
  } else {
    for (int i = 0; i < x.getMonth(); i++) {
      // Decrement @month
      month--;

      // Change @month and if it's January then need to decrement @year
      if (month == 0) {
        year--;
        month = 12;
      }
    }
  }

  // YEAR
  // Thirdly try to minus second date's @year
  if (x.getYear() < 0) {
    for (int i = x.getYear(); i < 0; i++) {
      year++;
    }
  } else {
    for (int i = 0; i < x.getYear(); i++) {
      year--;
    }
  }

  if (!validateDate(year, month, day))
    throw InvalidDateException();

  return CDate(year, month, day);
}
//-------------------------------------------------------------------------------------------------
CDate                 & CDate::operator +=            ( const YMD   & x )
{
  auto tmp = x.getVectorYMD();

  for (unsigned int i = 0; i < tmp.size(); i++) {
    //-------------------------------------------
    if (tmp[i].getYear() != 0) { // Year
      tmp[i].setYear(abs(tmp[i].getYear()));
      if (x.getYear() > 0)
        *this = *this + tmp[i];
      else
        *this = *this - tmp[i];
      //-------------------------------------------
    } else if (tmp[i].getMonth() != 0) { // Month
      tmp[i].setMonth(abs(tmp[i].getMonth()));
      if (x.getMonth() > 0)
        *this = *this + tmp[i];
      else
        *this = *this - tmp[i];
      //-------------------------------------------
    } else if (tmp[i].getDay() != 0) { // Day
      tmp[i].setDay(abs(tmp[i].getDay()));
      if (x.getDay() > 0)
        *this = *this + tmp[i];
      else
        *this = *this - tmp[i];
    }
  }

  return *this;
}
//-------------------------------------------------------------------------------------------------
bool                    CDate::operator ==            ( const CDate & x ) const
{
  if (m_year == x.m_year && m_month == x.m_month && m_day == x.m_day)
    return true;

  return false;
}
//-------------------------------------------------------------------------------------------------
bool                    CDate::operator !=            ( const CDate & x ) const
{
  if (m_year == x.m_year && m_month == x.m_month && m_day == x.m_day)
    return false;

  return true;
}
//-------------------------------------------------------------------------------------------------
bool                    CDate::operator <             ( const CDate & x ) const
{
  if (m_year < x.m_year)
    return true;
  else if (m_year > x.m_year)
    return false;

  if (m_month < x.m_month)
    return true;
  else if (m_month > x.m_month)
    return false;

  if (m_day < x.m_day)
    return true;
  else
    return false;
}
//-------------------------------------------------------------------------------------------------
ostream               & operator <<                   ( ostream & os, const CDate & x )
{

  return os << x.m_year << '-' << setfill('0') << setw(2) << x.m_month << '-' << setfill('0') << setw(2) << x.m_day;
}