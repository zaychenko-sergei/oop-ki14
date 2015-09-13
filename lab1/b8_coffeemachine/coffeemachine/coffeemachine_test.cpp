// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "coffeemachine.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_constructor )
{
	CoffeeMachine m( 1000, 2000, 16 );
	assert( m.getBeansWeight() == 0 );
	assert( m.getWaterVolume() == 0 );
	assert( m.getFreeWastePortions() == 16 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_constructor_wrong_beans_weight )
{
	try
	{
		CoffeeMachine m( 0, 2000, 16 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Incorrect initial parameters" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_constructor_wrong_water_volume )
{
	try
	{
		CoffeeMachine m( 1000, 0, 16 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Incorrect initial parameters" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_constructor_wrong_waste_space )
{
	try
	{
		CoffeeMachine m( 1000, 2000, 0 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Incorrect initial parameters" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_load_water )
{
	CoffeeMachine m( 1000, 2000, 16 );
	m.loadBeans();

	int usedWater = m.loadWater();
	assert( usedWater == 2000 );
	assert( m.getWaterVolume() == 2000 );

	bool res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );
	assert( res );
	usedWater = m.loadWater();
	assert( usedWater == CoffeeMachine::WATER_FOR_ESPRESSO );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_load_beans )
{
	CoffeeMachine m( 1000, 2000, 16 );
	m.loadWater();

	int usedBeans = m.loadBeans();
	assert( usedBeans == 1000 );
	assert( m.getBeansWeight() == 1000 );

	bool res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );
	assert( res );
	usedBeans = m.loadBeans();
	assert( usedBeans == CoffeeMachine::BEANS_FOR_LIGHT );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_waste_portions_small_can )
{
	CoffeeMachine m( 1000, 2000, 1 );
	m.loadBeans();
	m.loadWater();
	assert( m.getFreeWastePortions() == 1 );

	bool res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );
	assert( res );
	assert( m.getFreeWastePortions() == 0 );

	res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );
	assert( ! res );

	m.cleanWaste();
	assert( m.getFreeWastePortions() == 1 );
	assert( ! res );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_waste_portions_multiple_coffees )
{
	CoffeeMachine m( 1000, 2000, 10 );
	m.loadBeans();
	m.loadWater();
	assert( m.getFreeWastePortions() == 10 );

	bool res = true;
	for ( int i = 0; i < 3; i++ )
		res &= m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );

	assert( res );
	assert( m.getFreeWastePortions() == 7 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_wash_enough_water )
{
	CoffeeMachine m( 1000, 2000, 10 );
	m.loadWater();
	assert( m.getWaterVolume() == 2000 );
	m.washMachine();
	assert( m.getWaterVolume() == ( 2000 - CoffeeMachine::WATER_FOR_WASHING ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_wash_not_enough_water )
{
	CoffeeMachine m( 1000, CoffeeMachine::WATER_FOR_WASHING / 2, 10 );
	m.loadWater();
	assert( m.getWaterVolume() == CoffeeMachine::WATER_FOR_WASHING / 2 );
	m.washMachine();
	assert( m.getWaterVolume() == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_can_make_coffee_when_loaded_and_no_waste )
{
	CoffeeMachine m( 1000, 2000, 10 );
	m.loadBeans();
	m.loadWater();

	assert( m );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_cannnot_make_coffee_without_beans )
{
	CoffeeMachine m( 1000, 2000, 10 );
	m.loadWater();
	assert( ! m );
	bool res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );
	assert( ! res );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_cannnot_make_coffee_without_water )
{
	CoffeeMachine m( 1000, 2000, 10 );
	m.loadBeans();
	assert( ! m );
	bool res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );
	assert( ! res );
}


/*****************************************************************************/


DECLARE_OOP_TEST( coffee_test_correct_resource_uses )
{
	CoffeeMachine m( 1000, 2000, 10 );

	bool res;

	m.loadBeans();
	m.loadWater();
	res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Light );
	assert( res );
	assert( m.getBeansWeight() == ( 1000 - CoffeeMachine::BEANS_FOR_LIGHT ) );
	assert( m.getWaterVolume() == ( 2000 - CoffeeMachine::WATER_FOR_ESPRESSO ) );
	assert( m.getFreeWastePortions() == 9 );

	m.loadBeans();
	m.loadWater();
	res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Medium );
	assert( res );
	assert( m.getBeansWeight() == ( 1000 - CoffeeMachine::BEANS_FOR_MEDIUM ) );
	assert( m.getWaterVolume() == ( 2000 - CoffeeMachine::WATER_FOR_ESPRESSO ) );
	assert( m.getFreeWastePortions() == 8 );

	m.loadBeans();
	m.loadWater();
	res = m.makeCoffee( CoffeeMachine::Espresso, CoffeeMachine::Strong );
	assert( res );
	assert( m.getBeansWeight() == ( 1000 - CoffeeMachine::BEANS_FOR_STRONG ) );
	assert( m.getWaterVolume() == ( 2000 - CoffeeMachine::WATER_FOR_ESPRESSO ) );
	assert( m.getFreeWastePortions() == 7 );

	m.loadBeans();
	m.loadWater();
	res = m.makeCoffee( CoffeeMachine::Americano, CoffeeMachine::Light );
	assert( res );
	assert( m.getBeansWeight() == ( 1000 - CoffeeMachine::BEANS_FOR_LIGHT ) );
	assert( m.getWaterVolume() == ( 2000 - CoffeeMachine::WATER_FOR_AMERICANO ) );
	assert( m.getFreeWastePortions() == 6 );

	m.loadBeans();
	m.loadWater();
	res = m.makeCoffee( CoffeeMachine::Americano, CoffeeMachine::Medium );
	assert( res );
	assert( m.getBeansWeight() == ( 1000 - CoffeeMachine::BEANS_FOR_MEDIUM ) );
	assert( m.getWaterVolume() == ( 2000 - CoffeeMachine::WATER_FOR_AMERICANO ) );
	assert( m.getFreeWastePortions() == 5 );

	m.loadBeans();
	m.loadWater();
	res = m.makeCoffee( CoffeeMachine::Americano, CoffeeMachine::Strong );
	assert( res );
	assert( m.getBeansWeight() == ( 1000 - CoffeeMachine::BEANS_FOR_STRONG ) );
	assert( m.getWaterVolume() == ( 2000 - CoffeeMachine::WATER_FOR_AMERICANO ) );
	assert( m.getFreeWastePortions() == 4 );
}


/*****************************************************************************/
