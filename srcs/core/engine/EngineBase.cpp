#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : _DT( 0.0f ), _TS( 1.0f ), _state( ES_CLOSED )
{
	flog( 0 );
	if( getState() < ES_CLOSING ){ switchState( ES_INITIALIZED ); }
	fend();
}

Engine::~Engine()
{
	flog( 0 );
	if( getState() > ES_CLOSED ){ switchState( ES_CLOSING ); }
	fend();
}

Engine *Engine::getEngine() // NOTE : static class method ( singleton )
{
	flog( 0 );
	static Engine *instance = new Engine();
	freturn instance;
}

// ================================ ACCESSORS / MUTATORS

fixed_t  Engine::setTimeScale( fixed_t timeScale )
{
	flog( 0 );
	if( timeScale < 0 )
	{
		qlog( "setTimeScale : Time scale cannot be negative", WARN, 0 );
		_TS = 0;
	}
	else { _TS = timeScale; }

	freturn _TS;
}

bool Engine::canEngineTick()
{
	flog( 0 );
	if( getState() < ES_STARTED )
	{
		qlog( "canEngineTick : Engine needs to at least be started", WARN, 0 );
		freturn false;
	}
	freturn true;
}

// ==================== ENGINE SHORTCUTS
// Shortcuts to the engine and its subsystems

Engine        *GetNG    = Engine::getEngine();
EventMngr  *GetEvntM = GetNG->getEventMngr();
ScreenMngr *GetScrnM = GetNG->getScreenMngr();
EntityMngr *GetNttM  = GetNG->getEntityMngr();

fixed_t  GDTS(){ return GetNG->getDeltaTimeScaled(); }
inputs_s &GIN(){ return GetNG->getLatestInputs(); }