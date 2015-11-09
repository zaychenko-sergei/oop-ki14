// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const DocumentRightsAlreadyDefined = "Requested document rights already defined for current user";
	const char * const DocumentRightsUndefined = "Requested document rights were not defined for current user";
	const char * const UserLoginIsEmpty = "User login is empty";
	const char * const UserFullNameEmpty = "Full user name is empty";
	const char * const DocumentNameIsEmpty = "Document name is empty";
	const char * const DocumentPathIsEmpty = "Path to document is empty";
	const char * const UserLoginAlreadyExists = "Duplicate login";
	const char * const UserLoginDoesNotExist = "User login is unresolved";
	const char * const DocumentDoesNotExist = "Requested document does not exist";
	const char * const DocumentAlreadyExists = "Duplicate document ID";

}

/*****************************************************************************/

#endif // _MESSAGES_HPP_