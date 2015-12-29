// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const EmptyConsumerName          = "Name of the consumer is empty";
	const char * const EmptyConsumerAddress       = "Address of the consumer is empty";
	const char * const NegativeConsumerID         = "ID of the consumer must be non-negative";
	const char * const NonUniqueConsumerID        = "ID of the consumer must be unique";
	const char * const UnknownConsumerID          = "Consumer with the specified ID was not previously registered";
	const char * const NonPositiveConsumption     = "The amount of consumed water should be positive";
	const char * const NegativePrice              = "Price may not be negative";
	const char * const SubsidizedConsumersDontPay = "Subsidized consumer should not pay any money for the water";

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


#endif // _MESSAGES_HPP_
