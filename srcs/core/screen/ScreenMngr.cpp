#include <raylib.h>
#include "../../../incs/core.hpp"


// ================================ CORE METHODS

void ScreenMngr::open()
{
	flog( 0 );
	if( isOpened() )
	{
		qlog( "open : Window already opened", WARN, 0 );
		fend(); return;
	}

	InitWindow( _screenSize.x, _screenSize.y, WINDOW_DEFAULT_TITLE );

	if( !IsWindowReady() )
	{
		qlog( "open : Failed to open window", ERROR, 0 );
		fend(); return;
	}

	qlog( "open : Window successfully opened", INFO, 0 );
	SetTargetFPS( _targetFPS );
	_isOpened = true;

	fend();
}

void ScreenMngr::close()
{
	flog( 0 );
	if( isClosed() )
	{
		qlog( "close : Window already closed", INFO, 0 );
		fend(); return;
	}

	CloseWindow();

	if( IsWindowReady() )
	{
		qlog( "close : Failed to close window", ERROR, 0 );
		fend(); return;
	}

	qlog( "close : Window successfully closed", INFO, 0 );
	_isOpened = false;

	fend();
}

// ================================ UPDATE METHODS

void ScreenMngr::refresh()
{
	flog( 0 );

	ClearBackground( BACKGROUND_COLOUR );
	updateCamera();
	updateScreen();

	fend();
}

void ScreenMngr::updateScreen()
{
	flog( 0 );

	_screenSize.x = GetScreenWidth();
	_screenSize.y = GetScreenHeight();

	fend();
}

void ScreenMngr::updateCamera()
{
	flog( 0 );

	_camera.zoom     = Opfx::clmp( _camera.zoom, MIN_ZOOM, MAX_ZOOM );
	_camera.rotation = Opfx::clmp( _camera.rotation, 0, 360 );
	_camera.offset   = _screenSize / 2; // NOTE : this makes sure the camera is centered on the screen

	//if( isTracking() ){ _camera.target = _trackedEntity->getPos(); }

	fend();
}

// ================================ ACCESSORS / MUTATORS

void ScreenMngr::setTargetFPS( byte_t fps )
{
	flog( 0 );
	if( fps == 0 )
	{
		qlog( "setTargetFPS : FPS cannot be 0", ERROR, 0 );
		fend(); return;
	}
	_targetFPS = fps;
	if ( IsWindowReady() ){ SetTargetFPS( _targetFPS ); }

	fend();
}

// ================================ SCREEN ACCESSORS / MUTATORS

void ScreenMngr::setScreenSize( vec2_t size )
{
	flog( 0 );

	if( size.x <= 0 || size.y <= 0 )
	{
		qlog( "setScreenSize : Size cannot be 0 or negative", ERROR, 0 );
		fend(); return;
	}

	_screenSize = size;
	if ( isOpened() ){ SetWindowSize( _screenSize.x, _screenSize.y ); }
	else { qlog( "setScreenSize : Window is not opened, size will be set on next open", INFO, 0 ); }

	fend();
}

void ScreenMngr::setWindowTitle( const char *title )
{
	flog( 0 );

	if( isClosed() )
	{
		qlog( "setWindowTitle : Window is not opened", ERROR, 0 );
		fend(); return;
	}

	if( title == nullptr || strlen( title ) == 0 )
	{
		qlog( "setWindowTitle : Title cannot be empty", ERROR, 0 );
		fend(); return;
	}
	SetWindowTitle( title );

	fend();
}
void ScreenMngr::setWindowIcon( const char *iconPath )
{
	flog( 0 );

	if( isClosed() )
	{
		qlog( "setWindowIcon : Window is not opened", ERROR, 0 );
		fend(); return;
	}

	if( iconPath == nullptr || strlen( iconPath ) == 0 )
	{
		qlog( "setWindowIcon : Icon path cannot be empty", ERROR, 0 );
		fend(); return;
	}
	SetWindowIcon( LoadImage( iconPath ) );

	fend();
}

void ScreenMngr::setBackgroundColour( col_t colour )
{
	flog( 0 );

	if( isClosed() )
	{
		qlog( "setBackgroundColour : Window is not opened", ERROR, 0 );
		fend(); return;
	}

	ClearBackground( colour );

	fend();
}

// ================================== CAMERA ACCESSORS / MUTATORS

void ScreenMngr::setZoom( fixed_t zoom )
{
	flog( 0 );

	if( zoom < MIN_ZOOM || zoom > MAX_ZOOM )
	{
		qlog( "setZoom : values outside accepted range : clamping", ERROR, 0 );
		zoom = Opfx::clmp( zoom, MIN_ZOOM, MAX_ZOOM );
	}
	_camera.zoom = float( zoom );

	fend();
}

void ScreenMngr::setTarget( vec2_t target, bool overrideTracking )
{
	flog( 0 );
	( void )overrideTracking; // TODO : use me once entities are reimplemented
	//if( _trackedEntity )
	//{
	//	if( !overrideTracking )
	//	{
	//		qlog( "setTarget : Already tracking an object", INFO, 0 );
	//		qlog( "setTarget : Use overrideTracking = true to override", INFO, 0 );
	//		fend(); return;
	//	}
	//	else { qlog( "setTarget : Overriding tracking", INFO, 0 ); }
	//}
	_camera.target = target;
}
