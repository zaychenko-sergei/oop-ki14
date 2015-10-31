// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "programcategory.hpp"

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

	void createProgram (
			std::string const & _name
		,	std::string const & _manufacturer
		,	std::string const & _version
		,	unsigned int _releaseYear
		,	ProgramCategory _category
	);

	std::string const & getProgramManufacturer ( std::string const & _name, std::string const & _version ) const;

	int getProgramReleaseYear ( std::string const & _name, std::string const & _version ) const;

	ProgramCategory getProgramCategory ( std::string const & _name, std::string const & _version ) const;

/*-----------------------------------------------------------------*/

	void createAccount ( std::string const & _login, std::string const & _fullName );

	std::string const & getAccountFullName ( std::string const & _login ) const;

	std::string getAccountPreferredBrowserName ( std::string const & _login ) const;

	std::string getAccountPreferredOfficeToolName ( std::string const & _login ) const;

/*-----------------------------------------------------------------*/

	void setAccountPreferredBrowser (
			std::string const & _login
		,	std::string const & _programName
		,	std::string const & _programVersion
	);

	void setAccountPreferredOfficeTool(
			std::string const & _login
		,	std::string const & _programName
		,	std::string const & _programVersion
	);

/*-----------------------------------------------------------------*/

	std::vector< std::string > getUsersPreferringBrowser ( std::string const & _browserName ) const;

	int getUsersCountWithBrowsersAndOffice (
			std::string const & _browserName
		,	std::string const & _officeToolName
	) const;

	std::vector< std::string > getUsersPreferringOlderOfficeVersion () const;

	std::vector< std::pair< std::string, std::string > > getProgramsWithoutPreferences () const;

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
