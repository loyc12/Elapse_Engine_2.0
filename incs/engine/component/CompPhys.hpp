#ifndef COMP_PHYS_HPP
# define COMP_PHYS_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_DYNAMIC true // NOTE : default dynamic state for the component

# define COMP_MIN_MASS EPS //  NOTE : default mass for the component
# define COMP_MIN_DRAG 0.0f // NOTE : default drag for the component
# define COMP_MIN_FRIC 0.0f // NOTE : default friction for the component
# define COMP_MIN_ELAS 0.0f // NOTE : default elasticity for the component

# define TEMP_VALUE 0.0f

class CompPhys : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		bool _dynamic; // NOTE : true if true, the object can be moved by forces ( gravity, collisions, etc. )

		float _mass; // NOTE : mass of the object
		float _drag; // NOTE : acceleration countering movement
		float _fric; // NOTE : like drag, but only when touching surfaces
		float _elas; // NOTE : elasticity of the object ( 0 = no bounce, 1 = full bounce )

	// ================================ CORE METHODS
		void onCpy( const CompPhys &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompPhys();

		CompPhys();
		CompPhys( Entity *Ntt,
			bool isActive  = COMP_DEF_ACTIVITY,
			bool isDynamic = COMP_DEF_DYNAMIC,

			float mass = COMP_MIN_MASS,
			float drag = COMP_MIN_DRAG,
			float fric = COMP_MIN_FRIC,
			float elas = COMP_MIN_ELAS
		);

		CompPhys( const CompPhys &rhs );
		CompPhys &operator=( const CompPhys &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_PHYSIC; }
		inline comp_type_e getType() const override { return COMP_PHYSIC; }

		inline bool isDynamic() const { return _dynamic; }
		inline bool setDynamic( bool isDynamic ){ _dynamic = isDynamic; return true; }

		// NOTE : checks if the parent entity exists and has the needed components ( position, movement )
		bool hasSisterComps() const override;

	// ================ MASS METHODS
		inline float getMass() const { return _mass; }
		inline bool voidMass(){ _mass = COMP_MIN_MASS; return true; }
		inline bool setMass(    float mass  ){ _mass = fmax( COMP_MIN_MASS, mass ); return true; }
		inline bool changeMass( float delta ){ _mass = fmax( COMP_MIN_MASS, _mass + delta); return true; }

	// ================ DRAG METHODS
		inline float getDrag() const { return _drag; }
		inline bool voidDrag(){ _drag = COMP_MIN_DRAG; return true; }
		inline bool setDrag(    float drag  ){ _drag = fmax( COMP_MIN_DRAG, drag); return true; }
		inline bool changeDrag( float delta ){ _drag = fmax( COMP_MIN_DRAG, _drag + delta); return true; }

		Vector2 applyDrag(); // NOTE : applies a force in the opposite direction of the velocity ( acc -= drag * velocity / mass )

	// ================ FRICTION METHODS
		inline float getFric() const { return _fric; }
		inline bool voidFric(){ _fric = COMP_MIN_FRIC; return true; }
		inline bool setFric(    float fric  ){ _fric = fmax( COMP_MIN_FRIC, fric); return true; }
		inline bool changeFric( float delta ){ _fric = fmax( COMP_MIN_FRIC, _fric + delta); return true; }

		Vector2 applyFriction( Vector2 surfaceNormal ); // NOTE : applies a force perpendicular to the normal of the surface ( acc -= friction * normal / mass )

	// ================ ELASTICITY METHODS
		inline float getElas() const { return _elas; }
		inline bool voidElas(){ _elas = COMP_MIN_ELAS; return true; }
		inline bool setElas(    float elas  ){ _elas = fmax( COMP_MIN_ELAS, elas); return true; }
		inline bool changeElas( float delta ){ _elas = fmax( COMP_MIN_ELAS, _elas + delta); return true; }

		Vector2 applyBounce( Vector2 surfaceNormal ); //  NOTE : applies a force along the normal of the surface (

	// ================ CALCULATED PROPERTIES METHODS
		// TODO : replace this with calculations based on the shape component
		float getAvgRad()  const; // NOTE : returns aproximates the radius of the object by using the graphic component ( circle radius )
		float getArea()    const; // NOTE : returns the approximate area of the 2D object ( = PI * radius^2 )
		float getDensity() const; // NOTE : returns the density of the object ( = mass / volume )

		float getLinearMomentum() const; // NOTE : returns the linear momentum of the object ( = mass * velocity )
		float getLinearEnergy()   const; // NOTE : returns the linear kinetic energy of the object ( = 1/2 * mass * velocity^2 )

		//float getAngularMomentum() const; // NOTE : returns the angular momentum of the object ( = mass * radius * velocity )
		//float getAngularEnergy()   const; // NOTE : returns the rotational kinetic energy of the object ( = 1/2 * mass * radius^2 * velocity^2 )

	// ================ FORCE METHODS

		// these return the resulting acceleration
		Vector2 getGravAccAt( Vector2 pos ) const; // NOTE : returns the gravity acceleration towards this object at a given point ( = mass * gravity / distance^2 )
		Vector2 applyForceTowards( float force, Vector2 dir ); // NOTE : applies a force to the object in a given direction ( acc += force * dir / mass

		Vector2 applyForce(       Vector2 force ); //     NOTE : applies a force to the object ( acc += force / mass )
		Vector2 applyBreakForce(  float breakForce ); //  NOTE : applies a force in the opposite direction of the velocity ( acc -= breakForce * velocity / mass )
		Vector2 applyBreakFactor( float breakFactor ); // NOTE : multiplies the acceleration by a given factor ( acc *= breakFactor )

		// TODO : make sure these make sense
		//Vector2 applyRotForce(       float rotForce ); //       NOTE : applies a rotational force to the object ( rotAcc += rotForce / mass )
		//Vector2 applyRotBreakForce(  float rotBreakForce ); //  NOTE : applies a rotational force in the opposite direction of the velocity ( rotAcc -= rotBreakForce * velocity / mass )
		//Vector2 applyRotBreakFactor( float rotBreakFactor ); // NOTE : applies a rotational force in the opposite direction of the velocity ( rotAcc *= rotBreakFactor )

		// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_PHYS_HPP

// TODO : implement the physics component