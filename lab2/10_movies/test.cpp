// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_actor_trace_properties )
{
	Controller c;
	c.createActor( "Brad Pitt", 1963 );

	assert( c.getActorBirthYear( "Brad Pitt" ) == 1963 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_actors_trace_properties )
{
	Controller c;
	c.createActor( "Brad Pitt",  1963 );
	c.createActor( "Matt Damon", 1970 );

	assert( c.getActorBirthYear( "Brad Pitt" ) == 1963 );
	assert( c.getActorBirthYear( "Matt Damon" ) == 1970 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicate_actor )
{
	Controller c;
	c.createActor( "Brad Pitt", 1963 );
	
	ASSERT_THROWS(
		c.createActor( "Brad Pitt", 1963 ),
		Messages::ActorAlreadyRegistered
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_actor_empty_name )
{
	Controller c;

	ASSERT_THROWS(
		c.createActor( "", 1950 ),
		Messages::ActorNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_actor_birth_year_in_future )
{
	Controller c;

	ASSERT_THROWS(
		c.createActor( "Future Star", 2150 ),
		Messages::ActorBornInFuture
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_properties_not_existing_actor )
{
	Controller c;

	ASSERT_THROWS(
		c.getActorBirthYear( "Ivan Ivanov" ),
		Messages::ActorUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_movie_trace_properties )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );

	assert( c.getMovieProductionYear( "Troy" ) == 2004 );
	assert( c.getMovieRating( "Troy" ) == 8 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_movies_trace_properties )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );
	c.createMovie( "Fight Club", 1999, 9 );

	assert( c.getMovieProductionYear( "Troy" ) == 2004 );
	assert( c.getMovieRating( "Troy" ) == 8 );

	assert( c.getMovieProductionYear( "Fight Club" ) == 1999 );
	assert( c.getMovieRating( "Fight Club" ) == 9 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicate_movie )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );

	ASSERT_THROWS(
		c.createMovie( "Troy", 2004, 8 ),
		Messages::MovieAlreadyRegistered
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_movie_empty_title )
{
	Controller c;

	ASSERT_THROWS(
		c.createMovie( "", 2004, 8 ),
		Messages::MovieTitleEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_movie_production_in_future )
{
	Controller c;

	ASSERT_THROWS(
		c.createMovie( "Future Top-10", 2150, 9 ),
		Messages::MovieProducedInFuture
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_movie_rating_out_of_range )
{
	Controller c;
	c.createMovie( "Interstellar", 2014, 10 );
	c.createMovie( "Disaster", 2012, 1 );

	ASSERT_THROWS(
		c.createMovie( "Dummy", 2013, 0 ),
		Messages::RatingOutOfRange
	);

	ASSERT_THROWS(
		c.createMovie( "Genious", 2011, 11 ),
		Messages::RatingOutOfRange
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_properties_not_existing_movie )
{
	Controller c;

	ASSERT_THROWS(
		c.getMovieProductionYear( "Surprise" ),
		Messages::MovieUnresolved
	);

	ASSERT_THROWS(
		c.getMovieRating( "Surprise" ),
		Messages::MovieUnresolved
	);

	ASSERT_THROWS(
		c.getMovieGenres( "Surprise" ),
		Messages::MovieUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_movie_genre )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );
	c.addMovieGenre( "Troy", "History" );

	assert( c.getMovieGenres( "Troy" )    == std::vector< std::string > { "History" } );
	assert( c.getGenreMovies( "History" ) == std::vector< std::string > { "Troy"    } );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_movie_two_genres )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );
	c.addMovieGenre( "Troy", "History" );
	c.addMovieGenre( "Troy", "Drama" );

	std::vector< std::string > expectedGenres{ "Drama", "History" };
	assert( c.getMovieGenres( "Troy" ) == expectedGenres );
	assert( c.getGenreMovies( "History" ) == std::vector< std::string > { "Troy" } );
	assert( c.getGenreMovies( "Drama"   ) == std::vector< std::string > { "Troy" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_genre_to_two_movies )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );
	c.createMovie( "Braveheart", 1995, 8 );
	c.addMovieGenre( "Troy", "History" );
	c.addMovieGenre( "Braveheart", "History" );

	assert( c.getMovieGenres( "Troy" ) == std::vector< std::string >{ "History" } );
	assert( c.getMovieGenres( "Braveheart" ) == std::vector< std::string >{ "History" } );

	std::vector< std::string > expectedMovies{ "Braveheart", "Troy" };
	assert( c.getGenreMovies( "History" ) == expectedMovies );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_handle_empty_genre )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );

	ASSERT_THROWS(
		c.addMovieGenre( "Troy", "" ),
		Messages::GenreNameEmpty
	);

	ASSERT_THROWS(
		c.getGenreMovies( "" ),
		Messages::GenreNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_movie_duplicate_genre )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );
	c.addMovieGenre( "Troy", "History" );

	ASSERT_THROWS(
		c.addMovieGenre( "Troy", "History" ),
		Messages::MovieGenreAlreadyAdded
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_genre_to_unknown_movie )
{
	Controller c;

	ASSERT_THROWS(
		c.addMovieGenre( "Surprise", "Drama" ),
		Messages::MovieUnresolved
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_actor_to_movie )
{
	Controller c;
	c.createActor( "Brad Pitt", 1963 );
	c.createMovie( "Troy", 2004, 8 );
	c.addMovieActor( "Troy", "Brad Pitt" );

	assert( c.getMovieActors( "Troy" ) == std::vector< std::string >{ "Brad Pitt" } );
	assert( c.getActorMovies( "Brad Pitt" ) == std::vector< std::string > { "Troy" } );
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_two_actors_to_movie )
{
	Controller c;
	c.createActor( "Brad Pitt", 1963 );
	c.createActor( "Eric Bana", 1968 );

	c.createMovie( "Troy", 2004, 8 );
	c.addMovieActor( "Troy", "Brad Pitt" );
	c.addMovieActor( "Troy", "Eric Bana" );

	std::vector< std::string > expectedActors{ "Brad Pitt", "Eric Bana" };
	assert( c.getMovieActors( "Troy" ) == expectedActors );
	assert( c.getActorMovies( "Brad Pitt" ) == std::vector< std::string > { "Troy" } );
	assert( c.getActorMovies( "Eric Bana" ) == std::vector< std::string > { "Troy" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_actor_to_two_movies )
{
	Controller c;
	c.createActor( "Brad Pitt", 1963 );
	c.createMovie( "Troy", 2004, 8 );
	c.createMovie( "Fightclub", 1999, 9 );

	c.addMovieActor( "Troy", "Brad Pitt" );
	c.addMovieActor( "Fightclub", "Brad Pitt" );

	std::vector< std::string > expectedMovies{ "Fightclub", "Troy" };
	assert( c.getActorMovies( "Brad Pitt" ) == expectedMovies );
	assert( c.getMovieActors( "Troy" ) == std::vector< std::string >{ "Brad Pitt" }  );
	assert( c.getMovieActors( "Fightclub" ) == std::vector< std::string >{ "Brad Pitt" } );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_movie_actors_not_existing_movie )
{
	Controller c;
	c.createActor( "Brad Pitt", 1963 );

	ASSERT_THROWS(
		c.addMovieActor( "Surprise", "Brad Pitt" ),
		Messages::MovieUnresolved
	);

	ASSERT_THROWS(
		c.getMovieActors( "Surprise" ),
		Messages::MovieUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_movie_actors_not_existing_actor )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );

	ASSERT_THROWS(
		c.addMovieActor( "Troy", "Surprise" ),
		Messages::ActorUnresolved
	);

	ASSERT_THROWS(
		c.getActorMovies( "Surprise" ),
		Messages::ActorUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_oldest_movie_of_genre )
{
	Controller c;
	c.createMovie( "Troy", 2004, 8 );
	c.createMovie( "Braveheart", 1995, 8 );
	c.createMovie( "Interstellar", 2014, 9 );

	c.addMovieGenre( "Troy", "History" );
	c.addMovieGenre( "Troy", "Drama" );

	c.addMovieGenre( "Braveheart", "History" );
	c.addMovieGenre( "Braveheart", "Action" );

	c.addMovieGenre( "Interstellar", "Science Fiction" );
	c.addMovieGenre( "Interstellar", "Drama" );

	assert( c.getOldestMovieOfGenre( "History" ) == "Braveheart" );
	assert( c.getOldestMovieOfGenre( "Drama" )   == "Troy" );
	assert( c.getOldestMovieOfGenre( "Science Fiction" ) == "Interstellar" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_oldest_movie_of_bad_genre )
{
	Controller c;
	assert( c.getOldestMovieOfGenre( "History" ) == "" );

	ASSERT_THROWS(
		c.getOldestMovieOfGenre( "" ),
		Messages::GenreNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_actor_average_rating )
{
	Controller c;
	c.createActor( "Lazy Bastard", 1990 );
	c.createActor( "Brad Pitt", 1963 );

	c.createMovie( "Troy", 2004, 8 );
	c.createMovie( "Fightclub", 1999, 9 );

	c.addMovieActor( "Troy", "Brad Pitt" );
	c.addMovieActor( "Fightclub", "Brad Pitt" );

	assert( c.getActorAverageRating( "Brad Pitt" ) == 8.5 );
	assert( c.getActorAverageRating( "Lazy Bastard" ) == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_actor_average_rating_bad_actor )
{
	Controller c;

	ASSERT_THROWS(
		c.getActorAverageRating( "Dont Exister" ),
		Messages::ActorUnresolved
	);

	ASSERT_THROWS(
		c.getActorAverageRating( "" ),
		Messages::ActorUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_actor_never_played_in_genre )
{
	Controller c;
	c.createActor( "Jack Superstar", 1980 );
	c.createActor( "John Rookie", 1995 );

	c.createMovie( "Big Day", 2010, 3 );
	c.addMovieGenre( "Big Day", "Comedy" );
	c.addMovieActor( "Big Day", "Jack Superstar" );

	c.createMovie( "Big Bang", 2005, 2 );
	c.addMovieGenre( "Big Bang", "Action" );
	c.addMovieGenre( "Big Bang", "Thriller" );
	c.addMovieActor( "Big Bang", "Jack Superstar" );
	c.addMovieActor( "Big Bang", "John Rookie" );

	assert( c.getActorsThatNeverPlayedInGenre( "Comedy" ) == std::vector< std::string >{ "John Rookie" } );
	
	std::vector< std::string > bothActors{ "Jack Superstar", "John Rookie" };
	assert( c.getActorsThatNeverPlayedInGenre( "Drama" ) == bothActors );

	assert( c.getActorsThatNeverPlayedInGenre( "Action" ).empty() );
	assert( c.getActorsThatNeverPlayedInGenre( "Thriller" ).empty() );

	ASSERT_THROWS(
		c.getActorsThatNeverPlayedInGenre( "" ),
		Messages::GenreNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_actor_younger_than_age_when_filmed )
{
	Controller c;
	c.createActor( "Jack Superstar", 1980 );

	c.createMovie( "Big Day", 2010, 3 );
	c.addMovieActor( "Big Day", "Jack Superstar" ); // 30 years

	c.createMovie( "Big Bang", 2005, 2 );
	c.addMovieActor( "Big Bang", "Jack Superstar" ); // 25 years

	std::vector< std::string > bothMovies = { "Big Bang", "Big Day" };
	assert( c.getMoviesWhenActorWasYoungerThan( "Jack Superstar", 35 ) == bothMovies );
	assert( c.getMoviesWhenActorWasYoungerThan( "Jack Superstar", 28 ) == std::vector< std::string >{ "Big Bang" } );
	assert( c.getMoviesWhenActorWasYoungerThan( "Jack Superstar", 24 ).empty() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_actor_younger_than_age_bad_arguments )
{
	Controller c;
	c.createActor( "Jack Superstar", 1980 );

	ASSERT_THROWS(
		c.getMoviesWhenActorWasYoungerThan( "Mr. X", 30 ),
		Messages::ActorUnresolved
	);

	ASSERT_THROWS(
		c.getMoviesWhenActorWasYoungerThan( "Jack Superstar", -1 ),
		Messages::NegativeAge
	);
}


/*****************************************************************************/
