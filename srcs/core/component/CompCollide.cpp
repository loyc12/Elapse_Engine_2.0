#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void CompCollide::onCpy( const CompCollide &rhs )
{
	flog( 0 );
	if( this == &rhs ){ freturn; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_hitRad = rhs._hitRad;

	fend();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompCollide::~CompCollide()
{
	flog( 0 );
	fend();
}

CompCollide::CompCollide() : CompBase(), _collidable( COMP_DEF_COLLIDE ), _hitRad( COMP_DEF_HITRAD )
{
	flog( 0 );
	fend();
}
CompCollide::CompCollide( Entity *Ntt, bool isActive, bool isCollidable, fixed_t hitRad ):
	CompBase(   Ntt, isActive ),
	_collidable( isCollidable ),
	_hitRad(    hitRad )
{
	flog( 0 );
	fend();
}

CompCollide::CompCollide( const CompCollide &rhs ) : CompCollide()
{
	flog( 0 );
	*this = rhs;
	fend();
}
CompCollide &CompCollide::operator=( const CompCollide &rhs )
{
	flog( 0 );
	onCpy( rhs );
	freturn *this;
}

// ================================ ACCESSORS / MUTATORS

bool CompCollide::hasSisterComps() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompCollide::hasSisterComps() : no entity found for component", ERROR, 0 );
		freturn false;
	}
	if( !getEntity()->hasComponent< CompPos >() )
	{
		qlog( "CompCollide::hasSisterComps() : no position component found for entity", ERROR, 0 );
		freturn false;
	}
	if( !getEntity()->hasComponent< CompMove >() )
	{
		qlog( "CompCollide::hasSisterComps() : no movement component found for entity", ERROR, 0 );
		freturn false;
	}
	if( !getEntity()->hasComponent< CompPhys >() )
	{
		qlog( "CompCollide::hasSisterComps() : no physics component found for entity", ERROR, 0 );
		freturn false;
	}
	freturn true;
}

// ================ OVERLAP METHODS

bool CompCollide::isOverPos( vec2_t pos, fixed_t otherRad ) const
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn false; }
	if( pos == NULL_POS ){   freturn false; }

	freturn ( getEntity()->getLineDistTo( pos ) < _hitRad + otherRad );
}
bool CompCollide::isOverlaping( CompCollide *other ) const
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn false; }
	if( other == this ){     freturn false; }
	if( other == nullptr ){  freturn false; }

	freturn ( isOverPos( other->getEntity()->getPos(), other->getHitRad() ));
}
fixed_t CompCollide::getOverlap( CompCollide *other ) const
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn NULL_POS; }
	if( other == this ){     freturn NULL_POS; }
	if( other == nullptr ){  freturn NULL_POS; }

	fixed_t gap = getEntity()->getLineDistTo( other->getEntity()->getPos() );
	gap -= ( _hitRad + other->getHitRad() ); // NOTE : gap is negative if the two components are overlapping

	freturn ( Opfx::max( -gap, 0 ));
}

// ================ COLLISION METHODS

bool CompCollide::canCollide( CompCollide *other ) const
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn false; }
	if( other == this ){     freturn false; }
	if( other == nullptr ){  freturn false; }

	freturn ( _collidable && other->isCollidable() );
}
bool CompCollide::isColliding( CompCollide *other ) const
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn false; }
	if( other == this ){     freturn false; }
	if( other == nullptr ){  freturn false; }

	freturn ( canCollide( other ) && isOverlaping( other ));
}

vec2_t CompCollide::getCollideVec( CompCollide *other ) const
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn NULL_POS; }
	if( other == this ){     freturn NULL_POS; }
	if( other == nullptr ){  freturn NULL_POS; }

	vec2_t vec = getEntity()->getVecDistTo( other->getEntity()->getPos() );
	vec.normalize() *= -( getOverlap( other ));

	// NOTE : this is the movement this entity should do to get out of the overlap
	freturn vec;
}
vec2_t CompCollide::collideWith( CompCollide *other )
{
	flog( 0 );
	if( !hasSisterComps() ){ freturn NULL_POS; }
	if( other == this ){     freturn NULL_POS; }
	if( other == nullptr ){  freturn NULL_POS; }

	vec2_t vec = getCollideVec( other );

	if ( vec == NULL_POS )
	{
		qlog( "CompCollide::collideWith() : no collision vector found", ERROR, getEntityID() );
		freturn NULL_POS;
	}

	// TODO : rework this to use velocity and physic stuff
	getEntity()->movePos( vec * 0.5 ); // forces the entity to move out of the overlap region, assuming the other entity will do half the moving too
	freturn vec;
}

// ================================ TICK METHODS

bool CompCollide::onTick()
{
	flog( 0 );
	if( !canTick() ){ freturn false; }

	fixed_t dt = GDTS();
	if( dt <= 0 )
	{
		qlog( "CompMove::onTick() : delta time is 0 : skiping this tick", INFO, getEntityID() );
		freturn false;
	}

	// TODO : check for collisions based on other entities' pos, hitrad and statuses
	// TODO : then, call the collision function on this entity only

	freturn true;
}