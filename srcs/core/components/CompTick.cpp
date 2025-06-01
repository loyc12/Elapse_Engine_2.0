#include "../../../incs/core.hpp"

// ================================ BASE METHODS

bool CompBase::hasSisterComp( comp_type_e type ) const
{
	flog( _id );
	return GetNttM->hasComp( _id, type );
}

bool CompBase::canTick() const
{
	flog( _id );
	return( GetNttM->canTick( _id )); // NOTE : checks if the component can tick based on the EntityMngr's logic
}

// ================================ PHYSICS METHODS

bool CompPhysics::applyGravity( vec2_t gravity )
{
	flog( 0 );

	if( gravity == 0 )
	{
		qlog( "applyGravity : gravity vector is zero : skipping maths", DEBUG, 0 );
		return true;
	}
	if( !canTick() )
	{
		qlog( "applyGravity : cannot apply gravity, component is not initialized", ERROR, 0 );
		return false;
	}
	if( !hasSisterComp( CT_MOVEMENT ))
	{
		qlog( "applyGravity : transform component not found for entity with ID " + std::to_string( _id ), ERROR, 0 );
		return false;
	}

	// NOTE : getting the transform component
	CompMovement *moveComp = static_cast< CompMovement* >( GetNttM->getComp( _id, CT_TRANSFORM ));

	moveComp->moveAcceleration( gravity );

	return true;
}