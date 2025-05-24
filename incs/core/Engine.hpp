#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "../base.hpp"

# include "./ScreenMngr.hpp"
//# include "./EventMngr.hpp"
//# include "./EntityMngr.hpp"


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
	ES_RUNNING, // currently running

} engineState_e;

# define MUTEX_LOCK( mtx ) std::lock_guard< std::mutex > lock( mtx )

class Engine
{
	// ================================ ATTRIBUTES
	private:
		fixed_t _DT; // delta time
		fixed_t _TS; // time scale

		ScreenMngr *_screenMngr2D;
	//EventMngr  *_eventMngr;
	//EntityMngr *_entityMngr;

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
		void runStep();
			void refreshScreen();

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
		inline bool isEngineClosed(){  MUTEX_LOCK( mtx_state ); return _state == ES_CLOSED; }
		inline bool isEngineReady(){   MUTEX_LOCK( mtx_state ); return _state == ES_INITIALIZED; }
		inline bool isEngineStarted(){ MUTEX_LOCK( mtx_state ); return _state == ES_STARTED; }
		inline bool isEngineRunning(){ MUTEX_LOCK( mtx_state ); return _state == ES_RUNNING; }

		inline bool isTimePaused(){ return ( _TS == 0 ); }

		inline Camera2D   *getCamera(){     return _screenMngr2D->getCamera(); }
		inline ScreenMngr *getScreenMngr(){ return _screenMngr2D; }

		//inline inputs_s   &getLatestInputs(){   return _eventMngr->getLatestInputs(); }
		//inline inputs_s   &getPreviousInputs(){ return _eventMngr->getPreviousInputs(); }
		//inline EventMngr  *getEventMngr(){      return _eventMngr; }

		//inline Entity     *getEntity( id_t id ){ return _entityMngr->getEntity( id ); }
		//inline EntityMngr *getEntityMngr(){      return _entityMngr; }

		inline fixed_t updateDeltaTime() { _DT = GetFrameTime(); return _DT; }
		inline fixed_t getDeltaTimeScaled() const { return _DT * _TS; }

		fixed_t setTimeScale( fixed_t timeScale );
		bool    canEngineTick();

	// ================================ MUTEXED ACCESSORS / MUTATORS
	private:
		inline engineState_e getState(){                MUTEX_LOCK( mtx_state ); return _state; }
		inline void setState( engineState_e newState ){ MUTEX_LOCK( mtx_state ); _state = newState; }

};

// ==================== GLOBAL ENGINE SHORTCUTS
// Shortcuts to the engine and its components

extern Engine     *GetNG;
extern ScreenMngr *GetScrnM;
//extern EventMngr  *GetEvntM;
//extern EntityMngr *GetNttM;

extern fixed_t    GDTS(); // returns _DT * _TS ( aka the delta time scaled )
//extern inputs_s   &GIN();

#endif // ENGINE_HPP