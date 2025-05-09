#ifndef COMP_COLLIDE_HPP
# define COMP_COLLIDE_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_COLLIDE true // NOTE : default activity for the component
# define COMP_DEF_HITRAD 8 // NOTE : default hit radius for the component

class CompCollide : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		bool  _collidable; // NOTE : allows for wallhacks and triggers
		float _hitRad; //    NOTE : radius of the hitbox

	// ================================ CORE METHODS
		void onCpy( const CompCollide &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompCollide();

		CompCollide();
		CompCollide( Entity *Ntt,
			bool  isActive = COMP_DEF_ACTIVITY,
			bool isCollide = COMP_DEF_COLLIDE,
			float hitRad   = COMP_DEF_HITRAD
		);

		CompCollide( const CompCollide &rhs );
		CompCollide &operator=( const CompCollide &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_COLLIDE; }
		inline comp_type_e getType() const override { return COMP_COLLIDE; }

		inline bool isCollidable() const { return _collidable; }
		inline bool setCollidable( bool isCollide ){ _collidable = isCollide; return true; }

		// NOTE : checks if the parent entity exists and has the needed components ( position )
		bool hasSisterComps() const override;

	// ================ RADIUS METHODS
		inline float getHitRad() const { return _hitRad; }
		inline bool voidHitRad(){ _hitRad = COMP_DEF_HITRAD; return true; }

		inline bool setHitRad(    float hitRad ){ _hitRad = fmax( 0.0f, hitRad); return true; }
		inline bool changeHitRad( float delta  ){ _hitRad = fmax( 0.0f, _hitRad + delta); return true; }

	// ================================ COLLISION METHODS
		// NOTE : checks if the component is colliding with a point ( with or without its own collision radius )
		bool isOverlaping( Vector2 pos, float otherRad = 0 ) const;

		// NOTE : checks if two components are colliding
		bool isOverlaping( CompCollide *other ) const;
		bool isOverlaping( Entity *other ) const;
		bool isOverlaping( id_t id ) const;

		// NOTE : returns the vector between the two components
		Vector2 getCollisionVec( CompCollide *other ) const;
		Vector2 collideWith( CompCollide *other );

	// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_COLLIDE_HPP

// TODO : implement the collision component