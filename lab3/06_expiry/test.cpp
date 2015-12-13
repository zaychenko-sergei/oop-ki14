// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"
#include "utils.hpp"

#include "testslib.hpp"

/*****************************************************************************/

/*
	Expiry Testplan:
	Done	1) Consignment
	Done		1.1) One
	Done			1.1.1) With Null expiry policy
	Done			1.1.2) With Quick expiry policy
	Done			1.1.3) With Slow expiry policy
	Done		1.2) Several
	Done		1.3) With empty name
	Done		1.4) With duplicated name
	Done		1.5) With zero initial amount
	Done		1.6) With negative initial amount
	Done		1.7) With zero price
	Done		1.8) With negative price
	Done		1.9) With earlier date
	Done		1.10) With zero expires days
	Done			1.10.1) For Null policy
	Done			1.10.2) For Quick policy
	Done			1.10.3) For Slow policy
	Done		1.11) With negative expires policy
	Done			1.11.1) For Null policy
	Done			1.11.2) For Quick policy
	Done			1.11.3) For Slow policy
	Done		1.12) Obtain data by empty name
	Done		1.13) Obtain data by missing name
	Done	2) Expirations
	Done		2.1) Cannot set bad current date
	Done			2.1.1) Earliest
	Done			2.1.2) The same
	Done		2.2) All consignments are fresh
	Done		2.3) Obtain fresh cost by empty name
	Done		2.4) Obtain fresh cost by missing name
	Done		2.5) All consignments are expired
	Done		2.6) Obtain expired cost by empty name
	Done		2.7) Obtain expired cost by missing name
	Done		2.8) Fresh cost is zero for expired consignment
	Done		2.9) Expired cost is zero for fresh consignment
	Done		2.10) Slowly expiring consignment is contained in fresh cost
	Done	3) Sell
	Done		3.1) One action
	Done		3.2) With empty name
	Done		3.3) With missing name
	Done		3.4) With zero amount
	Done		3.5) With negative amount
	Done		3.6) With too big amount
	Done		3.7) For expired consignment
	Done		3.8) Different consignments
	Done		3.9) The same consignments several times
	Done		3.10) Consignment is deleted when amount is zero
	Done	4) Complex cases
	Done		4.1) Simple flow
*/

/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_1_1_consignment_one_with_null_expiry_policy )
{
	Controller c;
	Date date;
	c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Null );

	assert( c.getConsignmentAmount( "product" ) == 10.0 );
	assert( c.getConsignmentPrice( "product" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product" ) == ExpiryPolicyKind::Null );
	assert( c.isConsignmentExpired( "product" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_1_2_consignment_one_with_quick_expiry_policy )
{
	Controller c;
	Date date;
	c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Quick, 1 );

	assert( c.getConsignmentAmount( "product" ) == 10.0 );
	assert( c.getConsignmentPrice( "product" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_1_3_consignment_one_with_slow_expiry_policy )
{
	Controller c;
	Date date;
	c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Slow, 1 );

	assert( c.getConsignmentAmount( "product" ) == 10.0 );
	assert( c.getConsignmentPrice( "product" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_2_consignment_several )
{
	Controller c;
	Date date;
	c.createConsignment( "product #1", 10.1, date, 1.1, ExpiryPolicyKind::Null );
	c.createConsignment( "product #2", 18.0, date, 5.0, ExpiryPolicyKind::Null );
	c.createConsignment( "product #3", 2.9, date, 3.45, ExpiryPolicyKind::Slow, 20 );
	c.createConsignment( "product #4", 55.0, date, 8.17, ExpiryPolicyKind::Slow, 26 );
	c.createConsignment( "product #5", 55.5, date, 9.99, ExpiryPolicyKind::Quick, 13 );
	c.createConsignment( "product #6", 11.1, date, 0.1, ExpiryPolicyKind::Quick, 11 );

	assert( c.getConsignmentAmount( "product #1" ) == 10.1 );
	assert( c.getConsignmentPrice( "product #1" ) == 1.1 );
	assert( c.getConsignmentProductionDate( "product #1" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #1" ) == ExpiryPolicyKind::Null );
	assert( c.isConsignmentExpired( "product #1" ) == false );

	assert( c.getConsignmentAmount( "product #2" ) == 18.0 );
	assert( c.getConsignmentPrice( "product #2" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product #2" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #2" ) == ExpiryPolicyKind::Null );
	assert( c.isConsignmentExpired( "product #2" ) == false );

	assert( c.getConsignmentAmount( "product #3" ) == 2.9 );
	assert( c.getConsignmentPrice( "product #3" ) == 3.45 );
	assert( c.getConsignmentProductionDate( "product #3" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #3" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product #3" ) == false );

	assert( c.getConsignmentAmount( "product #4" ) == 55.0 );
	assert( c.getConsignmentPrice( "product #4" ) == 8.17 );
	assert( c.getConsignmentProductionDate( "product #4" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #4" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product #4" ) == false );

	assert( c.getConsignmentAmount( "product #5" ) == 55.5 );
	assert( c.getConsignmentPrice( "product #5" ) == 9.99 );
	assert( c.getConsignmentProductionDate( "product #5" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #5" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product #5" ) == false );

	assert( c.getConsignmentAmount( "product #6" ) == 11.1 );
	assert( c.getConsignmentPrice( "product #6" ) == 0.1 );
	assert( c.getConsignmentProductionDate( "product #6" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #6" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product #6" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_3_consignment_with_empty_name )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "", 10.0, date, 5.0, ExpiryPolicyKind::Slow, 1 );
		,	Messages::EmptyProductName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_4_consignment_with_duplicated_name )
{
	Controller c;
	Date date;
	c.createConsignment( "test", 7.8, date, 12.12, ExpiryPolicyKind::Quick, 2 );

	ASSERT_THROWS(
			c.createConsignment( "test", 10.0, date, 5.0, ExpiryPolicyKind::Slow, 1 );
		,	Messages::ProductNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_5_consignment_with_zero_initial_amount )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "fruit", 0.0, date, 5.0, ExpiryPolicyKind::Slow, 1 );
		,	Messages::NonPositiveAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_6_consignment_with_negative_initial_amount )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "fruit", -5.0, date, 5.0, ExpiryPolicyKind::Slow, 1 );
		,	Messages::NonPositiveAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_7_consignment_with_zero_price )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "fruit", 3.0, date, 0.0, ExpiryPolicyKind::Slow, 1 );
		,	Messages::NonPositivePrice
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_8_consignment_with_negative_price )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "fruit", 3.0, date, -5.0, ExpiryPolicyKind::Slow, 1 );
		,	Messages::NonPositivePrice
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_9_consignment_with_earlier_date )
{
	Controller c;

	Date date( 1993, 7, 19 );
	assert( date < Date() );

	c.createConsignment( "boy", 1.0, date, 5.0, ExpiryPolicyKind::Slow, 1'000'000 );

	assert( c.getConsignmentAmount( "boy" ) == 1.0 );
	assert( c.getConsignmentPrice( "boy" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "boy" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "boy" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "boy" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_10_1_consignment_with_zero_expires_days_for_null_policy )
{
	Controller c;
	Date date;
	c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Null, 0 );

	assert( c.getConsignmentAmount( "product" ) == 10.0 );
	assert( c.getConsignmentPrice( "product" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product" ) == ExpiryPolicyKind::Null );
	assert( c.isConsignmentExpired( "product" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_10_2_consignment_with_zero_expires_days_for_quick_policy )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Quick, 0 );
		,	Messages::NonPositiveExpiryDays
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_10_3_consignment_with_zero_expires_days_for_slow_policy )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Slow, 0 );
		,	Messages::NonPositiveExpiryDays
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_11_1_consignment_with_negative_expires_days_for_null_policy )
{
	Controller c;
	Date date;
	c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Null, -10 );

	assert( c.getConsignmentAmount( "product" ) == 10.0 );
	assert( c.getConsignmentPrice( "product" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product" ) == ExpiryPolicyKind::Null );
	assert( c.isConsignmentExpired( "product" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_11_2_consignment_with_negative_expires_days_for_quick_policy )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Quick, -10 );
		,	Messages::NonPositiveExpiryDays
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_11_3_consignment_with_negative_expires_days_for_slow_policy )
{
	Controller c;
	Date date;

	ASSERT_THROWS(
			c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Slow, -10 );
		,	Messages::NonPositiveExpiryDays
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_12_consignment_obtain_data_by_empty_name )
{
	Controller c;
	Date date;
	c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Null );

	ASSERT_THROWS(
			c.getConsignmentAmount( "" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.getConsignmentPrice( "" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.getConsignmentProductionDate( "" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.getConsignmentExpiryPolicyKind( "" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.isConsignmentExpired( "" );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_1_13_consignment_obtain_data_by_missing_name )
{
	Controller c;
	Date date;
	c.createConsignment( "product", 10.0, date, 5.0, ExpiryPolicyKind::Null );

	ASSERT_THROWS(
			c.getConsignmentAmount( "who" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.getConsignmentPrice( "who" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.getConsignmentProductionDate( "who" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.getConsignmentExpiryPolicyKind( "who" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.isConsignmentExpired( "who" );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_1_1_expirations_cannot_set_bad_current_date_earliest )
{
	Controller c;
	c.setCurrentDate( "2200/01/01" );

	ASSERT_THROWS(
			c.setCurrentDate( "2199/12/31" );
		,	Messages::ExpectLaterDate
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_1_2_expirations_cannot_set_bad_current_date_the_same )
{
	Controller c;
	c.setCurrentDate( "2200/01/01" );

	ASSERT_THROWS(
			c.setCurrentDate( "2200/01/01" );
		,	Messages::ExpectLaterDate
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_2_expirations_all_consignments_are_fresh )
{
	Controller c;
	Date date;
	c.createConsignment( "product #1", 10.1, date, 1.1, ExpiryPolicyKind::Null );
	c.createConsignment( "product #2", 18.0, date, 5.0, ExpiryPolicyKind::Null );
	c.createConsignment( "product #3", 2.9, date, 3.45, ExpiryPolicyKind::Slow, 20 );
	c.createConsignment( "product #4", 55.0, date, 8.17, ExpiryPolicyKind::Slow, 26 );
	c.createConsignment( "product #5", 55.5, date, 9.99, ExpiryPolicyKind::Quick, 13 );
	c.createConsignment( "product #6", 11.1, date, 0.1, ExpiryPolicyKind::Quick, 11 );

	assert( c.getConsignmentAmount( "product #1" ) == 10.1 );
	assert( c.getConsignmentPrice( "product #1" ) == 1.1 );
	assert( c.getConsignmentProductionDate( "product #1" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #1" ) == ExpiryPolicyKind::Null );
	assert( c.isConsignmentExpired( "product #1" ) == false );

	assert( c.getConsignmentAmount( "product #2" ) == 18.0 );
	assert( c.getConsignmentPrice( "product #2" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product #2" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #2" ) == ExpiryPolicyKind::Null );
	assert( c.isConsignmentExpired( "product #2" ) == false );

	assert( c.getConsignmentAmount( "product #3" ) == 2.9 );
	assert( c.getConsignmentPrice( "product #3" ) == 3.45 );
	assert( c.getConsignmentProductionDate( "product #3" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #3" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product #3" ) == false );

	assert( c.getConsignmentAmount( "product #4" ) == 55.0 );
	assert( c.getConsignmentPrice( "product #4" ) == 8.17 );
	assert( c.getConsignmentProductionDate( "product #4" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #4" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product #4" ) == false );

	assert( c.getConsignmentAmount( "product #5" ) == 55.5 );
	assert( c.getConsignmentPrice( "product #5" ) == 9.99 );
	assert( c.getConsignmentProductionDate( "product #5" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #5" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product #5" ) == false );

	assert( c.getConsignmentAmount( "product #6" ) == 11.1 );
	assert( c.getConsignmentPrice( "product #6" ) == 0.1 );
	assert( c.getConsignmentProductionDate( "product #6" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #6" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product #6" ) == false );

	assert( equalDoubles( c.getConsignmentFreshCost( "product #1" ), 11.11 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #2" ), 90.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #3" ), 10.005 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #4" ), 449.35 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #5" ), 554.445 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #6" ), 1.11 ) );
	assert( equalDoubles( c.getTotalFreshCost(), 1116.02 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_3_expirations_obtain_fresh_cost_by_empty_name )
{
	Controller c;
	Date date;
	c.createConsignment( "rubby", 10.1, date, 1.1, ExpiryPolicyKind::Null );

	ASSERT_THROWS(
			c.getConsignmentFreshCost( "" );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_4_expirations_obtain_fresh_cost_by_missing_name )
{
	Controller c;
	Date date;
	c.createConsignment( "rubby", 10.1, date, 1.1, ExpiryPolicyKind::Null );

	ASSERT_THROWS(
			c.getConsignmentFreshCost( "bubby" );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_5_expirations_all_consignments_are_expired )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "product #1", 10.1, date, 1.1, ExpiryPolicyKind::Quick, 1 );
	c.createConsignment( "product #2", 18.0, date, 5.0, ExpiryPolicyKind::Slow, 1 );
	c.createConsignment( "product #3", 2.9, date, 3.45, ExpiryPolicyKind::Slow, 20 );
	c.createConsignment( "product #4", 55.0, date, 8.17, ExpiryPolicyKind::Slow, 26 );
	c.createConsignment( "product #5", 55.5, date, 9.99, ExpiryPolicyKind::Quick, 13 );
	c.createConsignment( "product #6", 11.1, date, 0.1, ExpiryPolicyKind::Quick, 11 );

	c.setCurrentDate( "2201/01/01" );

	assert( c.getConsignmentAmount( "product #1" ) == 10.1 );
	assert( c.getConsignmentPrice( "product #1" ) == 1.1 );
	assert( c.getConsignmentProductionDate( "product #1" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #1" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product #1" ) == true );

	assert( c.getConsignmentAmount( "product #2" ) == 18.0 );
	assert( c.getConsignmentPrice( "product #2" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "product #2" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #2" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product #2" ) == true );

	assert( c.getConsignmentAmount( "product #3" ) == 2.9 );
	assert( c.getConsignmentPrice( "product #3" ) == 3.45 );
	assert( c.getConsignmentProductionDate( "product #3" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #3" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product #3" ) == true );

	assert( c.getConsignmentAmount( "product #4" ) == 55.0 );
	assert( c.getConsignmentPrice( "product #4" ) == 8.17 );
	assert( c.getConsignmentProductionDate( "product #4" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #4" ) == ExpiryPolicyKind::Slow );
	assert( c.isConsignmentExpired( "product #4" ) == true );

	assert( c.getConsignmentAmount( "product #5" ) == 55.5 );
	assert( c.getConsignmentPrice( "product #5" ) == 9.99 );
	assert( c.getConsignmentProductionDate( "product #5" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #5" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product #5" ) == true );

	assert( c.getConsignmentAmount( "product #6" ) == 11.1 );
	assert( c.getConsignmentPrice( "product #6" ) == 0.1 );
	assert( c.getConsignmentProductionDate( "product #6" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "product #6" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "product #6" ) == true );

	assert( equalDoubles( c.getConsignmentExpiredCost( "product #1" ), 11.11 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #2" ), 90.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #3" ), 10.005 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #4" ), 449.35 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #5" ), 554.445 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #6" ), 1.11 ) );
	assert( equalDoubles( c.getTotalExpiredCost(), 1116.02 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_6_expirations_obtain_expired_cost_by_empty_name )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "ioly", 10.1, date, 1.1, ExpiryPolicyKind::Quick, 1 );

	c.setCurrentDate( "2201/01/01" );

	ASSERT_THROWS(
			c.getConsignmentFreshCost( "" );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_7_expirations_obtain_expired_cost_by_missing_name )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "ioly", 10.1, date, 1.1, ExpiryPolicyKind::Quick, 1 );

	c.setCurrentDate( "2201/01/01" );

	ASSERT_THROWS(
			c.getConsignmentFreshCost( "bubby" );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_8_expirations_fresh_cost_is_zero_for_expired_consignment )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "product #1", 10.0, date, 6.0, ExpiryPolicyKind::Quick, 5 );
	c.createConsignment( "product #2", 20.0, date, 5.0, ExpiryPolicyKind::Quick, 10 );
	c.createConsignment( "product #3", 30.0, date, 4.0, ExpiryPolicyKind::Quick, 15 );
	c.createConsignment( "product #4", 40.0, date, 3.0, ExpiryPolicyKind::Slow, 5 );
	c.createConsignment( "product #5", 50.0, date, 2.0, ExpiryPolicyKind::Slow, 10 );
	c.createConsignment( "product #6", 60.0, date, 1.0, ExpiryPolicyKind::Slow, 15 );

	c.setCurrentDate( "2201/01/01" );

	assert( equalDoubles( c.getConsignmentFreshCost( "product #1" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #2" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #3" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #4" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #5" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #6" ), 0.0 ) );
	assert( equalDoubles( c.getTotalFreshCost(), 0.0 ) );

	assert( equalDoubles( c.getConsignmentExpiredCost( "product #1" ), 60.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #2" ), 100.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #3" ), 120.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #4" ), 120.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #5" ), 100.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #6" ), 60.0 ) );
	assert( equalDoubles( c.getTotalExpiredCost(), 560.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_9_expirations_expired_cost_is_zero_for_fresh_consignment )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "product #1", 10.0, date, 6.0, ExpiryPolicyKind::Quick, 5 );
	c.createConsignment( "product #2", 20.0, date, 5.0, ExpiryPolicyKind::Quick, 10 );
	c.createConsignment( "product #3", 30.0, date, 4.0, ExpiryPolicyKind::Quick, 15 );
	c.createConsignment( "product #4", 40.0, date, 3.0, ExpiryPolicyKind::Slow, 5 );
	c.createConsignment( "product #5", 50.0, date, 2.0, ExpiryPolicyKind::Slow, 10 );
	c.createConsignment( "product #6", 60.0, date, 1.0, ExpiryPolicyKind::Slow, 15 );

	assert( equalDoubles( c.getConsignmentFreshCost( "product #1" ), 60.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #2" ), 100.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #3" ), 120.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #4" ), 120.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #5" ), 100.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #6" ), 60.0 ) );
	assert( equalDoubles( c.getTotalFreshCost(), 560.0 ) );

	assert( equalDoubles( c.getConsignmentExpiredCost( "product #1" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #2" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #3" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #4" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #5" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #6" ), 0.0 ) );
	assert( equalDoubles( c.getTotalExpiredCost(), 0.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_2_10_expirations_slowly_expiring_consignment_is_not_contained_in_fresh_const )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "product #1", 10.0, date, 6.0, ExpiryPolicyKind::Quick, 5 );
	c.createConsignment( "product #2", 20.0, date, 5.0, ExpiryPolicyKind::Quick, 10 );
	c.createConsignment( "product #3", 30.0, date, 4.0, ExpiryPolicyKind::Quick, 15 );
	c.createConsignment( "product #4", 40.0, date, 3.0, ExpiryPolicyKind::Slow, 5 );
	c.createConsignment( "product #5", 50.0, date, 2.0, ExpiryPolicyKind::Slow, 10 );
	c.createConsignment( "product #6", 60.0, date, 1.0, ExpiryPolicyKind::Slow, 15 );

	c.setCurrentDate( "2200/01/10" );

	assert( c.isConsignmentExpired( "product #1" ) == true );
	assert( c.isConsignmentExpired( "product #2" ) == false );
	assert( c.isConsignmentExpired( "product #3" ) == false );
	assert( c.isConsignmentExpired( "product #4" ) == true );
	assert( c.isConsignmentExpired( "product #5" ) == false );
	assert( c.isConsignmentExpired( "product #6" ) == false );

	assert( equalDoubles( c.getConsignmentFreshCost( "product #1" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #2" ), 100.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #3" ), 120.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #4" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentFreshCost( "product #5" ), 10.0 ) ); // 9 days are passed: discount 90%
	assert( equalDoubles( c.getConsignmentFreshCost( "product #6" ), 24.0 ) ); // 9 days are passed: discount 60%
	assert( equalDoubles( c.getTotalFreshCost(), 254.0 ) );

	assert( equalDoubles( c.getConsignmentExpiredCost( "product #1" ), 60.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #2" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #3" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #4" ), 120.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #5" ), 0.0 ) );
	assert( equalDoubles( c.getConsignmentExpiredCost( "product #6" ), 0.0 ) );
	assert( equalDoubles( c.getTotalExpiredCost(), 180.0 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_1_sell_one_action )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "frog", 50.0, date, 5.0, ExpiryPolicyKind::Quick, 5 );

	assert( c.getConsignmentAmount( "frog" ) == 50.0 );
	assert( c.getConsignmentPrice( "frog" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "frog" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "frog" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "frog" ) == false );

	c.sell( "frog", 24.5 );

	assert( c.getConsignmentAmount( "frog" ) == 25.5 );
	assert( c.getConsignmentPrice( "frog" ) == 5.0 );
	assert( c.getConsignmentProductionDate( "frog" ) == date );
	assert( c.getConsignmentExpiryPolicyKind( "frog" ) == ExpiryPolicyKind::Quick );
	assert( c.isConsignmentExpired( "frog" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_2_sell_with_empty_name )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "frog", 50.0, date, 5.0, ExpiryPolicyKind::Quick, 5 );

	ASSERT_THROWS(
			c.sell( "", 24.5 );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_3_sell_with_missing_name )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "frog", 50.0, date, 5.0, ExpiryPolicyKind::Quick, 5 );

	ASSERT_THROWS(
			c.sell( "bob", 24.5 );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_4_sell_with_zero_amount )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "frog", 50.0, date, 5.0, ExpiryPolicyKind::Quick, 5 );

	ASSERT_THROWS(
			c.sell( "frog", 0.0 );
		,	Messages::NonPositiveAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_5_sell_with_negative_amount )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "frog", 50.0, date, 5.0, ExpiryPolicyKind::Quick, 5 );

	ASSERT_THROWS(
			c.sell( "frog", -12.0 );
		,	Messages::NonPositiveAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_6_sell_with_too_big_amount )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "frog", 50.0, date, 5.0, ExpiryPolicyKind::Quick, 5 );

	ASSERT_THROWS(
			c.sell( "frog", 500.0 );
		,	Messages::SellingOverAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_7_sell_for_expired_consignment )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	Date date( 2200, 1, 1 );
	c.createConsignment( "frog", 50.0, date, 5.0, ExpiryPolicyKind::Quick, 5 );

	c.setCurrentDate( "2200/01/10" );

	ASSERT_THROWS(
			c.sell( "frog", 1.0 );
		,	Messages::SellingExpired
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_8_sell_different_consignments )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	c.createConsignment( "frog", 50.0, Date( 2200, 1, 1 ), 2.0, ExpiryPolicyKind::Quick, 2 );
	c.createConsignment( "marly", 12.0, Date( 2200, 1, 2 ), 3.0, ExpiryPolicyKind::Quick, 3 );
	c.createConsignment( "bob", 87.1, Date( 2200, 1, 3 ), 4.0, ExpiryPolicyKind::Quick, 4 );

	c.sell( "frog", 7.0 );
	c.sell( "marly", 11.0 );
	c.sell( "bob", 48.0 );

	assert( equalDoubles( c.getConsignmentAmount( "frog" ), 43.0 ) );
	assert( equalDoubles( c.getConsignmentAmount( "marly" ), 1.0 ) );
	assert( equalDoubles( c.getConsignmentAmount( "bob" ), 39.1 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_9_sell_the_same_consignment_several_times )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	c.createConsignment( "frog", 50.0, Date( 2200, 1, 1 ), 2.0, ExpiryPolicyKind::Quick, 2 );
	c.createConsignment( "marly", 12.0, Date( 2200, 1, 2 ), 3.0, ExpiryPolicyKind::Quick, 3 );
	c.createConsignment( "bob", 87.1, Date( 2200, 1, 3 ), 4.0, ExpiryPolicyKind::Quick, 4 );

	c.sell( "frog", 7.0 );
	c.sell( "marly", 11.0 );
	c.sell( "bob", 48.0 );
	c.sell( "frog", 10.0 );
	c.sell( "bob", 9.0 );

	assert( equalDoubles( c.getConsignmentAmount( "frog" ), 33.0 ) );
	assert( equalDoubles( c.getConsignmentAmount( "marly" ), 1.0 ) );
	assert( equalDoubles( c.getConsignmentAmount( "bob" ), 30.1 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_3_10_sell_consignment_is_deleted_when_amount_is_zero )
{
	Controller c;

	c.setCurrentDate( "2200/01/01" );

	c.createConsignment( "frog", 50.0, Date( 2200, 1, 1 ), 2.0, ExpiryPolicyKind::Quick, 2 );
	c.createConsignment( "marly", 12.0, Date( 2200, 1, 2 ), 3.0, ExpiryPolicyKind::Quick, 3 );
	c.createConsignment( "bob", 87.1, Date( 2200, 1, 3 ), 4.0, ExpiryPolicyKind::Quick, 4 );

	c.sell( "frog", 7.0 );
	c.sell( "marly", 11.0 );
	c.sell( "bob", 48.0 );
	c.sell( "frog", 10.0 );
	c.sell( "bob", 9.0 );
	c.sell( "marly", 1.0 );

	assert( equalDoubles( c.getConsignmentAmount( "frog" ), 33.0 ) );
	assert( equalDoubles( c.getConsignmentAmount( "bob" ), 30.1 ) );
	ASSERT_THROWS(
			c.getConsignmentAmount( "marly" );
		,	Messages::ProductNotFound
	);

	c.sell( "frog", 33.0 );
	c.sell( "bob", 30.1 );

	ASSERT_THROWS(
			c.getConsignmentAmount( "frog" );
		,	Messages::ProductNotFound
	);
	ASSERT_THROWS(
			c.getConsignmentAmount( "bob" );
		,	Messages::ProductNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( expiry_4_1_complex_cases_simple_flow )
{
	Controller c;

	c.setCurrentDate( "2215/11/01" );

	std::string cheese = "Cheese";
	std::string vodka = "Vodka";
	std::string salad = "Green Salad";

	c.createConsignment( cheese, 20.0, "2215/11/01", 50.0, ExpiryPolicyKind::Slow, 100 );
	c.createConsignment( vodka, 50.0, "2215/06/01", 35.0, ExpiryPolicyKind::Null );
	c.createConsignment( salad, 10.0, "2215/11/01", 5.0, ExpiryPolicyKind::Quick, 2 );

	assert( c.getTotalFreshCost() == 20.0 * 50.0 + 50.0 * 35.0 + 10.0 * 5.0 );
	assert( c.getConsignmentFreshCost( cheese ) == 20.0 * 50.0 );
	assert( c.getConsignmentFreshCost( vodka )  == 50.0 * 35.0 );
	assert( c.getConsignmentFreshCost( salad )  == 10.0 *  5.0 );
	assert( c.getTotalExpiredCost() == 0.0 );

	assert( c.getConsignmentAmount( cheese ) == 20.0 );
	assert( c.getConsignmentAmount( vodka )  == 50.0 );
	assert( c.getConsignmentAmount( salad )  == 10.0 );

	c.sell( cheese, 0.5 );
	c.sell( salad, 0.25 );

	assert( c.getConsignmentAmount( cheese ) == 19.5  );
	assert( c.getConsignmentAmount( vodka )  == 50.0  );
	assert( c.getConsignmentAmount( salad )  ==  9.75 );

	assert( ! c.isConsignmentExpired( salad ) );
	assert( ! c.isConsignmentExpired( cheese ) );
	assert( ! c.isConsignmentExpired( vodka ) );

	assert( c.getTotalFreshCost() == 19.5 * 50.0 + 50.0 * 35.0 + 9.75 * 5.0 );
	assert( c.getConsignmentFreshCost( cheese ) == 19.50 * 50.0 );
	assert( c.getConsignmentFreshCost( vodka )  == 50.00 * 35.0 );
	assert( c.getConsignmentFreshCost( salad )  ==  9.75 *  5.0 );
	assert( c.getTotalExpiredCost() == 0.0 );

	// Salad should expire
	c.setCurrentDate( "2215/11/06" );
	
	assert( c.isConsignmentExpired( salad ) );
	assert( ! c.isConsignmentExpired( cheese ) );
	assert( ! c.isConsignmentExpired( vodka ) );

	assert( c.getTotalExpiredCost() == 9.75 * 5.0 );
	assert( c.getConsignmentExpiredCost( salad ) == 9.75 * 5.0 );
	assert( c.getTotalFreshCost() == 19.5 * 50.0 * 0.95 + 50.0 * 35.0 ); // cheese * 0.95 is due to 5 days of 100
	assert( c.getConsignmentFreshCost( cheese ) == 19.50 * 50.0 * 0.95 );
	assert( c.getConsignmentFreshCost( vodka )  == 50.00 * 35.0 );

	// Cheese should expire
	c.setCurrentDate( "2216/05/01" );
	assert( c.getTotalExpiredCost() == 9.75 * 5.0 + 19.5 * 50.0 );
	assert( c.getConsignmentExpiredCost( salad ) == 9.75 * 5.0 );
	assert( c.getConsignmentExpiredCost( cheese ) == 19.5 * 50.0 );
	assert( c.getTotalFreshCost() == 50.0 * 35.0 );
	assert( c.getConsignmentFreshCost( vodka )  == 50.00 * 35.0 );
}


/*****************************************************************************/
