#include "../../../incs/core.hpp"


// ================================ CORE METHODS

void EntityMngr::updateMaxID()
{
	flog( 0 );

	if( _usedIDs.empty())
	{
		qlog( "updateMaxID : no used IDs, setting maxID to 0", DEBUG, 0 );

		_activeIDs.clear(); // NOTE : clears the active IDs, since there are no used IDs
		_freedIDs.clear(); //  NOTE : clears the freed IDs,  since there are no used IDs
		_maxID = 0;

		resizeTbl(); // NOTE : resize the component table to the initial size
		return;
	}
	else
	{
		id_t newMax = *std::max_element( _usedIDs.begin(), _usedIDs.end()); // NOTE : finds new maxID based on the used IDs

		if ( newMax == _maxID )
		{
			qlog( "updateMaxID : maxID is already up to date", DEBUG, 0 );
			return;
		}
		else
		{
			_maxID = newMax;
			qlog( "updateMaxID : updated maxID to " + std::to_string( _maxID ), INFO, 0 );
		}
	}

	auto it = _freedIDs.upper_bound( _maxID ); // NOTE : find the first element greater than _maxID
	if ( it != _freedIDs.end() )
	{
			_freedIDs.erase( it, _freedIDs.end() ); // NOTE : erase all elements from 'it' to the end
			qlog("updateMaxID : removed freed IDs greater than maxID", DEBUG, 0);
	}
	resizeTbl(); // NOTE : resize the component table if necessary
}
id_t EntityMngr::getNewID()
{
	flog( 0 );
	id_t newID = 0;

	if ( _freedIDs.empty() ) // NOTE : if there are no previously freed IDs, we need to get a brand a new one
	{
		newID = ++_maxID; // NOTE : preincrementation also prevents giving ID 0, since it is reserved for invalid entities
		qlog( "getNewID : no previously freed ID available, creating a new ID " + std::to_string( newID ), DEBUG, 0 );
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

		qlog( "initTbl : initialized component table for type " + to_string( type ), DEBUG, 0 );
	}
	qlog( "initTbl : initialized component tables with size " + std::to_string( _CmpTblSize ), INFO, 0 );
}
void EntityMngr::resizeTbl()
{
	flog( 0 );


	if( _CmpTblSize > TblGrpSize && _maxID < _CmpTblSize - TblGrpSize - 4 )
	{ // NOTE : giving ourself some margin to avoid potential resizing back-and-forth issues

		qlog( "resizeTbl : shrinking component tables", DEBUG, 0 );
		_CmpTblSize -= TblGrpSize;
	}
	elif( _maxID >= _CmpTblSize - 1 )
	{

		qlog( "resizeTbl : expanding component tables", DEBUG, 0 );
		_CmpTblSize += TblGrpSize;
	}
	else { qlog( "resizeTbl : no need to resize component tables" , DEBUG, 0 ); return; }

	for( comp_count_t type = 0; type < CT_COUNT; ++type ){ _CmpTbl[ type ].resize( _CmpTblSize ); }

	qlog( "! resized all component tables !", INFO, 0 );
}
void EntityMngr::resetTbl()
{
	flog( 0 );
	for( comp_count_t type = 0; type < CT_COUNT; ++type ){ _CmpTbl[ type ].clear(); }

	_CmpTblSize = 0; // NOTE : reset the component table size
	qlog( "deinitTbl : deinitialized all component tables", INFO, 0 );
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
		qlog( "resetComps : invalid component type " + to_string( type ), ERROR, 0 );
		return;
	}
	for( id_t id = 1; id <= _maxID; ++id ){ resetComp( id, type ); } // TODO : iterate through used IDs instead of all IDs

	qlog( "resetComps : reset all components of type " + to_string( type ), DEBUG, 0 );
}
void EntityMngr::resetComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( id, type ))
	{
		qlog( "resetComp : invalid component type or ID", ERROR, 0 );
		return;
	}

	CompBase *comp = getComp( id, type );
	if( comp == nullptr )
	{
		qlog( "resetComp : component of type " + to_string( type ) + " does not exist for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return;
	}
	else { comp->deinit(); } // NOTE : deinitialize the component

	qlog( "resetComp : reset component of type " + to_string( type ) + " for entity with ID " + std::to_string( id ), DEBUG, 0 );
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

// ================================ COMPONENT METHODS

bool EntityMngr::canTick( id_t id ) const
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "canTick : ID cannot be 0", WARN, id );
		return false;
	}
	if( !isUsed( id ))
	{
		qlog( "canTick : entity does not exist", ERROR, id );
		return false;
	}
	if( !isActive( id ))
	{
		qlog( "canTick : entity is not active", INFO, id );
		return false;
	}
	return true; // NOTE : if all checks passed, the entity can tick
}
bool EntityMngr::canTick( id_t id, comp_type_e type ) const
{
	flog( id );

	if( !GetNG->canEngineTick() )
	{
		qlog( "CompBase::canTick : Engine cannot tick", INFO, id );
		return false;
	}
	if( !canTick( id ))
	{
		qlog( "CompBase::canTick : entity cannot tick", DEBUG, id );
		return false;
	}
	if( !_CmpTbl[ type ][ id ].isInit() )
	{
		qlog( "CompBase::canTick : component is not initialized", DEBUG, id );
		return false;
	}
	return true; // NOTE : if all checks passed, the component can tick
}

bool EntityMngr::hasComp( id_t id, comp_type_e type ) const
{
	flog( 0 );

	if( !IsValid( id, type )){  return false; }
	bool exists = _CmpTbl[ type ][ id ].isInit();

	qlog( "hasComp : component of type " + to_string( type ) + ( exists ? " exists for entity with ID " + std::to_string( id ) : " does not exist for entity with ID " + std::to_string( id )), DEBUG, 0 );
	return exists;
}
bool EntityMngr::initComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( id, type )){  return false; }
	if( _CmpTbl[ type ][ id ].isInit())
	{
		qlog( "addComp : component of type " + to_string( type ) + " already exists for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return false;
	}

	_CmpTbl[ type ][ id ].init( id );
	return true;
}
bool EntityMngr::deinitComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( id, type )){  return false; }
	if( !_CmpTbl[ type ][ id ].isInit())
	{
		qlog( "delComp : component of type " + to_string( type ) + " does not exist for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return false;
	}

	_CmpTbl[ type ][ id ].deinit();
	return true;
}

CompBase *EntityMngr::getComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( id, type )){  return nullptr; }
	if( !_CmpTbl[ type ][ id ].isInit())
	{
		qlog( "getComp : component of type " + to_string( type ) + " does not exist for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return nullptr;
	}

	return &( _CmpTbl[ type ][ id ]);
}