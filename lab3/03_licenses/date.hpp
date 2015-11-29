// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DATE_HPP_
#define _DATE_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/


class Date
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Date ();
	Date ( int _year, int _month, int _day );
	Date ( const char* _yyyyMMDD, char _sep = '/' );

	int getYear () const;
	int getMonth () const;
	int getDay () const;

	bool isLeapYear () const;

	bool operator == ( Date d ) const;
	bool operator != ( Date d ) const;
	bool operator < ( Date d ) const;
	bool operator <= ( Date d ) const;
	bool operator > ( Date d ) const;
	bool operator >= ( Date d ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	bool isValid () const;

/*-----------------------------------------------------------------*/

	int m_year, m_month, m_day;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


inline int Date::getYear () const
{
	return m_year;
}


/*****************************************************************************/


inline int Date::getMonth () const
{
	return m_month;
}


/*****************************************************************************/


inline int Date::getDay () const
{
	return m_day;
}


/*****************************************************************************/

std::ostream & operator << ( std::ostream & o, Date d );

std::istream & operator >> ( std::istream & i, Date & d );

/*****************************************************************************/

#endif //  _DATE_HPP_
