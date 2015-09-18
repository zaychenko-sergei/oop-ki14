// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "bitset.hpp"

#include <sstream>

/*****************************************************************************/


std::string getBitsetAsString ( Bitset const & _b )
{
	std::stringstream ss;
	ss << _b;
	return ss.str();
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_default_constructor )
{
	Bitset b;
	assert( b.getSize() == 32 );
	assert( getBitsetAsString( b ) == "00000000000000000000000000000000" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_bitsizes_constructor )
{
	Bitset b( 4 );
	assert( b.getSize() == 4 );
	assert( getBitsetAsString( b ) == "0000" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_constructor_non_positive_bitsize )
{
	try
	{
		Bitset b( 0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive bitset size" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_string_constructor )
{
	Bitset b( "01011" );
	assert( b.getSize() == 5 );
	assert( getBitsetAsString( b ) == "01011" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_empty_string_constructor )
{
	try
	{
		Bitset b( "" );
		assert( !"Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Non-positive bitset size" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_invalid_string_constructor )
{
	try
	{
		Bitset b( "ABC" );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Unexpected bitset symbol" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_constructor_large_bitsize )
{
	Bitset b( 70 );
	assert( b.getSize() == 70 );
	assert( getBitsetAsString( b ) == "0000000000000000000000000000000000000000000000000000000000000000000000" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_constructor_large_string )
{
	Bitset b( "000011110000111101010101101010100011001111001100" );
	assert( b.getSize() == 48 );
	assert( getBitsetAsString( b ) == "000011110000111101010101101010100011001111001100" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_copy_constructor )
{
	Bitset b1( "00010" );
	Bitset b2( "00000000000011111111111100000000001111111111" );
	
	Bitset b1Copy = b1;
	assert( b1Copy.getSize() == 5 );
	assert( getBitsetAsString( b1Copy ) == "00010" );

	Bitset b2Copy = b2;
	assert( b2Copy.getSize() == 44 );
	assert( getBitsetAsString( b2Copy ) == "00000000000011111111111100000000001111111111" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_copy_assignment_operator )
{
	Bitset b1( "00010" );
	Bitset b2( "00000000000011111111111100000000001111111111" );
	Bitset b3( 100 );
	Bitset b4( 10 );

	b3 = b1;
	assert( b3.getSize() == 5 );
	assert( getBitsetAsString( b3 ) == "00010" );

	b4 = b2;
	assert( b4.getSize() == 44 );
	assert( getBitsetAsString( b4 ) == "00000000000011111111111100000000001111111111" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_move_constructor )
{
	Bitset b1 = std::move( Bitset( "00010" ) );
	Bitset b2 = std::move( Bitset( "00000000000011111111111100000000001111111111" ) );

	assert( b1.getSize() == 5 );
	assert( getBitsetAsString( b1 ) == "00010" );

	assert( b2.getSize() == 44 );
	assert( getBitsetAsString( b2 ) == "00000000000011111111111100000000001111111111" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_move_assignment_operator )
{
	Bitset b1( 100 );
	Bitset b2( 5 );

	b1 = Bitset( "00010" );
	assert( b1.getSize() == 5 );
	assert( getBitsetAsString( b1 ) == "00010" );

	b2 = Bitset( "00000000000011111111111100000000001111111111" );
	assert( b2.getSize() == 44 );
	assert( getBitsetAsString( b2 ) == "00000000000011111111111100000000001111111111" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_clearAll )
{
	Bitset b1( "001101" );
	b1.clearAll();
	assert( getBitsetAsString( b1 ) == "000000" );

	Bitset b2( "00000000000011111111111100000000001111111111" );
	b2.clearAll();
	assert( getBitsetAsString( b2 ) == "00000000000000000000000000000000000000000000" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_bitwise_inversion )
{
	Bitset b1( "001101" );
	assert( getBitsetAsString( ~ b1 ) == "110010" );

	Bitset b2( "00000000000011111111111100000000001111111111" );
	assert( getBitsetAsString( ~ b2 ) == "11111111111100000000000011111111110000000000" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_logical_inversion_conversion )
{
	Bitset b1( "001101" );
	assert( b1 );

	Bitset b2( "00000000000011111111111100000000001111111111" );
	assert( b2 );

	Bitset b3;
	assert( ! b3 );

	Bitset b4( "000000000000000000000000000000000000000000000000000000000000" );
	assert( ! b4 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_bitwise_conjunction )
{
	Bitset b1( "001101" );
	Bitset b2( "101011" );
	
	assert( getBitsetAsString( b1 & b2 ) == "001001" );

	b1 &= b2;
	assert( getBitsetAsString( b1 ) == "001001" );

	Bitset b3( "100000000000000000001110000010001" );
	assert( getBitsetAsString( b2 & b3 ) == "100000" );
	assert( getBitsetAsString( b3 & b2 ) == "100000000000000000000000000000000" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_bitwise_disjunction )
{
	Bitset b1( "001101" );
	Bitset b2( "101011" );

	assert( getBitsetAsString( b1 | b2 ) == "101111" );

	b1 |= b2;
	assert( getBitsetAsString( b1 ) == "101111" );

	Bitset b3( "100100000000000000001110000010001" );
	assert( getBitsetAsString( b2 | b3 ) == "101111" );
	assert( getBitsetAsString( b3 | b2 ) == "101111000000000000001110000010001" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( bitset_test_get_set_clear_in_range )
{
	Bitset b( "011" );
	assert( ! b.isSet( 0 ) );
	assert(   b.isSet( 1 ) );
	assert(   b.isSet( 2 ) );

	b.set( 0 );
	assert( b.isSet( 0 ) );

	b.clear( 2 );
	assert( ! b.isSet( 2 ) );

	assert( getBitsetAsString( b ) == "110" );
}


/*****************************************************************************/

#define CHECK_OUT_OF_RANGE( operation )							\
	try                                                         \
    {                                                           \
		operation;                                              \
    }                                                           \
    catch ( const std::exception & e )                          \
    {                                                           \
        assert( ! strcmp( e.what(), "Index out of range" ) );   \
    }


DECLARE_OOP_TEST( bitset_test_get_set_clear_out_of_range )
{
	Bitset b( "011" );

	CHECK_OUT_OF_RANGE( b.isSet( -1 ) );
	CHECK_OUT_OF_RANGE( b.isSet( 3 ) );
	CHECK_OUT_OF_RANGE( b.set( -1 ) );
	CHECK_OUT_OF_RANGE( b.set( 3 ) );
	CHECK_OUT_OF_RANGE( b.clear( -1 ) );
	CHECK_OUT_OF_RANGE( b.clear( 3 ) );
}



/*****************************************************************************/
