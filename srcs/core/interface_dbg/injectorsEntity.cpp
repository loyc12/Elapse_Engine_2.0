#include <raylib.h>
#include "../../../incs/game.hpp"

// ===================== ENTITY TICK INJECTION FUNCTIONS
// for when the engine calls an entity's component tick methods

void OnEntityTickScript( Entity *Ntt )
{
	flog( Ntt->getID() );
	if ( Ntt == nullptr ){ return; }

	// TODO : add game specific code here
}

void OnEntityTickPhysic( Entity *Ntt )
{
	flog( Ntt->getID() );
	if ( Ntt == nullptr ){ return; }

	// TODO : add game specific code here
}

void OnEntityTickCollide( Entity *Ntt )
{
	flog( Ntt->getID() );
	if ( Ntt == nullptr ){ return; }

	// TODO : add game specific code here
}

void OnEntityTickMovement( Entity *Ntt )
{
	flog( Ntt->getID() );
	if ( Ntt == nullptr ){ return; }

	// TODO : add game specific code here
}

void OnEntityTickVisual( Entity *Ntt )
{
	flog( Ntt->getID() );
	if ( Ntt == nullptr ){ return; }

	// TODO : add game specific code here
}