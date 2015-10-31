// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const SkillDoesNotExistForEmployee = "Requested skill is not available for current employee";
	const char * const SkillAlreadyExistsForEmployee = "Requested skill already exists for employee";
	const char * const WrongSkillLevelRange = "Skill level doesn't match range 0..10";
	const char * const EmployeeNameIsEmpty = "Employee's name is empty";
	const char * const EmployeePositionIsEmpty = "Employee's position is empty";
	const char * const EmployeeBirthYearMoreThanCurrent = "Employee's birth year is more than current";
	const char * const SkillNameIsEmpty = "Skill name is empty";
	const char * const EmployeeDoesNotExist = "Employee with such name doesn't exist";
	const char * const EmployeeAlreadyExists = "Employee with such name already exists";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_