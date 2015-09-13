// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "realarray.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_constructor_defaultdata )
{
	RealArray a( 3 );
	assert( a.getSize() == 3 );
	assert( a[0] == 0 );
	assert( a[1] == 0 );
	assert( a[2] == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_constructor_concretedata )
{
	double data[] = { 2.0, 3.0, 4.0 };
	RealArray a( 3, data );
	assert( a.getSize() == 3 );
	assert( a[0] == 2.0 );
	assert( a[1] == 3.0 );
	assert( a[2] == 4.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_constructor_initializer_list )
{
	RealArray a{ 2.0, 3.0, 4.0 };
	assert( a.getSize() == 3 );
	assert( a[ 0 ] == 2.0 );
	assert( a[ 1 ] == 3.0 );
	assert( a[ 2 ] == 4.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_constructor_defaultdata_bad_size )
{
	try
	{
		RealArray a( 0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Size must be positive" ) );
	}

}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_constructor_concretedata_bad_size )
{
	try
	{
		RealArray a( 0, nullptr );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Size must be positive" ) );
	}

}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_constructor_concretedata_bad_data )
{
	try
	{
		RealArray a( 3, nullptr );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Data cannot be NULL" ) );
	}

}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_constructor_empty_initializer_list )
{
	try
	{
		RealArray a{};
		assert( !"Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Size must be positive" ) );
	}

}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_copy_constructor )
{
	double data[] = { 2.0, 3.0, 4.0 };
	RealArray a( 3, data );
	
	RealArray * pB = new RealArray( a );
	assert( pB->getSize() == 3 );
	assert( (*pB)[0] == 2.0 );
	assert( (*pB)[1] == 3.0 );
	assert( (*pB)[2] == 4.0 );

	delete pB;

	assert( a.getSize() == 3 );
	assert( a[0] == 2.0 );
	assert( a[1] == 3.0 );
	assert( a[2] == 4.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_move_constructor )
{
	double data[] = { 2.0, 3.0, 4.0 };
	RealArray a( 3, data );
	RealArray b = std::move( a );
	assert( b.getSize() == 3 );
	assert( b[0] == 2.0 );
	assert( b[1] == 3.0 );
	assert( b[2] == 4.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_copy_assignment )
{
	double data[] = { 2.0, 3.0, 4.0 };
	RealArray * pA = new RealArray( 3, data );
	
	RealArray b( 10 );
	b = * pA;

	delete pA;

	assert( b.getSize() == 3 );
	assert( b[0] == 2.0 );
	assert( b[1] == 3.0 );
	assert( b[2] == 4.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_move_assignment )
{
	double data[] = { 2.0, 3.0, 4.0 };
	RealArray b( 10 );
	b = RealArray( 3, data );
	assert( b.getSize() == 3 );
	assert( b[0] == 2.0 );
	assert( b[1] == 3.0 );
	assert( b[2] == 4.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_selection_out_of_range_1 )
{
	RealArray a( 3 );
	try
	{
		double temp = a[ - 1 ];
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Index out of range" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_selection_out_of_range_2 )
{
	RealArray a( 3 );
	try
	{
		double temp = a[ 3 ];
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Index out of range" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_selection_out_of_range_3 )
{
	RealArray a( 3 );
	try
	{
		a[ - 1 ] = 3;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Index out of range" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_selection_out_of_range_4 )
{
	RealArray a( 3 );
	try
	{
		a[ 3 ] = 3;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( !strcmp( e.what(), "Index out of range" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_get_min_max_element )
{
	double data[] = { 6.0, 2.0, 1.0, 7.0, 3.0 };
	RealArray a( 5, data );
	assert( a.getMinElement() == 1.0 );
	assert( a.getMaxElement() == 7.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( realarray_test_sort )
{
	double data[] = { 6.0, 2.0, 1.0, 7.0, 3.0 };
	RealArray a( 5, data );
	a.sort();
	assert( a[ 0 ] == 1.0 );
	assert( a[ 1 ] == 2.0 );
	assert( a[ 2 ] == 3.0 );
	assert( a[ 3 ] == 6.0 );
	assert( a[ 4 ] == 7.0 );
}


/*****************************************************************************/
