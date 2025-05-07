#include <raylib.h>
#include "../../../incs/game.hpp"

// ===================== ENTITY TICK INJECTION FUNCTIONS
// for when the engine calls an entity's component tick methods

void OnEntityTickMovement( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here
}
void OnEntityTickPhysic( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here
}
void OnEntityTickCollide( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here
}

void OnEntityTickSound( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here
}
void OnEntityTickShape( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here
}
void OnEntityTickGraphics( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here
}

void OnEntityTickScript( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here
}