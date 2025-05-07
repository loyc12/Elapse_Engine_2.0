#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : _DT( 0.0f ), _TS( 1.0f ), _state( ES_CLOSED )
{
	flog( 0 );
	if( getState() < ES_CLOSING )
		switchState( ES_INITIALIZED );
}

Engine::~Engine()
{
	flog( 0 );
	if( getState() > ES_CLOSED )
		switchState( ES_CLOSED );
}

Engine *Engine::getEngine() // NOTE : static class method ( singleton )
{
	flog( 0 );
	static Engine *instance = new Engine();
	return instance;
}

// ================================ ACCESSORS / MUTATORS

float  Engine::setTimeScale( float timeScale )
{
	flog( 0 );
	if( timeScale < 0 )
	{
		qlog( "setTimeScale : Time scale cannot be negative", WARN, 0 );
		_TS = 0;
	}
	else { _TS = timeScale; }

	return _TS;
}

bool Engine::canEngineTick()
{
	flog( 0 );
	if( getState() < ES_STARTED )
	{
		qlog( "canEngineTick : Engine needs to at least be started", WARN, 0 );
		return false;
	}
	return true;
}

// ==================== ENGINE SHORTCUTS
// Shortcuts to the engine and its components

Engine      *GNG = Engine::getEngine();
Controller  *GCN = GNG->getController();
Viewport2D  *GVP = GNG->getViewport();
CompManager *GCM = GNG->getCompManager();

float    GDTS(){ return GNG->getDeltaTimeScaled(); }
inputs_s &GIN(){ return GNG->getLatestInputs(); }