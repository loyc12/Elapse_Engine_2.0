#ifndef SCREEN_MANAGER_HPP
# define SCREEN_MANAGER_HPP

# include <raylib.h>
# include "../../base.hpp"
# include "../entity/Entity.hpp"


# define WINDOW_DEFAULT_TITLE  "ToyEngine"
# define WINDOW_DEFAULT_FPS    128
# define SCREEN_DEFAULT_WIDTH  2048
# define SCREEN_DEFAULT_HEIGHT 1024

# define DEBUG_FONT_SIZE 32
# define MAX_ZOOM        0.25f
# define DEFAULT_ZOOM    2.00f
# define MIN_ZOOM        16.0f

# define BACKGROUND_COLOUR { 64, 64, 64, 255 }

class ScreenManager
{
	private:
	// ================================ ATTRIBUTES
		byte_t	_targetFPS;

		vec2_t	_windowSize;     // latest size of the window in pixels
		vec2_t	_mouseScreenPos; // latest position of the mouse in pixels // TODO : move to event manager calls
		vec2_t	_mouseWorldPos;  // latest position of the mouse in world units

		Entity *_trackedEntity;

		Camera2D _camera;       // contains target, zoom, rotation, offset // FROM RAYLIB

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		ScreenManager();
		~ScreenManager();

	private:
	// ================================ CORE METHODS
		void init();

	public:
		void open();
		void close();

		void update();
		void refresh();

		void updateSize();
		void updateMouse();
		void updateCamera();

	// ================================ ACCESSORS / MUTATORS
		inline vec2_t  getMouseScreenPos() const { return _mouseScreenPos; }
		inline vec2_t  getMouseWorldPos()  const { return _mouseWorldPos; }
		inline fixed_t getTargetFPS()      const { return _targetFPS; }

		inline fixed_t getWidth()    const { return _windowSize.x; }
		inline fixed_t getHeight()   const { return _windowSize.y; }

		inline fixed_t getZoom()     const { return _camera.zoom; }
		inline fixed_t getRotation() const { return _camera.rotation; }

		inline vec2_t  getOffset()   const { return _camera.target; }
		inline vec2_t  getTarget()   const { return _camera.target; }

		void setTargetFPS( byte_t fps );

		void setZoom(   fixed_t zoom );
		void scaleZoom( fixed_t factor );

		void setRotation(  fixed_t rotation );
		void moveRotation( fixed_t delta );

		//void setOffset(  vec2_t offset );
		//void moveOffset( vec2_t delta );

	// ================================ CAMERA METHODS
		inline Camera2D *getCamera() { return &_camera; }

		fixed_t getZmdWidth()  const;
		fixed_t getZmdHeight() const;

		vec2_t getSize()     const;
		vec2_t getOrigin()   const;
		vec2_t getCenter()   const;

		vec2_t getTop()      const;
		vec2_t getBot()      const;
		vec2_t getLeft()     const;
		vec2_t getRight()    const;

		vec2_t getTopLeft()  const;
		vec2_t getTopRight() const;
		vec2_t getBotLeft()  const;
		vec2_t getBotRight() const;

	// ================================ ENTITY TRACKING METHODS

		void setTarget(  vec2_t target, bool overrideTracking = false );
		void moveTarget( vec2_t offset );

		inline Entity *getTrackedEntity() const { return _trackedEntity; }
		inline bool    isTracking()       const { return _trackedEntity != nullptr; }

		bool trackEntity( Entity *obj, bool overrideTracking = false );
		bool untrackEntity();

	// ================================ DRAWING METHODS
		void putPoin( vec2_t pos,                       Color colour = WHITE );
		void putLine( vec2_t p1,  vec2_t p2,            Color colour = WHITE, bool fill = true );
		void putTria( vec2_t p1,  vec2_t p2, vec2_t p3, Color colour = WHITE, bool fill = true ); // NOTE : point order does not matter

		void putRectCorn( vec2_t p1,  vec2_t p2,        Color colour = WHITE, bool fill = true ); // NOTE : point order does not matter
		void putRect(     vec2_t pos, vec2_t sizes,     Color colour = WHITE, bool fill = true );
		void putCirc(     vec2_t pos, fixed_t radius,   Color colour = WHITE, bool fill = true );
		void putCircSect( vec2_t pos, fixed_t radius, angle_t start, angle_t end, Color colour = WHITE, bool fill = true );

		void putRect( vec2_t pos, vec2_t sizes, angle_t angle,               Color colour = WHITE, bool fill = true  ); // TODO : implement me
		void putOval( vec2_t pos, vec2_t sizes, angle_t angle,               Color colour = WHITE, bool fill = true  ); // TODO : implement me
		void putPoly( vec2_t pos, vec2_t sizes, angle_t angle, byte_t sideC, Color colour = WHITE, bool fill = true  ); // TODO : implement me

		void putForm( vec2_arr_t points, Color colour = WHITE, bool fill = true ); // NOTE : point order does not matter // TODO : implement me
};


#endif // SCREEN_MANAGER_HPP