#include "../../../incs/engine.hpp"

CompBase *CompFactory( comp_type_e compType, Entity *Ntt, bool isActive )
{
	flog( 0 );
	switch( compType )
	{
		case COMP_POSITION: freturn CompFactory< CompPos >(     Ntt, isActive );
		case COMP_MOVEMENT: freturn CompFactory< CompMove >(    Ntt, isActive );
		case COMP_PHYSIC:   freturn CompFactory< CompPhys >(    Ntt, isActive );
		case COMP_COLLIDE:  freturn CompFactory< CompCollide >( Ntt, isActive );

	//case COMP_TEXT:     freturn CompFactory< CompText >(    Ntt, isActive );
	//case COMP_SOUND:    freturn CompFactory< CompSound >(   Ntt, isActive );
	//case COMP_SHAPE:    freturn CompFactory< CompShape >(   Ntt, isActive );
		case COMP_GRAPHIC:  freturn CompFactory< CompGraph >(   Ntt, isActive );

	//case COMP_SCRIPT:   freturn CompFactory< CompScript >(  Ntt, isActive );

		case COMP_TYPE_BASE:
	 		qlog( "CompFactory : Generating a base component", WARN, 0 );
			freturn CompFactory< CompBase >( Ntt, isActive );

		default: qlog( "CompFactory : Invalid component type", ERROR, 0 );
	}
	freturn nullptr;
}

// ================================ ACCESSORS / MUTATORS

// ================ COMPONENT METHODS

comp_count_t EntityMngr::getCompCount( id_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ freturn 0; }

	Entity *Ntt = getEntity( id );
	if( Ntt == nullptr ){ freturn 0; }

	freturn Ntt->getCompCount();
}
comp_count_t EntityMngr::getActCompCount( id_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ freturn 0; }

	Entity *Ntt = getEntity( id );
	if( Ntt == nullptr ){ freturn 0; }

	freturn Ntt->getActCompCount();
}

bool EntityMngr::hasComponent( id_t id, comp_type_e compType ) const
{
	flog( 0 );
	if( !hasEntity( id )){ freturn false; }

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "hasComponent : Entity is nullptr", WARN, 0 );
		freturn false;
	}

	freturn ( Ntt->hasComponent( compType ));
}
bool EntityMngr::addComponent( id_t id, comp_type_e compType )
{
	flog( 0 );
	if( !hasEntity( id )){ freturn false; }

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "addComponent : Entity is nullptr", WARN, 0 );
		freturn false;
	}

	freturn ( Ntt->addComponent( compType ));
}
bool EntityMngr::delComponent( id_t id, comp_type_e compType, bool freeMem )
{
	flog( 0 );
	if( !hasEntity( id )){ freturn false; }

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "delComponent : Entity is nullptr", WARN, 0 );
		freturn false;
	}

	freturn ( Ntt->delComponent( compType, freeMem ));
}