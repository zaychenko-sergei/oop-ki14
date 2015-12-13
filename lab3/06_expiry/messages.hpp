// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const NonPositiveAmount          = "Consignment amount must be positive";
	const char * const NonPositivePrice           = "Product price must be positive";
	const char * const NonPositiveExpiryDays      = "Number of days to expire must be positive";

	const char * const EmptyProductName           = "Product name cannot be empty";
	const char * const ProductNotUnique           = "Product with this name has already been added";
	const char * const ProductNotFound        = "Product cannot be found";

	const char * const ExpectLaterDate            = "New date must be later than current";

	const char * const SellingExpired             = "Trying to sell an expired product";
	const char * const SellingOverAmount          = "It is not enough products to sell";

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _MESSAGES_HPP_
