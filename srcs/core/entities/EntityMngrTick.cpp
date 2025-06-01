#include "../../../incs/core.hpp"

// ================================ TICK METHODS

bool EntityMngr::tickCompsByType( comp_type_e type )
{
	flog( 0 );

	if( !IsValid( type ))
	{
		qlog( "tickCompsByType : invalid component type " + to_string( type ), ERROR, 0 );
		return false;
	}

	switch( type )
	{
		case CT_MOVEMENT:  return tickMovements();

		default:
			qlog( "tickCompsByType : no tick logic for component type " + to_string( type ), WARN, 0 );
			return false;
	}
}

// ================ MOVEMENT METHODS

bool EntityMngr::tickMovements()
{
	flog( 0 );
	for( id_t id : _activeIDs )
	{
		CompTransform *ct = static_cast< CompTransform* >( getComp( id, CT_TRANSFORM ));
		CompMovement  *cm = static_cast< CompMovement*  >( getComp( id, CT_MOVEMENT ));

		applyMovement( id, cm, ct ); // NOTE : apply the movement to the transform component
	}
	return true;
}
bool EntityMngr::applyMovement( id_t id, CompMovement *cm, CompTransform *ct )
{
	flog( id );

	if( cm == nullptr || !cm->isInit())
	{
		qlog( "applyMovement : movement component not found for entity with ID " + std::to_string( id ), ERROR, id );
		return false;
	}

	if( cm->_rAcc == 0 && cm->_lAcc == 0 && cm->_rVel == 0 && cm->_lVel == 0 )
	{
		qlog( "applyVelocity : no velocity or acceleration to apply : skipping maths", DEBUG, id );
		return true;
	}

	// NOTE : if there is acceleration, apply it to the velocity and reset the acceleration
	if( cm->_lAcc != 0 ){ cm->_lVel += cm->_lAcc * GDTS(); cm->_lAcc = 0; }
	if( cm->_rAcc != 0 ){ cm->_rVel += cm->_rAcc * GDTS(); cm->_rAcc = 0; }

	// NOTE : getting the transform component
	if( ct == nullptr || !ct->isInit())
	{
		qlog( "applyVelocity : transform component not found", ERROR, id );
		return false;
	}

	// NOTE : if there is velocity, apply it to the position
	if( cm->_lVel != 0 ){ ct->movePosition( cm->_lVel * GDTS() ); }
	if( cm->_rVel != 0 ){ ct->moveAngle(    cm->_rVel * GDTS() ); }

	return true;
}