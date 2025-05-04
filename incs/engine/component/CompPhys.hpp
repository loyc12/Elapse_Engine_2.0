#ifndef COMP_PHYS_HPP
# define COMP_PHYS_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_MIN_MASS EPS // NOTE : default mass for the component

class CompPhys : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		bool  _Dynamic; // NOTE : true if the object is dynamic ( can be moved by forces )
		float _mass; //    NOTE : mass of the object
		float _drag; //    NOTE : acceleration countering movement
		float _fric; //    NOTE : like drag, but only when touching surfaces
		float _elas; //    NOTE : elasticity of the object ( 0 = no bounce, 1 = full bounce )

	// ================================ CORE METHODS
		void onCpy( const CompPhys &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompPhys();

		CompPhys();
		CompPhys( Entity *Ntt,
			bool isActive  = COMP_DEF_ACTIVITY,
			bool isDynamic = true,
			float mass     = COMP_MIN_MASS,
			float drag     = 0,
			float fric     = 0,
			float elas     = 0 );

		CompPhys( const CompPhys &rhs );
		CompPhys &operator=( const CompPhys &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_PHYSIC; }
		inline comp_type_e getType() const override { return COMP_PHYSIC; } // NOTE : overide this in derived classes

	// ================ MASS METHODS
		inline float getMass() const {                 return _mass; }
		inline bool voidMass(){ _mass = COMP_MIN_MASS; return true; }
		inline bool setMass(    float mass  ){ _mass = min( COMP_MIN_MASS, mass );  return true; }
		inline bool changeMass( float delta ){ _mass = min( COMP_MIN_MASS, _mass + delta); return true; }

		Vector2 applyGravity( Vector2 pullDir, float gravity ); // NOTE : applies a force in the direction of the gravity ( returns the resulting acceleration )

	// ================ DRAG METHODS
		inline float getDrag() const {     return _drag; }
		inline bool voidDrag(){ _drag = 0; return true; }
		inline bool setDrag(    float drag  ){ _drag = min( 0.0f, drag);  return true; }
		inline bool changeDrag( float delta ){ _drag = min( 0.0f, _drag + delta); return true; }

		Vector2 applyDrag(); // NOTE : applies a force in the opposite direction of the velocity ( returns the resulting acceleration )

	// ================ FRICTION METHODS
		inline float getFric() const {     return _fric; }
		inline bool voidFric(){ _fric = 0; return true; }
		inline bool setFric(    float fric  ){ _fric = min( 0.0f, fric);  return true; }
		inline bool changeFric( float delta ){ _fric = min( 0.0f, _fric + delta); return true; }

		Vector2 applyFriction( Vector2 normal ); // NOTE : applies a force perpendicular to the normal of the surface ( returns the resulting acceleration )

	// ================ ELASTICITY METHODS
		inline float getElas() const {     return _elas; }
		inline bool voidElas(){ _elas = 0; return true; }
		inline bool setElas(    float elas  ){ _elas = min( 0.0f, elas);  return true; }
		inline bool changeElas( float delta ){ _elas = min( 0.0f, _elas + delta); return true; }

		Vector2 applyBounce( Vector2 normal ); //  NOTE : applies a force along the normal of the surface ( returns the resulting acceleration )

	// ================ CALCULATION METHODS
		float getVolume() const; //  NOTE : returns the approximate volume of the object ( radius^2 * PI ) // TODO : add a shape component
		float getDensity() const; // NOTE : returns the density of the object ( mass / volume )
		float getInertia() const; // NOTE : returns the inertia of the object ( mass * radius^2 / 2 )
		float getMoment() const; //  NOTE : returns the moment of inertia of the object ( mass * radius^2 / 2 ) // TODO : add a shape component

		Vector2 applyForce( Vector2 force ); //           NOTE : applies a force to the object ( returns the resulting acceleration )
		Vector2 applyBreakForce( float breakForce ); //   NOTE : applies a force in the opposite direction of the velocity ( returns the resulting acceleration )
		Vector2 applyBreakFactor( float breakFactor ); // NOTE : applies a force in the opposite direction of the velocity ( returns the resulting acceleration )

	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompPhys
};

#endif // COMP_PHYS_HPP

// TODO : implement the physics component