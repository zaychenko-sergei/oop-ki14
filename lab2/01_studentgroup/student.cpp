// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "student.hpp"
#include "messages.hpp"

/*****************************************************************************/


Student::Student ( int _registrationId, std::string const & _fullName, Date _birthDay, StudyForm _studyForm )
	:	m_registrationId( _registrationId )
	,	m_fullName( _fullName )
	,	m_birthday( _birthDay )
	,	m_studyForm( _studyForm )
{
	if ( _fullName.empty() )
		throw std::logic_error( Messages::InvalidStudentName );

	if ( _birthDay >= Date() )
		throw std::logic_error( Messages::StudentBirthdayTooLate );
}


/*****************************************************************************/
