#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void CompPos::onCpy( const CompPos &rhs )
{
	flog( 0 );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_pos = rhs._pos;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompPos::~CompPos()
{
	flog( 0 );
	onDel();
}

CompPos::CompPos() : CompBase(), _pos({ 0, 0 })
{
	flog( 0 );
	onAdd();
}
CompPos::CompPos( Entity *Ntt, bool isActive, Vector2 pos ) : CompBase( Ntt, isActive ), _pos( pos )
{
	flog( 0 );
	onAdd();
}

CompPos::CompPos( const CompPos &rhs ) : CompBase( rhs )
{
	flog( 0 );
	*this = rhs;
}
CompPos &CompPos::operator=( const CompPos &rhs )
{
	flog( 0 );
	onCpy( rhs );
	return *this;
}