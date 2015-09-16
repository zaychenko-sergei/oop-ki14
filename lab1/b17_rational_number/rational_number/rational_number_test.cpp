// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include "utils.hpp"

#include <sstream>

#include "rational_number.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_constructor_simple_case )
{
	RationalNumber rn( 2, 3 );

	assert( rn.getNumerator() == 2 );
	assert( rn.getDenominator() == 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_constructor_negative_case )
{
	RationalNumber r1( -1,  3 );
	RationalNumber r2(  1, -3 );
	RationalNumber r3( -1, -3 );

	assert( r1.getNumerator() == -1 );
	assert( r1.getDenominator() == 3 );

	assert( r2.getNumerator() == -1 );
	assert( r2.getDenominator() == 3 );

	assert( r3.getNumerator() == 1 );
	assert( r3.getDenominator() == 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_constructor_nonoptimal_case )
{
	RationalNumber rn1( 2, 4 );
	RationalNumber rn2( 3, 6 );
	RationalNumber rn3( 462, 1071 );
	RationalNumber rn4( 5, 1 );
	RationalNumber rn5( 6, 3 );

	assert( rn1.getNumerator() == 1 );
	assert( rn1.getDenominator() == 2 );

	assert( rn2.getNumerator() == 1 );
	assert( rn2.getDenominator() == 2 );

	assert( rn3.getNumerator() == 22 );
	assert( rn3.getDenominator() == 51 );
	
	assert( rn4.getNumerator() == 5 );
	assert( rn4.getDenominator() == 1 );

	assert( rn5.getNumerator() == 2 );
	assert( rn5.getDenominator() == 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_constructor_zero_denominator )
{
	try
	{
		RationalNumber rn( 2, 0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Zero denominator" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_equality )
{
	RationalNumber r1( 1, 2 );
	RationalNumber r2( 2, 4 );
	RationalNumber r3( 1, 3 );

	assert( r1 == r1 );
	assert( r1 == r2 );
	assert( !( r1 == r3 ) );

	assert( !( r1 != r1 ) );
	assert( !( r1 != r2 ) );
	assert( r1 != r3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_relations_same_denominator )
{
	RationalNumber r1( 1, 5 );
	RationalNumber r2( 2, 5 );
	RationalNumber r3( 3, 5 );

	assert( !( r1 < r1 ) );
	assert( r1 < r2 );
	assert( r2 < r3 );
	assert( !( r2 < r1 ) );
	assert( !( r3 < r2 ) );

	assert( r1 <= r1 );
	assert( r1 <= r2 );
	assert( r2 <= r3 );
	assert( !( r2 <= r1 ) );
	assert( !( r3 <= r2 ) );

	assert( !( r1 > r1 ) );
	assert( !( r1 > r2 ) );
	assert( !( r2 > r3 ) );
	assert( r2 > r1 );
	assert( r3 > r2 );

	assert( r1 >= r1);
	assert( !( r1 >= r2 ) );
	assert( !( r2 >= r3 ) );
	assert( r2 >= r1 );
	assert( r3 >= r2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_relations_different_denominator )
{
	RationalNumber r1( 2, 3 );
	RationalNumber r2( 4, 5 );
	RationalNumber r3( 5, 6 );

	assert( !( r1 < r1 ) );
	assert( r1 < r2 );
	assert( r2 < r3 );
	assert( !( r2 < r1 ) );
	assert( !( r3 < r2 ) );

	assert( r1 <= r1 );
	assert( r1 <= r2 );
	assert( r2 <= r3 );
	assert( !( r2 <= r1 ) );
	assert( !( r3 <= r2 ) );

	assert( !( r1 > r1 ) );
	assert( !( r1 > r2 ) );
	assert( !( r2 > r3 ) );
	assert( r2 > r1 );
	assert( r3 > r2 );

	assert( r1 >= r1 );
	assert( !( r1 >= r2 ) );
	assert( !( r2 >= r3 ) );
	assert( r2 >= r1 );
	assert( r3 >= r2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_addition )
{
	RationalNumber r1( 1, 3 );
	RationalNumber r2( 2, 3 );
	RationalNumber r3( 1, 4 );

	RationalNumber x0 = r1 + r1;
	assert( x0.getNumerator() == 2 );
	assert( x0.getDenominator() == 3 );

	RationalNumber x1 = r1 + r2;
	assert( x1.getNumerator() == 1 );
	assert( x1.getDenominator() == 1 );

	RationalNumber x2 = r1 + r3;
	assert( x2.getNumerator() == 7 );
	assert( x2.getDenominator() == 12 );

	r2 += r3;
	assert( r2.getNumerator() == 11 );
	assert( r2.getDenominator() == 12 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_subtraction )
{
	RationalNumber r1( 1, 3 );
	RationalNumber r2( 2, 3 );
	RationalNumber r3( 1, 4 );

	RationalNumber x0 = r1 - r1;
	assert( x0.getNumerator() == 0 );
	assert( x0.getDenominator() == 1 );

	RationalNumber x1 = r2 - r1;
	assert( x1.getNumerator() == 1 );
	assert( x1.getDenominator() == 3 );

	RationalNumber x2 = r2 - r3;
	assert( x2.getNumerator() == 5 );
	assert( x2.getDenominator() == 12 );

	r1 -= r3;
	assert( r1.getNumerator() == 1 );
	assert( r1.getDenominator() == 12 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_multiplication )
{
	RationalNumber r1( 1, 3 );
	RationalNumber r2( 2, 3 );
	RationalNumber r3( 1, 4 );

	RationalNumber x0 = r1 * r1;
	assert( x0.getNumerator() == 1 );
	assert( x0.getDenominator() == 9 );

	RationalNumber x1 = r1 * r2;
	assert( x1.getNumerator() == 2 );
	assert( x1.getDenominator() == 9 );

	RationalNumber x2 = r2 * r3;
	assert( x2.getNumerator() == 1 );
	assert( x2.getDenominator() == 6 );

	r1 *= r3;
	assert( r1.getNumerator() == 1 );
	assert( r1.getDenominator() == 12 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_division )
{
	RationalNumber r1( 1, 3 );
	RationalNumber r2( 2, 3 );
	RationalNumber r3( 1, 4 );

	RationalNumber x0 = r1 / r1;
	assert( x0.getNumerator() == 1 );
	assert( x0.getDenominator() == 1 );

	RationalNumber x1 = r2 / r1;
	assert( x1.getNumerator() == 2 );
	assert( x1.getDenominator() == 1 );

	RationalNumber x2 = r2 / r3;
	assert( x2.getNumerator() == 8 );
	assert( x2.getDenominator() == 3 );

	r1 /= r2;
	assert( r1.getNumerator() == 1 );
	assert( r1.getDenominator() == 2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_operator_double )
{
	RationalNumber r1( 1, 2 );
	RationalNumber r2( 2, 5 );
	RationalNumber r3( 1, 4 );

	double x1 = r1;
	double x2 = r2;
	double x3 = r3;

	assert( x1 == 0.5 );
	assert( x2 == 0.4 );
	assert( x3 == 0.25 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rational_number_test_stream_output )
{
	RationalNumber r{ 1, 3 };
	std::stringstream s;
	s << r;

	assert( s.str() == "1/3" );
}


/*****************************************************************************/
