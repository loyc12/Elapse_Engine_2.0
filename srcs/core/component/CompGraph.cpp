#include "../../../incs/engine.hpp"
#include <raylib.h>

// ================================ CORE METHODS

void CompGraph::onCpy( const CompGraph &rhs )
{
	flog( 0 );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_col = rhs._col;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompGraph::~CompGraph()
{
	flog( 0 );
}

CompGraph::CompGraph() : CompBase(), _col( COMP_DEF_COLOUR)
{
	flog( 0 );
}
CompGraph::CompGraph( Entity *Ntt, bool isActive, Color col, float cirRad ) : CompBase( Ntt, isActive ), _col( col ), _cirRad( cirRad )

{
	flog( 0 );
}

CompGraph::CompGraph( const CompGraph &rhs ) : CompGraph()
{
	flog( 0 );
	*this = rhs;
}
CompGraph &CompGraph::operator=( const CompGraph &rhs )
{
	flog( 0 );
	onCpy( rhs );
	return *this;
}

// ================================ TICK METHODS

bool CompGraph::onTick()
{
	flog( 0 );
	if( !isActive() ){ return false; }
	if( _cirRad <= 0 ){ return false; }

	DrawCircle(
		_Ntt->getPos().x,
		_Ntt->getPos().y,
		_cirRad,
		_col
	);

	return true;
}