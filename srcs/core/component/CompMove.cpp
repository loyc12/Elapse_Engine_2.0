#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void CompMove::onCpy( const CompMove &rhs )
{
	flog( 0 );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_vel = rhs._vel;
	_acc = rhs._acc;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompMove::~CompMove()
{
	flog( 0 );
	onDel();
}

CompMove::CompMove() : CompBase(), _vel({ 0, 0 }), _acc({ 0, 0 })
{
	flog( 0 );
	onAdd();
}
CompMove::CompMove( Entity *Ntt, bool isActive, Vector2 vel, Vector2 acc ) : CompBase( Ntt, isActive ), _vel( vel ), _acc( acc ){
	flog( 0 );
	onAdd();
}

CompMove::CompMove( const CompMove &rhs ) : CompBase( rhs )
{
	flog( 0 );
	*this = rhs;
}
CompMove &CompMove::operator=( const CompMove &rhs )
{
	flog( 0 );
	onCpy( rhs );
	return *this;
}

// ================================ TICK METHODS

bool CompMove::onTick()
{
	flog( 0 );
	if( !isActive() ){ return false; }

	float dt = GDTS();
	if( dt == 0 )
	{
		qlog( "CompMove::onTick() : dt is 0", DEBUG, 0 );
		return false;
	}
	_vel.x += _acc.x * dt;
	_vel.y += _acc.y * dt;

	 // NOTE : reset acceleration after applying it, meaning it needs to be reset every tick for continual acceleration
	_acc.x = 0;
	_acc.y = 0;

	if( !hasEntity() )
	{
		qlog( "CompMove::onTick() : no entity found for component", ERROR, 0 );
		return false;
	}
	CompPos *cmp = _Ntt->getComponent< CompPos >();

	if( cmp == nullptr )
	{
		qlog( "CompMove::onTick() : no CompPos found for this entity", WARN, getEntityID() );
		return false;
	}
	cmp->changePos( _vel.x * dt, _vel.y * dt ); // NOTE : move this logic to physic component
	return true;
}