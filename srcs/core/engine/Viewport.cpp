#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CORE METHODS

void Viewport2D::init()
{
	flog( 0 );
	_targetFPS = WINDOW_DEFAULT_FPS;

	_windowSize    = vec2_t( SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT );
	_mousePos      = vec2_t( 0 );
	_mouseWorldPos = vec2_t( 0 );

	_camera.target   = { 0.0f, 0.0f };
	_camera.zoom     = DEFAULT_ZOOM;
	_camera.rotation = 0.0f;
	_camera.offset   = { _windowSize.x / 2, _windowSize.y / 2 };

	_trackingEntitity = false;
	_trackedEntitity  = nullptr;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Viewport2D::Viewport2D()
{
	flog( 0 );
	init();
}

Viewport2D::~Viewport2D()
{
	flog( 0 );
	close();
}

// ================================ ACCESSORS

fixed_t Viewport2D::getWidth()      const { return _windowSize.x; }
fixed_t Viewport2D::getHeight()     const { return _windowSize.y; }
fixed_t Viewport2D::getZmdWidth()   const { return _windowSize.x / _camera.zoom; } // returns the width of the camera view in world units
fixed_t Viewport2D::getZmdHeight()  const { return _windowSize.y / _camera.zoom; } // returns the height of the camera view in world units

vec2_t Viewport2D::getSize()     const { return _windowSize; }
vec2_t Viewport2D::getCenter()   const { return _camera.target; }
vec2_t Viewport2D::getOrigin()   const { return GetScreenToWorld2D( { 0, 0 }, _camera ); } // returns the origin of the camera view in world units

vec2_t Viewport2D::getTopLeft()  const { return GetScreenToWorld2D( { 0,                0 },                _camera ); }
vec2_t Viewport2D::getTopRight() const { return GetScreenToWorld2D( { getZmdWidth(),    0 },                _camera ); }
vec2_t Viewport2D::getBotLeft()  const { return GetScreenToWorld2D( { 0,                getZmdHeight()   }, _camera ); }
vec2_t Viewport2D::getBotRight() const { return GetScreenToWorld2D( { getZmdWidth(),    getZmdHeight()   }, _camera ); }

vec2_t Viewport2D::getTop()   const { return GetScreenToWorld2D( { _camera.target.x, 0 },                _camera ); }
vec2_t Viewport2D::getBot()   const { return GetScreenToWorld2D( { _camera.target.x, getZmdHeight()   }, _camera ); }
vec2_t Viewport2D::getLeft()  const { return GetScreenToWorld2D( { 0,                _camera.target.y }, _camera ); }
vec2_t Viewport2D::getRight() const { return GetScreenToWorld2D( { getZmdWidth(),    _camera.target.y }, _camera ); }

vec2_t Viewport2D::getMousePos()      const { return _mousePos; }
vec2_t Viewport2D::getMouseWorldPos() const { return _mouseWorldPos; }

// ================================ CAMERA ACCESSORS

Camera2D *Viewport2D::getCamera(){ return &_camera; }

vec2_t Viewport2D::getTarget() const { return _camera.target; }
void Viewport2D::moveTarget( vec2_t offset )
{
	_camera.target.x += float( offset.x );
	_camera.target.y += float( offset.y );
}
void Viewport2D::setTarget( vec2_t target, bool overrideTracking )
{
	flog( 0 );
	if( _trackedEntitity )
	{
		if( !overrideTracking )
		{
			qlog( "setTarget : Already tracking an object", INFO, 0 );
			qlog( "setTarget : Use overrideTracking = true to override", INFO, 0 );
			return;
		}
		else { qlog( "setTarget : Overriding tracking", INFO, 0 ); }
	}
	_trackingEntitity = true;
	_camera.target    = target;
}

fixed_t Viewport2D::getZoom(){ return _camera.zoom; }
void    Viewport2D::setZoom( fixed_t   zoom ){ _camera.zoom = zoom; }
void  Viewport2D::scaleZoom( fixed_t factor ){ _camera.zoom *= float( factor ); }

fixed_t Viewport2D::getRotation(){ return _camera.rotation; }
//void Viewport2D::setRotation(  fixed_t rotation ){ _camera.rotation = rotation; }
//void Viewport2D::moveRotation( fixed_t    delta ){ _camera.rotation += delta; }

vec2_t Viewport2D::getOffset() const { return _camera.offset; }
/*
void Viewport2D::setOffset(  vec2_t &offset ){ _camera.offset = offset; }
void Viewport2D::moveOffset( vec2_t &delta )
{
	_camera.offset.x += offset.x;
	_camera.offset.y += offset.y;
}
*/

// ================================ METHODS

void Viewport2D::open()
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

void Viewport2D::close()
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

void Viewport2D::update()
{
	flog( 0 );
	updateCamera();
	updateSize();
	updateMouse();
}

void Viewport2D::refresh()
{
	flog( 0 );
	ClearBackground( BACKGROUND_COLOUR );
	update();
}

void Viewport2D::updateSize()
{
	flog( 0 );
	// sets _windowSize to the camera view size
	_windowSize.x = GetScreenWidth()  * _camera.zoom;
	_windowSize.y = GetScreenHeight() * _camera.zoom;
}
void Viewport2D::updateMouse()
{
	flog( 0 );
	// sets _mousePos to were the mouse is in the world, accounting for the camera position
	_mousePos =      GetMousePosition();
	_mouseWorldPos = GetScreenToWorld2D( _mousePos, _camera );

}
void Viewport2D::updateCamera()
{
	flog( 0 );
	//if( _trackedEntitity ){ _camera.target = { _trackedEntitity->getPosition() }; } // TODO : implement this

	// Clamping camera values
	if( _camera.zoom > MIN_ZOOM ){ _camera.zoom = MIN_ZOOM; }
	if( _camera.zoom < MAX_ZOOM ){ _camera.zoom = MAX_ZOOM; }

	if( _camera.rotation < 0.0f   ) while( _camera.rotation < 0.0f   ){ _camera.rotation += 360.0f; }
	if( _camera.rotation > 360.0f ) while( _camera.rotation > 360.0f ){ _camera.rotation -= 360.0f; }

	//_camera.offset = { ( fixed_t )_windowSize.x / 2, ( fixed_t )_windowSize.y / 2 };

}

// ================================ OBJECTS TRACKING

Entity *Viewport2D::getTrackedEntity() const { return _trackedEntitity; }

bool Viewport2D::isTracking() const { return _trackingEntitity; }

bool Viewport2D::trackEntity( Entity *Ntt, bool overrideTracking )
{
	flog( 0 );
	if( Ntt == nullptr )
	{
		qlog( "trackEntity : Cannot track a nullptr", INFO, 0 );
		qlog( "trackEntity : Use untrackEntity() to stop tracking", DEBUG, 0 );
		return false;
	}

	if( _trackingEntitity )
	{
		if( !overrideTracking )
		{
			qlog( "trackEntity : Already tracking an object", WARN, 0 );
			qlog( "trackEntity : Use overrideTracking = true to override", INFO, 0 );
			return false;
		}
		else { qlog( "trackEntity : Overriding tracking", INFO, 0 ); }
	}

	_trackedEntitity  = Ntt;
	_trackingEntitity = true;

	return true;
}

bool Viewport2D::untrackEntity()
{
	flog( 0 );
	_trackedEntitity = nullptr;

	if( !_trackingEntitity ){ return false; }

	_trackingEntitity = false; return true;
}

