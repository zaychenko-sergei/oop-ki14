// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "time.hpp"
#include "messages.hpp"

#include <ctime>
#include <cassert>
#include <cstdio>
#include <stdexcept>

/*****************************************************************************/


Time::Time()
{
	time_t currentTime = time( nullptr );

	tm* currentTM = gmtime( &currentTime );

	m_hours = currentTM->tm_hour;
	m_minutes = currentTM->tm_min;
	m_seconds = currentTM->tm_sec;
}


/*****************************************************************************/


Time::Time( int _hours, int _minutes, int _seconds )
	:    m_hours( _hours ), m_minutes( _minutes ), m_seconds( _seconds )
{
	if ( !isValid() )
		throw std::logic_error( Messages::InvalidDateTime );
}


/*****************************************************************************/


Time::Time( const char * _time, char _timesep )
{
	char sep1, sep2;
	int nMatched = sscanf(
			_time
		,	"%d%c%d%c%d"
		,	&m_hours, &sep1, &m_minutes, &sep2, &m_seconds
	);
	if ( nMatched != 5 || sep1 != _timesep || sep2 != _timesep )
		throw std::logic_error( Messages::InvalidDateTimeFormat );

	if ( !isValid() )
		throw std::logic_error( Messages::InvalidDateTime );
}


/*****************************************************************************/


int
Time::getHours() const
{
	return m_hours;
}


/*****************************************************************************/


int
Time::getMinutes() const
{
	return m_minutes;
}


/*****************************************************************************/


int
Time::getSeconds() const
{
	return m_seconds;
}


/*****************************************************************************/


bool
Time::isValid() const
{
	if ( m_hours < 0 || m_hours > 24 )
		return false;
	else if ( m_minutes < 0 || m_minutes > 60 )
		return false;
	else if ( m_seconds < 0 || m_seconds > 60 )
		return false;

	return true;
}


/*****************************************************************************/


bool
Time::operator == ( Time t ) const
{
	return m_hours   == t.getHours()
		&& m_minutes == t.getMinutes()
		&& m_seconds == t.getSeconds();
}


/*****************************************************************************/


bool
Time::operator != ( Time t ) const
{
	return !( *this == t );
}


/*****************************************************************************/


bool
Time::operator < ( Time t ) const
{
	if ( m_hours < t.getHours() )
		return true;

	else if ( m_hours == t.getHours() )
	{
		if ( m_minutes < t.getMinutes() )
			return true;

		else if ( m_minutes == t.getMinutes() )
			return m_seconds < t.getSeconds();
	}
	return false;
}


/*****************************************************************************/


bool
Time::operator > ( Time t ) const
{
	return t < *this;
}


/*****************************************************************************/


bool
Time::operator <= ( Time t ) const
{
	return ( *this < t ) || ( *this == t );
}


/*****************************************************************************/


bool
Time::operator >= ( Time t ) const
{
	return ( t < *this ) || ( *this == t );
}


/*****************************************************************************/
