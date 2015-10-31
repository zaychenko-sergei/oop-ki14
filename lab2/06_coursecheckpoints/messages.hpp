// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const CheckpointsSumMismatch = "Checkpoints' sum != 100";
	const char * const CheckpointsCountMismatch = "Checkpoints' count == 0";
	const char * const EmptyCheckpointName = "Checkpoint name cannot be empty";
	const char * const EmptyCourseName = "Course name cannot be empty";
	const char * const EmptyStudentName = "Student name cannot be empty";
	const char * const InvalidMarkValue = "Invalid mark value";
	const char * const MarkCannotBeFound = "Mark cannot be found";
	const char * const CourseCannotBeFound = "Course cannot be found";
	const char * const CheckpointCannotBeFound = "Checkpoint cannot be found";
	const char * const StudentCannotBeFound = "Student cannot be found";
	const char * const DuplicateCourse = "Course has already beed added";
	const char * const DuplicateStudent = "Student has already beed added";
	const char * const DuplicateCheckpointMark = "Student has already beed marked for this checkpoint";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_
