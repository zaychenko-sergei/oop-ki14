// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const UnknownAccountID = "Account ID is not recognized";

	const char * const AccountIDNotUnique       = "Account ID must be unique";
	const char * const OwnerNameNotUnique       = "Owner name must be unique";
	const char * const OwnerNameIsEmpty         = "Owner name may not be empty";
	const char * const NegativeInitialBalance   = "Cannot create account with negative initial balance";
	const char * const NegativeOverdraft        = "Cannot create account with negative overdraft setting";
	const char * const NonPositiveDeposit       = "Cannot deposit negative or zero amount of money";
	const char * const NonPositiveWithdrawal    = "Cannot withdraw negative or zero amount of money";
	const char * const NonPositiveTransfer      = "Cannot transfer negative or zero amount of money";
	const char * const WithdrawalLimitExceeded  = "Withdrawal limit exceeded";

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


#endif // _MESSAGES_HPP_
