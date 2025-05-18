#ifndef SCREEN_MNGR_HPP
# define SCREEN_MNGR_HPP

# include <raylib.h>
# include "../../base.hpp"
# include "../entity/Entity.hpp"


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
		byte_t	_targetFPS; 		 // target frames per second
		vec2_t	_screenMngr;       // latest size of camera field of view in world units
		vec2_t	_mouseScreenPos; // latest position of the mouse in pixels //        TODO : move these two to event mngr calls
		vec2_t	_mouseWorldPos;  // latest position of the mouse in world units

		Entity  *_trackedEntity; // entity being tracked by the camera, if any
		Camera2D _camera;        // contains target, zoom, rotation, offset //   FROM RAYLIB

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		ScreenMngr();
		~ScreenMngr();

	private:
	// ================================ CORE METHODS
		void init();

	public:
		void open();
		void close();

		void update();
		void refresh();

		void updateView();
		void updateMouse(); // TODO : move this to event mngr calls
		void updateCamera();

	// ================================ ACCESSORS / MUTATORS
		inline vec2_t  getMouseScreenPos() const { return _mouseScreenPos; }
		inline vec2_t  getMouseWorldPos()  const { return _mouseWorldPos; }
		inline fixed_t getTargetFPS()      const { return _targetFPS; }

		inline fixed_t getWidth()    const { return _screenMngr.x; }
		inline fixed_t getHeight()   const { return _screenMngr.y; }
		inline fixed_t getZoom()     const { return _camera.zoom; }
		inline fixed_t getRotation() const { return _camera.rotation; }
		inline vec2_t  getOffset()   const { return _camera.target; }
		inline vec2_t  getTarget()   const { return _camera.target; }

		void setTargetFPS( byte_t fps );
		void setZoom(      fixed_t zoom );
		void scaleZoom(    fixed_t factor );
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
		void putPoin( vec2_t pos,                       col_t colour = WHITE );
		void putLine( vec2_t p1,  vec2_t p2,            col_t colour = WHITE, bool fill = true );
		void putTria( vec2_t p1,  vec2_t p2, vec2_t p3, col_t colour = WHITE, bool fill = true, bool checkOrder = true );

		void putRect(     vec2_t pos, vec2_t  sizes,    col_t colour = WHITE, bool fill = true );
		void putCirc(     vec2_t pos, fixed_t radius,   col_t colour = WHITE, bool fill = true );
		void putRectCorn( vec2_t p1,  vec2_t  p2,       col_t colour = WHITE, bool fill = true );
		void putCircSect( vec2_t pos, fixed_t radius, angle_t start, angle_t end, col_t colour = WHITE, bool fill = true );

		void putRect( vec2_t pos, vec2_t sizes, angle_t angle,               col_t colour = WHITE, bool fill = true  ); // TODO : implement me
		void putOval( vec2_t pos, vec2_t sizes, angle_t angle,               col_t colour = WHITE, bool fill = true  ); // TODO : implement me
		void putPoly( vec2_t pos, vec2_t sizes, angle_t angle, byte_t sideC, col_t colour = WHITE, bool fill = true  ); // TODO : implement me

		void putForm( vec2_arr_t points, col_t colour = WHITE, bool fill = true, bool checkOrder = true );// TODO : implement me
};


#endif // SCREEN_MNGR_HPP