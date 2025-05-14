#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

ScreenManager::ScreenManager()
{
	flog( 0 );
	init();
}

ScreenManager::~ScreenManager()
{
	flog( 0 );
	close();
}

// ================================ CORE METHODS

void ScreenManager::init()
{
	flog( 0 );

	_targetFPS = WINDOW_DEFAULT_FPS;

	_windowSize      = vec2_t( SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT );
	_mouseScreenPos  = vec2_t( 0 );
	_mouseWorldPos   = vec2_t( 0 );
	_trackedEntity   = nullptr;

	_camera.target   = { 0.0f, 0.0f };
	_camera.zoom     = DEFAULT_ZOOM;
	_camera.rotation = 0.0f;
	_camera.offset   = { _windowSize.x / 2, _windowSize.y / 2 };
}

void ScreenManager::open()
{
	flog( 0 );
	if( IsWindowReady() )
	{
		qlog( "open : Window already opened", WARN, 0 );
		return;
	}

	InitWindow( _windowSize.x, _windowSize.y, WINDOW_DEFAULT_TITLE );

	if( !IsWindowReady() )
	{
		qlog( "open : Failed to open window", ERROR, 0 );
		return;
	}
	qlog( "open : Window successfully opened", INFO, 0 );

	SetTargetFPS( _targetFPS );
}

void ScreenManager::close()
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

void ScreenManager::update()
{
	flog( 0 );
	updateCamera();
	updateSize();
	updateMouse();
}

void ScreenManager::refresh()
{
	flog( 0 );
	ClearBackground( BACKGROUND_COLOUR );
	update();
}

void ScreenManager::updateSize()
{
	flog( 0 );
	// sets _windowSize to the camera view size
	_windowSize.x = GetScreenWidth()  * _camera.zoom;
	_windowSize.y = GetScreenHeight() * _camera.zoom;
}
void ScreenManager::updateMouse()
{
	flog( 0 );
	_mouseScreenPos = GetMousePosition();
	_mouseWorldPos  = GetScreenToWorld2D( _mouseScreenPos, _camera );

}
void ScreenManager::updateCamera()
{
	flog( 0 );
	if( isTracking() ){ _camera.target = _trackedEntity->getPos(); }

	// Clamping camera values
	if( _camera.zoom > MIN_ZOOM ){ _camera.zoom = MIN_ZOOM; }
	if( _camera.zoom < MAX_ZOOM ){ _camera.zoom = MAX_ZOOM; }

	if( _camera.rotation < 0.0f   ) while( _camera.rotation < 0.0f   ){ _camera.rotation += 360.0f; }
	if( _camera.rotation > 360.0f ) while( _camera.rotation > 360.0f ){ _camera.rotation -= 360.0f; }

	//_camera.offset = { _windowSize.x / 2, _windowSize.y / 2 }; TODO : make sure this works well with zooming

}

// ================================ ACCESSORS / MUTATORS

void ScreenManager::setTargetFPS( byte_t fps )
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

void ScreenManager::setZoom(   fixed_t   zoom ){ _camera.zoom = zoom; }
void ScreenManager::scaleZoom( fixed_t factor ){ _camera.zoom *= float( factor ); }

void ScreenManager::setRotation(  fixed_t rotation ){ _camera.rotation = rotation; }
void ScreenManager::moveRotation( fixed_t    delta ){ _camera.rotation += float( delta ); }

/*
void ScreenManager::setOffset(  vec2_t &offset ){ _camera.offset = offset; }
void ScreenManager::moveOffset( vec2_t &delta )
{
	_camera.offset.x += offset.x;
	_camera.offset.y += offset.y;
}
*/