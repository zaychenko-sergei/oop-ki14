// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "ownershiprights.hpp"

#include <vector>
#include <string>

/*****************************************************************************/


class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void addUser ( std::string const & _login, std::string const & _fullName );

	std::string const & getUserFullName ( std::string const & _login ) const;

/*-----------------------------------------------------------------*/

	void addDocument ( 
		unsigned int _uid, 
		std::string const & _name, 
		std::string const & _path, 
		OwnershipRights _defaultRight
	);

	std::string const & getDocumentName ( unsigned int _uid ) const;

	std::string const & getDocumentPath ( unsigned int _uid ) const;

	OwnershipRights getDocumentDefaultRights ( unsigned int _uid ) const;

/*-----------------------------------------------------------------*/

	void addDocumentRightsForUser ( 
		std::string const & _userLogin,
		int _documentUid,
		OwnershipRights _rights 
	);

	void changeDocumentRightsForUser (
		std::string const & _userLogin,
		unsigned int _documentUid,
		OwnershipRights _rights
	);

	void eraseDocumentRightsForUser ( 
		std::string const & _userLogin, 
		unsigned int _documentUid 
	);

	OwnershipRights getDocumentRightsForUser( 
		std::string const & _userLogin, 
		unsigned int _documentUid 
	) const;

/*-----------------------------------------------------------------*/

	typedef
		std::unordered_map<
				std::string /* login */
			,	std::unordered_map<
						unsigned int /* uid */
					,	OwnershipRights
				>
		>
	AllRights;

	AllRights getUserPermissionsReport () const;

	typedef
		std::unordered_map< unsigned int /* uid */, std::string /*name*/ >
		DocumentsInfo;

	DocumentsInfo getDocumentsNotHavingPermittedUsers () const;

	std::unordered_set< std::string /* login */ >
	getUsersNotHavingPermittedDocuments () const;

	DocumentsInfo getDocumentsHavingMultipleWriteUsers () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

    // TODO: place private methods here

/*-----------------------------------------------------------------*/

    // TODO: place private fields here

/*-----------------------------------------------------------------*/  

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
