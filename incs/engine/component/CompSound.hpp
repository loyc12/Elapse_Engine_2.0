#ifndef COMP_SOUND_HPP
# define COMP_SOUND_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_SOUND "UNDEFINED" // NOTE : default sound for the component

class CompSound : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		string _soundPath; // NOTE : path to the sound file

	// ================================ CORE METHODS
		void onCpy( const CompSound &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompSound();

		CompSound();
		CompSound( Entity *Ntt,
			bool isActive    = COMP_DEF_ACTIVITY,
			string soundPath = COMP_DEF_SOUND
		);

		CompSound( const CompSound &rhs );
		CompSound &operator=( const CompSound &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_SOUND; }
		inline comp_type_e getType() const override { return COMP_SOUND; } // NOTE : overide this in derived classes

	// ================ SOUND METHODS
		inline string getSoundPath() const { return _soundPath; }
		inline bool voidSoundPath(){ _soundPath = COMP_DEF_SOUND; return true; }
		inline bool setSoundPath(   string soundPath ){ _soundPath  = soundPath; return true; }
		inline bool addToSoundPath( string soundPath ){ _soundPath += soundPath; return true; }

		bool playSound(); //                   NOTE : plays the sound at the given path
		bool playSound( string soundPath ); // NOTE : switches to and plays the sound at the given path


	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompSound
};

#endif // COMP_SOUND_HPP

// TODO : implement the sound component