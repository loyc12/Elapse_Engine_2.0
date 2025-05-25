#include "../../../incs/core.hpp"

// ================================ CORE METHODS

void EntityMngr::onAdd()
{
	flog( 0 );

	_maxID = 0;
	clearAllIDs();
	initCompTables();

	qlog( "onAdd : initialized EntityMngr", DEBUG, 0 );
}
void EntityMngr::onDel()
{
	flog( 0 );

	clearAllComps(); // NOTE : delete all components
	clearAllIDs(); //   NOTE : clear all ID sets & reset maxID to 0

	qlog( "onDel : destroyed EntityMngr", DEBUG, 0 );
}



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

	if ( _freedIDs.empty()) // NOTE : if there are no previously freed IDs, we need to get a brand a new one
	{
		qlog( "getNewID : no freed ID available, creating a new ID", DEBUG, 0 );
		newID = ++_maxID; // NOTE : preincrementation also prevents giving ID 0, since it is reserved for invalid entities
	}
	else // NOTE : if there are previously freed IDs, we can reuse one of them
	{
		auto it = _freedIDs.begin(); // NOTE : get the first freed ID

		qlog( "getNewID : reused previously freed ID " + std::to_string( newID ), DEBUG, 0 );

		newID = *it;
		_usedIDs.insert( *it );
		_freedIDs.erase(  it );
	}
	return newID;
}



void EntityMngr::clearAllIDs()
{
	flog( 0 );

	_usedIDs.clear();
	_activeIDs.clear();
//_toAddIDs.clear();
//_toDelIDs.clear();
	_freedIDs.clear();
	_maxID = 0;

	qlog( "clearAllIDs : cleared all ID sets & reset maxID", DEBUG, 0 );
}
void EntityMngr::clearID( id_t id )
{
	flog( 0 );

	if( id == 0 ) // NOTE : if the ID is 0, return
	{
		qlog( "clearID : ID cannot be 0", WARN, 0 );
		return;
	}

	_usedIDs.erase( id );
	_activeIDs.erase( id );
//_toAddIDs.erase( id );
//_toDelIDs.erase( id );
	_freedIDs.insert( id );
}



void EntityMngr::clearAllComps()
{
	flog( 0 );
	for( comp_count_t type = 0; type < COMP_TYPE_COUNT; ++type ){ clearCompsByType( comp_type_e( type )); } // NOTE : clear all components by type
	qlog( "clearAllComponents : cleared all components", DEBUG, 0 );
}
void EntityMngr::clearCompsByType( comp_type_e type )
{
	flog( 0 );
	if( !IsValid( type ))
	{
		qlog( "clearCompsByType : invalid component type " + std::to_string( type ), ERROR, 0 );
		return;
	}

	qlog( "clearCompsByType : deinitializing all components of type " + std::to_string( type ), DEBUG, 0 );
	for( id_t id = 1; id <= _maxID; ++id ){ _CmpTbl[ type ][ id ].deinit(); }
	_CmpTbl[ type ].clear();
}



void EntityMngr::initCompTables()
{
	flog( 0 );
	for( comp_count_t type = 0; type < COMP_TYPE_COUNT; ++type )
	{
		_CmpTbl[ type ].clear(); //             NOTE : clear the component table for the given type
		_CmpTbl[ type ].resize( GroupSize ); // NOTE : resize the component table to the maximum possible ID
		_maxPossibleID = GroupSize; //          NOTE : set the maximum possible ID to the initial size
		qlog( "initCompTables : initialized component table for type " + std::to_string( type ), DEBUG, 0 );
	}
	_maxID = 0; // NOTE : reset the maxID to 0
}
void EntityMngr::resizeCompTables()
{
	flog( 0 );

	if( _maxID < _maxPossibleID - 1 ) // NOTE : if the maxID is less than the maximum possible ID, return
	{
		if ( _maxPossibleID <= GroupSize || _maxID > _maxPossibleID - GroupSize )
		{
			qlog( "resizeCompTables : no need to resize component tables" , DEBUG, 0 );
			return;
		}

		qlog( "resizeCompTables : shrinking component tables", DEBUG, 0 );
		_maxPossibleID -= GroupSize; // NOTE : decrease the maximum possible ID by the group size
	}
	else
	{
		qlog( "resizeCompTables : expanding component tables", DEBUG, 0 );
		_maxPossibleID += GroupSize; // NOTE : increase the maximum possible ID by the group size
	}

	for( comp_count_t type = 0; type < COMP_TYPE_COUNT; ++type )
	{
		_CmpTbl[ type ].resize( _maxPossibleID );
		qlog( "resizeCompTables : resized component table for type " + std::to_string( type ), DEBUG, 0 );
	}
	qlog( "resizeCompTables : resized all component tables", DEBUG, 0 );
}

// ================================ ENTITY METHODS

bool EntityMngr::hasEntity( id_t id ) const
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "hasEntity : invalid ID " + std::to_string( id ), ERROR, 0 );
		return false; // NOTE : if the ID is invalid, return false
	}

	bool exists = _usedIDs.find( id ) != _usedIDs.end(); // NOTE : check if the ID exists in the used IDs

	qlog( "hasEntity : entity with ID " + std::to_string( id ) + ( exists ? " exists" : " does not exist" ), DEBUG, 0 );
	return exists;
}
bool EntityMngr::delEntity( id_t id )
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "delEntity : ID cannot be 0", WARN, 0 );
		return false;
	}

	auto it = _usedIDs.find( id ); // NOTE : find the ID in the used IDs
	if( it == _usedIDs.end()) //     NOTE : if the ID is not found, return false
	{
		qlog( "delEntity : entity with ID " + std::to_string( id ) + " does not exist", WARN, 0 );
		return false;
	}

	clearID( id ); // NOTE : clear the ID from all ID sets, then adds it to the freed IDs
	updateMaxID(); // NOTE : update the maxID after deleting the entity

	qlog( "delEntity : deleted entity with ID " + std::to_string( id ), DEBUG, 0 );
	return true;
}
id_t EntityMngr::addEntity()
{
	flog( 0 );
	id_t newID = getNewID(); // NOTE : get a new ID for the entity

	if( !IsValid( newID ))
	{
		qlog( "addEntity : failed to get a valid ID", ERROR, 0 );
		return 0;
	}
	_usedIDs.insert( newID ); // NOTE : add the new ID to the used IDs

	qlog( "addEntity : added entity with ID " + std::to_string( newID ), DEBUG, 0 );
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

	if( !hasEntity( id )) // NOTE : if the entity does not exist, return false
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

// ================================ COMPONENT METHODS

void EntityMngr::updateAllComps()
{
	flog( 0 );
	for( comp_count_t type = 0; type < COMP_TYPE_COUNT; ++type ){ updateCompsByType( comp_type_e( type )); } // NOTE : update all components by type

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
	comps.resize( COMP_TYPE_COUNT );

	if( !IsValid( id )) // NOTE : if the ID is invalid, return an empty component table
	{
		qlog( "getAllComps : ID cannot be 0", WARN, 0 );
		for( comp_count_t type = 0; type < COMP_TYPE_COUNT; ++type ){ comps[ type ] = CompBase(); } // NOTE : fill the component table with nullptrs
		return comps;
	}

	for( comp_count_t type = 0; type < COMP_TYPE_COUNT; ++type ){ comps[ type ] = _CmpTbl[ type ][ id ]; }
	return comps;
}
