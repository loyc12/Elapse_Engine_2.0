#include <raylib.h>
#include "../../../incs/core.hpp"

// ================================ STEP METHODS

bool Engine::launchLoop()
{
	flog( 0 );
	if( getState() < ES_STARTED )
	{
		qlog( "launchLoop : Engine not yet started", ERROR, 0 );
		return false;
	}
	qlog( "launchLoop : starting the game loop", DEBUG, 0 );
	OnStartLoop(); // from injectors.hpp

	while( getState() >= ES_STARTED && !WindowShouldClose() ){ runStep(); } // TODO : Multithread this

	qlog( "launchLoop : ending the game loop", DEBUG, 0 );
	OnEndLoop(); // from injectors.hpp

	return true;
}

void Engine::runStep()
{
	flog( 0 );
	if( getState() < ES_STARTED ){ qlog( "runStep : Engine not started", ERROR, 0 );  return; }

	qlog( "! starting a game step !", DEBUG, 0 );

	OnStartStep(); // from injectors.hpp

	_DT = updateDeltaTime();

	// TODO : implement game loop logic here

	_screenMngr->refresh();

	OnEndStep(); // from injectors.hpp
}
