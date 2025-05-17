#include "../../../incs/engine.hpp"

// ================================ METHODS UPDATE METHODS

void EntityMngr::updateAllEntities()
{	// NOTE : calls the onTick() method of all components in the map ( one entity at a time )
	flog( 0 );
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it ) // NOTE : Loop on all entities
	{
		Entity *Ntt = it->second;
		if( Ntt == nullptr )
		{
			qlog( "EntityMngr::updateAllEntities : Skipping nullptr entity", INFO, 0 );
			continue;
		}
		for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i ) // NOTE : loop on all component types
		{
			if( Ntt->getCompArray()[ i ] == nullptr ){ continue; }
			Ntt->tickComponent( comp_type_e( i ));
		}
	}
	fend();
}
void EntityMngr::updateAllComponents()
{	// NOTE : calls the onTick() method of all components in the map ( each component type at a time)
	flog( 0 );
	for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i ) // NOTE : loop on all component types
	{
		updateCompsByType( comp_type_e( i ));
	}
	fend();
}
void EntityMngr::updateCompsByType( comp_type_e compType )
{	// NOTE : calls the onTick() method of all components of the given type in the map
	flog( 0 );
	if( !IsValidCompType( compType )){ freturn; }

	qlog( "updateCompsByType : Updating components of type: " + std::to_string( compType ), DEBUG, 0 );

	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it ) // NOTE : Loop on all entities
	{
		Entity *Ntt = it->second;

		if( Ntt == nullptr )
		{
			qlog( "EntityMngr::updateAllComponents : Skipping nullptr entity", INFO, 0 );
			continue;
		}
		if( Ntt->getCompArray()[ compType ] == nullptr )
		{
			qlog( "EntityMngr::updateCompsByType : Skipping nullptr component", INFO, 0 );
			continue;
		}
		Ntt->tickComponent( comp_type_e( compType ));
	}
	fend();
}

// ================ TICK METHODS

void EntityMngr::tickMovements()
{
	flog( 0 );
	OnTickMovements(); // from injectors.hpp
	updateCompsByType( COMP_MOVEMENT );
	fend();
}
void EntityMngr::tickCollides()
{
	flog( 0 );
	OnTickCollides(); // from injectors.hpp
	updateCompsByType( COMP_COLLIDE );
	fend();
}
void EntityMngr::tickPhysics()
{
	flog( 0 );
	OnTickPhysics(); // from injectors.hpp
	updateCompsByType( COMP_PHYSIC );
	fend();
}

void EntityMngr::tickSounds()
{
	flog( 0 );
	OnTickSounds(); // from injectors.hpp
	//updateCompsByType( COMP_SOUND );
	fend();
}
void EntityMngr::tickShapes()
{
	flog( 0 );
	OnTickShapes(); // from injectors.hpp
	//updateCompsByType( COMP_SHAPE );
	fend();
}
void EntityMngr::tickGraphics()
{
	flog( 0 );
	OnTickGraphics(); // from injectors.hpp
	updateCompsByType( COMP_GRAPHIC );
	fend();
}

void EntityMngr::tickScripts()
{
	flog( 0 );
	OnTickScripts(); // from injectors.hpp
	//updateCompsByType( COMP_SCRIPT );
	fend();
}