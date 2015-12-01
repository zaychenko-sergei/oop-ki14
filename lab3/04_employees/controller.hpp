// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "regularemployeelevel.hpp"

#include <string>
#include <unordered_set>

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

	void createManager ( std::string const & _fullName );

	void createRegular ( 
			std::string const & _fullName
		,	RegularEmployeeLevel _startingLevel
	);

	bool isKnownEmployee ( std::string const & _fullName ) const;

	RegularEmployeeLevel getRegularEmployeeLevel ( std::string const & _fullName ) const;

	double getEmployeeSalary ( std::string const & _fullName, double _baseSalary );

	double getTotalSalary ( double _baseSalary ) const;

	void changeBonus ( std::string const & _fullName, double _newBonus );

	double getEmployeeBonus ( std::string const & _fullName ) const;

	std::string getEmployeeManager ( std::string const & _fullName ) const;

	std::unordered_set< std::string > getManagerSubordinates ( std::string const & _fullName ) const;

	void assignManager ( std::string const & _employeeFullName, std::string const & _managerFullName );

	void deassignManager ( std::string const & _employeeFullName );

	void promote ( std::string const & _employeeFullName );

	void fire ( std::string const & _employeeFullName );

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	// TODO ...

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
