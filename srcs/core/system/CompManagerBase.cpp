#include "../../../incs/base.hpp"
#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void CompManager::deleteAllEntities() // TODO : TEST ME
{
	flog( 0 );

	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		if ( it->second != nullptr ){ delete it->second; it->second = nullptr; }
		else { qlog( "deleteAllEntities : Entity is already a nullptr", WARN, 0 ); }
	}

	_NttMap.clear();
	_maxID = 0;
}

void CompManager::updateMaxID()
{
	flog( 0 );
	id_t newMaxID = 0;
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		if( it->first > newMaxID ){ newMaxID = it->first; }
	}
	_maxID = newMaxID;
}

// ================================ STATIC METHODS

bool CompManager::isValidID( id_t id )
{
	flog( 0 );
	if( id == 0 )
	{
		qlog( "isValidID : Entity ID cannot be 0", WARN, 0 );
		return false;
	}
	return true;
}