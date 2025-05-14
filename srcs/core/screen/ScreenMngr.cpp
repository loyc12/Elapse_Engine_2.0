#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

ScreenMngr::ScreenMngr()
{
	flog( 0 );
	init();
}

ScreenMngr::~ScreenMngr()
{
	flog( 0 );
	close();
}

// ================================ CORE METHODS

void ScreenMngr::init()
{
	flog( 0 );

	_targetFPS = WINDOW_DEFAULT_FPS;

	_screenMngr        = vec2_t( SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT );
	_mouseScreenPos  = vec2_t( 0 );
	_mouseWorldPos   = vec2_t( 0 );
	_trackedEntity   = nullptr;

	_camera.target   = { 0.0f, 0.0f };
	_camera.zoom     = DEFAULT_ZOOM;
	_camera.rotation = 0.0f;
	_camera.offset   = { _screenMngr.x / 2, _screenMngr.y / 2 };
}

void ScreenMngr::open()
{
	flog( 0 );
	if( IsWindowReady() )
	{
		qlog( "open : Window already opened", WARN, 0 );
		return;
	}

	InitWindow( _screenMngr.x, _screenMngr.y, WINDOW_DEFAULT_TITLE );

	if( !IsWindowReady() )
	{
		qlog( "open : Failed to open window", ERROR, 0 );
		return;
	}
	qlog( "open : Window successfully opened", INFO, 0 );

	SetTargetFPS( _targetFPS );
}

void ScreenMngr::close()
{
	flog( 0 );
	if( !IsWindowReady() )
	{
		qlog( "close : Window already closed", INFO, 0 );
		return;
	}

	CloseWindow();

	if( IsWindowReady() )
	{
		qlog( "close : Failed to close window", ERROR, 0 );
		return;
	}
	qlog( "close : Window successfully closed", INFO, 0 );
}

void ScreenMngr::update()
{
	flog( 0 );
	updateCamera();
	updateView();
	updateMouse();
}

void ScreenMngr::refresh()
{
	flog( 0 );
	ClearBackground( BACKGROUND_COLOUR );
	update();
}

void ScreenMngr::updateView()
{
	flog( 0 );
	// sets _screenMngr to the camera view size
	_screenMngr.x = GetScreenWidth()  * _camera.zoom;
	_screenMngr.y = GetScreenHeight() * _camera.zoom;
}
void ScreenMngr::updateMouse()
{
	flog( 0 );
	_mouseScreenPos = GetMousePosition();
	_mouseWorldPos  = GetScreenToWorld2D( _mouseScreenPos, _camera );

}
void ScreenMngr::updateCamera()
{
	flog( 0 );
	if( isTracking() ){ _camera.target = _trackedEntity->getPos(); }

	// Clamping camera values
	if( _camera.zoom > MIN_ZOOM ){ _camera.zoom = MIN_ZOOM; }
	if( _camera.zoom < MAX_ZOOM ){ _camera.zoom = MAX_ZOOM; }

	if( _camera.rotation < 0.0f   ) while( _camera.rotation < 0.0f   ){ _camera.rotation += 360.0f; }
	if( _camera.rotation > 360.0f ) while( _camera.rotation > 360.0f ){ _camera.rotation -= 360.0f; }

	_camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

}

// ================================ ACCESSORS / MUTATORS

void ScreenMngr::setTargetFPS( byte_t fps )
{
	flog( 0 );
	if( fps == 0 )
	{
		qlog( "setTargetFPS : FPS cannot be 0", ERROR, 0 );
		return;
	}
	_targetFPS = fps;
	if ( IsWindowReady() ){ SetTargetFPS( _targetFPS ); }
}

void ScreenMngr::setZoom(   fixed_t   zoom ){ _camera.zoom = zoom; }
void ScreenMngr::scaleZoom( fixed_t factor ){ _camera.zoom *= float( factor ); }

void ScreenMngr::setRotation(  fixed_t rotation ){ _camera.rotation = rotation; }
void ScreenMngr::moveRotation( fixed_t    delta ){ _camera.rotation += float( delta ); }

/*
void ScreenMngr::setOffset(  vec2_t &offset ){ _camera.offset = offset; }
void ScreenMngr::moveOffset( vec2_t &delta )
{
	_camera.offset.x += offset.x;
	_camera.offset.y += offset.y;
}
*/