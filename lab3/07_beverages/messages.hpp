// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const CustomerNameNotUnique = "Name of the customer must be unique";
	const char * const CustomerNameUnknown   = "Name of the customer is not recognized";
	const char * const BeverageNameNotUnique = "Name of the beverage must be unique";
	const char * const BeverageNameUnknown   = "Name of the beverage is not recognized";

	const char * const NegativeAge           = "Age must not be negative";
	const char * const NegativeBalance       = "Balance must not be negative";
	const char * const NonPositiveAmount     = "Amount must be positive";
	const char * const NonPositivePrice      = "Price must be positive";

	const char * const EmptyIngredientName   = "Ingredient name cannot be empty";
	const char * const EmptyCustomerName     = "Customer name cannot be empty";
	const char * const EmptyBeverageName     = "Beverage name cannot be empty";

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _MESSAGES_HPP_
