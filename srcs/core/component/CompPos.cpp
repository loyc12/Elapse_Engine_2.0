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
// ================== DISTANCE METHODS
fixed_t CompPos::getLineDistTo( id_t id ) const
{
	flog( 0 );
	if( id == 0 )
	{
		qlog( "CompPos::getLineDistTo() : id is 0", WARN, 0 );
		freturn 0;
	}
	freturn getLineDistTo( GetNttM->getEntity( id ) );
}
fixed_t CompPos::getLineDistTo( Entity *other ) const
{
	flog( 0 );
	if( other == nullptr )
	{
		qlog( "CompPos::getLineDistTo() : other is nullptr", WARN, 0 );
		freturn 0;
	}
	freturn getLineDistTo( other->getComponent< CompPos >() );
}
fixed_t CompPos::getLineDistTo( CompPos *other ) const
{
	flog( 0 );
	if( other == nullptr )
	{
		qlog( "CompPos::getLineDistTo() : other is nullptr", WARN, 0 );
		freturn 0;
	}
	freturn getLineDistTo( other->getPos() );
}
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


// ================================ TICK METHODS
bool CompPos::onTick()
{
	flog( 0 );
	if( !canTick() ){ freturn false; }
	// NOTE : CompPos does not do anything on tick
	freturn true;
}