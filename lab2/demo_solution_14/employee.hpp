// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_

/*****************************************************************************/

#include <string>
#include <vector>
#include <memory>
#include <functional>

/*****************************************************************************/

class Skill;

/*****************************************************************************/


class Employee
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Employee ( std::string const & _name,
		       std::string const & _position,
		       int _birthYear );

	~ Employee ();

	const std::string & getName () const;

	const std::string & getPosition () const;

	int getBirthYear () const;

	void addSkill ( std::unique_ptr< Skill > _skill );

	int getSkillsCount () const;

	Skill const & getSkill ( int _index ) const;

	Skill const * findSkill ( std::string const & _name ) const;

	typedef std::vector< std::unique_ptr< Skill > >::const_iterator SkillIterator;

	SkillIterator skillsBegin () const;

	SkillIterator skillsEnd () const;

	class IterableSkills
	{
	public:

		IterableSkills ( SkillIterator _chaptersBegin, SkillIterator _chaptersEnd )
			: m_begin( _chaptersBegin ), m_end( _chaptersEnd )
		{}

		SkillIterator begin () const { return m_begin; }
		SkillIterator end () const { return m_end; }

	private:

		SkillIterator m_begin, m_end;
	};


	IterableSkills skills () const;

	void forEachSkill ( std::function< void ( Skill const & ) > _action ) const;

	int getTotalSkillPoints () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	const std::string m_name;

	const std::string m_position;

	int m_birthYear;

	std::vector< std::unique_ptr< Skill > > m_skills;

/*-----------------------------------------------------------------*/  

};


/*****************************************************************************/


inline const std::string & 
Employee::getName () const
{
	return m_name;
}


/*****************************************************************************/


inline const std::string & 
Employee::getPosition () const
{
	return m_position;
}


/*****************************************************************************/


inline int 
Employee::getBirthYear () const
{
	return m_birthYear;
}


/*****************************************************************************/


inline int 
Employee::getSkillsCount () const
{
	return m_skills.size();
}


/*****************************************************************************/


inline Skill const & 
Employee::getSkill ( int _index ) const
{
	return *( m_skills.at( _index ) );
}


/*****************************************************************************/


inline Employee::SkillIterator 
Employee::skillsBegin () const
{
	return m_skills.begin();
}


/*****************************************************************************/


inline Employee::SkillIterator
Employee::skillsEnd () const
{
	return m_skills.end();
}


/*****************************************************************************/


inline
Employee::IterableSkills 
Employee::skills () const
{
	return IterableSkills( skillsBegin(), skillsEnd() );
}


/*****************************************************************************/

#endif //  _EMPLOYEE_HPP_
