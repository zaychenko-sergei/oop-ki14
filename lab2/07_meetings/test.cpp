// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "datetime.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_1_add_participant_one )
{
	Controller c;
	c.addParticipant( "Ivan Ivanov", "you@example.com" );

	assert( c.getParticipantEmail( "Ivan Ivanov" ) == "you@example.com" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_2_add_participant_several )
{
	Controller c;
	c.addParticipant( "Ivan Ivanov", "www@site.com" );
	c.addParticipant( "Vitalka", "you@example.com" );

	assert( c.getParticipantEmail( "Ivan Ivanov" ) == "www@site.com" );

	assert( c.getParticipantEmail( "Vitalka" ) == "you@example.com" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_3_add_participant_with_empty_full_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addParticipant( "", "you@example.com" );
		,	Messages::EmptyParticipantName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_4_add_participant_with_empty_email )
{
	Controller c;

	ASSERT_THROWS(
			c.addParticipant( "Ivan Ivanov", "" );
		,	Messages::EmptyParticipantEmail
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_5_add_participant_with_duplicate_full_name )
{
	Controller c;
	c.addParticipant( "Ivan Ivanov", "www@site.com" );

	ASSERT_THROWS(
			c.addParticipant( "Ivan Ivanov", "you@example.com" );
		,	Messages::DuplicateParticipant
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_6_add_participant_with_duplicate_email )
{
	Controller c;
	c.addParticipant( "Ivan Ivanov", "sss@site.com" );

	ASSERT_THROWS(
			c.addParticipant( "Jack", "sss@site.com" );
		,	Messages::DuplicateEmail
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_7_add_participant_with_duplicate_position )
{
	Controller c;
	c.addParticipant( "Ivan Ivanov", "ivan@site.com" );
	c.addParticipant( "Petr Petrov", "petr@site.com" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_8_add_participant_obtain_email_by_empty_name )
{
	Controller c;
	c.addParticipant( "Ivan Ivanov", "ivan@site.com" );

	ASSERT_THROWS(
			c.getParticipantEmail( "" )
		,	Messages::ParticipantCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_1_9_add_participant_obtain_email_by_unknown_name )
{
	Controller c;
	c.addParticipant( "Ivan Ivanov", "ivan@site.com" );

	ASSERT_THROWS(
			c.getParticipantEmail( "Petr" )
		,	Messages::ParticipantCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_1_add_meeting_one )
{
	Controller c;
	DateTime time;
	c.addMeeting( 430, "planning", time );

	assert( c.getMeetingName( 430 ) == "planning" );
	assert( c.getMeetingStartTime( 430 ) == time );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_2_add_meeting_several )
{
	Controller c;
	DateTime time1( 2200, 1, 1, 7, 0, 0 );
	DateTime time2( 2100, 6, 10, 15, 27, 12 );
	c.addMeeting( 430, "planning", time1 );
	c.addMeeting( 689, "breakfast", time2 );

	assert( c.getMeetingName( 430 ) == "planning" );
	assert( c.getMeetingStartTime( 430 ) == time1 );
	assert( c.getMeetingName( 689 ) == "breakfast" );
	assert( c.getMeetingStartTime( 689 ) == time2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_3_add_meeting_with_empty_name )
{
	Controller c;
	DateTime time;

	ASSERT_THROWS(
			c.addMeeting( 100, "", time );
		,	Messages::EmptyMeetingName
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_4_add_meeting_with_bad_time )
{
	Controller c;
	DateTime time( 1993, 7, 19, 7, 12, 45 );

	ASSERT_THROWS(
			c.addMeeting( 100, "meeting", time );
		,	Messages::InvalidMeetingTime
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_5_add_meeting_with_duplicate_id )
{
	Controller c;
	DateTime time1( 2093, 7, 19, 7, 12, 45 );
	DateTime time2( 2093, 9, 10, 9, 0, 10 );
	c.addMeeting( 100, "meeting", time1 );

	ASSERT_THROWS(
			c.addMeeting( 100, "another", time2 );
		,	Messages::DuplicateMeeting
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_6_add_meeting_with_duplicate_name )
{
	Controller c;
	DateTime time1( 2093, 7, 19, 7, 12, 45 );
	DateTime time2( 2093, 9, 10, 9, 0, 10 );
	c.addMeeting( 100, "meeting", time1 );
	c.addMeeting( 200, "meeting", time2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_7_add_meeting_with_duplicate_start_time )
{
	Controller c;
	DateTime time( 2094, 7, 19, 7, 12, 45 );
	c.addMeeting( 100, "meeting #1", time );
	c.addMeeting( 200, "meeting #2", time );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_8_add_meeting_obtain_name_for_missing_meeting )
{
	Controller c;
	DateTime time( 2094, 7, 19, 7, 12, 45 );
	c.addMeeting( 100, "meeting #1", time );

	ASSERT_THROWS(
			c.getMeetingName( 0 )
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_2_9_add_meeting_obtain_start_time_for_missing_meeting )
{
	Controller c;
	DateTime time( 2094, 7, 19, 7, 12, 45 );
	c.addMeeting( 100, "meeting #1", time );

	ASSERT_THROWS(
			c.getMeetingStartTime( 0 )
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_1_add_meeting_participant_one )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 100, "meeting #1", DateTime() );

	c.addMeetingParticipant( 100, "Rover" );

	std::vector< std::string > expectation;
	expectation.push_back( "Rover" );

	assert( c.getMeetingParticipants( 100 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_2_add_meeting_participant_several_for_one_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Manager", "manager@example.com" );
	c.addMeeting( 100, "meeting #1", DateTime() );

	c.addMeetingParticipant( 100, "Rover" );
	c.addMeetingParticipant( 100, "Manager" );

	// NOTE: Participants were sorted in alphabetic order
	std::vector< std::string > expectation;
	expectation.push_back( "Manager" );
	expectation.push_back( "Rover" );

	assert( c.getMeetingParticipants( 100 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_3_add_meeting_participant_several_for_several_meetings )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Manager", "manager@example.com" );
	c.addParticipant( "Jack", "jack@example.com" );
	c.addParticipant( "Pack", "pack@example.com" );
	c.addMeeting( 100, "meeting #1", DateTime() );
	c.addMeeting( 101, "meeting #2", DateTime() );

	c.addMeetingParticipant( 100, "Rover" );
	c.addMeetingParticipant( 100, "Jack" );
	c.addMeetingParticipant( 101, "Manager" );
	c.addMeetingParticipant( 101, "Pack" );

	// NOTE: Participants were sorted in alphabetic order
	std::vector< std::string > expectation1;
	expectation1.push_back( "Jack" );
	expectation1.push_back( "Rover" );
	std::vector< std::string > expectation2;
	expectation2.push_back( "Manager" );
	expectation2.push_back( "Pack" );

	assert( c.getMeetingParticipants( 100 ) == expectation1 );
	assert( c.getMeetingParticipants( 101 ) == expectation2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_4_add_meeting_participant_twice_add_of_the_same_participant )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 600, "meeting #1", DateTime() );

	c.addMeetingParticipant( 600, "Rover" );
	c.addMeetingParticipant( 600, "Rover" );

	// NOTE: Participants were sorted in alphabetic order
	std::vector< std::string > expectation;
	expectation.push_back( "Rover" );

	assert( c.getMeetingParticipants( 600 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_5_add_meeting_participant_for_unknown_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 600, "meeting #1", DateTime() );

	ASSERT_THROWS(
			c.addMeetingParticipant( 400, "Rover" );
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_6_add_meeting_participant_with_empty_participant_name )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 400, "meeting #1", DateTime() );

	ASSERT_THROWS(
			c.addMeetingParticipant( 400, "" );
		,	Messages::ParticipantCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_7_add_meeting_participant_with_unknown_participant )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 400, "meeting #1", DateTime() );

	ASSERT_THROWS(
			c.addMeetingParticipant( 400, "Jack" );
		,	Messages::ParticipantCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_8_add_meeting_participant_obtain_participants_list_for_empty_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 600, "meeting #1", DateTime() );

	std::vector< std::string > expectation;
	assert( c.getMeetingParticipants( 600 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_9_add_meeting_participant_obtain_participants_list_for_missing_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 400, "meeting #1", DateTime() );

	ASSERT_THROWS(
			c.getMeetingParticipants( 890 );
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_10_1_meeting_validation_less_than_2_participants )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );

	DateTime time( 2042, 7, 7, 15, 0, 0 );
	c.addMeeting( 12456, "meeting #2234", time );

	c.addMeetingParticipant( 12456, "Rover" );

	ASSERT_THROWS(
			c.validateMeceting( 12456 );
		,	Messages::NotEnoughParticipants
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_10_2_meeting_validation_exactly_2_participants )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Manager", "manager@example.com" );

	DateTime time( 2042, 7, 7, 15, 0, 0 );
	c.addMeeting( 12456, "meeting #2234", time );

	c.addMeetingParticipant( 12456, "Rover" );
	c.addMeetingParticipant( 12456, "Manager" );

	c.validateMeceting( 12456 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_10_3_meeting_validation_more_than_2_participants )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Manager", "manager@example.com" );
	c.addParticipant( "Vitalka", "vitalka@example.com" );

	DateTime time( 2042, 7, 7, 15, 0, 0 );
	c.addMeeting( 12456, "meeting #2234", time );

	c.addMeetingParticipant( 12456, "Rover" );
	c.addMeetingParticipant( 12456, "Manager" );
	c.addMeetingParticipant( 12456, "Vitalka" );

	c.validateMeceting( 12456 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_10_4_meeting_validation_validate_for_missing_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Manager", "manager@example.com" );
	c.addParticipant( "Vitalka", "vitalka@example.com" );

	DateTime time( 2042, 7, 7, 15, 0, 0 );
	c.addMeeting( 12456, "meeting #2234", time );

	c.addMeetingParticipant( 12456, "Rover" );
	c.addMeetingParticipant( 12456, "Manager" );
	c.addMeetingParticipant( 12456, "Vitalka" );

	ASSERT_THROWS(
			c.validateMeceting( 10 );
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_11_add_meeting_participant_the_same_participant_for_several_meetings )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );

	DateTime time1( 2042, 7, 7, 15, 0, 0 );
	DateTime time2( 2042, 8, 8, 15, 0, 0 );
	c.addMeeting( 12456, "meeting #2234", time1 );
	c.addMeeting( 12472, "meeting #2289", time2 );

	c.addMeetingParticipant( 12456, "Rover" );
	c.addMeetingParticipant( 12472, "Rover" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_3_12_add_meeting_participant_the_same_participant_for_several_meetings_at_the_same_time )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );

	DateTime time( 2042, 7, 7, 15, 0, 0 );
	c.addMeeting( 12456, "meeting #2234", time );
	c.addMeeting( 12472, "meeting #2289", time );

	c.addMeetingParticipant( 12456, "Rover" );
	c.addMeetingParticipant( 12472, "Rover" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_4_1_remove_meeting_participant_from_meeting_with_one_participant )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 69, "meeting #1", DateTime() );
	c.addMeetingParticipant( 69, "Rover" );
	c.removeMeetingParticipant( 69, "Rover" );

	std::vector< std::string > expectation;
	assert( c.getMeetingParticipants( 69 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_4_2_remove_meeting_participant_from_meeting_with_several_participants )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Jack", "jack@example.com" );
	c.addMeeting( 100, "meeting", DateTime() );

	c.addMeetingParticipant( 100, "Rover" );
	c.addMeetingParticipant( 100, "Jack" );

	c.removeMeetingParticipant( 100, "Rover" );

	std::vector< std::string > expectation;
	expectation.push_back( "Jack" );

	assert( c.getMeetingParticipants( 100 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_4_3_remove_meeting_participant_from_empty_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 69, "meeting #1", DateTime() );

	ASSERT_THROWS(
			c.removeMeetingParticipant( 69, "Rover" );
		,	Messages::ParticipantNotPartOfMeeting
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_4_4_remove_meeting_participant_from_missing_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 22, "meeting #1", DateTime() );

	c.addMeetingParticipant( 22, "Rover" );

	ASSERT_THROWS(
			c.removeMeetingParticipant( 33, "Rover" );
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_4_5_remove_meeting_participant_unknown_participant )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 22, "meeting #1", DateTime() );

	c.addMeetingParticipant( 22, "Rover" );

	ASSERT_THROWS(
			c.removeMeetingParticipant( 22, "Jack" );
		,	Messages::ParticipantCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_1_moderator_no_moderator_in_meeting_by_default )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 22, "meeting #1", DateTime() );

	c.addMeetingParticipant( 22, "Rover" );

	assert( c.getMeetingModeratorName( 22 ) == "" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_2_moderator_set_moderator_for_meeting_with_one_participant )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addMeeting( 22, "meeting #1", DateTime() );

	c.addMeetingParticipant( 22, "Rover" );
	c.setMeetingModerator( 22, "Rover" );

	assert( c.getMeetingModeratorName( 22 ) == "Rover" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_3_moderator_set_moderator_for_meeting_with_several_participants )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Ivan", "ivan@example.com" );
	c.addParticipant( "Petr", "petr@example.com" );
	c.addMeeting( 42, "meeting #42", DateTime() );

	c.addMeetingParticipant( 42, "Rover" );
	c.addMeetingParticipant( 42, "Ivan" );
	c.addMeetingParticipant( 42, "Petr" );
	c.setMeetingModerator( 42, "Ivan" );

	assert( c.getMeetingModeratorName( 42 ) == "Ivan" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_4_moderator_set_moderator_for_meeting_with_empty_participants )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Ivan", "ivan@example.com" );
	c.addParticipant( "Petr", "petr@example.com" );
	c.addMeeting( 42, "meeting #42", DateTime() );

	ASSERT_THROWS(
			c.setMeetingModerator( 42, "Ivan" );
		,	Messages::ModeratorIsNotParticipant
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_5_moderator_participant_must_be_added_to_meeting_to_be_a_moderator )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Ivan", "ivan@example.com" );
	c.addParticipant( "Petr", "petr@example.com" );
	c.addMeeting( 42, "meeting #42", DateTime() );
	c.addMeeting( 43, "meeting #43", DateTime() );

	c.addMeetingParticipant( 43, "Rover" );
	c.addMeetingParticipant( 43, "Ivan" );
	c.addMeetingParticipant( 43, "Petr" );

	ASSERT_THROWS(
			c.setMeetingModerator( 42, "Ivan" );
		,	Messages::ModeratorIsNotParticipant
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_6_moderator_set_moderator_twice )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Ivan", "ivan@example.com" );
	c.addParticipant( "Petr", "petr@example.com" );
	c.addMeeting( 1, "meeting #1", DateTime() );

	c.addMeetingParticipant( 1, "Rover" );
	c.setMeetingModerator( 1, "Rover" );
	c.setMeetingModerator( 1, "Rover" );

	assert( c.getMeetingModeratorName( 1 ) == "Rover" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_7_moderator_set_another_moderator )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Ivan", "ivan@example.com" );
	c.addParticipant( "Petr", "petr@example.com" );
	c.addMeeting( 1, "meeting #1", DateTime() );

	c.addMeetingParticipant( 1, "Rover" );
	c.addMeetingParticipant( 1, "Ivan" );
	c.addMeetingParticipant( 1, "Petr" );
	c.setMeetingModerator( 1, "Rover" );
	c.setMeetingModerator( 1, "Petr" );

	assert( c.getMeetingModeratorName( 1 ) == "Petr" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_5_8_moderator_obtain_moderator_name_for_missing_meeting )
{
	Controller c;
	c.addParticipant( "Rover", "rover@example.com" );
	c.addParticipant( "Ivan", "ivan@example.com" );
	c.addParticipant( "Petr", "petr@example.com" );
	c.addMeeting( 42, "meeting #42", DateTime() );

	c.addMeetingParticipant( 42, "Rover" );
	c.addMeetingParticipant( 42, "Ivan" );
	c.addMeetingParticipant( 42, "Petr" );
	c.setMeetingModerator( 42, "Ivan" );

	ASSERT_THROWS(
			c.getMeetingModeratorName( 45 )
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_6_1_agenda_add_only_one_row )
{
	Controller c;
	c.addMeeting( 50, "whiskas", DateTime() );

	c.addMeetingAgendaRow( 50, "drink" );

	std::vector< std::string > expectation;
	expectation.push_back( "drink" );

	assert( c.getMeetingAgenda( 50 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_6_2_agenda_add_several_rows )
{
	Controller c;
	c.addMeeting( 50, "whiskas", DateTime() );

	c.addMeetingAgendaRow( 50, "drink" );
	c.addMeetingAgendaRow( 50, "drink again" );

	std::vector< std::string > expectation;
	expectation.push_back( "drink" );
	expectation.push_back( "drink again" );

	assert( c.getMeetingAgenda( 50 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_6_3_agenda_add_empty_row )
{
	Controller c;
	c.addMeeting( 50, "whiskas", DateTime() );

	ASSERT_THROWS(
			c.addMeetingAgendaRow( 50, "" );
		,	Messages::EmptyMeetingAgendaRow
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_6_4_agenda_add_row_for_missing_meeting )
{
	Controller c;
	c.addMeeting( 50, "whiskas", DateTime() );

	ASSERT_THROWS(
			c.addMeetingAgendaRow( 43, "discuss" );
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_6_5_agenda_obtain_empty_agenda )
{
	Controller c;
	c.addMeeting( 50, "whiskas", DateTime() );

	std::vector< std::string > expectation;

	assert( c.getMeetingAgenda( 50 ) == expectation );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_6_6_agenda_obtain_agenda_for_missing_meeting )
{
	Controller c;
	c.addMeeting( 50, "whiskas", DateTime() );

	ASSERT_THROWS(
			c.getMeetingAgenda( 43 );
		,	Messages::MeetingCannotBeFound
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_6_7_agenda_add_two_equal_rows )
{
	Controller c;
	c.addMeeting( 50, "whiskas", DateTime() );

	c.addMeetingAgendaRow( 50, "do something" );
	c.addMeetingAgendaRow( 50, "do something" );

	std::vector< std::string > expectation;
	expectation.push_back( "do something" );
	expectation.push_back( "do something" );

	assert( c.getMeetingAgenda( 50 ) == expectation );
}


/*****************************************************************************/


void generateModel( Controller & _c )
{
	_c.addParticipant( "Ivan", "ivan@oop" );
	_c.addParticipant( "Vitaliy", "vitaliy@oop" );
	_c.addParticipant( "Inokentiy", "inokentiy@oop" );
	_c.addParticipant( "Cucumber", "cucumber@oop" );

	_c.addMeeting( 1, "meeting #1", DateTime( 3000, 1, 1, 12, 0, 0 ) );
	_c.addMeeting( 2, "meeting #2", DateTime( 3001, 1, 1, 12, 0, 0 ) );
	_c.addMeeting( 3, "meeting #3", DateTime( 3002, 1, 1, 12, 0, 0 ) );
	_c.addMeeting( 4, "meeting #4", DateTime( 3003, 1, 1, 12, 0, 0 ) );
	_c.addMeeting( 5, "meeting #5", DateTime( 3003, 1, 1, 12, 0, 0 ) );
	_c.addMeeting( 6, "meeting #6", DateTime( 3003, 1, 1, 12, 0, 0 ) );
	_c.addMeeting( 7, "meeting #7", DateTime( 3004, 1, 1, 12, 0, 0 ) );
	_c.addMeeting( 8, "meeting #8", DateTime( 3004, 1, 1, 12, 0, 0 ) );

	_c.addMeetingAgendaRow( 1, "take a rest" );
	_c.addMeetingAgendaRow( 1, "eat something" );

	_c.addMeetingAgendaRow( 2, "read the report" );

	_c.addMeetingAgendaRow( 3, "do thomething #1" );
	_c.addMeetingAgendaRow( 3, "do thomething #2" );
	_c.addMeetingAgendaRow( 3, "do thomething #3" );

	_c.addMeetingAgendaRow( 4, "joke #1" );
	_c.addMeetingAgendaRow( 4, "joke #2" );

	_c.addMeetingAgendaRow( 5, "dismiss" );

	_c.addMeetingAgendaRow( 6, "tell about river" );
	_c.addMeetingAgendaRow( 6, "tell about dog" );
	_c.addMeetingAgendaRow( 6, "tell about cat" );

	_c.addMeetingAgendaRow( 7, "drink a vodka" );
	_c.addMeetingAgendaRow( 7, "drink a beer" );

	_c.addMeetingAgendaRow( 8, "sleep" );
	_c.addMeetingAgendaRow( 8, "more sleep" );

	_c.addMeetingParticipant( 1, "Ivan" );
	_c.addMeetingParticipant( 1, "Vitaliy" );
	_c.setMeetingModerator( 1, "Ivan" );

	_c.addMeetingParticipant( 2, "Vitaliy" );
	_c.addMeetingParticipant( 2, "Inokentiy" );
	_c.setMeetingModerator( 2, "Vitaliy" );

	_c.addMeetingParticipant( 3, "Inokentiy" );
	_c.addMeetingParticipant( 3, "Cucumber" );
	_c.setMeetingModerator( 3, "Inokentiy" );

	_c.addMeetingParticipant( 4, "Cucumber" );
	_c.addMeetingParticipant( 4, "Ivan" );
	_c.setMeetingModerator( 4, "Ivan" );

	_c.addMeetingParticipant( 5, "Ivan" );
	_c.addMeetingParticipant( 5, "Vitaliy" );
	_c.addMeetingParticipant( 5, "Inokentiy" );
	_c.addMeetingParticipant( 5, "Cucumber" );
	_c.setMeetingModerator( 5, "Inokentiy" );

	_c.addMeetingParticipant( 6, "Cucumber" );

	_c.addMeetingParticipant( 7, "Ivan" );
	_c.addMeetingParticipant( 7, "Vitaliy" );
	_c.addMeetingParticipant( 7, "Inokentiy" );
	_c.addMeetingParticipant( 7, "Cucumber" );
	_c.setMeetingModerator( 7, "Inokentiy" );

	_c.addMeetingParticipant( 8, "Ivan" );
	_c.addMeetingParticipant( 8, "Cucumber" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_7_1_queries_get_most_frequent_moderator_name )
{
	Controller c;
	generateModel( c );

	assert( c.getMostFrequentModeratorName() == "Inokentiy" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_7_2_queries_get_meeting_with_longest_agenda )
{
	Controller c;
	generateModel( c );

	assert( c.getMeetingWithLongestAgenda() == "meeting #3" );
}


/*****************************************************************************/


DECLARE_OOP_TEST( meetings_7_3_queries_get_overlaps )
{
	Controller c;
	generateModel( c );

	std::map< std::string, std::vector< std::string > > expectation;
	expectation[ "Ivan" ] = { "meeting #4", "meeting #5", "meeting #7", "meeting #8" };
	expectation[ "Cucumber" ] = { "meeting #4", "meeting #5", "meeting #6", "meeting #7", "meeting #8" };

	assert( c.getOverlaps() == expectation );
}


/*****************************************************************************/
