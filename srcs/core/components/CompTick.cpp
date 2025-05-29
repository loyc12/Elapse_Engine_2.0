#include "../../../incs/core.hpp"

// ================================ BASE METHODS

bool CompBase::hasSisterComp( comp_type_e type ) const // TODO : move this logic to the EntityMngr, so that it can run in batches
{
	flog( _id );
	return GetNttM->hasComp( type, _id );
}

bool CompBase::canTick() const // TODO : move this logic to the EntityMngr, so that it can run in batches
{
	flog( _id );

	if( !isInit() )
	{
		qlog( "CompBase::canTick : component with ID " + std::to_string( _id ) + " is not initialized", WARN, 0 );
		return false;
	}
	if( !GetNttM->isActive( _id ))
	{
		qlog( "CompBase::canTick : component with ID " + std::to_string( _id ) + " is not active", WARN, 0 );
		return false;
	}
	if( !GetNG->canEngineTick() )
	{
		qlog( "CompBase::canTick : Engine cannot tick", WARN, 0 );
		return false;
	}
	return true;
}

// ================================ MOVEMENT METHODS

bool CompMovement::applyVelocity() // TODO : move this logic to the EntityMngr, so that it can run in batches
{
	flog( _id );

	if( _rAcc == 0 && _lAcc == 0 && _rVel == 0 && _lVel == 0 )
	{
		qlog( "applyVelocity : no velocity or acceleration to apply : skipping maths", DEBUG, _id );
		return true;
	}
	if( !canTick() )
	{
		qlog( "applyVelocity : component is not initialized", ERROR, _id );
		return false;
	}

	// NOTE : if there is acceleration, apply it to the velocity and reset the acceleration
	if( _lAcc != 0 ){ _lVel += _lAcc * GDTS(); _lAcc = 0; }
	if( _rAcc != 0 ){ _rVel += _rAcc * GDTS(); _rAcc = 0; }

	// NOTE : getting the transform component
	if( !hasSisterComp( CT_TRANSFORM )) // TODO : move this logic to the EntityMngr, so that it can run in batches
	{
		qlog( "applyVelocity : transform component not found", ERROR, _id );
		return false;
	}
	CompTransform *transComp = static_cast< CompTransform* >( GetNttM->getComp( CT_TRANSFORM, _id ));

	// NOTE : if there is velocity, apply it to the position
	if( _lVel != 0 ){ transComp->movePosition( _lVel * GDTS() ); }
	if( _rVel != 0 ){ transComp->moveAngle(    _rVel * GDTS() ); }

	return true;
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
	CompMovement *moveComp = static_cast< CompMovement* >( GetNttM->getComp( CT_TRANSFORM, _id ));

	moveComp->moveAcceleration( gravity );

	return true;
}