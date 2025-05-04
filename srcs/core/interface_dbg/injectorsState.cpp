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
		G_PlayerNtt->getComponent< CompPos >()->setPos( 32, 32 );

		G_PlayerNtt->addComponent< CompMove >();
		G_PlayerNtt->getComponent< CompMove >()->setVel( 3, 4 );

		G_PlayerNtt->addComponent< CompGraph >();
		G_PlayerNtt->getComponent< CompGraph >()->setCircleRadius( 16 );
		G_PlayerNtt->getComponent< CompGraph >()->setCol( BLUE );
	}

	G_ObjectNtt = new Entity();
	{
		G_ObjectNtt->addComponent< CompPos >();
		G_ObjectNtt->getComponent< CompPos >()->setPos( 0, 0 );

		G_ObjectNtt->addComponent< CompGraph >();
		G_ObjectNtt->getComponent< CompGraph >()->setCircleRadius( 32 );
		G_ObjectNtt->getComponent< CompGraph >()->setCol( GRAY );

	}

	G_EnemyNtt = new Entity();
	{
		G_EnemyNtt->addComponent< CompPos >();
		G_EnemyNtt->getComponent< CompPos >()->setPos( -32, -32 );

		G_EnemyNtt->addComponent< CompMove >();
		G_EnemyNtt->getComponent< CompMove >()->setVel( -5, 0 );

		G_EnemyNtt->addComponent< CompGraph >();
		G_EnemyNtt->getComponent< CompGraph >()->setCircleRadius( 16 );
		G_EnemyNtt->getComponent< CompGraph >()->setCol( RED );
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
