// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const DidNotOpenParentPreviously = "Attempting to close parent node that was not open previously";
	const char * const NodePathUnresolved         = "Node with the specified path does not exist";
	const char * const NotAParentNode             = "Expected a parent node, but leaf node was specified";

	const char * const EmptyDescriptionText   = "Description text is empty";

	const char * const TreeItemHasNotChildren = "Tree item has not any children";

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _MESSAGES_HPP_
