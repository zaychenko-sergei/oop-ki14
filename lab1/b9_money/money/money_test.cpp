// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "money.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( money_test_constructor_default )
{
	Money m;
	assert( m.getDollars() == 0 );
	assert( m.getCents() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_constructor_concrete )
{
	Money m1( 100, 50 );
	assert( m1.getDollars() == 100 );
	assert( m1.getCents() == 50 );

	Money m2( -30, 40 );
	assert( m2.getDollars() == -30 );
	assert( m2.getCents() == 40 );

	Money m3( 100, 0 );
	assert( m3.getDollars() == 100 );
	assert( m3.getCents() == 0 );

	Money m4( 0, 0 );
	assert( m4.getDollars() == 0 );
	assert( m4.getCents() == 0 );

	Money m5( -20, 0 );
	assert( m5.getDollars() == -20 );
	assert( m5.getCents() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_constructor_concrete_invalid_cents )
{
	try
	{
		Money m( 10, -1 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid cents" ) );
	}

	try
	{
		Money m( 10, 100 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid cents" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_constructor_double )
{
	Money m1( 100.00 );
	Money m2( 100.01 );
	Money m3( 100.001 );
	Money m4( 0.00 );
	Money m5( -2.00 );
	Money m6( -2.34 );

	assert( m1.getDollars() == 100 );
	assert( m1.getCents()   == 0 );

	assert( m2.getDollars() == 100 );
	assert( m2.getCents()   == 1 );

	assert( m3.getDollars() == 100 );
	assert( m3.getCents()   == 0 );

	assert( m4.getDollars() == 0 );
	assert( m4.getCents()   == 0 );

	assert( m5.getDollars() == -2 );
	assert( m5.getCents()   == 0 );

	assert( m6.getDollars() == -2 );
	assert( m6.getCents()   == 34 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_constructor_correct_string )
{
	Money m1( "0.0" );
	assert( m1.getDollars() == 0 );
	assert( m1.getCents()   == 0 );

	Money m2( "10.0" );
	assert( m2.getDollars() == 10 );
	assert( m2.getCents()   == 0 );

	Money m3( "10.30" );
	assert( m3.getDollars() == 10 );
	assert( m3.getCents()   == 30 );

	Money m4( "0.55" );
	assert( m4.getDollars() == 0 );
	assert( m4.getCents()   == 55 );

	Money m5( "-2.35" );
	assert( m5.getDollars() == -2 );
	assert( m5.getCents()   == 35 );

	Money m6( "-2.00" );
	assert( m6.getDollars() == -2 );
	assert( m6.getCents()   == 0 );
}


/*****************************************************************************/


#define TEST_INCORRECT_MONEY_FORMAT( sample )						\
	try																\
	{																\
		Money m( sample );											\
	}																\
	catch ( std::exception & e )									\
	{																\
		assert( ! strcmp( e.what(), "Incorrect money format" ) );	\
	}


DECLARE_OOP_TEST( money_test_constructor_incorrect_string )
{
	TEST_INCORRECT_MONEY_FORMAT( "Hello" );
	TEST_INCORRECT_MONEY_FORMAT( "123" );
	TEST_INCORRECT_MONEY_FORMAT( "1.2." );
	TEST_INCORRECT_MONEY_FORMAT( "1.2.3" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_constructor_correct_string_negative_cents )
{
	try
	{
		Money m( "10.-1" );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid cents" ) );
	}

	try
	{
		Money m( "10.100" );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid cents" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_as_string )
{
	Money m1( 20, 30 );
	assert( ! strcmp( m1.asString(), "20.30" ) );

	Money m2( 20, 33 );
	assert( ! strcmp( m2.asString(), "20.33" ) );

	Money m3( 20, 0 );
	assert( ! strcmp( m3.asString(), "20.00" ) );

	Money m4( 20, 5 );
	assert( ! strcmp( m4.asString(), "20.05" ) );

	Money m5( 0, 10 );
	assert( ! strcmp( m5.asString(), "0.10" ) );

	Money m6( 0, 0 );
	assert( ! strcmp( m6.asString(), "0.00" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_equality_inequality )
{
	Money m1( 10, 00 );
	Money m2( 10, 30 );
	Money m3( 10, 00 );
	Money m4( 10, 30 );

	assert( m1 == m3 );
	assert( m2 == m4 );

	assert( !( m1 != m3 ) );
	assert( !( m2 != m4 ) );

	assert( m1 != m2 );
	assert( m3 != m4 );

	assert( !( m1 == m2 ) );
	assert( !( m3 == m4 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_relational_operators )
{
	Money m1( 10, 00 );
	Money m2( 10, 10 );

	assert( m1 < m2 );
	assert( m1 <= m2 );
	assert( !( m1 > m2 ) );
	assert( !( m1 >= m2 ) );

	assert( m1 <= m1 );
	assert( m1 >= m1 );
	assert( !( m1 < m1 ) );
	assert( !( m1 > m1 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_add_subtract )
{
	Money m1( 10, 30 );
	m1 += Money( 0, 20 );
	assert( m1.getDollars() == 10 );
	assert( m1.getCents() == 50 );

	Money m2 = m1 + Money( 10, 25 );
	assert( m2.getDollars() == 20 );
	assert( m2.getCents() == 75 );
	assert( m1.getDollars() == 10 );
	assert( m1.getCents() == 50 );

	m1 -= Money( 10, 00 );
	assert( m1.getDollars() == 0 );
	assert( m1.getCents() == 50 );

	m2 = m1 - Money( 0, 10 );
	assert( m2.getDollars() == 0 );
	assert( m2.getCents() == 40 );
	assert( m1.getDollars() == 0 );
	assert( m1.getCents() == 50 );

	Money m3( 1, 2 );
	m3 -= Money( 0, 10 );
	assert( m3.getDollars() == 0 );
	assert( m3.getCents() == 92 );

	Money m4( 0, 10 );
	m4 -= Money( 1, 50 );
	assert( m4.getDollars() == -1 );
	assert( m4.getCents() == 40 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_multiply_divide )
{
	Money m1( 10, 20 );
	m1 *= 3;
	assert( m1.getDollars() == 30 );
	assert( m1.getCents() == 60 );

	Money m2( 10, 50 );
	m2 *= 5;
	assert( m2.getDollars() == 52 );
	assert( m2.getCents() == 50 );

	Money m3 = m1 * 2;
	assert( m3.getDollars() == 61 );
	assert( m3.getCents() == 20 );
	assert( m1.getDollars() == 30 );
	assert( m1.getCents() == 60 );

	Money m4 = m1 / 2;
	assert( m4.getDollars() == 15 );
	assert( m4.getCents() == 30 );
	assert( m1.getDollars() == 30 );
	assert( m1.getCents() == 60 );

	m1 /= 3;
	assert( m1.getDollars() == 10 );
	assert( m1.getCents() == 20 );

	Money m5( 0, 7 );
	m5 /= 2;
	assert( m5.getDollars() == 0 );
	assert( m5.getCents() == 3 );

	Money m6( 1, 0 );
	m6 /= 2;
	assert( m6.getDollars() == 0 );
	assert( m6.getCents() == 50 );

	Money m7;
	m7 / 2;
	assert( m7 == Money() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_divide_on_zero )
{
	Money m( 10, 10 );
	try
	{
		m /= 0;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Division by zero" ) );
	}

	try
	{
		Money m2 = m / 0;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Division by zero" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( money_test_using_literals )
{
	Money m1 = 25.20_USD;
	assert( m1.getDollars() == 25 );
	assert( m1.getCents() == 20 );

	Money m2 = 10.00_USD;
	assert( m2.getDollars() == 10 );
	assert( m2.getCents() == 0 );

	Money m3 = 0.170_USD;
	assert( m3.getDollars() == 0 );
	assert( m3.getCents() == 17 );

	Money m4 = 1.181_USD;
	assert( m4.getDollars() == 1 );
	assert( m4.getCents() == 18 );

	assert( !strcmp( ( 5.5_USD ).asString(), "5.50" ) );
}


/*****************************************************************************/
