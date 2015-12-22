// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"
#include "energyprice.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_person_consumer )
{
	Controller c;

	int personConsumerID = 1984;

	c.createPersonConsumer( personConsumerID );

	assert( c.getConsumerDebt( personConsumerID ) == 0 );
	assert( c.isConsumerBlocked( personConsumerID ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_organization_consumer )
{
	Controller c;

	int organizationConsumerID = 1337;

	c.createOrganizationConsumer( organizationConsumerID );

	assert( c.getConsumerDebt( organizationConsumerID ) == 0 );
	assert( c.isConsumerBlocked( organizationConsumerID ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_system_consumer )
{
	Controller c;

	int organizationConsumerID = 86420341;

	c.createSystemConsumer( organizationConsumerID );

	assert( c.getConsumerDebt( organizationConsumerID ) == 0 );
	assert( c.isConsumerBlocked( organizationConsumerID ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_person_consumer_with_negative_id )
{
	Controller c;

	int personConsumerID = -1984;

	
	ASSERT_THROWS(
			c.createPersonConsumer( personConsumerID )
		,	Messages::NegativeConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_organization_consumer_with_negative_id )
{
	Controller c;

	int organizationConsumerID = -1337;

	ASSERT_THROWS(
			c.createOrganizationConsumer( organizationConsumerID )
		,	Messages::NegativeConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_system_consumer_with_negative_id )
{
	Controller c;

	int systemConsumerID = -11;

	ASSERT_THROWS(
			c.createSystemConsumer( systemConsumerID )
		,	Messages::NegativeConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_person_consumer_with_zero_id )
{
	Controller c;

	int personConsumerID = 0;
	
	c.createPersonConsumer( personConsumerID );

	assert( c.getConsumerDebt( personConsumerID ) == 0 );
	assert( c.isConsumerBlocked( personConsumerID ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_person_consumers_with_same_id )
{
	Controller c;

	int personConsumerID = 1984;
	
	c.createPersonConsumer( personConsumerID );

	ASSERT_THROWS(
			c.createPersonConsumer( personConsumerID )
		,	Messages::NonUniqueConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_different_consumers_kind_with_same_id )
{
	Controller c;

	int consumerID = 1984;
	int systemID = 45;

	c.createPersonConsumer( consumerID );
	c.createSystemConsumer( systemID );

	ASSERT_THROWS(
			c.createOrganizationConsumer( consumerID )
		,	Messages::NonUniqueConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_person_consumer_consuming_lower_than_threshold )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 150 );

	double consumerDebt = c.getConsumerDebt( consumerID );

	assert( consumerDebt == 150 * EnergyPrice_PersonalSmall );
	assert( consumerDebt == c.getTotalDebt() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_person_consumer_consuming_higher_than_threshold )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 250 );

	double consumerDebt = c.getConsumerDebt( consumerID );

	assert( consumerDebt == ( 200 * EnergyPrice_PersonalSmall + 50 * EnergyPrice_PersonalLarge ) );
	assert( consumerDebt == c.getTotalDebt() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_person_consumer_consume_in_few_stages )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 250 );
	c.consume( consumerID, 250 );

	double consumerDebt = c.getConsumerDebt( consumerID );

	assert( consumerDebt == ( 200 * EnergyPrice_PersonalSmall + 300 * EnergyPrice_PersonalLarge ) );
	assert( consumerDebt == c.getTotalDebt() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_consume_with_wrong_id )
{
	Controller c;

	int consumerID = 1984;

	c.createOrganizationConsumer( consumerID );

	ASSERT_THROWS(
			c.consume( consumerID + 1, 250 )
		,	Messages::UnknownConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_consume_with_negative_id )
{
	Controller c;

	int consumerID = 1984;

	c.createOrganizationConsumer( consumerID );

	ASSERT_THROWS(
			c.consume( -consumerID, 250 )
		,	Messages::UnknownConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_debt_with_wrong_id )
{
	Controller c;

	int consumerID = 1984;

	c.createOrganizationConsumer( consumerID );

	c.consume( consumerID, 250 );

	ASSERT_THROWS(
			c.getConsumerDebt( consumerID + 1 )
		,	Messages::UnknownConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_debt_from_multiple_consumers )
{
	Controller c;

	int personID1 = 1984;
	int personID2 = 1985;
	int organizationID1 = 4512;
	int organizationID2 = 4513;
	int systemID1 = 1337;
	int systemID2 = 1338;

	c.createPersonConsumer( personID1 );
	c.createPersonConsumer( personID2 );

	c.createOrganizationConsumer( organizationID1 );
	c.createOrganizationConsumer( organizationID2 );

	c.createSystemConsumer( systemID1 );
	c.createSystemConsumer( systemID2 );

	c.consume( personID1, 100 );
	c.consume( personID2, 600 );
	c.consume( organizationID1, 2500 );
	c.consume( organizationID2, 55000 );
	c.consume( systemID1, 350000 );
	c.consume( systemID2, 1000000 );

	double totalDebt
		=	EnergyPrice_PersonalSmall * 100
		+	EnergyPrice_PersonalSmall * 200 + EnergyPrice_PersonalLarge * 400
		+	EnergyPrice_Corporate * 2500
		+	EnergyPrice_Corporate * 55000
	;

	assert( c.getConsumerDebt( personID1 ) == EnergyPrice_PersonalSmall * 100 );
	assert(
			c.getConsumerDebt( personID2 )
		==	EnergyPrice_PersonalSmall * 200 + EnergyPrice_PersonalLarge * 400
	);
	assert( c.getConsumerDebt( organizationID1 ) == EnergyPrice_Corporate * 2500 );
	assert( c.getConsumerDebt( organizationID2 ) == EnergyPrice_Corporate * 55000 );
	assert( c.getConsumerDebt( systemID1 ) == 0.0 );
	assert( c.getConsumerDebt( systemID2 ) == 0.0 );

	assert( c.getTotalDebt() == totalDebt );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_block_absence_for_person_consumer )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 2500000 );

	assert( c.isConsumerBlocked( consumerID ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_blocking_with_wrong_id )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 2500000 );

	ASSERT_THROWS(
			c.isConsumerBlocked( consumerID + 1 ) 
		,	Messages::UnknownConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_organization_block )
{
	Controller c;

	int consumerID = 1984;

	c.createOrganizationConsumer( consumerID );

	c.consume( consumerID, 2500 );

	assert( c.isConsumerBlocked( consumerID ) == false );

	c.consume( consumerID, 47500 );
	
	assert( c.isConsumerBlocked( consumerID ) == true );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_wrong_id_block )
{
	Controller c;

	int consumerID = 1984;

	c.createOrganizationConsumer( consumerID );

	c.consume( consumerID, 2500 );

	ASSERT_THROWS(
			c.isConsumerBlocked( consumerID + 1 )
		,	Messages::UnknownConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_pay_for_person_consumer )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 2500 );

	c.trackConsumerPayment( consumerID, 450.0 );

	assert(
			c.getConsumerDebt( consumerID )
		==	200 * EnergyPrice_PersonalSmall + 2300 * EnergyPrice_PersonalLarge - 450.0
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_pay_for_person_consumer_negative_amount )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 2500 );

	ASSERT_THROWS(
			c.trackConsumerPayment( consumerID, -450.0 )
		,	Messages::NonPositivePaymentAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_pay_for_person_consumer_wrong_id )
{
	Controller c;

	int consumerID = 1984;

	c.createPersonConsumer( consumerID );

	c.consume( consumerID, 2500 );

	ASSERT_THROWS(
			c.trackConsumerPayment( consumerID + 1, 450.0 )
		,	Messages::UnknownConsumerID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_pay_for_the_debts_in_multiple_stages_with_organization_unlock )
{
	Controller c;

	int consumerID = 1984;

	c.createOrganizationConsumer( consumerID );

	assert( c.isConsumerBlocked( consumerID ) == false );

	c.consume( consumerID, 60000 );

	assert( c.isConsumerBlocked( consumerID ) == true );

	c.trackConsumerPayment( consumerID, 10000 * EnergyPrice_Corporate );

	assert( c.isConsumerBlocked( consumerID ) == true );

	c.trackConsumerPayment( consumerID, 1 * EnergyPrice_Corporate );

	assert( c.isConsumerBlocked( consumerID ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_pay_for_system_consumer )
{
	Controller c;

	int consumerID = 1984;

	c.createSystemConsumer( consumerID );

	c.consume( consumerID, 156 );

	ASSERT_THROWS(
			c.trackConsumerPayment( consumerID, 10000 * EnergyPrice_Corporate )
		,	Messages::SystemConsumersDontPay
	);
}


/*****************************************************************************/
