#ifndef VIEWPORT_HPP
# define VIEWPORT_HPP

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

class Viewport2D
{
	private:
	// ================================ ATTRIBUTES
		uint8_t	_targetFPS;

		vec2_t	_windowSize;    // latest size of the window in pixels
		vec2_t	_mousePos;      // latest position of the mouse in pixels
		vec2_t	_mouseWorldPos; // latest position of the mouse in world units

		Camera2D _camera;       // contains target, zoom, rotation, offset
		Entity  *_trackedEntitity;

		bool _trackingEntitity;

		// ================================ CORE METHODS
		void init();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Viewport2D();
		~Viewport2D();

	// ================================ ACCESSORS
		fixed_t getWidth()     const;
		fixed_t getHeight()    const;
		fixed_t getZmdWidth()  const;
		fixed_t getZmdHeight() const;

		vec2_t getSize()   const;
		vec2_t getOrigin() const;
		vec2_t getCenter() const;

		vec2_t getTop()   const;
		vec2_t getBot()   const;
		vec2_t getLeft()  const;
		vec2_t getRight() const;

		vec2_t getTopLeft()  const;
		vec2_t getTopRight() const;
		vec2_t getBotLeft()  const;
		vec2_t getBotRight() const;

		vec2_t getMousePos()      const;
		vec2_t getMouseWorldPos() const;

		// ================================ CAMERA ACCESSORS
		Camera2D *getCamera();

		vec2_t	getTarget() const;
		void    setTarget(  vec2_t target, bool overrideTracking = false );
		void    moveTarget( vec2_t offset );

		fixed_t getZoom();
		void    setZoom(   fixed_t zoom );
		void    scaleZoom( fixed_t factor );

		fixed_t getRotation();
		void    setRotation(  fixed_t rotation );
		void    moveRotation( fixed_t delta );

		vec2_t getOffset() const;
		//void    setOffset( vec2_t offset );
		//void    moveOffset( vec2_t delta );

	// ================================ OPERATORS

	// ================================ METHODS
		void open();
		void close();
		void update();
		void refresh();

		void updateSize();
		void updateMouse();
		void updateCamera();

	// ================================ OBJECT TRACKING
		Entity *getTrackedEntity() const;

		bool isTracking() const;
		bool trackEntity( Entity *obj, bool overrideTracking = false );
		bool untrackEntity();
};


#endif // VIEWPORT_HPP