#include "../../../incs/engine.hpp"
#include <raylib.h>

// ================================ CORE METHODS

void CompPhys::onCpy( const CompPhys &rhs )
{
	flog( 0 );
	if( this == &rhs ){ freturn; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_dynamic = rhs._dynamic;

	_mass = rhs._mass;
	_drag = rhs._drag;
	_fric = rhs._fric;
	_elas = rhs._elas;

	fend();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompPhys::~CompPhys()
{
	flog( 0 );
	fend();
}

CompPhys::CompPhys() : CompBase(),
	_dynamic( COMP_DEF_DYNAMIC ),

	_mass( COMP_MIN_MASS ),
	_drag( COMP_MIN_DRAG ),
	_fric( COMP_MIN_FRIC ),
	_elas( COMP_MIN_ELAS )
{
	flog( 0 );
	fend();
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
	fend();
}

CompPhys::CompPhys( const CompPhys &rhs ) : CompPhys()
{
	flog( 0 );
	*this = rhs;
	fend();
}
CompPhys &CompPhys::operator=( const CompPhys &rhs )
{
	flog( 0 );
	onCpy( rhs );
	freturn *this;
}

// ================================ ACCESSORS / MUTATORS

bool CompPhys::hasSisterComps() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompPhys::hasSisterComps() : no entity found for component", WARN, 0 );
		freturn false;
	}
	if( !getEntity()->hasComponent< CompPos >() )
	{
		qlog( "CompPhys::hasSisterComps() : no position component found for entity", INFO, 0 );
		freturn false;
	}
	if( !getEntity()->hasComponent< CompMove >() )
	{
		qlog( "CompPhys::hasSisterComps() : no movement component found for entity", INFO, 0 );
		freturn false;
	}
	freturn true;
}

vec2_t CompPhys::applyDrag()
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn vec2_t(); }
	vec2_t dAcc = {
		-_drag * getEntity()->getVel().x / _mass,
		-_drag * getEntity()->getVel().y / _mass
	};
	getEntity()->moveAcc( dAcc );
	freturn dAcc;
}
vec2_t CompPhys::applyFriction( vec2_t surfaceNormal )
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn vec2_t(); }
	if( surfaceNormal == 0 )
	{
		qlog( "CompPhys::applyFriction() : surface normal is 0", DEBUG, 0 );
		freturn vec2_t();
	}

	( void )surfaceNormal;

	// TODO : replace this with a real friction calculation

	freturn { TEMP_VALUE, TEMP_VALUE };
}
vec2_t CompPhys::applyBounce( vec2_t surfaceNormal )
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn vec2_t(); }
	if( surfaceNormal == 0 )
	{
		qlog( "CompPhys::applyBounce() : surface normal is 0", DEBUG, 0 );
		freturn vec2_t();
	}

	( void )surfaceNormal;

	// TODO : replace this with a real bounce calculation

	freturn { TEMP_VALUE, TEMP_VALUE };
}

// ================ CALCULATED PROPERTIES METHODS

fixed_t CompPhys::getAvgRad() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompPhys::getAvgRad() : no entity found for component", ERROR, 0 );
		freturn 0;
	}
	if( !getEntity()->hasComponent< CompCollide >() )
	{
		qlog( "CompPhys::getAvgRad() : no collision component found for entity", ERROR, 0 );
		freturn 0;
	}
	freturn getEntity()->getHitRad();
}
fixed_t CompPhys::getArea() const
{
	flog( 0 );
	freturn getAvgRad() * getAvgRad() * PI; // NOTE : area of a circle
}
fixed_t CompPhys::getDensity() const
{
	flog( 0 );
	freturn _mass / getArea(); // NOTE : density = mass / volume
}

fixed_t CompPhys::getLinearMomentum() const
{
	flog( 0 ); // NOTE : linear momentum = mass * velocity
	if( !hasSisterComps()){ freturn 0; }
	freturn _mass * getEntity()->getLinearVel();
}
fixed_t CompPhys::getLinearEnergy() const
{
	flog( 0 ); // NOTE : linear energy = 1/2 * mass * velocity^2
	if( !hasSisterComps()){ freturn 0; }

	fixed_t vel = getEntity()->getLinearVel();
	freturn _mass * vel * vel * 0.5f;
}

// ================ FORCE METHODS

vec2_t CompPhys::getGravAccAt( vec2_t pos ) const
{
	flog( 0 ); // NOTE : gravity acceleration = mass * gravity / distance^2
	if( !hasSisterComps() ){ freturn vec2_t(); }

	( void )pos;

	// TODO : replace this with a real gravity calculation

	freturn { TEMP_VALUE, TEMP_VALUE };
}

vec2_t CompPhys::applyForceTowards( fixed_t force, vec2_t dir )
{
	flog( 0 ); // NOTE : applies a force to the object in a given direction ( acc += force * dir / mass )
	if( !hasSisterComps() ){ freturn vec2_t(); }
	if( force == 0 ){ freturn vec2_t(); }
	if( dir == 0 )
	{
		qlog( "CompPhys::applyForceFrom() : direction is 0", DEBUG, 0 );
		freturn vec2_t();
	}
	dir.normalize();

	fixed_t mag  = Opfx::sqrt( dir.x * dir.x + dir.y * dir.y );
	fixed_t ax = force * dir.x / ( mag * _mass );
	fixed_t ay = force * dir.y / ( mag * _mass );

	getEntity()->moveAcc({ ax, ay });
	freturn { ax, ay };
}

vec2_t CompPhys::applyForce( vec2_t force )
{
	flog( 0 ); // NOTE : applies a force to the object ( acc += force / mass )
	if( !hasSisterComps() ){ freturn vec2_t(); }
	if( force == 0 )
	{
		qlog( "CompPhys::applyForce() : force is 0", DEBUG, 0 );
		freturn vec2_t();
	}

	fixed_t ax = force.x / _mass;
	fixed_t ay = force.y / _mass;

	getEntity()->moveAcc({ ax, ay });
	freturn { ax, ay };
}

vec2_t CompPhys::applyBreakForce( fixed_t breakForce )
{
	flog( 0 ); // NOTE : applies a force in the opposite direction of the velocity ( acc -= breakForce * velocity / mass )
	if( !hasSisterComps() ){ freturn vec2_t(); }
	if( breakForce == 0 )
	{
		qlog( "CompPhys::applyBreakForce() : break force is 0 : skipping maths", DEBUG, 0 );
		freturn vec2_t();
	}
	if( breakForce < 0 )
	{
		qlog( "CompPhys::applyBreakForce() : break force is negative", WARN, 0 );
		breakForce = o_abs( breakForce );
	}

	vec2_t vel = getEntity()->getVel();
	if( vel == 0 )
	{
		qlog( "CompPhys::applyBreakForce() : velocity is 0 : skipping maths", DEBUG, 0 );
		freturn vec2_t();
	}

	// TODO : Check if this is correct
	// Accelerates by breakForce in the opposite direction of the velocity

	fixed_t mag  = Opfx::sqrt( vel.x * vel.x + vel.y * vel.y );
	fixed_t ax = -breakForce * vel.x / ( mag * _mass );
	fixed_t ay = -breakForce * vel.y / ( mag * _mass );

	getEntity()->moveAcc({ ax, ay });
	freturn { ax, ay };
}

vec2_t CompPhys::applyBreakFactor( fixed_t breakFactor )
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn vec2_t(); }

	if( breakFactor == 0 )
	{
		qlog( "CompPhys::applyBreakFactor() : break factor is 0 : skipping maths", DEBUG, 0 );
		freturn vec2_t();
	}
	if( breakFactor < 0 || breakFactor > 1 )
	{
		qlog( "CompPhys::applyBreakFactor() : break factor is not between 0 and 1", WARN, 0 );
		breakFactor = o_clmp( o_abs( breakFactor ), fixed_t( 0 ), fixed_t( 1 ));
	}

	vec2_t vel = getEntity()->getVel();
	if( vel == 0 )
	{
		qlog( "CompPhys::applyBreakFactor() : velocity is 0 : skipping maths", DEBUG, 0 );
		freturn vec2_t();
	}

	fixed_t ax = -breakFactor * vel.x;
	fixed_t ay = -breakFactor * vel.y;

	getEntity()->moveAcc({ ax, ay });
	freturn { ax, ay };
}


// ================================ TICK METHODS

bool CompPhys::onTick()
{
	flog( 0 );
	if( !canTick() ){ freturn false; }

	fixed_t dt = GDTS();
	if( dt <= 0 )
	{
		qlog( "CompMove::onTick() : delta time is 0 : skiping this tick", INFO, getEntityID() );
		freturn false;
	}

	// TODO : apply physics calculations here
	// NOTE : for exemple, gravity, drag, friction, etc

	freturn true;
}