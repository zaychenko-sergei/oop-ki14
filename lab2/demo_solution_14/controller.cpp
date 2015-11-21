// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"

#include "employee.hpp"
#include "skill.hpp"

#include <algorithm>

/*****************************************************************************/


Controller::Controller () = default;


/*****************************************************************************/  


Controller::~Controller () = default;


/*****************************************************************************/  


void Controller::addEmployee (
		std::string const & _employeeName
	,	std::string const & _position
	,	int _birthYear
)
{
	if ( findEmployee( _employeeName ) )
		throw std::logic_error( Messages::EmployeeAlreadyExists );

	m_employees[ _employeeName ] = 
		std::make_unique< Employee >( _employeeName, _position, _birthYear );
}


/*****************************************************************************/


std::string const & 
Controller::getEmployeePosition ( std::string const & _employeeName ) const
{
	return resolveEmployee( _employeeName ).getPosition();
}


/*****************************************************************************/


int Controller::getEmployeeBirthYear ( std::string const & _employeeName ) const
{
	return resolveEmployee( _employeeName ).getBirthYear();
}


/*****************************************************************************/


Employee *
Controller::findEmployee ( std::string const & _name ) const
{
	auto it = m_employees.find( _name );
	return ( it == m_employees.end() ) ? nullptr : it->second.get();
}


/*****************************************************************************/


Employee & 
Controller::resolveEmployee ( std::string const & _name ) const
{
	Employee * pEmployee = findEmployee( _name );
	if ( pEmployee )
		return *pEmployee;

	throw std::logic_error( Messages::EmployeeDoesNotExist );
}


/*****************************************************************************/


void
Controller::addSkillForEmployee (
		std::string const & _employeeName
	,	std::string const & _skillName
	,	int _level
)
{
	Employee & e = resolveEmployee( _employeeName );
	e.addSkill( std::make_unique< Skill >( _skillName, _level ) );
}


/*****************************************************************************/


int
Controller::getEmployeeSkillsCount ( std::string const & _employeeName ) const
{
	return resolveEmployee( _employeeName ).getSkillsCount();
}


/*****************************************************************************/


int
Controller::getEmployeeSkillLevel (
		std::string const & _employeeName
	,	std::string const & _skillName
) const
{
	Employee const & e = resolveEmployee( _employeeName );
	Skill const * pSkill = e.findSkill( _skillName );
	if ( pSkill )
		return pSkill->getLevel();

	else
		throw std::logic_error( Messages::SkillUndefinedForEmployee );
}


/*****************************************************************************/


std::unordered_set< std::string >
Controller::getEmployeeSkillNames ( std::string const & _employeeName ) const
{
	std::unordered_set< std::string > result;

	const Employee & e = resolveEmployee( _employeeName );

	// Alternative: using getSkillsCount()/getSkill(index) methods
	/*for ( int i = 0; i < e.getSkillsCount(); i++ )
		result.insert( e.getSkill( i ).getName() );
		*/
/*
	// Alternative: using ranged-based for loop and container iterators
	for ( auto const & pSkill : e.skills() )
		result.insert( pSkill->getName() );
		*/

	e.forEachSkill(
		[ & ] ( const Skill & _skill )
		{
			result.insert( _skill.getName() );
		}
	);

	return result;
}

/*****************************************************************************/


Controller::BestSkill 
Controller::getEmployeeBestSkill ( std::string const & _employeeName ) const
{
	const Employee & e = resolveEmployee( _employeeName );

	BestSkill result( "", 0 );

	for ( int i = 0; i < e.getSkillsCount(); i++ )
	{
		const Skill & s = e.getSkill( i );
		if ( s.getLevel() > result.second )
		{
			result.first = s.getName();
			result.second = s.getLevel();
		}
	}

	return result;
}


/*****************************************************************************/


Controller::BestEmployees Controller::getBestEmployeesHavingSkill (
		std::string const & _skillName
	,	const int _bestCount
) const
{
	if ( _bestCount <= 0 )
		throw std::exception();

	struct Record
	{
		std::string m_employeeName;
		int m_levelInSelectedSkill;

		Record ( std::string const & _employeeName, int _levelInSelectedSkill )
			:	m_employeeName( _employeeName ), m_levelInSelectedSkill( _levelInSelectedSkill )
		{}
	};

	std::vector< Record > employeesWithSelectedSkill;

	for ( auto const & p : m_employees )
	{
		Employee const & e = *p.second;
		Skill const * pSkill = e.findSkill( _skillName );
		if ( pSkill )
			employeesWithSelectedSkill.push_back( Record( e.getName(), pSkill->getLevel() ) );
	}

	std::sort( 
		employeesWithSelectedSkill.begin(), employeesWithSelectedSkill.end(),
		[ & ] ( Record const & r1, Record const & r2 )
		{
			if ( r1.m_levelInSelectedSkill > r2.m_levelInSelectedSkill )
				return true;

			else if ( r1.m_levelInSelectedSkill == r2.m_levelInSelectedSkill )
				return r1.m_employeeName < r2.m_employeeName;

			else
				return false;
		}
	);

	int nEmployeesWithSkill = employeesWithSelectedSkill.size();
	int resultSize = ( _bestCount < nEmployeesWithSkill ) ? _bestCount : nEmployeesWithSkill;

	BestEmployees best;
	for ( int i = 0; i < resultSize; i++ )
		best.insert( employeesWithSelectedSkill[ i ].m_employeeName );

	return best;
}


/*****************************************************************************/


std::string
Controller::getEldestEmployeeWithSkillAtLeast (
		std::string const & _skillName
	,	int _minSkillLevel
) const
{
	struct Record
	{
		std::string m_employeeName;
		int m_birthYear;

		Record ( std::string const & _name, int _birthYear )
			: m_employeeName( _name ), m_birthYear( _birthYear )
		{}
	};

	std::vector< Record > filteredEmployees;

	for ( auto const & p : m_employees )
	{
		Employee const & e = * p.second;
		Skill const * pSkill = e.findSkill( _skillName );
		if ( pSkill && pSkill->getLevel() >= _minSkillLevel )
			filteredEmployees.push_back( Record( e.getName(), e.getBirthYear() ) );
	}

	std::sort(
		filteredEmployees.begin(), filteredEmployees.end(),
		[ & ] ( Record const & r1, Record const & r2 )
		{
			if ( r1.m_birthYear < r2.m_birthYear )
				return true;

			else if ( r1.m_birthYear == r2.m_birthYear )
				return r1.m_employeeName < r2.m_employeeName;

			else
				return false;
		}
	);

	return ( filteredEmployees.empty() ) ? "" : filteredEmployees.front().m_employeeName;
}


/*****************************************************************************/


std::string Controller::getEmployeeWithBiggestTotalSkillPoints () const
{
	Employee const * pBestEmployee = nullptr;
	int bestTotal = 0;

	for ( auto const & p : m_employees )
	{
		Employee const & e = * p.second;
		int employeeTotal = e.getTotalSkillPoints();
		if ( employeeTotal > bestTotal )
		{
			pBestEmployee = & e;
			bestTotal = employeeTotal;
		}
	}

	return ( pBestEmployee ) ? pBestEmployee->getName() : "";
}


/*****************************************************************************/
