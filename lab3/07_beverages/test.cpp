// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_1_customer_one )
{
	Controller c;
	c.createCustomer( "Ivanov", 18, 722.0 );

	assert( c.getCustomerAge( "Ivanov" ) == 18 );
	assert( c.getCustomerBalance( "Ivanov" ) == 722.0 );
	assert( c.getCustomerAllergicIngredient( "Ivanov" ) == "" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_2_customer_several )
{
	Controller c;
	c.createCustomer( "Ivanov", 25, 1000.0 );
	c.createCustomer( "Petrov", 60, 25445.0 );

	assert( c.getCustomerAge( "Ivanov" ) == 25 );
	assert( c.getCustomerBalance( "Ivanov" ) == 1000.0 );
	assert( c.getCustomerAllergicIngredient( "Ivanov" ) == "" );

	assert( c.getCustomerAge( "Petrov" ) == 60 );
	assert( c.getCustomerBalance( "Petrov" ) == 25445.0 );
	assert( c.getCustomerAllergicIngredient( "Petrov" ) == "" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_3_customer_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.createCustomer( "", 25, 1000.0 )
		,	Messages::EmptyCustomerName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_4_customer_with_negative_age )
{
	Controller c;

	ASSERT_THROWS(
			c.createCustomer( "Petrov", -1, 1000.0 )
		,	Messages::NegativeAge
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_5_customer_with_negative_balance )
{
	Controller c;

	ASSERT_THROWS(
			c.createCustomer( "Petrov", 20, -2.0 )
		,	Messages::NegativeBalance
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_6_customer_with_duplicated_name )
{
	Controller c;
	c.createCustomer( "Petrov", 20, 100.0 );

	ASSERT_THROWS(
			c.createCustomer( "Petrov", 21, 200.0 )
		,	Messages::CustomerNameNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_7_customer_with_allergy )
{
	Controller c;
	c.createCustomer( "Ivanov", 53, 5569.0 );
	c.makeCustomerAllergicTo( "Ivanov", "Cucumber" );

	assert( c.getCustomerAge( "Ivanov" ) == 53 );
	assert( c.getCustomerBalance( "Ivanov" ) == 5569.0 );
	assert( c.getCustomerAllergicIngredient( "Ivanov" ) == "Cucumber" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_8_customer_with_empty_allergic_ingredient )
{
	Controller c;
	c.createCustomer( "Ivanov", 53, 5569.7 );

	ASSERT_THROWS(
			c.makeCustomerAllergicTo( "Ivanov", "" )
		,	Messages::EmptyIngredientName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_9_customer_reassign_allergic_ingredient )
{
	Controller c;
	c.createCustomer( "Ivanov", 99, 458.2 );
	c.makeCustomerAllergicTo( "Ivanov", "Cucumber" );
	c.makeCustomerAllergicTo( "Ivanov", "Apple" );

	assert( c.getCustomerAge( "Ivanov" ) == 99 );
	assert( c.getCustomerBalance( "Ivanov" ) == 458.2 );
	assert( c.getCustomerAllergicIngredient( "Ivanov" ) == "Apple" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_10_customer_obtain_customer_data_by_empty_name )
{
	Controller c;
	c.createCustomer( "Ivanov", 43, 45.5 );
	c.makeCustomerAllergicTo( "Ivanov", "Apple" );

	ASSERT_THROWS(
			c.getCustomerAge( "" )
		,	Messages::CustomerNameUnknown
	);
	ASSERT_THROWS(
			c.getCustomerBalance( "" )
		,	Messages::CustomerNameUnknown
	);
	ASSERT_THROWS(
			c.getCustomerAllergicIngredient( "" )
		,	Messages::CustomerNameUnknown
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_1_11_customer_obtain_customer_data_by_missing_name )
{
	Controller c;
	c.createCustomer( "Ivanov", 43, 45.0 );
	c.makeCustomerAllergicTo( "Ivanov", "Apple" );

	ASSERT_THROWS(
			c.getCustomerAge( "Petrov" )
		,	Messages::CustomerNameUnknown
	);
	ASSERT_THROWS(
			c.getCustomerBalance( "Petrov" )
		,	Messages::CustomerNameUnknown
	);
	ASSERT_THROWS(
			c.getCustomerAllergicIngredient( "Petrov" )
		,	Messages::CustomerNameUnknown
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_1_beverage_beer )
{
	Controller c;
	c.createBeer( "Terry", 500, 5.0 );
	c.createBeer( "Gry", 300, 7.4 );

	assert( c.getBeveragePrice( "Terry" ) == 5.0 );
	assert( c.getBeverageVolumeMl( "Terry" ) == 500 );
	assert( c.getBeverageMainIngredient( "Terry" ) == "Corn" );

	assert( c.getBeveragePrice( "Gry" ) == 7.4 );
	assert( c.getBeverageVolumeMl( "Gry" ) == 300 );
	assert( c.getBeverageMainIngredient( "Gry" ) == "Corn" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_2_beverage_juice )
{
	Controller c;
	c.createJuice( "Laguna", 100, 10.0, "Apple" );
	c.createJuice( "Eute", 124, 11.1, "Steel" );

	assert( c.getBeveragePrice( "Laguna" ) == 10.0 );
	assert( c.getBeverageVolumeMl( "Laguna" ) == 100 );
	assert( c.getBeverageMainIngredient( "Laguna" ) == "Apple" );

	assert( c.getBeveragePrice( "Eute" ) == 11.1 );
	assert( c.getBeverageVolumeMl( "Eute" ) == 124 );
	assert( c.getBeverageMainIngredient( "Eute" ) == "Steel" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_3_beverage_poison )
{
	Controller c;
	c.createPoison( "Fairy", 50, 56.7 );
	c.createPoison( "Tide", 51, 67.8 );

	assert( c.getBeveragePrice( "Fairy" ) == 56.7 );
	assert( c.getBeverageVolumeMl( "Fairy" ) == 50 );
	assert( c.getBeverageMainIngredient( "Fairy" ) == "Technical alcohol" );

	assert( c.getBeveragePrice( "Tide" ) == 67.8 );
	assert( c.getBeverageVolumeMl( "Tide" ) == 51 );
	assert( c.getBeverageMainIngredient( "Tide" ) == "Technical alcohol" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_4_beverage_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.createBeer( "", 500, 7.0 )
		,	Messages::EmptyBeverageName
	);
	ASSERT_THROWS(
			c.createJuice( "", 500, 7.0, "Apple" )
		,	Messages::EmptyBeverageName
	);
	ASSERT_THROWS(
			c.createPoison( "", 500, 7.0 )
		,	Messages::EmptyBeverageName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_5_beverage_with_negative_volume )
{
	Controller c;

	ASSERT_THROWS(
			c.createBeer( "Terry", -100, 7.0 )
		,	Messages::NonPositiveAmount
	);
	ASSERT_THROWS(
			c.createJuice( "Laguna", -890, 7.0, "Apple" )
		,	Messages::NonPositiveAmount
	);
	ASSERT_THROWS(
			c.createPoison( "Fairy", -1, 7.0 )
		,	Messages::NonPositiveAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_6_beverage_with_negative_price )
{
	Controller c;

	ASSERT_THROWS(
			c.createBeer( "Terry", 400, -2.0 )
		,	Messages::NonPositivePrice
	);
	ASSERT_THROWS(
			c.createJuice( "Laguna", 1, -0.1, "Apple" )
		,	Messages::NonPositivePrice
	);
	ASSERT_THROWS(
			c.createPoison( "Fairy", 11, -70.0 )
		,	Messages::NonPositivePrice
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_7_beverage_with_empty_main_ingredient_for_juice )
{
	Controller c;

	ASSERT_THROWS(
			c.createJuice( "Laguna", 100, 10.0, "" )
		,	Messages::EmptyIngredientName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_8_beverage_the_same_name_for_the_same_beverages_type )
{
	Controller c;
	c.createBeer( "Oxy", 400, 4.5 );

	ASSERT_THROWS(
			c.createBeer( "Oxy", 501, 5.5 )
		,	Messages::BeverageNameNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_9_beverage_the_same_name_for_the_different_beverages_types )
{
	Controller c;
	c.createBeer( "Oxy", 400, 4.5 );

	ASSERT_THROWS(
			c.createPoison( "Oxy", 501, 5.5 )
		,	Messages::BeverageNameNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_10_beverage_obtain_beverage_data_by_empty_name )
{
	Controller c;
	c.createBeer( "Terry", 1000, 45.78 );

	ASSERT_THROWS(
			c.getBeveragePrice( "" )
		,	Messages::BeverageNameUnknown
	);
	ASSERT_THROWS(
			c.getBeverageVolumeMl( "" )
		,	Messages::BeverageNameUnknown
	);
	ASSERT_THROWS(
			c.getBeverageMainIngredient( "" )
		,	Messages::BeverageNameUnknown
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_2_11_beverage_obtain_beverage_data_by_missing_name )
{
	Controller c;
	c.createBeer( "Doxy", 1000, 45.78 );

	ASSERT_THROWS(
			c.getBeveragePrice( "Foxy" )
		,	Messages::BeverageNameUnknown
	);
	ASSERT_THROWS(
			c.getBeverageVolumeMl( "Foxy" )
		,	Messages::BeverageNameUnknown
	);
	ASSERT_THROWS(
			c.getBeverageMainIngredient( "Foxy" )
		,	Messages::BeverageNameUnknown
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_1_selling_success_for_juice )
{
	Controller c;
	c.createCustomer( "Bob", 18, 10.0 );
	c.createJuice( "Doxy", 1000, 8.0, "Apple" );

	assert( c.trySelling( "Bob", "Doxy" ) == true );
	assert( c.getCustomerBalance( "Bob" ) == 2.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_2_selling_not_enough_money_for_juice )
{
	Controller c;
	c.createCustomer( "Bob", 18, 7.0 );
	c.createJuice( "Doxy", 1000, 11.0, "Lemon" );

	assert( c.trySelling( "Bob", "Doxy" ) == false );
	assert( c.getCustomerBalance( "Bob" ) == 7.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_3_selling_too_young_for_beer )
{
	Controller c;
	c.createCustomer( "Bob", 20, 100.0 );
	c.createCustomer( "Elly", 16, 101.0 );
	c.createBeer( "Krago", 450, 12.5 );

	assert( c.trySelling( "Elly", "Krago" ) == false );
	assert( c.getCustomerBalance( "Elly" ) == 101.0 );

	assert( c.trySelling( "Bob", "Krago" ) == true );
	assert( c.getCustomerBalance( "Bob" ) == 87.5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_4_selling_allergy_to_apples )
{
	Controller c;
	c.createCustomer( "Bob", 18, 10.0 );
	c.makeCustomerAllergicTo( "Bob", "Apple" );
	c.createJuice( "Doxy", 1000, 8.0, "Apple" );

	assert( c.trySelling( "Bob", "Doxy" ) == false );
	assert( c.getCustomerBalance( "Bob" ) == 10.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_5_selling_allergy_to_corn )
{
	Controller c;
	c.createCustomer( "Bob", 18, 12.0 );
	c.makeCustomerAllergicTo( "Bob", "Corn" );
	c.createBeer( "Tuki", 1000, 1.0 );

	assert( c.trySelling( "Bob", "Tuki" ) == false );
	assert( c.getCustomerBalance( "Bob" ) == 12.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_6_selling_allergy_to_cucumber )
{
	Controller c;
	c.createCustomer( "Bob", 18, 12.0 );
	c.makeCustomerAllergicTo( "Bob", "Cucumber" );
	c.createBeer( "Tuki", 1000, 1.0 );

	assert( c.trySelling( "Bob", "Tuki" ) == true );
	assert( c.getCustomerBalance( "Bob" ) == 11.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_7_selling_poison_is_not_sold )
{
	Controller c;
	c.createCustomer( "Bob", 25, 15.0 );
	c.createPoison( "Qwerty", 100, 1.0 );

	assert( c.trySelling( "Bob", "Qwerty" ) == false );
	assert( c.getCustomerBalance( "Bob" ) == 15.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_8_selling_several_things_are_sold_for_one_customer )
{
	Controller c;
	c.createCustomer( "Bob", 25, 15.0 );
	c.createBeer( "Fro", 500, 4.0 );
	c.createJuice( "Ascii", 256, 3.5, "Char" );

	assert( c.trySelling( "Bob", "Fro" ) == true );
	assert( c.getCustomerBalance( "Bob" ) == 11.0 );

	assert( c.trySelling( "Bob", "Ascii" ) == true );
	assert( c.getCustomerBalance( "Bob" ) == 7.5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_9_selling_one_thing_is_sold_for_several_customers )
{
	Controller c;
	c.createCustomer( "Dev", 27, 50.0 );
	c.createCustomer( "Kate", 24, 6.0 );
	c.createJuice( "Ascii", 256, 4.5, "Char" );

	assert( c.trySelling( "Dev", "Ascii" ) == true );
	assert( c.getCustomerBalance( "Dev" ) == 45.5 );

	assert( c.trySelling( "Kate", "Ascii" ) == true );
	assert( c.getCustomerBalance( "Kate" ) == 1.5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_3_10_selling_the_same_thing_is_sold_for_one_customer )
{
	Controller c;
	c.createCustomer( "Dev", 27, 50.0 );
	c.createJuice( "Ascii", 256, 10.0, "Char" );

	assert( c.trySelling( "Dev", "Ascii" ) == true );
	assert( c.trySelling( "Dev", "Ascii" ) == true );
	assert( c.trySelling( "Dev", "Ascii" ) == true );
	assert( c.trySelling( "Dev", "Ascii" ) == true );
	assert( c.trySelling( "Dev", "Ascii" ) == true );
	assert( c.getCustomerBalance( "Dev" ) == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( beverages_4_1_complex_cases_simple_flow )
{
	Controller c;

	c.createCustomer( "Ivan", 30, 20.0 );
	c.createCustomer( "Petr", 28,  0.0 );
	c.createCustomer( "Sidor", 16, 11.0 );
	c.createCustomer( "Fedor", 25, 100.0 );

	c.makeCustomerAllergicTo( "Fedor", "Orange" );

	c.createJuice( "Apple juice", 1000, 10.25, "Apple" );
	c.createJuice( "Orange juice", 1000, 10.25, "Orange" );
	c.createBeer( "Low-Quality Beer", 500, 5.00 );
	c.createBeer( "High-Quality Beer", 500, 25.00 );
	c.createPoison( "Black Shaitan", 700, 15.00 );

	assert( c.getBeverageMainIngredient( "Apple juice" ) == "Apple" );
	assert( c.getBeverageMainIngredient( "Orange juice" ) == "Orange" );
	assert( c.getBeverageMainIngredient( "Low-Quality Beer" ) == "Corn" );
	assert( c.getBeverageMainIngredient( "High-Quality Beer" ) == "Corn" );
	assert( c.getBeverageMainIngredient( "Black Shaitan" ) == "Technical alcohol" );

	assert( c.trySelling( "Ivan", "High-Quality Beer" ) == false ); // not enough money
	assert( c.getCustomerBalance( "Ivan" ) == 20.0 );

	assert( c.trySelling( "Ivan", "Low-Quality Beer" ) == true );
	assert( c.getCustomerBalance( "Ivan" ) == 15.0 );

	assert( c.trySelling( "Petr", "Apple juice" ) == false ); // not enough money
	assert( c.getCustomerBalance( "Petr" ) == 0.0 );

	assert( c.trySelling( "Sidor", "Low-Quality Beer" ) == false ); // too young
	assert( c.getCustomerBalance( "Sidor" ) == 11 );
	assert( c.trySelling( "Sidor", "Apple juice" ) == true );
	assert( c.getCustomerBalance( "Sidor" ) == 0.75 );

	assert( c.trySelling( "Fedor", "Orange juice" ) == false ); // alergic to oranges
	assert( c.getCustomerBalance( "Fedor" ) == 100 );
	assert( c.trySelling( "Fedor", "Black Shaitan" ) == false ); // don't drink this stuff
	assert( c.getCustomerBalance( "Fedor" ) == 100 );
}


/*****************************************************************************/
