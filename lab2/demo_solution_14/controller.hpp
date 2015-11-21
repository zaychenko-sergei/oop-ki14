// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class Employee;

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

	void addEmployee (
			std::string const & _employeeName
		,	std::string const & _position
		,	int _birthYear
	);

	std::string const & getEmployeePosition ( std::string const & _employeeName ) const;

	int getEmployeeBirthYear ( std::string const & _employeeName ) const;

/*-----------------------------------------------------------------*/

	void addSkillForEmployee (
			std::string const & _employeeName
		,	std::string const & _skillName
		,	int _level
	);

	int getEmployeeSkillsCount ( std::string const & _employeeName ) const;

	int
	getEmployeeSkillLevel (
			std::string const & _employeeName
		,	std::string const & _skillName
	) const;

	std::unordered_set< std::string >
	getEmployeeSkillNames ( std::string const & _employeeName ) const;

/*-----------------------------------------------------------------*/

	typedef
		std::pair< std::string /*skill name*/, int /*level*/ >
		BestSkill;

	BestSkill getEmployeeBestSkill ( std::string const & _employeeName ) const;

	typedef
		std::unordered_set< std::string >
		BestEmployees;

	BestEmployees getBestEmployeesHavingSkill (
			std::string const & _skillName
		,	const int _bestCount 
	) const;

	std::string 
	getEldestEmployeeWithSkillAtLeast (
			std::string const & _skillName
		,	int _skillLevel
	) const;

	std::string getEmployeeWithBiggestTotalSkillPoints () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	Employee * findEmployee ( std::string const & _name ) const;

	Employee & resolveEmployee ( std::string const & _name ) const;

/*-----------------------------------------------------------------*/

	std::unordered_map< std::string, std::unique_ptr< Employee > > m_employees;

/*-----------------------------------------------------------------*/  

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
