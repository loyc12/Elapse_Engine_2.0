#include <raylib.h>
#include "../../../incs/core.hpp"


// ================================ CORE METHODS

void ScreenMngr::open()
{
	flog( 0 );
	if( isOpened() )
	{
		qlog( "open : Window already opened", WARN, 0 );
		return;
	}

	InitWindow( _screenSize.x, _screenSize.y, WINDOW_DEFAULT_TITLE );

	if( !IsWindowReady() )
	{
		qlog( "open : Failed to open window", ERROR, 0 );
		return;
	}

	qlog( "open : Window successfully opened", INFO, 0 );

	if( _targetFPS > 0 ){ SetTargetFPS( _targetFPS ); } // NTOE : if the target FPS is 0, it will default to WINDOW_DEFAULT_FPS
	else{ SetTargetFPS( WINDOW_DEFAULT_FPS ); qlog( "setTargetFPS : FPS cannot be 0 or negative, setting to default", WARN, 0 ); }

	_isOpened = true;
}

void ScreenMngr::close()
{
	flog( 0 );
	if( isClosed() )
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
	_isOpened = false;
}

// ================================ UPDATE METHODS

void ScreenMngr::refresh()
{
	flog( 0 );

	ClearBackground( BACKGROUND_COLOUR );
	updateCamera();
	updateScreen();
}

void ScreenMngr::updateScreen()
{
	flog( 0 );

	_screenSize.x = GetScreenWidth();
	_screenSize.y = GetScreenHeight();
}

void ScreenMngr::updateCamera()
{
	flog( 0 );

	_camera.zoom     = Opfx::clmp( _camera.zoom, MIN_ZOOM, MAX_ZOOM );
	_camera.rotation = Opfx::clmp( _camera.rotation, 0, 360 );
	_camera.offset   = _screenSize / 2; // NOTE : this makes sure the camera is centered on the screen

	//if( isTracking() ){ _camera.target = _trackedEntity->getPos(); }
}

// ================================ ACCESSORS / MUTATORS

void ScreenMngr::setTargetFPS( byte_t fps )
{
	flog( 0 );
	_targetFPS = fps;

	if ( IsWindowReady() )
	{
		if( _targetFPS > 0 ){ SetTargetFPS( _targetFPS ); } // NTOE : if the target FPS is 0, it will default to WINDOW_DEFAULT_FPS
		else{ SetTargetFPS( WINDOW_DEFAULT_FPS ); qlog( "setTargetFPS : FPS cannot be 0 or negative, setting to default", WARN, 0 ); }
	}
	else{ qlog( "setTargetFPS : Window is not opened, FPS will be set on next open", INFO, 0 ); }
}

// ================================ SCREEN ACCESSORS / MUTATORS

void ScreenMngr::setScreenSize( vec2_t size )
{
	flog( 0 );

	if( size.x <= 0 || size.y <= 0 )
	{
		qlog( "setScreenSize : Size cannot be 0 or negative", ERROR, 0 );
		return;
	}

	_screenSize = size;
	if ( isOpened() ){ SetWindowSize( _screenSize.x, _screenSize.y ); }
	else { qlog( "setScreenSize : Window is not opened, size will be set on next open", INFO, 0 ); }
}

void ScreenMngr::setWindowTitle( const char *title )
{
	flog( 0 );

	if( isClosed() )
	{
		qlog( "setWindowTitle : Window is not opened", ERROR, 0 );
		return;
	}

	if( title == nullptr || strlen( title ) == 0 )
	{
		qlog( "setWindowTitle : Title cannot be empty", ERROR, 0 );
		return;
	}
	SetWindowTitle( title );
}
void ScreenMngr::setWindowIcon( const char *iconPath )
{
	flog( 0 );

	if( isClosed() )
	{
		qlog( "setWindowIcon : Window is not opened", ERROR, 0 );
		return;
	}

	if( iconPath == nullptr || strlen( iconPath ) == 0 )
	{
		qlog( "setWindowIcon : Icon path cannot be empty", ERROR, 0 );
		return;
	}
	SetWindowIcon( LoadImage( iconPath ) );
}

void ScreenMngr::setBackgroundColour( col_t colour )
{
	flog( 0 );

	if( isClosed() )
	{
		qlog( "setBackgroundColour : Window is not opened", ERROR, 0 );
		return;
	}

	ClearBackground( colour );
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
	//		return;
	//	}
	//	else { qlog( "setTarget : Overriding tracking", INFO, 0 ); }
	//}
	_camera.target = target;
}
