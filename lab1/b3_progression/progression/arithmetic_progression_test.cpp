// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include "utils.hpp"

#include "arithmetic_progression.hpp"

#include <sstream>

/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_DefaultConstructor )
{
    ArithmeticProgression p;
    assert( p.getInitialValue() == 0 );
    assert( p.getStep() == 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_FullConstructor_ValueOnly )
{
    ArithmeticProgression p( 5 );
    assert( p.getInitialValue() == 5 );
    assert( p.getStep() == 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_FullConstructor_ValueStep )
{
    ArithmeticProgression p( 5, 2 );
    assert( p.getInitialValue() == 5 );
    assert( p.getStep() == 2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_getIthElement_Correct )
{
    ArithmeticProgression p1( 2, 2 );
    assert( p1.getIthElement( 0 ) == 2 );
    assert( p1.getIthElement( 1 ) == 4 );
    assert( p1.getIthElement( 3 ) == 8 );
    assert( p1.getIthElement( 10 ) == 22 );

    ArithmeticProgression p2( 2, -2 );
    assert( p2.getIthElement( 0 ) == 2 );
    assert( p2.getIthElement( 1 ) == 0 );
    assert( p2.getIthElement( 3 ) == -4 );
    assert( p2.getIthElement( 10 ) == -18 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_getIthElement_Wrong )
{
    ArithmeticProgression p;
    try
    {
        p.getIthElement( - 1 );
        assert( ! "Exception must have been thrown by getIthElement" );
    }
    catch ( std::exception & e )
    {
        assert( ! strcmp( e.what(), "Invalid index" ) );
    }
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_partialSum )
{
     ArithmeticProgression p;
     assert( p.partialSum( 0, 0 ) ==  0 );
     assert( p.partialSum( 0, 5 ) == 15 );
     assert( p.partialSum( 2, 4 ) ==  9 );

     ArithmeticProgression p2( 1, 2 ); // 1 3 5 7 9 11
     assert( p2.partialSum( 0, 3 ) == 16 );
     assert( p2.partialSum( 3, 5 ) == 27 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_partialAverage )
{
     ArithmeticProgression p;
     assert( equalDoubles( p.partialAverage( 0, 0 ), 0.0 ) );
     assert( equalDoubles( p.partialAverage( 0, 5 ), 2.5 ) );
     assert( equalDoubles( p.partialAverage( 2, 4 ), 3.0 ) );

     ArithmeticProgression p2( 1, 2 ); // 1 3 5 7 9 11
     assert( equalDoubles( p2.partialAverage( 0, 3 ), 4.0 ) );
     assert( equalDoubles( p2.partialAverage( 3, 5 ), 9.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_display )
{
    std::ostringstream o1;
    ArithmeticProgression p1;
    p1.display( 2, 5, o1 );
    assert( o1.str() == "2 3 4 5" );

    std::ostringstream o2;
    ArithmeticProgression p2( 2, 3 ); // 2 5 8 11 14 17
    p2.display( 3, 5, o2 );
    assert( o2.str() == "11 14 17" );
}


/*****************************************************************************/


#define TEST_VALID_INDEX_RANGE( methodName, loIndex, hiIndex )                \
    try                                                                        \
    {                                                                        \
        ArithmeticProgression p;                                            \
        p.methodName( loIndex, hiIndex );                                    \
        assert( ! "Exception must have been thrown by " #methodName );        \
    }                                                                        \
    catch ( std::exception & e )                                            \
    {                                                                        \
        assert( ! strcmp( e.what(), "Invalid index range" ) );                \
    }


DECLARE_OOP_TEST( progression_test_bad_indices_various_methods )
{
    TEST_VALID_INDEX_RANGE( partialSum, 4, 2 );
    TEST_VALID_INDEX_RANGE( partialSum, -2, 3 );

    TEST_VALID_INDEX_RANGE( partialAverage, 4, 2 );
    TEST_VALID_INDEX_RANGE( partialAverage, -2, 3 );

    TEST_VALID_INDEX_RANGE( display, 4, 2 );
    TEST_VALID_INDEX_RANGE( display, -2, 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_equality_inequality )
{
    ArithmeticProgression p1( 3, 2 );
    ArithmeticProgression p2( 3, 2 );
    ArithmeticProgression p3( 3, 3 );
    ArithmeticProgression p4( 2, 2 );

    assert( p1 == p2 );
    assert( !( p1 != p2 ) );

    assert( p1 != p3 );
    assert( !( p1 == p3 ) );

    assert( p1 != p4 );
    assert( !( p1 == p4 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_matches_array )
{
    const int data[] = { 1, 3, 5, 7, 9 };

    ArithmeticProgression p1( 1, 2 );
    assert( p1.matchesArray( data, 5 ) );
    assert( p1.matchesArray( data, 3 ) );

    ArithmeticProgression p2( 3, 2 );
    assert( ! p2.matchesArray( data, 5 ) );

    ArithmeticProgression p3( 1, 3 );
    assert( ! p3.matchesArray( data, 5 ) );

    const int data2[] = { 1, 3, 5, 7, 8 };
    assert( ! p1.matchesArray( data2, 5 ) );
    assert(   p1.matchesArray( data2, 4 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_matches_array_initializer_list )
{
    ArithmeticProgression p1( 1, 2 );
    assert( p1.matchesArray( { 1, 3, 5, 7, 9 } ) );
    assert( p1.matchesArray( { 1, 3, 5 } ) );

    ArithmeticProgression p2( 3, 2 );
    assert( !p2.matchesArray( { 1, 3, 5, 7, 9 } ) );

    ArithmeticProgression p3( 1, 3 );
    assert( !p3.matchesArray( { 1, 3, 5, 7, 9 } ) );

    assert( !p1.matchesArray( { 1, 3, 5, 7, 8 } ) );
    assert( p1.matchesArray( { 1, 3, 5, 7 } ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( progression_test_make_inverted )
{
    ArithmeticProgression p1( 3, 2 );

    ArithmeticProgression p2 = p1.makeInverted();
    assert( p2.getInitialValue() == 3 );
    assert( p2.getStep() == -2 );

    ArithmeticProgression p3 = p2.makeInverted();
    assert( p1 == p3 );
}


/*****************************************************************************/
