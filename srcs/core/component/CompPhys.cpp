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

CompPhys::CompPhys( Entity *Ntt, bool isActive, bool isDynamic, float mass, float drag, float fric, float elas ) : CompBase( Ntt, isActive ),
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

Vector2 CompPhys::applyDrag()
{
	flog( 0 );
	if( !hasSisterComps() ){ return { 0, 0 }; }
	Vector2 dAcc = {
		-_drag * getEntity()->getVel().x / _mass,
		-_drag * getEntity()->getVel().y / _mass
	};
	getEntity()->changeAcc( dAcc );
	return dAcc;
}
Vector2 CompPhys::applyFriction( Vector2 surfaceNormal )
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
Vector2 CompPhys::applyBounce( Vector2 surfaceNormal )
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

float CompPhys::getAvgRad() const
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
float CompPhys::getArea() const
{
	flog( 0 );
	return getAvgRad() * getAvgRad() * PI; // NOTE : area of a circle
}
float CompPhys::getDensity() const
{
	flog( 0 );
	return _mass / getArea(); // NOTE : density = mass / volume
}

float CompPhys::getLinearMomentum() const
{
	flog( 0 ); // NOTE : linear momentum = mass * velocity
	if( !hasSisterComps()){ return 0; }
	return _mass * getEntity()->getLinearVel();
}
float CompPhys::getLinearEnergy() const
{
	flog( 0 ); // NOTE : linear energy = 1/2 * mass * velocity^2
	if( !hasSisterComps()){ return 0; }

	float vel = getEntity()->getLinearVel();
	return 0.5f * _mass * vel * vel;
}

// ================ FORCE METHODS

Vector2 CompPhys::getGravAccAt( Vector2 pos ) const
{
	flog( 0 ); // NOTE : gravity acceleration = mass * gravity / distance^2
	if( !hasSisterComps() ){ return { 0, 0 }; }

	( void )pos;
	// TODO : replace this with a real gravity calculation
	return { TEMP_VALUE, TEMP_VALUE };
}
Vector2 CompPhys::applyForceTowards( float force, Vector2 dir )
{
	flog( 0 ); // NOTE : applies a force to the object in a given direction ( acc += force * dir / mass )
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( force == 0 ){ return { 0, 0 }; }
	if( dir.x == 0 && dir.y == 0 )
	{
		qlog( "CompPhys::applyForceFrom() : direction is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	float mag  = sqrt( dir.x * dir.x + dir.y * dir.y );
	float accX = force * dir.x / ( mag * _mass );
	float accY = force * dir.y / ( mag * _mass );

	getEntity()->changeAcc({ accX, accY });
	return { accX, accY };
}

Vector2 CompPhys::applyForce( Vector2 force )
{
	flog( 0 ); // NOTE : applies a force to the object ( acc += force / mass )
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( force.x == 0 && force.y == 0 )
	{
		qlog( "CompPhys::applyForce() : force is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	float accX = force.x / _mass;
	float accY = force.y / _mass;

	getEntity()->changeAcc({ accX, accY });
	return { accX, accY };
}
Vector2 CompPhys::applyBreakForce( float breakForce )
{
	flog( 0 ); // NOTE : applies a force in the opposite direction of the velocity ( acc -= breakForce * velocity / mass )
	if( !hasSisterComps() ){ return { 0, 0 }; }
	if( breakForce == 0 )
	{
		qlog( "CompPhys::applyBreakForce() : break force is 0", DEBUG, 0 );
		return { 0, 0 };
	}
	Vector2 vel = getEntity()->getVel();
	if( vel.x == 0 && vel.y == 0 )
	{
		qlog( "CompPhys::applyBreakForce() : velocity is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	float mag = sqrt(  vel.x * vel.x + vel.y * vel.y );
	float accX = -breakForce * vel.x / ( mag * _mass );
	float accY = -breakForce * vel.y / ( mag * _mass );

	getEntity()->changeAcc({ accX, accY });
	return { accX, accY };
}

Vector2 CompPhys::applyBreakFactor( float breakFactor )
{
	flog( 0 ); // NOTE : multiplies the acceleration by a given factor ( acc *= breakFactor )
	if( !hasSisterComps() ){ return { 0, 0 }; }

	Vector2 acc = getEntity()->getAcc();
	if( acc.x == 0 && acc.y == 0 )
	{
		qlog( "CompPhys::applyBreakFactor() : acceleration is 0", DEBUG, 0 );
		return { 0, 0 };
	}

	float accX = -breakFactor * acc.x;
	float accY = -breakFactor * acc.y;

	getEntity()->changeAcc({ accX, accY });
	return { accX, accY };
}


// ================================ TICK METHODS

bool CompPhys::onTick()
{
	flog( 0 );
	if( !canTick() ){ return false; }

	float dt = GDTS();
	if( dt <= 0 )
	{
		qlog( "CompMove::onTick() : delta time is 0 : skiping this tick", INFO, getEntityID() );
		return false;
	}

	// TODO : apply physics calculations here
	// NOTE : for exemple, gravity, drag, friction, etc

	return true;
}