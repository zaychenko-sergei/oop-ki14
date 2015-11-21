// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


void createCommonConfiguration ( Controller & c )
{
	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database", 3 );

	c.addEmployee( "Davin Alden", "Researcher", 1981 );

	c.addSkillForEmployee( "Davin Alden", "TDD", 8 );
	c.addSkillForEmployee( "Davin Alden", "C++", 5 );
	c.addSkillForEmployee( "Davin Alden", "Database", 7 );

	c.addEmployee( "Kimberlyn Scrivener", "Architect", 1987 );

	c.addSkillForEmployee( "Kimberlyn Scrivener", "TDD", 9 );
	c.addSkillForEmployee( "Kimberlyn Scrivener", "C++", 10 );
	c.addSkillForEmployee( "Kimberlyn Scrivener", "Database", 4 );

	c.addEmployee( "Serena Summers", "Developer", 1990 );

	c.addSkillForEmployee( "Serena Summers", "TDD", 6 );
	c.addSkillForEmployee( "Serena Summers", "C++", 7 );
	c.addSkillForEmployee( "Serena Summers", "Database", 1 );

	c.addEmployee( "Murphy Mounce", "Developer", 1960 );

	c.addSkillForEmployee( "Murphy Mounce", "TDD", 5 );
	c.addSkillForEmployee( "Murphy Mounce", "C++", 6 );
	c.addSkillForEmployee( "Murphy Mounce", "Database", 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_trace_properties )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Recruiter", 1980 );

	assert( c.getEmployeePosition( "John Tedlow" ) == "Recruiter" );
	assert( c.getEmployeeBirthYear( "John Tedlow" ) == 1980 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_empty_full_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addEmployee( "", "Recruiter", 1980 )
		,	Messages::EmployeeNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_empty_position )
{
	Controller c;

	ASSERT_THROWS(
			c.addEmployee( "John Tedlow", "", 1980 )
		,	Messages::EmployeePositionIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_year_more_than_current )
{
	Controller c;

	ASSERT_THROWS(
			c.addEmployee( "John Tedlow", "Recruiter", 2099 )
		,	Messages::EmployeeBornInFuture
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_duplicated_full_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Recruiter", 1980 );

	ASSERT_THROWS(
			c.addEmployee( "John Tedlow", "Developer", 1987 )
		,	Messages::EmployeeAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_duplicated_position )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );
	c.addEmployee( "Davin Alden", "Developer", 1977 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_skill_trace_properties )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "Test Driven Development", 7 );

	assert( c.getEmployeeSkillsCount( "John Tedlow" ) == 1 );
	assert( c.getEmployeeSkillLevel( "John Tedlow", "Test Driven Development" ) == 7 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_skill_with_empty_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	ASSERT_THROWS(
			c.addSkillForEmployee( "", "Test Driven Development", 7 )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_skill_with_unexisting_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	ASSERT_THROWS(
			c.addSkillForEmployee( "Rob Johnson", "Test Driven Development", 7 )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_skill_with_empty_skill_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	ASSERT_THROWS(
			c.addSkillForEmployee( "John Tedlow", "", 7 )
		,	Messages::SkillNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_skill_with_too_high_mark )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	ASSERT_THROWS(
			c.addSkillForEmployee( "John Tedlow", "Test Driven Development", 11 )
		,	Messages::WrongSkillLevelRange
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_skill_with_same_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );
	c.addEmployee( "Davin Alden", "Developer", 1982 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "Davin Alden", "TDD", 4 );

	assert( c.getEmployeeSkillLevel( "John Tedlow", "TDD" ) == 7 );
	assert( c.getEmployeeSkillLevel( "Davin Alden", "TDD" ) == 4 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicating_skill )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );

	ASSERT_THROWS(
			c.addSkillForEmployee( "John Tedlow", "TDD", 9 )
		,	Messages::SkillAlreadyDefinedForEmployee
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_skill_with_empty_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );

	ASSERT_THROWS(
			c.getEmployeeSkillLevel( "", "TDD" )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_skill_with_unexisting_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );

	ASSERT_THROWS(
			c.getEmployeeSkillLevel( "Davin Alden", "TDD" )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_skill_with_empty_skill_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );

	ASSERT_THROWS(
			c.getEmployeeSkillLevel( "John Tedlow", "" )
		,	Messages::SkillUndefinedForEmployee
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_skill_with_unexisting_skill_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );

	ASSERT_THROWS(
			c.getEmployeeSkillLevel( "John Tedlow", "C++" )
		,	Messages::SkillUndefinedForEmployee
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_skill_names )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database Deployment", 3 );

	std::unordered_set< std::string > expectedResult = { "TDD", "C++", "Database Deployment" };

	assert( expectedResult == c.getEmployeeSkillNames( "John Tedlow" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_skill_names_empty_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database Deployment", 3 );

	ASSERT_THROWS(
			c.getEmployeeSkillNames( "" )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_skill_names_unexisting_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database Deployment", 3 );

	ASSERT_THROWS(
			c.getEmployeeSkillNames( "Davin Alden" )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_skills_count_empty_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database Deployment", 3 );

	ASSERT_THROWS(
			c.getEmployeeSkillsCount( "" )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_skills_count_unexisting_employee_name )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database Deployment", 3 );

	ASSERT_THROWS(
			c.getEmployeeSkillsCount( "Davin Alden" )
		,	Messages::EmployeeDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_best_skill_query )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 7 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database Deployment", 3 );

	Controller::BestSkill expectedResult = std::make_pair( "C++", 9 );

	assert( c.getEmployeeBestSkill( "John Tedlow" )  == expectedResult );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_best_skill_query_same_max_skill )
{
	Controller c;

	c.addEmployee( "John Tedlow", "Developer", 1977 );

	c.addSkillForEmployee( "John Tedlow", "TDD", 9 );
	c.addSkillForEmployee( "John Tedlow", "C++", 9 );
	c.addSkillForEmployee( "John Tedlow", "Database Deployment", 3 );

	std::vector< Controller::BestSkill > expectedResult
		=	
		{
				std::make_pair( "C++", 9 )
			,	std::make_pair( "TDD", 9 )
		};

	assert(
			std::find(
					expectedResult.begin()
				,	expectedResult.end()
				,	c.getEmployeeBestSkill( "John Tedlow" )
			)
		!=	expectedResult.end()
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_best_employees_having_skill_cpp )
{
	Controller c;

	createCommonConfiguration( c );

	std::unordered_set< std::string > expectedResult = { "John Tedlow","Kimberlyn Scrivener" };

	assert( expectedResult == c.getBestEmployeesHavingSkill( "C++", 2 ) );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_best_employees_having_skill_database )
{
	Controller c;

	createCommonConfiguration( c );
	
	std::unordered_set< std::string > expectedResult =
	{
			"John Tedlow"
		,	"Davin Alden"
		,	"Kimberlyn Scrivener"
	};

	assert( expectedResult == c.getBestEmployeesHavingSkill( "Database", 3 ) );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_best_employees_having_skill_tdd )
{
	Controller c;

	createCommonConfiguration( c );
	
	std::unordered_set< std::string > expectedResult = { "Kimberlyn Scrivener" };

	assert( expectedResult == c.getBestEmployeesHavingSkill( "TDD", 1 ) );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_eldest_employee_with_skill_at_least )
{
	Controller c;

	createCommonConfiguration( c );

	assert( c.getEldestEmployeeWithSkillAtLeast( "C++", 9 ) == "John Tedlow" );
	assert( c.getEldestEmployeeWithSkillAtLeast( "C++", 10 ) == "Kimberlyn Scrivener" );
	assert( c.getEldestEmployeeWithSkillAtLeast( "TDD", 8 ) == "Davin Alden" );
	assert( c.getEldestEmployeeWithSkillAtLeast( "Database", 1 ) == "Murphy Mounce" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_employee_with_best_total_skill_points )
{
	Controller c;

	createCommonConfiguration( c );

	assert( c.getEmployeeWithBiggestTotalSkillPoints() == "Kimberlyn Scrivener" );
}


/*****************************************************************************/
