#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void CompCollide::onCpy( const CompCollide &rhs )
{
	flog( 0 );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_hitRad = rhs._hitRad;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompCollide::~CompCollide()
{
	flog( 0 );
}

CompCollide::CompCollide() : CompBase(), _collidable( COMP_DEF_COLLIDE ), _hitRad( COMP_DEF_HITRAD )
{
	flog( 0 );
}
CompCollide::CompCollide( Entity *Ntt, bool isActive, bool isCollidable, float hitRad ):
	CompBase(   Ntt, isActive ),
	_collidable( isCollidable ),
	_hitRad(    hitRad )
{
	flog( 0 );
}

CompCollide::CompCollide( const CompCollide &rhs ) : CompCollide()
{
	flog( 0 );
	*this = rhs;
}
CompCollide &CompCollide::operator=( const CompCollide &rhs )
{
	flog( 0 );
	onCpy( rhs );
	return *this;
}

// ================================ ACCESSORS / MUTATORS

bool CompCollide::hasSisterComps() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompCollide::hasSisterComps() : no entity found for component", ERROR, 0 );
		return false;
	}
	if( !getEntity()->hasComponent< CompPos >() )
	{
		qlog( "CompCollide::hasSisterComps() : no position component found for entity", ERROR, 0 );
		return false;
	}
	if( !getEntity()->hasComponent< CompMove >() )
	{
		qlog( "CompCollide::hasSisterComps() : no movement component found for entity", ERROR, 0 );
		return false;
	}
	if( !getEntity()->hasComponent< CompPhys >() )
	{
		qlog( "CompCollide::hasSisterComps() : no physics component found for entity", ERROR, 0 );
		return false;
	}
	return true;
}

// ================================ TICK METHODS

bool CompCollide::onTick()
{
	flog( 0 );
	if( !canTick() ){ return false; }

	float dt = GDTS();
	if( dt <= 0 )
	{
		qlog( "CompMove::onTick() : delta time is 0 : skiping this tick", INFO, getEntityID() );
		return false;
	}

	// TODO : check for collisions based on other entities' pos, hitrad and statuses
	// TODO : then, call the collision function on this entity only

	return true;
}