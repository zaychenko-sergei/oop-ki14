// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include "utils.hpp"

#include "lengthunit.hpp"

#include <string>

/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_constructor_default )
{
	LengthUnit u;
	assert( u.getAsMeters() == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_constructor_metric )
{
	LengthUnit u1( 2.5 );
	assert( u1.getAsMeters() == 2.5 );

	LengthUnit u2( 0.0 );
	assert( u2.getAsMeters() == 0.0 );

	LengthUnit u3( -2.5 );
	assert( u3.getAsMeters() == -2.5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_constructor_english )
{
	int feet, inches;

	LengthUnit u1( 3, 5 );
	u1.fetchAsEnglish( feet, inches );
	assert( feet == 3 );
	assert( inches == 5 );

	LengthUnit u2( 0, 8 );
	u2.fetchAsEnglish( feet, inches );
	assert( feet == 0 );
	assert( inches == 8 );

	LengthUnit u3( 5, 0 );
	u3.fetchAsEnglish( feet, inches );
	assert( feet == 5 );
	assert( inches == 0 );

	LengthUnit u4( 0, 0 );
	u4.fetchAsEnglish( feet, inches );
	assert( feet == 0 );
	assert( inches == 0 );

	LengthUnit u5( -3, 5 );
	u5.fetchAsEnglish( feet, inches );
	assert( feet == -3 );
	assert( inches == 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_constructor_english_incorrect_inches )
{
	try
	{
		LengthUnit l( 3, 15 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Inches out of range" ) );
	}

	try
	{
		LengthUnit l( 3, -1 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Inches out of range" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_constructor_metric_string )
{
	LengthUnit u1( "2.50m" );
	assert( u1.getAsMeters() == 2.50 );

	LengthUnit u2( "0.00m" );
	assert( u2.getAsMeters() == 0.00 );

	LengthUnit u3( "-2.50m" );
	assert( u3.getAsMeters() == -2.50 );

	LengthUnit u4 ( "3m" );
	assert( u4.getAsMeters() == 3.00 );
}



/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_constructor_english_string )
{
	int feet, inches;

	LengthUnit u1( "3'5\"" );
	u1.fetchAsEnglish( feet, inches );
	assert( feet == 3 );
	assert( inches == 5 );

	LengthUnit u2( "0'0\"" );
	u2.fetchAsEnglish( feet, inches );
	assert( feet == 0 );
	assert( inches == 0 );
}



/*****************************************************************************/


#define TEST_LENGTHUNIT_INCORRECT_FORMAT( str )			\
	try													\
	{													\
		LengthUnit( str );								\
		assert( ! "Exception must have been thrown" );	\
	}													\
	catch ( std::exception & e )						\
	{													\
		assert( ! strcmp( e.what(), "Bad format" ) );	\
	}


DECLARE_OOP_TEST( lengthunit_test_constructor_incorrect_string )
{
	TEST_LENGTHUNIT_INCORRECT_FORMAT( "Fignia" );
	TEST_LENGTHUNIT_INCORRECT_FORMAT( "1.25g" );
	TEST_LENGTHUNIT_INCORRECT_FORMAT( "a'3\"" );
	TEST_LENGTHUNIT_INCORRECT_FORMAT( "'3\"" );
	TEST_LENGTHUNIT_INCORRECT_FORMAT( "a'3" );
}


/*****************************************************************************/



DECLARE_OOP_TEST( lengthunit_test_conversion )
{
	LengthUnit u1( 3, 2 );
	assert( equalDoubles( u1.getAsMeters(), 0.9652L ) ); 

	int feet, inches;
	LengthUnit u2( 0.0 );
	u2.fetchAsEnglish( feet, inches );
	assert( feet == 0 );
	assert( inches == 0 );

	LengthUnit u3( 1.00 );
	u3.fetchAsEnglish( feet, inches );
	assert( feet == 3 );
	assert( inches == 3 );

	LengthUnit u4( 0.303 );
	u4.fetchAsEnglish( feet, inches );
	assert( feet == 0 );
	assert( inches == 11 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_to_metric_string )
{
	LengthUnit u1( 2.5 );
	assert( ! strcmp( u1.toMetricString(), "2.50m" ) );

	LengthUnit u2;
	assert( ! strcmp( u2.toMetricString(), "0.00m" ) );

	LengthUnit u3( -2.5 );
	assert( ! strcmp( u3.toMetricString(), "-2.50m" ) );
}



/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_to_english_string )
{
	LengthUnit u1( 3, 5 );
	assert( ! strcmp( u1.toEnglishString(), "3'5\"" ) );

	LengthUnit u2( 3, 0 );
	assert( ! strcmp( u2.toEnglishString(), "3'0\"" ) );

	LengthUnit u3( 0, 5 );
	assert( ! strcmp( u3.toEnglishString(), "0'5\"" ) );

	LengthUnit u4( 0, 0 );
	assert( ! strcmp( u4.toEnglishString(), "0'0\"" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_equality_inequality )
{
	LengthUnit u1( 2.50 );
	LengthUnit u2( 2.50 );
	LengthUnit u3( 2.51 );

	assert( u1 == u2 );
	assert( !( u1 != u2 ) );

	assert( u1 != u3 );
	assert( !( u1 == u3 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_relations )
{
	LengthUnit u1( 2.50 );
	LengthUnit u2( 2.50 );
	LengthUnit u3( 2.51 );

	assert( u1 <= u2 );
	assert( u1 <= u3 );

	assert( u1 < u3 );
	assert( ! ( u1 < u2 ) );

	assert( !( u1 > u2 ) );
	assert( !( u1 > u3 ) );

	assert( u1 >= u2 );
	assert( !( u1 >= u3 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( lengthunit_test_user_defined_literals )
{
	LengthUnit l1 = 2.5_m;
	LengthUnit l2 = 2.0_m;

	assert( l1.getAsMeters() == 2.5 );
	assert( l2.getAsMeters() == 2.0 );

	assert( ( 3.4_m ).getAsMeters() == 3.4 );
}


/*****************************************************************************/
