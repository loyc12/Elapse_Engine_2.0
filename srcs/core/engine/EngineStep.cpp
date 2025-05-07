#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ STEP METHODS

bool Engine::launchLoop()
{
	flog( 0 );
	if( getState() < ES_STARTED )
	{
		qlog( "launchLoop : Engine not yet started", ERROR, 0 );
		return false;
	}

	OnStartLoop(); // from injectors.hpp

	while( getState() >= ES_STARTED && !WindowShouldClose() ){ runStep(); } // TODO : Multithread this

	OnEndLoop(); // from injectors.hpp

	return true;
}

void Engine::runStep()
{
	flog( 0 );
	if( getState() < ES_STARTED ){ qlog( "runStep : Engine not started", ERROR, 0 ); return; }

	OnStartStep(); // from injectors.hpp

	_DT = updateDeltaTime();

	_controller->refreshInputs();

	_compManager->tickScripts();
	_compManager->tickPhysics();
	_compManager->tickCollides();
	_compManager->tickMovements();

	// NOTE : tickVisuals() is called in refreshScreen()
	refreshScreen();

	OnEndStep(); // from injectors.hpp
}

void Engine::refreshScreen()
{
	flog( 0 );

	BeginDrawing();
	{
		_viewport2D->refresh();

		OnRenderBackground(); // from injectors.hpp
		BeginMode2D( *_viewport2D->getCamera() );
		{
			_compManager->tickGraphics();
			OnRenderWorld(); // from injectors.hpp
		}
		EndMode2D();
		OnRenderUI(); // from injectors.hpp
	}
	EndDrawing();
}