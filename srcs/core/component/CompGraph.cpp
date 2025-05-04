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
	onDel();
}

CompGraph::CompGraph() : CompBase(), _col( DEF_COLOUR)
{
	flog( 0 );
	onAdd();
}
CompGraph::CompGraph( Entity *Ntt, bool isActive, Color col ) : CompBase( Ntt, isActive ), _col( col )
{
	flog( 0 );
	onAdd();
}

CompGraph::CompGraph( const CompGraph &rhs ) : CompBase( rhs )
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

	DrawCircle(
		_Ntt->getPos().x,
		_Ntt->getPos().y,
		_cirleRadius,
		_col
	);

	return true;
}