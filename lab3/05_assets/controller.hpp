// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "realestatestate.hpp"

#include <string>
#include <unordered_set>

/*****************************************************************************/


class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;
	
	~ Controller ();

/*-----------------------------------------------------------------*/

	void createOwner ( std::string const & _fullName );
	
	void addRealEstate ( 
			std::string const & _ownerFullName
		,	std::string const & _assetName
		,	double _baseCost
		,	RealEstateState _initialState
	);

	void addVehicle (
			std::string const & _ownerFullName
		,	std::string const & _assetName
		,	double _baseCost
		,	int _yearsInUse
		,	bool _hadAccidents
	);

	std::unordered_set< std::string > getOwnerAssetNames ( std::string const & _ownerFullName  ) const;

	double getOwnerAssetsCurrentCost  ( std::string const & _ownerFullName ) const;

	double getAssetBaseCost  ( std::string const & _ownerFullName, std::string const & _assetName ) const;

	double getAssetCurrentCost  ( std::string const & _ownerFullName, std::string const & _assetName ) const;

	void repair ( std::string const & _ownerFullName, std::string const & _assetName );
	
	void damage ( std::string const & _ownerFullName, std::string const & _assetName );

	RealEstateState getRealEstateState ( std::string const & _ownerFullName, std::string const & _assetName ) const;

	int getVehicleYearsInUse ( std::string const & _ownerFullName, std::string const & _assetName ) const;

	bool isVehicleCrashed ( std::string const & _ownerFullName, std::string const & _assetName ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	// TODO ...

/*-----------------------------------------------------------------*/


};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
