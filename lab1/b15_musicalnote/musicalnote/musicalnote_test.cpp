// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "musicalnote.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_constructor_direct )
{
	MusicalNote n1( MusicalNote::Note_C );
	assert( n1.getNote() == MusicalNote::Note_C );
	assert( n1.getSign() == MusicalNote::Sign_None );

	MusicalNote n2( MusicalNote::Note_E, MusicalNote::Sign_Flat );
	assert( n2.getNote() == MusicalNote::Note_E );
	assert( n2.getSign() == MusicalNote::Sign_Flat );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_constructor_illegal_notes )
{
	MusicalNote::Note notes[] = { MusicalNote::Note_B,     MusicalNote::Note_C,    MusicalNote::Note_E,     MusicalNote::Note_F };
	MusicalNote::Sign signs[] = { MusicalNote::Sign_Sharp, MusicalNote::Sign_Flat, MusicalNote::Sign_Sharp, MusicalNote::Sign_Flat };

	for ( int i = 0; i < 4; i++ )
	{
		try
		{
			MusicalNote n( notes[ i ], signs[ i ] );
			assert( ! "Exception must have been thrown" );
		}
		catch ( std::exception & e )
		{
			assert( ! strcmp( e.what(), "Invalid note" ) );
		}
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_constructor_string )
{
	MusicalNote n1( "D" );
	assert( n1.getNote() == MusicalNote::Note_D );
	assert( n1.getSign() == MusicalNote::Sign_None );

	MusicalNote n2( "F#" );
	assert( n2.getNote() == MusicalNote::Note_F );
	assert( n2.getSign() == MusicalNote::Sign_Sharp );

	MusicalNote n3( "Eb" );
	assert( n3.getNote() == MusicalNote::Note_E );
	assert( n3.getSign() == MusicalNote::Sign_Flat );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_constructor_string_invalid_notes )
{
	const char * notes[] = { "B#", "Cb", "E#", "Fb" };
	for ( int i = 0; i < 4; i++ )
	{
		try
		{
			MusicalNote n( notes[ i ] );
			assert( ! "Exception must have been thrown" );
		}
		catch ( std::exception & e )
		{
			assert( ! strcmp( e.what(), "Invalid note" ) );
		}
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_constructor_string_bad_format )
{
	const char * notes[] = { "B##", "", "Z#", "##", "C$" };
	for ( int i = 0; i < 5; i++ )
	{
		try
		{
			MusicalNote n( notes[ i ] );
			assert( ! "Exception must have been thrown" );
		}
		catch ( std::exception & e )
		{
			assert( ! strcmp( e.what(), "Invalid format" ) );
		}
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_to_string )
{
	MusicalNote n1( MusicalNote::Note_D );
	assert( ! strcmp( n1.toString(), "D" ) );

	MusicalNote n2( MusicalNote::Note_D, MusicalNote::Sign_Sharp );
	assert( ! strcmp( n2.toString(), "D#" ) );

	MusicalNote n3( MusicalNote::Note_D, MusicalNote::Sign_Flat );
	assert( ! strcmp( n3.toString(), "Db" ) );

}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_equality_inequality )
{
	MusicalNote n1( MusicalNote::Note_D, MusicalNote::Sign_Sharp );
	MusicalNote n2( MusicalNote::Note_D, MusicalNote::Sign_Sharp );
	MusicalNote n3( MusicalNote::Note_E, MusicalNote::Sign_Flat );
	MusicalNote n4( MusicalNote::Note_D, MusicalNote::Sign_Flat );

	assert( n1 == n2 );
	assert( !( n1 != n2 ) );

	assert( n1 == n3 );			// D# == Eb
	assert( !( n1 != n3 ) );

	assert( n1 != n4 );
	assert( !( n1 == n4 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_prefix_increment )
{
	MusicalNote n( "A" );

	++n;
	assert( !strcmp( n.toString(), "A#" ) || !strcmp( n.toString(), "Bb" ) );

	++n;
	assert( !strcmp( n.toString(), "B" ) );

	++n;
	assert( !strcmp( n.toString(), "C" ) );

	++n;
	assert( !strcmp( n.toString(), "C#" ) || !strcmp( n.toString(), "Db" ) );

	++n;
	assert( !strcmp( n.toString(), "D" ) );
	
	++n;
	assert( !strcmp( n.toString(), "D#" ) || !strcmp( n.toString(), "Eb" ) );

	++n;
	assert( !strcmp( n.toString(), "E" ) );
	
	++n;
	assert( !strcmp( n.toString(), "F" ) );
	
	++n;
	assert( !strcmp( n.toString(), "F#" ) || !strcmp( n.toString(), "Gb" ) );
		
	++n;
	assert( !strcmp( n.toString(), "G" ) );
	
	++n;
	assert( !strcmp( n.toString(), "G#" ) || !strcmp( n.toString(), "Ab" ) );
		
	++n;
	assert( !strcmp( n.toString(), "A" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_postfix_increment )
{
	MusicalNote n( "A" );

	MusicalNote n2 = n++;
	assert( !strcmp( n.toString(), "A#" ) || !strcmp( n.toString(), "Bb" ) );
	assert( !strcmp( n2.toString(), "A" ) );

	n2 = n++;
	assert( !strcmp( n.toString(), "B" ) );
	assert( !strcmp( n2.toString(), "A#" ) || !strcmp( n2.toString(), "Bb" ) );

	n2 = n++;
	assert( !strcmp( n.toString(), "C" ) );
	assert( !strcmp( n2.toString(), "B" ) );

	n2 = n++;
	assert( !strcmp( n.toString(), "C#" ) || !strcmp( n.toString(), "Db" ) );
	assert( !strcmp( n2.toString(), "C" ) );

	n2 = n++;
	assert( !strcmp( n.toString(), "D" ) );
	assert( !strcmp( n2.toString(), "C#" ) || !strcmp( n2.toString(), "Db" ) );
	
	n2 = n++;
	assert( !strcmp( n.toString(), "D#" ) || !strcmp( n.toString(), "Eb" ) );
	assert( !strcmp( n2.toString(), "D" ) );

	n2 = n++;
	assert( !strcmp( n.toString(), "E" ) );
	assert( !strcmp( n2.toString(), "D#" ) || !strcmp( n2.toString(), "Eb" ) );
	
	n2 = n++;
	assert( !strcmp( n.toString(), "F" ) );
	assert( !strcmp( n2.toString(), "E" ) );
	
	n2 = n++;
	assert( !strcmp( n.toString(), "F#" ) || !strcmp( n.toString(), "Gb" ) );
	assert( !strcmp( n2.toString(), "F" ) );
		
	n2 = n++;
	assert( !strcmp( n.toString(), "G" ) );
	assert( !strcmp( n2.toString(), "F#" ) || !strcmp( n2.toString(), "Gb" ) );
	
	n2 = n++;
	assert( !strcmp( n.toString(), "G#" ) || !strcmp( n.toString(), "Ab" ) );
	assert( !strcmp( n2.toString(), "G" ) );
		
	n2 = n++;
	assert( !strcmp( n.toString(), "A" ) );
	assert( !strcmp( n2.toString(), "G#" ) || !strcmp( n2.toString(), "Ab" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_prefix_decrement )
{
	MusicalNote n( "A" );
	
	--n;
	assert( !strcmp( n.toString(), "G#" ) || !strcmp( n.toString(), "Ab" ) );
			
	--n;
	assert( !strcmp( n.toString(), "G" ) );
		
	--n;
	assert( !strcmp( n.toString(), "F#" ) || !strcmp( n.toString(), "Gb" ) );
	
	--n;
	assert( !strcmp( n.toString(), "F" ) );

	--n;
	assert( !strcmp( n.toString(), "E" ) );
	
	--n;
	assert( !strcmp( n.toString(), "D#" ) || !strcmp( n.toString(), "Eb" ) );

	--n;
	assert( !strcmp( n.toString(), "D" ) );

	--n;
	assert( !strcmp( n.toString(), "C#" ) || !strcmp( n.toString(), "Db" ) );
	
	--n;
	assert( !strcmp( n.toString(), "C" ) );
	
	--n;
	assert( !strcmp( n.toString(), "B" ) );

	--n;
	assert( !strcmp( n.toString(), "A#" ) || !strcmp( n.toString(), "Bb" ) );

	--n;
	assert( !strcmp( n.toString(), "A" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_postfix_decrement )
{
	MusicalNote n( "A" );
			
	MusicalNote n2 = n--;
	assert( !strcmp( n.toString(), "G#" ) || !strcmp( n.toString(), "Ab" ) );
	assert( !strcmp( n2.toString(), "A" ) );

	n2 = n--;
	assert( !strcmp( n.toString(), "G" ) );
	assert( !strcmp( n2.toString(), "G#" ) || !strcmp( n2.toString(), "Ab" ) );
		
	n2 = n--;
	assert( !strcmp( n.toString(), "F#" ) || !strcmp( n.toString(), "Gb" ) );
	assert( !strcmp( n2.toString(), "G" ) );
		
	n2 = n--;
	assert( !strcmp( n.toString(), "F" ) );
	assert( !strcmp( n2.toString(), "F#" ) || !strcmp( n2.toString(), "Gb" ) );
		
	n2 = n--;
	assert( !strcmp( n.toString(), "E" ) );
	assert( !strcmp( n2.toString(), "F" ) );
		
	n2 = n--;
	assert( !strcmp( n.toString(), "D#" ) || !strcmp( n.toString(), "Eb" ) );
	assert( !strcmp( n2.toString(), "E" ) );
	
	n2 = n--;
	assert( !strcmp( n.toString(), "D" ) );
	assert( !strcmp( n2.toString(), "D#" ) || !strcmp( n2.toString(), "Eb" ) );
	
	n2 = n--;
	assert( !strcmp( n.toString(), "C#" ) || !strcmp( n.toString(), "Db" ) );
	assert( !strcmp( n2.toString(), "D" ) );
	
	n2 = n--;
	assert( !strcmp( n.toString(), "C" ) );
	assert( !strcmp( n2.toString(), "C#" ) || !strcmp( n2.toString(), "Db" ) );
	
	n2 = n--;
	assert( !strcmp( n.toString(), "B" ) );
	assert( !strcmp( n2.toString(), "C" ) );

	n2 = n--;
	assert( !strcmp( n.toString(), "A#" ) || !strcmp( n.toString(), "Bb" ) );
	assert( !strcmp( n2.toString(), "B" ) );

	n2 = n--;
	assert( !strcmp( n.toString(), "A" ) );
	assert( !strcmp( n2.toString(), "A#" ) || !strcmp( n2.toString(), "Bb" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_add_semitones )
{
	MusicalNote n( "A" );
	
	n += 3;
	assert( n.getNote() == MusicalNote::Note_C );
	assert( n.getSign() == MusicalNote::Sign_None );

	n += 3;
	assert( !strcmp( n.toString(), "D#" ) || !strcmp( n.toString(), "Cb" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_sub_semitones )
{
	MusicalNote n( "A" );
	
	n -= 3;
	assert( !strcmp( n.toString(), "Gb" ) || !strcmp( n.toString(), "F#" ) );

	n -= 2;
	assert( !strcmp( n.toString(), "E" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( musicalnote_test_intervals )
{
	MusicalNote b( "A" );
	MusicalNote n( "A" );

	assert( ( n - b ) == MusicalNote::Interval_Prime );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Minor_Second );
	
	++n;
	assert( ( n - b ) == MusicalNote::Interval_Major_Second );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Minor_Third );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Major_Third );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Fourth );
		
	++n;
	assert( ( n - b ) == MusicalNote::Interval_Small_Fifth );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Fifth );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Minor_Sixth );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Major_Sixth );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Minor_Seventh );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Major_Seventh );

	++n;
	assert( ( n - b ) == MusicalNote::Interval_Prime );
}


/*****************************************************************************/
