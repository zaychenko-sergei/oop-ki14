// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "datetime.hpp"
#include "messages.hpp"
#include "utils.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_1_add_contact_one )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_2_add_contact_several )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );
	c.addContact( "Petr Petrov", "5555" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_3_with_empty_full_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addContact( "", "101" );
		,	Messages::EmptyFullName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_4_with_empty_phone_number )
{
	Controller c;

	ASSERT_THROWS(
			c.addContact( "Ivan Ivanov", "" );
		,	Messages::EmptyPhoneNumber
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_5_with_the_same_full_name )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );

	ASSERT_THROWS(
			c.addContact( "Ivan Ivanov", "202" );
		,	Messages::DuplicateContact
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_6_with_the_same_phone_number )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );

	ASSERT_THROWS(
			c.addContact( "Petr Petrov", "101" );
		,	Messages::DuplicateContact
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_7_obtain_full_name_by_phone_number )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );

	assert( c.getFullName( "101" ) == "Ivan Ivanov" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_8_obtain_full_name_by_empty_phone_number )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );

	ASSERT_THROWS(
			c.getFullName( "" )
		,	Messages::EmptyPhoneNumber
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_1_9_obtain_full_name_by_unregistered_phone_number )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );

	ASSERT_THROWS(
			c.getFullName( "202" )
		,	Messages::ContactCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_2_1_add_call_one )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );

	DateTime callTime;
	c.addCall( "101", CallType::Incoming, callTime, 100 );

	assert( c.getCallsCount() == 1 );
	assert( c.getContactName( 0 ) == "Ivan Ivanov" );
	assert( c.getPhoneNumber( 0 ) == "101" );
	assert( c.getCallType( 0 ) == CallType::Incoming );
	assert( c.getCallTime( 0 ) == callTime );
	assert( c.getCallDuration( 0 ) == 100 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_2_2_add_call_several )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );
	c.addContact( "Vitalka", "550055" );

	DateTime callTime1( 2010, 12, 31, 23, 59, 59 );
	DateTime callTime2( 1993, 07, 19, 11, 3, 27 );
	c.addCall( "101", CallType::Outgoing, callTime1, 57 );
	c.addCall( "550055", CallType::Incoming, callTime2, 2090 );

	assert( c.getCallsCount() == 2 );

	assert( c.getContactName( 0 ) == "Ivan Ivanov" );
	assert( c.getPhoneNumber( 0 ) == "101" );
	assert( c.getCallType( 0 ) == CallType::Outgoing );
	assert( c.getCallTime( 0 ) == callTime1 );
	assert( c.getCallDuration( 0 ) == 57 );

	assert( c.getContactName( 1 ) == "Vitalka" );
	assert( c.getPhoneNumber( 1 ) == "550055" );
	assert( c.getCallType( 1 ) == CallType::Incoming );
	assert( c.getCallTime( 1 ) == callTime2 );
	assert( c.getCallDuration( 1 ) == 2090 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_2_3_add_with_empty_phone_number )
{
	Controller c;
	c.addContact( "Ivan Ivanov", "101" );

	DateTime callTime;

	ASSERT_THROWS(
			c.addCall( "", CallType::Incoming, callTime, 100 )
		,	Messages::EmptyPhoneNumber
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_2_4_add_with_unregistered_phone_number )
{
	Controller c;
	DateTime callTime;
	c.addCall( "101", CallType::Incoming, callTime, 567 );

	assert( c.getCallsCount() == 1 );
	assert( c.getContactName( 0 ) == "" );
	assert( c.getPhoneNumber( 0 ) == "101" );
	assert( c.getCallType( 0 ) == CallType::Incoming );
	assert( c.getCallTime( 0 ) == callTime );
	assert( c.getCallDuration( 0 ) == 567 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_2_5_add_with_bad_call_time )
{
	Controller c;
	DateTime callTime( 2212, 12, 12, 12, 12, 12 );

	ASSERT_THROWS(
			c.addCall( "101", CallType::Outgoing, callTime, 400 )
		,	Messages::InvalidCallTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_2_6_add_with_bad_call_duration )
{
	Controller c;
	DateTime callTime;

	ASSERT_THROWS(
			c.addCall( "101", CallType::Outgoing, callTime, -98 )
		,	Messages::InvalidCallDuration
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_2_7_add_with_equal_parameters )
{
	Controller c;
	DateTime callTime;
	c.addCall( "101", CallType::Incoming, callTime, 33 );
	c.addCall( "101", CallType::Incoming, callTime, 33 );

	assert( c.getCallsCount() == 2 );

	assert( c.getContactName( 0 ) == "" );
	assert( c.getPhoneNumber( 0 ) == "101" );
	assert( c.getCallType( 0 ) == CallType::Incoming );
	assert( c.getCallTime( 0 ) == callTime );
	assert( c.getCallDuration( 0 ) == 33 );

	assert( c.getContactName( 1 ) == "" );
	assert( c.getPhoneNumber( 1 ) == "101" );
	assert( c.getCallType( 1 ) == CallType::Incoming );
	assert( c.getCallTime( 1 ) == callTime );
	assert( c.getCallDuration( 1 ) == 33 );
}


/*****************************************************************************/


DateTime generateTime( int _hours, int _minutes, int _seconds )
{
	return DateTime(
			1993
		,	7
		,	19
		,	_hours
		,	_minutes
		,	_seconds
	);
}


/*****************************************************************************/


void generateModel( Controller & _c )
{
	_c.addContact( "Ivan Ivanov", "101" );
	_c.addContact( "Petr Smirnov", "332" );

	_c.addCall( "101", CallType::Incoming, generateTime( 07, 0, 0 ), 10 );
	_c.addCall( "877", CallType::Incoming, generateTime( 07, 30, 27 ), 50 );
	_c.addCall( "877", CallType::Outgoing, generateTime( 9, 0, 0 ), 34 );
	_c.addCall( "101", CallType::Outgoing, generateTime( 10, 27, 0 ), 32 );
	_c.addCall( "332", CallType::Incoming, generateTime( 13, 27, 0 ), 78 );
	_c.addCall( "332", CallType::Incoming, generateTime( 16, 21, 0 ), 10 );
	_c.addCall( "101", CallType::Incoming, generateTime( 16, 22, 0 ), 22 );
	_c.addCall( "567", CallType::Outgoing, generateTime( 16, 31, 0 ), 90 );
	_c.addCall( "101", CallType::Outgoing, generateTime( 16, 31, 0 ), 91 );
	_c.addCall( "332", CallType::Outgoing, generateTime( 16, 35, 0 ), 46 );
	_c.addCall( "877", CallType::Outgoing, generateTime( 17, 0, 0 ), 44 );
	_c.addCall( "332", CallType::Incoming, generateTime( 18, 59, 0 ), 87 );
	_c.addCall( "877", CallType::Outgoing, generateTime( 20, 0, 0 ), 44 );

	assert( _c.getCallsCount() == 13 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_3_1_average_business_time_calls_duration )
{
	Controller c;
	generateModel( c );

	// NOTE: Only YYYY/MM/DD information is important
	DateTime dateTime = generateTime( 0, 0, 0 );

	assert( equalDoubles( c.getAverageBusinessTimeCallsDuration( dateTime ), 49.6666 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_3_2_unregistered_contacts_from_calls )
{
	Controller c;
	generateModel( c );

	std::vector< std::string > expectation;
	expectation.push_back( "877" );
	expectation.push_back( "567" );

	assert( c.getUnregisteredContactsFromCalls() == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_3_3_most_frequent_incoming_contact )
{
	Controller c;
	generateModel( c );

	assert( c.getMostFrequentIncomingContact() == "Petr Smirnov" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( calls_3_4_longest_outgoing_contact )
{
	Controller c;
	generateModel( c );

	assert( c.getLongestOutgoingContact() == "Ivan Ivanov" );
}


/*****************************************************************************/
