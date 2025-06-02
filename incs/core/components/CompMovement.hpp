#ifndef COMP_MOVEMENT_HPP
# define COMP_MOVEMENT_HPP

# include "./CompBase.hpp"

class CompMovement : public CompBase
{
	public: // NOTE : public to allow access from EntityMngr
	// ================================ ATTRIBUTES
		vec2_t  _lVel; // NOTE : linear velocity
		vec2_t  _lAcc; // NOTE : linear acceleration
		angle_t _rVel; // NOTE : rotational velocity
		angle_t _rAcc; // NOTE : rotational acceleration

	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ~CompMovement(){}
		inline CompMovement( id_t NttID = 0, vec2_t lVel = { 0, 0 }, vec2_t lAcc = { 0, 0 }, angle_t rVel = 0, angle_t rAcc = 0 ) :
			CompBase( NttID ), _lVel( lVel ), _lAcc( lAcc ), _rVel( rVel ), _rAcc( rAcc ){ flog( NttID ); }

		inline CompMovement( const CompMovement &cpy ) : CompBase( cpy ){ *this = cpy; }
		inline CompMovement &operator=( const CompMovement &cpy )
		{
			if( this != &cpy )
			{
				_lVel = cpy._lVel;
				_lAcc = cpy._lAcc;
				_rVel = cpy._rVel;
				_rAcc = cpy._rAcc;
			}
			return *this;
		}

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getType(){ return CT_MOVEMENT; }

		inline vec2_t getVelocity() const { return _lVel; }
		inline void  setVelocity( vec2_t  lVel ){ _lVel  = lVel; }
		inline void moveVelocity( vec2_t delta ){ _lVel += delta; }

		inline vec2_t getAcceleration() const { return _lAcc; }
		inline void  setAcceleration( vec2_t  lAcc ){ _lAcc  = lAcc; }
		inline void moveAcceleration( vec2_t delta ){ _lAcc += delta; }

		inline angle_t getRotVelocity() const { return _rVel; }
		inline void  setRotVelocity( angle_t  rVel ){ _rVel  = rVel; }
		inline void moveRotVelocity( angle_t delta ){ _rVel += delta; }

		inline angle_t getRotAcceleration() const { return _rAcc; }
		inline void  setRotAcceleration( angle_t  rAcc ){ _rAcc  = rAcc; }
		inline void moveRotAcceleration( angle_t delta ){ _rAcc += delta; }

		// ================================ FRIEND METHODS
		inline friend std::ostream &operator<<( std::ostream &os, const CompMovement &cm )
		{
			os << "CompMovement : [ ID: " << cm._id << ", lVel: " << cm._lVel << ", lAcc: " << cm._lAcc << ", rVel: " << cm._rVel << ", rAcc: " << cm._rAcc << " ]";
			return os;
		}
};

#endif // COMP_MOVEMENT_HPP