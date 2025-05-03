#include "../../../incs/engine.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ COMPONENT METHODS

CompC_t CompManager::getCompCount( id_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return 0; }

	Entity *Ntt = getEntity( id );
	if( Ntt == nullptr ){ return 0; }

	return Ntt->getCompCount();
}

bool CompManager::hasComponent( id_t id, comp_e compType ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	Entity *ent = _NttMap.find( id )->second;
	if( ent == nullptr )
	{
		qlog( "hasComponent : Entity is nullptr", WARN, 0 );
		return false;
	}

	return ( ent->hasComponent( compType ));
}
bool CompManager::addComponent( id_t id, comp_e compType )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	Entity *ent = _NttMap.find( id )->second;
	if( ent == nullptr )
	{
		qlog( "addComponent : Entity is nullptr", WARN, 0 );
		return false;
	}

	return ( ent->addComponent( compType ));
}
bool CompManager::delComponent( id_t id, comp_e compType, bool freeMem )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	Entity *ent = _NttMap.find( id )->second;
	if( ent == nullptr )
	{
		qlog( "delComponent : Entity is nullptr", WARN, 0 );
		return false;
	}

	return ( ent->delComponent( compType, freeMem ));
}