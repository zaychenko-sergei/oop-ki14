// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

#include <limits>
#include <vector>

/*****************************************************************************/

int alive = std::numeric_limits< int >::max();

/*****************************************************************************/


void createCommonConfiguration ( Controller & c )
{
	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );
	c.addLeader( "Louis X", "King", 1289, 1316 );
	c.addLeader( "Philip V", "King", 1291, 1322 );
	c.addLeader( "Charles IV", "King", 1294, 1328 );

	c.addHistoryPeriod( "France", 1285, 1314, "Philip IV", 3000000 );
	c.addHistoryPeriod( "France", 1314, 1316, "Louis X", 3100000 );
	c.addHistoryPeriod( "France", 1316, 1322, "Philip V", 3200000 );
	c.addHistoryPeriod( "France", 1322, 1328, "Charles IV", 3300000 );

	c.addCountry( "England" );

	c.addLeader( "Edward I", "King", 1239, 1307 );
	c.addLeader( "Edward II", "King", 1284, 1327 );
	c.addLeader( "Edward III", "King", 1312, 1377 );

	c.addHistoryPeriod( "England", 1272, 1307, "Edward I", 2400000 );
	c.addHistoryPeriod( "England", 1307, 1327, "Edward II", 2450000 );
	c.addHistoryPeriod( "England", 1327, 1377, "Edward III", 3000000 );

	c.addCountry( "Germany" );

	c.addLeader( "Gerhard Schroder", "Chancellor", 1944, alive );
	c.addLeader( "Angela Merkel", "Chancellor", 1954, alive );

	c.addHistoryPeriod( "Germany", 1998, 2005, "Gerhard Schroder", 50000000 );
	c.addHistoryPeriod( "Germany", 2005, 2015, "Angela Merkel", 52000000 );

	c.addLeader( "Idi Amin", "President", 1928, 2003 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_leader_properties )
{
	Controller c;

	c.addLeader( "Angela Merkel", "Chancellor", 1954, alive );

	assert( c.getLeaderPosition( "Angela Merkel" ) == "Chancellor" );
	assert( c.getLeaderBirthDate( "Angela Merkel" )  == 1954 );
	assert( c.getLeaderDeathDate( "Angela Merkel" )  == alive );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_leader_with_empty_full_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addLeader( "", "Chancellor", 1954, alive )
		,	Messages::LeaderNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_leader_with_empty_position )
{
	Controller c;

	ASSERT_THROWS(
			c.addLeader( "Angela Merkel", "", 1954, alive )
		,	Messages::LeaderPositionIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_leader_with_negative_living_period )
{
	Controller c;

	ASSERT_THROWS(
			c.addLeader( "Angela Merkel", "Chancellor", alive, 1954 )
		,	Messages::LeaderUncorrectLivingYears
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_leader_on_bc_ad_edge )
{
	Controller c;

	c.addLeader( "Augustus", "Emperor", -63, 14 );

	assert( c.getLeaderPosition( "Augustus" ) == "Emperor" );
	assert( c.getLeaderBirthDate( "Augustus" )  == -63 );
	assert( c.getLeaderDeathDate( "Augustus" )  == 14 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_existing_leader )
{
	Controller c;

	c.addLeader( "Augustus", "Emperor", -63, 14 );

	ASSERT_THROWS(
			c.addLeader( "Augustus", "Emperor", 105, 142 )
		,	Messages::LeaderAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country )
{
	Controller c;

	c.addCountry( "England" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addCountry( "" )
		,	Messages::CountryNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_existing_name )
{
	Controller c;

	c.addCountry( "England" );

	ASSERT_THROWS(
			c.addCountry( "England" )
		,	Messages::CountryAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_period )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	c.addHistoryPeriod( "France", 1285, 1314, "Philip IV", 3000000 );

	assert( c.getHistoryPeriodsCount( "France" ) == 1 );
	assert( c.getHistoryPeriodPopulation( "France", "Philip IV", 1285 ) == 3000000 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_negative_period )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	ASSERT_THROWS(
			c.addHistoryPeriod( "France", 1314, 1285, "Philip IV", 3000000 )
		,	Messages::HistoryPeriodIsNegative
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_empty_country_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	ASSERT_THROWS(
			c.addHistoryPeriod( "", 1285, 1314, "Philip IV", 3000000 )
		,	Messages::CountryNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_empty_leader_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	ASSERT_THROWS(
			c.addHistoryPeriod( "France", 1285, 1314, "", 3000000 )
		,	Messages::LeaderNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_unexisting_country_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	ASSERT_THROWS(
			c.addHistoryPeriod( "England", 1285, 1314, "Philip IV", 3000000 )
		,	Messages::CountryDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_country_with_unexisting_leader_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	ASSERT_THROWS(
			c.addHistoryPeriod( "France", 1285, 1314, "Henry IV", 3000000 )
		,	Messages::LeaderDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_same_year_history_period )
{
	Controller c;

	c.addCountry( "Neverland" );

	c.addLeader( "Recruit", "Master", 1990, alive );

	c.addHistoryPeriod( "Neverland", 2, 2, "Recruit", 5 );

	assert( c.getHistoryPeriodsCount( "Neverland" ) == 1 );
	assert( c.getHistoryPeriodPopulation( "Neverland", "Recruit", 2 ) == 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_multiple_country_periods_with_same_leader )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	c.addHistoryPeriod( "France", 1284, 1285, "Philip IV", 2900000 );
	c.addHistoryPeriod( "France", 1285, 1314, "Philip IV", 3000000 );

	assert( c.getHistoryPeriodsCount( "France" ) == 2 );
	assert( c.getHistoryPeriodPopulation( "France", "Philip IV", 1284 ) == 2900000 );
	assert( c.getHistoryPeriodPopulation( "France", "Philip IV", 1285 ) == 3000000 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_population_query_with_empty_country_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	c.addHistoryPeriod( "France", 1285, 1314, "Philip IV", 3000000 );

	ASSERT_THROWS(
			c.getHistoryPeriodPopulation( "", "Philip IV", 1285 )
		,	Messages::CountryNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_population_query_with_unexisting_country_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	c.addHistoryPeriod( "France", 1285, 1314, "Philip IV", 3000000 );

	ASSERT_THROWS(
			c.getHistoryPeriodPopulation( "England", "Philip IV", 1285 )
		,	Messages::CountryDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_population_query_with_empty_leader_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	c.addHistoryPeriod( "France", 1285, 1314, "Philip IV", 3000000 );

	ASSERT_THROWS(
			c.getHistoryPeriodPopulation( "France", "", 1285 )
		,	Messages::LeaderNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_population_query_with_enexisting_leader_name )
{
	Controller c;

	c.addCountry( "France" );

	c.addLeader( "Philip IV", "King", 1268, 1314 );

	c.addHistoryPeriod( "France", 1285, 1314, "Philip IV", 3000000 );

	ASSERT_THROWS(
			c.getHistoryPeriodPopulation( "France", "Karl I", 1285 )
		,	Messages::LeaderDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_longest_running_country_names_query )
{
	Controller c;

	createCommonConfiguration( c );

	std::pair< std::string, std::string > expectedResult
		= std::make_pair( "Edward III", "England" );

	assert( expectedResult == c.getLongestRunningCountryLeader() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_biggest_population_percentage_growth_query )
{
	Controller c;

	createCommonConfiguration( c );

	std::pair< std::string, std::string > expectedResult
		= std::make_pair( "Edward III", "England" );

	assert( expectedResult == c.getCaseWithBiggestPopulationPercentageGrowth() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_country_with_most_leader_changes_during_last_50_years )
{
	Controller c;

	createCommonConfiguration( c );

	assert( c.getCountryWithMostFrequentLeaderChangesDuringLastYears( 50 ) == "Germany" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_country_with_most_leader_changes_during_last_1000_years )
{
	Controller c;

	createCommonConfiguration( c );

	assert( c.getCountryWithMostFrequentLeaderChangesDuringLastYears( 1000 ) == "France" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_leaders_that_are_not_chancellors )
{
	Controller c;

	createCommonConfiguration( c );

	auto expectedLeaders = std::vector< std::string >{
			"Philip IV"
		,	"Louis X"
		,	"Philip V"
		,	"Charles IV"
		,	"Edward I"
		,	"Edward II"
		,	"Edward III"
		,	"Idi Amin"
	};

	auto recievedLeaders = c.getCurrentLeadersNotCalled( "Chancellor" );

	std::sort( expectedLeaders.begin(), expectedLeaders.end() );
	std::sort( recievedLeaders.begin(), recievedLeaders.end() );

	assert( expectedLeaders == recievedLeaders );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_leaders_that_are_not_kings )
{
	Controller c;

	createCommonConfiguration( c );

	auto expectedLeaders = std::vector< std::string >{
			"Angela Merkel"
		,	"Gerhard Schroder"
		,	"Idi Amin"
	};

	auto recievedLeaders = c.getCurrentLeadersNotCalled( "King" );

	std::sort( expectedLeaders.begin(), expectedLeaders.end() );
	std::sort( recievedLeaders.begin(), recievedLeaders.end() );

	assert( expectedLeaders == recievedLeaders );
}


/*****************************************************************************/
