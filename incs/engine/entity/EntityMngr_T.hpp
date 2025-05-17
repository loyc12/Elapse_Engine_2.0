
#ifndef ENTITY_MNGR_TPP
# define ENTITY_MNGR_TPP

# pragma once
# include "./EntityMngr.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ COMPONENT METHODS

/*
TTC CompT *EntityMngr::getComponent( id_t id, comp_type_e compType ) const
{
	flog( 0 );
	if( !hasEntity( id )){ freturn nullptr; } // NOTE : returns a null CompBaseonent ( innactive )

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "getComponent : Entity is nullptr", WARN, 0 );
		freturn nullptr;
	}

	CompT *comp = Ntt->getComponent< CompT >( compType );
	if( comp == nullptr )
	{
		qlog( "getComponent : Component is nullptr", WARN, 0 );
		freturn nullptr;
	}
	freturn nullptr;
}
*/
TTC CompT *EntityMngr::getComponent( id_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ freturn nullptr; } // NOTE : returns a null CompBaseonent ( innactive )

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "getComponent : Entity is nullptr", WARN, 0 );
		freturn nullptr;
	}

	CompT *comp = Ntt->getComponent< CompT >();
	if( comp == nullptr )
	{
		qlog( "getComponent : Component is nullptr", WARN, 0 );
		freturn nullptr;
	}
	freturn nullptr;
}


#endif // ENTITY_MNGR_TPP