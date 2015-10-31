// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const EmptyFullName = "Full name cannot be empty";
	const char * const EmptyPhoneNumber = "Phone number cannot be empty";
	const char * const DuplicateContact = "Contact has already been registered";
	const char * const ContactCannotBeFound = "Contact cannot be found";
	const char * const InvalidCallTime = "Call's time is not earlier than current time";
	const char * const InvalidCallDuration = "Call's duration cannot be negative";

	const char * const InvalidDateTime = "Date is not valid";
	const char * const InvalidDateTimeFormat = "Date format is incorrect";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_
