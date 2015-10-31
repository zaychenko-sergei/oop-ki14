// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "date.hpp"

#include <ctime>
#include <cassert>
#include <cstdio>
#include <stdexcept>

/*****************************************************************************/


Date::Date ()
{
	time_t currentTime = time( nullptr );

	tm* currentTM = gmtime( &currentTime );

	m_year = currentTM->tm_year + 1900;
	m_month = currentTM->tm_mon + 1;
	m_day = currentTM->tm_mday;
}


/*****************************************************************************/


Date::Date ( int _year, int _month, int _day )
	: m_year( _year ), m_month( _month ), m_day( _day )
{
	if ( ! isValid() )
		throw std::logic_error( "Error: date is not valid!" );
}


/*****************************************************************************/


Date::Date ( const char * _yyyyMMDD, char _sep )
{
	char sep1, sep2;
	int nMatched = sscanf( _yyyyMMDD, "%d%c%d%c%d", &m_year, &sep1, &m_month, &sep2, &m_day );
	if ( nMatched != 5 || sep1 != _sep || sep2 != _sep )
		throw std::logic_error( "Error: date format is incorrect!" );

	if ( ! isValid() )
		throw std::logic_error( "Error: date is not valid!" );
}


/*****************************************************************************/


bool Date::isValid () const
{
	if ( m_year == 0 )
		return false;

	if ( m_month < 1 || m_month > 12 )
		return false;

	if ( m_day < 1 )
		return false;

	else if ( m_month == 2 && isLeapYear() )
		return m_day <= 29;

	else
	{
		static const int s_daysInMonth[] = {
			31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};

		return m_day <= s_daysInMonth[ m_month - 1 ];
	}
}


/*****************************************************************************/


bool Date::isLeapYear () const
{
	if ( m_year % 4 != 0 )
		return false;

	else if ( m_year % 100 == 0 )
		return ( m_year % 400 == 0 );

	return true;
}


/*****************************************************************************/


bool Date::operator == ( Date d ) const
{
	return m_year == d.getYear() && m_month == d.getMonth() && m_day == d.getDay();
}


/*****************************************************************************/


bool Date::operator != ( Date d ) const
{
	return !( *this == d );
}


/*****************************************************************************/


bool Date::operator < ( Date d ) const
{
	if ( m_year < d.getYear() )
		return true;

	else if ( m_year == d.getYear() )
	{
		if ( m_month < d.getMonth() )
			return true;

		else if ( m_month == d.getMonth() )
			return m_day < d.getDay();
	}

	return false;
}


/*****************************************************************************/


bool Date::operator > ( Date d ) const
{
	return d < *this;
}


/*****************************************************************************/


bool Date::operator <= ( Date d ) const
{
	return ( *this < d ) || ( *this == d );
}


/*****************************************************************************/


bool Date::operator >= ( Date d ) const
{
	return ( d < *this ) || ( *this == d );
}


/*****************************************************************************/


std::ostream & operator << ( std::ostream & o, Date d )
{
	o << d.getYear() << '/' << d.getMonth() << '/' << d.getDay();
	return o;
}


/*****************************************************************************/


std::istream & operator >> ( std::istream & i, Date & d )
{
	char buf[ 100 ];
	i >> buf;

	d = Date( buf );
	return i;
}


/*****************************************************************************/
