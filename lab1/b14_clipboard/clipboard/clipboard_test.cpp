// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "clipboard.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_constructor )
{
	Clipboard c1;
	assert( c1.getMaxBufferSize() == 4096 );
	assert( c1.getCurrentDataSize() == 0 );
	assert( c1.getCurrentFormat() == Clipboard::Format_Empty );

	Clipboard c2( 100000 );
	assert( c2.getMaxBufferSize() == 100000);
	assert( c2.getCurrentDataSize() == 0 );
	assert( c2.getCurrentFormat() == Clipboard::Format_Empty );
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_constructor_wrong_size )
{
	try
	{
		Clipboard c( 0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Buffer size must be positive" ) );
	}

	try
	{
		Clipboard c( -100 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Buffer size must be positive" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_put_small_text )
{
	Clipboard c;
	c.putText( "Hello" );
	assert( c.getCurrentDataSize() == 6 );
	assert( c.getCurrentFormat() == Clipboard::Format_Text );

	char buf[ 100 ];
	c.copyTextTo( buf );
	assert( ! strcmp( buf, "Hello" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_put_text_longer_than_buffer )
{
	Clipboard c( 10 );
	c.putText( "Hello magic world" );
	assert( c.getCurrentDataSize() == 10 );
	assert( c.getCurrentFormat() == Clipboard::Format_Text );

	char buf[ 100 ];
	c.copyTextTo( buf );
	assert( ! strcmp( buf, "Hello mag" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_put_small_binary )
{
	Clipboard c;
	int data[] = { 1, 2, 3 };
	bool accepted = c.putBinaryData( data, sizeof( data ) );
	assert( accepted );
	assert( c.getCurrentDataSize() == 3 * sizeof( int ) );
	assert( c.getCurrentFormat() == Clipboard::Format_Binary );

	int data2[ 4 ] = { 0, 0, 0, 0 };
	c.copyBinaryDataTo( data2 );
	assert( ! memcmp( data, data2, 3 * sizeof( int ) ) );
	assert( data2[ 3 ] == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_put_binary_larger_than_buffer )
{
	Clipboard c( 10 );
	int data[] = { 1, 2, 3 };
	bool accepted = c.putBinaryData( data, sizeof( data ) );
	assert( ! accepted );
	assert( c.getCurrentDataSize() == 0 );
	assert( c.getCurrentFormat() == Clipboard::Format_Empty );
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_append_text_to_different_modes )
{
	Clipboard c1, c2, c3;
	
	c1 += "Hello";

	c2.putText( "Hello" );
	c2 += " World";

	c3.putBinaryData( & clipboard_test_append_text_to_different_modes, 100 );
	c3 += " World";

	assert( c1.getCurrentDataSize() == 6 );
	assert( c1.getCurrentFormat() == Clipboard::Format_Text );
	char buf[ 100 ];
	c1.copyTextTo( buf );
	assert( ! strcmp( buf, "Hello" ) );

	assert( c2.getCurrentDataSize() == 12 );
	assert( c2.getCurrentFormat() == Clipboard::Format_Text );
	c2.copyTextTo( buf );
	assert( ! strcmp( buf, "Hello World" ) );

	assert( c3.getCurrentDataSize() == 100 );
	assert( c3.getCurrentFormat() == Clipboard::Format_Binary );
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_clear )
{
	Clipboard c1, c2, c3;
	c1.putText( "Hello" );
	c2.putBinaryData( & c1, 10 );

	c1.clear();
	c2.clear();
	c3.clear();

	assert( c1.getCurrentDataSize() == 0 );
	assert( c2.getCurrentDataSize() == 0 );
	assert( c3.getCurrentDataSize() == 0 );

	assert( c1.getCurrentFormat() == Clipboard::Format_Empty );
	assert( c2.getCurrentFormat() == Clipboard::Format_Empty );
	assert( c3.getCurrentFormat() == Clipboard::Format_Empty );
}
	


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_operator_bool )
{
	Clipboard c1, c2, c3;
	c1.putText( "Hello" );
	c2.putBinaryData( & c1, 10 );

	assert( c1 );
	assert( c2 );
	assert( ! c3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_copy_text_when_having_non_text )
{
	Clipboard c1;
	c1.putBinaryData( & c1, 10 );

	char buf[ 100 ];
	try
	{
		c1.copyTextTo( buf );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "No text in clipboard" ) );
	}

	Clipboard c2;

	try
	{
		c2.copyTextTo( buf );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "No text in clipboard" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_copy_binary_when_having_non_binary )
{
	Clipboard c1;
	c1.putText( "Hello" );

	int data[ 100 ];
	try
	{
		c1.copyBinaryDataTo( data );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "No binary data in clipboard" ) );
	}

	Clipboard c2;

	try
	{
		c2.copyBinaryDataTo( data );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "No binary data in clipboard" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( clipboard_test_copy_and_move )
{
	Clipboard c1;
	c1.putText( "Hello" );

	Clipboard c2 = c1;
	assert( c2.getCurrentDataSize() == 6 );
	assert( c2.getCurrentFormat() == Clipboard::Format_Text );
	char buf[ 100 ];
	c2.copyTextTo( buf );
	assert( ! strcmp( buf, "Hello" ) );

	Clipboard c3;
	c3 = c1;
	assert( c3.getCurrentDataSize() == 6 );
	assert( c3.getCurrentFormat() == Clipboard::Format_Text );
	c3.copyTextTo( buf );
	assert( ! strcmp( buf, "Hello" ) );

	c1.clear();
	int x = 0x55555555;
	c1.putBinaryData( & x, sizeof( int ) );

	Clipboard c4 = std::move( c1 );
	assert( c4.getCurrentDataSize() == 4 );
	assert( c4.getCurrentFormat() == Clipboard::Format_Binary );
	int data[ 2 ] = { 0, 0 };
	c4.copyBinaryDataTo( & data );
	assert( data[ 0 ] == x );
	assert( data[ 1 ] == 0 );

	Clipboard c5;
	c5 = std::move( c4 );

	assert( c5.getCurrentDataSize() == 4 );
	assert( c5.getCurrentFormat() == Clipboard::Format_Binary );
	int data2[ 2 ] = { 0, 0 };
	c5.copyBinaryDataTo( & data2 );
	assert( data2[ 0 ] == x );
	assert( data2[ 1 ] == 0 );

	assert( c4.getCurrentFormat() == Clipboard::Format_Empty );

}


/*****************************************************************************/
