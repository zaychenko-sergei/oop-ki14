// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "matrix.hpp"

#include <sstream>

/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_constructor_default )
{
	Matrix m( 2, 3 );
	assert( m.getNumRows() == 2 );
	assert( m.getNumColumns() == 3 );
	
	for ( int i = 0; i < 2; i++ )
		for ( int k = 0; k < 3; k++ )
			assert( m[ i ][ k ] == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_constructor_initial_data )
{ 
	double data[ 2 ][ 3 ] = { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 } };

	Matrix m( 2, 3, ( double * )( data ) );
	assert( m.getNumRows() == 2 );
	assert( m.getNumColumns() == 3 );
	
	for ( int i = 0; i < 2; i++ )
		for ( int k = 0; k < 3; k++ )
			assert( m[ i ][ k ] == data[ i ][ k ] );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_constructor_bad_dimensions )
{
	int dimensions[ 3 ][ 2 ] = { { 0, 5 }, { 5, 0 }, { 0, 0 } };

	for ( int i = 0; i < 3; i++ )
	{
		try
		{
			Matrix m( dimensions[ i ][ 0 ], dimensions[ i ][ 1 ] );
			assert( ! "Exception must have been thrown" );
		}
		catch ( std::exception & e )
		{
			assert( ! strcmp( e.what(), "Invalid dimensions" ) );
		}
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_constructor_bad_data )
{
	try
	{
		Matrix m( 2, 2, nullptr );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Bad data pointer" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_valid_access )
{
	Matrix m( 3, 2 );
	
	m[ 0 ][ 0 ] = 1.0;
	m[ 0 ][ 1 ] = 2.0;
	m[ 1 ][ 0 ] = 3.0;
	m[ 1 ][ 1 ] = 4.0;
	m[ 2 ][ 0 ] = 5.0;
	m[ 2 ][ 1 ] = 6.0;

	assert( m[ 0 ][ 0 ] =  1.0 );
	assert( m[ 0 ][ 1 ] =  2.0 );
	assert( m[ 1 ][ 0 ] =  3.0 );
	assert( m[ 1 ][ 1 ] =  4.0 );
	assert( m[ 2 ][ 0 ] =  5.0 );
	assert( m[ 2 ][ 1 ] =  6.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_invalid_access )
{
	int indices[ 4 ][ 2 ] = { { -1, 0 }, { 0, -1 }, { 2, 0 }, { 0, 2 } };

	for ( int i = 0; i < 4; i++ )
	{
		try
		{
			Matrix m( 2, 2 );
			m[ indices[ i ][ 0 ] ][ indices[ i ][ 1 ] ] = 0.0;
			assert( ! "Exception must have been thrown" );
		}
		catch ( std::exception & e )
		{
			assert( ! strcmp( e.what(), "Out of range" ) );
		}
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_copy_move )
{
	double initialData[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	Matrix m1( 3, 2, initialData );

	Matrix m2 = m1;
	
	assert( m2.getNumColumns() == 2 );
	assert( m2.getNumRows() == 3 );
	assert( m2[ 1 ][ 1 ] == 4.0 );

	Matrix m3( 2, 3 );
	m3 = m2;

	assert( m3.getNumColumns() == 2 );
	assert( m3.getNumRows() == 3 );
	assert( m3[ 1 ][ 1 ] == 4.0 );

	Matrix m4 = std::move( m3 );

	assert( m4.getNumColumns() == 2 );
	assert( m4.getNumRows() == 3 );
	assert( m4[ 1 ][ 1 ] == 4.0 );

	Matrix m5( 1, 1 );
	m5 = std::move( m4 );

	assert( m5.getNumColumns() == 2 );
	assert( m5.getNumRows() == 3 );
	assert( m5[ 1 ][ 1 ] == 4.0 );

	assert( m4.getNumColumns() == 1 );
	assert( m4.getNumRows() == 1 );
	assert( m4[ 0 ][ 0 ] == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_equality_inequality )
{
	Matrix m1( 2, 2 );
	Matrix m2( 2, 2 );
	Matrix m3( 2, 2 );
	m3[ 0 ][ 0 ] = 1.0;
	Matrix m4( 3, 2 );
	Matrix m5( 2, 3 );

	assert( m1 == m2 );
	assert( !( m1 != m2 ) );

	assert( m1 != m3 );
	assert( !( m1 == m3 ) );

	assert( m1 != m4 );
	assert( !( m1 == m4 ) );

	assert( m1 != m5 );
	assert( !( m1 == m5 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_add )
{
	double data1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	double data2[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

	Matrix m1( 3, 2, data1 );
	Matrix m2( 3, 2, data2 );

	Matrix m3 = m1 + m2;
	
	assert( m3.getNumRows() == 3 );
	assert( m3.getNumColumns() == 2 );
	assert( m3[ 0 ][ 0 ] == 2.0 );
	assert( m3[ 0 ][ 1 ] == 3.0 );
	assert( m3[ 1 ][ 0 ] == 4.0 );
	assert( m3[ 1 ][ 1 ] == 5.0 );
	assert( m3[ 2 ][ 0 ] == 6.0 );
	assert( m3[ 2 ][ 1 ] == 7.0 );

	assert( m1[ 0 ][ 0 ] == 1.0 );
	assert( m1[ 0 ][ 1 ] == 2.0 );
	assert( m1[ 1 ][ 0 ] == 3.0 );
	assert( m1[ 1 ][ 1 ] == 4.0 );
	assert( m1[ 2 ][ 0 ] == 5.0 );
	assert( m1[ 2 ][ 1 ] == 6.0 );

	m1 += m2;

	assert( m1[ 0 ][ 0 ] == 2.0 );
	assert( m1[ 0 ][ 1 ] == 3.0 );
	assert( m1[ 1 ][ 0 ] == 4.0 );
	assert( m1[ 1 ][ 1 ] == 5.0 );
	assert( m1[ 2 ][ 0 ] == 6.0 );
	assert( m1[ 2 ][ 1 ] == 7.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_sub )
{
	double data1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	double data2[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

	Matrix m1( 3, 2, data1 );
	Matrix m2( 3, 2, data2 );

	Matrix m3 = m1 - m2;
	
	assert( m3.getNumRows() == 3 );
	assert( m3.getNumColumns() == 2 );
	assert( m3[ 0 ][ 0 ] == 0.0 );
	assert( m3[ 0 ][ 1 ] == 1.0 );
	assert( m3[ 1 ][ 0 ] == 2.0 );
	assert( m3[ 1 ][ 1 ] == 3.0 );
	assert( m3[ 2 ][ 0 ] == 4.0 );
	assert( m3[ 2 ][ 1 ] == 5.0 );

	assert( m1[ 0 ][ 0 ] == 1.0 );
	assert( m1[ 0 ][ 1 ] == 2.0 );
	assert( m1[ 1 ][ 0 ] == 3.0 );
	assert( m1[ 1 ][ 1 ] == 4.0 );
	assert( m1[ 2 ][ 0 ] == 5.0 );
	assert( m1[ 2 ][ 1 ] == 6.0 );

	m1 -= m2;

	assert( m1[ 0 ][ 0 ] == 0.0 );
	assert( m1[ 0 ][ 1 ] == 1.0 );
	assert( m1[ 1 ][ 0 ] == 2.0 );
	assert( m1[ 1 ][ 1 ] == 3.0 );
	assert( m1[ 2 ][ 0 ] == 4.0 );
	assert( m1[ 2 ][ 1 ] == 5.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_add_sub_wrong_dimensions )
{
	try
	{
		Matrix m1( 2, 2 );
		Matrix m2( 2, 3 );
		Matrix m3 = m1 + m2;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Size mismatch" ) );
	}

	try
	{
		Matrix m1( 2, 2 );
		Matrix m2( 2, 3 );
		m1 += m2;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Size mismatch" ) );
	}

	try
	{
		Matrix m1( 2, 2 );
		Matrix m2( 2, 3 );
		Matrix m3 = m1 - m2;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Size mismatch" ) );
	}

	try
	{
		Matrix m1( 2, 2 );
		Matrix m2( 2, 3 );
		m1 -= m2;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Size mismatch" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_multiply )
{
	double data1[] = { 2.0, 2.0, 2.0 };
	double data2[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	Matrix m1( 1, 3, data1 );
	Matrix m2( 3, 2, data2 );

	Matrix m3 = m1 * m2;
	assert( m3.getNumRows() == 1 );
	assert( m3.getNumColumns() == 2 );
	assert( m3[ 0 ][ 0 ] == 18 );
	assert( m3[ 0 ][ 1 ] == 24 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_multiply_wrong_dimensions )
{
	try
	{
		Matrix m1( 2, 2 );
		Matrix m2( 3, 2 );
		Matrix m3 = m1 * m2;
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Size mismatch" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_multiply_scalar )
{
	double data1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	Matrix m1( 2, 3, data1 );

	Matrix m2 = m1 * 2.5;
	assert( m2.getNumRows() == 2 );
	assert( m2.getNumColumns() == 3 );

	assert( m2[ 0 ][ 0 ] ==  2.5 );
	assert( m2[ 0 ][ 1 ] ==  5.0 );
	assert( m2[ 0 ][ 2 ] ==  7.5 );
	assert( m2[ 1 ][ 0 ] == 10.0 );
	assert( m2[ 1 ][ 1 ] == 12.5 );
	assert( m2[ 1 ][ 2 ] == 15.0 );

	assert( m1[ 0 ][ 0 ] == 1.0 );
	assert( m1[ 0 ][ 1 ] == 2.0 );
	assert( m1[ 0 ][ 2 ] == 3.0 );
	assert( m1[ 1 ][ 0 ] == 4.0 );
	assert( m1[ 1 ][ 1 ] == 5.0 );
	assert( m1[ 1 ][ 2 ] == 6.0 );

	m1 *= 2.5;

	assert( m1[ 0 ][ 0 ] ==  2.5 );
	assert( m1[ 0 ][ 1 ] ==  5.0 );
	assert( m1[ 0 ][ 2 ] ==  7.5 );
	assert( m1[ 1 ][ 0 ] == 10.0 );
	assert( m1[ 1 ][ 1 ] == 12.5 );
	assert( m1[ 1 ][ 2 ] == 15.0 );

}


/*****************************************************************************/


DECLARE_OOP_TEST( matrix_test_output_stream )
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	Matrix m( 2, 3, data );

	std::stringstream s;
	s << m;

	const char * pattern =
		"1\t2\t3\n"
		"4\t5\t6\n"
		;

	assert( s.str() == pattern );
}



/*****************************************************************************/
