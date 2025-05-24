#include <raylib.h>
#include "../../../incs/game.hpp"

// ==================== ENGINE STATE INJECTION FUNCTIONS
// for when the engine changes state

void OnEngineInit()
{ // NOTE : do not add entities here ( or do anything that requires the engine to be started )
	flog( 0 );

	// TODO : add game specific code here

	fend();
}
void OnEngineStart()
{
	flog( 0 );

	// TODO : add game specific code here

	fend();
}
void OnEngineResume()
{
	flog( 0 );

	// TODO : add game specific code here

	fend();
}

void OnEnginePause()
{
	flog( 0 );

	// TODO : add game specific code here

	fend();
}
void OnEngineStop()
{
	flog( 0 );

	// TODO : add game specific code here

	fend();
}
void OnEngineClose()
{
	flog( 0 );

	// TODO : add game specific code here

	fend();
}
