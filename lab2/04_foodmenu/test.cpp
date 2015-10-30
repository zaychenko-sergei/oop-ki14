// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"
#include "foodcomponents.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_product_trace_properties )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );

	assert( c.getFoodProductComponents( "Milk" ) == FoodComponents( 3.2, 3.6, 4.8 ) );
	assert( c.getFoodProductEnergeticValue( "Milk" ) == 64.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicate_product )
{
	Controller c;
	FoodComponents components{ 3.2, 3.6, 4.8 };
	c.createFoodProduct( "Milk", components, 64.0 );

	ASSERT_THROWS(
		c.createFoodProduct( "Milk", components, 64.0 ),
		Messages::ProductAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_product_empty_name )
{
	Controller c;
	FoodComponents components{ 3.2, 3.6, 4.8 };

	ASSERT_THROWS(
		c.createFoodProduct( "", components, 64.0 ),
		Messages::EmptyProductName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_product_negative_parameters )
{
	Controller c;

	ASSERT_THROWS(
		c.createFoodProduct( "Test", FoodComponents{ -1.0, 0.0, 0.0 }, 1.0 ),
		Messages::NegativeProteins
	);

	ASSERT_THROWS(
		c.createFoodProduct( "Test", FoodComponents{ 0.0, -1.0, 0.0 }, 1.0 ),
		Messages::NegativeFat
	);

	ASSERT_THROWS(
		c.createFoodProduct( "Test", FoodComponents{ 0.0, 0.0, -1.0 }, 1.0 ),
		Messages::NegativeCarbohydrates
	);

	ASSERT_THROWS(
		c.createFoodProduct( "Test", FoodComponents{ 0.0, 0.0, 0.0 }, -1.0 ),
		Messages::NegativeEnergeticValue
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_parameters_of_unexisting_product )
{
	Controller c;

	ASSERT_THROWS(
		c.getFoodProductComponents( "Surprise" ),
		Messages::ProductNotFound
	);

	ASSERT_THROWS(
		c.getFoodProductEnergeticValue( "Surprise" ),
		Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_empty_menu )
{
	Controller c;
	c.createMenu( "Breakfast" );
	assert( c.getProductsInMenu( "Breakfast" ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_menu_empty_title )
{
	Controller c;

	ASSERT_THROWS(
		c.createMenu( "" ),
		Messages::EmptyMenuTitle
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_menu_duplicate_title )
{
	Controller c;

	c.createMenu( "Breakfast" );

	ASSERT_THROWS(
		c.createMenu( "Breakfast" ),
		Messages::MenuAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_products_of_not_existing_menu )
{
	Controller c;

	ASSERT_THROWS(
		c.getProductsInMenu( "Surprise" ),
		Messages::MenuNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_product_to_menu )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 200 );

	assert( c.getProductsInMenu( "Breakfast" ) == std::vector< std::string >{ "Milk" } );
	assert( c.getProductWeightInMenu( "Breakfast", "Milk" ) == 200 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_two_products_to_menu )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents(  3.2,  3.6, 4.8 ),  64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );

	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 200 );
	c.addProductToMenu( "Breakfast", "Eggs", 100 );

	std::vector< std::string > expectedProducts{ "Eggs", "Milk" };
	assert( c.getProductsInMenu( "Breakfast" ) == expectedProducts );
	assert( c.getProductWeightInMenu( "Breakfast", "Milk" ) == 200 );
	assert( c.getProductWeightInMenu( "Breakfast", "Eggs" ) == 100 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_product_to_two_menus )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );
	c.createMenu( "Lunch" );

	c.addProductToMenu( "Breakfast", "Milk", 200 );
	c.addProductToMenu( "Lunch", "Milk", 300 );

	assert( c.getProductsInMenu( "Breakfast" ) == std::vector< std::string > { "Milk" } );
	assert( c.getProductsInMenu( "Lunch" ) == std::vector< std::string > { "Milk" } );
	assert( c.getProductWeightInMenu( "Breakfast", "Milk" ) == 200 );
	assert( c.getProductWeightInMenu( "Lunch", "Milk" ) == 300 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_product_to_menu_complex_case )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );
	c.createFoodProduct( "Potatoes", FoodComponents( 2.0, 0.4, 16.3 ), 77.0 );

	c.createMenu( "Breakfast" );
	c.createMenu( "Lunch" );

	c.addProductToMenu( "Breakfast", "Milk", 200 );
	c.addProductToMenu( "Breakfast", "Eggs", 100 );

	c.addProductToMenu( "Lunch", "Eggs", 150 );
	c.addProductToMenu( "Lunch", "Potatoes", 300 );

	std::vector< std::string > expectedBreakfastProducts{ "Eggs", "Milk" };
	assert( c.getProductsInMenu( "Breakfast" ) == expectedBreakfastProducts );

	std::vector< std::string > expectedLunchProducts{ "Eggs", "Potatoes" };
	assert( c.getProductsInMenu( "Lunch" ) == expectedLunchProducts );

	assert( c.getProductWeightInMenu( "Breakfast", "Milk" ) == 200 );
	assert( c.getProductWeightInMenu( "Breakfast", "Eggs" ) == 100 );
	assert( c.getProductWeightInMenu( "Lunch", "Eggs" ) == 150 );
	assert( c.getProductWeightInMenu( "Lunch", "Potatoes" ) == 300 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_duplicate_product_to_menu )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 200 );

	ASSERT_THROWS(
		c.addProductToMenu( "Breakfast", "Milk", 100 ),
		Messages::ProductAlreadyIncluded
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_bad_product_weight )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );

	ASSERT_THROWS(
		c.addProductToMenu( "Breakfast", "Milk", -1 ),
		Messages::NonPositiveWeight
	);

	ASSERT_THROWS(
		c.addProductToMenu( "Breakfast", "Milk", 0 ),
		Messages::NonPositiveWeight
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_product_to_menu_unknown_object )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );

	ASSERT_THROWS(
		c.addProductToMenu( "Breakfast", "Surprise", 100 ),
		Messages::ProductNotFound
	);

	ASSERT_THROWS(
		c.addProductToMenu( "Surprise", "Milk", 100 ),
		Messages::MenuNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_remove_product_from_menu )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );

	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 100 );
	c.addProductToMenu( "Breakfast", "Eggs", 200 );

	c.removeProductFromMenu( "Breakfast", "Milk" );

	assert( c.getProductsInMenu( "Breakfast" ) == std::vector< std::string >{ "Eggs" } );
	assert( c.getProductWeightInMenu( "Breakfast", "Eggs" ) == 200 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_remove_product_that_was_not_included )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );

	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 100 );

	ASSERT_THROWS(
		c.removeProductFromMenu( "Breakfast", "Eggs" ),
		Messages::ProductNotIncluded
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_remove_product_not_existing_object )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );

	ASSERT_THROWS(
		c.removeProductFromMenu( "Breakfast", "Suprise" ),
		Messages::ProductNotFound
	);

	ASSERT_THROWS(
		c.removeProductFromMenu( "Surprise", "Milk" ),
		Messages::MenuNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_product_in_menu )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 100 );

	c.updateProductWeightInMenu( "Breakfast", "Milk", 200 );

	assert( c.getProductsInMenu( "Breakfast" ) == std::vector< std::string > { "Milk" } );
	assert( c.getProductWeightInMenu( "Breakfast", "Milk" ) == 200 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_product_that_was_not_included )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );

	ASSERT_THROWS(
		c.updateProductWeightInMenu( "Breakfast", "Milk", 200 ),
		Messages::ProductNotIncluded
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_product_bad_new_weight )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 100 );

	ASSERT_THROWS(
		c.updateProductWeightInMenu( "Breakfast", "Milk", -1 ),
		Messages::NonPositiveWeight
	);

	ASSERT_THROWS(
		c.updateProductWeightInMenu( "Breakfast", "Milk", 0 ),
		Messages::NonPositiveWeight
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_product_unknown_object )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );

	ASSERT_THROWS(
		c.updateProductWeightInMenu( "Breakfast", "Surprise", 100 ),
		Messages::ProductNotFound
	);

	ASSERT_THROWS(
		c.updateProductWeightInMenu( "Surprise", "Milk", 100 ),
		Messages::MenuNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_product_weight_unknown_objects )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createMenu( "Breakfast" );

	ASSERT_THROWS(
		c.getProductWeightInMenu( "Breakfast", "Surprise" ),
		Messages::ProductNotFound
	);

	ASSERT_THROWS(
		c.getProductWeightInMenu( "Surprise", "Milk" ),
		Messages::MenuNotFound
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_calculate_total_components_of_menu )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents(  3.2,  3.6, 4.8 ),  64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );

	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 200 );
	c.addProductToMenu( "Breakfast", "Eggs", 300 );

	FoodComponents totalComponents = c.getTotalComponentsInMenu( "Breakfast" );
	assert( totalComponents.getProteins() == 44.5 ); // 200 / 100 * 3.2 + 300 / 100 * 12.7  = 44.5
	assert( totalComponents.getFat()      == 41.7 ); // 200 / 100 * 3.6 + 300 / 100 * 11.5  = 41.7
	assert( totalComponents.getCarbo()    == 11.7 ); // 200 / 100 * 4.8 + 300 / 100 * 0.7   = 11.7
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_calculate_total_components_empty_menu )
{
	Controller c;
	c.createMenu( "Breakfast" );

	assert( c.getTotalComponentsInMenu( "Breakfast" ) == FoodComponents( 0.0, 0.0, 0.0 ) );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_calculate_total_components_not_existing_menu )
{
	Controller c;

	ASSERT_THROWS(
		c.getTotalComponentsInMenu( "Surprise" ),
		Messages::MenuNotFound
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_menu_daily_energetic_percentage )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );

	c.createMenu( "Breakfast" );
	c.addProductToMenu( "Breakfast", "Milk", 200 );
	c.addProductToMenu( "Breakfast", "Eggs", 300 );

	// 200 / 100 * 64.0 + 300 / 100 * 157.0 = 599
	// 599 / 2396 * 100.0% = 25.0 % 
	assert( c.getMenuDailyEnergeticPercentage( "Breakfast", 2396.00 ) == 25.0 ); 
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_menu_daily_energetic_percentage_empty_menu )
{
	Controller c;
	c.createMenu( "Breakfast" );

	assert( c.getMenuDailyEnergeticPercentage( "Breakfast" ) == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_menu_daily_energetic_percentage_not_existing_menu )
{
	Controller c;
	ASSERT_THROWS(
		c.getMenuDailyEnergeticPercentage( "Surprise" ),
		Messages::MenuNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_find_product_minimal_fat_over_given_energy )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );
	c.createFoodProduct( "Potatoes", FoodComponents( 2.0, 0.4, 16.3 ), 77.0 );

	assert( c.findProductWithMinimalFatWithEnergyOver( 70.0 )  == "Potatoes" );
	assert( c.findProductWithMinimalFatWithEnergyOver( 100.0 ) == "Eggs"     );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_find_product_minimal_fat_over_given_energy_given_bad_energy )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );

	ASSERT_THROWS(
		c.findProductWithMinimalFatWithEnergyOver( -1.0 ),
		Messages::NegativeEnergeticValue
	);

	assert( c.findProductWithMinimalFatWithEnergyOver( 0.0 ) == "Milk" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_find_menu_with_biggest_weight )
{
	Controller c;
	c.createFoodProduct( "Milk", FoodComponents( 3.2, 3.6, 4.8 ), 64.0 );
	c.createFoodProduct( "Eggs", FoodComponents( 12.7, 11.5, 0.7 ), 157.0 );
	c.createFoodProduct( "Potatoes", FoodComponents( 2.0, 0.4, 16.3 ), 77.0 );

	c.createMenu( "Breakfast" );
	c.createMenu( "Lunch" );

	c.addProductToMenu( "Breakfast", "Milk", 100 );
	c.addProductToMenu( "Breakfast", "Eggs", 120 );

	c.addProductToMenu( "Lunch", "Milk", 150 );
	c.addProductToMenu( "Lunch", "Potatoes", 250 );

	assert( c.findMenuWithBiggestWeight() == "Lunch" );
}


/*****************************************************************************/
