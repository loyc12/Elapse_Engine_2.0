#include <raylib.h>
#include <sys/types.h>
#include "../../../incs/game.hpp"

// ==================== ENGINE STATE INJECTION FUNCTIONS
// called when the engine changes state

void OnEngineStart()
{
	flog( 0 );

	G_PlayerNtt = GetNttM->getNewEntity(); // NOTE : get the player entity with ID 1

	G_PlayerNtt->initComp( CT_TRANSFORM ); // NOTE : initialize the transform component
	G_PlayerNtt->initComp( CT_MOVEMENT );  // NOTE : initialize the movement component
	G_PlayerNtt->initComp( CT_SHAPE );     // NOTE : initialize the shape component

	// TODO : add game specific code here
}

void OnEngineResume()
{
	flog( 0 );

	// TODO : add game specific code here
}

void OnEnginePause()
{
	flog( 0 );

	// TODO : add game specific code here
}

void OnEngineStop()
{
	flog( 0 );

	delete G_PlayerNtt; // NOTE : delete the player entity

	// TODO : add game specific code here
}
