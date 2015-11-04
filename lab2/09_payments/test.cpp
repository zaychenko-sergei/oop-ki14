// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "datetime.hpp"
#include "messages.hpp"

#include "testslib.hpp"

#include <sstream>
#include <ctime>

/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_1_organization_one )
{
	Controller c;
	c.addOrganization( "exception", "00000001", 5569 );

	assert( c.getRegistrationNumber( "exception" ) == "00000001" );
	assert( c.getBalance( "exception" ) == 5569 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_2_organization_several )
{
	Controller c;
	c.addOrganization( "whiskas", "00000003", 18 );
	c.addOrganization( "hello-kitty", "00000055", 79 );

	assert( c.getRegistrationNumber( "whiskas" ) == "00000003" );
	assert( c.getBalance( "whiskas" ) == 18 );
	assert( c.getRegistrationNumber( "hello-kitty" ) == "00000055" );
	assert( c.getBalance( "hello-kitty" ) == 79 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_3_organization_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addOrganization( "", "00000055", 79 );
		,	Messages::EmptyOrganizationName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_4_organization_with_empty_registration_number )
{
	Controller c;

	ASSERT_THROWS(
			c.addOrganization( "whiskas", "", 79 );
		,	Messages::InvalidRegistrationNumberFormat
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_5_organization_with_duplicate_name )
{
	Controller c;
	c.addOrganization( "test", "00000000", 18 );

	ASSERT_THROWS(
			c.addOrganization( "test", "11111111", 43 );
		,	Messages::DuplicateOrganization
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_6_organization_with_duplicate_registration_number )
{
	Controller c;
	c.addOrganization( "test #1", "00000000", 18 );

	ASSERT_THROWS(
			c.addOrganization( "test #2", "00000000", 43 );
		,	Messages::DuplicateRegistrationNumber
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_7_organization_with_bad_registration_number )
{
	Controller c;

	ASSERT_THROWS(
			c.addOrganization( "test", "0000000", 18 );
		,	Messages::InvalidRegistrationNumberFormat
	);
	ASSERT_THROWS(
			c.addOrganization( "test", "000000000", 18 );
		,	Messages::InvalidRegistrationNumberFormat
	);
	ASSERT_THROWS(
			c.addOrganization( "test", "0000000A", 18 );
		,	Messages::InvalidRegistrationNumberFormat
	);
	ASSERT_THROWS(
			c.addOrganization( "test", "elephant", 18 );
		,	Messages::InvalidRegistrationNumberFormat
	);
	ASSERT_THROWS(
			c.addOrganization( "test", "    ", 18 );
		,	Messages::InvalidRegistrationNumberFormat
	);
	ASSERT_THROWS(
			c.addOrganization( "test", "OOOOOOOO", 18 );
		,	Messages::InvalidRegistrationNumberFormat
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_8_organization_with_negative_balance )
{
	Controller c;
	c.addOrganization( "own", "00000001", -100 );

	assert( c.getBalance( "own" ) == -100 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_9_organization_with_zero_balance )
{
	Controller c;
	c.addOrganization( "own", "00000001", 0 );

	assert( c.getBalance( "own" ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_10_organization_obtain_registration_number_by_empty_name )
{
	Controller c;
	c.addOrganization( "test #1", "00000000", 18 );

	ASSERT_THROWS(
			c.getRegistrationNumber( "" );
		,	Messages::OrganizationCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_10_organization_obtain_registration_number_for_missing_organization )
{
	Controller c;
	c.addOrganization( "test #1", "00000000", 18 );

	ASSERT_THROWS(
			c.getRegistrationNumber( "test #2" );
		,	Messages::OrganizationCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_12_organization_obtain_balance_by_empty_name )
{
	Controller c;
	c.addOrganization( "test #1", "00000000", 18 );

	ASSERT_THROWS(
			c.getBalance( "" );
		,	Messages::OrganizationCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_1_13_organization_obtain_balance_for_missing_organization )
{
	Controller c;
	c.addOrganization( "test #1", "00000000", 18 );

	ASSERT_THROWS(
			c.getBalance( "test #2" );
		,	Messages::OrganizationCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_1_payment_one )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	assert( c.getSenderName( "1" ) == "mystic" );
	assert( c.getReceiverName( "1" ) == "moon" );
	assert( c.getPaymentPurpose( "1" ) == "Just for fun!" );
	assert( c.getPaymentDateTime( "1" ) == dateTime );
	assert( c.getPaymentSum( "1" ) == 69 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_2_1_payment_several_for_different_organizations )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );
	c.addOrganization( "sausages", "22334455", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime1( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "556", "Rrrrr!", dateTime1, 12 );
	DateTime dateTime2( 2013, 2, 18, 16, 44, 44 );
	c.addPayment( "sausages", "kitty", "37", "Mew", dateTime2, 13 );

	assert( c.getSenderName( "556" ) == "mystic" );
	assert( c.getReceiverName( "556" ) == "moon" );
	assert( c.getPaymentPurpose( "556" ) == "Rrrrr!" );
	assert( c.getPaymentDateTime( "556" ) == dateTime1 );
	assert( c.getPaymentSum( "556" ) == 12 );

	assert( c.getSenderName( "37" ) == "sausages" );
	assert( c.getReceiverName( "37" ) == "kitty" );
	assert( c.getPaymentPurpose( "37" ) == "Mew" );
	assert( c.getPaymentDateTime( "37" ) == dateTime2 );
	assert( c.getPaymentSum( "37" ) == 13 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_2_2_payment_several_for_one_sender )
{
	Controller c;
	c.addOrganization( "moon", "12345678", 999 );
	c.addOrganization( "sausages", "22334455", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime1( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "sausages", "moon", "556", "Rrrrr!", dateTime1, 12 );
	DateTime dateTime2( 2013, 2, 18, 16, 44, 44 );
	c.addPayment( "sausages", "kitty", "37", "Mew", dateTime2, 13 );

	assert( c.getSenderName( "556" ) == "sausages" );
	assert( c.getReceiverName( "556" ) == "moon" );
	assert( c.getPaymentPurpose( "556" ) == "Rrrrr!" );
	assert( c.getPaymentDateTime( "556" ) == dateTime1 );
	assert( c.getPaymentSum( "556" ) == 12 );

	assert( c.getSenderName( "37" ) == "sausages" );
	assert( c.getReceiverName( "37" ) == "kitty" );
	assert( c.getPaymentPurpose( "37" ) == "Mew" );
	assert( c.getPaymentDateTime( "37" ) == dateTime2 );
	assert( c.getPaymentSum( "37" ) == 13 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_2_3_payment_several_for_one_receiver )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "sausages", "22334456", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime1( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "kitty", "556", "Rrrrr!", dateTime1, 12 );
	DateTime dateTime2( 2013, 2, 18, 16, 44, 44 );
	c.addPayment( "sausages", "kitty", "37", "Mew", dateTime2, 13 );

	assert( c.getSenderName( "556" ) == "mystic" );
	assert( c.getReceiverName( "556" ) == "kitty" );
	assert( c.getPaymentPurpose( "556" ) == "Rrrrr!" );
	assert( c.getPaymentDateTime( "556" ) == dateTime1 );
	assert( c.getPaymentSum( "556" ) == 12 );

	assert( c.getSenderName( "37" ) == "sausages" );
	assert( c.getReceiverName( "37" ) == "kitty" );
	assert( c.getPaymentPurpose( "37" ) == "Mew" );
	assert( c.getPaymentDateTime( "37" ) == dateTime2 );
	assert( c.getPaymentSum( "37" ) == 13 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_2_4_payment_several_for_the_same_sender_and_receiver )
{
	Controller c;
	c.addOrganization( "sausages", "22334456", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime1( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "sausages", "kitty", "556", "Rrrrr!", dateTime1, 12 );
	DateTime dateTime2( 2013, 2, 18, 16, 44, 44 );
	c.addPayment( "sausages", "kitty", "37", "Mew", dateTime2, 13 );

	assert( c.getSenderName( "556" ) == "sausages" );
	assert( c.getReceiverName( "556" ) == "kitty" );
	assert( c.getPaymentPurpose( "556" ) == "Rrrrr!" );
	assert( c.getPaymentDateTime( "556" ) == dateTime1 );
	assert( c.getPaymentSum( "556" ) == 12 );

	assert( c.getSenderName( "37" ) == "sausages" );
	assert( c.getReceiverName( "37" ) == "kitty" );
	assert( c.getPaymentPurpose( "37" ) == "Mew" );
	assert( c.getPaymentDateTime( "37" ) == dateTime2 );
	assert( c.getPaymentSum( "37" ) == 13 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_3_payment_with_empty_sender_name )
{
	Controller c;
	c.addOrganization( "sausages", "22334456", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );

	ASSERT_THROWS(
			c.addPayment( "", "kitty", "1", "Just for fun!", dateTime, 69 );
		,	Messages::OrganizationCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_4_payment_with_empty_reciever_name )
{
	Controller c;
	c.addOrganization( "sausages", "22334456", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );

	ASSERT_THROWS(
			c.addPayment( "sausages", "", "1", "Just for fun!", dateTime, 69 );
		,	Messages::OrganizationCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_5_payment_with_empty_unique_number )
{
	Controller c;
	c.addOrganization( "sausages", "22334456", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );

	ASSERT_THROWS(
			c.addPayment( "sausages", "kitty", "", "Just for fun!", dateTime, 69 );
		,	Messages::EmptyPaymentId
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_6_payment_with_empty_purpose )
{
	Controller c;
	c.addOrganization( "sausages", "22334456", 0 );
	c.addOrganization( "kitty", "00991234", -3 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );

	ASSERT_THROWS(
			c.addPayment( "sausages", "kitty", "1", "", dateTime, 69 );
		,	Messages::EmptyPaymentPurpose
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_7_payment_with_duplicate_unique_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000100", 122 );
	c.addOrganization( "moon", "12345578", 133 );
	c.addOrganization( "sausages", "22334456", 1 );
	c.addOrganization( "kitty", "00991234", 1 );

	DateTime dateTime1( 2015, 1, 1, 12, 0, 0 );
	DateTime dateTime2( 2015, 1, 1, 12, 0, 1 );
	c.addPayment( "mystic", "kitty", "1", "Purpose #1", dateTime1, 67 );

	ASSERT_THROWS(
			c.addPayment( "sausages", "moon", "1", "Purpose #2", dateTime2, 50 );
		,	Messages::DuplicatePayment
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_8_payment_with_duplicate_purpose )
{
	Controller c;
	c.addOrganization( "mystic", "00000100", 122 );
	c.addOrganization( "moon", "12345578", 133 );
	c.addOrganization( "sausages", "22334456", 1 );
	c.addOrganization( "kitty", "00991234", 1 );

	DateTime dateTime1( 2015, 1, 1, 12, 0, 0 );
	DateTime dateTime2( 2015, 1, 1, 12, 0, 1 );
	c.addPayment( "mystic", "kitty", "1", "Purpose #1", dateTime1, 67 );
	c.addPayment( "sausages", "moon", "2", "Purpose #1", dateTime2, 50 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_9_payment_with_time_in_the_future )
{
	Controller c;
	c.addOrganization( "testFrom", "00000100", 100 );
	c.addOrganization( "testTo", "10000000", 200 );

	DateTime dateTime( 2093, 7, 19, 11, 0, 0 );
	ASSERT_THROWS(
			c.addPayment( "testFrom", "testTo", "88", "purpose", dateTime, 99 );
		,	Messages::InvalidPaymentTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_10_payment_with_current_time )
{
	Controller c;
	c.addOrganization( "testFrom", "00000100", 100 );
	c.addOrganization( "testTo", "10000000", 200 );

	DateTime dateTime;
	c.addPayment( "testFrom", "testTo", "88", "purpose", dateTime, 99 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_11_payment_two_payments_with_the_same_time )
{
	Controller c;
	c.addOrganization( "testFrom", "00000100", 100 );
	c.addOrganization( "testTo", "10000000", 200 );

	DateTime dateTime;
	c.addPayment( "testFrom", "testTo", "88", "purpose", dateTime, 99 );
	c.addPayment( "testFrom", "testTo", "89", "purpose", dateTime, 99 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_12_payment_with_custom_chars_in_unique_number )
{
	Controller c;
	c.addOrganization( "testFrom", "00000100", 100 );
	c.addOrganization( "testTo", "10000000", 200 );

	DateTime dateTime;
	c.addPayment( "testFrom", "testTo", "AAA", "purpose", dateTime, 34 );
	c.addPayment( "testFrom", "testTo", "%$#@", "purpose", dateTime, 34 );
	c.addPayment( "testFrom", "testTo", "00DD88", "purpose", dateTime, 34 );
	c.addPayment( "testFrom", "testTo", "-", "purpose", dateTime, 34 );
	c.addPayment( "testFrom", "testTo", "bn", "purpose", dateTime, 34 );
	c.addPayment( "testFrom", "testTo", "[]", "purpose", dateTime, 34 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_13_payment_with_negative_sum )
{
	Controller c;
	c.addOrganization( "testFrom", "00000100", 100 );
	c.addOrganization( "testTo", "10000000", 200 );

	DateTime dateTime;
	ASSERT_THROWS(
			c.addPayment( "testFrom", "testTo", "88", "purpose", dateTime, -2 );
		,	Messages::InvalidPaymentSum
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_14_payment_with_zero_sum )
{
	Controller c;
	c.addOrganization( "testFrom", "00000100", 100 );
	c.addOrganization( "testTo", "10000000", 200 );

	DateTime dateTime;
	ASSERT_THROWS(
			c.addPayment( "testFrom", "testTo", "88", "purpose", dateTime, 0 );
		,	Messages::InvalidPaymentSum
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_15_payment_for_itself )
{
	Controller c;
	c.addOrganization( "testFrom", "00000100", 100 );
	c.addOrganization( "testTo", "10000000", 200 );

	DateTime dateTime;
	ASSERT_THROWS(
			c.addPayment( "testFrom", "testFrom", "88", "purpose", dateTime, 2 );
		,	Messages::PaymentForItself
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_16_payment_obtain_sender_name_by_empty_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getSenderName( "" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_17_payment_obtain_sender_name_for_missing_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getSenderName( "2" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_18_payment_obtain_receiver_name_by_empty_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getReceiverName( "" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_19_payment_obtain_receiver_name_for_missing_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getReceiverName( "2" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_20_payment_obtain_purpose_by_empty_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getPaymentPurpose( "" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_21_payment_obtain_purpose_for_missing_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getPaymentPurpose( "2" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_22_payment_obtain_datetime_by_empty_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getPaymentDateTime( "" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_23_payment_obtain_datetime_for_missing_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getPaymentDateTime( "2" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_24_payment_obtain_sum_by_empty_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getPaymentSum( "" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_2_25_payment_obtain_sum_for_missing_number )
{
	Controller c;
	c.addOrganization( "mystic", "00000000", 666 );
	c.addOrganization( "moon", "12345678", 999 );

	DateTime dateTime( 2015, 1, 1, 12, 0, 0 );
	c.addPayment( "mystic", "moon", "1", "Just for fun!", dateTime, 69 );

	ASSERT_THROWS(
			c.getPaymentSum( "2" );
		,	Messages::PaymentCannotBeFound
	);
}


/*****************************************************************************/


DateTime date ( int _year, int _month, int _day )
{
	int hours = rand() % 24;
	int minutes = rand() % 60;
	int seconds = rand() % 60;

	return DateTime(
			_year
		,	_month
		,	_day
		,	hours
		,	minutes
		,	seconds
	);
}


/*****************************************************************************/


void generateModel ( Controller & _c )
{
	srand( static_cast< unsigned int >( time( nullptr ) ) );

	_c.addOrganization( "Yoha", "00110030", 0 );
	_c.addOrganization( "Toto", "00110047", 100 );
	_c.addOrganization( "Rute", "00110134", -25 );
	_c.addOrganization( "Gofi", "00120267", 45 );
	_c.addOrganization( "Qwer", "01003401", 20 );

	_c.addPayment( "Yoha", "Toto", "01", "payment #01", date( 2010, 1, 1 ), 21 );
	_c.addPayment( "Yoha", "Rute", "02", "payment #02", date( 2010, 1, 1 ), 21 );
	_c.addPayment( "Yoha", "Gofi", "03", "payment #03", date( 2010, 1, 1 ), 21 );
	_c.addPayment( "Yoha", "Qwer", "04", "payment #04", date( 2010, 1, 1 ), 21 );

	_c.addPayment( "Toto", "Yoha", "05", "payment #05", date( 2010, 2, 1 ), 21 );
	_c.addPayment( "Toto", "Rute", "06", "payment #06", date( 2010, 2, 1 ), 21 );
	_c.addPayment( "Toto", "Gofi", "07", "payment #07", date( 2010, 2, 1 ), 21 );
	_c.addPayment( "Toto", "Qwer", "08", "payment #08", date( 2010, 2, 1 ), 21 );

	_c.addPayment( "Rute", "Yoha", "09", "payment #09", date( 2010, 1, 2 ), 21 );
	_c.addPayment( "Rute", "Toto", "10", "payment #10", date( 2010, 1, 2 ), 21 );
	_c.addPayment( "Rute", "Gofi", "11", "payment #11", date( 2010, 1, 2 ), 21 );
	_c.addPayment( "Rute", "Qwer", "12", "payment #12", date( 2010, 1, 2 ), 21 );

	_c.addPayment( "Gofi", "Yoha", "13", "payment #13", date( 2010, 3, 1 ), 21 );
	_c.addPayment( "Gofi", "Toto", "14", "payment #14", date( 2010, 3, 1 ), 21 );
	_c.addPayment( "Gofi", "Rute", "15", "payment #15", date( 2010, 3, 1 ), 21 );
	_c.addPayment( "Gofi", "Qwer", "16", "payment #16", date( 2010, 3, 1 ), 21 );

	_c.addPayment( "Qwer", "Yoha", "17", "payment #17", date( 2010, 1, 3 ), 21 );
	_c.addPayment( "Qwer", "Toto", "18", "payment #18", date( 2010, 1, 3 ), 21 );
	_c.addPayment( "Qwer", "Rute", "19", "payment #19", date( 2010, 1, 3 ), 21 );
	_c.addPayment( "Qwer", "Gofi", "20", "payment #20", date( 2010, 1, 3 ), 21 );

	_c.addPayment( "Qwer", "Rute", "21", "payment #21", date( 2010, 4, 1 ), 50 );
	_c.addPayment( "Gofi", "Yoha", "22", "payment #22", date( 2010, 4, 1 ), 25 );
	_c.addPayment( "Gofi", "Toto", "23", "payment #23", date( 2010, 4, 1 ), 20 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_3_1_queries_get_final_balances )
{
	Controller c;
	generateModel( c );

	// NOTE: Organizations were sorted in alphabetical order
	std::vector< std::pair< std::string, double > > expectation =
	{
			{ "Gofi", 0 }
		,	{ "Qwer", -30 }
		,	{ "Rute", 25 }
		,	{ "Toto", 120 }
		,	{ "Yoha", 25 }
	};
	assert( c.getFinalBalances() == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_3_2_queries_get_organizations_with_negative_saldo )
{
	Controller c;
	generateModel( c );

	// NOTE: Organizations were sorted in alphabetical order
	std::vector< std::string > expectation =
	{
			"Gofi"
		,	"Qwer"
	};
	assert( c.getOrganizationsWithNegativeSaldo() == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_3_3_queries_get_biggest_payment_data )
{
	Controller c;
	generateModel( c );

	assert( c.getIdOfBiggestPayment() == "21" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( payments_3_4_queries_get_date_with_biggest_total_payments_amount )
{
	Controller c;
	generateModel( c );

	Date expectation( 2010, 4, 1 );
	assert( c.getDateWithBiggestTotalPayments() == expectation );
}


/*****************************************************************************/
