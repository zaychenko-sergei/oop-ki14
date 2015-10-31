// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const DocumentRightsAlreadyExists = "Requested document rights already exists for current user";
	const char * const DocumentRightsDoesNotExist = "Requested document rights does not exist for current user";
	const char * const UserLoginIsEmpty = "User login is empty";
	const char * const UserFullNameEmpty = "Full user name is empty";
	const char * const DocumentNameIsEmpty = "Document name is empty";
	const char * const DocumentPathIsEmpty = "Path to document is empty";
	const char * const UserLoginAlreadyExists = "Requested login name for user already exists";
	const char * const UserLoginDoesNotExist = "Requested login name for user does not exist";
	const char * const DocumentDoesNotExist = "Requested document does not exist";
	const char * const DocumentAlreadyExists = "Document with such ID already exists";

}

/*****************************************************************************/

#endif // _MESSAGES_HPP_