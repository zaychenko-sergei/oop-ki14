// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "watermachine.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_constructor )
{
	WaterMachine m( 1000.0, 100, 100, 0.63 );
	assert( m.getMaxVolume() == 1000.0 );
	assert( m.getMaxPapers() == 100 );
	assert( m.getMaxCoins()  == 100 );
	assert( m.getPricePerLiter() == 0.63 );

	assert( m.getRemainingWaterVolume() == 0.0 );
	assert( m.getNumPapersInside() == 0 );
	assert( m.getNumCoinsInside() == 0 );
	assert( m.getCurrentPrepaymentAmount() == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_constructor_wrong_parameters )
{
	try
	{
		WaterMachine m( 0.0, 1, 1, 1.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		WaterMachine m( -0.1, 1, 1, 1.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		WaterMachine m( 1.0, 0, 1, 1.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		WaterMachine m( 1.0, -1, 1, 1.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		WaterMachine m( 1.0, 1, 0, 1.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		WaterMachine m( 1.0, 1, -1, 1.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		WaterMachine m( 1.0, 1, 1, 0.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		WaterMachine m( 1.0, 1, 1, -1.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_price_update )
{
	WaterMachine m( 100.0, 1, 1, 0.63 );
	m.updatePricePerLiter( 0.67 );
	assert( m.getPricePerLiter() == 0.67 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_price_update_invalid )
{
	WaterMachine m( 100.0, 1, 1, 0.63 );

	try
	{
		m.updatePricePerLiter( - 0.67 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}

	try
	{
		m.updatePricePerLiter( 0.0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Non-positive parameter" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_pay_with_coins_simple )
{
	WaterMachine m( 100.0, 1, 5, 0.50 );
	m.fillWater();
	
	bool res = m.payWithCoins( WaterMachine::Coin_Hundred );
	res &= m.payWithCoins( WaterMachine::Coin_Fifty );
	res &= m.payWithCoins( WaterMachine::Coin_TwentyFive );
	assert( res );
	
	assert( m.getCurrentPrepaymentAmount() == 1.75 );
	assert( m.getVolumeForCurrentPrepayment() == 3.5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_pay_with_coins_exceed_limit )
{
	WaterMachine m( 100.0, 1, 2, 0.5 );
	m.fillWater();
	
	bool res = m.payWithCoins( WaterMachine::Coin_Hundred );
	assert( res );

	res = m.payWithCoins( WaterMachine::Coin_Fifty );
	assert( res );

	res = m.payWithCoins( WaterMachine::Coin_TwentyFive );
	assert( ! res );
	
	assert( m.getCurrentPrepaymentAmount() == 1.50 );
	assert( m.getVolumeForCurrentPrepayment() == 3.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_pay_with_papers_simple )
{
	WaterMachine m( 100.0, 5, 1, 2.00 );
	m.fillWater();
	
	bool res = m.payWithPaperMoney( WaterMachine::Paper_Five );
	res &= m.payWithPaperMoney( WaterMachine::Paper_Two );
	res &= m.payWithPaperMoney( WaterMachine::Paper_One );
	assert( res );
	
	assert( m.getCurrentPrepaymentAmount() == 8.0 );
	assert( m.getVolumeForCurrentPrepayment() == 4.0 );

}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_pay_with_papers_exceed_limit )
{
	WaterMachine m( 100.0, 2, 1, 2.00 );
	m.fillWater();
	
	bool res = m.payWithPaperMoney( WaterMachine::Paper_Five );
	assert( res );

	res = m.payWithPaperMoney( WaterMachine::Paper_Two );
	assert( res );

	res = m.payWithPaperMoney( WaterMachine::Paper_One );
	assert( ! res );
	
	assert( m.getCurrentPrepaymentAmount() == 7.00 );
	assert( m.getVolumeForCurrentPrepayment() == 3.5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_fill_water )
{
	WaterMachine m( 100.0, 1, 1, 1 );
	assert( m.getRemainingWaterVolume() == 0.0 );
	m.fillWater();
	assert( m.getRemainingWaterVolume() == 100.0 );
	m.payWithCoins( WaterMachine::Coin_Hundred );
	m.serve();
	assert( m.getRemainingWaterVolume() == 99.0 );
	m.fillWater();
	assert( m.getRemainingWaterVolume() == 100.0 );
	m.fillWater();
	assert( m.getRemainingWaterVolume() == 100.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_take_money )
{
	WaterMachine m( 100.0, 5, 20, 1.00 );
	m.fillWater();

	assert( m.getNumCoinsInside() == 0 );
	assert( m.getNumPapersInside() == 0 );

	for ( int i = 0; i < 3; i++ )
		m.payWithCoins( WaterMachine::Coin_Fifty );

	m.payWithPaperMoney( WaterMachine::Paper_One );

	assert( m.getNumCoinsInside() == 3 );
	assert( m.getNumPapersInside() == 1 );

	m.takeAwayMoney();

	assert( m.getNumCoinsInside() == 0 );
	assert( m.getNumPapersInside() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_limited_water )
{
	WaterMachine m( 2.0, 5, 20, 1.00 );

	m.fillWater();
	assert( m.getRemainingWaterVolume() == 2.0 );

	bool res = m.payWithPaperMoney( WaterMachine::Paper_Two );
	assert( res );
	assert( m.getCurrentPrepaymentAmount() == 2.00 );

	res = m.payWithCoins( WaterMachine::Coin_TwentyFive );
	assert( ! res );
	assert( m.getCurrentPrepaymentAmount() == 2.00 );

	m.serve();

	assert( m.getCurrentPrepaymentAmount() == 0.0 );
	assert( m.getRemainingWaterVolume() == 0.0 );

}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_attempt_serving_without_prepayment )
{
	WaterMachine m( 2.0, 5, 20, 1.00 );
	m.fillWater();
	
	try
	{
		m.serve();
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Prepayment expected" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( watermachine_test_operator_bool )
{
	WaterMachine m1( 1.0, 100, 100, 0.25 );
	m1.fillWater();
	assert( m1 == true );

	WaterMachine m2( 0.5, 100, 100, 0.3 );
	m2.fillWater();
	assert( m2 == false );

	WaterMachine m3( 0.1, 1, 1, 1.0 );
	m3.fillWater();
	assert( m3 == false );
}


/*****************************************************************************/

