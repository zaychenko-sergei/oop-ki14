// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "chandelier.hpp"

#include <sstream>

/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_constructor )
{
	Chandelier c1( 1 );
	assert( c1.getSlotsCount() == 1 );

	Chandelier c2( 5 );
	assert( c2.getSlotsCount() == 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_constructor_wrong_slots_count )
{
	try
	{
		Chandelier c( 0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive number of slots" ) );
	}

	try
	{
		Chandelier c( -1 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive number of slots" ) );
	}

}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_setup_and_get_slot_power )
{
	Chandelier c( 3 );
	for ( int i = 0; i < 3; i++ )
		assert( c.getSlotPower( i ) == 0.0 );

	c.setSlotPower( 0, 20 );
	c.setSlotPower( 1, 30 );
	
	assert( c.getSlotPower( 0 ) == 20 );
	assert( c.getSlotPower( 1 ) == 30 );
	assert( c.getSlotPower( 2 ) ==  0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_get_slot_power_wrong_index )
{
	try
	{
		Chandelier c( 2 );
		int p = c.getSlotPower( 2 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Out of range" ) );
	}

	try
	{
		Chandelier c( 2 );
		int p = c.getSlotPower( -1 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Out of range" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_set_slot_power_wrong_index )
{
	try
	{
		Chandelier c( 2 );
		c.setSlotPower( 2, 20 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Out of range" ) );
	}

	try
	{
		Chandelier c( 2 );
		c.setSlotPower( -1, 20 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Out of range" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_set_slot_power_negative )
{
	try
	{
		Chandelier c( 1 );
		c.setSlotPower( 0, -10 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Negative power" ) );
	}


	Chandelier c( 1 );
	c.setSlotPower( 0, 0 );
	assert( c.getSlotPower( 0 ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_get_set_power_mode )
{
	Chandelier c( 1 );
	assert( c.getPowerMode() == Chandelier::Power_Off );

	c.setPowerMode( Chandelier::Power_Full );
	assert( c.getPowerMode() == Chandelier::Power_Full );

	c.setPowerMode( Chandelier::Power_Half );
	assert( c.getPowerMode() == Chandelier::Power_Half );

	c.setPowerMode( Chandelier::Power_Third );
	assert( c.getPowerMode() == Chandelier::Power_Third );
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_get_total_power_simple )
{
	Chandelier c( 4 );
	c.setSlotPower( 0, 20 );
	c.setSlotPower( 1, 30 );
	c.setSlotPower( 2, 10 );
	c.setSlotPower( 3, 20 );

	assert( c.getTotalPower() == 0 );
	
	c.setPowerMode( Chandelier::Power_Full );
	assert( c.getTotalPower() == 80 ); // 20 + 30 + 10 + 20

	c.setPowerMode( Chandelier::Power_Half );
	assert( c.getTotalPower() == 50 ); // 20 + 30

	c.setPowerMode( Chandelier::Power_Third );
	assert( c.getTotalPower() == 20 ); // 20
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_get_total_power_empty_slots )
{
	Chandelier c( 5 );
	c.setSlotPower( 0, 20 );
	c.setSlotPower( 1, 10 );
	c.setSlotPower( 3, 30 );

	assert( c.getTotalPower() == 0 );
	
	c.setPowerMode( Chandelier::Power_Full );
	assert( c.getTotalPower() == 60 ); // 20 + 10 + 30

	c.setPowerMode( Chandelier::Power_Half );
	assert( c.getTotalPower() == 30 ); // 20 + 10

	c.setPowerMode( Chandelier::Power_Third );
	assert( c.getTotalPower() == 20 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_output_operator )
{
	Chandelier c( 3 );

	std::stringstream s1;
	s1 << c;
	assert( s1.str() == "()" );

	c.setSlotPower( 0, 10 );
	c.setSlotPower( 1, 20 );
	c.setSlotPower( 2, 30 );

	std::stringstream s2;
	s2 << c;
	assert( s2.str() == "()" );

	c.setPowerMode( Chandelier::Power_Full );

	std::stringstream s3;
	s3 << c;
	assert( s3.str() == "(10-20-30)" );

	c.setPowerMode( Chandelier::Power_Half );

	std::stringstream s4;
	s4 << c;
	assert( s4.str() == "(10-20-30)" );

	c.setSlotPower( 0, 0 );
	c.setSlotPower( 1, 0 );

	std::stringstream s5;
	s5 << c;
	assert( s5.str() == "(30)" );

}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_copy_move_constructor )
{
	Chandelier c1( 3 );
	c1.setPowerMode( Chandelier::Power_Half );
	c1.setSlotPower( 0, 10 );
	c1.setSlotPower( 2, 20 );

	Chandelier c2 = c1;
	assert( c2.getSlotsCount() == 3 );
	assert( c2.getSlotPower( 0 ) == 10 );
	assert( c2.getSlotPower( 1 ) ==  0 );
	assert( c2.getSlotPower( 2 ) == 20 );
	assert( c2.getPowerMode() == Chandelier::Power_Half );

	Chandelier c3 = std::move( c2 );
	assert( c3.getSlotsCount() == 3 );
	assert( c3.getSlotPower( 0 ) == 10 );
	assert( c3.getSlotPower( 1 ) ==  0 );
	assert( c3.getSlotPower( 2 ) == 20 );
	assert( c3.getPowerMode() == Chandelier::Power_Half );
}


/*****************************************************************************/


DECLARE_OOP_TEST( chandelier_test_copy_move_assignment )
{
	Chandelier c1( 3 );
	c1.setPowerMode( Chandelier::Power_Half );
	c1.setSlotPower( 0, 10 );
	c1.setSlotPower( 2, 20 );

	Chandelier c2( 5 );
	
	c2 = c1;
	assert( c2.getSlotsCount() == 3 );
	assert( c2.getSlotPower( 0 ) == 10 );
	assert( c2.getSlotPower( 1 ) ==  0 );
	assert( c2.getSlotPower( 2 ) == 20 );
	assert( c2.getPowerMode() == Chandelier::Power_Half );

	Chandelier c3( 2 );
	
	c3 = std::move( c2 );
	assert( c3.getSlotsCount() == 3 );
	assert( c3.getSlotPower( 0 ) == 10 );
	assert( c3.getSlotPower( 1 ) ==  0 );
	assert( c3.getSlotPower( 2 ) == 20 );
	assert( c3.getPowerMode() == Chandelier::Power_Half );

	assert( c2.getSlotsCount() == 2 );
	assert( c2.getPowerMode() == Chandelier::Power_Off );
	assert( c2.getSlotPower( 0 ) == 0 );
	assert( c2.getSlotPower( 1 ) == 0 );
}


/*****************************************************************************/
