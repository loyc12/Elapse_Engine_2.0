#include <raylib.h>
#include <sys/types.h>
#include "../../../incs/game.hpp"

// ==================== ENGINE STATE INJECTION FUNCTIONS
// called when the engine changes state

void OnEngineStart()
{
	flog( 0 );

	G_PlayerNtt = GetNttM->getNewEntity(); // NOTE : get the player entity with ID 1

	for ( uint i = 0; i < 1000; ++i )
	{
		GetNttM->addID(); // NOTE : add 1000 IDs to the EntityMngr
	}

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
