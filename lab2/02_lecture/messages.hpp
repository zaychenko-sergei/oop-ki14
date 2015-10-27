// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/


namespace Messages
{
	const char * const SubtopicExists       = "Subtopic already exists";
	const char * const InstructorNameEmpty  = "Instructor name cannot be empty";
	const char * const DisciplineNameEmpty  = "Discipline name cannot be empty";
	const char * const TopicNameEmpty       = "Topic name cannot be empty";
	const char * const MainTopicDuplication = "Name of the main topic must be unique";
	const char * const MainTopicUnknown     = "Unknown main topic";
	const char * const TopicUnknown         = "Unknown topic";
	const char * const NegativeSlidesCount  = "Number of slides in a topic must not be negative";
	const char * const HierarchicalTopicNameEmpty = "Hierarchical topic name must hold at least 1 string";
}


/*****************************************************************************/

#endif // _MESSAGES_HPP_