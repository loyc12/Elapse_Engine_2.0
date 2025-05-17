#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void CompMove::onCpy( const CompMove &rhs )
{
	flog( 0 );
	if( this == &rhs ){ freturn; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_vel = rhs._vel;
	_acc = rhs._acc;

	fend();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompMove::~CompMove()
{
	flog( 0 );
	fend();
}

CompMove::CompMove() : CompBase(), _vel(), _acc()
{
	flog( 0 );
	fend();
}
CompMove::CompMove( Entity *Ntt, bool isActive, vec2_t vel, vec2_t acc ):
	CompBase( Ntt, isActive ),
	_vel( vel ),
	_acc( acc )
{
	flog( 0 );
	fend();
}

CompMove::CompMove( const CompMove &rhs ) : CompMove()
{
	flog( 0 );
	*this = rhs;
	fend();
}
CompMove &CompMove::operator=( const CompMove &rhs )
{
	flog( 0 );
	onCpy( rhs );
	freturn *this;
}

// ================================ ACCESSORS / MUTATORS

bool CompMove::hasSisterComps() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompMove::hasSisterComps() : no entity found for component", WARN, 0 );
		freturn false;
	}
	if( !getEntity()->hasComponent< CompPos >() )
	{
		qlog( "CompMove::hasSisterComps() : no position component found for entity", INFO, 0 );
		freturn false;
	}
	freturn true;
}

// ================================ TICK METHODS

bool CompMove::onTick()
{
	flog( 0 );
	if( !canTick() ){ freturn false; }

	fixed_t dt = GDTS();
	if( dt <= 0 )
	{
		qlog( "CompMove::onTick() : delta time is 0 : skiping this tick", INFO, getEntityID() );
		freturn false;
	}

	// NOTE : apply acceleration to velocity
	_vel.x  += _acc.x * dt;
	_vel.y  += _acc.y * dt;
	_rotVel += _rotAcc * dt;

	 // NOTE : reseting acceleration after applying it, meaning it needs to be reset every tick for continual acceleration
	_acc = COMP_DEF_ACC;
	_rotAcc = 0;

	CompPos *cmp = _Ntt->getComponent< CompPos >();
	if( cmp == nullptr )
	{
		qlog( "CompCollide::onTick() : no CompPos found for this entity", WARN, getEntityID() );
		freturn false;
	}

	// TODO : move this logic to physic component
	cmp->movePos( _vel.x * dt, _vel.y * dt );
	cmp->moveAngle( _rotVel * dt );

	freturn true;
}