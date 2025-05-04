#ifndef COMP_SCRIPT_HPP
# define COMP_SCRIPT_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_SCRIPT "UNDEFINED" // NOTE : default sound for the component

class CompSound : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		string _scriptPath; // NOTE : path to the sound file

	// ================================ CORE METHODS
		void onCpy( const CompSound &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompSound();

		CompSound();
		CompSound( Entity *Ntt,
			bool isActive     = COMP_DEF_ACTIVITY,
			string scriptPath = COMP_DEF_SCRIPT
		);

		CompSound( const CompSound &rhs );
		CompSound &operator=( const CompSound &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_SCRIPT; }
		inline comp_type_e getType() const override { return COMP_SCRIPT; } // NOTE : overide this in derived classes

	// ================ SOUND METHODS
		inline string getScriptPath() const { return _scriptPath; }
		inline bool voidScriptPath(){ _scriptPath = COMP_DEF_SCRIPT; return true; }
		inline bool setScriptPath(   string scriptPath ){ _scriptPath  = scriptPath; return true; }
		inline bool addToScriptPath( string scriptPath ){ _scriptPath += scriptPath; return true; }

		bool runScript(); //                    NOTE : runs the script at the given path
		bool runScript( string scriptPath ); // NOTE : switches to and runs the script at the given path

	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompSound
};

#endif // COMP_SCRIPT_HPP

// TODO : implement the script component