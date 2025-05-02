#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <raylib.h>
# include "../base.hpp"

class Component;
class Entity;

class Viewport2D;
class Controller;
class CompManager;

typedef enum : byte_t
{
	ES_CLOSED, // either not yet initialized or closed ( deinitialized )
	ES_INITIALIZING,

	ES_CLOSING,
	ES_INITIALIZED, // initialized but either not yet started or stopped
	ES_STARTING,

	ES_STOPPING,
	ES_STARTED, // started but either not yet ran or paused
	ES_RESUMING,

	ES_PAUSING,
	ES_RUNNING, // running

} engineState_e;

class Engine
{
	// ================================ ATTRIBUTES
	private:
		id_t _maxID;
		float   _DT; // delta time
		float   _TS; // time scale

		Viewport2D  *_viewport2D;
		Controller  *_controller;
		CompManager *_compManager;

		engineState_e _state;
		std::mutex mtx_state;

	// ================================ STATE METHODS
	public:
		bool switchState(  engineState_e targetState );
		bool togglePause(); // switches the state between paused and running

	private:
		void init(); // initializes the engine's data
			void start(); // opens the window and readies the engine for the game loop
				void resume(); // resumes the engine physics
				void pause(); // pauses the engine physics
			void stop(); // stops the engine
		void close(); // closes the engine

	// ================================ STEP METHODS
	public:
		bool launchLoop(); // launches the game loop
		// NOTE : this is a blocking call for now. It will be multithreaded later
		// TODO : add a way to run the game loop in a separate thread
		// DEBUG : for now, this is called manually in main.cpp once I know the window is opened

	private:
		void runStep(); // calls the update methods once
			void readInputs();
			void runPhysics();
			void runScripts();
			void runRenders(); // calls the render methods once
				void renderWorld();
				void renderUIs();

	// ================================ CONSTRUCTORS / DESTRUCTORS
	private:
		// prevents this singleton from being copied
		Engine( const Engine &cpy ) = delete;
		Engine &operator=( const Engine &cpy ) = delete;

	public:
		Engine();     ~Engine();
		static Engine *getEngine();

	// ================================ ACCESSORS / MUTATORS
	public:
		engineState_e  getState();

		Camera2D    *getCamera();
		Viewport2D  *getViewport();

		Controller  *getController();

		CompManager *getCompManager();
		Entity      *getEntityByID( id_t id );

		void  setTimeScale( float timeScale );
		float getDeltaTime() const; // multiplied by the time scale

	// ================================ MUTEXED ACCESSORS
	private:
		void setState( engineState_e newState );

};

// ==================== ENGINE SHORTCUTS
// Shortcuts to the engine and its components

extern Engine      *GNG;
extern Viewport2D  *GVP;
extern Controller  *GCN;
extern CompManager *GCM;

extern float GDTS();

#endif // ENGINE_HPP