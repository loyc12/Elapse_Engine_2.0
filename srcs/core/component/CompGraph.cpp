#include "../../../incs/engine.hpp"
#include <raylib.h>

// ================================ CORE METHODS

void CompGraph::onCpy( const CompGraph &rhs )
{
	flog( 0 );
	if( this == &rhs ){ freturn; } // NOTE : checks if the objects are the same

	CompBase::onCpy( rhs );
	_col = rhs._col;

	fend();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompGraph::~CompGraph()
{
	flog( 0 );
	fend();
}

CompGraph::CompGraph() : CompBase(), _col( COMP_DEF_COLOUR), _cirRad( COMP_DEF_CIRRAD )
{
	flog( 0 );
	fend();
}
CompGraph::CompGraph( Entity *Ntt, bool isActive, Color col, fixed_t cirRad ):
	CompBase( Ntt, isActive ),
	_col( col ), _cirRad( cirRad )
{
	flog( 0 );
	fend();
}

CompGraph::CompGraph( const CompGraph &rhs ) : CompGraph()
{
	flog( 0 );
	*this = rhs;
	fend();
}
CompGraph &CompGraph::operator=( const CompGraph &rhs )
{
	flog( 0 );
	onCpy( rhs );
	freturn *this;
}

// ================================ ACCESSORS / MUTATORS

bool CompGraph::hasSisterComps() const
{
	flog( 0 );
	if( !hasEntity() )
	{
		qlog( "CompGraph::hasSisterComps() : no entity found for component", ERROR, 0 );
		freturn false;
	}
	if( !getEntity()->hasComponent< CompPos  >() )
	{
		qlog( "CompGraph::hasSisterComps() : no position component found for entity", ERROR, 0 );
		freturn false;
	}
	freturn true;
}

// ================================ TICK METHODS

bool CompGraph::onTick()
{
	flog( 0 );
	if( !canTick() ){ freturn false; }
	if( _cirRad == 0 )
	{
		qlog( "CompGraph::onTick() : cannot draw a circle of radius 0", ERROR, getEntityID() );
		freturn false;
	}

	GetScrnM->putCirc( getEntity()->getPos(), _cirRad, _col );

	freturn true;
}