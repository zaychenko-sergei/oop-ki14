// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const InvalidRegistrationNumberFormat = "Invalid registration number format";
	const char * const InvalidPaymentTime = "Payment's time is not earlier than current time";
	const char * const InvalidPaymentSum = "Invalid payment sum";
	const char * const EmptyPaymentPurpose = "Payment purpose cannot be empty";
	const char * const EmptyPaymentId = "Payment identifier cannot be empty";
	const char * const EmptyOrganizationName = "Organization name cannot be empty";
	const char * const DuplicatePayment = "Payment has already been added";
	const char * const DuplicateOrganization = "Organization has already been added";
	const char * const DuplicateRegistrationNumber = "Registration number has already been added";
	const char * const PaymentForItself = "Cannot add payment for itself";
	const char * const OrganizationCannotBeFound = "Organization cannot be found";
	const char * const PaymentCannotBeFound = "Payment cannot be found";

	const char * const InvalidDateTime = "Date is not valid";
	const char * const InvalidDateTimeFormat = "Date format is incorrect";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_
