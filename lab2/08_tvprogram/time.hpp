// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TIME_HPP_
#define _TIME_HPP_

/*****************************************************************************/


class Time
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Time();
	Time( int _hours, int _minutes, int _seconds );
	// Format: H:M:S
	Time( const char * _time, char _timesep = ':' );

	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;

	bool operator == ( Time t ) const;
	bool operator != ( Time t ) const;
	bool operator < ( Time t ) const;
	bool operator <= ( Time t ) const;
	bool operator > ( Time t ) const;
	bool operator >= ( Time t ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	bool isValid() const;

/*-----------------------------------------------------------------*/

	int m_hours, m_minutes, m_seconds;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif // _TIME_HPP_
