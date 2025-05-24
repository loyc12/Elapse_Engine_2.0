#include <raylib.h>
#include "../../../incs/core.hpp"

// ================================ STEP METHODS

bool Engine::launchLoop()
{
	flog( 0 );
	if( getState() < ES_STARTED )
	{
		qlog( "launchLoop : Engine not yet started", ERROR, 0 );
		fend(); return false;
	}

	OnStartLoop(); // from injectors.hpp

	while( getState() >= ES_STARTED && !WindowShouldClose() ){ runStep(); } // TODO : Multithread this

	OnEndLoop(); // from injectors.hpp

	fend(); return true;
}

void Engine::runStep()
{
	flog( 0 );
	if( getState() < ES_STARTED ){ qlog( "runStep : Engine not started", ERROR, 0 ); fend(); return; }

	OnStartStep(); // from injectors.hpp

	_DT = updateDeltaTime();

	// TODO : implement game loop logic here

	refreshScreen();

	OnEndStep(); // from injectors.hpp

	fend();
}

void Engine::refreshScreen() // TODO : move me to ScreenMngr
{
	flog( 0 );

	BeginDrawing();
	{
		_screenMngr2D->refresh();

		OnRenderBackground(); // from injectors.hpp
		BeginMode2D( *_screenMngr2D->getCamera() );
		{
			//_entityMngr->tickGraphics();
			OnRenderWorld(); // from injectors.hpp
		}
		EndMode2D();
		OnRenderUI(); // from injectors.hpp
	}
	EndDrawing();

	fend();
}