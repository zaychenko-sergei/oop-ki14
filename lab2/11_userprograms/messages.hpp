// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const EmptyProgramName = "Program name cannot be empty";
	const char * const EmptyManufacturer = "Manufacturer cannot be empty";
	const char * const EmptyVersion = "Version of the program cannot be empty";

	const char * const EmptyLogin = "Login cannot be empty";
	const char * const EmptyFullName = "Full user name cannot be empty";

	const char * const ProgramNotFound = "Program with specified version was not found";
	const char * const AccountNotFound = "Account with specified login was not found";

	const char * const LoginShouldBeUnique = "Login of the account isn't unique";
	const char * const VersionDuplication = "Only single version of same program is allowed";

	const char * const ProgramCategoryMismatch = "Another category of the program expected";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_