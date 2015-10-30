// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/


namespace Messages
{
	const char * const EmptyProductName       = "Product name cannot be empty";
	const char * const NegativeProteins       = "Proteins must be zero or positive";
	const char * const NegativeFat            = "Fat must be zero or positive";
	const char * const NegativeCarbohydrates  = "Carbohydrates must be zero or positive";
	const char * const NegativeEnergeticValue = "Energetic value must be zero or positive";
	const char * const ProductNotIncluded     = "Product was not included to the menu";
	const char * const ProductAlreadyIncluded = "Product was already included to the menu";
	const char * const NonPositiveWeight      = "Weight must be positive";
	const char * const EmptyMenuTitle         = "Menu name cannot be empty";
	const char * const MenuNotFound           = "Menu with specified name not found";
	const char * const MenuAlreadyExists      = "Menu with specified name already exists";
	const char * const ProductNotFound        = "Product with specified name not found";
	const char * const ProductAlreadyExists   = "Product with specified name already exists";
}


/*****************************************************************************/

#endif // _MESSAGES_HPP_