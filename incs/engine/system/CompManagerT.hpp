
#ifndef COMP_MANAGER_TPP
# define COMP_MANAGER_TPP

# pragma once
# include "./CompManager.hpp"


TTC CompT *CompFactory( comp_e compType, id_t id )
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
		//case COMP_RENDER:    return CompFactory< CompRender >( id );
		default:
		qlog( "CompFactory : Invalid component type", ERROR, 0 );
		return nullptr;
	}
}

// ================================ ACCESSORS / MUTATORS

// ================ COMPONENT METHODS

TTC CompT *CompManager::getComponent( id_t id, comp_e compType ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return nullptr; } // NOTE : returns a null BaseComponent ( innactive )

	Entity *ent = _NttMap.find( id )->second;
	if( ent == nullptr )
	{
		qlog( "getComponent : Entity is nullptr", WARN, 0 );
		return nullptr;
	}

	CompT *comp = ent->getComponent< CompT >( compType );
	if( comp == nullptr )
	{
		qlog( "getComponent : Component is nullptr", WARN, 0 );
		return nullptr;
	}
	return nullptr;
}

#endif // COMP_MANAGER_TPP