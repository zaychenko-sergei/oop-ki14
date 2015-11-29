// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_simple_program )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );
	
	assert( c.getProgramVendor( "Windows 10" ) == "Microsoft" );
	assert( c.getProgramLicenseType( "Windows 10" ) == LicenseType::Undefined );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_programs )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );
	c.createProgram( "Picasa", "Google" );

	assert( c.getProgramVendor( "Windows 10" ) == "Microsoft" );
	assert( c.getProgramLicenseType( "Windows 10" ) == LicenseType::Undefined );

	assert( c.getProgramVendor( "Picasa" ) == "Google" );
	assert( c.getProgramLicenseType( "Picasa" ) == LicenseType::Undefined );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_program_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.createProgram( "", "Microsoft" )
		,	Messages::ProgramNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_program_with_empty_vendor )
{
	Controller c;

	ASSERT_THROWS(
			c.createProgram( "Windows 10", "" )
		,	Messages::VendorNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_program_with_duplicate_name )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );

	ASSERT_THROWS(
			c.createProgram( "Windows 10", "Microsoft" )
		,	Messages::ProgramNameNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_ask_unlicensed_program_various_queries )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );

	ASSERT_THROWS(
			c.getProgramLicenseIssueDate( "Windows 10" )
		,	Messages::ProgramHasNoLicense
	);

	ASSERT_THROWS(
			c.canUse( "Windows 10", Date( 2015, 01, 01 ) )
		,	Messages::ProgramHasNoLicense
	);

	ASSERT_THROWS(
			c.trackUse( "Windows 10", Date( 2015, 01, 01 ) )
		,	Messages::ProgramHasNoLicense
	);

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_define_perpetual_license )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );
	c.createPerpetualLicense( "Windows 10", Date( 2015, 01, 01 ) );

	assert( c.getProgramLicenseType( "Windows 10" ) == LicenseType::Perpetual );
	assert( c.getProgramLicenseIssueDate( "Windows 10" ) == Date( 2015, 01, 01 ) );
	
	assert( ! c.canUse( "Windows 10", Date( 2014, 12, 31 ) ) );
	assert( c.canUse( "Windows 10", Date( 2015, 01, 01 ) ) );
	assert( c.canUse( "Windows 10", Date( 2100, 01, 01 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_use_perpetual_license_any_day_not_earlier_than_issued )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );
	c.createPerpetualLicense( "Windows 10", Date( 2015, 01, 01 ) );

	c.trackUse( "Windows 10", Date( 2015, 01, 01 ) );
	c.trackUse( "Windows 10", Date( 2100, 01, 01 ) );

	ASSERT_THROWS(
			c.trackUse( "Windows 10", Date( 2014, 12, 31 ) )
		,	Messages::NoValidLicense
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_define_time_based_license )
{
	Controller c;
	c.createProgram( "IDEA", "JetBrains" );
	c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2016, 01, 01 ) );

	assert( c.getProgramLicenseType( "IDEA" ) == LicenseType::TimeBased );
	assert( c.getProgramLicenseIssueDate( "IDEA" ) == Date( 2015, 01, 01 ) );
	assert( c.getLicenseExpiryDate( "IDEA" ) == Date( 2016, 01, 01 ) );
	
	assert( c.canUse( "IDEA", Date( 2015, 01, 01 ) ) );
	assert( c.canUse( "IDEA", Date( 2016, 01, 01 ) ) );

	assert( ! c.canUse( "IDEA", Date( 2014, 12, 31 ) ) );
	assert( ! c.canUse( "IDEA", Date( 2016, 01, 02 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_define_time_based_license_bad_expiry_date )
{
	Controller c;
	c.createProgram( "IDEA", "JetBrains" );

	ASSERT_THROWS(
			c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2014, 12, 31 ) )
		,	Messages::ExpiryEarlierThanIssue
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_define_time_based_license_expire_same_as_issued )
{
	Controller c;
	c.createProgram( "IDEA", "JetBrains" );
	c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2015, 01, 01 ) );

	assert( c.getProgramLicenseType( "IDEA" ) == LicenseType::TimeBased );
	assert( c.getProgramLicenseIssueDate( "IDEA" ) == Date( 2015, 01, 01 ) );
	assert( c.getLicenseExpiryDate( "IDEA" ) == Date( 2015, 01, 01 ) );

	assert( c.canUse( "IDEA", Date( 2015, 01, 01 ) ) );

	assert( ! c.canUse( "IDEA", Date( 2014, 12, 31 ) ) );
	assert( ! c.canUse( "IDEA", Date( 2015, 01, 02 ) ) );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_prolong_time_based_license_normally )
{
	Controller c;
	c.createProgram( "IDEA", "JetBrains" );
	c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2015, 01, 01 ) );

	assert( ! c.canUse( "IDEA", Date( 2015, 01, 02 ) ) );

	c.prolongLicense( "IDEA", Date( 2015, 01, 02 ) );

	assert( c.canUse( "IDEA", Date( 2015, 01, 02 ) ) );
	assert( ! c.canUse( "IDEA", Date( 2015, 01, 03 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_prolong_time_based_license_to_same_day )
{
	Controller c;
	c.createProgram( "IDEA", "JetBrains" );
	c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2015, 01, 01 ) );
	c.prolongLicense( "IDEA", Date( 2015, 01, 01 ) );

	assert( c.getLicenseExpiryDate( "IDEA" ) == Date( 2015, 01, 01 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_usage_fails_when_expiry_date_reached )
{
	Controller c;
	c.createProgram( "IDEA", "JetBrains" );
	c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2015, 02, 01 ) );

	ASSERT_THROWS(
			c.trackUse( "IDEA", Date( 2015, 02, 02 ) )
		,	Messages::NoValidLicense
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_prolong_time_based_license_to_previous_day )
{
	Controller c;
	c.createProgram( "IDEA", "JetBrains" );
	c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2015, 02, 01 ) );
	
	ASSERT_THROWS(
			c.prolongLicense( "IDEA", Date( 2015, 01, 31 ) )
		,	Messages::ProlongingToEarlierDate
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_try_time_based_functions_on_different_license )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );
	c.createPerpetualLicense( "Windows 10", Date( 2015, 01, 01 ) );

	c.createProgram( "Angry Birds", "Rovio" );
	c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), 1 );

	ASSERT_THROWS(
			c.getLicenseExpiryDate( "Windows 10" )
		,	Messages::TimeBasedLicenseExpected
	);

	ASSERT_THROWS(
			c.prolongLicense( "Windows 10", Date( 2015, 01, 31 ) )
		,	Messages::TimeBasedLicenseExpected
	);

	ASSERT_THROWS(
			c.getLicenseExpiryDate( "Angry Birds" )
		,	Messages::TimeBasedLicenseExpected
	);

	ASSERT_THROWS(
			c.prolongLicense( "Angry Birds", Date( 2015, 01, 31 ) )
		,	Messages::TimeBasedLicenseExpected
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_try_time_based_functions_on_program_without_license )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );

	ASSERT_THROWS(
			c.getLicenseExpiryDate( "Windows 10" )
		,	Messages::ProgramHasNoLicense
	);

	ASSERT_THROWS(
			c.prolongLicense( "Windows 10", Date( 2016, 01, 01 ) )
		,	Messages::ProgramHasNoLicense
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_define_token_based_license )
{
	Controller c;
	c.createProgram( "Angry Birds", "Rovio" );
	c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), 5 );

	assert( c.getProgramLicenseType( "Angry Birds" ) == LicenseType::TokenBased );
	assert( c.getProgramLicenseIssueDate( "Angry Birds" ) == Date( 2015, 01, 01 ) );
	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 5 );

	assert( c.canUse( "Angry Birds", Date( 2015, 01, 01 ) ) );
	assert( c.canUse( "Angry Birds", Date( 2100, 01, 01 ) ) );

	assert( ! c.canUse( "Angry Birds", Date( 2014, 12, 31 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_define_wrong_tokens_count )
{
	Controller c;
	c.createProgram( "Angry Birds", "Rovio" );

	ASSERT_THROWS(
			c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), -1 )
		,	Messages::NonPositiveTokens
	);

	ASSERT_THROWS(
			c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), 0 )
		,	Messages::NonPositiveTokens
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_extra_tokens_later )
{
	Controller c;
	c.createProgram( "Angry Birds", "Rovio" );

	c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), 5 );
	c.addLicenseTokens( "Angry Birds", 3 );

	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 8 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_bad_tokens_count )
{
	Controller c;
	c.createProgram( "Angry Birds", "Rovio" );
	c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), 5 );
	
	ASSERT_THROWS(
			c.addLicenseTokens( "Angry Birds", -1 )
		,	Messages::NonPositiveTokens
	);

	ASSERT_THROWS(
			c.addLicenseTokens( "Angry Birds", 0 )
		,	Messages::NonPositiveTokens
	);

	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_program_usage_decreases_tokens_count )
{
	Controller c;
	c.createProgram( "Angry Birds", "Rovio" );
	c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), 1 );

	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 1 );
	assert( c.canUse( "Angry Birds", Date( 2015, 01, 01 ) ) );

	c.trackUse( "Angry Birds", Date( 2015, 01, 01 ) );

	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 0 );
	assert( ! c.canUse( "Angry Birds", Date( 2015, 01, 01 ) ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_program_usage_impossible_when_no_tokens_left )
{
	Controller c;
	c.createProgram( "Angry Birds", "Rovio" );
	c.createTokenBasedLicense( "Angry Birds", Date( 2015, 01, 01 ), 1 );

	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 1 );

	c.trackUse( "Angry Birds", Date( 2015, 01, 01 ) );

	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 0 );

	ASSERT_THROWS(
			c.trackUse( "Angry Birds", Date( 2015, 01, 01 ) )
		,	Messages::NoValidLicense
	);

	assert( c.getLicenseTokensLeft( "Angry Birds" ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_try_token_based_functions_on_different_license )
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );
	c.createPerpetualLicense( "Windows 10", Date( 2015, 01, 01 ) );

	c.createProgram( "IDEA", "JetBrains" );
	c.createTimeBasedLicense( "IDEA", Date( 2015, 01, 01 ), Date( 2016, 01, 01 ) );

	ASSERT_THROWS(
			c.getLicenseTokensLeft( "Windows 10" )
		,	Messages::TokenBasedLicenseExpected
	);

	ASSERT_THROWS(
			c.addLicenseTokens( "Windows 10", 1 )
		,	Messages::TokenBasedLicenseExpected
	);

	ASSERT_THROWS(
			c.getLicenseTokensLeft( "IDEA" )
		,	Messages::TokenBasedLicenseExpected
	);

	ASSERT_THROWS(
			c.addLicenseTokens( "IDEA", 1 )
		,	Messages::TokenBasedLicenseExpected
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_try_token_based_functions_on_program_without_license)
{
	Controller c;
	c.createProgram( "Windows 10", "Microsoft" );

	ASSERT_THROWS(
			c.getLicenseTokensLeft( "Windows 10" )
		,	Messages::ProgramHasNoLicense
	);

	ASSERT_THROWS(
			c.addLicenseTokens( "Windows 10", 1 )
		,	Messages::ProgramHasNoLicense
	);
}


/*****************************************************************************/
