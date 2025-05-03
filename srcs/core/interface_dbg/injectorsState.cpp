# include <raylib.h>
# include "../../../incs/engine.hpp"

// ==================== ENGINE STATE INJECTION FUNCTIONS
// for when the engine changes state

void OnEngineInit()
{ // NOTE : do not instanciate objects here ( or do anything that requires the engine to be started )
	flog( 0 );
	// TODO : add game specific code here
}
void OnEngineStart()
{ // NOTE : instanciate objects or load files from here on out
	flog( 0 );
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
void OnEngineClose() // The engine takes care to delete all objects
{
	flog( 0 );
	// TODO : add game specific code here
}
