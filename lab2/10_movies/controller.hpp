// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include <string>
#include <vector>

/*****************************************************************************/

class Movie;
class MovieActor;

/*****************************************************************************/


class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void createActor ( std::string const & _actorName, int _birthYear );

	int getActorBirthYear ( std::string const & _actorName ) const;

/*-----------------------------------------------------------------*/

	void createMovie ( std::string const & _movieTitle, int _productionYear, int _rating );

	int getMovieProductionYear ( std::string const & _movieTitle ) const;

	int getMovieRating ( std::string const & _movieTitle ) const;

/*-----------------------------------------------------------------*/

	void addMovieGenre ( std::string const & _movieTitle, std::string const & _genre );

	std::vector< std::string > getMovieGenres ( std::string const & _movieTitle ) const;

	std::vector< std::string > getGenreMovies ( std::string const & _genre ) const;

/*-----------------------------------------------------------------*/

	void addMovieActor ( std::string const & _movieTitle, std::string const & _actorName );

	std::vector< std::string > getMovieActors ( std::string const & _movieTitle ) const;

	std::vector< std::string > getActorMovies ( std::string const & _actorName ) const;

/*-----------------------------------------------------------------*/

	std::string getOldestMovieOfGenre ( std::string const & _genre ) const;

	double getActorAverageRating ( std::string const & _actorName ) const;

	std::vector< std::string > getActorsThatNeverPlayedInGenre ( std::string const & _genre ) const;

	std::vector< std::string > getMoviesWhenActorWasYoungerThan ( std::string const & _actorName, int _age ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

    // TODO: place private methods here

/*-----------------------------------------------------------------*/

    // TODO: place private fields here

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
