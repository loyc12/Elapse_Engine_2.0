#include "../../../incs/core.hpp"

// ================================ ENTITY METHODS

bool EntityMngr::freeID( id_t id )
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "freeID : ID cannot be 0", WARN, 0 );
		return false;
	}

	auto it = _usedIDs.find( id ); // NOTE : find the ID in the used IDs
	if( it == _usedIDs.end()) //     NOTE : if the ID is not found, return false
	{
		qlog( "freeID : entity with ID " + std::to_string( id ) + " does not exist", WARN, 0 );
		return false;
	}

	clearID( id ); // NOTE : clear the ID from the used and active sets, adding it to the freed set
	updateMaxID();

	return true;
}

id_t EntityMngr::initID()
{
	flog( 0 );
	id_t newID = getNewID();

	_usedIDs.insert( newID );
	if ( IS_ID_ACTIVE_BY_DEF ){ _activeIDs.insert( newID ); }

	resizeTbl(); // NOTE : resize the component table if necessary

	qlog( "addID : initialized ID " + std::to_string( newID ), DEBUG, 0 );
	return newID;
}

bool EntityMngr::setActive( id_t id, bool activate )
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "setActivity : ID cannot be 0", WARN, 0 );
		return false;
	}

	if( !isUsed( id )) // NOTE : if the ID is not used, return false
	{
		qlog( "setActivity : entity does not exist", WARN, id );
		return false;
	}
	if( activate ) // NOTE : if the entity is being activated
	{
		if( isActive( id )) // NOTE : if the entity is already active, return false
		{
			qlog( "setActivity : entity already active", DEBUG, id );
			return false;
		}

		_activeIDs.insert( id ); // NOTE : add the ID to the active IDs
		qlog( "setActivity : entity activated", DEBUG, id );
	}
	else // NOTE : if the entity is being deactivated
	{
		if( !isActive( id )) // NOTE : if the entity is not active, return false
		{
			qlog( "setActivity : entity is already inactive", DEBUG, id );
			return false;
		}

		_activeIDs.erase( id ); // NOTE : remove the ID from the active IDs
		qlog( "setActivity : entity deactivated", DEBUG, id );
	}
	return true;
}

bool EntityMngr::isUsed( id_t id ) const // NOTE : check if the ID is in the used IDs
{
	flog( 0 );
	return _usedIDs.find( id ) != _usedIDs.end();
}
bool EntityMngr::isActive( id_t id ) const // NOTE : check if the ID is in the active IDs
{
	flog( 0 );
	return _activeIDs.find( id ) != _activeIDs.end();
}
bool EntityMngr::isFreed( id_t id ) const // NOTE : check if the ID is in the freed IDs
{
	flog( 0 );
	return _freedIDs.find( id ) != _freedIDs.end();
}



Entity *EntityMngr::getNewEntity()
{
	flog( 0 );

	id_t newID = initID(); // NOTE : get a new ID for the entity
	if( newID == 0 )
	{
		qlog( "getNewEntity : failed to get a new ID", ERROR, 0 );
		return nullptr; // NOTE : return an invalid entity
	}

	return getEntity( newID ); // NOTE : create a new entity with the new ID
}
Entity *EntityMngr::getEntity( id_t id )
{
	flog( id );

	if( !IsValid( id ))
	{
		qlog( "getEntity : ID cannot be 0", ERROR, 0 );
		return nullptr; // NOTE : return an invalid entity
	}
	if( !isUsed( id )) // NOTE : if the ID is not used, return an invalid entity
	{
		qlog( "getEntity : entity does not exist", ERROR, id );
		return nullptr; // NOTE : return an invalid entity
	}

	// NOTE : copy the components of the entity from the component table
	CmpArr_t comps = CmpArr_t();
	for( comp_count_t type = 0; type < CT_COUNT; ++type ) { comps[ type ] = &( _CmpTbl[ type ][ id ]); }

	qlog( "getEntity : created entity with ID " + std::to_string( id ), DEBUG, 0 );
	return new Entity( id, comps ); // NOTE : return the entity with the components
}
