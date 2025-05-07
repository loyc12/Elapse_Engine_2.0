#include "../../../incs/engine.hpp"

// ================================ METHODS UPDATE METHODS

void CompManager::updateAllEntities()
{	// NOTE : calls the onTick() method of all components in the map ( one entity at a time )
	flog( 0 );
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it ) // NOTE : Loop on all entities
	{
		Entity *Ntt = it->second;
		if( Ntt == nullptr )
		{
			qlog( "CompManager::updateAllEntities : Skipping nullptr entity", INFO, 0 );
			continue;
		}
		for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i ) // NOTE : loop on all component types
		{
			if( Ntt->getCompArray()[ i ] == nullptr ){ continue; }
			Ntt->tickComponent( comp_type_e( i ));
		}
	}
}
void CompManager::updateAllComponents()
{	// NOTE : calls the onTick() method of all components in the map ( each component type at a time)
	flog( 0 );
	for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i ) // NOTE : loop on all component types
	{
		updateCompsByType( comp_type_e( i ));
	}
}
void CompManager::updateCompsByType( comp_type_e compType )
{	// NOTE : calls the onTick() method of all components of the given type in the map
	flog( 0 );
	if( !IsValidCompType( compType )){ return; }
	// DEBUG : remove this qlog
	qlog( "updateCompsByType : Updating components of type: " + std::to_string( compType ), DEBUG, 0 );
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it ) // NOTE : Loop on all entities
	{
		Entity *Ntt = it->second;

		if( Ntt == nullptr )
		{
			qlog( "CompManager::updateAllComponents : Skipping nullptr entity", INFO, 0 );
			continue;
		}
		if( Ntt->getCompArray()[ compType ] == nullptr )
		{
			qlog( "CompManager::updateCompsByType : Skipping nullptr component", INFO, 0 );
			continue;
		}
		Ntt->tickComponent( comp_type_e( compType ));
	}
}

// ================ TICK METHODS

void CompManager::tickMovements()
{
	flog( 0 );
	OnTickMovements(); // from injectors.hpp
	updateCompsByType( COMP_MOVEMENT );
}
void CompManager::tickCollides()
{
	flog( 0 );
	OnTickCollides(); // from injectors.hpp
	updateCompsByType( COMP_COLLIDE );
}
void CompManager::tickPhysics()
{
	flog( 0 );
	OnTickPhysics(); // from injectors.hpp
	updateCompsByType( COMP_PHYSIC );
}

void CompManager::tickSounds()
{
	flog( 0 );
	OnTickSounds(); // from injectors.hpp
	//updateCompsByType( COMP_SOUND );
}
void CompManager::tickShapes()
{
	flog( 0 );
	OnTickShapes(); // from injectors.hpp
	//updateCompsByType( COMP_SHAPE );
}
void CompManager::tickGraphics()
{
	flog( 0 );
	OnTickGraphics(); // from injectors.hpp
	updateCompsByType( COMP_GRAPHIC );
}

void CompManager::tickScripts()
{
	flog( 0 );
	OnTickScripts(); // from injectors.hpp
	//updateCompsByType( COMP_SCRIPT );
}