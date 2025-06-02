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
	if( _screenMngr->isClosed() )
	{
		qlog( "launchLoop : ScreenMngr is closed", ERROR, 0 );
		return false;
	}

	// have this run in a separate thread, so this isn't blocking
	{
		qlog( "launchLoop : starting the game loop", DEBUG, 0 );
		OnStartLoop(); // from injectors.hpp

		while( getState() >= ES_STARTED && !WindowShouldClose() ){ runStep(); }

		qlog( "launchLoop : ending the game loop", DEBUG, 0 );
		OnEndLoop(); // from injectors.hpp
	}

	return true;
}

void Engine::runStep()
{
	flog( 0 );
	if( getState() < ES_STARTED ){ qlog( "runStep : Engine not started", ERROR, 0 );  return; }

	qlog( "! starting a new game step !", DEBUG, 0 );

	OnStartStep(); // from injectors.hpp

	_DT = updateDeltaTime();

//_eventMngr->readInputs();

	OnReadInputs(); // from injectors.hpp // TODO : put in EventManager::readInputs()
	{
		GetNttM->tickPhysics(); // NOTE : tick the movement components
	}
	_screenMngr->refresh();

	OnEndStep(); // from injectors.hpp
}
