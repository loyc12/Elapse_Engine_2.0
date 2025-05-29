#ifndef COMP_PHYSICS_HPP
# define COMP_PHYSICS_HPP

# include "./CompBase.hpp"

# define COMP_DEF_MASS 1.0f // NOTE : default mass value
# define COMP_DEF_FRIC 0.5f // NOTE : default friction coefficient
# define COMP_DEF_ELAS 0.5f // NOTE : default elasticity coefficient

class CompPhysics : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		fixed_t _mass;
		fixed_t _fric; // NOTE : friction coefficient
		fixed_t _elas; // NOTE : elasticity coefficient


	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ~CompPhysics(){}
		inline CompPhysics( id_t NttID = 0, fixed_t mass = COMP_DEF_MASS, fixed_t fric = COMP_DEF_FRIC, fixed_t elas = COMP_DEF_ELAS ) :
			CompBase( NttID ), _mass( mass ), _fric( fric ), _elas( elas ){}

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getType(){ return CT_PHYSICS; }

		inline fixed_t getMass() const { return _mass; }
		inline void setMass(   fixed_t   mass ){ _mass = Opfx::max( 0,  mass ); }
		inline void moveMass(  fixed_t  delta ){ _mass = Opfx::max( 0, _mass + delta ); }
		inline void scaleMass( fixed_t factor ){ _mass = Opfx::max( 0, _mass * factor ); }

		inline fixed_t getElasticity() const { return _elas; }
		inline void setElasticity(   fixed_t   elas ){ _elas = Opfx::clmp(  elas,          0.0f, 1.0f ); }
		inline void moveElasticity(  fixed_t  delta ){ _elas = Opfx::clmp( _elas + delta,  0.0f, 1.0f ); }
		inline void scaleElasticity( fixed_t factor ){ _elas = Opfx::clmp( _elas * factor, 0.0f, 1.0f ); }

		inline fixed_t getFriction() const { return _fric; }
		inline void setFriction(   fixed_t   fric ){ _fric = Opfx::clmp(  fric,          0.0f, 1.0f ); }
		inline void moveFriction(  fixed_t  delta ){ _fric = Opfx::clmp( _fric + delta,  0.0f, 1.0f ); }
		inline void scaleFriction( fixed_t factor ){ _fric = Opfx::clmp( _fric * factor, 0.0f, 1.0f ); }

	// ================================ TICK METHODS

		// TODO : move this logic to the EntityMngr, so that it can run in batches
		bool applyGravity( vec2_t gravity = { 0.0f, 9.81f } );
	//bool applyFriction( vec2_t surfaceNormal, fixed_t surfaceFric = COMP_DEF_FRIC );
	//bool applyBounce(   vec2_t surfaceNormal, fixed_t surfaceElas = COMP_DEF_ELAS );
};

#endif // COMP_PHYSICS_HPP