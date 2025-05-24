#ifndef SCREEN_MNGR_HPP
# define SCREEN_MNGR_HPP

# include "../base.hpp"
//# include "../entity/Entity.hpp"

# define WINDOW_DEFAULT_TITLE  "ToyEngine"
# define WINDOW_DEFAULT_FPS    128
# define SCREEN_DEFAULT_WIDTH  2048
# define SCREEN_DEFAULT_HEIGHT 1024

# define DEBUG_FONT_SIZE 32
# define MAX_ZOOM        0.25f
# define DEFAULT_ZOOM    1.00f
# define MIN_ZOOM        16.0f

# define BACKGROUND_COLOUR { 64, 64, 64, 255 }

class ScreenMngr
{
	private:
	// ================================ ATTRIBUTES
		bool   _isOpened;   // wether the screen is opened
		byte_t _targetFPS;  // target frames per second
		vec2_t _screenSize; // latest size of camera field of view in world units

		Camera2D _camera;   // contains target, zoom, rotation, offset //   FROM RAYLIB

		//Entity  *_trackedEntity; // entity being tracked by the camera, if any

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ScreenMngr(){  init(); }
		inline ~ScreenMngr(){ close(); }

	private:
	// ================================ CORE METHODS
		inline void init()
		{
			flog( 0 );

			_isOpened   = false;
			_targetFPS  = WINDOW_DEFAULT_FPS;
			_screenSize = vec2_t( SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT );

			_camera.target   = { 0, 0 };
			_camera.zoom     = DEFAULT_ZOOM;
			_camera.rotation = 0;
			_camera.offset   = { _screenSize.x / 2, _screenSize.y / 2 };

			//_trackedEntity   = nullptr;

			fend();
		}

	public:
		void open();
		void close();

	// ================================ UPDATE METHODS

		void refresh(); // NOTE : clears the screen calls all update methods

		void updateScreen();
		void updateCamera();

	// ================================ ACCESSORS / MUTATORS
		inline bool isOpened() const { return  _isOpened &&  IsWindowReady(); }
		inline bool isClosed() const { return !_isOpened || !IsWindowReady(); }

		inline fixed_t getTargetFPS() const { return _targetFPS; }

		void setTargetFPS( byte_t  fps );

	// ================================ SCREEN ACCESSORS / MUTATORS

		inline vec2_t getScreenSize() const { return _screenSize; }

		inline void setScreenSize( fixed_t width, fixed_t height ){ setScreenSize( vec2_t( width, height ) ); }
		void setScreenSize( vec2_t size );

		void setWindowTitle( const char *title );
		void setWindowIcon(  const char *iconPath );

		void setBackgroundColour( col_t colour = BACKGROUND_COLOUR );

	// ================================ CAMERA ACCESSORS / MUTATORS

		inline Camera2D *getCamera() { return &_camera; }

		inline fixed_t getZoom() const { return _camera.zoom; }
		inline void scaleZoom( fixed_t factor ){ setZoom( factor * _camera.zoom ); }
		void setZoom( fixed_t zoom );

		inline fixed_t getRotation() const { return _camera.rotation; }
		inline void moveRotation( angle_t    delta ){ setRotation( delta + fixed_t( _camera.rotation * DtoR )); }
		inline void setRotation(  angle_t rotation ){ _camera.rotation = rotation.getDeg(); }

		inline vec2_t getTarget() const { return _camera.target; }
		inline void moveTarget( vec2_t delta, bool overrideTracking = false ){ setTarget( delta + _camera.target, overrideTracking ); }
		void setTarget( vec2_t target, bool overrideTracking = false );

		inline vec2_t getOffset() const { return _camera.offset; }
		//inline void moveOffset( vec2_t delta ){ _camera.offset = delta + _camera.offset; }
		//inline void setOffset(  vec2_t offset ){ _camera.offset = offset; }

		// NOTE : these are all in world units
		inline vec2_t  getCenter()   const { return getTarget(); }
		inline fixed_t getWidth()    const { return _screenSize.x / _camera.zoom; }
		inline fixed_t getHeight()   const { return _screenSize.y / _camera.zoom; }
		inline vec2_t  getSize()     const { return _screenSize   / _camera.zoom; }

		inline vec2_t  getTop()      const { return GetScreenToWorld2D({ 0,             0             }, _camera ); }
		inline vec2_t  getBot()      const { return GetScreenToWorld2D({ getWidth(),    0             }, _camera ); }
		inline vec2_t  getLeft()     const { return GetScreenToWorld2D({ 0,             getHeight()   }, _camera ); }
		inline vec2_t  getRight()    const { return GetScreenToWorld2D({ getWidth(),    getHeight()   }, _camera ); }

		inline vec2_t  getTopLeft()  const { return GetScreenToWorld2D({ getCenter().x, 0             }, _camera ); }
		inline vec2_t  getTopRight() const { return GetScreenToWorld2D({ getCenter().x, getHeight()   }, _camera ); }
		inline vec2_t  getBotLeft()  const { return GetScreenToWorld2D({ 0,             getCenter().y }, _camera ); }
		inline vec2_t  getBotRight() const { return GetScreenToWorld2D({ getWidth(),    getCenter().y }, _camera ); }

	// ================================ ENTITY TRACKING METHODS

		//inline Entity *getTrackedEntity() const { return _trackedEntity; }
		//inline bool    isTracking()       const { return _trackedEntity != nullptr; }

		//bool trackEntity( Entity *obj, bool overrideTracking = false );
		//bool untrackEntity();

	// ================================ DRAWING METHODS
		void putPoin( vec2_t pos,                       col_t colour = WHITE );
		void putLine( vec2_t p1,  vec2_t p2,            col_t colour = WHITE, bool fill = true );
		void putTria( vec2_t p1,  vec2_t p2, vec2_t p3, col_t colour = WHITE, bool fill = true, bool checkOrder = true );

		void putRect( vec2_t pos, vec2_t  sizes,  col_t colour = WHITE, bool fill = true );
		void putCirc( vec2_t pos, fixed_t radius, col_t colour = WHITE, bool fill = true );

		void putRectCorn( vec2_t p1,  vec2_t  p2,       col_t colour = WHITE, bool fill = true );
		void putCircSect( vec2_t pos, fixed_t radius, angle_t start, angle_t end, col_t colour = WHITE, bool fill = true );

		//void putRectTurn( vec2_t pos, vec2_t sizes, angle_t angle,               col_t colour = WHITE, bool fill = true  ); // TODO : implement me
		//void putOval(     vec2_t pos, vec2_t sizes, angle_t angle,               col_t colour = WHITE, bool fill = true  ); // TODO : implement me
		//void putPoly(     vec2_t pos, vec2_t sizes, angle_t angle, byte_t sideC, col_t colour = WHITE, bool fill = true  ); // TODO : implement me

		//void putForm( vec2_arr_t points, col_t colour = WHITE, bool fill = true, bool checkOrder = true );// TODO : implement me
};


#endif // SCREEN_MNGR_HPP