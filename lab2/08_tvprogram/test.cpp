// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "day.hpp"
#include "time.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_1_1_add_channel_one )
{
	Controller c;
	c.addChannel( "elephant" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_1_2_add_channel_severals )
{
	Controller c;
	c.addChannel( "elephant" );
	c.addChannel( "rabbit" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_1_3_add_channel_with_the_same_name )
{
	Controller c;
	c.addChannel( "news" );

	ASSERT_THROWS(
			c.addChannel( "news" );
		,	Messages::DuplicateChannel
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_1_4_add_channel_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addChannel( "" );
		,	Messages::EmptyChannelName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_1_add_program_one )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Monday, "cartoons", Time( 7, 0, 0 ), Genre::Series, 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_2_add_program_several )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Monday, "cartoons", Time( 7, 0, 0 ), Genre::Series, 4 );
	c.addProgram( "test", Day::Tuesday, "news", Time( 7, 0, 0 ), Genre::Information, 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_3_add_program_with_bad_day_index )
{
	Controller c;
	c.addChannel( "test" );

	ASSERT_THROWS(
			c.addProgram( "test", Day::Count, "cartoons", Time( 7, 0, 0 ), Genre::Series, 4 );
		,	Messages::InvalidDayIndex
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_4_add_program_with_empty_program_name )
{
	Controller c;
	c.addChannel( "test" );

	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "", Time( 15, 34, 1 ), Genre::Series, 4 );
		,	Messages::EmptyProgramName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_5_1_add_program_with_bad_time_time_is_earlier_than_previous_program )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Monday, "program #1", Time( 15, 0, 0 ), Genre::Sport, 1 );

	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #2", Time( 14, 0, 0 ), Genre::Show, 5 );
		,	Messages::InvalidProgramTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_5_2_add_program_for_previous_programs_day )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Tuesday, "program #1", Time( 15, 0, 0 ), Genre::Series, 3 );

	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #2", Time( 16, 0, 0 ), Genre::Movie, 2 );
		,	Messages::InvalidProgramTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_5_3_add_program_with_bad_time_the_same_day_for_the_previous_weeks_day )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Tuesday, "program #1", Time( 16, 0, 0 ), Genre::Series, 3 );

	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #2", Time( 15, 0, 0 ), Genre::Movie, 2 );
		,	Messages::InvalidProgramTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_5_4_add_program_with_bad_time_the_same_time_as_previous_program )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Monday, "program #1", Time( 15, 0, 0 ), Genre::Series, 2 );

	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #2", Time( 15, 0, 0 ), Genre::Movie, 2 );
		,	Messages::InvalidProgramTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_6_add_program_with_bad_rating )
{
	Controller c;
	c.addChannel( "test" );

	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #69", Time( 0, 0, 0 ), Genre::Other, -5 );
		,	Messages::InvalidRatingValue
	);
	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #69", Time( 0, 0, 0 ), Genre::Other, 0 );
		,	Messages::InvalidRatingValue
	);
	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #69", Time( 0, 0, 0 ), Genre::Other, 6 );
		,	Messages::InvalidRatingValue
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_7_add_program_programs_on_different_channels_with_the_same_time )
{
	Controller c;
	c.addChannel( "channel #1" );
	c.addChannel( "channel #2" );

	c.addProgram( "channel #1", Day::Monday, "program #1", Time( 0, 0, 0 ), Genre::Other, 1 );
	c.addProgram( "channel #2", Day::Monday, "program #2", Time( 0, 0, 0 ), Genre::Other, 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_8_add_program_programs_on_different_channels_with_the_same_name )
{
	Controller c;
	c.addChannel( "channel #1" );
	c.addChannel( "channel #2" );

	c.addProgram( "channel #1", Day::Monday, "program", Time( 1, 0, 0 ), Genre::Movie, 2 );
	c.addProgram( "channel #2", Day::Monday, "program", Time( 2, 0, 0 ), Genre::Series, 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_9_add_program_with_the_same_name )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Monday, "news", Time( 7, 0, 0 ), Genre::Information, 3 );
	c.addProgram( "test", Day::Monday, "news", Time( 8, 0, 0 ), Genre::Information, 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_10_add_program_with_empty_channel_name )
{
	Controller c;
	c.addChannel( "test" );

	ASSERT_THROWS(
			c.addProgram( "", Day::Monday, "program", Time( 0, 0, 0 ), Genre::Other, 1 );
		,	Messages::ChannelCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_11_add_program_for_missing_name )
{
	Controller c;
	c.addChannel( "test" );

	ASSERT_THROWS(
			c.addProgram( "other", Day::Monday, "program", Time( 0, 0, 0 ), Genre::Other, 1 );
		,	Messages::ChannelCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_12_add_program_when_previous_channels_are_empty )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Sunday, "program", Time( 0, 0, 0 ), Genre::Other, 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_13_add_program_to_the_last_day_after_added_to_first_day_some_time )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Monday, "program #69", Time( 23, 50, 0 ), Genre::Other, 5 );
	c.addProgram( "test", Day::Sunday, "program #69", Time( 23, 50, 0 ), Genre::Other, 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_2_14_add_program_to_the_first_day_with_bad_date_when_other_program_added_to_the_last_day )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Sunday, "program #69", Time( 23, 50, 0 ), Genre::Other, 5 );

	// NOTE: We add program with "12" day, but the first day of week is "11" day.
	// NOTE: It was calculated relatively to existing program.
	ASSERT_THROWS(
			c.addProgram( "test", Day::Monday, "program #69", Time( 23, 50, 0 ), Genre::Other, 5 );
		,	Messages::InvalidProgramTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_3_1_get_programs_by_day_empty_programs_list )
{
	Controller c;
	c.addChannel( "test" );

	std::vector< std::string > empty;
	assert( c.getPrograms( "test", Day::Monday ) == empty );
	assert( c.getPrograms( "test", Day::Tuesday ) == empty );
	assert( c.getPrograms( "test", Day::Wednesday ) == empty );
	assert( c.getPrograms( "test", Day::Thursday ) == empty );
	assert( c.getPrograms( "test", Day::Friday ) == empty );
	assert( c.getPrograms( "test", Day::Saturday ) == empty );
	assert( c.getPrograms( "test", Day::Sunday ) == empty );
}

/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_3_2_get_programs_by_day_only_one_program )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Friday, "program", Time( 23, 50, 0 ), Genre::Other, 5 );

	std::vector< std::string > empty;
	std::vector< std::string > day4 = { "program" };
	assert( c.getPrograms( "test", Day::Monday ) == empty );
	assert( c.getPrograms( "test", Day::Tuesday ) == empty );
	assert( c.getPrograms( "test", Day::Wednesday ) == empty );
	assert( c.getPrograms( "test", Day::Thursday ) == empty );
	assert( c.getPrograms( "test", Day::Friday ) == day4 );
	assert( c.getPrograms( "test", Day::Saturday ) == empty );
	assert( c.getPrograms( "test", Day::Sunday ) == empty );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_3_3_get_programs_by_day_several_programs )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Wednesday, "small",   Time( 12, 50, 0 ), Genre::Movie, 4 );
	c.addProgram( "test", Day::Friday, "program #1", Time( 23, 50, 0 ), Genre::Other, 5 );
	c.addProgram( "test", Day::Friday, "program #3", Time( 23, 51, 0 ), Genre::Other, 3 );

	std::vector< std::string > empty;
	std::vector< std::string > day2 = { "small" };
	std::vector< std::string > day4 = { "program #1", "program #3" };
	assert( c.getPrograms( "test", Day::Monday ) == empty );
	assert( c.getPrograms( "test", Day::Tuesday ) == empty );
	assert( c.getPrograms( "test", Day::Wednesday ) == day2 );
	assert( c.getPrograms( "test", Day::Thursday ) == empty );
	assert( c.getPrograms( "test", Day::Friday ) == day4 );
	assert( c.getPrograms( "test", Day::Saturday ) == empty );
	assert( c.getPrograms( "test", Day::Sunday ) == empty );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_3_4_get_programs_by_day_with_bad_day_index )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Wednesday, "small", Time( 12, 50, 0 ), Genre::Movie, 4 );
	c.addProgram( "test", Day::Friday, "program #1", Time( 23, 50, 0 ), Genre::Other, 5 );
	c.addProgram( "test", Day::Friday, "program #3", Time(23, 51, 0 ),  Genre::Other, 3 );

	ASSERT_THROWS(
			c.getPrograms( "test", Day::Count );
		,	Messages::InvalidDayIndex
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_3_5_get_programs_by_day_with_empty_channel_name )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Wednesday, "small", Time( 12, 50, 0 ), Genre::Movie, 4 );
	c.addProgram( "test", Day::Friday, "program #1", Time( 23, 50, 0 ), Genre::Other, 5 );
	c.addProgram( "test", Day::Friday, "program #3", Time( 23, 51, 0 ), Genre::Other, 3 );

	ASSERT_THROWS(
			c.getPrograms( "", Day::Friday );
		,	Messages::ChannelCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_3_6_get_programs_by_day_for_missing_channel )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Wednesday, "small", Time( 12, 50, 0 ), Genre::Movie, 4 );
	c.addProgram( "test", Day::Friday, "program #1", Time( 23, 50, 0 ), Genre::Other, 5 );
	c.addProgram( "test", Day::Friday, "program #3", Time( 23, 51, 0 ), Genre::Other, 3 );

	ASSERT_THROWS(
			c.getPrograms( "other", Day::Friday );
		,	Messages::ChannelCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_4_1_get_week_programs_empty_programs_list )
{
	Controller c;
	c.addChannel( "test" );

	std::vector< std::vector< std::string > > expectation =
	{
			{}
		,	{}
		,	{}
		,	{}
		,	{}
		,	{}
		,	{}
	};
	assert( c.getPrograms( "test" ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_4_2_get_week_programs_only_one_day )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Sunday, "program #1", Time( 23, 50, 0 ), Genre::Movie, 5 );
	c.addProgram( "test", Day::Sunday, "program #2", Time( 23, 51, 0 ), Genre::Movie, 5 );
	c.addProgram( "test", Day::Sunday, "program #3", Time( 23, 52, 0 ), Genre::Movie, 5 );

	std::vector< std::vector< std::string > > expectation =
	{
			{}
		,	{}
		,	{}
		,	{}
		,	{}
		,	{}
		,	{ "program #1", "program #2", "program #3" }
	};
	assert( c.getPrograms( "test" ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_4_3_get_week_programs_empty_day_between_filled_days )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Tuesday, "program #1",  Time( 23, 50, 0 ), Genre::Movie, 1 );
	c.addProgram( "test", Day::Tuesday, "program #2",  Time( 23, 51, 0 ), Genre::Series, 5 );
	c.addProgram( "test", Day::Saturday, "program #3", Time( 23, 50, 0 ), Genre::Show, 3 );
	c.addProgram( "test", Day::Saturday, "program #4", Time( 23, 51, 0 ), Genre::Sport, 4 );
	c.addProgram( "test", Day::Saturday, "program #5", Time( 23, 52, 0 ), Genre::Information, 5 );
	c.addProgram( "test", Day::Saturday, "program #6", Time( 23, 53, 0 ), Genre::Other, 2 );
	c.addProgram( "test", Day::Sunday, "program #7",   Time( 23, 50, 0 ), Genre::Show, 2 );
	c.addProgram( "test", Day::Sunday, "program #8",   Time( 23, 51, 0 ), Genre::Series, 3 );
	c.addProgram( "test", Day::Sunday, "program #9",   Time( 23, 52, 0 ), Genre::Series, 5 );

	std::vector< std::vector< std::string > > expectation =
	{
			{}
		,	{ "program #1", "program #2" }
		,	{}
		,	{}
		,	{}
		,	{ "program #3", "program #4", "program #5", "program #6" }
		,	{ "program #7", "program #8", "program #9" }
	};
	assert( c.getPrograms( "test" ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_4_4_get_week_programs_full_week )
{
	Controller c;
	c.addChannel( "test" );
	c.addProgram( "test", Day::Monday, "program #1",	Time( 23, 50, 0 ), Genre::Movie, 1 );
	c.addProgram( "test", Day::Tuesday, "program #2",	Time( 23, 50, 0 ), Genre::Movie, 1 );
	c.addProgram( "test", Day::Tuesday, "program #3",	Time( 23, 51, 0 ), Genre::Series, 5 );
	c.addProgram( "test", Day::Wednesday, "program #4", Time( 23, 50, 0 ), Genre::Movie, 1 );
	c.addProgram( "test", Day::Wednesday, "program #5", Time( 23, 51, 0 ), Genre::Series, 5 );
	c.addProgram( "test", Day::Thursday, "program #6",	Time( 23, 50, 0 ), Genre::Show, 3 );
	c.addProgram( "test", Day::Friday, "program #7",	Time( 23, 50, 0 ), Genre::Show, 2 );
	c.addProgram( "test", Day::Friday, "program #8",	Time( 23, 51, 0 ), Genre::Series, 3 );
	c.addProgram( "test", Day::Friday, "program #9",	Time( 23, 52, 0 ), Genre::Sport, 5 );
	c.addProgram( "test", Day::Saturday, "program #10", Time( 23, 50, 0 ), Genre::Show, 3 );
	c.addProgram( "test", Day::Saturday, "program #11", Time( 23, 51, 0 ), Genre::Sport, 4 );
	c.addProgram( "test", Day::Saturday, "program #12", Time( 23, 52, 0 ), Genre::Information, 5 );
	c.addProgram( "test", Day::Saturday, "program #13", Time( 23, 53, 0 ), Genre::Other, 2 );
	c.addProgram( "test", Day::Sunday, "program #14",	Time( 23, 50, 0 ), Genre::Show, 2 );
	c.addProgram( "test", Day::Sunday, "program #15",	Time( 23, 51, 0 ), Genre::Sport, 3 );
	c.addProgram( "test", Day::Sunday, "program #16",	Time( 23, 52, 0 ), Genre::Series, 5 );

	std::vector< std::vector< std::string > > expectation =
	{
			{ "program #1" }
		,	{ "program #2", "program #3" }
		,	{ "program #4", "program #5" }
		,	{ "program #6" }
		,	{ "program #7", "program #8", "program #9" }
		,	{ "program #10", "program #11", "program #12", "program #13" }
		,	{ "program #14", "program #15", "program #16" }
	};
	assert( c.getPrograms( "test" ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_4_5_get_week_programs_with_empty_channel_name )
{
	Controller c;
	c.addChannel( "test" );

	ASSERT_THROWS(
			c.getPrograms( "" );
		,	Messages::ChannelCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_4_6_get_week_programs_for_missing_channel )
{
	Controller c;
	c.addChannel( "test" );

	ASSERT_THROWS(
			c.getPrograms( "other" );
		,	Messages::ChannelCannotBeFound
	);
}


/*****************************************************************************/


void generateModel( Controller & _c )
{
	_c.addChannel( "News 24/7" );
	_c.addChannel( "Discovery" );
	_c.addChannel( "IT" );

	const int firstDay = 11;

	for ( int i = 0; i < static_cast< int >( Day::Count ); ++i )
	{
		Day day = static_cast< Day >( i );

		_c.addProgram( "News 24/7", day, "News #1", Time( 3, 0, 0 ), Genre::Information, 3 );
		_c.addProgram( "News 24/7", day, "News #2", Time( 7, 0, 0 ), Genre::Information, 3 );
		_c.addProgram( "News 24/7", day, "Sport News #1", Time( 11, 0, 0 ), Genre::Sport, 4 );
		_c.addProgram( "News 24/7", day, "News #4", Time( 15, 0, 0 ), Genre::Information, 4 );
		_c.addProgram( "News 24/7", day, "Sport News #2", Time( 19, 0, 0 ), Genre::Sport, 3 );
		_c.addProgram( "News 24/7", day, "News #5", Time( 22, 0, 0 ), Genre::Show, 4 );
	}

	for ( int i = 0; i < static_cast< int >( Day::Count ); ++i )
	{
		Day day = static_cast< Day >( i );

		_c.addProgram( "Discovery", day, "How to eat monkeys", Time( 3, 0, 0 ), Genre::Show, 5 );
		_c.addProgram( "Discovery", day, "Safari run", Time( 7, 0, 0 ), Genre::Other, 4 );
		_c.addProgram( "Discovery", day, "Epic destination", Time( 11, 0, 0 ), Genre::Movie, 4 );
		_c.addProgram( "Discovery", day, "Cats and dogs", Time( 15, 0, 0 ), Genre::Other, 5 );
		_c.addProgram( "Discovery", day, "Do not watch us", Time( 19, 0, 0 ), Genre::Other, 4 );

		if ( day == Day::Saturday )
			_c.addProgram( "Discovery", day, "How to train your QA", Time( 19, 30, 0 ), Genre::Show, 5 );
		else
			_c.addProgram( "Discovery",day, "Holy evening", Time( 21, 0, 0 ), Genre::Other, 4 );
	}

	for ( int i = 0; i < static_cast< int >( Day::Count ); ++i )
	{
		Day day = static_cast< Day >( i );

		_c.addProgram( "IT", day, "Teach yourself C++ in 21 days", Time( 3, 0, 0 ), Genre::Information, 1 );
		_c.addProgram( "IT", day, "Clouds and Fogs", Time( 7, 0, 0 ), Genre::Information, 5 );
		_c.addProgram( "IT", day, "Java vs C#", Time( 11, 0, 0 ), Genre::Information, 4 );
		_c.addProgram( "IT", day, "Why we need QA?", Time( 15, 0, 0 ), Genre::Information, 5 );
		_c.addProgram( "IT", day, "Agile", Time( 19, 0, 0 ), Genre::Information, 5 );
		_c.addProgram( "IT", day, "VCS", Time( 21, 0, 0 ), Genre::Series, 4 );
	}
	_c.addProgram( "IT", Day::Friday, "Pizza & Beer", Time( 22, 0, 0 ), Genre::Sport, 5 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_5_1_queries_get_all_sport_programs )
{
	Controller c;
	generateModel( c );

	// NOTE: Programs were sorted in alphabetical order
	std::vector< std::string > expectation =
	{
			"Pizza & Beer"
		,	"Sport News #1"
		,	"Sport News #2"
	};
	assert( c.getAllSportPrograms() == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_5_2_queries_get_channel_with_highest_average_rating )
{
	Controller c;
	generateModel( c );

	assert( c.getChannelWithHighestAverageRating() == "Discovery" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_5_3_queries_get_longest_program )
{
	Controller c;
	generateModel( c );

	assert( c.getLongestProgram() == "How to train your QA" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( tvprogram_5_4_queries_get_best_program_choise_for )
{
	Controller c;
	generateModel( c );

	typedef
		std::pair< std::string, std::string >
		Result;

	Result expectation1 = std::make_pair( "Discovery", "How to eat monkeys" );
	Result result1 = c.getBestProgramChoiceFor( Day::Monday, 2 );
	assert( result1 == expectation1 );

	Result expectation2 = std::make_pair( "IT", "Pizza & Beer" );
	Result result2 = c.getBestProgramChoiceFor( Day::Friday, 22 );
	assert( result2 == expectation2 );

	Result expectation3 = std::make_pair( "Discovery", "How to train your QA" );
	Result result3 = c.getBestProgramChoiceFor( Day::Saturday, 19 );
	assert( result3 == expectation3 );

	Result expectation4 = std::make_pair( "IT", "Agile" );
	Result result4 = c.getBestProgramChoiceFor( Day::Sunday, 19 );
	assert( result4 == expectation4 );

	Result expectation5 = std::make_pair( "News 24/7", "Sport News #1" );
	Result result5 = c.getBestProgramChoiceFor( Day::Wednesday, 11 );
	assert( result5 == expectation5 );
}


/*****************************************************************************/
