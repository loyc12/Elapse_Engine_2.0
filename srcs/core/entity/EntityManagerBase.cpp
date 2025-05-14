#include "../../../incs/base.hpp"
#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void EntityManager::updateMaxID()
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

bool EntityManager::isValidID( id_t id )
{
	flog( 0 );
	if( id == 0 )
	{
		qlog( "isValidID : Entity ID cannot be 0", WARN, 0 );
		return false;
	}
	return true;
}