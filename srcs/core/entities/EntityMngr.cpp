#include "../../../incs/core.hpp"


// ================================ CORE METHODS

void EntityMngr::updateMaxID()
{
	flog( 0 );

	if( _usedIDs.empty())
	{
		qlog( "updateMaxID : no used IDs, setting maxID to 0", DEBUG, 0 );

		_freedIDs.clear(); // NOTE : clears the freed IDs, since there are no used IDs
		_maxID = 0;
	}
	else
	{
		_maxID = *std::max_element( _usedIDs.begin(), _usedIDs.end()); // NOTE : finds new maxID based on the used IDs
		qlog( "updateMaxID : updated maxID to " + std::to_string( _maxID ), DEBUG, 0 );
	}

	auto it = _freedIDs.upper_bound( _maxID ); // NOTE : find the first element greater than _maxID
	if ( it != _freedIDs.end() )
	{
			_freedIDs.erase( it, _freedIDs.end() ); // NOTE : erase all elements from 'it' to the end
			qlog("updateMaxID : removed freed IDs greater than maxID", DEBUG, 0);
	}
}
id_t EntityMngr::getNewID()
{
	flog( 0 );
	id_t newID = 0;

	if ( _freedIDs.empty() ) // NOTE : if there are no previously freed IDs, we need to get a brand a new one
	{
		qlog( "getNewID : no freed ID available, creating a new ID", DEBUG, 0 );
		newID = ++_maxID; // NOTE : preincrementation also prevents giving ID 0, since it is reserved for invalid entities
	}
	else // NOTE : if there are previously freed IDs, we can reuse one of them
	{
		qlog( "getNewID : reusing previously freed ID " + std::to_string( newID ), DEBUG, 0 );

		auto it = _freedIDs.begin(); // NOTE : get the first freed ID
		newID = *it;

		_usedIDs.insert( newID );
		_freedIDs.erase( it );
	}
	return newID;
}

void EntityMngr::initTbl()
{
	flog( 0 );
	_CmpTblSize = TblGrpSize; // NOTE : set the initial size of the component table

	for( comp_count_t type = 0; type < CT_COUNT; ++type )
	{
		_CmpTbl[ type ].clear(); //             NOTE : clear the component table for the given type
		_CmpTbl[ type ].resize( TblGrpSize ); // NOTE : resize the component table to the maximum possible ID

		qlog( "initTbl : initialized component table for type " + std::to_string( type ), DEBUG, 0 );
	}
	qlog( "initTbl : initialized component tables with size " + std::to_string( _CmpTblSize ), INFO, 0 );
}
void EntityMngr::resizeTbl()
{
	flog( 0 );


	if( _CmpTblSize > TblGrpSize && _maxID < _CmpTblSize - TblGrpSize - 8 )
	{ // NOTE : giving ourself some margin to avoid potential resizing issues

		qlog( "resizeTbl : shrinking component tables", DEBUG, 0 );
		_CmpTblSize -= TblGrpSize;
	}
	elif( _maxID >= _CmpTblSize - 4 )
	{ // NOTE : giving ourself some margin to avoid potential resizing issues

		qlog( "resizeTbl : expanding component tables", DEBUG, 0 );
		_CmpTblSize += TblGrpSize;
	}
	else { qlog( "resizeTbl : no need to resize component tables" , DEBUG, 0 ); return; }

	for( comp_count_t type = 0; type < CT_COUNT; ++type ){ _CmpTbl[ type ].resize( _CmpTblSize ); }

	qlog( "resizeTbl : resized all component tables", DEBUG, 0 );
}

void EntityMngr::resetAllComps()
{
	flog( 0 );

	for( comp_count_t type = 0; type < CT_COUNT; ++type ){ resetComps( comp_type_e( type )); }

	qlog( "resetAllComps : reset all components", DEBUG, 0 );
}
void EntityMngr::resetComps( id_t id )
{
	flog( id );

	if( !IsValid( id ))
	{
		qlog( "resetComps : ID cannot be 0", WARN, 0 );
		return;
	}
	for( comp_count_t type = 0; type < CT_COUNT; ++type ){ resetComp( id, comp_type_e( type )); }

	qlog( "resetComps : reset all components for entity with ID " + std::to_string( id ), DEBUG, 0 );
}
void EntityMngr::resetComps( comp_type_e type )
{
	flog( 0 );

	if( !IsValid( type ))
	{
		qlog( "resetComps : invalid component type " + std::to_string( type ), ERROR, 0 );
		return;
	}
	for( id_t id = 1; id <= _maxID; ++id ){ resetComp( id, type ); } // TODO : iterate through used IDs instead of all IDs

	qlog( "resetComps : reset all components of type " + std::to_string( type ), DEBUG, 0 );
}
void EntityMngr::resetComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( type, id ))
	{
		qlog( "resetComp : invalid component type or ID", ERROR, 0 );
		return;
	}

	_CmpTbl[ type ].at( id ).deinit();
	qlog( "resetComp : reset component of type " + std::to_string( type ) + " for entity with ID " + std::to_string( id ), DEBUG, 0 );
}

void EntityMngr::clearIDsets()
{
	flog( 0 );
	_maxID = 0;

	_usedIDs.clear();
	_activeIDs.clear();
	_freedIDs.clear(); // NOTE : no need to add the freed IDs to the used IDs, since maxID is now zero

	qlog( "clearAllIDs : cleared all ID sets & reset maxID", DEBUG, 0 );
}
void EntityMngr::clearID( id_t id )
{
	flog( 0 );

	if( id == 0 )
	{
		qlog( "clearID : ID cannot be 0", WARN, 0 );
		return;
	}

	_usedIDs.erase(   id );
	_activeIDs.erase( id );
	_freedIDs.insert( id ); // NOTE : add the ID to the freed ID, so it can be reused later
}

// ================================ ENTITY METHODS

bool EntityMngr::hasID( id_t id ) const
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "hasID : invalid ID " + std::to_string( id ), ERROR, 0 );
		return false; // NOTE : if the ID is invalid, return false
	}

	bool exists = _usedIDs.find( id ) != _usedIDs.end(); // NOTE : check if the ID exists in the used IDs

	qlog( "hasID : entity with ID " + std::to_string( id ) + ( exists ? " exists" : " does not exist" ), DEBUG, 0 );
	return exists;
}
bool EntityMngr::delID( id_t id )
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "delID : ID cannot be 0", WARN, 0 );
		return false;
	}

	auto it = _usedIDs.find( id ); // NOTE : find the ID in the used IDs
	if( it == _usedIDs.end()) //     NOTE : if the ID is not found, return false
	{
		qlog( "delID : entity with ID " + std::to_string( id ) + " does not exist", WARN, 0 );
		return false;
	}

	clearID( id ); // NOTE : clear the ID from all ID sets, then adds it to the freed IDs
	updateMaxID(); // NOTE : update the maxID after deleting the entity

	qlog( "delID : deleted entity with ID " + std::to_string( id ), DEBUG, 0 );
	return true;
}
id_t EntityMngr::addID()
{
	flog( 0 );

	id_t newID = getNewID();
	_usedIDs.insert( newID );

	qlog( "addID : added entity with ID " + std::to_string( newID ), DEBUG, 0 );
	return newID;
}



bool EntityMngr::setActivity( id_t id, bool activate )
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "setActivity : ID cannot be 0", WARN, 0 );
		return false;
	}

	if( !hasID( id )) // NOTE : if the entity does not exist, return false
	{
		qlog( "setActivity : entity with ID " + std::to_string( id ) + " does not exist", WARN, 0 );
		return false;
	}

	if( activate ) // NOTE : if we want to activate the entity
	{
		if( isActive( id )) // NOTE : if the entity is already active, return true
		{
			qlog( "setActivity : entity with ID " + std::to_string( id ) + " is already active", DEBUG, 0 );
			return false;
		}
		else // NOTE : if the entity is not active, just log and return true
		{
			_activeIDs.insert( id ); // NOTE : add the ID to the active IDs

			qlog( "setActivity : activated entity with ID " + std::to_string( id ), DEBUG, 0 );
			return true;
		}
	}
	else // NOTE : if we want to deactivate the entity
	{
		if( !isActive( id )) // NOTE : if the entity is already inactive, return true
		{
			qlog( "setActivity : entity with ID " + std::to_string( id ) + " is already inactive", DEBUG, 0 );
			return false;
		}
		else // NOTE : if the entity is active, just log and return true
		{
			_activeIDs.erase( id ); // NOTE : remove the ID from the active IDs

			qlog( "setActivity : deactivated entity with ID " + std::to_string( id ), DEBUG, 0 );
			return true;
		}
	}
}
bool EntityMngr::isActive( id_t id ) const
{
	flog( 0 );
	bool active = _activeIDs.find( id ) != _activeIDs.end(); // NOTE : check if the ID is in the active IDs

	qlog( "isActive : entity with ID " + std::to_string( id ) + ( active ? " is active" : " is inactive" ), DEBUG, 0 );
	return active;
}
bool EntityMngr::isFreeID( id_t id ) const
{
	flog( 0 );
	bool freed = _freedIDs.find( id ) != _freedIDs.end(); // NOTE : check if the ID is in the freed IDs

	qlog( "isFreeID : ID " + std::to_string( id ) + ( freed ? " is free" : " is not free" ), DEBUG, 0 );
	return freed;
}



Entity *EntityMngr::getNewEntity()
{
	id_t newID = addID();
	flog( newID );

	_NttMap[ newID ] = new Entity( newID, false ); // NOTE : create a new entity with the new ID and add it to the NttMap
	qlog( "getEntity : returning new entity with ID " + std::to_string( newID ), DEBUG, 0 );

	return _NttMap[ newID ];
}
Entity *EntityMngr::getEntity( id_t id )
{
	flog( id );

	if( !IsValid( id ))
	{
		qlog( "getEntity : ID cannot be 0", WARN, 0 );
		return nullptr;
	}
	if( !hasID( id ))
	{
		qlog( "getEntity : entity with ID " + std::to_string( id ) + " does not exist", WARN, 0 );
		return nullptr;
	}
	if( !hasNttPtr( id )) // NOTE : if the entity is not stored in the NttMap, create a new entity
	{
		qlog( "getEntity : entity with ID " + std::to_string( id ) + " does not exist in the NttMap, creating a new entity", DEBUG, 0 );
		_NttMap[ id ] = new Entity( id, false );
	}

	qlog( "getEntity : returning entity with ID " + std::to_string( id ), DEBUG, 0 );
	return _NttMap[ id ];
}

bool EntityMngr::hasNttPtr( id_t id ) const
{
	flog( 0 );

	if( !IsValid( id )){ return false; }
	bool exists = _NttMap.find( id ) != _NttMap.end();

	qlog( "hasNttPtr : entity with ID " + std::to_string( id ) + ( exists ? " exists in the NttMap" : " does not exist in the NttMap" ), DEBUG, 0 );
	return exists;
}
bool EntityMngr::storeNttPtr( Entity *entity )
{
	if( entity == nullptr )
	{
		qlog( "storeNttPtr : entity cannot be nullptr", ERROR, 0 );
		return false;
	}
	flog( entity->getID() );

	_NttMap[ entity->getID() ] = entity; // NOTE : store the entity in the NttMap
	entity->setIsInMngr( true );

	qlog( "storeNttPtr : stored entity with ID " + std::to_string( entity->getID() ), DEBUG, 0 );
	return true;
}
bool EntityMngr::removeNttPtr( id_t id )
{
	flog( id );

	if( !IsValid( id )){   return false; }
	if( !hasNttPtr( id )){ return false; }

	auto it = _NttMap.find( id ); // NOTE : find the entity in the NttMap
	if( it == _NttMap.end()) // NOTE : if the entity is not found, return false
	{
		qlog( "removeNttPtr : entity with ID " + std::to_string( id ) + " does not exist in the NttMap", WARN, 0 );
		return false;
	}
	delete it->second;
	it->second = nullptr;
	_NttMap.erase( it );

	qlog( "removeNttPtr : removed entity with ID " + std::to_string( id ), DEBUG, 0 );
	return true;
}
void EntityMngr::clearAllNtts()
{
	flog( 0 );

	for( auto &pair : _NttMap )
	{
		delete pair.second;
	}
	_NttMap.clear();

	qlog( "clearAllNtts : cleared all entities from the NttMap", DEBUG, 0 );
}

// ================================ COMPONENT METHODS

void EntityMngr::updateAllComps()
{
	flog( 0 );
	for( comp_count_t type = 0; type < CT_COUNT; ++type ){ updateCompsByType( comp_type_e( type )); } // NOTE : update all components by type

	qlog( "updateAllComponents : updated all components", DEBUG, 0 );
}
void EntityMngr::updateCompsByType( comp_type_e type )
{
	flog( 0 );

	if( !IsValid( type )) // NOTE : if the type is invalid, return
	{
		qlog( "updateCompsByType : invalid component type " + std::to_string( type ), ERROR, 0 );
		return;
	}

	for( id_t id = 1; id <= _maxID; ++id ) // NOTE : iterate through all IDs from 1 to maxID
	{
		if( !isActive( id )){ continue; } //                 NOTE : if the entity is not active,  skip to the next ID
		if( !_CmpTbl[ type ][ id ].isInit()){ continue; } // NOTE : if the component is not init, skip to the next ID

		qlog( "updateCompsByType : updating component of type " + std::to_string( type ) + " for entity with ID " + std::to_string( id ), DEBUG, 0 );
		// _CmpTbl[ type ][ id ].onTick(); // NOTE : call the onTick method of the component   TODO : find another way to call the tick method, since its not supposed to be virtual for performance reasons
	}
}



bool EntityMngr::hasComp( comp_type_e type, id_t id ) const
{
	flog( 0 );

	if( !IsValid( type, id )){  return false; }
	bool exists = _CmpTbl[ type ][ id ].isInit();

	qlog( "hasComp : component of type " + std::to_string( type ) + ( exists ? " exists for entity with ID " + std::to_string( id ) : " does not exist for entity with ID " + std::to_string( id )), DEBUG, 0 );
	return exists;
}
bool EntityMngr::delComp( comp_type_e type, id_t id )
{
	flog( 0 );

	if( !IsValid( type, id )){  return false; }
	if( !_CmpTbl[ type ][ id ].isInit())
	{
		qlog( "delComp : component of type " + std::to_string( type ) + " does not exist for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return false;
	}

	_CmpTbl[ type ][ id ].deinit();
	return true;
}
bool EntityMngr::addComp( comp_type_e type, id_t id )
{
	flog( 0 );

	if( !IsValid( type, id )){  return false; }
	if( _CmpTbl[ type ][ id ].isInit())
	{
		qlog( "addComp : component of type " + std::to_string( type ) + " already exists for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return false;
	}

	_CmpTbl[ type ][ id ].init( id );
	return true;
}



CompBase *EntityMngr::getComp( comp_type_e type, id_t id )
{
	flog( 0 );

	if( !IsValid( type, id )){  return nullptr; }
	if( !_CmpTbl[ type ][ id ].isInit())
	{
		qlog( "getComp : component of type " + std::to_string( type ) + " does not exist for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return nullptr;
	}

	return &(_CmpTbl[ type ][ id ]);
}
CmpVec_t EntityMngr::getAllComps( id_t id )
{
	flog( 0 );
	CmpVec_t comps = CmpVec_t(); // NOTE : create a new vector
	comps.resize( CT_COUNT );

	if( !IsValid( id )) // NOTE : if the ID is invalid, return an empty component table
	{
		qlog( "getAllComps : ID cannot be 0", WARN, 0 );
		for( comp_count_t type = 0; type < CT_COUNT; ++type ){ comps[ type ] = CompBase(); } // NOTE : fill the component table with nullptrs
		return comps;
	}

	for( comp_count_t type = 0; type < CT_COUNT; ++type ){ comps[ type ] = _CmpTbl[ type ][ id ]; }
	return comps;
}
