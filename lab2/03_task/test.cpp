// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_trace_properties )
{
	Controller c;
	c.createEmployee( "Ivan Ivanov", 1 );

	assert( c.getEmployeeLevel( "Ivan Ivanov" ) == 1 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_gwo_employees_trace_properties )
{
	Controller c;
	c.createEmployee( "Ivan Ivanov", 1 );
	c.createEmployee( "Petr Petrov", 3 );

	assert( c.getEmployeeLevel( "Ivan Ivanov" ) == 1 );
	assert( c.getEmployeeLevel( "Petr Petrov" ) == 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_empty_name_fails )
{
	Controller c;

	ASSERT_THROWS(
		c.createEmployee( "", 1 ),
		Messages::EmptyEmployeeName
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_employee_correct_and_wrong_levels )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );
	c.createEmployee( "Petrov", 5 );

	ASSERT_THROWS(
		c.createEmployee( "Sidorov", 0 ),
		Messages::LevelOutOfRange
	);

	ASSERT_THROWS(
		c.createEmployee( "Fedorov", 6 ),
		Messages::LevelOutOfRange
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicate_employee )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.createEmployee( "Ivanov", 1 ),
		Messages::EmployeeAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_existing_employee_level )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );
	c.updateEmployeeLevel( "Ivanov", 2 );

	assert( c.getEmployeeLevel( "Ivanov" ) == 2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_non_existing_employee_level )
{
	Controller c;

	ASSERT_THROWS(
		c.updateEmployeeLevel( "Petrov", 2 ),
		Messages::EmployeeNotFound
	);

	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.updateEmployeeLevel( "Petrov", 2 ),
		Messages::EmployeeNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_task_passes )
{
	Controller c;
	c.createTask( "Do Job" );
	assert( c.getTaskTotalHours( "Do Job" ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_task_with_empty_title_fails )
{
	Controller c;
	ASSERT_THROWS(
		c.createTask( "" ),
		Messages::EmptyTaskTitle
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicate_task_fails )
{
	Controller c;
	c.createTask( "Job" );
	ASSERT_THROWS(
		c.createTask( "Job" ),
		Messages::TaskAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employee_to_task )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );
	c.createTask( "Do Job" );

	c.assignEmployeeToTask( "Do Job", "Ivanov", 10 );

	assert( c.getEmployeeAllocationInTask( "Do Job", "Ivanov" ) == 10 );
	assert( c.getEmployeeTasks( "Ivanov" ) == std::vector< std::string >{ "Do Job" } );
	assert( c.getTaskEmployees( "Do Job" ) == std::vector< std::string >{ "Ivanov" } );
	assert( c.getTaskTotalHours( "Do Job" ) == 10 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_two_employees_to_task )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );
	c.createEmployee( "Petrov", 2 );
	c.createTask( "Do Job" );

	c.assignEmployeeToTask( "Do Job", "Ivanov", 10 );
	c.assignEmployeeToTask( "Do Job", "Petrov", 5 );

	assert( c.getEmployeeAllocationInTask( "Do Job", "Ivanov" ) == 10 );
	assert( c.getEmployeeAllocationInTask( "Do Job", "Petrov" ) ==  5 );
	
	assert( c.getEmployeeTasks( "Ivanov" ) == std::vector< std::string >{ "Do Job" } );
	assert( c.getEmployeeTasks( "Petrov" ) == std::vector< std::string >{ "Do Job" } );

	std::vector< std::string > expectedEmployees{ "Ivanov", "Petrov" };
	assert( c.getTaskEmployees( "Do Job" ) == expectedEmployees );

	assert( c.getTaskTotalHours( "Do Job" ) == 15 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employee_to_two_tasks )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );
	c.createTask( "Prepare Job" );
	c.createTask( "Do Job" );

	c.assignEmployeeToTask( "Prepare Job", "Ivanov",  5 );
	c.assignEmployeeToTask( "Do Job",      "Ivanov", 10 );

	assert( c.getEmployeeAllocationInTask( "Prepare Job", "Ivanov" ) ==  5 );
	assert( c.getEmployeeAllocationInTask( "Do Job",      "Ivanov" ) == 10 );

	std::vector< std::string > expectedTasks{ "Do Job", "Prepare Job" };
	assert( c.getEmployeeTasks( "Ivanov" ) == expectedTasks );

	assert( c.getTaskEmployees( "Prepare Job" ) == std::vector< std::string >{ "Ivanov" } );
	assert( c.getTaskEmployees( "Do Job" )      == std::vector< std::string >{ "Ivanov" }  );

	assert( c.getTaskTotalHours( "Prepare Job" ) == 5 );
	assert( c.getTaskTotalHours( "Do Job" ) == 10 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employees_to_tasks_overlap )
{
	Controller c;
	c.createEmployee( "Ivanov",  1 );
	c.createEmployee( "Petrov",  2 );
	c.createEmployee( "Sidorov", 3 );

	c.createTask( "Job 1" );
	c.createTask( "Job 2" );

	c.assignEmployeeToTask( "Job 1", "Ivanov", 10 );
	c.assignEmployeeToTask( "Job 1", "Petrov", 12 );

	c.assignEmployeeToTask( "Job 2", "Petrov",   5 );
	c.assignEmployeeToTask( "Job 2", "Sidorov", 15 );

	assert( c.getEmployeeAllocationInTask( "Job 1", "Ivanov"  ) == 10 );
	assert( c.getEmployeeAllocationInTask( "Job 1", "Petrov"  ) == 12 );
	assert( c.getEmployeeAllocationInTask( "Job 2", "Petrov"  ) ==  5 );
	assert( c.getEmployeeAllocationInTask( "Job 2", "Sidorov" ) == 15 );

	assert( c.getEmployeeTasks( "Ivanov" )  == std::vector< std::string >{ "Job 1" } );
	assert( c.getEmployeeTasks( "Sidorov" ) == std::vector< std::string >{ "Job 2" } );
	std::vector< std::string > expectedPetrovTasks{ "Job 1", "Job 2" };
	assert( c.getEmployeeTasks( "Petrov" ) == expectedPetrovTasks );

	std::vector< std::string > expectedJob1Employees{ "Ivanov", "Petrov" };
	std::vector< std::string > expectedJob2Employees{ "Petrov", "Sidorov" };
	assert( c.getTaskEmployees( "Job 1" ) == expectedJob1Employees );
	assert( c.getTaskEmployees( "Job 2" ) == expectedJob2Employees );

	assert( c.getTaskTotalHours( "Job 1" ) == 22 );
	assert( c.getTaskTotalHours( "Job 2" ) == 20 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employee_to_missing_task_fails )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.assignEmployeeToTask( "Job", "Ivanov", 10 ),
		Messages::TaskNotFound
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_non_existing_employee_to_task_fails )
{
	Controller c;
	c.createTask( "Job" );

	ASSERT_THROWS(
		c.assignEmployeeToTask( "Job", "Ivanov", 10 ),
		Messages::EmployeeNotFound
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employee_negative_or_zero_load )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.assignEmployeeToTask( "Job", "Ivanov", -1 ),
		Messages::NonPositiveHours
	);

	ASSERT_THROWS(
		c.assignEmployeeToTask( "Job", "Ivanov", 0 ),
		Messages::NonPositiveHours
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_assign_employee_to_same_task_twice )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );
	c.assignEmployeeToTask( "Job", "Ivanov", 10 );

	ASSERT_THROWS(
		c.assignEmployeeToTask( "Job", "Ivanov", 20 ),
		Messages::EmployeeAlreadyAllocated
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_employee_load )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );
	c.assignEmployeeToTask( "Job", "Ivanov", 10 );
	
	c.updateEmployeeTaskLoad( "Job", "Ivanov", 15 );

	assert( c.getEmployeeAllocationInTask( "Job", "Ivanov" ) == 15 );
	assert( c.getTaskEmployees( "Job" ) == std::vector< std::string >{ "Ivanov" } );
	assert( c.getEmployeeTasks( "Ivanov" ) == std::vector< std::string >{ "Job" } );
	assert( c.getTaskTotalHours( "Job" ) == 15 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_employee_load_non_existing_job )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );
	c.assignEmployeeToTask( "Job", "Ivanov", 10 );

	ASSERT_THROWS(
		c.updateEmployeeTaskLoad( "Surprise", "Ivanov", 15 ),
		Messages::TaskNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_employee_load_non_existing_employee )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );
	c.assignEmployeeToTask( "Job", "Ivanov", 10 );

	ASSERT_THROWS(
		c.updateEmployeeTaskLoad( "Job", "Surprise", 15 ),
		Messages::EmployeeNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_employee_load_no_relation_to_job )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.updateEmployeeTaskLoad( "Job", "Ivanov", 15 ),
		Messages::EmployeeNotAllocated
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_update_employee_load_non_positive_hours )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );
	c.assignEmployeeToTask( "Job", "Ivanov", 10 );

	ASSERT_THROWS(
		c.updateEmployeeTaskLoad( "Job", "Ivanov", -1 ),
		Messages::NonPositiveHours
	);

	ASSERT_THROWS(
		c.updateEmployeeTaskLoad( "Job", "Ivanov", 0 ),
		Messages::NonPositiveHours
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_unassign_employee_from_task )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );
	c.createEmployee( "Petrov", 2 );
	c.createTask( "Job 1" );
	c.createTask( "Job 2" );
	c.assignEmployeeToTask( "Job 1", "Ivanov", 5 );
	c.assignEmployeeToTask( "Job 1", "Petrov", 10 );
	c.assignEmployeeToTask( "Job 2", "Petrov", 15 );

	c.unassignEmployeeFromTask( "Job 1", "Petrov" );

	assert( c.getEmployeeAllocationInTask( "Job 1", "Ivanov" ) == 5 );
	assert( c.getEmployeeAllocationInTask( "Job 1", "Petrov" ) == 0 );

	assert( c.getEmployeeAllocationInTask( "Job 2", "Ivanov" ) ==  0 );
	assert( c.getEmployeeAllocationInTask( "Job 2", "Petrov" ) == 15 );

	assert( c.getTaskEmployees( "Job 1" ) == std::vector< std::string >{ "Ivanov" } );
	assert( c.getTaskEmployees( "Job 2" ) == std::vector< std::string >{ "Petrov" } );

	assert( c.getEmployeeTasks( "Ivanov" ) == std::vector< std::string >{ "Job 1" } );
	assert( c.getEmployeeTasks( "Petrov" ) == std::vector< std::string >{ "Job 2" } );

	assert( c.getTaskTotalHours( "Job 1" ) == 5 );
	assert( c.getTaskTotalHours( "Job 2" ) == 15 );

}


/*****************************************************************************/


DECLARE_OOP_TEST( test_unassign_employee_from_non_existing_task )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.unassignEmployeeFromTask( "Surprise", "Ivanov" ),
		Messages::TaskNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_unassign_unexisting_employee_from_task )
{
	Controller c;
	c.createTask( "Job" );

	ASSERT_THROWS(
		c.unassignEmployeeFromTask( "Job", "Surprise" ),
		Messages::EmployeeNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_unassign_unrelated_employee_from_task )
{
	Controller c;
	c.createTask( "Job" );
	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.unassignEmployeeFromTask( "Job", "Ivanov" ),
		Messages::EmployeeNotAllocated
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_get_task_employees_corner_cases )
{
	Controller c;
	
	ASSERT_THROWS(
		c.getTaskEmployees( "Surprise" ),
		Messages::TaskNotFound
	);

	c.createTask( "Job" );

	assert( c.getTaskEmployees( "Job" ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_get_employee_tasks_corner_cases )
{
	Controller c;

	ASSERT_THROWS(
		c.getEmployeeTasks( "Surprise" ),
		Messages::EmployeeNotFound
	);

	c.createEmployee( "Ivanov", 1 );

	assert( c.getEmployeeTasks( "Ivanov" ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_get_employee_tasks_allocation_corner_cases )
{
	Controller c;
	c.createEmployee( "Ivanov", 1 );

	ASSERT_THROWS(
		c.getEmployeeAllocationInTask( "Surprise", "Ivanov" ),
		Messages::TaskNotFound
	);

	c.createTask( "Job" );

	ASSERT_THROWS(
		c.getEmployeeAllocationInTask( "Job", "Petrov" ),
		Messages::EmployeeNotFound
	);

	assert( c.getEmployeeAllocationInTask( "Job", "Ivanov" ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_get_total_hours_corner_cases )
{
	Controller c;
	ASSERT_THROWS(
		c.getTaskTotalHours( "Surprise" ),
		Messages::TaskNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_get_employes_with_load_over )
{
	Controller c;
	c.createTask( "Job 1" );
	c.createTask( "Job 2" );

	c.createEmployee( "Ivanov", 1 );
	c.createEmployee( "Petrov", 2 );
	c.createEmployee( "Sidorov", 3 );
	c.createEmployee( "Fedorov", 4 );

	c.assignEmployeeToTask( "Job 1", "Ivanov", 10 );
	c.assignEmployeeToTask( "Job 1", "Petrov", 20 );
	c.assignEmployeeToTask( "Job 2", "Ivanov", 5 );
	c.assignEmployeeToTask( "Job 2", "Petrov", 10 );
	c.assignEmployeeToTask( "Job 1", "Sidorov", 30 );

	std::vector< std::string > expectedOverloaders{ "Petrov", "Sidorov" };
	assert( c.getEmployeesWithLoadOver( 25 ) == expectedOverloaders );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_calculate_task_cost )
{
	Controller c;
	c.createTask( "Job 1" );
	c.createTask( "Job 2" );
	c.createTask( "Job 3" );

	c.createEmployee( "Ivanov", 1 );
	c.createEmployee( "Petrov", 2 );
	c.createEmployee( "Sidorov", 3 );

	c.assignEmployeeToTask( "Job 1", "Ivanov", 10 );
	c.assignEmployeeToTask( "Job 1", "Petrov", 20 );
	c.assignEmployeeToTask( "Job 1", "Sidorov", 30 );
	c.assignEmployeeToTask( "Job 2", "Sidorov", 10 );

	assert( c.calculateTaskCost( "Job 1", 5.0 ) == ( 50 + 200 + 450 ) ); // 10 * 5 * 1 + 20 * 5 * 2 + 30 * 5 * 3
	assert( c.calculateTaskCost( "Job 2", 3.0 ) == 90 ); // 10 * 3 * 3
	assert( c.calculateTaskCost( "Job 3", 2.0 ) == 0.0 );

	ASSERT_THROWS(
		c.calculateTaskCost( "Surprise" ),
		Messages::TaskNotFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_predict_employee_payment )
{
	Controller c;
	c.createTask( "Job 1" );
	c.createTask( "Job 2" );
	c.createTask( "Job 3" );

	c.createEmployee( "Ivanov", 1 );
	c.createEmployee( "Petrov", 2 );
	c.createEmployee( "Sidorov", 3 );

	c.assignEmployeeToTask( "Job 1", "Ivanov", 10 );
	c.assignEmployeeToTask( "Job 1", "Petrov", 20 );
	c.assignEmployeeToTask( "Job 1", "Sidorov", 30 );
	c.assignEmployeeToTask( "Job 2", "Sidorov", 10 );

	assert( c.predictEmployeePayment( "Ivanov",  5.0 ) ==  50 ); // 10 * 5 * 1
	assert( c.predictEmployeePayment( "Petrov",  5.0 ) == 200 ); // 20 * 5 * 2
	assert( c.predictEmployeePayment( "Sidorov", 5.0 ) == 600 ); // 30 * 5 * 3 + 10 * 5 * 3

	ASSERT_THROWS(
		c.predictEmployeePayment( "Surprise" ),
		Messages::EmployeeNotFound
	);
}


/*****************************************************************************/
