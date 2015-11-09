// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const SkillUndefinedForEmployee = "Requested skill is not defined for employee";
	const char * const SkillAlreadyDefinedForEmployee = "Requested skill was already defined for employee";
	const char * const WrongSkillLevelRange = "Skill level must be in range [0-10]";
	const char * const EmployeeNameIsEmpty = "Employee name is empty";
	const char * const EmployeePositionIsEmpty = "Employee position is empty";
	const char * const EmployeeBornInFuture = "Employee born in future";
	const char * const SkillNameIsEmpty = "Skill name is empty";
	const char * const EmployeeDoesNotExist = "Employee with such name doesn't exist";
	const char * const EmployeeAlreadyExists = "Employee with such name already exists";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_