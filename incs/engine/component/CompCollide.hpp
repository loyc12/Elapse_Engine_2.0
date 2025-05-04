#ifndef COMP_COLLIDE_HPP
# define COMP_COLLIDE_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_HITRAD 8 // NOTE : default hit radius for the component

class CompCollide : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		float _hitRad; // NOTE : radius of the hitbox

	// ================================ CORE METHODS
		void onCpy( const CompCollide &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompCollide();

		CompCollide();
		CompCollide( Entity *Ntt,
			bool isActive = COMP_DEF_ACTIVITY,
			float hitRad  = COMP_DEF_HITRAD
		);

		CompCollide( const CompCollide &rhs );
		CompCollide &operator=( const CompCollide &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_COLLIDE; }
		inline comp_type_e getType() const override { return COMP_COLLIDE; } // NOTE : overide this in derived classes

	// ================ RADIUS METHODS
		inline float getHitRad() const { return _hitRad; }
		inline bool voidHitRad(){ _hitRad = COMP_DEF_HITRAD; return true; }

		inline bool setHitRad(    float hitRad ){ _hitRad = min( 0.0f, hitRad); return true; }
		inline bool changeHitRad( float delta  ){ _hitRad = min( 0.0f, _hitRad + delta); return true; }

	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompCollide
};

#endif // COMP_COLLIDE_HPP

// TODO : implement the collision component