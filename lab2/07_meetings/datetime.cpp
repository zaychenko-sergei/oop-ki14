// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "datetime.hpp"
#include "messages.hpp"

#include <ctime>
#include <cassert>
#include <cstdio>
#include <stdexcept>

/*****************************************************************************/


DateTime::DateTime()
{
	time_t currentTime = time( nullptr );

	tm* currentTM = gmtime( &currentTime );

	m_year = currentTM->tm_year + 1900;
	m_month = currentTM->tm_mon + 1;
	m_day = currentTM->tm_mday;
	m_hours = currentTM->tm_hour;
	m_minutes = currentTM->tm_min;
	m_seconds = currentTM->tm_sec;
}


/*****************************************************************************/


DateTime::DateTime( int _year, int _month, int _day, int _hours, int _minutes, int _seconds )
	: m_year( _year ), m_month( _month ), m_day( _day ), m_hours( _hours ), m_minutes( _minutes ), m_seconds( _seconds )
{
	if ( !isValid() )
		throw std::logic_error( Messages::InvalidDateTime );
}


/*****************************************************************************/


DateTime::DateTime( const char * _datetime, char _datesep, char _datetimesep, char _timesep )
{
	char sep1, sep2, spacesep, sep3, sep4;
	int nMatched = sscanf(
			_datetime
		,	"%d%c%d%c%d%c%d%c%d%c%d"
		,	&m_year, &sep1, &m_month, &sep2, &m_day,
			&spacesep,
			&m_hours, &sep3, &m_minutes, &sep4, &m_seconds
	);
	if (	nMatched != 11
		||	sep1 != _datesep || sep2 != _datesep
		||	spacesep != _datetimesep
		||	sep3 != _timesep || sep4 != _timesep
	)
		throw std::logic_error( Messages::InvalidDateTimeFormat );

	if ( !isValid() )
		throw std::logic_error( Messages::InvalidDateTime );
}


/*****************************************************************************/


int
DateTime::getYear() const
{
	return m_year;
}


/*****************************************************************************/


int
DateTime::getMonth() const
{
	return m_month;
}


/*****************************************************************************/


int
DateTime::getDay() const
{
	return m_day;
}


/*****************************************************************************/


int
DateTime::getHours() const
{
	return m_hours;
}


/*****************************************************************************/


int
DateTime::getMinutes() const
{
	return m_minutes;
}


/*****************************************************************************/


int
DateTime::getSeconds() const
{
	return m_seconds;
}


/*****************************************************************************/


bool
DateTime::isLeapYear() const
{
	if ( m_year % 4 != 0 )
		return false;

	else if ( m_year % 100 == 0 )
		return ( m_year % 400 == 0 );

	return true;
}


/*****************************************************************************/


bool
DateTime::isValid() const
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

		if ( m_day > s_daysInMonth[ m_month - 1 ] )
			return false;

		else if ( m_hours < 0 || m_hours > 24 )
			return false;
		else if ( m_minutes < 0 || m_minutes > 60 )
			return false;
		else if ( m_seconds < 0 || m_seconds > 60 )
			return false;
	}

	return true;
}


/*****************************************************************************/


bool
DateTime::operator == ( const DateTime & d ) const
{
	return m_year == d.getYear()
		&& m_month == d.getMonth()
		&& m_day == d.getDay()
		&& m_hours == d.getHours()
		&& m_minutes == d.getMinutes()
		&& m_seconds == d.getSeconds();
}


/*****************************************************************************/


bool
DateTime::operator != ( const DateTime & d ) const
{
	return !( *this == d );
}


/*****************************************************************************/


bool
DateTime::operator < ( const DateTime & d ) const
{
	if ( m_year < d.getYear() )
		return true;

	else if ( m_year == d.getYear() )
	{
		if ( m_month < d.getMonth() )
			return true;

		else if ( m_month == d.getMonth() )
		{
			if ( m_day < d.getDay() )
				return true;

			else if ( m_day == d.getDay() )
			{
				if ( m_hours < d.getHours() )
					return true;

				else if ( m_hours == d.getHours() )
				{
					if ( m_minutes < d.getMinutes() )
						return true;

					else if ( m_minutes == d.getMinutes() )
						return m_seconds < d.getSeconds();
				}
			}
		}
	}

	return false;
}


/*****************************************************************************/


bool
DateTime::operator > ( const DateTime & d ) const
{
	return d < *this;
}


/*****************************************************************************/


bool
DateTime::operator <= ( const DateTime & d ) const
{
	return ( *this < d ) || ( *this == d );
}


/*****************************************************************************/


bool
DateTime::operator >= ( const DateTime & d ) const
{
	return ( d < *this ) || ( *this == d );
}


/*****************************************************************************/


std::ostream & operator << ( std::ostream & o, const DateTime & d )
{
	o << d.getYear() << '/' << d.getMonth() << '/' << d.getDay();
	o << '-';
	o << d.getHours() << ':' << d.getMinutes() << ':' << d.getSeconds();

	return o;
}


/*****************************************************************************/


std::istream & operator >> ( std::istream & i, DateTime & d )
{
	char buf[ 100 ];
	i >> buf;

	d = DateTime( buf );
	return i;
}


/*****************************************************************************/

