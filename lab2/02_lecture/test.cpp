// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_lecture_check_properties )
{
	Controller c;
	c.createLecture( "Ivan Ivanov", "Math", "Derivatives" );

	assert( c.getLectureInstructorName( "Derivatives" ) == "Ivan Ivanov" );
	assert( c.getLectureDisciplineName( "Derivatives" ) == "Math" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_several_lectures_check_properties )
{
	Controller c;
	c.createLecture( "Ivan Ivanov", "Math", "Derivatives" );
	c.createLecture( "Ivan Ivanov", "Math", "Integrals"   );
	c.createLecture( "Ivan Ivanov", "Programming", "C++ Loops" );
	c.createLecture( "Petr Petrov", "Math", "Matrices multiplication" );

	assert( c.getLectureInstructorName( "Derivatives" ) == "Ivan Ivanov" );
	assert( c.getLectureDisciplineName( "Derivatives" ) == "Math" );

	assert( c.getLectureInstructorName( "Integrals" ) == "Ivan Ivanov" );
	assert( c.getLectureDisciplineName( "Integrals" ) == "Math" );

	assert( c.getLectureInstructorName( "C++ Loops" ) == "Ivan Ivanov" );
	assert( c.getLectureDisciplineName( "C++ Loops" ) == "Programming" );

	assert( c.getLectureInstructorName( "Matrices multiplication" ) == "Petr Petrov" );
	assert( c.getLectureDisciplineName( "Matrices multiplication" ) == "Math" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_lecture_with_empty_fields_forbidden )
{
	Controller c;

	ASSERT_THROWS(
		c.createLecture( "", "Math", "Derivatives" ),
		Messages::InstructorNameEmpty
	);

	ASSERT_THROWS(
		c.createLecture( "Ivan Ivanov", "", "Derivatives" ),
		Messages::DisciplineNameEmpty
	);

	ASSERT_THROWS(
		c.createLecture( "Ivan Ivanov", "Math", "" ),
		Messages::TopicNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_lecture_with_duplicate_main_topic_forbidden )
{
	Controller c;
	c.createLecture( "Ivanov", "Math", "Integrals" );

	ASSERT_THROWS(
		c.createLecture( "Ivanov", "Math", "Integrals" ),
		Messages::MainTopicDuplication
	);

	ASSERT_THROWS(
		c.createLecture( "Petrov", "Math", "Integrals" ),
		Messages::MainTopicDuplication
	);

	ASSERT_THROWS(
		c.createLecture( "Ivanov", "Physics", "Integrals" ),
		Messages::MainTopicDuplication
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_view_subtopics_when_empty )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "C++ Loops" );

	std::vector< std::string > expectedTopics{ /* empty */ };
	assert( c.getSubtopicNames( { "C++ Loops" } ) == expectedTopics );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_single_subtopic )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "C++ Loops" );
	c.addTopic( { "C++ Loops" }, "for loop" );

	std::vector< std::string > expectedTopics{ "for loop" };
	assert( c.getSubtopicNames( { "C++ Loops" } ) == expectedTopics );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_several_subtopics_view_sorted_names )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "C++ Loops" );
	c.addTopic( { "C++ Loops" }, "for loop" );
	c.addTopic( { "C++ Loops" }, "while loop" );
	c.addTopic( { "C++ Loops" }, "do-while loop" );
	c.addTopic( { "C++ Loops" }, "ranged for loop" );

	std::vector< std::string > expectedTopics{ "do-while loop", "for loop", "ranged for loop", "while loop" };
	assert( c.getSubtopicNames( { "C++ Loops" } ) == expectedTopics );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_duplicate_subtopics_forbidden )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "C++ Loops" );
	c.addTopic( { "C++ Loops" }, "for loop" );

	ASSERT_THROWS(
		c.addTopic( { "C++ Loops" }, "for loop" ),
		Messages::SubtopicExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_identical_subtopics_to_different_lectures )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "C++ Loops" );
	c.addTopic( { "C++ Loops" }, "for loop" );

	c.createLecture( "Ivanov", "Programming", "Java Loops" );
	c.addTopic( { "Java Loops" }, "for loop" );

	std::vector< std::string > expectedTopics{ "for loop" };
	assert( c.getSubtopicNames( { "C++ Loops" } ) == expectedTopics );
	assert( c.getSubtopicNames( { "Java Loops" } ) == expectedTopics );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_add_two_levels_of_topics )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "OOP Basics" );
	c.addTopic( { "OOP Basics" }, "Decomposition" );
	c.addTopic( { "OOP Basics", "Decomposition" }, "Functional Decomposition" );
	c.addTopic( { "OOP Basics", "Decomposition" }, "Object-Oriented Decomposition" );
	c.addTopic( { "OOP Basics" }, "Classes" );
	c.addTopic( { "OOP Basics", "Classes" }, "Declaring Class" );
	c.addTopic( { "OOP Basics", "Classes" }, "Allocating Objects" );

	std::vector< std::string > expectedSub{ "Classes", "Decomposition" };
	assert( c.getSubtopicNames( { "OOP Basics" } ) == expectedSub );

	std::vector< std::string > expectsSubSub1{ "Functional Decomposition", "Object-Oriented Decomposition" };
	assert( c.getSubtopicNames( { "OOP Basics", "Decomposition" } ) == expectsSubSub1 );

	std::vector< std::string > expectsSubSub2{ "Allocating Objects", "Declaring Class" };
	assert( c.getSubtopicNames( { "OOP Basics", "Classes" } ) == expectsSubSub2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_zero_slides_by_default )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "Topic" );
	c.addTopic( { "Topic" }, "Subtopic" );

	assert( c.getTopicTotalSlidesCount( { "Topic" } ) == 0 );
	assert( c.getTopicOwnSlidesCount(   { "Topic" } ) == 0 );

	assert( c.getTopicTotalSlidesCount( { "Topic", "Subtopic" } ) == 0 );
	assert( c.getTopicOwnSlidesCount( { "Topic", "Subtopic" } ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_set_main_topic_slides_count )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "Topic" );
	c.addTopic( { "Topic" }, "Subtopic" );
	c.setTopicSlidesCount( { "Topic" }, 5 );

	assert( c.getTopicTotalSlidesCount( { "Topic" } ) == 5 );
	assert( c.getTopicOwnSlidesCount( { "Topic" } ) == 5 );

	assert( c.getTopicTotalSlidesCount( { "Topic", "Subtopic" } ) == 0 );
	assert( c.getTopicOwnSlidesCount( { "Topic", "Subtopic" } ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_set_subtopic_slides_count )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "Topic" );
	c.addTopic( { "Topic" }, "Subtopic1" );
	c.addTopic( { "Topic" }, "Subtopic2" );
	c.setTopicSlidesCount( { "Topic", "Subtopic1" }, 3 );
	c.setTopicSlidesCount( { "Topic", "Subtopic2" }, 6 );

	assert( c.getTopicTotalSlidesCount( { "Topic" } ) == 9 );
	assert( c.getTopicOwnSlidesCount( { "Topic" } ) == 0 );

	assert( c.getTopicTotalSlidesCount( { "Topic", "Subtopic1" } ) == 3 );
	assert( c.getTopicOwnSlidesCount( { "Topic", "Subtopic1" } ) == 3 );

	assert( c.getTopicTotalSlidesCount( { "Topic", "Subtopic2" } ) == 6 );
	assert( c.getTopicOwnSlidesCount( { "Topic", "Subtopic2" } ) == 6 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_set_both_topic_and_subtopic_slides_count )
{
	Controller c;
	c.createLecture( "Ivanov", "Programming", "Topic" );
	c.addTopic( { "Topic" }, "Subtopic1" );
	c.addTopic( { "Topic" }, "Subtopic2" );
	c.setTopicSlidesCount( { "Topic" }, 7 );
	c.setTopicSlidesCount( { "Topic", "Subtopic1" }, 3 );
	c.setTopicSlidesCount( { "Topic", "Subtopic2" }, 6 );

	assert( c.getTopicTotalSlidesCount( { "Topic" } ) == 16 );
	assert( c.getTopicOwnSlidesCount( { "Topic" } ) == 7 );

	assert( c.getTopicTotalSlidesCount( { "Topic", "Subtopic1" } ) == 3 );
	assert( c.getTopicOwnSlidesCount( { "Topic", "Subtopic1" } ) == 3 );

	assert( c.getTopicTotalSlidesCount( { "Topic", "Subtopic2" } ) == 6 );
	assert( c.getTopicOwnSlidesCount( { "Topic", "Subtopic2" } ) == 6 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_largest_lecture_when_empty )
{
	Controller c;
	assert( c.findLargestLecture() == "" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_largest_lecture_when_only_one )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "CCC" );
	assert( c.findLargestLecture() == "CCC" );
	
	c.setTopicSlidesCount( { "CCC" }, 3 );
	assert( c.findLargestLecture() == "CCC" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_largest_between_unequal_flat )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Lec1" );
	c.createLecture( "AAA", "BBB", "Lec2" );
	c.createLecture( "AAA", "BBB", "Lec3" );
	
	c.setTopicSlidesCount( { "Lec1" }, 3 );
	c.setTopicSlidesCount( { "Lec2" }, 5 );
	c.setTopicSlidesCount( { "Lec3" }, 2 );

	assert( c.findLargestLecture() == "Lec2" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_largest_between_equal_flat_choose_by_alhabet )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Lec1" );
	c.createLecture( "AAA", "BBB", "Lec2" );

	c.setTopicSlidesCount( { "Lec2" }, 3 );
	c.setTopicSlidesCount( { "Lec1" }, 3 );

	assert( c.findLargestLecture() == "Lec1" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_largest_between_unequal_hierarchical )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Lec1" );  // 3 + 5 = 8
	c.addTopic( { "Lec1" }, "Sub11" );
	c.setTopicSlidesCount( { "Lec1", "Sub11" }, 3 );
	c.addTopic( { "Lec1" }, "Sub12" );
	c.setTopicSlidesCount( { "Lec1", "Sub12" }, 5 );

	c.createLecture( "AAA", "BBB", "Lec2" ); // 2 + 4 + 6 = 12
	c.setTopicSlidesCount( { "Lec2" }, 2 );
	c.addTopic( { "Lec2" }, "Sub21" );
	c.setTopicSlidesCount( { "Lec2", "Sub21" }, 4 );
	c.addTopic( { "Lec2" }, "Sub22" );
	c.setTopicSlidesCount( { "Lec2", "Sub22" }, 6 );

	assert( c.findLargestLecture() == "Lec2" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_largest_between_equal_hierarchical_choose_by_alhabet )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Lec1" );  // 4 + 3 + 5 = 12
	c.setTopicSlidesCount( { "Lec1" }, 4 );
	c.addTopic( { "Lec1" }, "Sub11" );
	c.setTopicSlidesCount( { "Lec1", "Sub11" }, 3 );
	c.addTopic( { "Lec1" }, "Sub12" );
	c.setTopicSlidesCount( { "Lec1", "Sub12" }, 5 );

	c.createLecture( "AAA", "BBB", "Lec2" ); // 2 + 4 + 6 = 12
	c.setTopicSlidesCount( { "Lec2" }, 2 );
	c.addTopic( { "Lec2" }, "Sub21" );
	c.setTopicSlidesCount( { "Lec2", "Sub21" }, 4 );
	c.addTopic( { "Lec2" }, "Sub22" );
	c.setTopicSlidesCount( { "Lec2", "Sub22" }, 6 );

	assert( c.findLargestLecture() == "Lec1" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_detect_empty_when_no_lectures )
{
	Controller c;
	assert( c.detectEmptyLectures().empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_detect_empty_when_one_empty )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "CCC" );
	assert( c.detectEmptyLectures() == std::vector< std::string >{ "CCC" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_detect_empty_when_one_of_three_empty )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Lec1" );
	c.createLecture( "AAA", "BBB", "Lec2" );
	c.createLecture( "AAA", "BBB", "Lec3" );

	c.setTopicSlidesCount( { "Lec1" }, 2 );
	c.setTopicSlidesCount( { "Lec2" }, 3 );

	assert( c.detectEmptyLectures() == std::vector< std::string >{ "Lec3" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_find_lecture_by_keyword_when_no_match_fails )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Flowers" );
	c.createLecture( "AAA", "BBB", "Animals" );

	assert( c.findLecturesByKeyword( "Birds" ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_find_lecture_by_keyword_when_matches_at_main_topic )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Defining Testplan" );
	c.createLecture( "AAA", "BBB", "Tests Automation" );
	c.createLecture( "AAA", "BBB", "Running Tests" );

	std::vector< std::string > expectedResults{ "Running Tests", "Tests Automation"  };
	assert( c.findLecturesByKeyword( "Tests" ) == expectedResults );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_find_lecture_by_keyword_when_matches_at_deeper_level )
{
	Controller c;
	c.createLecture( "AAA", "BBB", "Lecture 1" );
	c.addTopic( { "Lecture 1" }, "Subtopic" );
	c.addTopic( { "Lecture 1", "Subtopic" }, "Key 2nd-level topic" );
	c.createLecture( "AAA", "BBB", "Lecture 2" );
	c.addTopic( { "Lecture 2" }, "Unrelated topic" );
	c.createLecture( "AAA", "BBB", "Lecture 3" );
	c.addTopic( { "Lecture 3" }, "Another Key topic" );

	std::vector< std::string > expectedResults{ "Lecture 1", "Lecture 3" };
	assert( c.findLecturesByKeyword( "Key" ) == expectedResults );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_lectures_count_per_discipline )
{
	Controller c;
	c.createLecture( "Ivanov", "Math", "Linear Programming" );
	c.createLecture( "Ivanov", "Math", "Gauss Method" );
	c.createLecture( "Ivanov", "Physics", "Newton's Laws" );

	assert( c.getLecturesCountForDiscipline( "Math" ) == 2 );
	assert( c.getLecturesCountForDiscipline( "Physics" ) == 1 );
	assert( c.getLecturesCountForDiscipline( "Chemistry" ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_lectures_count_empty_discipline_name )
{
	Controller c;
	
	ASSERT_THROWS(
		c.getLecturesCountForDiscipline( "" ),
		Messages::DisciplineNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_instructor_disciplines_simple_case )
{
	Controller c;
	c.createLecture( "Ivanov", "Math", "Linear Programming" );
	c.createLecture( "Ivanov", "Math", "Raphson Method" );
	c.createLecture( "Petrov", "Math", "Gauss Method" );
	c.createLecture( "Ivanov", "Physics", "Newton's Laws" );

	std::vector< std::string > expectedResults1{ "Math", "Physics" };
	assert( c.getInstructorDisciplines( "Ivanov" ) == expectedResults1 );

	std::vector< std::string > expectedResults2{ "Math" };
	assert( c.getInstructorDisciplines( "Petrov" ) == expectedResults2 );

	std::vector< std::string > expectedResults3{ };
	assert( c.getInstructorDisciplines( "Sidorov" ) == expectedResults3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_instructor_disciplines_empty_name )
{
	Controller c;
	ASSERT_THROWS(
		c.getInstructorDisciplines( "" ),
		Messages::InstructorNameEmpty
	);
}



/*****************************************************************************/
