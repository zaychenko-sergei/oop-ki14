// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "date.hpp"
#include "license_type.hpp"

#include <string>

/*****************************************************************************/


class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

	~ Controller ();

/*-----------------------------------------------------------------*/

	void createProgram ( std::string const & _name, std::string const & _vendorName );

	std::string const & getProgramVendor ( std::string const & _programName ) const;

	void createPerpetualLicense ( std::string const & _programName, Date _issued );

	void createTimeBasedLicense ( std::string const & _programName, Date _issued, Date _expires );

	void createTokenBasedLicense ( std::string const & _programName, Date _issued, int _nTokens );

	LicenseType getProgramLicenseType ( const std::string & _programName ) const;

	Date getProgramLicenseIssueDate ( const std::string & _programName ) const;

	bool canUse ( std::string const & _programName, Date _date ) const;

	void trackUse ( std::string const & _programName, Date _date );

	void prolongLicense ( std::string const & _programName, Date _newExpires );

	Date getLicenseExpiryDate ( std::string const & _programName ) const;

	int getLicenseTokensLeft ( std::string const & _programName ) const;

	void addLicenseTokens ( std::string const & _programName, int _nTokens );

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	// TODO ...

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
