// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const AbsentProgramName = "Program name cannot be absent";
	const char * const AbsentManufacturer = "Manufacturer cannot be absent";
	const char * const AbsentVersion = "Version of the program cannot be absent";

	const char * const AbsentLogin = "Login cannot be absent";
	const char * const AbsentFullName = "Full user name cannot be absent";

	const char * const ProgramDoesNotFound = "Program with specified version doesn't found";
	const char * const AccountDoesNotFound = "Account with specified login doesn't found";

	const char * const LoginShouldBeUnique = "Login of the account isn't unique";
	const char * const VersionDuplication = "Only single version of single program allowed";

	const char * const ProgramCategoryMismatch = "Another category of the program expected";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_