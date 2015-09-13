// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "stopwatch.hpp"

#include <windows.h>
#include <sstream>

/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_constructor )
{
	Stopwatch s;
	assert( s.isPaused() );
	assert( s.getElapsed() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_after_second )
{
	Stopwatch s;
	s.resume();
	::Sleep( 1000 );
	assert( abs( s.getElapsed() - 1000 ) < 100 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_paused_after_second )
{
	Stopwatch s;
	::Sleep( 1000 );
	assert( s.getElapsed() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_second_pause_another_second )
{
	Stopwatch s;
	s.resume();
	::Sleep( 1000 );
	s.pause();
	::Sleep( 1000 );
	assert( abs( s.getElapsed() - 1000 ) < 100 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_zero_and_paused_after_reset )
{
	Stopwatch s;
	s.resume();
	::Sleep( 1000 );
	s.reset();
	assert( s.getElapsed() == 0 );
	assert( s.isPaused() );
	::Sleep( 1000 );
	assert( s.getElapsed() == 0 );
	assert( s.isPaused() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_wait_pause_wait_resume )
{
	Stopwatch s;
	s.resume();
	::Sleep( 1000 );
	s.pause();
	::Sleep( 1000 );
	s.resume();
	::Sleep( 1000 );
	assert( abs( s.getElapsed() - 2000 ) < 100 );
	assert( ! s.isPaused() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_cannot_pause_paused )
{
	try
	{
		Stopwatch s;
		s.pause();
		assert( !"Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Stopwatch is paused already" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_cannot_resume_not_paused )
{
	Stopwatch s;
	s.resume();

	try
	{
		s.resume();
		assert( !"Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Stopwatch is not paused" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_get_elapsed_unit_methods )
{
	Stopwatch s;
	s.resume();
	::Sleep( 2100 );
	s.pause();

	assert( s.getElapsedHours() == 0 );
	assert( s.getElapsedMinutes() == 0 );
	assert( s.getElapsedSeconds() == 2 );

	s += 3500;

	assert( s.getElapsedHours() == 0 );
	assert( s.getElapsedMinutes() == 0 );
	assert( s.getElapsedSeconds() == 5 );

	s += 120000;

	assert( s.getElapsedHours() == 0 );
	assert( s.getElapsedMinutes() == 2 );
	assert( s.getElapsedSeconds() == 5 );

	s += 3600000;
	assert( s.getElapsedHours() == 1 );
	assert( s.getElapsedMinutes() == 2 );
	assert( s.getElapsedSeconds() == 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_display )
{
	Stopwatch s;
	s += 3600000;
	s +=  120000;
	s +=    5500;

	std::stringstream o;
	s.display( o );
	assert( o.str() == "1:2:5" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( stopwatch_test_increments_decrements )
{
	Stopwatch s;
	s += 1000;

	Stopwatch s2 = s + 1000;
	assert( s2.getElapsed() == 2000 );
	assert( s2.isPaused() );

	s2.resume();
	Stopwatch s3 = s2 - 1000;
	assert( abs( s3.getElapsed() - 1000 ) < 100 );
	assert( ! s3.isPaused() );

	Stopwatch s4 = s;
	s4 -= 1000;
	assert( s4.isPaused() );
}


/*****************************************************************************/
