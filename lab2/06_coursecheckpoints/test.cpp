// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"
#include "utils.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_1_add_course_one )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_2_add_course_several )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Test );
	c.addCourse( "math", ControlForm::Exam );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_3_add_course_with_the_same_name )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );

	ASSERT_THROWS(
			c.addCourse( "oop", ControlForm::Exam );
		,	Messages::DuplicateCourse
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_4_add_course_with_the_same_control_form )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCourse( "cucumber", ControlForm::Exam );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_5_add_course_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addCourse( "", ControlForm::Exam );
		,	Messages::EmptyCourseName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_6_add_course_obtain_control_form_by_name )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Test );

	assert( c.getCourseControlForm( "cucumber" ) == ControlForm::Test );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_7_add_course_obtain_control_form_by_empty_name )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Test );

	ASSERT_THROWS(
			c.getCourseControlForm( "" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_1_8_add_course_obtain_control_form_for_missing_course )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Test );

	ASSERT_THROWS(
			c.getCourseControlForm( "oop" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_1_add_checkpoint_one )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 100 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_2_1_add_checkpoint_several_for_one_cource )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 50 );
	c.addCheckpoint( "cucumber", "pampam", 50 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_2_2_add_checkpoint_several_for_different_cources )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 99 );
	c.addCheckpoint( "oop", "classes", 99 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_3_add_checkpoint_with_empty_course_name )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Test );

	ASSERT_THROWS(
			c.addCheckpoint( "", "fresh", 99 );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_4_add_checkpoint_with_empty_checkpoint_name )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Test );

	ASSERT_THROWS(
			c.addCheckpoint( "cucumber", "", 99 );
		,	Messages::EmptyCheckpointName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_5_add_checkpoint_with_bad_mark )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Test );

	ASSERT_THROWS(
			c.addCheckpoint( "cucumber", "fresh", 0 );
		,	Messages::InvalidMarkValue
	);
	ASSERT_THROWS(
			c.addCheckpoint( "cucumber", "fresh", -5 );
		,	Messages::InvalidMarkValue
	);
	ASSERT_THROWS(
			c.addCheckpoint( "cucumber", "fresh", 101 );
		,	Messages::InvalidMarkValue
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_6_1_add_checkpoint_obtain_max_mark_correct )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 99 );
	c.addCheckpoint( "cucumber", "cake", 57 );

	assert( c.getCheckpointMaxMark( "cucumber", "fresh" ) == 99 );
	assert( c.getCheckpointMaxMark( "cucumber", "cake" ) == 57 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_6_2_add_checkpoint_obtain_max_mark_with_empty_course_name )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 99 );
	
	ASSERT_THROWS(
			c.getCheckpointMaxMark( "", "fresh" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_6_3_add_checkpoint_obtain_max_mark_for_missing_course )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 99 );
	
	ASSERT_THROWS(
			c.getCheckpointMaxMark( "oop", "fresh" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_7_1_add_checkpoint_obtain_min_mark_correct )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 67 );
	c.addCheckpoint( "cucumber", "cake", 35 );

	assert( c.getCheckpointMinMark( "cucumber", "fresh" ) == 40 );
	assert( c.getCheckpointMinMark( "cucumber", "cake" )  == 21 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_7_2_add_checkpoint_obtain_min_mark_with_empty_course_name )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 67 );
	
	ASSERT_THROWS(
			c.getCheckpointMinMark( "", "fresh" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_7_3_add_checkpoint_obtain_min_mark_for_missing_course )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 99 );
	
	ASSERT_THROWS(
			c.getCheckpointMinMark( "oop", "fresh" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_8_1_add_checkpoint_validate_correct )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 67 );
	c.addCheckpoint( "cucumber", "cake", 33 );

	c.validateCourseCheckpoints( "cucumber" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_8_2_add_checkpoint_validate_without_checkpoints )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );

	ASSERT_THROWS(
			c.validateCourseCheckpoints( "cucumber" );
		,	Messages::NoCheckpointsFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_8_3_add_checkpoint_validate_less_than_100 )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 34 );
	c.addCheckpoint( "cucumber", "cake", 46 );

	ASSERT_THROWS(
			c.validateCourseCheckpoints( "cucumber" );
		,	Messages::CheckpointsSumMismatch
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_8_4_add_checkpoint_validate_more_than_100 )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 82 );
	c.addCheckpoint( "cucumber", "cake", 79 );

	ASSERT_THROWS(
			c.validateCourseCheckpoints( "cucumber" );
		,	Messages::CheckpointsSumMismatch
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_8_5_add_checkpoint_validate_by_empty_course_name )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 82 );

	ASSERT_THROWS(
			c.validateCourseCheckpoints( "" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_8_6_add_checkpoint_validate_for_missing_course )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );
	c.addCheckpoint( "cucumber", "fresh", 82 );

	ASSERT_THROWS(
			c.validateCourseCheckpoints( "math" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_2_8_9_add_checkpoint_for_missing_course )
{
	Controller c;
	c.addCourse( "cucumber", ControlForm::Exam );

	ASSERT_THROWS(
			c.addCheckpoint( "pt", "gym", 69 );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_1_add_student_one )
{
	Controller c;
	c.addStudent( "Vitalka" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_2_add_student_several )
{
	Controller c;
	c.addStudent( "Vitalka" );
	c.addStudent( "Valerka" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_3_add_student_with_the_same_name )
{
	Controller c;
	c.addStudent( "Valerka" );

	ASSERT_THROWS(
			c.addStudent( "Valerka" );
		,	Messages::DuplicateStudent
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_4_add_student_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addStudent( "" );
		,	Messages::EmptyStudentName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_1_add_student_checkpoint_one )
{
	Controller c;
	c.addCourse( "math", ControlForm::Exam );
	c.addCheckpoint( "math", "division", 100 );

	c.validateCourseCheckpoints( "math" );

	c.addStudent( "Valera" );
	c.addStudentCheckpoint( "Valera", "math", "division", 60 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_2_add_student_checkpoint_several_for_one_student )
{
	Controller c;
	c.addCourse( "math", ControlForm::Exam );
	c.addCheckpoint( "math", "division", 50 );
	c.addCheckpoint( "math", "multiplication", 50 );

	c.validateCourseCheckpoints( "math" );
	
	c.addStudent( "Valera" );
	c.addStudentCheckpoint( "Valera", "math", "division", 40 );
	c.addStudentCheckpoint( "Valera", "math", "multiplication", 43 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_3_add_student_checkpoint_several_for_several_students )
{
	Controller c;
	c.addCourse( "math", ControlForm::Exam );
	c.addCheckpoint( "math", "division", 1 );
	c.addCheckpoint( "math", "multiplication", 99 );

	c.validateCourseCheckpoints( "math" );
	
	c.addStudent( "Valera" );
	c.addStudentCheckpoint( "Valera", "math", "division", 1 );
	c.addStudentCheckpoint( "Valera", "math", "multiplication", 99 );

	c.addStudent( "Ivan" );
	c.addStudentCheckpoint( "Ivan", "math", "division", 1 );
	c.addStudentCheckpoint( "Ivan", "math", "multiplication", 57 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_4_add_student_checkpoint_with_empty_student_name )
{
	Controller c;
	c.addCourse( "math", ControlForm::Exam );
	c.addCheckpoint( "math", "division", 23 );
	c.addCheckpoint( "math", "multiplication", 77 );

	c.validateCourseCheckpoints( "math" );

	c.addStudent( "Petr" );

	ASSERT_THROWS(
			c.addStudentCheckpoint( "", "math", "division", 41 );
		,	Messages::StudentCannotBeFound
	);
}

/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_5_add_student_checkpoint_with_empty_course_name )
{
	Controller c;
	c.addCourse( "math", ControlForm::Exam );
	c.addCheckpoint( "math", "division", 89 );
	c.addCheckpoint( "math", "multiplication", 11 );

	c.validateCourseCheckpoints( "math" );

	c.addStudent( "Petr" );

	ASSERT_THROWS(
			c.addStudentCheckpoint( "Petr", "", "division", 41 );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_6_add_student_checkpoint_with_empty_checkpoint_name )
{
	Controller c;
	c.addCourse( "math", ControlForm::Exam );
	c.addCheckpoint( "math", "division", 75 );
	c.addCheckpoint( "math", "multiplication", 25 );

	c.validateCourseCheckpoints( "math" );

	c.addStudent( "Petr" );

	ASSERT_THROWS(
			c.addStudentCheckpoint( "Petr", "math", "", 41 );
		,	Messages::CheckpointCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_7_add_student_checkpoint_with_bad_mark )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 88 );
	c.addCheckpoint( "oop", "functions", 12 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );

	ASSERT_THROWS(
			c.addStudentCheckpoint( "Ivanko", "oop", "classes", -5 );
		,	Messages::InvalidMarkValue
	);
	ASSERT_THROWS(
			c.addStudentCheckpoint( "Ivanko", "oop", "classes", 89 );
		,	Messages::InvalidMarkValue
	);
	ASSERT_THROWS(
			c.addStudentCheckpoint( "Ivanko", "oop", "functions", 13 );
		,	Messages::InvalidMarkValue
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_8_add_student_checkpoint_for_missing_student )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 100 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );

	ASSERT_THROWS(
			c.addStudentCheckpoint( "Vitalka", "oop", "classes", 80 );
		,	Messages::StudentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_9_add_student_checkpoint_for_missing_course )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 100 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );

	ASSERT_THROWS(
			c.addStudentCheckpoint( "Ivanko", "math", "classes", 80 );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_10_add_student_checkpoint_for_missing_checkpoint )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 100 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );

	ASSERT_THROWS(
			c.addStudentCheckpoint( "Ivanko", "oop", "functions", 80 );
		,	Messages::CheckpointCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_5_11_add_student_checkpoint_with_zero_mark )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 100 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_6_1_obtain_checkpoint_mark_correct )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	assert( c.getStudentCheckpointMark( "Ivanko", "oop", "classes" ) == 50 );
	assert( c.getStudentCheckpointMark( "Ivanko", "oop", "pointers" ) == 41 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_6_2_obtain_checkpoint_mark_with_empty_student_name )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	ASSERT_THROWS(
			c.getStudentCheckpointMark( "", "oop", "classes" );
		,	Messages::StudentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_6_3_obtain_checkpoint_mark_with_empty_course_name )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	ASSERT_THROWS(
			c.getStudentCheckpointMark( "Ivanko", "", "classes" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_6_4_obtain_checkpoint_mark_with_empty_checkpoint_name )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	ASSERT_THROWS(
			c.getStudentCheckpointMark( "Ivanko", "oop", "" );
		,	Messages::CheckpointCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_6_5_obtain_checkpoint_mark_for_missing_student )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	ASSERT_THROWS(
			c.getStudentCheckpointMark( "Jack", "oop", "classes" );
		,	Messages::StudentCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_6_6_obtain_checkpoint_mark_for_missing_course )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	ASSERT_THROWS(
			c.getStudentCheckpointMark( "Ivanko", "met", "classes" );
		,	Messages::CourseCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_6_7_obtain_checkpoint_mark_for_missing_checkpoint )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	ASSERT_THROWS(
			c.getStudentCheckpointMark( "Ivanko", "oop", "rabbit" );
		,	Messages::CheckpointCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_7_duplicate_mark )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );
	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 41 );

	c.addStudentCheckpoint( "Ivanko", "oop", "pointers", 45 );
	assert( c.getStudentCheckpointMark( "Ivanko", "oop", "pointers" ) == 45 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_3_8_unpassed_checkpoint )
{
	Controller c;
	c.addCourse( "oop", ControlForm::Exam );
	c.addCheckpoint( "oop", "classes", 51 );
	c.addCheckpoint( "oop", "pointers", 49 );

	c.validateCourseCheckpoints( "oop" );

	c.addStudent( "Ivanko" );
	c.addStudentCheckpoint( "Ivanko", "oop", "classes", 50 );

	assert( c.getStudentCheckpointMark( "Ivanko", "oop", "pointers" ) == 0 );
}


/*****************************************************************************/


void generateModel( Controller & _c )
{
	_c.addCourse( "math", ControlForm::Exam );
	_c.addCheckpoint( "math", "checkpoint #1", 25 );
	_c.addCheckpoint( "math", "checkpoint #2", 30 );
	_c.addCheckpoint( "math", "checkpoint #3", 39 );
	_c.addCheckpoint( "math", "checkpoint #4", 6 );
	_c.validateCourseCheckpoints( "math" );

	_c.addCourse( "oop", ControlForm::Test );
	_c.addCheckpoint( "oop", "pointers", 10 );
	_c.addCheckpoint( "oop", "classes", 60 );
	_c.addCheckpoint( "oop", "templates", 30 );
	_c.validateCourseCheckpoints( "oop" );

	_c.addCourse( "cucumber", ControlForm::Test );
	_c.addCheckpoint( "cucumber", "fresh", 100 );
	_c.validateCourseCheckpoints( "cucumber" );

	_c.addCourse( "hercules", ControlForm::Exam );
	_c.addCheckpoint( "hercules", "aerobic", 22 );
	_c.addCheckpoint( "hercules", "fitness", 20 );
	_c.addCheckpoint( "hercules", "football", 24 );
	_c.addCheckpoint( "hercules", "basketball", 20 );
	_c.addCheckpoint( "hercules", "whiskas", 14 );
	_c.validateCourseCheckpoints( "hercules" );

	_c.addStudent( "Ivan" );
	_c.addStudentCheckpoint( "Ivan", "math", "checkpoint #1", 24 );
	_c.addStudentCheckpoint( "Ivan", "math", "checkpoint #2", 29 );
	_c.addStudentCheckpoint( "Ivan", "math", "checkpoint #3", 38 );
	_c.addStudentCheckpoint( "Ivan", "math", "checkpoint #4", 5 );
	_c.addStudentCheckpoint( "Ivan", "oop", "pointers", 9 );
	_c.addStudentCheckpoint( "Ivan", "oop", "classes", 59 );
	_c.addStudentCheckpoint( "Ivan", "oop", "templates", 29 );
	_c.addStudentCheckpoint( "Ivan", "cucumber", "fresh", 99 );
	_c.addStudentCheckpoint( "Ivan", "hercules", "aerobic", 21 );
	_c.addStudentCheckpoint( "Ivan", "hercules", "fitness", 20 );
	_c.addStudentCheckpoint( "Ivan", "hercules", "football", 23 );
	_c.addStudentCheckpoint( "Ivan", "hercules", "basketball", 20 );
	_c.addStudentCheckpoint( "Ivan", "hercules", "whiskas", 13 );

	_c.addStudent( "Snoop" );
	_c.addStudentCheckpoint( "Snoop", "math", "checkpoint #1", 20 );
	_c.addStudentCheckpoint( "Snoop", "math", "checkpoint #2", 22 );
	_c.addStudentCheckpoint( "Snoop", "math", "checkpoint #3", 26 );
	_c.addStudentCheckpoint( "Snoop", "math", "checkpoint #4", 4 );
	_c.addStudentCheckpoint( "Snoop", "oop", "pointers", 7 );
	_c.addStudentCheckpoint( "Snoop", "oop", "classes", 51 );
	_c.addStudentCheckpoint( "Snoop", "oop", "templates", 19 );
	_c.addStudentCheckpoint( "Snoop", "cucumber", "fresh", 75 );
	_c.addStudentCheckpoint( "Snoop", "hercules", "aerobic", 14 );
	_c.addStudentCheckpoint( "Snoop", "hercules", "fitness", 18 );
	_c.addStudentCheckpoint( "Snoop", "hercules", "football", 14 );
	_c.addStudentCheckpoint( "Snoop", "hercules", "basketball", 18 );
	_c.addStudentCheckpoint( "Snoop", "hercules", "whiskas", 11 );

	_c.addStudent( "Doggy" );
	_c.addStudentCheckpoint( "Doggy", "math", "checkpoint #1", 20 );
	_c.addStudentCheckpoint( "Doggy", "math", "checkpoint #2", 22 );
	_c.addStudentCheckpoint( "Doggy", "math", "checkpoint #3", 26 );
	_c.addStudentCheckpoint( "Doggy", "math", "checkpoint #4", 4 );
	_c.addStudentCheckpoint( "Doggy", "oop", "pointers", 7 );
	_c.addStudentCheckpoint( "Doggy", "oop", "classes", 51 );
	_c.addStudentCheckpoint( "Doggy", "oop", "templates", 1 );
	_c.addStudentCheckpoint( "Doggy", "cucumber", "fresh", 75 );
	_c.addStudentCheckpoint( "Doggy", "hercules", "aerobic", 14 );
	_c.addStudentCheckpoint( "Doggy", "hercules", "fitness", 18 );
	_c.addStudentCheckpoint( "Doggy", "hercules", "football", 1 );
	_c.addStudentCheckpoint( "Doggy", "hercules", "basketball", 1 );
	_c.addStudentCheckpoint( "Doggy", "hercules", "whiskas", 11 );

	_c.addStudent( "Copypaster" );
	_c.addStudentCheckpoint( "Copypaster", "math", "checkpoint #1", 24 );
	_c.addStudentCheckpoint( "Copypaster", "math", "checkpoint #2", 29 );
	_c.addStudentCheckpoint( "Copypaster", "math", "checkpoint #3", 38 );
	_c.addStudentCheckpoint( "Copypaster", "math", "checkpoint #4", 5 );
	_c.addStudentCheckpoint( "Copypaster", "oop", "pointers", 9 );
	_c.addStudentCheckpoint( "Copypaster", "oop", "classes", 59 );
	_c.addStudentCheckpoint( "Copypaster", "oop", "templates", 29 );
	_c.addStudentCheckpoint( "Copypaster", "cucumber", "fresh", 99 );
	_c.addStudentCheckpoint( "Copypaster", "hercules", "aerobic", 21 );
	_c.addStudentCheckpoint( "Copypaster", "hercules", "fitness", 20 );
	_c.addStudentCheckpoint( "Copypaster", "hercules", "football", 23 );
	_c.addStudentCheckpoint( "Copypaster", "hercules", "basketball", 20 );
	_c.addStudentCheckpoint( "Copypaster", "hercules", "whiskas", 13 );

	_c.addStudent( "Eminem" );
	_c.addStudentCheckpoint( "Eminem", "math", "checkpoint #1", 17 );
	_c.addStudentCheckpoint( "Eminem", "math", "checkpoint #2", 23 );
	_c.addStudentCheckpoint( "Eminem", "math", "checkpoint #3", 27 );
	_c.addStudentCheckpoint( "Eminem", "math", "checkpoint #4", 5 );
	_c.addStudentCheckpoint( "Eminem", "oop", "pointers", 7 );
	_c.addStudentCheckpoint( "Eminem", "oop", "classes", 48 );
	_c.addStudentCheckpoint( "Eminem", "oop", "templates", 21 );
	_c.addStudentCheckpoint( "Eminem", "cucumber", "fresh", 80 );
	_c.addStudentCheckpoint( "Eminem", "hercules", "aerobic", 15 );
	_c.addStudentCheckpoint( "Eminem", "hercules", "fitness", 16 );
	_c.addStudentCheckpoint( "Eminem", "hercules", "football", 16 );
	_c.addStudentCheckpoint( "Eminem", "hercules", "basketball", 16 );
	_c.addStudentCheckpoint( "Eminem", "hercules", "whiskas", 9 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_4_1_queries_students_permitted_for_exams )
{
	Controller c;
	generateModel( c );

	// NOTE: Students were sorted in alphabetical order
	std::vector< std::string > expectation;
	expectation.push_back( "Copypaster" );
	expectation.push_back( "Eminem" );
	expectation.push_back( "Ivan" );
	expectation.push_back( "Snoop" );

	assert( c.getStudentsPermittedForExams() == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_4_2_courses_with_everyone_passed )
{
	Controller c;
	generateModel( c );
	
	// NOTE: Courses were sorted in alphabetical order
	std::vector< std::string > expectation;
	expectation.push_back( "cucumber" );
	expectation.push_back( "math" );

	assert( c.getCoursesWithEveryonePassed() == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_4_3_average_score_by_course )
{
	Controller c;
	generateModel( c );
	
	// NOTE: Courses were sorted in alphabetical order
	std::vector< std::pair< std::string, double > > expectation;
	expectation.push_back( { "cucumber", 85.6 } );
	expectation.push_back( { "hercules", 77.2 } );
	expectation.push_back( { "math", 81.6 } );
	expectation.push_back( { "oop", 81.2 } );

	std::vector< std::pair< std::string, double > > result = c.getAverageScoreByCourse();

	int size = result.size();
	assert( size > 0 );

	for ( int i = 0; i < size; ++i )
	{
		assert( result[ i ].first == expectation[ i ].first );
		assert( equalDoubles( result[ i ].second, expectation[ i ].second ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( courses_4_4_students_with_best_average_score )
{
	Controller c;
	generateModel( c );

	assert( c.getStudentWithBestAverageScore() == "Copypaster" );
}


/*****************************************************************************/
