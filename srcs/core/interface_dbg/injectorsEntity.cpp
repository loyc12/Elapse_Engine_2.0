#include <raylib.h>
#include "../../../incs/game.hpp"

// ===================== ENTITY TICK INJECTION FUNCTIONS
// for when the engine calls an entity's component tick methods

void OnEntityTickMovement( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here

	fend();
}
void OnEntityTickPhysic( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here

	fend();
}
void OnEntityTickCollide( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here

	fend();
}

void OnEntityTickSound( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here

	fend();
}
void OnEntityTickShape( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here

	fend();
}
void OnEntityTickGraphics( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here

	fend();
}

void OnEntityTickScript( Entity *Ntt )
{
	if( Ntt == nullptr ){ return; }
	flog( Ntt->getID() );

	// TODO : add game specific code here

	fend();
}