// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"
#include "utils.hpp"

#include "rgbcolor.hpp"

#include <sstream>

/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_simple_constructor )
{
	RGBColor c1( 10, 20, 30 );
	assert( c1.getRed() == 10 );
	assert( c1.getGreen() == 20 );
	assert( c1.getBlue() == 30 );
	assert( c1.getPackedRGB() == 0x0A141E );

	RGBColor c2( 0, 0, 0 );
	assert( c2.getRed() == 0 );
	assert( c2.getGreen() == 0 );
	assert( c2.getBlue() == 0 );
	assert( c2.getPackedRGB() == 0x0 );

	RGBColor c3( 255, 255, 255 );
	assert( c3.getRed() == 255 );
	assert( c3.getGreen() == 255 );
	assert( c3.getBlue() == 255 );
	assert( c3.getPackedRGB() == 0xFFFFFF );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_packed_constructor )
{
	RGBColor c1( 0x0A141E );
	assert( c1.getRed() == 10 );
	assert( c1.getGreen() == 20 );
	assert( c1.getBlue() == 30 );
	assert( c1.getPackedRGB() == 0x0A141E );

	RGBColor c2( 0 );
	assert( c2.getRed() == 0 );
	assert( c2.getGreen() == 0 );
	assert( c2.getBlue() == 0 );
	assert( c2.getPackedRGB() == 0x0 );

	RGBColor c3( 0xFFFFFF );
	assert( c3.getRed() == 0xFF );
	assert( c3.getGreen() == 0xFF );
	assert( c3.getBlue() == 0xFF );
	assert( c3.getPackedRGB() == 0xFFFFFF );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_black_key )
{
	RGBColor black( 0, 0, 0 );
	RGBColor white( 255, 255, 255 );
	RGBColor red( 255, 0, 0 );
	RGBColor green( 0, 255, 0 );
	RGBColor blue( 0, 0, 255 );
	RGBColor yellow( 255, 255, 0 );
	RGBColor cyan( 0, 255, 255 );
	RGBColor magenta( 255, 0, 255 );

	RGBColor some( 50, 100, 150 );

	assert( equalDoubles( black.getBlackKey(),   1.0 ) );
	assert( equalDoubles( white.getBlackKey(),   0.0 ) );
	assert( equalDoubles( red.getBlackKey(),     0.0 ) );
	assert( equalDoubles( green.getBlackKey(),   0.0 ) );
	assert( equalDoubles( blue.getBlackKey(),    0.0 ) );
	assert( equalDoubles( yellow.getBlackKey(),  0.0 ) );
	assert( equalDoubles( cyan.getBlackKey(),    0.0 ) );
	assert( equalDoubles( magenta.getBlackKey(), 0.0 ) );

	assert( equalDoubles( some.getBlackKey(),    0.412 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_cyan_color )
{
	RGBColor black( 0, 0, 0 );
	RGBColor white( 255, 255, 255 );
	RGBColor red( 255, 0, 0 );
	RGBColor green( 0, 255, 0 );
	RGBColor blue( 0, 0, 255 );
	RGBColor yellow( 255, 255, 0 );
	RGBColor cyan( 0, 255, 255 );
	RGBColor magenta( 255, 0, 255 );

	RGBColor some( 50, 100, 150 );

	assert( equalDoubles( black.getCyanColor(),   0.0 ) );
	assert( equalDoubles( white.getCyanColor(),   0.0 ) );
	assert( equalDoubles( red.getCyanColor(),     0.0 ) );
	assert( equalDoubles( green.getCyanColor(),   1.0 ) );
	assert( equalDoubles( blue.getCyanColor(),    1.0 ) );
	assert( equalDoubles( yellow.getCyanColor(),  0.0 ) );
	assert( equalDoubles( cyan.getCyanColor(),    1.0 ) );
	assert( equalDoubles( magenta.getCyanColor(), 0.0 ) );

	assert( equalDoubles( some.getCyanColor(),  0.667 ) );
}

/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_magenta_color )
{
	RGBColor black( 0, 0, 0 );
	RGBColor white( 255, 255, 255 );
	RGBColor red( 255, 0, 0 );
	RGBColor green( 0, 255, 0 );
	RGBColor blue( 0, 0, 255 );
	RGBColor yellow( 255, 255, 0 );
	RGBColor cyan( 0, 255, 255 );
	RGBColor magenta( 255, 0, 255 );

	RGBColor some( 50, 100, 150 );

	assert( equalDoubles( black.getMagentaColor(),   0.0 ) );
	assert( equalDoubles( white.getMagentaColor(),   0.0 ) );
	assert( equalDoubles( red.getMagentaColor(),     1.0 ) );
	assert( equalDoubles( green.getMagentaColor(),   0.0 ) );
	assert( equalDoubles( blue.getMagentaColor(),    1.0 ) );
	assert( equalDoubles( yellow.getMagentaColor(),  0.0 ) );
	assert( equalDoubles( cyan.getMagentaColor(),    0.0 ) );
	assert( equalDoubles( magenta.getMagentaColor(), 1.0 ) );

	assert( equalDoubles( some.getMagentaColor(), 0.333 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_yellow_color )
{
	RGBColor black( 0, 0, 0 );
	RGBColor white( 255, 255, 255 );
	RGBColor red( 255, 0, 0 );
	RGBColor green( 0, 255, 0 );
	RGBColor blue( 0, 0, 255 );
	RGBColor yellow( 255, 255, 0 );
	RGBColor cyan( 0, 255, 255 );
	RGBColor magenta( 255, 0, 255 );

	RGBColor some( 50, 100, 150 );

	assert( equalDoubles( black.getYellowColor(),   0.0 ) );
	assert( equalDoubles( white.getYellowColor(),   0.0 ) );
	assert( equalDoubles( red.getYellowColor(),     1.0 ) );
	assert( equalDoubles( green.getYellowColor(),   1.0 ) );
	assert( equalDoubles( blue.getYellowColor(),    0.0 ) );
	assert( equalDoubles( yellow.getYellowColor(),  1.0 ) );
	assert( equalDoubles( cyan.getYellowColor(),    0.0 ) );
	assert( equalDoubles( magenta.getYellowColor(), 0.0 ) );

	assert( equalDoubles( some.getYellowColor(),    0.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_color_equality_inequality )
{
	RGBColor c0( 0, 0, 0 );
	RGBColor c1( 0, 0, 0 );
	RGBColor c2( 0, 0, 0 );

	assert( c0 == c1 && c1 == c2 && c0 == c2 );
	assert( !( c0 != c1 ) && !( c1 != c2 ) && !( c0 != c2 ) );

	RGBColor c3( 1, 0, 0 );
	assert( !( c0 == c3 ) );
	assert( c0 != c3 );

	RGBColor c4( 0, 1, 0 );
	assert( !( c0 == c4 ) );
	assert( c0 != c4 );

	RGBColor c5( 0, 0, 1 );
	assert( !( c0 == c5 ) );
	assert( c0 != c5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_color_addition )
{
	RGBColor c1( 1, 2, 3 );
	RGBColor c2( 3, 2, 1 );
	RGBColor c3 = c1 + c2;
	assert( c3.getPackedRGB() == 0x040404 );

	c3 += c1;
	assert( c3.getPackedRGB() == 0x050607 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( rgb_test_inverted_color )
{
	RGBColor c1( 1, 2, 3 );
	assert( c1.getInvertedColor().getPackedRGB() == 0xFEFDFC );

	RGBColor c2( 0, 0, 0 );
	assert( c2.getInvertedColor().getPackedRGB() == 0xFFFFFF );

	RGBColor c3( 255, 255, 255 );
	assert( c3.getInvertedColor().getPackedRGB() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( rgb_test_stream_output )
{
	std::stringstream s;
	
	RGBColor black( 0, 0, 0 );
	RGBColor white( 255, 255, 255 );
	RGBColor red( 255, 0, 0 );
	RGBColor green( 0, 255, 0 );
	RGBColor blue( 0, 0, 255 );
	RGBColor yellow( 255, 255, 0 );
	RGBColor cyan( 0, 255, 255 );
	RGBColor magenta( 255, 0, 255 );

	s << black;
	assert( s.str() == "#000000" );
	s.str( "" );

	s << white;
	assert( s.str() == "#FFFFFF" );
	s.str( "" );

	s << red;
	assert( s.str() == "#FF0000" );
	s.str( "" );

	s << green;
	assert( s.str() == "#00FF00" );
	s.str( "" );

	s << blue;
	assert( s.str() == "#0000FF" );
	s.str( "" );

	s << yellow;
	assert( s.str() == "#FFFF00" );
	s.str( "" );

	s << cyan;
	assert( s.str() == "#00FFFF" );
	s.str( "" );

	s << magenta;
	assert( s.str() == "#FF00FF" );
	s.str( "" );
}


/*****************************************************************************/
