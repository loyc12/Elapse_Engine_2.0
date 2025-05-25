#include <raylib.h>
#include "../../../incs/game.hpp"

// ==================== ENGINE STATE INJECTION FUNCTIONS
// called when the engine changes state

void OnEngineInit()
{ // NOTE : do not add entities here ( or do anything that requires the engine to be started )
	flog( 0 );

	// TODO : add game specific code here
}
void OnEngineStart()
{
	flog( 0 );

	G_PlayerNtt = GetNttM->getNewEntity(); // NOTE : get the player entity with ID 1

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

	// TODO : add game specific code here
}
void OnEngineClose()
{
	flog( 0 );

	// TODO : add game specific code here
}
