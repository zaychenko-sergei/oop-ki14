// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "ownershiprights.hpp"

#include <string>
#include <unordered_set>
#include <unordered_map>

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
		int _documentID, 
		std::string const & _name, 
		std::string const & _path, 
		OwnershipRights _defaultRight
	);

	std::string const & getDocumentName ( int _documentID ) const;

	std::string const & getDocumentPath ( int _documentID ) const;

	OwnershipRights getDocumentDefaultRights ( int _documentID ) const;

/*-----------------------------------------------------------------*/

	void addDocumentRightsForUser ( 
		std::string const & _userLogin,
		int _documentID,
		OwnershipRights _rights 
	);

	void changeDocumentRightsForUser (
		std::string const & _userLogin,
		int _documentID,
		OwnershipRights _rights
	);

	void eraseDocumentRightsForUser ( 
		std::string const & _userLogin, 
		int _documentID
	);

	OwnershipRights getDocumentRightsForUser( 
		std::string const & _userLogin, 
		int _documentID
	) const;

/*-----------------------------------------------------------------*/

	typedef
		std::unordered_map<
				std::string /* login */
			,	std::unordered_map<
						int /* _documentID */
					,	OwnershipRights
				>
		>
	AllRights;

	AllRights getUserPermissionsReport () const;

	typedef
		std::unordered_map< int /* _documentID */, std::string /*name*/ >
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
