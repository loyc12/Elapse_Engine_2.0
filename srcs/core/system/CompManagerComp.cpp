#include "../../../incs/engine.hpp"

BaseComp *CompFactory( comp_e compType, id_t id )
{
	flog( 0 );
	switch( compType )
	{
		case COMP_BASE_TYPE: return CompFactory< BaseComp >( id );
		//case COMP_SCRIPT:    return CompFactory< CompScript >( id );
		//case COMP_PHYSIC:    return CompFactory< CompPhysic >( id );
		//case COMP_MOVEMENT:  return CompFactory< CompMovement >( id );
		case COMP_POSITION:  return CompFactory< CompPos >( id );
		//case COMP_COLLIDE:   return CompFactory< CompCollide >( id );
		//case COMP_GRAPHIC:    return CompFactory< CompGraphic >( id );
		default: qlog( "CompFactory : Invalid component type", ERROR, 0 );
	}
	return nullptr;
}

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

	Entity *Ntt = _NttMap.find( id )->second;
	if( Ntt == nullptr )
	{
		qlog( "hasComponent : Entity is nullptr", WARN, 0 );
		return false;
	}

	return ( Ntt->hasComponent( compType ));
}
bool CompManager::addComponent( id_t id, comp_e compType )
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
bool CompManager::delComponent( id_t id, comp_e compType, bool freeMem )
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