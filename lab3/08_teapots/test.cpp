// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_1_manual_teapot_one )
{
	Controller c;
	c.createManualTeapot( 500, 10 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_2_manual_teapot_several )
{
	Controller c;
	c.createManualTeapot( 450, 23 );
	c.createManualTeapot( 1000, 45 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 450 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 23 );
	assert( c.isTeapotOn( 0 ) == false );

	assert( c.getTeapotCurrentVolume( 1 ) == 0 );
	assert( c.getTeapotMaxVolume( 1 ) == 1000 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 1 ) == 45 );
	assert( c.isTeapotOn( 1 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_3_manual_teapot_with_negative_max_volume )
{
	Controller c;

	ASSERT_THROWS(
			c.createManualTeapot( -1000, 10 )
		,	Messages::NonPositiveVolume
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_4_manual_teapot_with_negative_boiling_speed )
{
	Controller c;

	ASSERT_THROWS(
			c.createManualTeapot( 750, -5 )
		,	Messages::NonPositiveSpeed
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_5_manual_teapot_with_duplicated_data )
{
	Controller c;
	c.createManualTeapot( 1000, 100 );
	c.createManualTeapot( 1000, 100 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 1000 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 100 );
	assert( c.isTeapotOn( 0 ) == false );

	assert( c.getTeapotCurrentVolume( 1 ) == 0 );
	assert( c.getTeapotMaxVolume( 1 ) == 1000 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 1 ) == 100 );
	assert( c.isTeapotOn( 1 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_6_manual_teapot_obtain_data_by_bad_index )
{
	Controller c;
	c.createManualTeapot( 100, 1 );

	// NOTE: Check for negative index
	ASSERT_THROWS(
			c.getTeapotCurrentVolume( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotMaxVolume( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotCurrentTemperature( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotBoilingSpeed( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.isTeapotOn( -1 )
		,	Messages::WrongTeapotIndex
	);

	// NOTE: Check for excess positive index
	ASSERT_THROWS(
			c.getTeapotCurrentVolume( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotMaxVolume( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotCurrentTemperature( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotBoilingSpeed( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.isTeapotOn( 1 )
		,	Messages::WrongTeapotIndex
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_7_manual_teapot_add_water_when_teapot_is_turned_off )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 150 );

	assert( c.getTeapotCurrentVolume( 0 ) == 150 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_8_manual_teapot_take_water_when_teapot_is_turned_off )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 150 );
	c.takeWater( 0, 90 );

	assert( c.getTeapotCurrentVolume( 0 ) == 60 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_9_manual_teapot_add_water_when_teapot_is_turned_on )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.turnOnTeapot( 0 );

	ASSERT_THROWS(
			c.addWater( 0, 150 )
		,	Messages::TeapotIsNotModifiable
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_10_manual_teapot_take_water_when_teapot_is_turned_on )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 150 );
	c.turnOnTeapot( 0 );

	ASSERT_THROWS(
			c.takeWater( 0, 90 )
		,	Messages::TeapotIsNotModifiable
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_11_manual_teapot_add_water_with_negative_volume )
{
	Controller c;
	c.createManualTeapot( 500, 10 );

	ASSERT_THROWS(
			c.addWater( 0, -100 )
		,	Messages::NonPositiveVolume
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_12_manual_teapot_add_water_to_produce_teapot_overflow )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 400 );

	ASSERT_THROWS(
			c.addWater( 0, 200 )
		,	Messages::TeapotVolumeOverflow
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_13_manual_teapot_take_water_with_negative_volume )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 200 );

	ASSERT_THROWS(
			c.takeWater( 0, -100 )
		,	Messages::NonPositiveVolume
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_14_manual_teapot_take_water_to_produce_teapot_underflow )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 200 );
	c.takeWater( 0, 100 );

	ASSERT_THROWS(
			c.takeWater( 0, 200 )
		,	Messages::TeapotVolumeUnderflow
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_15_manual_teapot_wait_several_minutes_with_turned_on )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 150 );

	c.turnOnTeapot( 0 );
	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 150 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 50 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_16_manual_teapot_wait_until_teapot_will_be_boiling )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 400 );

	c.turnOnTeapot( 0 );
	c.wait( 5 );

	assert( c.getTeapotCurrentVolume( 0 ) == 400 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 70 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 2 );

	assert( c.getTeapotCurrentVolume( 0 ) == 400 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 90 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 400 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_17_manual_teapot_wait_several_minutes_when_teapot_is_boiling )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.addWater( 0, 400 );

	c.turnOnTeapot( 0 );
	c.wait( 8 );

	assert( c.getTeapotCurrentVolume( 0 ) == 400 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 380 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 320 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_18_manual_teapot_turn_on_empty_teapot_for_1_minute )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_19_manual_teapot_turn_on_empty_teapot_for_3_minutes )
{
	Controller c;
	c.createManualTeapot( 500, 10 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 2 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	ASSERT_THROWS(
			c.wait( 1 )
		,	Messages::TeapotAlmostBurned
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_20_manual_teapot_teapot_is_boiling_until_water_will_be_missed )
{
	Controller c;
	c.createManualTeapot( 200, 20 );
	c.addWater( 0, 100 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 4 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 19 );

	assert( c.getTeapotCurrentVolume( 0 ) == 5 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 2 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_21_manual_teapot_teapot_is_boiling_until_water_will_be_missed_and_teapot_is_burned )
{
	Controller c;
	c.createManualTeapot( 200, 20 );
	c.addWater( 0, 100 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 4 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 19 );

	assert( c.getTeapotCurrentVolume( 0 ) == 5 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 2 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	ASSERT_THROWS(
			c.wait( 1 )
		,	Messages::TeapotAlmostBurned
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_22_manual_teapot_wait_several_minutes_with_turned_off_at_the_room_temperature )
{
	Controller c;
	c.createManualTeapot( 200, 20 );
	c.addWater( 0, 100 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_23_manual_teapot_wait_several_minutes_with_turned_off_at_the_high_temperature )
{
	Controller c;
	c.createManualTeapot( 200, 20 );
	c.addWater( 0, 100 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 80 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.turnOffTeapot( 0 );
	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 78 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 8 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 62 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_1_24_manual_teapot_temperature_is_not_lower_than_room_temperature )
{
	Controller c;
	c.createManualTeapot( 200, 20 );
	c.addWater( 0, 100 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 80 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.turnOffTeapot( 0 );
	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 78 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 1000 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_1_automatic_teapot_one )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_2_automatic_teapot_several )
{
	Controller c;
	c.createAutomaticTeapot( 450, 23 );
	c.createAutomaticTeapot( 1000, 45 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 450 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 23 );
	assert( c.isTeapotOn( 0 ) == false );

	assert( c.getTeapotCurrentVolume( 1 ) == 0 );
	assert( c.getTeapotMaxVolume( 1 ) == 1000 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 1 ) == 45 );
	assert( c.isTeapotOn( 1 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_3_automatic_teapot_with_negative_max_volume )
{
	Controller c;

	ASSERT_THROWS(
			c.createAutomaticTeapot( -1000, 10 )
		,	Messages::NonPositiveVolume
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_4_automatic_teapot_with_negative_boiling_speed )
{
	Controller c;

	ASSERT_THROWS(
			c.createAutomaticTeapot( 750, -5 )
		,	Messages::NonPositiveSpeed
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_5_automatic_teapot_with_duplicated_data )
{
	Controller c;
	c.createAutomaticTeapot( 1000, 100 );
	c.createAutomaticTeapot( 1000, 100 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 1000 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 100 );
	assert( c.isTeapotOn( 0 ) == false );

	assert( c.getTeapotCurrentVolume( 1 ) == 0 );
	assert( c.getTeapotMaxVolume( 1 ) == 1000 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 1 ) == 100 );
	assert( c.isTeapotOn( 1 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_6_automatic_teapot_obtain_data_by_bad_index )
{
	Controller c;
	c.createAutomaticTeapot( 100, 1 );

	// NOTE: Check for negative index
	ASSERT_THROWS(
			c.getTeapotCurrentVolume( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotMaxVolume( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotCurrentTemperature( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotBoilingSpeed( -1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.isTeapotOn( -1 )
		,	Messages::WrongTeapotIndex
	);

	// NOTE: Check for excess positive index
	ASSERT_THROWS(
			c.getTeapotCurrentVolume( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotMaxVolume( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotCurrentTemperature( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.getTeapotBoilingSpeed( 1 )
		,	Messages::WrongTeapotIndex
	);
	ASSERT_THROWS(
			c.isTeapotOn( 1 )
		,	Messages::WrongTeapotIndex
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_7_automatic_teapot_add_water_when_teapot_is_turned_off )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 150 );

	assert( c.getTeapotCurrentVolume( 0 ) == 150 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_8_automatic_teapot_take_water_when_teapot_is_turned_off )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 150 );
	c.takeWater( 0, 90 );

	assert( c.getTeapotCurrentVolume( 0 ) == 60 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_9_automatic_teapot_add_water_when_teapot_is_turned_on )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.turnOnTeapot( 0 );

	ASSERT_THROWS(
			c.addWater( 0, 150 )
		,	Messages::TeapotIsNotModifiable
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_10_automatic_teapot_take_water_when_teapot_is_turned_on )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 150 );
	c.turnOnTeapot( 0 );

	ASSERT_THROWS(
			c.takeWater( 0, 90 )
		,	Messages::TeapotIsNotModifiable
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_11_automatic_teapot_add_water_with_negative_volume )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );

	ASSERT_THROWS(
			c.addWater( 0, -100 )
		,	Messages::NonPositiveVolume
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_12_automatic_teapot_add_water_to_produce_teapot_overflow )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 400 );

	ASSERT_THROWS(
			c.addWater( 0, 200 )
		,	Messages::TeapotVolumeOverflow
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_13_automatic_teapot_take_water_with_negative_volume )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 200 );

	ASSERT_THROWS(
			c.takeWater( 0, -100 )
		,	Messages::NonPositiveVolume
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_14_automatic_teapot_take_water_to_produce_teapot_underflow )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 200 );
	c.takeWater( 0, 100 );

	ASSERT_THROWS(
			c.takeWater( 0, 200 )
		,	Messages::TeapotVolumeUnderflow
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_15_automatic_teapot_wait_several_minutes_with_turned_on )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 150 );

	c.turnOnTeapot( 0 );
	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 150 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 50 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_16_automatic_teapot_teapot_is_auto_turned_off_when_boiled )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );
	c.addWater( 0, 400 );

	c.turnOnTeapot( 0 );
	c.wait( 5 );

	assert( c.getTeapotCurrentVolume( 0 ) == 400 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 70 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 2 );

	assert( c.getTeapotCurrentVolume( 0 ) == 400 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 90 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 400 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_17_automatic_teapot_teapot_is_auto_turned_off_when_empty )
{
	Controller c;
	c.createAutomaticTeapot( 500, 10 );

	c.turnOnTeapot( 0 );
	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotMaxVolume( 0 ) == 500 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 10 );
	assert( c.isTeapotOn( 0 ) == false );
}

/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_18_automatic_teapot_wait_several_minutes_with_turned_off_at_the_room_temperature )
{
	Controller c;
	c.createAutomaticTeapot( 200, 20 );
	c.addWater( 0, 100 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_19_automatic_teapot_wait_several_minutes_with_turned_off_at_the_high_temperature )
{
	Controller c;
	c.createAutomaticTeapot( 200, 20 );
	c.addWater( 0, 100 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 80 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.turnOffTeapot( 0 );
	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 78 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 8 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 62 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_20_automatic_teapot_temperature_is_not_lower_than_room_temperature )
{
	Controller c;
	c.createAutomaticTeapot( 200, 20 );
	c.addWater( 0, 100 );
	c.turnOnTeapot( 0 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 80 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == true );

	c.turnOffTeapot( 0 );
	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 78 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );

	c.wait( 1000 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 200 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 20 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_2_21_automatic_teapot_back_to_initial_state_after_hour )
{
	Controller c;
	c.createAutomaticTeapot( 150, 15 );
	c.addWater( 0, 100 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 150 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 15 );
	assert( c.isTeapotOn( 0 ) == false );

	c.turnOnTeapot( 0 );
	c.wait( 60 );

	assert( c.getTeapotCurrentVolume( 0 ) == 100 );
	assert( c.getTeapotMaxVolume( 0 ) == 150 );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotBoilingSpeed( 0 ) == 15 );
	assert( c.isTeapotOn( 0 ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( teapots_3_1_complex_cases_simple_flow )
{
	Controller c;

	c.createManualTeapot( 2500, 10 );
	c.createAutomaticTeapot( 1700, 20 );

	assert( c.getTeapotCurrentVolume( 0 ) == 0 );
	assert( c.getTeapotCurrentVolume( 1 ) == 0 );
	assert( c.isTeapotOn( 0 ) == false );
	assert( c.isTeapotOn( 1 ) == false );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 20 );

	c.addWater( 0, 1000 );
	c.addWater( 1, 800 );
	c.turnOnTeapot( 0 );
	c.turnOnTeapot( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 1000 );
	assert( c.getTeapotCurrentVolume( 1 ) == 800 );
	assert( c.isTeapotOn( 0 ) == true );
	assert( c.isTeapotOn( 1 ) == true );
	assert( c.getTeapotCurrentTemperature( 0 ) == 20 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 20 );

	c.wait( 3 );

	assert( c.getTeapotCurrentVolume( 0 ) == 1000 );
	assert( c.getTeapotCurrentVolume( 1 ) == 800 );
	assert( c.isTeapotOn( 0 ) == true );
	assert( c.isTeapotOn( 1 ) == true );
	assert( c.getTeapotCurrentTemperature( 0 ) == 50 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 80 );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 1000 );
	assert( c.getTeapotCurrentVolume( 1 ) == 800 );
	assert( c.isTeapotOn( 0 ) == true );
	assert( c.isTeapotOn( 1 ) == false );
	assert( c.getTeapotCurrentTemperature( 0 ) == 60 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 100 );

	c.wait( 4 );

	assert( c.getTeapotCurrentVolume( 0 ) == 1000 );
	assert( c.getTeapotCurrentVolume( 1 ) == 800 );
	assert( c.isTeapotOn( 0 ) == true );
	assert( c.isTeapotOn( 1 ) == false );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 92 );

	c.wait( 1 );

	assert( c.getTeapotCurrentVolume( 0 ) == 950 );
	assert( c.getTeapotCurrentVolume( 1 ) == 800 );
	assert( c.isTeapotOn( 0 ) == true );
	assert( c.isTeapotOn( 1 ) == false );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 90 );

	c.turnOffTeapot( 0 );
	c.takeWater( 0, 250 );

	assert( c.getTeapotCurrentVolume( 0 ) == 700 );
	assert( c.getTeapotCurrentVolume( 1 ) == 800 );
	assert( c.isTeapotOn( 0 ) == false );
	assert( c.isTeapotOn( 1 ) == false );
	assert( c.getTeapotCurrentTemperature( 0 ) == 100 );
	assert( c.getTeapotCurrentTemperature( 1 ) == 90 );
}


/*****************************************************************************/
