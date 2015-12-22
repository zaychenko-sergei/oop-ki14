// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const NegativeConsumerID       = "ID of consumer must be non-negative";
	const char * const NonUniqueConsumerID      = "ID of the consumer must be unique";
	const char * const UnknownConsumerID        = "Consumer with the specified ID was not previously registered";
	const char * const NonPositiveConsumption   = "The amount of consumed energy should be positive";
	const char * const NonPositivePaymentAmount = "Payment amount should be positive";
	const char * const SystemConsumersDontPay   = "System consumer should not pay any money for the energy";
	const char * const ConsumerBlocked          = "Consumer can't consume energy caused by lock";

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


#endif // _MESSAGES_HPP_