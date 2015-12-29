// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"
#include "constants.hpp"

#include "testslib.hpp"

/*****************************************************************************/

const double eps = 0.00001;

#define CHECK_EQUAL( _a, _b ) assert( abs( _a - _b ) < eps )

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_counted_consumer )
{
	int countedID = 4598;

	Controller c;
	c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" );

	CHECK_EQUAL( c.getConsumerDebt( countedID, WaterPrice ), 0 );
	CHECK_EQUAL( c.getTotalDebt( WaterPrice ), 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_counted_consumer_empty_name )
{
	int countedID = 4598;

	Controller c;
	ASSERT_THROWS(
			c.createCountedConsumer( countedID, "", "Lenina 15" )
		,	Messages::EmptyConsumerName
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_counted_consumer_empty_address )
{
	int countedID = 4598;

	Controller c;
	ASSERT_THROWS(
			c.createCountedConsumer( countedID, "Ivanov", "" )
		,	Messages::EmptyConsumerAddress
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_counted_consumer_negative_id )
{
	int countedID = -598;

	Controller c;
	ASSERT_THROWS(
			c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" )
		,	Messages::NegativeConsumerID
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_consumer )
{
	int standardID = 1230;
	int nUsers = 2;

	Controller c;
	c.createStandardConsumer( standardID, "Petrov", "Sumska' 22", nUsers );

	double expectedDebt = WaterPrice * StandardWaterConsumptionPerUser * nUsers;

	CHECK_EQUAL( c.getConsumerDebt( standardID, WaterPrice ), expectedDebt );

	CHECK_EQUAL( c.getTotalDebt( WaterPrice ), expectedDebt );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_consumer_empty_name )
{
	int standardID = 1230;

	Controller c;
	ASSERT_THROWS(
			c.createStandardConsumer( standardID, "", "Sumska' 22", 2 )
		,	Messages::EmptyConsumerName
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_consumer_empty_address )
{
	int standardID = 1230;

	Controller c;
	ASSERT_THROWS(
			c.createStandardConsumer( standardID, "Petrov", "", 2 )
		,	Messages::EmptyConsumerAddress
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_consumer_negative_id )
{
	int countedID = -123;

	Controller c;
	ASSERT_THROWS(
			c.createStandardConsumer( countedID, "Petrov", "Sumska' 22", 2 )
		,	Messages::NegativeConsumerID
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_consumer_negative_users_count )
{
	int countedID = 1235;

	Controller c;
	ASSERT_THROWS(
			c.createStandardConsumer( countedID, "Petrov", "Sumska' 22", -2 )
		,	Messages::NonPositiveUsersCount
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_consumer_zero_users_count )
{
	int countedID = 1235;

	Controller c;
	ASSERT_THROWS(
			c.createStandardConsumer( countedID, "Petrov", "Sumska' 22", 0 )
		,	Messages::NonPositiveUsersCount
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_subsidized_consumer )
{
	int standardID = 6173;

	Controller c;
	c.createSubsidizedConsumer( standardID, "Sidorov", "Klochkivska 56" );

	CHECK_EQUAL( c.getConsumerDebt( standardID, WaterPrice ), 0 );
	CHECK_EQUAL( c.getTotalDebt( WaterPrice ), 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_subsidized_consumer_empty_name )
{
	int standardID = 6173;

	Controller c;
	ASSERT_THROWS(
			c.createCountedConsumer( standardID, "", "Klochkivska 56" )
		,	Messages::EmptyConsumerName
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_subsidized_consumer_empty_address )
{
	int standardID = 6173;

	Controller c;
	ASSERT_THROWS(
			c.createSubsidizedConsumer( standardID, "Sidorov", "" )
		,	Messages::EmptyConsumerAddress
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_subsidized_consumer_negative_id )
{
	int countedID = -617;

	Controller c;
	ASSERT_THROWS(
			c.createSubsidizedConsumer( countedID, "Sidorov", "Klochkivska 56" )
		,	Messages::NegativeConsumerID
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_multiple_consumers )
{
	int countedID = 8450, standardID = 6173, subsidizedID = 1460;

	Controller c;
	c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" );
	c.createSubsidizedConsumer( subsidizedID, "Sidorov", "Klochkivska 56" );
	c.createStandardConsumer( standardID, "Petrov", "Sumska' 22", 2 );

	double expectedDebt = WaterPrice * StandardWaterConsumptionPerUser * 2;

	CHECK_EQUAL( c.getConsumerDebt( standardID, WaterPrice ), expectedDebt );
	CHECK_EQUAL( c.getTotalDebt( WaterPrice ), expectedDebt );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_use_water_for_counted_consumer )
{
	int countedID = 8450;
	double waterAmount = 4.2;

	Controller c;
	c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" );

	c.useWater( countedID, waterAmount );
	c.useWater( countedID, waterAmount );

	double expectedDebt = WaterPrice * waterAmount * 2;

	CHECK_EQUAL( c.getConsumerDebt( countedID, WaterPrice ), expectedDebt );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_use_water_for_counted_consumer_negative_consume )
{
	int countedID = 8450;
	double waterAmount = -1.2;

	Controller c;
	c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" );

	ASSERT_THROWS(
			c.useWater( countedID, waterAmount )
		,	Messages::NonPositiveConsumption
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_use_water_for_counted_consumer_zero_consume )
{
	int countedID = 8450;
	double waterAmount = 0.0;

	Controller c;
	c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" );

	ASSERT_THROWS(
			c.useWater( countedID, waterAmount )
		,	Messages::NonPositiveConsumption
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_use_water_for_standard_consumer )
{
	int standardID = 4521, nUsers = 3;

	Controller c;
	c.createStandardConsumer( standardID, "Petrov", "Sumska' 22", nUsers );

	c.useWater( standardID, 1.48);
	c.useWater( standardID, 2.34 );

	double expectedDebt = WaterPrice * StandardWaterConsumptionPerUser * nUsers;

	CHECK_EQUAL( c.getConsumerDebt( standardID, WaterPrice ), expectedDebt );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_use_water_for_subsidized_consumer )
{
	int subsidizedID = 6021;

	Controller c;
	c.createSubsidizedConsumer( subsidizedID, "Sidorov", "Klochkivska 56" );

	c.useWater( subsidizedID, 1.48);
	c.useWater( subsidizedID, 2.34 );
	c.useWater( subsidizedID, 9000.0 );

	CHECK_EQUAL( c.getConsumerDebt( subsidizedID, WaterPrice ), 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_total_debt )
{
	int countedID = 8450, standardID = 6173, subsidizedID = 1460, nUsers = 2;

	double countedVolume = 5.4, subsidizedVolume = 6.1, standardVolume = 4.7;

	Controller c;
	c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" );
	c.createSubsidizedConsumer( subsidizedID, "Sidorov", "Klochkivska 56" );
	c.createStandardConsumer( standardID, "Petrov", "Sumska' 22", nUsers );

	c.useWater( countedID, countedVolume );
	c.useWater( subsidizedID, subsidizedVolume );
	c.useWater( standardID, standardVolume );

	double expectedTotalDebt
		=
			WaterPrice * countedVolume
		+	WaterPrice * StandardWaterConsumptionPerUser * nUsers
	;

	CHECK_EQUAL( c.getConsumerDebt( countedID, WaterPrice ), WaterPrice * countedVolume );
	CHECK_EQUAL(
			c.getConsumerDebt( standardID, WaterPrice )
		,	WaterPrice * StandardWaterConsumptionPerUser * nUsers
	);
	CHECK_EQUAL( c.getConsumerDebt( subsidizedID, WaterPrice ), 0 );
	
	CHECK_EQUAL( c.getTotalDebt( WaterPrice ), expectedTotalDebt );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_track_payment_counted_consumer )
{
	int countedID = 8450;
	double waterAmount = 4.2, payment = 24.50;

	Controller c;
	c.createCountedConsumer( countedID, "Ivanov", "Lenina 15" );

	c.useWater( countedID, waterAmount );
	c.useWater( countedID, waterAmount );

	double expectedDebt = WaterPrice * waterAmount * 2;

	CHECK_EQUAL( c.getConsumerDebt( countedID, WaterPrice ), expectedDebt );

	c.trackConsumerPayment( countedID, payment );

	CHECK_EQUAL( c.getConsumerDebt( countedID, WaterPrice ), ( expectedDebt - payment ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_track_payment_standard_consumer )
{
	int standardID = 8450, nUsers = 4;
	double waterAmount = 4.2, payment = 16.50;

	Controller c;
	c.createStandardConsumer( standardID, "Petrov", "Sumska' 22", nUsers );

	c.useWater( standardID, 52.1 );
	c.useWater( standardID, 14.2 );
	c.useWater( standardID, 2.1 );

	double expectedDebt = WaterPrice * StandardWaterConsumptionPerUser * nUsers;

	CHECK_EQUAL( c.getConsumerDebt( standardID, WaterPrice ), expectedDebt );

	c.trackConsumerPayment( standardID, payment );

	CHECK_EQUAL( c.getConsumerDebt( standardID, WaterPrice ), ( expectedDebt - payment ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_track_payment_standard_consumer_negative_payment )
{
	int standardID = 8450, nUsers = 4;
	double payment = -16.50;

	Controller c;
	c.createStandardConsumer( standardID, "Petrov", "Sumska' 22", nUsers );

	ASSERT_THROWS(
			c.trackConsumerPayment( standardID, payment )
		,	Messages::NonPositivePaymentAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_track_payment_standard_consumer_zero_payment )
{
	int standardID = 8450, nUsers = 4;
	double payment = 0.0;

	Controller c;
	c.createStandardConsumer( standardID, "Petrov", "Sumska' 22", nUsers );

	ASSERT_THROWS(
			c.trackConsumerPayment( standardID, payment )
		,	Messages::NonPositivePaymentAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_track_payment_subsidized_user )
{
	int subsidizedID = 2523;
	double waterAmount = 4.2, payment = 15.34;

	Controller c;
	c.createSubsidizedConsumer( subsidizedID, "Sidorov", "Klochkivska 56" );

	ASSERT_THROWS(
			c.trackConsumerPayment( subsidizedID, payment )
		,	Messages::SubsidizedConsumersDontPay
	);
}


/*****************************************************************************/
