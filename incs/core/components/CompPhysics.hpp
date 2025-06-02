#ifndef COMP_PHYSICS_HPP
# define COMP_PHYSICS_HPP

# include "./CompBase.hpp"

# define COMP_DEF_MASS 1.0f // NOTE : default mass value
# define COMP_DEF_FRIC 0.5f // NOTE : default friction coefficient
# define COMP_DEF_ELAS 0.5f // NOTE : default elasticity coefficient

class CompPhysics : public CompBase
{
	public: // NOTE : public to allow access from EntityMngr
	// ================================ ATTRIBUTES
		fixed_t _mass;
		fixed_t _fric; // NOTE : friction coefficient
		fixed_t _elas; // NOTE : elasticity coefficient

	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ~CompPhysics(){}
		inline CompPhysics( id_t NttID = 0, fixed_t mass = COMP_DEF_MASS, fixed_t fric = COMP_DEF_FRIC, fixed_t elas = COMP_DEF_ELAS ) :
			CompBase( NttID ), _mass( mass ), _fric( fric ), _elas( elas ){}

		inline CompPhysics( const CompPhysics &cpy ) : CompBase( cpy ){ *this = cpy; }
		inline CompPhysics &operator=( const CompPhysics &cpy )
		{
			if( this != &cpy )
			{
				_mass	= cpy._mass;
				_fric = cpy._fric;
				_elas = cpy._elas;
			}
			return *this;
		}

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getType(){ return CT_PHYSICS; }

		inline fixed_t getMass() const { return _mass; }
		inline void setMass(   fixed_t   mass ){ _mass = Opfx::max( EPS,  mass ); }
		inline void moveMass(  fixed_t  delta ){ _mass = Opfx::max( EPS, _mass + delta ); }
		inline void scaleMass( fixed_t factor ){ _mass = Opfx::max( EPS, _mass * factor ); }

		inline fixed_t getElasticity() const { return _elas; }
		inline void setElasticity(   fixed_t   elas ){ _elas = Opfx::clmp(  elas,          0.0f, 1.0f ); }
		inline void moveElasticity(  fixed_t  delta ){ _elas = Opfx::clmp( _elas + delta,  0.0f, 1.0f ); }
		inline void scaleElasticity( fixed_t factor ){ _elas = Opfx::clmp( _elas * factor, 0.0f, 1.0f ); }

		inline fixed_t getFriction() const { return _fric; }
		inline void setFriction(   fixed_t   fric ){ _fric = Opfx::clmp(  fric,          0.0f, 1.0f ); }
		inline void moveFriction(  fixed_t  delta ){ _fric = Opfx::clmp( _fric + delta,  0.0f, 1.0f ); }
		inline void scaleFriction( fixed_t factor ){ _fric = Opfx::clmp( _fric * factor, 0.0f, 1.0f ); }

		// ================================ FRIEND METHODS
		inline friend std::ostream &operator<<( std::ostream &os, const CompPhysics &cp )
		{
			os << "CompPhysics : [ ID: " << cp._id << ", mass: " << cp._mass << ", friction: " << cp._fric << ", elasticity: " << cp._elas << " ]";
			return os;
		}
};

#endif // COMP_PHYSICS_HPP