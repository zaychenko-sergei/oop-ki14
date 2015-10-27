// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_student_trace_properties )
{
	const int STUDENT_ID = 12345;

	Controller c;
	c.createStudent( STUDENT_ID, "Ivan Ivanov", "1995/05/01", StudyForm::Budget );

	assert( c.getStudentName( STUDENT_ID ) == "Ivan Ivanov" );
	assert( c.getStudentBirthday( STUDENT_ID ) == "1995/05/01" );
	assert( c.getStudentStudyForm( STUDENT_ID ) == StudyForm::Budget );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_students_trace_properties )
{
	const int STUDENT1_ID = 12345;
	const int STUDENT2_ID = 12346;

	Controller c;
	c.createStudent( STUDENT1_ID, "Ivan Ivanov", "1995/05/01", StudyForm::Budget );
	c.createStudent( STUDENT2_ID, "Petr Petrov", "1995/07/15", StudyForm::Contract );

	assert( c.getStudentName( STUDENT1_ID ) == "Ivan Ivanov" );
	assert( c.getStudentBirthday( STUDENT1_ID ) == "1995/05/01" );
	assert( c.getStudentStudyForm( STUDENT1_ID ) == StudyForm::Budget );

	assert( c.getStudentName( STUDENT2_ID ) == "Petr Petrov" );
	assert( c.getStudentBirthday( STUDENT2_ID ) == "1995/07/15" );
	assert( c.getStudentStudyForm( STUDENT2_ID ) == StudyForm::Contract );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_student_with_empty_name )
{
	const int STUDENT_ID = 12345;

	Controller c;

	ASSERT_THROWS(
		c.createStudent( STUDENT_ID, "", "1995/05/01", StudyForm::Budget ),
		Messages::InvalidStudentName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_student_with_bad_date )
{
	const int STUDENT_ID = 12345;

	Controller c;

	ASSERT_THROWS(
		c.createStudent( STUDENT_ID, "Ivan Ivanov", Date(), StudyForm::Budget ),
		Messages::StudentBirthdayTooLate
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_student_with_duplicate_id )
{
	const int STUDENT_ID = 12345;

	Controller c;
	c.createStudent( STUDENT_ID, "Ivan Ivanov", "1995/05/01", StudyForm::Budget );

	ASSERT_THROWS(
		c.createStudent( STUDENT_ID, "Petr Petrov", "1996/01/28", StudyForm::Budget ),
		Messages::StudentIdNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_query_unknown_student )
{
	const int STUDENT_ID = 12345;

	Controller c;
	ASSERT_THROWS( c.getStudentName( STUDENT_ID ),      Messages::StudentNotFound );
	ASSERT_THROWS( c.getStudentBirthday( STUDENT_ID ),  Messages::StudentNotFound );
	ASSERT_THROWS( c.getStudentStudyForm( STUDENT_ID ), Messages::StudentNotFound );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_group_trace_properties )
{
	const char * GROUP_NAME = "TEST-14-1";

	Controller c;
	c.createGroup( GROUP_NAME );

	assert( c.getStudentIdsOfGroup( GROUP_NAME ).empty() );
	assert( c.getGroupCaptainId( GROUP_NAME ) == -1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_groups_trace_properties )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";

	Controller c;
	c.createGroup( GROUP1_NAME );
	c.createGroup( GROUP2_NAME );

	assert( c.getStudentIdsOfGroup( GROUP1_NAME ).empty() );
	assert( c.getGroupCaptainId( GROUP1_NAME ) == -1 );

	assert( c.getStudentIdsOfGroup( GROUP2_NAME ).empty() );
	assert( c.getGroupCaptainId( GROUP2_NAME ) == -1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_group_empty_name )
{
	Controller c;
	ASSERT_THROWS( c.createGroup( "" ), Messages::InvalidGroupName );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_groups_with_duplicate_names )
{
	const char * GROUP_NAME = "TEST-14-1";

	Controller c;
	c.createGroup( GROUP_NAME );
	ASSERT_THROWS( c.createGroup( GROUP_NAME ), Messages::GroupNameNotUnique );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_traverse_empty_group )
{
	const char * GROUP_NAME = "TEST-14-1";

	Controller c;
	c.createGroup( GROUP_NAME );

	auto expectedIds = std::vector< int > {};
	assert( c.getStudentIdsOfGroup( GROUP_NAME ) == expectedIds );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_traverse_non_existing_group )
{
	const char * GROUP_NAME = "TEST-14-1";

	Controller c;

	ASSERT_THROWS(
			c.getStudentIdsOfGroup( GROUP_NAME )
		,	Messages::GroupNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_single_student_to_single_group )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT_ID = 12345;
	
	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.addStudentToGroup( STUDENT_ID, GROUP_NAME );

	auto expectedIds = std::vector< int >{ STUDENT_ID };
	assert( c.getStudentIdsOfGroup( GROUP_NAME ) == expectedIds );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_two_students_to_single_group )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT1_ID = 12345;
	const int STUDENT2_ID = 23456;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT1_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.createStudent( STUDENT2_ID, "Petrov", "1994/02/02", StudyForm::Contract );
	c.addStudentToGroup( STUDENT1_ID, GROUP_NAME );
	c.addStudentToGroup( STUDENT2_ID, GROUP_NAME );

	auto receivedIds = c.getStudentIdsOfGroup( GROUP_NAME );
	auto expectedIds = std::vector< int >{ STUDENT1_ID, STUDENT2_ID };
	std::sort( receivedIds.begin(), receivedIds.end() );
	assert( receivedIds == expectedIds );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_two_students_to_different_groups )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";
	const int STUDENT1_ID = 12345;
	const int STUDENT2_ID = 23456;

	Controller c;
	c.createGroup( GROUP1_NAME );
	c.createGroup( GROUP2_NAME );
	c.createStudent( STUDENT1_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.createStudent( STUDENT2_ID, "Petrov", "1994/02/02", StudyForm::Contract );
	c.addStudentToGroup( STUDENT1_ID, GROUP1_NAME );
	c.addStudentToGroup( STUDENT2_ID, GROUP2_NAME );

	auto expectedIds1 = std::vector< int >{ STUDENT1_ID };
	auto expectedIds2 = std::vector< int >{ STUDENT2_ID };
	assert( c.getStudentIdsOfGroup( GROUP1_NAME ) == expectedIds1 );
	assert( c.getStudentIdsOfGroup( GROUP2_NAME ) == expectedIds2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_student_to_two_groups_must_fail )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";
	const int STUDENT_ID = 12345;

	Controller c;
	c.createGroup( GROUP1_NAME );
	c.createGroup( GROUP2_NAME );
	c.createStudent( STUDENT_ID, "Ivanov", "1995/01/01", StudyForm::Budget );

	c.addStudentToGroup( STUDENT_ID, GROUP1_NAME );
	ASSERT_THROWS( 
		c.addStudentToGroup( STUDENT_ID, GROUP2_NAME ),
		Messages::StudentCannotStudyInTwoGroups
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_single_student_to_same_group_twice_ignored )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT_ID = 12345;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.addStudentToGroup( STUDENT_ID, GROUP_NAME );
	c.addStudentToGroup( STUDENT_ID, GROUP_NAME );

	auto expectedIds = std::vector< int >{ STUDENT_ID };
	assert( c.getStudentIdsOfGroup( GROUP_NAME ) == expectedIds );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_non_existing_student_or_group_fails )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";
	const int STUDENT_ID = 12345;

	Controller c;
	c.createGroup( GROUP1_NAME );

	ASSERT_THROWS(
			c.addStudentToGroup( STUDENT_ID, GROUP1_NAME )
		,	Messages::StudentNotFound
	);

	c.createStudent( STUDENT_ID, "Ivanov", "1995/01/01", StudyForm::Budget );

	ASSERT_THROWS(
			c.addStudentToGroup( STUDENT_ID, GROUP2_NAME )
		,	Messages::GroupNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_remove_single_student_makes_group_empty )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT_ID = 12345;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.addStudentToGroup( STUDENT_ID, GROUP_NAME );
	c.removeStudentFromGroup( STUDENT_ID, GROUP_NAME );
	
	auto expectedIds = std::vector< int >{};
	assert( c.getStudentIdsOfGroup( GROUP_NAME ) == expectedIds );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_two_remove_one_leaves_other_in_group )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT1_ID = 12345;
	const int STUDENT2_ID = 23456;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT1_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.createStudent( STUDENT2_ID, "Petrov", "1995/01/01", StudyForm::Contract );
	c.addStudentToGroup( STUDENT1_ID, GROUP_NAME );
	c.addStudentToGroup( STUDENT2_ID, GROUP_NAME );
	c.removeStudentFromGroup( STUDENT1_ID, GROUP_NAME );

	auto expectedIds = std::vector< int >{ STUDENT2_ID };
	assert( c.getStudentIdsOfGroup( GROUP_NAME ) == expectedIds );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_remove_existing_student_from_empty_group_fails )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT_ID = 12345;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT_ID, "Ivanov", "1995/01/01", StudyForm::Budget );

	ASSERT_THROWS(
			c.removeStudentFromGroup( STUDENT_ID, GROUP_NAME )
		,	Messages::RemovingStudentNotInGroup
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_no_captain_in_group_by_default )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT_ID = 12345;

	Controller c;
	c.createGroup( GROUP_NAME );

	assert( c.getGroupCaptainId( GROUP_NAME ) == -1 );

	c.createStudent( STUDENT_ID, "Ivanov", "1995/04/04", StudyForm::Budget );
	c.addStudentToGroup( STUDENT_ID, GROUP_NAME );

	assert( c.getGroupCaptainId( GROUP_NAME ) == -1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_two_students_in_group_assign_existing_captain )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT1_ID = 12345;
	const int STUDENT2_ID = 23456;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT1_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.createStudent( STUDENT2_ID, "Petrov", "1997/03/02", StudyForm::Contract );
	c.addStudentToGroup( STUDENT1_ID, GROUP_NAME );
	c.addStudentToGroup( STUDENT2_ID, GROUP_NAME );

	c.assignGroupCaptain( STUDENT1_ID, GROUP_NAME );
	assert( c.getGroupCaptainId( GROUP_NAME ) == STUDENT1_ID );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_student_must_study_in_group_to_be_captain )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT_ID = 12345;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT_ID, "Ivanov", "1995/01/01", StudyForm::Budget );

	ASSERT_THROWS(
		c.assignGroupCaptain( STUDENT_ID, GROUP_NAME ),
		Messages::CaptainMustStudyInGroup
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_reassign_captain_is_ok )
{
	const char * GROUP_NAME = "TEST-14-1";
	const int STUDENT1_ID = 12345;
	const int STUDENT2_ID = 23456;

	Controller c;
	c.createGroup( GROUP_NAME );
	c.createStudent( STUDENT1_ID, "Ivanov", "1995/01/01", StudyForm::Budget );
	c.createStudent( STUDENT2_ID, "Petrov", "1995/05/05", StudyForm::Budget );
	c.addStudentToGroup( STUDENT1_ID, GROUP_NAME );
	c.addStudentToGroup( STUDENT2_ID, GROUP_NAME );

	c.assignGroupCaptain( STUDENT1_ID, GROUP_NAME );
	c.assignGroupCaptain( STUDENT2_ID, GROUP_NAME );
	c.assignGroupCaptain( STUDENT2_ID, GROUP_NAME );
}


/*****************************************************************************/


void createCommonConfiguration ( Controller & c, const char * group1 , const char * group2 )
{
	c.createGroup( group1 );
	c.createGroup( group2 );

	c.createStudent( 1, "Ivanov",  "1995/01/01", StudyForm::Budget   );
	c.createStudent( 2, "Petrov",  "1995/02/02", StudyForm::Budget   );
	c.createStudent( 3, "Sidorov", "1995/03/03", StudyForm::Budget   );
	c.createStudent( 4, "Fedorov", "1995/04/01", StudyForm::Budget   );
	c.createStudent( 5, "Kozlov",  "1994/05/05", StudyForm::Contract );

	c.addStudentToGroup( 1, group1 );
	c.addStudentToGroup( 2, group1 );
	c.addStudentToGroup( 3, group1 );
	c.addStudentToGroup( 4, group2 );
	c.addStudentToGroup( 5, group2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_calculations_of_study_form_count )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";

	Controller c;
	createCommonConfiguration( c, GROUP1_NAME, GROUP2_NAME );

	assert( c.getStudentsCountPerStudyForm( StudyForm::Budget   ) == 4 );
	assert( c.getStudentsCountPerStudyForm( StudyForm::Contract ) == 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_calculations_of_group_budget_percentage )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";

	Controller c;
	createCommonConfiguration( c, GROUP1_NAME, GROUP2_NAME );

	assert( c.getBudgetStudentsPercentageInGroup( GROUP1_NAME ) == 100.0 );
	assert( c.getBudgetStudentsPercentageInGroup( GROUP2_NAME ) ==  50.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_students_born_on_first_day_of_month )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";

	Controller c;
	createCommonConfiguration( c, GROUP1_NAME, GROUP2_NAME );

	auto expectedIds = std::vector< int >{ 1 /* Ivanov */, 4 /* Fedorov */ };
	assert( c.getStudentsBornFirstDayOfMonth() == expectedIds );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_eldest_captain_when_having_captains )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";

	Controller c;
	createCommonConfiguration( c, GROUP1_NAME, GROUP2_NAME );
	c.assignGroupCaptain( 2 /* Petrov */, GROUP1_NAME );
	c.assignGroupCaptain( 5 /* Kozlov */, GROUP2_NAME );

	assert( c.getEldestCaptainName() == "Kozlov" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_eldest_captain_when_no_captains )
{
	const char * GROUP1_NAME = "TEST-14-1";
	const char * GROUP2_NAME = "TEST-14-2";

	Controller c;
	createCommonConfiguration( c, GROUP1_NAME, GROUP2_NAME );

	assert( c.getEldestCaptainName() == "" );
}


/*****************************************************************************/
