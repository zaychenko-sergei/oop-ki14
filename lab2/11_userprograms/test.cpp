// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


void createCommonConfiguration ( Controller & c )
{
	c.createAccount( "first", "First Account" );
	c.createAccount( "second", "Second Account" );
	c.createAccount( "third", "Third Account" );
	c.createAccount( "fourth", "Fourth Account" );
	c.createAccount( "fifth", "Fifth Account" );
	c.createAccount( "sixth", "Sixth Account" );
	c.createAccount( "seventh", "Seventh Account" );

	c.createProgram( "Netscape", "Netscape inc.", "5.4", 1995, ProgramCategory::Browser );
	c.createProgram( "Netscape", "Netscape inc.", "2.1", 1994, ProgramCategory::Browser );
	c.createProgram( "Internet Explorer", "Microsoft", "2.1", 1996, ProgramCategory::Browser );
	c.createProgram( "Internet Explorer", "Microsoft", "5.0", 2000, ProgramCategory::Browser );

	c.createProgram( "OpenOffice", "Oracle", "5.4", 2008, ProgramCategory::Office );
	c.createProgram( "OpenOffice", "Oracle", "2.1", 2004, ProgramCategory::Office );
	c.createProgram( "Word", "Microsoft", "2002", 2002, ProgramCategory::Office );
	c.createProgram( "Word", "Microsoft", "2003", 2003, ProgramCategory::Office );

	c.createProgram( "Firefox", "Mozilla", "1.0", 1996, ProgramCategory::Browser );
	c.createProgram( "Firefox", "Mozilla", "1.5", 1998, ProgramCategory::Browser );
	c.createProgram( "Pidguin", "FSF", "5.0", 1997, ProgramCategory::Browser );
	c.createProgram( "LibreOffice", "FSF", "1.2", 2004, ProgramCategory::Office );
	c.createProgram( "LibreOffice", "FSF", "1.4", 2004, ProgramCategory::Office );

	c.setAccountPreferredBrowser( "first", "Netscape", "5.4" );
	c.setAccountPreferredOfficeTool( "first", "OpenOffice", "5.4" );

	c.setAccountPreferredBrowser( "second", "Netscape", "2.1" );
	c.setAccountPreferredOfficeTool( "second", "OpenOffice", "2.1" );

	c.setAccountPreferredBrowser( "third", "Internet Explorer", "2.1" );
	c.setAccountPreferredOfficeTool( "third", "Word", "2002" );

	c.setAccountPreferredBrowser( "fourth", "Internet Explorer", "5.0" );
	c.setAccountPreferredOfficeTool( "fourth", "Word", "2003" );

	c.setAccountPreferredBrowser( "fifth", "Netscape", "2.1" );
	c.setAccountPreferredOfficeTool( "fifth", "Word", "2002" );

	c.setAccountPreferredBrowser( "sixth", "Netscape", "5.4" );
	c.setAccountPreferredOfficeTool( "sixth", "Word", "2003" );

	c.setAccountPreferredBrowser( "seventh", "Netscape", "2.1" );
	c.setAccountPreferredOfficeTool( "seventh", "Word", "2003" );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_account_properties )
{
	Controller c;

	c.createAccount( "ivani", "Ivan Ivanov" );

	assert( c.getAccountFullName( "ivani" ) == "Ivan Ivanov" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_program_properties )
{
	Controller c;

	c.createProgram( "Word", "MS", "5.0.1", 2014, ProgramCategory::Office );

	assert( c.getProgramManufacturer( "Word", "5.0.1" ) == "MS" );
	assert( c.getProgramReleaseYear( "Word", "5.0.1" ) == 2014 );
	assert( c.getProgramCategory( "Word", "5.0.1" ) == ProgramCategory::Office );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_account_with_empty_full_name )
{
	Controller c;

	ASSERT_THROWS(
			c.createAccount( "ivani", "" )
		,	Messages::AbsentFullName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_account_with_empty_login )
{
	Controller c;

	ASSERT_THROWS(
			c.createAccount( "", "Ivan Ivanov" )
		,	Messages::AbsentLogin
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_program_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.createProgram( "", "Google", "40.0.1.15648321", 2015, ProgramCategory::Browser )
		,	Messages::AbsentProgramName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_program_with_empty_manufacturer )
{
	Controller c;

	ASSERT_THROWS(
			c.createProgram( "Chrome", "", "40.0.1.15648321", 2015, ProgramCategory::Browser )
		,	Messages::AbsentManufacturer
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_program_with_empty_version )
{
	Controller c;

	ASSERT_THROWS(
			c.createProgram( "Chrome", "Google", "", 2015, ProgramCategory::Browser )
		,	Messages::AbsentVersion
	);
}


/*****************************************************************************//*****************************************************************************/


DECLARE_OOP_TEST ( test_create_user_and_assign_preferred_apps )
{
	Controller c;

	c.createAccount( "ashleyp", "Ivan Ivanov" );
	c.createAccount( "ivani", "Ivan Ivanov" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_account_with_duplicating_login )
{
	Controller c;

	c.createAccount( "ivani", "Ivan Ivanov" );
	ASSERT_THROWS(
			c.createAccount( "ivani", "Ivan Ivanenko" )
		,	Messages::LoginShouldBeUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_account_with_duplicating_full_name )
{
	Controller c;

	c.createAccount( "ivani", "Ivan Ivanov" );
	c.createAccount( "ivaniv", "Ivan Ivanov" );

	assert( c.getAccountFullName( "ivani" ) == "Ivan Ivanov" );
	assert( c.getAccountFullName( "ivaniv" ) == "Ivan Ivanov" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_program_with_same_name_and_different_versions )
{
	Controller c;

	c.createProgram( "Chrome", "Google", "42.0.15", 2015, ProgramCategory::Browser );
	c.createProgram( "Chrome", "Google", "43.0.53", 2015, ProgramCategory::Browser );

	assert( c.getProgramManufacturer( "Chrome", "42.0.15" ) == "Google" );
	assert( c.getProgramManufacturer( "Chrome", "43.0.53" ) == "Google" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_program_with_same_name_and_different_versions_and_manufacturers )
{
	Controller c;

	c.createProgram( "Chrome", "Google", "42.0.15", 2015, ProgramCategory::Browser );
	c.createProgram( "Chrome", "Not Google", "43.0.53", 2015, ProgramCategory::Browser );

	assert( c.getProgramManufacturer( "Chrome", "42.0.15" ) == "Google" );
	assert( c.getProgramManufacturer( "Chrome", "43.0.53" ) == "Not Google" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_program_with_same_name_and_same_version )
{
	Controller c;

	c.createProgram( "Chrome", "Google", "42.0.15", 2015, ProgramCategory::Browser );

	ASSERT_THROWS(
			c.createProgram( "Chrome", "Google", "42.0.15", 2015, ProgramCategory::Browser )
		,	Messages::VersionDuplication
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_program_with_different_name_and_same_version )
{
	Controller c;

	c.createProgram( "Chrome", "Google", "42.0.15", 2015, ProgramCategory::Browser );
	c.createProgram( "Hangouts", "Google", "42.0.15", 2015, ProgramCategory::Other );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_program_with_different_categories )
{
	Controller c;

	c.createProgram( "Chrome", "Google", "42.0.15", 2015, ProgramCategory::Browser );
	c.createProgram( "Hangouts", "Google", "42.0.15", 2014, ProgramCategory::Other );
	c.createProgram( "OpenOffice", "Oracle", "6.0.153", 2013, ProgramCategory::Office );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_account_with_preferred_programs )
{
	Controller c;

	c.createAccount( "darthv", "Darth Vader" );

	c.createProgram( "Destroyer Deck", "Empire inc.", "3.1", 9000, ProgramCategory::Browser );
	c.createProgram( "Deathstar", "Empire inc.", "1.0", 9002, ProgramCategory::Office );

	c.setAccountPreferredBrowser( "darthv", "Destroyer Deck", "3.1" );
	c.setAccountPreferredOfficeTool( "darthv", "Deathstar", "1.0" );

	assert( c.getProgramsWithoutPreferences().size() == 0 );
	assert( c.getUsersCountWithBrowsersAndOffice( "Destroyer Deck", "Deathstar" ) == 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_account_with_preferred_programs_mismatch_office_to_browser )
{
	Controller c;

	c.createAccount( "darthv", "Darth Vader" );

	c.createProgram( "Deathstar", "Empire inc.", "1.0", 9002, ProgramCategory::Office );

	ASSERT_THROWS(
			c.setAccountPreferredBrowser( "darthv", "Deathstar", "1.0" )
		,	Messages::ProgramCategoryMismatch
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_account_with_preferred_programs_mismatch_browser_to_office )
{
	Controller c;

	c.createAccount( "darthv", "Darth Vader" );

	c.createProgram( "Destroyer Deck", "Empire inc.", "3.1", 9002, ProgramCategory::Browser );

	ASSERT_THROWS(
			c.setAccountPreferredOfficeTool( "darthv", "Destroyer Deck", "3.1" )
		,	Messages::ProgramCategoryMismatch
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_account_with_preferred_programs_version_mismatch )
{
	Controller c;

	c.createAccount( "darthv", "Darth Vader" );

	c.createProgram( "Destroyer Deck", "Empire inc.", "3.1", 9002, ProgramCategory::Office );

	ASSERT_THROWS(
			c.setAccountPreferredOfficeTool( "darthv", "Destroyer Deck", "42" )
		,	Messages::ProgramDoesNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_account_without_preferred_programs )
{
	Controller c;

	c.createAccount( "darthv", "Darth Vader" );

	c.createProgram( "Destroyer Deck", "Empire inc.", "3.1", 9002, ProgramCategory::Office );
	c.createProgram( "Deathstar", "Empire inc.", "1.0", 9002, ProgramCategory::Office );

	assert( c.getAccountPreferredBrowserName( "darthv" ) == "" );
	assert( c.getAccountPreferredOfficeToolName( "darthv" ) == "" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_accounts_preferring_browser_query )
{
	Controller c;

	c.createAccount( "first", "First Account" );
	c.createAccount( "second", "Second Account" );
	c.createAccount( "third", "Third Account" );

	c.createProgram( "Netscape", "Netscape inc.", "5.4", 1995, ProgramCategory::Browser );
	c.createProgram( "Netscape", "Netscape inc.", "2.1", 1994, ProgramCategory::Browser );
	c.createProgram( "Internet Explorer", "Microsoft", "2.1", 1996, ProgramCategory::Browser );

	c.setAccountPreferredBrowser( "first", "Netscape", "5.4" );
	c.setAccountPreferredBrowser( "second", "Internet Explorer", "2.1" );
	c.setAccountPreferredBrowser( "third", "Netscape", "2.1" );

	auto expectedLogins = std::vector< std::string >{ "first", "third" };
	auto recievedLogins = c.getUsersPreferringBrowser( "Netscape" );
	std::sort( recievedLogins.begin(), recievedLogins.end() );
	std::sort( expectedLogins.begin(), expectedLogins.end() );

	assert( expectedLogins == recievedLogins );
	assert( c.getUsersPreferringBrowser( "Internet Explorer" ) == std::vector< std::string >{ "second" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_accounts_preferring_browser_and_office_tool_query )
{
	Controller c;

	createCommonConfiguration( c );

	assert( c.getUsersCountWithBrowsersAndOffice( "Netscape", "Word" ) == 3 );
	assert( c.getUsersCountWithBrowsersAndOffice( "Internet Explorer", "Word" ) == 2 );
	assert( c.getUsersCountWithBrowsersAndOffice( "Netscape", "OpenOffice" ) == 2 );
	assert( c.getUsersCountWithBrowsersAndOffice( "Internet Explorer", "OpenOffice" ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_accounts_with_older_office_version )
{
	Controller c;

	createCommonConfiguration( c );

	auto recievedLogins = c.getUsersPreferringOlderOfficeVersion();
	auto expectedLogins = std::vector< std::string >{ "second", "third", "fifth" };

	std::sort( recievedLogins.begin(), recievedLogins.end() );
	std::sort( expectedLogins.begin(), expectedLogins.end() );

	assert( expectedLogins == recievedLogins );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_print_programs_without_preferences )
{
	Controller c;

	createCommonConfiguration( c );

	auto recievedLogins = c.getProgramsWithoutPreferences();
	auto expectedLogins = std::vector< std::pair< std::string, std::string > > {
			std::make_pair( "Firefox", "1.0" )
		,	std::make_pair( "Firefox", "1.5" )
		,	std::make_pair( "Pidguin", "5.0" )
		,	std::make_pair( "LibreOffice", "1.2" )
		,	std::make_pair( "LibreOffice", "1.4" )
	};

	std::sort( recievedLogins.begin(), recievedLogins.end() );
	std::sort( expectedLogins.begin(), expectedLogins.end() );

	assert( expectedLogins == recievedLogins );
}


/*****************************************************************************/