// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "triangle.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_CoordinatesConstructor )
{
    Triangle t( 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 );
    assert( t.getPoint1() == Point( 0.0, 1.0 ) );
    assert( t.getPoint2() == Point( 2.0, 3.0 ) );
    assert( t.getPoint3() == Point( 4.0, 5.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_PointsConstructor )
{
    Triangle t( Point( 0.0, 1.0 ), Point( 2.0, 3.0 ), Point( 4.0, 5.0 ) );
    assert( t.getPoint1() == Point( 0.0, 1.0 ) );
    assert( t.getPoint2() == Point( 2.0, 3.0 ) );
    assert( t.getPoint3() == Point( 4.0, 5.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_SideLength )
{
    Triangle t( Point( 0.0, 0.0 ), Point( 1.0, 0.0 ), Point( 0.0, 1.0 ) );
    assert( equalDoubles( t.getSide12Length(), 1.0 ) );
    assert( equalDoubles( t.getSide13Length(), 1.0 ) );
    assert( equalDoubles( t.getSide23Length(), sqrt( 2.0 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_Perimeter )
{
    Triangle t( Point( 0.0, 1.0 ), Point( - 1.0, 0.0 ), Point( 1.0, 0.0 ) );
    assert( equalDoubles( t.getPerimeter(), 2.0 * sqrt( 2.0 ) + 2 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_Area )
{
    Triangle t( Point( 0.0, 1.0 ), Point( - 1.0, 0.0 ), Point( 1.0, 0.0 ) );
    assert( equalDoubles( t.getArea(), 1.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_Equality_Inequality )
{
    Triangle t1( Point( 0.0, 1.0 ), Point( - 1.0, 0.0 ), Point( 1.0, 0.0 ) );
    Triangle t2( Point( 0.0, 1.0 ), Point( - 1.0, 0.0 ), Point( 1.0, 0.0 ) );
    Triangle t3( Point( 0.0, 1.0 ), Point( - 2.0, 0.0 ), Point( 1.0, 0.0 ) );
    Triangle t4( Point( 0.0, 1.0 ), Point( - 1.0, 0.0 ), Point( 1.0, 1.0 ) );
    Triangle t5( Point( 1.0, 2.0 ), Point(   0.0, 1.0 ), Point( 2.0, 1.0 ) );
    
    assert(     t1 == t2   );
    assert( ! ( t1 != t2 ) );

    assert( !( t1 == t3 ) );
    assert(    t1 != t3   );

    assert( !( t1 == t4 ) );
    assert(    t1 != t4   );

    assert( !( t1 == t5 ) );
    assert(    t1 != t5   );

}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_Angles )
{
    Triangle t( Point( 0.0, 0.0 ), Point( 1.0, 1.0 ), Point( 2.0, 0.0 ) );
    assert( equalDoubles( t.getAngle1(), 0.785398 ) );
    assert( equalDoubles( t.getAngle2(), 1.570796 ) );
    assert( equalDoubles( t.getAngle3(), 0.785398 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_IsRectangular )
{
    Triangle t1( Point( 0.0, 3.0 ), Point( 0.0, 0.0 ), Point( 7.0, 0.0 ) );
    Triangle t2( Point( 0.0, 3.0 ), Point( 0.0, 0.0 ), Point( 7.0, 2.0 ) );
    assert( t1.isRectangular() );
    assert( ! t2.isRectangular() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_IsIsoceles )
{
    Triangle t1( Point( 0.0, 3.0 ), Point( -1.0, 0.0 ), Point( 1.0, 0.0 ) );
    Triangle t2( Point( 0.0, 3.0 ), Point( -1.0, 0.0 ), Point( 2.0, 0.0 ) );
    assert( t1.isIsosceles() );
    assert( ! t2.isIsosceles() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( triangles_test_IsEquilateral )
{
    Triangle t1( Point( 0.0, 3.464 ), Point( -2.0, 0.0 ), Point( 2.0, 0.0 ) );
    Triangle t2( Point( 0.0, 3.0 ), Point( -1.0, 0.0 ), Point( 1.0, 0.0 ) );
    assert( t1.isEquilateral() );
    assert( ! t2.isEquilateral() );
}


/*****************************************************************************/
