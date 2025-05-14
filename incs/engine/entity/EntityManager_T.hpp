
#ifndef ENTITY_MANAGER_TPP
# define ENTITY_MANAGER_TPP

# pragma once
# include "./EntityManager.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ COMPONENT METHODS

/*
TTC CompT *EntityManager::getComponent( id_t id, comp_type_e compType ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return nullptr; } // NOTE : returns a null CompBaseonent ( innactive )

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "getComponent : Entity is nullptr", WARN, 0 );
		return nullptr;
	}

	CompT *comp = Ntt->getComponent< CompT >( compType );
	if( comp == nullptr )
	{
		qlog( "getComponent : Component is nullptr", WARN, 0 );
		return nullptr;
	}
	return nullptr;
}
*/
TTC CompT *EntityManager::getComponent( id_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return nullptr; } // NOTE : returns a null CompBaseonent ( innactive )

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "getComponent : Entity is nullptr", WARN, 0 );
		return nullptr;
	}

	CompT *comp = Ntt->getComponent< CompT >();
	if( comp == nullptr )
	{
		qlog( "getComponent : Component is nullptr", WARN, 0 );
		return nullptr;
	}
	return nullptr;
}


#endif // ENTITY_MANAGER_TPP