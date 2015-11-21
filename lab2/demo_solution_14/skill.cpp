// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "skill.hpp"

#include "messages.hpp"

/*****************************************************************************/


Skill::Skill ( const std::string & _name, int _level )
	:	m_name( _name ), m_level( _level )
{
	if ( m_name.empty() )
		throw std::logic_error( Messages::SkillNameIsEmpty );

	if ( m_level < 0 || m_level > 10 )
		throw std::logic_error( Messages::WrongSkillLevelRange );
}


/*****************************************************************************/   