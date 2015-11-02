// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/


namespace Messages
{
	const char * const EmptyEmployeeName        = "Empty employee name not allowed";
	const char * const LevelOutOfRange          = "Level should be within [1:5] range";
	const char * const TaskAlreadyAssigned      = "Task was already assigned to this employee";
	const char * const TaskWasNotAssigned       = "Task was not assigned to this employee";
	const char * const EmptyTaskTitle           = "Empty task title not allowed";
	const char * const EmployeeAlreadyAllocated = "Employee already allocated to task";
	const char * const EmployeeNotAllocated     = "Employee was not allocated to task";
	const char * const NonPositiveHours         = "Load hours must be positive";
	const char * const EmployeeAlreadyExists    = "Employee with identical name already exists ";
	const char * const TaskAlreadyExists        = "Task with identical name already exists";
	const char * const EmployeeNotFound         = "Specified employee not found";
	const char * const TaskNotFound             = "Task not found";
	const char * const NegativeHourCost         = "Hour cost cannot be negative";
}


/*****************************************************************************/

#endif // _MESSAGES_HPP_