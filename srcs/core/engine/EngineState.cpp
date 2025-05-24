#include <raylib.h>
#include "../../../incs/core.hpp"

// ================================ STATE METHODS

// Goes trought the steps needed to go from one state to another
bool Engine::switchState(  engineState_e targetState )
{
	flog( 0 );
	if( getState() == targetState )
	{
		qlog( "switchState : State matches current state : " + to_string( targetState ), WARN, 0 );
		fend(); return false;
	}
	if ( targetState == ES_CLOSED ){ qlog( "! ================ CLOSING THE ENGINE ================ !", INFO, 0 ); }

	engineState_e previousState = getState();
	qlog( "switchState : Changing state from " + to_string( getState() ) + " to " + to_string( targetState ), INFO, 0 );

	// goes through the steps to raise the state
	if( targetState > getState() ){ switch ( getState() )
	{
		case ES_CLOSED:
			qlog( "switchState : Raising to ES_INITIALIZED", DEBUG, 0 );
			setState( ES_INITIALIZING ); init();
			if( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_INITIALIZED:
			qlog( "switchState : Raising to ES_STARTED", DEBUG, 0 );
			setState( ES_STARTING ); start();
			if( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_STARTED:
			qlog( "switchState : Raising to ES_RUNNING", DEBUG, 0 );
			setState( ES_RESUMING ); resume();
			if( getState() == targetState ) break;

			[[ fallthrough ]];

		default:
			qlog( "switchState : Invalid state : Raising from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR, 0 );
			fend(); return false;
	}}

	// goes through the steps to lower the state
	if( targetState < getState() ){ switch ( getState() )
	{
		case ES_RUNNING:
			qlog( "switchState : Lowering to ES_STARTED", DEBUG, 0 );
			setState( ES_PAUSING ); pause();
			if( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_STARTED:
			qlog( "switchState : Lowering to ES_INITIALIZED", DEBUG, 0 );
			setState( ES_STOPPING ); stop();
			if( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_INITIALIZED:
			qlog( "switchState : Lowering to ES_CLOSED", DEBUG, 0 );
			setState( ES_CLOSING ); close();
			if( getState() == targetState ) break;

			[[ fallthrough ]];

		default:
			qlog( "switchState : Invalid state : Lowering from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR, 0 );
			fend(); return false;
	}}

	qlog( "switchState : State changed from " + to_string( previousState ) + " to " + to_string( targetState ), INFO, 0 );
	fend(); return true;
}

bool Engine::togglePause()
{
	flog( 0 );
	static fixed_t prevTS = 0.0f;

	if( prevTS == 0.0f )
	{
		prevTS = _TS;
		_TS = 0.0f;
		fend(); return true;
	}
	else
	{
		_TS = prevTS;
		prevTS = 0.0f;
		fend(); return false;
	}
}

void Engine::init()
{
	flog( 0 );
	if( getState() > ES_INITIALIZING ){ qlog( "init : Engine already initialized",  ERROR, 0 ); fend(); return; }
	if( getState() < ES_CLOSED){        qlog( "init : how did you even get here ?", ERROR, 0 ); fend(); return; }

	_screenMngr2D = new ScreenMngr();  GetScrnM = _screenMngr2D;
	//_eventMngr    = new EventMngr();   GetEvntM = _eventMngr;
	//_entityMngr   = new EntityMngr();  GetNttM  = _entityMngr;

	OnEngineInit(); // from injectors.hpp
	setState( ES_INITIALIZED );

	fend();
}

void Engine::start()
{
	flog( 0 );
	if( getState() > ES_STARTING ){    qlog( "start : Engine already started", ERROR, 0 ); fend(); return; }
	if( getState() < ES_INITIALIZED ){ qlog( "start : Engine not initialized", ERROR, 0 ); fend(); return; }

	_screenMngr2D->open();

	OnEngineStart(); // from injectors.hpp
	setState( ES_STARTED );

	fend();
}

void Engine::resume()
{
	flog( 0 );
	if( getState() > ES_RESUMING ){ qlog( "resume : Engine already running", ERROR, 0 ); fend(); return; }
	if( getState() < ES_STARTED ){  qlog( "resume : Engine not yet started", ERROR, 0 ); fend(); return; }

	OnEngineResume(); // from injectors.hpp
	setState( ES_RUNNING );

	fend();
}

void Engine::pause()
{
	flog( 0 );
	if( getState() < ES_PAUSING ){ qlog( "pause : Engine not currently running", ERROR, 0 ); fend(); return; }
	if( getState() > ES_RUNNING ){ qlog( "pause : how did you even get here ?",  ERROR, 0 ); fend(); return; }

	OnEnginePause(); // from injectors.hpp
	setState( ES_STARTED );

	fend();
}

void Engine::stop()
{
	flog( 0 );
	if( getState() < ES_STOPPING ){ qlog( "stop : Engine not yet started",  ERROR, 0 ); fend(); return; }
	if( getState() > ES_STARTED ){  qlog( "stop : Engine is still running", ERROR, 0 ); fend(); return; }

	_screenMngr2D->close();

	OnEngineStop(); // from injectors.hpp
	setState( ES_INITIALIZED );

	fend();
}

void Engine::close()
{
	flog( 0 );
	if( getState() < ES_CLOSING ){     qlog( "close : Engine not initialized", ERROR, 0 ); fend(); return; }
	if( getState() > ES_INITIALIZED ){ qlog( "close : Engine still started",   ERROR, 0 ); fend(); return; }

	OnEngineClose(); // from injectors.hpp
	setState( ES_CLOSED );

	//delete _entityMngr;     _entityMngr = nullptr;     GetNttM = nullptr;
	//delete _eventMngr;      _eventMngr = nullptr;      GetEvntM = nullptr;
	delete _screenMngr2D;   _screenMngr2D = nullptr;   GetScrnM = nullptr;

	fend();
}
