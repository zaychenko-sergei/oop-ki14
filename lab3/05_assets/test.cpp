// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_owner )
{
	Controller c;
	c.createOwner( "Ivanov" );

	assert( c.getOwnerAssetNames( "Ivanov" ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_owners )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.createOwner( "Petrov" );

	assert( c.getOwnerAssetNames( "Ivanov" ).empty() );
	assert( c.getOwnerAssetNames( "Petrov" ).empty() );
}


/*****************************************************************************/



DECLARE_OOP_TEST ( test_create_owner_empty_name )
{
	Controller c;
	
	ASSERT_THROWS(
			c.createOwner( "" )
		,	Messages::OwnerNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_owner_duplicate_name )
{
	Controller c;
	c.createOwner( "Ivanov" );

	ASSERT_THROWS(
			c.createOwner( "Ivanov" )
		,	Messages::OwnerNameNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_real_estate )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Villa", 1000000.0, RealEstateState::Ideal );

	assert( c.getOwnerAssetNames( "Ivanov" ) == std::unordered_set< std::string > { "Villa" } );

	assert( c.getAssetBaseCost( "Ivanov", "Villa" ) == 1000000.0 );
	assert( c.getRealEstateState( "Ivanov", "Villa" ) == RealEstateState::Ideal );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_real_estates )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Villa", 1000000.0, RealEstateState::Ideal );
	c.addRealEstate( "Ivanov", "Dacha",   10000.0, RealEstateState::CapitalRepairs );

	std::unordered_set< std::string > expectedAssets{ "Villa", "Dacha" };
	assert( c.getOwnerAssetNames( "Ivanov" ) == expectedAssets );

	assert( c.getAssetBaseCost( "Ivanov", "Villa" ) == 1000000.0 );
	assert( c.getRealEstateState( "Ivanov", "Villa" ) == RealEstateState::Ideal );

	assert( c.getAssetBaseCost( "Ivanov", "Dacha" ) == 10000.0 );
	assert( c.getRealEstateState( "Ivanov", "Dacha" ) == RealEstateState::CapitalRepairs );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_real_estate_empty_name )
{
	Controller c;
	c.createOwner( "Ivanov" );

	ASSERT_THROWS(
			c.addRealEstate( "Ivanov", "", 1000000.0, RealEstateState::Ideal )
		,	Messages::AssetNameEmpty
	);

	assert( c.getOwnerAssetNames( "Ivanov" ).empty() );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_real_estate_duplicate_name )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Villa", 1000000.0, RealEstateState::Ideal );

	ASSERT_THROWS(
			c.addRealEstate( "Ivanov", "Villa", 1000000.0, RealEstateState::Ideal );
		,	Messages::AssetNameNotUniqueWithinOwner
	);

	assert( c.getOwnerAssetNames( "Ivanov" ) == std::unordered_set< std::string > { "Villa" } );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_real_estate_negative_price )
{
	Controller c;
	c.createOwner( "Ivanov" );

	ASSERT_THROWS(
			c.addRealEstate( "Ivanov", "Villa", -1.0, RealEstateState::Ideal )
		,	Messages::NegativeAssetBaseCost
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_real_estate_zero_price )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Villa", 0.0, RealEstateState::Ideal );

	assert( c.getOwnerAssetNames( "Ivanov" ) == std::unordered_set< std::string > { "Villa" } );

	assert( c.getAssetBaseCost( "Ivanov", "Villa" ) == 0.0 );
	assert( c.getRealEstateState( "Ivanov", "Villa" ) == RealEstateState::Ideal );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_vehicle )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addVehicle( "Ivanov", "Mers", 100000.0, 0, false );

	assert( c.getOwnerAssetNames( "Ivanov" ) == std::unordered_set< std::string > { "Mers" } );

	assert( c.getAssetBaseCost( "Ivanov", "Mers" ) == 100000.0 );
	assert( c.getVehicleYearsInUse( "Ivanov", "Mers" ) == 0 );
	assert( ! c.isVehicleCrashed( "Ivanov", "Mers" ) );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_vehicles )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addVehicle( "Ivanov", "Mers",  100000.0, 0,  false );
	c.addVehicle( "Ivanov", "Zapor",    200.0, 20, true );

	std::unordered_set< std::string > expectedAssets { "Mers", "Zapor" };
	assert( c.getOwnerAssetNames( "Ivanov" ) == expectedAssets );

	assert( c.getAssetBaseCost( "Ivanov", "Mers" ) == 100000.0 );
	assert( c.getVehicleYearsInUse( "Ivanov", "Mers" ) == 0 );
	assert( ! c.isVehicleCrashed( "Ivanov", "Mers" ) );

	assert( c.getAssetBaseCost( "Ivanov", "Zapor" ) == 200.0 );
	assert( c.getVehicleYearsInUse( "Ivanov", "Zapor" ) == 20 );
	assert( c.isVehicleCrashed( "Ivanov", "Zapor" ) );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_vehicle_empty_name )
{
	Controller c;
	c.createOwner( "Ivanov" );

	ASSERT_THROWS(
			c.addVehicle( "Ivanov", "", 200.0, 20, true )
		,	Messages::AssetNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_vehicle_duplicate_name )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addVehicle( "Ivanov", "Mers", 100000.0, 0, false );

	ASSERT_THROWS(
			c.addVehicle( "Ivanov", "Mers", 100000.0, 0, false );
		,	Messages::AssetNameNotUniqueWithinOwner
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_vehicle_negative_price )
{
	Controller c;
	c.createOwner( "Ivanov" );

	ASSERT_THROWS(
			c.addVehicle( "Ivanov", "Mers", -1.0, 0, false )
		,	Messages::NegativeAssetBaseCost
	);

	assert( c.getOwnerAssetNames( "Ivanov" ).empty() );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_vehicle_zero_price )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addVehicle( "Ivanov", "Zapor", 0.0, 20, true );

	assert( c.getOwnerAssetNames( "Ivanov" ) == std::unordered_set< std::string > { "Zapor" } );

	assert( c.getAssetBaseCost( "Ivanov", "Zapor" ) == 0.0 );
	assert( c.getVehicleYearsInUse( "Ivanov", "Zapor" ) == 20 );
	assert( c.isVehicleCrashed( "Ivanov", "Zapor" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_vehicle_negative_years )
{
	Controller c;
	c.createOwner( "Ivanov" );

	ASSERT_THROWS(
			c.addVehicle( "Ivanov", "Mers", 1000000, -1, false )
		,	Messages::NegativeVehicleUseYears
	);

	assert( c.getOwnerAssetNames( "Ivanov" ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_mix_real_estate_and_vehicle )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Villa", 1000000.0, RealEstateState::Ideal );
	c.addVehicle( "Ivanov", "Mers", 100000.0, 0, false );

	std::unordered_set< std::string > expectedAssets = { "Villa", "Mers" };
	assert( c.getOwnerAssetNames( "Ivanov" ) == expectedAssets );

	assert( c.getOwnerAssetsCurrentCost( "Ivanov" ) == 1100000.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_vehicle_named_same_as_real_estate )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Villa", 1000000.0, RealEstateState::Ideal );

	ASSERT_THROWS(
			c.addVehicle( "Ivanov", "Villa", 100000.0, 0, false )
		,	Messages::AssetNameNotUniqueWithinOwner
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_multiple_vehicles_try_cost )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addVehicle( "Ivanov", "V1", 1000, 0, false );
	c.addVehicle( "Ivanov", "V2", 1000, 1, false );
	c.addVehicle( "Ivanov", "V3", 1000, 1, true );
	c.addVehicle( "Ivanov", "V4", 1000, 2, false );
	c.addVehicle( "Ivanov", "V5", 1000, 2, true );

	assert( c.getAssetBaseCost( "Ivanov", "V1" ) == 1000 );
	assert( c.getAssetBaseCost( "Ivanov", "V2" ) == 1000 );
	assert( c.getAssetBaseCost( "Ivanov", "V3" ) == 1000 );
	assert( c.getAssetBaseCost( "Ivanov", "V4" ) == 1000 );
	assert( c.getAssetBaseCost( "Ivanov", "V5" ) == 1000 );

	assert( c.getAssetCurrentCost( "Ivanov", "V1" ) == 1000.0 );
	assert( c.getAssetCurrentCost( "Ivanov", "V2" ) ==  850.0 );
	assert( c.getAssetCurrentCost( "Ivanov", "V3" ) ==  425.0 );
	assert( c.getAssetCurrentCost( "Ivanov", "V4" ) ==  722.5 );
	assert( c.getAssetCurrentCost( "Ivanov", "V5" ) ==  361.25 );

	assert( c.getOwnerAssetsCurrentCost( "Ivanov" ) == 3358.75 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_multiple_real_estates_try_cost )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "RE1", 1000, RealEstateState::Ideal );
	c.addRealEstate( "Ivanov", "RE2", 1000, RealEstateState::CosmeticRepairs );
	c.addRealEstate( "Ivanov", "RE3", 1000, RealEstateState::CapitalRepairs );
	c.addRealEstate( "Ivanov", "RE4", 1000, RealEstateState::Construction );

	assert( c.getAssetBaseCost( "Ivanov", "RE1" ) == 1000 );
	assert( c.getAssetBaseCost( "Ivanov", "RE2" ) == 1000 );
	assert( c.getAssetBaseCost( "Ivanov", "RE3" ) == 1000 );
	assert( c.getAssetBaseCost( "Ivanov", "RE4" ) == 1000 );

	assert( c.getAssetCurrentCost( "Ivanov", "RE1" ) == 1000.0 );
	assert( c.getAssetCurrentCost( "Ivanov", "RE2" ) ==  850.0 );
	assert( c.getAssetCurrentCost( "Ivanov", "RE3" ) ==  700.0 );
	assert( c.getAssetCurrentCost( "Ivanov", "RE4" ) ==  500.0 );

	assert( c.getOwnerAssetsCurrentCost( "Ivanov" ) == 3050.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_calc_cost_mixed_assets )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "RE", 2000, RealEstateState::Ideal );
	c.addVehicle( "Ivanov", "V", 1000, 0, false );

	assert( c.getAssetBaseCost( "Ivanov", "RE" ) == 2000 );
	assert( c.getAssetBaseCost( "Ivanov", "V" )  == 1000 );

	assert( c.getAssetCurrentCost( "Ivanov", "RE" ) == 2000.0 );
	assert( c.getAssetCurrentCost( "Ivanov", "V" )  == 1000.0 );

	assert( c.getOwnerAssetsCurrentCost( "Ivanov" ) == 3000.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_repair_real_estate )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Lachuga", 10000.0, RealEstateState::Construction );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::Construction );
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 5000.0 );

	c.repair( "Ivanov", "Lachuga" );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::CapitalRepairs );
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 7000.0 );

	c.repair( "Ivanov", "Lachuga" );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::CosmeticRepairs );
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 8500.0 );

	c.repair( "Ivanov", "Lachuga" );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::Ideal );
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 10000.0 );

	ASSERT_THROWS(
			c.repair( "Ivanov", "Lachuga" )
		,	Messages::RepairingIdealRealEstate
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_damage_real_estate )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addRealEstate( "Ivanov", "Lachuga", 10000.0, RealEstateState::Ideal );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::Ideal );
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 10000.0 );

	c.damage( "Ivanov", "Lachuga" );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::CosmeticRepairs);
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 8500.0 );

	c.damage( "Ivanov", "Lachuga" );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::CapitalRepairs );
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 7000.0 );

	c.damage( "Ivanov", "Lachuga" );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::Construction);
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 5000.0 );

	c.damage( "Ivanov", "Lachuga" );

	assert( c.getRealEstateState( "Ivanov", "Lachuga" ) == RealEstateState::Construction );
	assert( c.getAssetCurrentCost( "Ivanov", "Lachuga" ) == 5000.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_repair_vehicle )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addVehicle( "Ivanov", "Tachka", 1000, 0, true );

	assert( c.getAssetCurrentCost( "Ivanov", "Tachka" ) == 500 );
	assert( c.isVehicleCrashed( "Ivanov", "Tachka" ) );

	c.repair( "Ivanov", "Tachka" );

	assert( c.getAssetCurrentCost( "Ivanov", "Tachka" ) == 1000 );
	assert( ! c.isVehicleCrashed( "Ivanov", "Tachka" ) );

	ASSERT_THROWS(
			c.repair( "Ivanov", "Tachka" )
		,	Messages::RepairingWorkingVehicle
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_damage_vehicle )
{
	Controller c;
	c.createOwner( "Ivanov" );
	c.addVehicle( "Ivanov", "Tachka", 1000, 0, false );

	assert( c.getAssetCurrentCost( "Ivanov", "Tachka" ) == 1000 );
	assert( ! c.isVehicleCrashed( "Ivanov", "Tachka" ) );

	c.damage( "Ivanov", "Tachka" );

	assert( c.getAssetCurrentCost( "Ivanov", "Tachka" ) == 500 );
	assert( c.isVehicleCrashed( "Ivanov", "Tachka" ) );

	c.damage( "Ivanov", "Tachka" );

	assert( c.getAssetCurrentCost( "Ivanov", "Tachka" ) == 500 );
	assert( c.isVehicleCrashed( "Ivanov", "Tachka" ) );
}


/*****************************************************************************/
