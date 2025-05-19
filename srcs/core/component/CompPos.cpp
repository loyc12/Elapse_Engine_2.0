#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void CompPos::onCpy( const CompPos &rhs )
{
	flog( 0 );
	if( this == &rhs ){ freturn; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_pos = rhs._pos;

	fend();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompPos::~CompPos()
{
	flog( 0 );
	fend();
}

CompPos::CompPos() : CompBase(), _pos()
{
	flog( 0 );
	fend();
}
CompPos::CompPos( Entity *Ntt, bool isActive, vec2_t pos ):
	CompBase( Ntt, isActive ),
	_pos( pos )
{
	flog( 0 );
	fend();
}

CompPos::CompPos( const CompPos &rhs ) : CompBase( rhs )
{
	flog( 0 );
	*this = rhs;
	fend();
}
CompPos &CompPos::operator=( const CompPos &rhs )
{
	flog( 0 );
	onCpy( rhs );
	freturn *this;
}

// ================================ ACCESSORS / MUTATORS

fixed_t CompPos::getLineDistTo( vec2_t other ) const
{
	flog( 0 );
	freturn getLineDistTo( other.x, other.y );
}
fixed_t CompPos::getLineDistTo( fixed_t x, fixed_t y ) const
{
	flog( 0 );
	freturn sqrt( sqrf( x - _pos.x ) + sqrf( y - _pos.y ));
}

vec2_t CompPos::getVecDistTo( vec2_t other ) const
{
	flog( 0 );
	freturn getVecDistTo( other.x, other.y );
}
vec2_t CompPos::getVecDistTo( fixed_t x, fixed_t y ) const
{
	flog( 0 );
	vec2_t vec;

	vec.x = x - _pos.x;
	vec.y = y - _pos.y;

	freturn vec;
}


// ================================ TICK METHODS
bool CompPos::onTick()
{
	flog( 0 );
	if( !canTick() ){ freturn false; }
	// NOTE : CompPos does not do anything on tick
	freturn true;
}