#include "../../../incs/engine.hpp"

// ================================ METHODS UPDATE METHODS

void CompManager::updateAllEntities()
{	// NOTE : calls the onTick() method of all components in the map ( one entity at a time )
	flog( 0 );
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		if( it->second == nullptr )
		{
			qlog( "updateAllEntities : Skipping nullptr entity", INFO, 0 );
			continue;
		}
		for ( CompC_t i = 0; i < COMP_TYPE_COUNT; ++i ){ it->second->tickComponent( comp_e( i )); }
	}
}
void CompManager::updateAllComponents()
{	// NOTE : calls the onTick() method of all components in the map ( each component type at a time)
	flog( 0 );
	for ( CompC_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
		{
			if( it->second == nullptr ){ continue; }
			it->second->tickComponent( comp_e( i ));
		}
	}

}

void CompManager::updateCompsByType( comp_e compType )
{	// NOTE : calls the onTick() method of all components of the given type in the map
	flog( 0 );
	if( !IsValidCompType( compType ))
	{
		qlog( "updateCompsByType : Invalid component type", ERROR, 0 );
		return;
	}
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		if( it->second == nullptr ){ continue; }
		it->second->tickComponent( compType );
	}
}

// ================ TICK METHODS

void CompManager::tickScripts()
{
	flog( 0 );
	OnTickScripts(); // from injectors.hpp
	updateCompsByType( COMP_SCRIPT );
}

void CompManager::tickPhysics()
{
	flog( 0 );
	OnTickPhysics(); // from injectors.hpp
	updateCompsByType( COMP_PHYSIC );
}

void CompManager::tickCollides()
{
	flog( 0 );
	OnTickCollides(); // from injectors.hpp
	updateCompsByType( COMP_COLLIDE );
}

void CompManager::tickMovements()
{
	flog( 0 );
	OnTickMovements(); // from injectors.hpp
	updateCompsByType( COMP_MOVEMENT );
}

void CompManager::tickVisuals()
{
	flog( 0 );
	OnTickVisuals(); // from injectors.hpp
	updateCompsByType( COMP_GRAPHIC );
}