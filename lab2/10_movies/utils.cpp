// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include <ctime>

/*****************************************************************************/


int currentCalendarYear ()
{
	time_t currentTime = time( nullptr );
	return gmtime( &currentTime )->tm_year + 1900;
}


/*****************************************************************************/
