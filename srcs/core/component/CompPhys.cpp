#include "../../../incs/engine.hpp"
#include <raylib.h>

// ================================ CORE METHODS

void CompPhys::onCpy( const CompPhys &rhs )
{
	flog( 0 );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_dynamic = rhs._dynamic;

	_mass = rhs._mass;
	_drag = rhs._drag;
	_fric = rhs._fric;
	_elas = rhs._elas;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompPhys::~CompPhys()
{
	flog( 0 );
}

CompPhys::CompPhys() : CompBase(),
	_dynamic( COMP_DEF_DYNAMIC ),

	_mass( COMP_MIN_MASS ),
	_drag( COMP_MIN_DRAG ),
	_fric( COMP_MIN_FRIC ),
	_elas( COMP_MIN_ELAS )
{
	flog( 0 );
}

CompPhys::CompPhys( Entity *Ntt, bool isActive, bool isDynamic, fixed_t mass, fixed_t drag, fixed_t fric, fixed_t elas ) :
	CompBase( Ntt, isActive ),
	_dynamic( isDynamic ),

	_mass( fmin( COMP_MIN_MASS, mass )),
	_drag( fmin( COMP_MIN_DRAG, drag )),
	_fric( fmin( COMP_MIN_FRIC, fric )),
	_elas( fmin( COMP_MIN_ELAS, elas ))
{
	flog( 0 );
}

CompPhys::CompPhys( const CompPhys &rhs ) : CompPhys()
{
	flog( 0 );
	*this = rhs;
}
CompPhys &CompPhys::operator=( const CompPhys &rhs )
{
	flog( 0 );
	onCpy( rhs );
	return *this;
}

// ================================ ACCESSORS / MUTATORS

bool CompPhys::hasSisterComps() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompPhys::hasSisterComps() : no entity found for component", WARN, 0 );
		return false;
	}
	if( !getEntity()->hasComponent< CompPos >() )
	{
		qlog( "CompPhys::hasSisterComps() : no position component found for entity", INFO, 0 );
		return false;
	}
	if( !getEntity()->hasComponent< CompMove >() )
	{
		qlog( "CompPhys::hasSisterComps() : no movement component found for entity", INFO, 0 );
		return false;
	}
	return true;
}

vec2_t CompPhys::applyDrag()
{
	flog( 0 );
	if( !hasSisterComps() ){ return { 0, 0 }; }
	vec2_t dAcc = {
		-_drag * getEntity()->getVel().x / _mass,
		-_drag * getEntity()->getVel().y / _mass
	};
	getEntity()->moveAcc( dAcc );
	return dAcc;
}
vec2_t CompPhys::applyFriction( vec2_t surfaceNormal )
{
	flog( 0 );
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( surfaceNormal.x == 0 && surfaceNormal.y == 0 )
	{
		qlog( "CompPhys::applyFriction() : surface normal is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	( void )surfaceNormal;
	// TODO : replace this with a real friction calculation
	return { TEMP_VALUE, TEMP_VALUE };
}
vec2_t CompPhys::applyBounce( vec2_t surfaceNormal )
{
	flog( 0 );
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( surfaceNormal.x == 0 && surfaceNormal.y == 0 )
	{
		qlog( "CompPhys::applyBounce() : surface normal is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	( void )surfaceNormal;
	// TODO : replace this with a real bounce calculation
	return { TEMP_VALUE, TEMP_VALUE };
}

// ================ CALCULATED PROPERTIES METHODS

fixed_t CompPhys::getAvgRad() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompPhys::getAvgRad() : no entity found for component", ERROR, 0 );
		return 0;
	}
	if( !getEntity()->hasComponent< CompCollide >() )
	{
		qlog( "CompPhys::getAvgRad() : no collision component found for entity", ERROR, 0 );
		return 0;
	}
	return getEntity()->getHitRad();
}
fixed_t CompPhys::getArea() const
{
	flog( 0 );
	return getAvgRad() * getAvgRad() * PI; // NOTE : area of a circle
}
fixed_t CompPhys::getDensity() const
{
	flog( 0 );
	return _mass / getArea(); // NOTE : density = mass / volume
}

fixed_t CompPhys::getLinearMomentum() const
{
	flog( 0 ); // NOTE : linear momentum = mass * velocity
	if( !hasSisterComps()){ return 0; }
	return _mass * getEntity()->getLinearVel();
}
fixed_t CompPhys::getLinearEnergy() const
{
	flog( 0 ); // NOTE : linear energy = 1/2 * mass * velocity^2
	if( !hasSisterComps()){ return 0; }

	fixed_t vel = getEntity()->getLinearVel();
	return _mass * vel * vel * 0.5f;
}

// ================ FORCE METHODS

vec2_t CompPhys::getGravAccAt( vec2_t pos ) const
{
	flog( 0 ); // NOTE : gravity acceleration = mass * gravity / distance^2
	if( !hasSisterComps() ){ return { 0, 0 }; }

	( void )pos;
	// TODO : replace this with a real gravity calculation
	return { TEMP_VALUE, TEMP_VALUE };
}
vec2_t CompPhys::applyForceTowards( fixed_t force, vec2_t dir )
{
	flog( 0 ); // NOTE : applies a force to the object in a given direction ( acc += force * dir / mass )
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( force == 0 ){ return { 0, 0 }; }
	if( dir.x == 0 && dir.y == 0 )
	{
		qlog( "CompPhys::applyForceFrom() : direction is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	fixed_t mag  = Operate< fixed_t >::sqrt( dir.x * dir.x + dir.y * dir.y );
	fixed_t accX = force * dir.x / ( mag * _mass );
	fixed_t accY = force * dir.y / ( mag * _mass );

	getEntity()->moveAcc({ accX, accY });
	return { accX, accY };
}

vec2_t CompPhys::applyForce( vec2_t force )
{
	flog( 0 ); // NOTE : applies a force to the object ( acc += force / mass )
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( force.x == 0 && force.y == 0 )
	{
		qlog( "CompPhys::applyForce() : force is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	fixed_t accX = force.x / _mass;
	fixed_t accY = force.y / _mass;

	getEntity()->moveAcc({ accX, accY });
	return { accX, accY };
}
vec2_t CompPhys::applyBreakForce( fixed_t breakForce )
{
	flog( 0 ); // NOTE : applies a force in the opposite direction of the velocity ( acc -= breakForce * velocity / mass )
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( breakForce == 0 )
	{
		qlog( "CompPhys::applyBreakForce() : break force is 0", DEBUG, 0 );
		return { 0, 0 };
	}
	vec2_t vel = getEntity()->getVel();
	if( vel.x == 0 && vel.y == 0 )
	{
		qlog( "CompPhys::applyBreakForce() : velocity is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	// TODO : Check if this is correct
	// TODO : handle when the velocity is 0
	// Accelerates by breakForce in the opposite direction of the velocity

	fixed_t mag  = Operate< fixed_t >::sqrt( vel.x * vel.x + vel.y * vel.y );
	fixed_t accX = -breakForce * vel.x / ( mag * _mass );
	fixed_t accY = -breakForce * vel.y / ( mag * _mass );

	getEntity()->moveAcc({ accX, accY });
	return { accX, accY };
}

vec2_t CompPhys::applyBreakFactor( fixed_t breakFactor )
{
	flog( 0 );
	if( !hasSisterComps() ){ return { 0, 0 }; }

	vec2_t acc = getEntity()->getAcc();
	if( acc.x == 0 && acc.y == 0 )
	{
		qlog( "CompPhys::applyBreakFactor() : acceleration is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	fixed_t accX = -breakFactor * acc.x;
	fixed_t accY = -breakFactor * acc.y;

	getEntity()->moveAcc({ accX, accY });
	return { accX, accY };
}


// ================================ TICK METHODS

bool CompPhys::onTick()
{
	flog( 0 );
	if( !canTick() ){ return false; }

	fixed_t dt = GDTS();
	if( dt <= 0 )
	{
		qlog( "CompMove::onTick() : delta time is 0 : skiping this tick", INFO, getEntityID() );
		return false;
	}

	// TODO : apply physics calculations here
	// NOTE : for exemple, gravity, drag, friction, etc

	return true;
}