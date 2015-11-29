// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const ProgramNameNotUnique          = "Program name must be unique";
	const char * const ProgramNameEmpty              = "Program name cannot be empty";
	const char * const VendorNameEmpty               = "Vendor name cannot be empty";
	const char * const ProgramNotRegistered          = "Program was not registered";
	const char * const DuplicateLicense              = "Program already has a license";
	const char * const ProgramHasNoLicense           = "Program was not associated with a license";
	const char * const ExpiryEarlierThanIssue        = "License should not expire earlier than issue date";
	const char * const NonPositiveTokens             = "Number of tokens must be positive";
	const char * const NoValidLicense                = "No valid license found for the program";
	const char * const TokenBasedLicenseExpected     = "Operation requires a token-based license";
	const char * const TimeBasedLicenseExpected      = "Operation requires a time-based license";
	const char * const ProlongingToEarlierDate       = "Prolonging license to a date that is earlier than previus expiry date";


/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


#endif // _MESSAGES_HPP_
