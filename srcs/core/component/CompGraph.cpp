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

CompGraph::CompGraph() : CompBase(), _col( COMP_DEF_COLOUR), _cirRad( COMP_DEF_CIRRAD )
{
	flog( 0 );
}
CompGraph::CompGraph( Entity *Ntt, bool isActive, Color col, float cirRad ):
	CompBase( Ntt, isActive ),
	_col( col ),
	_cirRad( cirRad )
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

// ================================ ACCESSORS / MUTATORS

bool CompGraph::hasSisterComps() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompGraph::hasSisterComps() : no entity found for component", ERROR, 0 );
		return false;
	}
	if( !getEntity()->hasComponent< CompPos  >() )
	{
		qlog( "CompGraph::hasSisterComps() : no position component found for entity", ERROR, 0 );
		return false;
	}
	return true;
}

// ================================ TICK METHODS

bool CompGraph::onTick()
{
	flog( 0 );
	if( !canTick() ){ return false; }
	if( _cirRad == 0 )
	{
		qlog( "CompGraph::onTick() : cannot draw a circle of radius 0", ERROR, getEntityID() );
		return false;
	}

	DrawCircle(
		_Ntt->getPos().x,
		_Ntt->getPos().y,
		_cirRad,
		_col
	);

	return true;
}