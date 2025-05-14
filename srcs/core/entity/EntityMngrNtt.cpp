#include "../../../incs/engine.hpp"

// ================================ ASSOCIATED FUNCTIONS

Entity *CpyEntityOver( Entity *src, Entity *dst )
{
	flog( 0 );
	if( src == nullptr )
	{
		qlog( "cpyEntityOver : src is nullptr", INFO, 0 );
		if( dst != nullptr )
		{
			qlog( "cpyEntityOver : dst is not nullptr : deleting dst", INFO, 0 );
			delete dst;
			dst = nullptr;
		}
		else
		{
			qlog( "cpyEntityOver : dst is nullptr : nothing to do", INFO, 0 );
		}
	}
	else
	{
		qlog( "cpyEntityOver : src is not nullptr", INFO, 0 );
		if( dst == nullptr )
		{
			qlog( "cpyEntityOver : dst is nullptr : creating new dst", INFO, 0 );
			dst = EntityMngr::EntityFactory( src );
		}
		else
		{
			qlog( "cpyEntityOver : dst is not nullptr : copying src to dst", INFO, 0 );
			*dst = *src;
		}
	}
	return dst;
}

// ================================ CORE METHODS

void EntityMngr::deleteAllEntities() // TODO : TEST ME
{
	flog( 0 );
	for( auto it = _NttMap.begin(); it != _NttMap.end(); )
	{
		if( !delThatEntity( it->second, true )){ qlog( "deleteAllEntities : entity already deleted for ID:" + std::to_string( it->first ), INFO, 0 ); }
		it = _NttMap.erase( it );
	}

	qlog( "deleteAllEntities : Clearing the entity map", INFO, 0 );
	_NttMap.clear();
	_maxID = 0;
}

// ================================ ACCESSORS / MUTATORS

// ================ ENTITY METHODS

id_t EntityMngr::getEntityCount() const
{
	flog( 0 );
	return _NttMap.size();
}

Entity *EntityMngr::getEntity( id_t id ) const
{
	flog( 0 );
	if( id == 0 ){ return nullptr; }

	if( !hasEntity( id )){ return nullptr; } // NOTE : returns a null entity ( ID = 0 )
	return _NttMap.find( id )->second;
}

bool EntityMngr::hasEntity( id_t id ) const
{
	flog( 0 );
	if( id == 0 ){ return false; }
	return ( _NttMap.find( id ) != _NttMap.end() );
}
bool EntityMngr::addEntity( id_t id )
{
	flog( 0 );
	if( id == 0 ){ return false; }
	if( hasEntity( id ))
	{
		qlog( "addEntity : Entity already exists in the map", WARN, 0 );
		return false;
	}

	qlog( "addEntity : Adding entity with ID: " + std::to_string( id ), INFO, 0 );

	_NttMap[ id ] = EntityMngr::EntityFactory( id );

	qlog( "addEntity : Added entity with ID: " + std::to_string( id ), INFO, 0 );

	if( id > _maxID ){ _maxID = id; }
	return true;
}

bool EntityMngr::delEntity( id_t id, bool freeMemory )
{
	flog( 0 );
	if( id == 0 ){ return false; }
	if( !hasEntity( id )){ return false; }
	qlog( "delEntity : Deleting entity with ID: " + std::to_string( id ), INFO, 0 );

	auto it = _NttMap.find( id );

	if( it->second != nullptr )
	{
		if( freeMemory )
		{
			delete it->second;
			it->second = nullptr;
		}
		else { it->second->delID(); }
	}
	else { qlog( "delEntity : Entity is already a nullptr", WARN, 0 ); }
	_NttMap.erase( it );

	qlog( "delEntity : Deleted entity with ID: " + std::to_string( id ), INFO, 0 );
	if( id == _maxID ){ --_maxID; }

	return true;
}

bool EntityMngr::hasThatEntity( Entity *Ntt ) const
{
	flog( 0 );
	if( Ntt == nullptr ){ return false; }

	for ( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		if( it->second == nullptr )
		{
			qlog( "hasThatEntity : Skipping nullptr entity", INFO, 0 );
			continue;
		}
		if( it->second == Ntt )
		{
			qlog( "hasThatEntity : Found entity with ID: " + std::to_string( it->first ), DEBUG, 0 );
			return true;
		}
	}
	qlog( "hasThatEntity : Specific entity not found in the map", DEBUG, 0 );

	return ( false );
}
bool EntityMngr::addThatEntity( Entity *Ntt )
{
	flog( 0 );
	if( hasThatEntity( Ntt ))
	{
		qlog( "addThatEntity : Entity already exists in the map", WARN, 0 );
		return false;
	}

	Ntt->setID( getNewID() );
	_NttMap[ Ntt->getID() ] = { Ntt };

	qlog( "addThatEntity : Added entity with ID: " + std::to_string( Ntt->getID()), INFO, 0 );
	return true;
}
bool EntityMngr::delThatEntity( Entity *Ntt, bool freeMemory )
{
	flog( 0 );
	if( Ntt == nullptr ){ return false; }
	if( !hasThatEntity( Ntt )){ return false; }

	qlog( "delThatEntity : Deleting entity with ID: " + std::to_string( Ntt->getID()), INFO, 0 );

	auto it = _NttMap.find( Ntt->getID() );

	if( it->second != nullptr )
	{
		it->second->delID();
		if( freeMemory )
		{
			qlog( "delThatEntity : Freeing the memory of entity with ID: " + std::to_string( it->first ), DEBUG, 0 );
			delete it->second;
		}
		it->second = nullptr;
	}

	qlog( "delThatEntity : Deleted the entity", INFO, 0 );
	return true;
}

bool EntityMngr::defragEntityMap()
{
	flog( 0 );
	qlog( "defragEntityMap : Defragmenting the entity map", INFO, 0 );

	for( auto it = _NttMap.begin(); it != _NttMap.end(); )
	{
		if( it->second == nullptr )
		{
			qlog( "defragEntityMap : Removing nullptr entity", INFO, 0 );
			it = _NttMap.erase( it );
		}
		else { ++it; }
	}

	updateMaxID();
	return true;
}

bool EntityMngr::dupEntity( id_t src ){ return dupEntity( getEntity( src )); }
bool EntityMngr::dupEntity( Entity *src )
{
	flog( 0 );
	if( src == nullptr ){ return false; }

	Entity *newNtt = EntityMngr::EntityFactory( src );

	if( newNtt == nullptr )
	{
		qlog( "dupEntity : Failed to allocate memory for new entity", ERROR, 0 );
		return false;
	}

	qlog( "dupEntity : Created new entity with ID: " + std::to_string( newNtt->getID()), INFO, 0 );
	return true;
}

// ================================ FACTORY METHODS

Entity *EntityMngr::EntityFactory( id_t id )
{
	flog( 0 );

	Entity *Ntt = new Entity( bool( id ), id );

	if( Ntt == nullptr )
	{
		qlog( "EntityFactory : Failed to allocate memory for new entity", ERROR, 0 );
		return nullptr;
	}
	return Ntt;
}
Entity *EntityMngr::EntityFactory( Entity *src, id_t id )
{
	flog( 0 );
	Entity* Ntt = EntityMngr::EntityFactory( id );

	if( Ntt != nullptr ){ *Ntt = *src; } // NOTE : copies the entity and its components

	return Ntt;
}
