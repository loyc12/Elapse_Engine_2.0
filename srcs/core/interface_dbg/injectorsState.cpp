#include <raylib.h>
#include "../../../incs/game.hpp"

// ==================== ENGINE STATE INJECTION FUNCTIONS
// for when the engine changes state

void OnEngineInit()
{ // NOTE : do not add entities here ( or do anything that requires the engine to be started )
	flog( 0 );
	// TODO : add game specific code here
}
void OnEngineStart()
{
	flog( 0 );

	G_PlayerNtt = new Entity();
	{
		G_PlayerNtt->addComponent< CompPos >();
	}

	G_ObjectNtt = new Entity();
	{
		G_ObjectNtt->addComponent< CompPos >();
	}

	G_EnemyNtt = new Entity();
	{
		G_EnemyNtt->addComponent< CompPos >();
	}
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
void OnEngineClose()// NOTE : entities are deleted automatically
{
	flog( 0 );
	// TODO : add game specific code here
}
