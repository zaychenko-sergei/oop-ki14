// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_regular_employee )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	assert( c.isKnownEmployee( "Ivanov" ) );
	assert( c.getRegularEmployeeLevel( "Ivanov" ) == RegularEmployeeLevel::Junior );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_regular_employees )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createRegular( "Petrov", RegularEmployeeLevel::Senior );

	assert( c.isKnownEmployee( "Ivanov" ) );
	assert( c.isKnownEmployee( "Petrov" ) );
	assert( c.getRegularEmployeeLevel( "Ivanov" ) == RegularEmployeeLevel::Junior );
	assert( c.getRegularEmployeeLevel( "Petrov" ) == RegularEmployeeLevel::Senior );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_manager )
{
	Controller c;
	c.createManager( "Sidorov" );

	assert( c.isKnownEmployee( "Sidorov" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_manager_and_regular )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Sidorov" );

	assert( c.isKnownEmployee( "Ivanov" ) );
	assert( c.isKnownEmployee( "Sidorov" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.createRegular( "", RegularEmployeeLevel::Junior )
		,	Messages::EmployeeFullNameEmpty
	);

	ASSERT_THROWS(
			c.createManager( "" )
		,	Messages::EmployeeFullNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicate_employees )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Sidorov" );

	ASSERT_THROWS(
			c.createRegular( "Ivanov", RegularEmployeeLevel::Junior )
		,	Messages::EmployeeFullNameNonUnique
	);

	ASSERT_THROWS(
			c.createManager( "Sidorov" )
		,	Messages::EmployeeFullNameNonUnique
	);

	ASSERT_THROWS(
			c.createManager( "Ivanov" )
		,	Messages::EmployeeFullNameNonUnique
	);

	ASSERT_THROWS(
			c.createRegular( "Sidorov", RegularEmployeeLevel::Lead )
		,	Messages::EmployeeFullNameNonUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_promote_regular_employee )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );

	assert( c.getRegularEmployeeLevel( "Ivanov" ) == RegularEmployeeLevel::Junior );
	c.promote( "Ivanov" );
	assert( c.getRegularEmployeeLevel( "Ivanov" ) == RegularEmployeeLevel::Middle );
	c.promote( "Ivanov" );
	assert( c.getRegularEmployeeLevel( "Ivanov" ) == RegularEmployeeLevel::Senior );
	c.promote( "Ivanov" );
	assert( c.getRegularEmployeeLevel( "Ivanov" ) == RegularEmployeeLevel::Lead );
	c.promote( "Ivanov" );
	assert( c.getRegularEmployeeLevel( "Ivanov" ) == RegularEmployeeLevel::Lead );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_promote_manager )
{
	Controller c;
	c.createManager( "Sidorov" );

	ASSERT_THROWS(
			c.promote( "Sidorov" )
		,	Messages::CannotPromoteManagers
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_regular_salary_depends_on_base_salary )
{
	Controller c;
	c.createRegular( "Petrov", RegularEmployeeLevel::Middle );

	assert( c.getEmployeeSalary( "Petrov", 500.0 ) == 500.0 );
	assert( c.getEmployeeSalary( "Petrov", 200.0 ) == 200.0 );
	assert( c.getEmployeeSalary( "Petrov", 10000.0 ) == 10000.0 );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_regular_salary_depends_on_level )
{
	Controller c;
	c.createRegular( "Ivanov",  RegularEmployeeLevel::Junior );
	c.createRegular( "Petrov",  RegularEmployeeLevel::Middle );
	c.createRegular( "Sidorov", RegularEmployeeLevel::Senior );
	c.createRegular( "Fedorov", RegularEmployeeLevel::Lead   );

	assert( c.getEmployeeSalary( "Ivanov",  500.0 ) == 250.0 );
	assert( c.getEmployeeSalary( "Petrov",  500.0 ) == 500.0 );
	assert( c.getEmployeeSalary( "Sidorov", 500.0 ) == 600.0 );
	assert( c.getEmployeeSalary( "Fedorov", 500.0 ) == 750.0 );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_manager_salary_depends_on_average )
{
	Controller c;
	c.createRegular( "Ivanov",  RegularEmployeeLevel::Junior );
	c.createRegular( "Petrov",  RegularEmployeeLevel::Middle );
	c.createRegular( "Sidorov", RegularEmployeeLevel::Senior );
	c.createRegular( "Fedorov", RegularEmployeeLevel::Lead );

	c.createManager( "Alekseyev" );
	c.assignManager( "Ivanov",  "Alekseyev" );
	c.assignManager( "Petrov",  "Alekseyev" );
	c.assignManager( "Sidorov", "Alekseyev" );

	assert( c.getEmployeeSalary( "Alekseyev", 500.0 ) == 900.0 ); // 2 * ( 250 + 500 + 600 ) / 3

	c.assignManager( "Fedorov", "Alekseyev" );

	assert( c.getEmployeeSalary( "Alekseyev", 500.0 ) == 1050.0 ); // 2 * ( 250 + 500 + 600 + 750) / 4
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_manager_salary_without_subordinates )
{
	Controller c;
	c.createManager( "Alekseyev" );
	assert( c.getEmployeeSalary( "Alekseyev", 500.0 ) == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_salary_with_bonus )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Petrov" );
	c.assignManager( "Ivanov", "Petrov" );

	assert( c.getEmployeeBonus( "Ivanov" ) == 0.0 );
	assert( c.getEmployeeBonus( "Petrov" ) == 0.0 );
	
	c.changeBonus( "Ivanov", 100.0 );
	c.changeBonus( "Petrov", 300.0 );

	assert( c.getEmployeeBonus( "Ivanov" ) == 100.0 );
	assert( c.getEmployeeBonus( "Petrov" ) == 300.0 );

	assert( c.getEmployeeSalary( "Ivanov", 500.0 ) == 350.0 ); // 0.5 * 500 + 100
	assert( c.getEmployeeSalary( "Petrov", 500.0 ) == 800.0 ); // 2 * 250 + 300
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_salary_with_bonus_only )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Petrov" );
	c.assignManager( "Ivanov", "Petrov" );

	assert( c.getEmployeeBonus( "Ivanov" ) == 0.0 );
	assert( c.getEmployeeBonus( "Petrov" ) == 0.0 );

	c.changeBonus( "Ivanov", 100.0 );
	c.changeBonus( "Petrov", 300.0 );

	assert( c.getEmployeeSalary( "Ivanov", 0.0 ) == 100.0 );
	assert( c.getEmployeeSalary( "Petrov", 0.0 ) == 300.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_zero_bonus )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.changeBonus( "Ivanov", 0.0 );
	assert( c.getEmployeeSalary( "Ivanov", 500.0 ) == 250.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_negative_bonus )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	ASSERT_THROWS(
			c.changeBonus( "Ivanov", -100.0 )
		,	Messages::NegativeBonusAmount
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_salary_negative_base )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );

	ASSERT_THROWS(
			c.getEmployeeSalary( "Ivanov", -1.0 )
		,	Messages::NegativeBaseSalary
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_distribute_employees_between_managers )
{
	Controller c;
	c.createRegular( "Ivanov1", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov2", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov3", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov4", RegularEmployeeLevel::Junior );

	c.createManager( "Korolyov1" );
	c.createManager( "Korolyov2" );

	c.assignManager( "Ivanov1", "Korolyov1" );
	c.assignManager( "Ivanov2", "Korolyov1" );
	c.assignManager( "Ivanov3", "Korolyov2" );
	c.assignManager( "Ivanov4", "Korolyov2" );

	assert( c.getEmployeeManager( "Korolyov1" ) == "" );
	assert( c.getEmployeeManager( "Korolyov2" ) == "" );

	assert( c.getEmployeeManager( "Ivanov1" ) == "Korolyov1" );
	assert( c.getEmployeeManager( "Ivanov2" ) == "Korolyov1" );
	assert( c.getEmployeeManager( "Ivanov3" ) == "Korolyov2" );
	assert( c.getEmployeeManager( "Ivanov4" ) == "Korolyov2" );

	std::unordered_set< std::string > expectedSubordinates1 = { "Ivanov1", "Ivanov2" };
	std::unordered_set< std::string > expectedSubordinates2 = { "Ivanov3", "Ivanov4" };
	assert( c.getManagerSubordinates( "Korolyov1" ) == expectedSubordinates1 );
	assert( c.getManagerSubordinates( "Korolyov2" ) == expectedSubordinates2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_management_hierarchy )
{
	Controller c;
	c.createRegular( "Ivanov1", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov2", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov3", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov4", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov5", RegularEmployeeLevel::Junior );
	c.createRegular( "Ivanov6", RegularEmployeeLevel::Junior );

	c.createManager( "Korolyov1" );
	c.createManager( "Korolyov2" );
	c.createManager( "Korolyov3" );

	c.createManager( "Bogov" );

	c.assignManager( "Ivanov1", "Korolyov1" );
	c.assignManager( "Ivanov2", "Korolyov1" );
	c.assignManager( "Ivanov3", "Korolyov2" );
	c.assignManager( "Ivanov4", "Korolyov2" );
	c.assignManager( "Ivanov5", "Korolyov3" );
	c.assignManager( "Ivanov6", "Korolyov3" );

	c.assignManager( "Korolyov1", "Bogov" );
	c.assignManager( "Korolyov2", "Bogov" );
	c.assignManager( "Korolyov3", "Bogov" );

	assert( c.getEmployeeManager( "Ivanov1" ) == "Korolyov1" );
	assert( c.getEmployeeManager( "Ivanov2" ) == "Korolyov1" );
	assert( c.getEmployeeManager( "Ivanov3" ) == "Korolyov2" );
	assert( c.getEmployeeManager( "Ivanov4" ) == "Korolyov2" );
	assert( c.getEmployeeManager( "Ivanov5" ) == "Korolyov3" );
	assert( c.getEmployeeManager( "Ivanov6" ) == "Korolyov3" );

	assert( c.getEmployeeManager( "Korolyov1" ) == "Bogov" );
	assert( c.getEmployeeManager( "Korolyov2" ) == "Bogov" );
	assert( c.getEmployeeManager( "Korolyov3" ) == "Bogov" );

	assert( c.getEmployeeManager( "Bogov" ) == "" );

	std::unordered_set< std::string > expectedSubordinates1 = { "Ivanov1", "Ivanov2" };
	std::unordered_set< std::string > expectedSubordinates2 = { "Ivanov3", "Ivanov4" };
	std::unordered_set< std::string > expectedSubordinates3 = { "Ivanov5", "Ivanov6" };
	assert( c.getManagerSubordinates( "Korolyov1" ) == expectedSubordinates1 );
	assert( c.getManagerSubordinates( "Korolyov2" ) == expectedSubordinates2 );
	assert( c.getManagerSubordinates( "Korolyov3" ) == expectedSubordinates3 );

	std::unordered_set < std::string > expectedSubmanagers = { "Korolyov1", "Korolyov2", "Korolyov3" };
	assert( c.getManagerSubordinates( "Bogov" ) == expectedSubmanagers );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_non_manager_as_manager )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createRegular( "Petrov", RegularEmployeeLevel::Middle );

	ASSERT_THROWS(
			c.assignManager( "Ivanov", "Petrov" )
		,	Messages::NotAManager
	);

	ASSERT_THROWS(
			c.getManagerSubordinates( "Ivanov" )
		,	Messages::NotAManager
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employee_to_two_managers_leaves_last )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Korolyov1" );
	c.createManager( "Korolyov2" );

	c.assignManager( "Ivanov", "Korolyov1" );
	c.assignManager( "Ivanov", "Korolyov2" );

	assert( c.getEmployeeManager( "Ivanov" ) == "Korolyov2" );
	assert( c.getManagerSubordinates( "Korolyov2" ) == std::unordered_set< std::string > { "Ivanov" } );
	assert( c.getManagerSubordinates( "Korolyov1" ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employee_to_same_manager_twice )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Korolyov" );
	c.assignManager( "Ivanov", "Korolyov" );

	ASSERT_THROWS(
			c.assignManager( "Ivanov", "Korolyov" )
		,	Messages::SubordinateAlreadyAdded
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_unassign_employee_from_manager )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createRegular( "Petrov", RegularEmployeeLevel::Middle );
	c.createManager( "Korolyov" );

	c.assignManager( "Ivanov", "Korolyov" );
	c.assignManager( "Petrov", "Korolyov" );

	c.deassignManager( "Ivanov" );

	assert( c.getEmployeeManager( "Ivanov" ) == "" );
	assert( c.getEmployeeManager( "Petrov" ) == "Korolyov" );
	assert( c.getManagerSubordinates( "Korolyov" ) == std::unordered_set< std::string > { "Petrov" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_unassign_employee_that_was_not_assigned )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Korolyov" );

	ASSERT_THROWS(
			c.deassignManager( "Ivanov" )
		,	Messages::EmployeeHasNoManager
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_fire_unmanaged_employee )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Korolyov" );

	assert( c.isKnownEmployee( "Ivanov" ) );
	assert( c.isKnownEmployee( "Korolyov" ) );

	c.fire( "Ivanov" );

	assert( ! c.isKnownEmployee( "Ivanov" ) );
	assert( c.isKnownEmployee( "Korolyov" ) );

	c.fire( "Korolyov" );

	assert( ! c.isKnownEmployee( "Ivanov" ) );
	assert( ! c.isKnownEmployee( "Korolyov" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_fire_managed_employee )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createRegular( "Petrov", RegularEmployeeLevel::Middle );
	c.createManager( "Korolyov" );

	c.assignManager( "Ivanov", "Korolyov" );
	c.assignManager( "Petrov", "Korolyov" );

	c.fire( "Ivanov" );

	assert( ! c.isKnownEmployee( "Ivanov" ) );

	assert( c.getManagerSubordinates( "Korolyov" ) == std::unordered_set< std::string >{ "Petrov" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_fire_assigned_manager )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Korolyov" );
	c.assignManager( "Ivanov", "Korolyov" );

	ASSERT_THROWS(
			c.fire( "Korolyov")
		,	Messages::CannotFireAssignedManager
	);

	assert( c.getEmployeeManager( "Ivanov" ) == "Korolyov" );
	assert( c.getManagerSubordinates( "Korolyov" ) == std::unordered_set< std::string >{ "Ivanov" } );

	c.deassignManager( "Ivanov" );

	c.fire( "Korolyov" );
	
	assert( ! c.isKnownEmployee( "Korolyov" ) );
	assert( c.isKnownEmployee( "Ivanov" ) );

	assert( c.getEmployeeManager( "Ivanov" ) == "" );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_operate_on_unknown_employee )
{
	Controller c;
	c.createRegular( "Ivanov", RegularEmployeeLevel::Junior );
	c.createManager( "Korolyov" );

	assert( ! c.isKnownEmployee( "Surprise" ) );
	
	ASSERT_THROWS(
			c.getRegularEmployeeLevel( "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);
	
	ASSERT_THROWS(
			c.getEmployeeSalary( "Surprise", 100.0 )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.changeBonus( "Surprise", 100.0 )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.getEmployeeBonus( "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.getEmployeeManager( "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.getManagerSubordinates( "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.assignManager( "Surprise", "Korolyov" )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.assignManager( "Ivanov", "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.deassignManager( "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.fire( "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);

	ASSERT_THROWS(
			c.promote( "Surprise" )
		,	Messages::UnregisteredEmployeeName
	);
}


/*****************************************************************************/
