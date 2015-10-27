// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const InvalidStudentName = "Invalid student name";
	const char * const StudentBirthdayTooLate = "Student birthday is not earlier than current date";
	const char * const StudentIdNotUnique = "Student ID must be unique";
	const char * const StudentNotFound = "Student not found";

	const char * const InvalidGroupName = "Invalid group name";
	const char * const GroupNameNotUnique = "Group name must be unique";
	const char * const GroupNotFound = "Group not found";
	
	const char * const StudentCannotStudyInTwoGroups = "Student cannot be in two groups simultaneously";
	const char * const CaptainMustStudyInGroup = "Captain must study in the group";
	const char * const RemovingStudentNotInGroup = "Student must study in the group";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_