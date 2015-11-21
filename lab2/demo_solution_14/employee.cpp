// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "employee.hpp"
#include "skill.hpp"
#include "messages.hpp"

#include <algorithm>

/*****************************************************************************/


Employee::Employee (
	std::string const & _name,
	std::string const & _position,
	int _birthYear 
)
	:	m_name( _name ), m_position( _position ), m_birthYear( _birthYear )
{
	if ( m_name.empty() )
		throw std::logic_error( Messages::EmployeeNameIsEmpty );

	if ( m_position.empty() )
		throw std::logic_error( Messages::EmployeePositionIsEmpty );

	if ( _birthYear > 2015 )
		throw std::logic_error( Messages::EmployeeBornInFuture );

}


/*****************************************************************************/   


Employee::~Employee () = default;


/*****************************************************************************/


void Employee::addSkill ( std::unique_ptr< Skill > _skill )
{
	if ( findSkill( _skill->getName() ) )
		throw std::logic_error( Messages::SkillAlreadyDefinedForEmployee );

	m_skills.push_back( std::move( _skill ) );
}


/*****************************************************************************/


Skill const *
Employee::findSkill ( std::string const & _name ) const
{
	auto it = std::find_if( 
				m_skills.begin(), m_skills.end(), 
				[ & ] ( auto const & _skill )
				{
					return _skill->getName() == _name;
				}
			 );

	if ( it == m_skills.end() )
		return nullptr;

	else
		return it->get();
}


/*****************************************************************************/


void Employee::forEachSkill ( std::function< void ( Skill const & ) > _action ) const
{
	for ( auto const & pSkill : m_skills )
		_action( * pSkill );
}


/*****************************************************************************/


int Employee::getTotalSkillPoints () const
{
	int total = 0;
	for ( auto const & pSkill : m_skills )
		total += pSkill->getLevel();
	return total;
}


/*****************************************************************************/
