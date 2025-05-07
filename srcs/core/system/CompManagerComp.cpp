#include "../../../incs/engine.hpp"

CompBase *CompFactory( comp_type_e compType, Entity *Ntt, bool isActive )
{
	flog( 0 );
	switch( compType )
	{
		case COMP_POSITION: return CompFactory< CompPos >(     Ntt, isActive );
		case COMP_MOVEMENT: return CompFactory< CompMove >(    Ntt, isActive );
		case COMP_PHYSIC:   return CompFactory< CompPhys >(    Ntt, isActive );
		case COMP_COLLIDE:  return CompFactory< CompCollide >( Ntt, isActive );

	//case COMP_TEXT:     return CompFactory< CompText >(    Ntt, isActive );
	//case COMP_SOUND:    return CompFactory< CompSound >(   Ntt, isActive );
	//case COMP_SHAPE:    return CompFactory< CompShape >(   Ntt, isActive );
		case COMP_GRAPHIC:  return CompFactory< CompGraph >(   Ntt, isActive );

	//case COMP_SCRIPT:   return CompFactory< CompScript >(  Ntt, isActive );

		case COMP_TYPE_BASE:
	 		qlog( "CompFactory : Generating a base component", WARN, 0 );
			return CompFactory< CompBase >( Ntt, isActive );

		default: qlog( "CompFactory : Invalid component type", ERROR, 0 );
	}
	return nullptr;
}

// ================================ ACCESSORS / MUTATORS

// ================ COMPONENT METHODS

comp_count_t CompManager::getCompCount( id_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return 0; }

	Entity *Ntt = getEntity( id );
	if( Ntt == nullptr ){ return 0; }

	return Ntt->getCompCount();
}
comp_count_t CompManager::getActCompCount( id_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return 0; }

	Entity *Ntt = getEntity( id );
	if( Ntt == nullptr ){ return 0; }

	return Ntt->getActCompCount();
}

bool CompManager::hasComponent( id_t id, comp_type_e compType ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "hasComponent : Entity is nullptr", WARN, 0 );
		return false;
	}

	return ( Ntt->hasComponent( compType ));
}
bool CompManager::addComponent( id_t id, comp_type_e compType )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "addComponent : Entity is nullptr", WARN, 0 );
		return false;
	}

	return ( Ntt->addComponent( compType ));
}
bool CompManager::delComponent( id_t id, comp_type_e compType, bool freeMem )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "delComponent : Entity is nullptr", WARN, 0 );
		return false;
	}

	return ( Ntt->delComponent( compType, freeMem ));
}