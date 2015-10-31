// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const ModeratorIsNotParticipant = "Moderator is not participant";
	const char * const EmptyMeetingName = "Meeting name is empty";
	const char * const EmptyMeetingAgendaRow = "Meeting agenda row is empty";
	const char * const EmptyParticipantName = "Participant name is empty";
	const char * const EmptyParticipantEmail = "Participant email is empty";
	const char * const MeetingCannotBeFound = "Meeting cannot be found";
	const char * const ParticipantCannotBeFound = "Participant cannot be found";
	const char * const DuplicateParticipant = "Participant had already been added";
	const char * const DuplicateMeeting = "Meeting had already been added";
	const char * const DuplicateEmail = "Email has already beed added";
	const char * const InvalidMeetingTime = "Meeting's time is not later than current time";
	const char * const NotEnoughParticipants = "Not enough participants for meeting";

	const char * const InvalidDateTime = "Date is not valid";
	const char * const InvalidDateTimeFormat = "Date format is incorrect";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_
