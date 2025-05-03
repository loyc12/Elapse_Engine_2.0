#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ STEP METHODS


bool Engine::launchLoop()
{
	flog( 0 );
	if ( getState() < ES_STARTED )
	{
		qlog( "launchLoop : Engine not yet started", ERROR, 0 );
		return false;
	}

	//OnGameLaunch(); // from game.hpp
	while ( getState() >= ES_STARTED && !WindowShouldClose() )
	{
		runStep(); // TODO : Multithread this shit
	}

	return true;
}

void Engine::runStep()
{
	flog( 0 );
	if ( getState() < ES_STARTED ){ qlog( "runStep : Engine not started", ERROR, 0 ); return; }

	_DT = GetFrameTime();

	_controller->refreshInputs();

	//runScripts();

	//if ( getState() >= ES_RUNNING ){ runPhysics(); } // Only runs the physics call if the enguine is unpaused

	refreshScreen();

	//OnGameStep(); // from game.hpp
}

void Engine::readInputs()
{
	flog( 0 );
	_controller->refreshInputs();
}



void Engine::renderWorld()
{
	flog( 0 );

	BeginMode2D( *_viewport2D->getCamera() );

	// TODO : update the render components here

	//OnRenderWorld(); // from game.hpp

	EndMode2D();
}

void Engine::renderUIs()
{
	flog( 0 );
	//OnRenderUI(); // from game.hpp
}

void Engine::refreshScreen()
{
	flog( 0 );

	BeginDrawing();
	_viewport2D->refresh();

	renderWorld();
	renderUIs();

	EndDrawing();
}