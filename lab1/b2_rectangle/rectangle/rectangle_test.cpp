// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "rectangle.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_ConstructorTopLeftRightBottom )
{
	Rectangle r( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	assert( r.getTopLeft() == Point( 0.0, 5.0 ) );
	assert( r.getBottomRight() == Point( 3.0, 1.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_ConstructorTopLeftWidthHeight )
{
	Rectangle r( Point( 0.0, 5.0 ), 2.0, 4.0 );
	assert( r.getTopLeft() == Point( 0.0, 5.0 ) );
	assert( r.getBottomRight() == Point( 2.0, 1.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_ConstructorTopLeftRightBottom_wrong )
{
	try
	{
		Rectangle r( Point( 0.0, 5.0 ), Point( -2.0, 3.0 ) );
		assert( ! "Exception expected" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid rectangle coordinates" ) );
	}

	try
	{
		Rectangle r( Point( 0.0, 5.0 ), Point( 2.0, 6.0 ) );
		assert( ! "Exception expected" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid rectangle coordinates" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_ConstructorTopLeftWidthHeight_wrong )
{
	try
	{
		Rectangle r( Point( 0.0, 5.0 ), -2.0, 3.0 );
		assert( ! "Exception expected" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid rectangle coordinates" ) );
	}

	try
	{
		Rectangle r( Point( 0.0, 5.0 ), 2.0, -1.0 );
		assert( ! "Exception expected" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid rectangle coordinates" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_AccessAllPoints )
{
	Rectangle r1( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	assert( r1.getTopLeft() == Point( 0.0, 5.0 ) );
	assert( r1.getTopRight() == Point( 3.0, 5.0 ) );
	assert( r1.getBottomLeft() == Point( 0.0, 1.0 ) );
	assert( r1.getBottomRight() == Point( 3.0, 1.0 ) );

	Rectangle r2( Point( 0.0, 5.0 ), 2.0, 3.0 );
	assert( r2.getTopLeft() == Point( 0.0, 5.0 ) );
	assert( r2.getTopRight() == Point( 2.0, 5.0 ) );
	assert( r2.getBottomLeft() == Point( 0.0, 2.0 ) );
	assert( r2.getBottomRight() == Point( 2.0, 2.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_AccessWidthHeight )
{
	Rectangle r1( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	assert( equalDoubles( r1.getWidth(), 3.0 ) );
	assert( equalDoubles( r1.getHeight(), 4.0 ) );

	Rectangle r2( Point( 0.0, 5.0 ), 2.0, 3.0 );
	assert( equalDoubles( r2.getWidth(), 2.0 ) );
	assert( equalDoubles( r2.getHeight(), 3.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_getPerimeter )
{
	Rectangle r( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	assert( equalDoubles( r.getPerimeter(), 14.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_getArea )
{
	Rectangle r( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	assert( equalDoubles( r.getArea(), 12.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_EqualityInequality )
{
	Rectangle r1( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	Rectangle r2( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	Rectangle r3( Point( 0.0, 5.0 ), Point( 2.0, 1.0 ) );
	Rectangle r4( Point( 0.1, 2.0 ), Point( 2.0, 1.0 ) );
	
	assert( r1 == r2 );
	assert( !( r1 != r2 ) );

	assert( !( r1 == r3 ) );
	assert(    r1 != r3   );

	assert( !( r1 == r4 ) );
	assert(    r1 != r4   );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_containsPoint )
{
	Rectangle r( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	assert( r.contains( Point( 1.5, 3.0 ) ) );
	assert( r.contains( Point( 0.0, 5.0 ) ) );
	assert( r.contains( Point( 3.0, 3.0 ) ) );
	
	assert( ! r.contains( Point( 0.0, 0.0 ) ) );
	assert( ! r.contains( Point( 4.0, 3.0 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_containsSegment )
{
	Rectangle r( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	assert( r.contains( Point( 1.0, 4.0 ), Point( 2.0, 2.0 ) ) );
	assert( r.contains( Point( 0.0, 1.0 ), Point( 3.0, 5.0 ) ) );

	assert( ! r.contains( Point( 0.0, 6.0 ), Point( 2.0, 2.0 ) ) );
	assert( ! r.contains( Point( 1.0, 4.0 ), Point( 2.0, 0.0 ) ) );
	assert( ! r.contains( Point( 8.0, 7.0 ), Point( 9.0, 7.0 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_intersects )
{
	Rectangle r1( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	Rectangle r2( Point( 1.0, 3.0 ), Point( 5.0, 0.0 ) );
	Rectangle r3( Point( 0.0, 0.0 ), Point( 5.0, -2.0 ) );
	Rectangle r4( Point( 4.0, 3.0 ), Point( 5.0, 2.0 ) );

	assert( r1.intersects( r2 ) );
	assert( ! r1.intersects( r3 ) );
	assert( ! r1.intersects( r4 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rectangle_test_covers )
{
	Rectangle r1( Point( 0.0, 5.0 ), Point( 3.0, 1.0 ) );
	Rectangle r2( Point( 1.0, 4.0 ), Point( 2.0, 2.0 ) );
	Rectangle r3( Point( 1.0, 4.0 ), Point( 3.5, 2.0 ) );
	Rectangle r4( Point( 1.0, 4.0 ), Point( 2.0, 0.0 ) );

	assert( r1.covers( r2 ) );
	assert( ! r1.covers( r3 ) );
	assert( ! r1.covers( r4 ) );
}


/*****************************************************************************/
