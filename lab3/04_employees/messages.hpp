// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const EmployeeFullNameNonUnique     = "Name of the employee is not unique";
	const char * const EmployeeFullNameEmpty		 = "Empoyee name cannot be empty";
	const char * const NegativeBonusAmount           = "Bonus amount cannot be negative";
	const char * const NegativeBaseSalary            = "Base salary cannot be negative";
	const char * const SubordinateAlreadyAdded       = "Subordinate is already a part of manager's team";
	const char * const UnregisteredEmployeeName      = "Name of the empoyee is not recognized";
	const char * const NotAManager                   = "Specified employee has no managerial role";
	const char * const NotARegular                   = "Specified person is not a regular employee";
	const char * const EmployeeHasNoManager          = "Employee has no manager at the moment";
	const char * const CannotPromoteManagers         = "Cannot promote employee with managerial role";
	const char * const CannotFireAssignedManager     = "Cannot fire a manager who has employees assigned";
	
/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


#endif // _MESSAGES_HPP_
