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

		fixed_t _mass; // NOTE : mass of the object
		fixed_t _drag; // NOTE : acceleration countering movement
		fixed_t _fric; // NOTE : like drag, but only when touching surfaces
		fixed_t _elas; // NOTE : elasticity of the object ( 0 = no bounce, 1 = full bounce )

	// ================================ CORE METHODS
		void onCpy( const CompPhys &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompPhys();

		CompPhys();
		CompPhys( Entity *Ntt,
			bool  isActive = COMP_DEF_ACTIVITY,
			bool isDynamic = COMP_DEF_DYNAMIC,

			fixed_t mass = COMP_MIN_MASS,
			fixed_t drag = COMP_MIN_DRAG,
			fixed_t fric = COMP_MIN_FRIC,
			fixed_t elas = COMP_MIN_ELAS
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
		inline fixed_t getMass() const { return _mass; }
		inline bool voidMass(){ _mass = COMP_MIN_MASS; return true; }
		inline bool setMass(   fixed_t mass  ){ _mass = Opfx::max( mass,          COMP_MIN_MASS ); return true; }
		inline bool moveMass(  fixed_t delta ){ _mass = Opfx::max( _mass + delta, COMP_MIN_MASS ); return true; }
		inline bool scaleMass( fixed_t scale ){ _mass = Opfx::max( _mass * scale, COMP_MIN_MASS ); return true; }

	// ================ DRAG METHODS
		inline fixed_t getDrag() const { return _drag; }
		inline bool voidDrag(){ _drag = COMP_MIN_DRAG; return true; }
		inline bool setDrag(   fixed_t drag  ){ _drag = Opfx::max( drag,          COMP_MIN_DRAG ); return true; }
		inline bool moveDrag(  fixed_t delta ){ _drag = Opfx::max( _drag + delta, COMP_MIN_DRAG ); return true; }
		inline bool scaleDrag( fixed_t scale ){ _drag = Opfx::max( _drag * scale, COMP_MIN_DRAG ); return true; }

		vec2_t applyDrag(); // NOTE : applies a force in the opposite direction of the velocity ( acc -= drag * velocity / mass )

	// ================ FRICTION METHODS
		inline fixed_t getFric() const { return _fric; }
		inline bool voidFric(){ _fric = COMP_MIN_FRIC; return true; }
		inline bool setFric(   fixed_t fric  ){ _fric = Opfx::max( fric,          COMP_MIN_FRIC ); return true; }
		inline bool moveFric(  fixed_t delta ){ _fric = Opfx::max( _fric + delta, COMP_MIN_FRIC ); return true; }
		inline bool scaleFric( fixed_t scale ){ _fric = Opfx::max( _fric * scale, COMP_MIN_FRIC ); return true; }

		vec2_t applyFriction( vec2_t surfaceNormal ); // NOTE : applies a force perpendicular to the normal of the surface ( acc -= friction * normal / mass )

	// ================ ELASTICITY METHODS
		inline fixed_t getElas() const { return _elas; }
		inline bool voidElas(){ _elas = COMP_MIN_ELAS; return true; }
		inline bool setElas(   fixed_t elas  ){ _elas = Opfx::max( elas,          COMP_MIN_ELAS ); return true; }
		inline bool moveElas(  fixed_t delta ){ _elas = Opfx::max( _elas + delta, COMP_MIN_ELAS ); return true; }
		inline bool scaleElas( fixed_t scale ){ _elas = Opfx::max( _elas * scale, COMP_MIN_ELAS ); return true; }

		vec2_t applyBounce( vec2_t surfaceNormal ); //  NOTE : applies a force along the normal of the surface (

	// ================ CALCULATED PROPERTIES METHODS
		// TODO : replace this with calculations based on the shape component
		fixed_t getAvgRad()  const; // NOTE : returns aproximates the radius of the object by using the graphic component ( circle radius )
		fixed_t getArea()    const; // NOTE : returns the approximate area of the 2D object ( = PI * radius^2 )
		fixed_t getDensity() const; // NOTE : returns the density of the object ( = mass / volume )

		fixed_t getLinearMomentum() const; // NOTE : returns the linear momentum of the object ( = mass * velocity )
		fixed_t getLinearEnergy()   const; // NOTE : returns the linear kinetic energy of the object ( = 1/2 * mass * velocity^2 )

		//fixed_t getAngularMomentum() const; // NOTE : returns the angular momentum of the object ( = mass * radius * velocity )
		//fixed_t getAngularEnergy()   const; // NOTE : returns the rotational kinetic energy of the object ( = 1/2 * mass * radius^2 * velocity^2 )

	// ================ FORCE METHODS

		// these return the resulting acceleration
		vec2_t getGravAccAt( vec2_t pos ) const; // NOTE : returns the gravity acceleration towards this object at a given point ( = mass * gravity / distance^2 )
		vec2_t applyForceTowards( fixed_t force, vec2_t dir ); // NOTE : applies a force to the object in a given direction ( acc += force * dir / mass

		vec2_t applyForce(       vec2_t force ); //     NOTE : applies a force to the object ( acc += force / mass )
		vec2_t applyBreakForce(  fixed_t breakForce ); //  NOTE : applies a force in the opposite direction of the velocity ( acc -= breakForce * velocity / mass )
		vec2_t applyBreakFactor( fixed_t breakFactor ); // NOTE : applies an acceleration to cancel out a given portion of the current velocity ( acc = -breakFactor * velocity )

		// TODO : make sure these make sense
		//vec2_t applyRotForce(       fixed_t rotForce ); //       NOTE : applies a rotational force to the object ( rotAcc += rotForce / mass )
		//vec2_t applyRotBreakForce(  fixed_t rotBreakForce ); //  NOTE : applies a rotational force in the opposite direction of the velocity ( rotAcc -= rotBreakForce * velocity / mass )
		//vec2_t applyRotBreakFactor( fixed_t rotBreakFactor ); // NOTE : applies a rotational force in the opposite direction of the velocity ( rotAcc *= rotBreakFactor )

		// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_PHYS_HPP

// TODO : implement the physics component