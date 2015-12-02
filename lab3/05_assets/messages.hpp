// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const OwnerNameNotUnique              = "Owner name must be unique";
	const char * const OwnerNameEmpty                  = "Owner name cannot be empty";
	const char * const OwnerUnknown                    = "Owner of the asset was not previously registered";
	const char * const AssetNameNotUniqueWithinOwner   = "Assets should have unique names within single owner";
	const char * const AssetNameEmpty                  = "Asset name cannot be empty";
	const char * const AssetUnknown                    = "Asset was not previously registered by the owner";
	const char * const NegativeAssetBaseCost           = "Asset's base cost cannot be negative";
	const char * const RepairingIdealRealEstate        = "Trying to repair real estate that is in ideal state";
	const char * const NegativeVehicleUseYears         = "Vehicle use years cannot be negative";
	const char * const RepairingWorkingVehicle         = "Trying to repair vehicle that was not damaged";
	const char * const NotRealEstateAsset              = "Operation expected a real estate asset";
	const char * const NotVehicleAsset                 = "Operation expected a vehicle asset";
	
/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


#endif // _MESSAGES_HPP_
