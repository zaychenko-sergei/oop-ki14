// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include "utils.hpp"

#include "numeric_range.hpp"

#include <sstream>
#include <vector>

/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_default_constructor )
{
	NumericRange r;

	assert( r.getLowBound() == 0 );
	assert( r.getHighBound() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_concrete_range_constructor )
{
	NumericRange r1( 2, 5 );
	NumericRange r2( 3, 3 );
	NumericRange r3( -2, 4 );

	assert( r1.getLowBound() == 2 );
	assert( r1.getHighBound() == 5 );

	assert( r2.getLowBound() == 3 );
	assert( r2.getHighBound() == 3 );

	assert( r3.getLowBound() == -2 );
	assert( r3.getHighBound() == 4 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_concrete_range_constructor_invalid_range )
{
	try
	{
		NumericRange r( 1, 0 );
		assert( !"Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Low bound higher than high bound" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_string_constructor )
{
	NumericRange r1( "[2:5]" );
	NumericRange r2( "[3:3]" );
	NumericRange r3( "[-2:4]" );

	assert( r1.getLowBound() == 2 );
	assert( r1.getHighBound() == 5 );

	assert( r2.getLowBound() == 3 );
	assert( r2.getHighBound() == 3 );

	assert( r3.getLowBound() == -2 );
	assert( r3.getHighBound() == 4 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_string_bad_format )
{
	const char * samples[] = { "[2:5", "[2-5]", "2:5]", "[2]", "2:5", "[2:5:7]" };
	for ( const char * s : samples )
	{
		try
		{
			NumericRange r( s );
			assert( !"Exception must have been thrown" );
		}
		catch ( std::exception & e )
		{
			assert( !strcmp( e.what(), "Invalid format" ) );
		}
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_concrete_string_constructor_invalid_range )
{
	try
	{
		NumericRange r( "[3:1]" );
		assert( !"Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Low bound higher than high bound" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_width )
{
	NumericRange r0;
	NumericRange r1( 2, 5 );
	NumericRange r2( 3, 3 );
	NumericRange r3( -2, 4 );

	assert( r0.getWidth() == 1 );
	assert( r1.getWidth() == 4 );
	assert( r2.getWidth() == 1 );
	assert( r3.getWidth() == 7 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_contains )
{
	NumericRange r1( 2, 4 );
	NumericRange r2( 3, 3 );

	assert( ! r1.contains( 1 ) );
	assert( r1.contains( 2 ) );
	assert( r1.contains( 3 ) );
	assert( r1.contains( 4 ) );
	assert( ! r1.contains( 5 ) );

	assert( ! r2.contains( 2 ) );
	assert( r2.contains( 3 ) );
	assert( ! r2.contains( 4 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_intersectsWith )
{
	NumericRange r( 2, 5 );
	
	NumericRange r1( 3, 4 );
	NumericRange r2( 3, 5 );
	NumericRange r3( 3, 7 );
	NumericRange r4( 2, 4 );
	NumericRange r5( 0, 4 );
	NumericRange r6( 0, 2 );
	NumericRange r7( 0, 1 );
	NumericRange r8( 6, 8 );
	NumericRange r9( 0, 8 );
	
	assert( r.intersectsWith( r1 ) );
	assert( r.intersectsWith( r2 ) );
	assert( r.intersectsWith( r3 ) );
	assert( r.intersectsWith( r4 ) );
	assert( r.intersectsWith( r5 ) );
	assert( r.intersectsWith( r6 ) );
	assert( ! r.intersectsWith( r7 ) );
	assert( ! r.intersectsWith( r8 ) );
	assert( r.intersectsWith( r9 ) );
	assert( r.intersectsWith( r ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_includes )
{
	NumericRange r( 2, 5 );

	NumericRange r1( 3, 4 );
	NumericRange r2( 3, 5 );
	NumericRange r3( 3, 7 );
	NumericRange r4( 2, 4 );
	NumericRange r5( 0, 4 );
	NumericRange r6( 0, 2 );
	NumericRange r7( 0, 1 );
	NumericRange r8( 6, 8 );
	NumericRange r9( 0, 8 );

	assert( r.includes( r1 ) );
	assert( r.includes( r2 ) );
	assert( ! r.includes( r3 ) );
	assert( r.includes( r4 ) );
	assert( ! r.includes( r5 ) );
	assert( ! r.includes( r6 ) );
	assert( ! r.includes( r7 ) );
	assert( ! r.includes( r8 ) );
	assert( ! r.includes( r9 ) );
	assert( r.includes( r ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_adjacentTo )
{
	NumericRange r( 2, 5 );

	NumericRange r1( 3, 4 );
	NumericRange r2( 3, 5 );
	NumericRange r3( 3, 7 );
	NumericRange r4( 2, 4 );
	NumericRange r5( 0, 4 );
	NumericRange r6( 0, 2 );
	NumericRange r7( 0, 1 );
	NumericRange r8( 6, 8 );
	NumericRange r9( 0, 8 );

	assert( ! r.adjacentTo( r1 ) );
	assert( ! r.adjacentTo( r2 ) );
	assert( ! r.adjacentTo( r3 ) );
	assert( ! r.adjacentTo( r4 ) );
	assert( ! r.adjacentTo( r5 ) );
	assert( ! r.adjacentTo( r6 ) );
	assert( r.adjacentTo( r7 ) );
	assert( r.adjacentTo( r8 ) );
	assert( ! r.adjacentTo( r9 ) );
	assert( ! r.adjacentTo( r ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_belongsTo )
{
	NumericRange r( 2, 5 );

	NumericRange r1( 3, 4 );
	NumericRange r2( 3, 5 );
	NumericRange r3( 3, 7 );
	NumericRange r4( 2, 4 );
	NumericRange r5( 0, 4 );
	NumericRange r6( 0, 2 );
	NumericRange r7( 0, 1 );
	NumericRange r8( 6, 8 );
	NumericRange r9( 0, 8 );

	assert( ! r.belongsTo( r1 ) );
	assert( ! r.belongsTo( r2 ) );
	assert( ! r.belongsTo( r3 ) );
	assert( ! r.belongsTo( r4 ) );
	assert( ! r.belongsTo( r5 ) );
	assert( ! r.belongsTo( r6 ) );
	assert( ! r.belongsTo( r7 ) );
	assert( ! r.belongsTo( r8 ) );
	assert( r.belongsTo( r9 ) );
	assert( r.belongsTo( r ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_relations )
{
	NumericRange r1( 2, 5 );
	NumericRange r2( 3, 6 );
	NumericRange r3( 1, 4 );
	NumericRange r4( 2, 4 );
	NumericRange r5( 1, 5 );

	assert( r1 == r1 );
	assert( !( r1 == r2 ) );

	assert( !( r1 != r1 ) );
	assert( r1 != r2 );

	assert( !( r1 < r1 ) );
	assert( r1 < r2 );
	assert( !( r1 < r3 ) );
	assert( !( r1 < r4 ) );
	assert( !( r1 < r5 ) );

	assert( r1 <= r1 );
	assert( r1 <= r2 );
	assert( !( r1 <= r3 ) );
	assert( !( r1 <= r4 ) );
	assert( !( r1 <= r5 ) );

	assert( !( r1 > r1 ) );
	assert( !( r1 > r2 ) );
	assert( r1 > r3 );
	assert( r1 > r4 );
	assert( r1 > r5 );

	assert( r1 >= r1 );
	assert( !( r1 >= r2 ) );
	assert( r1 >= r3 );
	assert( r1 >= r4 );
	assert( r1 >= r5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_range_based_loop )
{
	NumericRange r0;
	NumericRange r1( 2, 5 );
	NumericRange r2( 3, 3 );

	std::vector< int > v0Result, v0Pattern = { 0 };
	for ( int x : r0 )
		v0Result.push_back( x );
	assert( v0Result == v0Pattern );

	std::vector< int > v1Result, v1Pattern = { 2, 3, 4, 5 };
	for ( int x : r1 )
		v1Result.push_back( x );
	assert( v1Result == v1Pattern );

	std::vector< int > v2Result, v2Pattern = { 3 };
	for ( int x : r2 )
		v2Result.push_back( x );
	assert( v2Result == v2Pattern );
}


/*****************************************************************************/


DECLARE_OOP_TEST( numeric_range_test_stream_output )
{
	NumericRange r{ 1, 6 };
	std::stringstream s;
	s << r;

	assert( s.str() == "[1:6]" );
}


/*****************************************************************************/
