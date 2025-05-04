#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : _DT( 0 ), _TS( 1 ), _state( ES_CLOSED )
{
	flog( 0 );
	if( getState() < ES_CLOSING )
		switchState(  ES_INITIALIZED );
}

Engine::~Engine()
{
	flog( 0 );
	if( getState() > ES_CLOSED )
		switchState(  ES_CLOSED );
}

Engine *Engine::getEngine()
{
	flog( 0 );
	static Engine *instance = new Engine();

	return instance;
}

// ================================ ACCESSORS / MUTATORS

float Engine::getDeltaTime() const { return _DT * _TS; }
void  Engine::setTimeScale( float timeScale )
{
	flog( 0 );
	if( timeScale < 0 )
	{
		qlog( "setTimeScale : Time scale cannot be negative", WARN, 0 );
		_TS = 0;
		return;
	}
	_TS = timeScale;
}

// ==================== ENGINE SHORTCUTS
// Shortcuts to the engine and its components

Engine      *GNG = Engine::getEngine();
Controller  *GCN = GNG->getController();
Viewport2D  *GVP = GNG->getViewport();
CompManager *GCM = GNG->getCompManager();

float    GDTS(){ return GNG->getDeltaTime(); }
inputs_s &GIN(){ return GNG->getLatestInputs(); }