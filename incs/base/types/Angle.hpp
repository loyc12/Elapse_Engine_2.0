#ifndef ANGLE_HPP
# define ANGLE_HPP

# include <raylib.h>
# include "../core.hpp"

# include "./FixedPoint.hpp"

#ifndef ANGLE_HPP_FORWARD // forward declaration
# define ANGLE_HPP_FORWARD

	class Angle;

	namespace std
	{
		template <> struct is_integral<       Angle > : std::true_type {};
		template <> struct is_floating_point< Angle > : std::true_type {};
	}

#endif // ANGLE_HPP

class Angle
{
	#define TU template < typename U, typename = std::enable_if_t<( !std::is_same_v< U, Angle >&& ( std::is_integral_v< U >|| std::is_floating_point_v< U > ))>>

	#define SMOD( a, b ) Opfx::pmod( a, b )

	protected:
		fixed_t _angle; // NOTE : the angle stored in radians and between [0, TAU]

	// ============================ CONSTRUCTORS / DESTRUCTORS
	public:
		inline ~Angle(){};    inline Angle() : _angle( 0.0f ){} // defaults to an angle of 0

		// copy constructors
		inline Angle( const Angle   &a ){ _angle = a._angle; }
		inline Angle( const Vector2 &v ){ _angle = atan2f( v.y, v.x );}
		TU inline Angle( U angle )
		{
			if constexpr( std::is_floating_point_v< U >){ _angle = SMOD( angle, TAU ); } // angle in radians
			else /* std::is_integral_v< U > */ {   _angle = SMOD( angle * DtoR, TAU ); } // angle in degrees *
		}


		// copy assignment operators
		inline Angle operator=( const Angle   &a ){ _angle = a._angle; return *this; }
		inline Angle operator=( const Vector2 &v ){ _angle = atan2f( v.y, v.x ); return *this; }
		TU inline Angle operator=( const U &angle )
		{
			if constexpr( std::is_floating_point_v< U > ){ _angle = SMOD( angle, TAU ); } // angle in radians
			else /* std::is_integral_v< U > */ {    _angle = SMOD( angle * DtoR, TAU ); } // angle in degrees *
			return *this;
		}

		// ============================ ACCESSORS / MUTATORS
		inline fixed_t normalize() { _angle = SMOD( _angle, TAU ); return _angle; } // returns the angle in the range [0, TAU]

		inline fixed_t getRad() const { return _angle; } //                 returns the angle in the range [0, TAU]
		inline fixed_t getDeg() const { return _angle * RtoD; } //          returns the angle in the range [0, 360]
		inline fixed_t getOne() const { return _angle / TAU; } //           returns the angle in the range [0, 1]
		inline fixed_t getTwo() const { return ( _angle / PI ) - 1.0f; } // returns the angle in the range [-1, 1]

		inline fixed_t getRadPos() const { return _angle; } //              returns the angle in the range [0, TAU]
		inline fixed_t getRadCen() const { return _angle - PI; } //         returns the angle in the range [-PI, PI]
		inline fixed_t getRadNeg() const { return _angle - TAU; } //        returns the angle in the range [-TAU, 0]

		inline fixed_t getDegPos() const { return ( _angle * RtoD ); } //       returns the angle in the range [0, 360]
		inline fixed_t getDegCen() const { return ( _angle - PI ) * RtoD; } //  returns the angle in the range [-180, 180]
		inline fixed_t getDegNeg() const { return ( _angle - TAU ) * RtoD; } // returns the angle in the range [-360, 0]

		// returns the angle as a unit vector ( normalized )
		inline Vector2 getVec2() const
		{
			Vector2 v = {
				this->cos(),
				this->sin(),
			};
			return v;
		}

		inline void setTo( const Vector2 &v ){ _angle = atan2f( v.y, v.x ); } //           angle as a vector
		TU inline void setTo( U angle )
		{
			if constexpr( std::is_floating_point_v< U >){ _angle = SMOD( angle, TAU ); } //        angle in radians
			else /* std::is_integral_v< U > */ {     _angle = SMOD( angle * DtoR, TAU ); } // angle in degrees *
		}

		inline fixed_t cos()  const { return Opfx::cos( _angle ); }
		inline fixed_t sin()  const { return Opfx::sin( _angle ); }
		inline fixed_t tan()  const { return Opfx::tan( _angle ); }

		inline fixed_t cot()  const { return Opfx::cot( _angle ); }
		inline fixed_t sec()  const { return Opfx::sec( _angle ); }
		inline fixed_t csc()  const { return Opfx::csc( _angle ); }

		inline fixed_t acos() const { return Opfx::acos( _angle ); }
		inline fixed_t asin() const { return Opfx::asin( _angle ); }
		inline fixed_t atan() const { return Opfx::atan( _angle ); }

		inline operator Vector2() const { return getVec2(); } // Returns the angle as a vector

		TU inline operator U() const
		{
			if constexpr( std::is_floating_point_v< U > ){ return getRad(); } // angle in radians
			else /* std::is_integral_v< U > */ {           return getDeg(); } // angle in degrees *
		}

		// ============================ OPERATORS

		inline Angle operator+( const Angle   &a ) const { return Angle( SMOD( _angle + a._angle, TAU )); }
		inline Angle operator+( const Vector2 &v ) const { return Angle( SMOD( _angle + Angle( v )._angle, TAU )); }

		inline Angle operator-( const Angle   &a ) const { return Angle( SMOD( _angle - a._angle, TAU )); }
		inline Angle operator-( const Vector2 &v ) const { return Angle( SMOD( _angle - Angle( v )._angle, TAU )); }

		inline Angle operator*( const Angle   &a ) const { return Angle( SMOD( _angle * a._angle, TAU )); }
		inline Angle operator*( const Vector2 &v ) const { return Angle( SMOD( _angle * Angle( v )._angle, TAU )); }

		inline Angle operator/( const Angle   &a ) const { return Angle( SMOD( _angle / a._angle, TAU )); }
		inline Angle operator/( const Vector2 &v ) const { return Angle( SMOD( _angle / Angle( v )._angle, TAU )); }

		inline Angle operator%( const Angle   &a ) const { return Angle( SMOD( _angle,  a._angle )); }
		inline Angle operator%( const Vector2 &v ) const { return Angle( SMOD( _angle,  Angle( v )._angle )); }

		TU inline Angle operator+( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return Angle( SMOD( _angle + angle,  TAU )); } // angle in radians
			else /* std::is_integral_v< U > */ { return Angle( SMOD( _angle + ( angle * DtoR ), TAU )); } // angle in degrees *
		}
		TU inline Angle operator-( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return Angle( SMOD( _angle - angle,  TAU )); } // angle in radians
			else /* std::is_integral_v< U > */ { return Angle( SMOD( _angle - ( angle * DtoR ), TAU )); } // angle in degrees *
		}

		TU inline Angle operator*( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return Angle( SMOD( _angle * angle,  TAU )); } // angle in radians
			else /* std::is_integral_v< U > */ { return Angle( SMOD( _angle * ( angle * DtoR ), TAU )); } // angle in degrees *
		}
		TU inline Angle operator/( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return Angle( SMOD( _angle / angle,  TAU )); } // angle in radians
			else /* std::is_integral_v< U > */ { return Angle( SMOD( _angle / ( angle * DtoR ), TAU )); } // angle in degrees *
		}
		TU inline Angle operator%( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return Angle( SMOD( _angle,  angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return Angle( SMOD( _angle,  ( angle * DtoR ))); } // angle in degrees *
		}

		//Checks for relative position of the angles // TODO : check if all this is correct

		inline bool operator==( const Angle   &a ) const { return this->isEqual( a ); }
		inline bool operator==( const Vector2 &v ) const { return this->isEqual( Angle( v )); }

		TU inline bool operator==( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return this->isEqual( Angle( angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return    this->isEqual( Angle( angle * DtoR )); } // angle in degrees *
		}

		inline bool operator!=( const Angle   &a ) const { return this->isDiff( a ); }
		inline bool operator!=( const Vector2 &v ) const { return this->isDiff( Angle( v )); }

		TU inline bool operator!=( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return this->isDiff( Angle( angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return    this->isDiff( Angle( angle * DtoR )); } // angle in degrees *
		}

		// NOTE : checks if this a is left of this ( 0 to -180 degrees )
		inline bool operator<( const Angle   &a ) const { return this->isRightOf( a ); }
		inline bool operator<( const Vector2 &v ) const { return this->isRightOf( Angle( v )); }

		TU inline bool operator<( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return this->isRightOf( Angle( angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return    this->isRightOf( Angle( angle * DtoR )); } // angle in degrees *
		}

		// NOTE : checks if this a is right of this ( 0 to +180 degrees )
		inline bool operator>( const Angle   &a ) const { return this->isLeftOf( a ); }
		inline bool operator>( const Vector2 &v ) const { return this->isLeftOf( Angle( v )); }

		TU inline bool operator>( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return this->isLeftOf( Angle( angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return    this->isLeftOf( Angle( angle * DtoR )); } // angle in degrees *
		}

		// NOTE : checks if this a is parallel to this ( +90 or -90 degrees )
		inline bool operator|( const Angle   &a ) const { return this->isParallel( a ); }
		inline bool operator|( const Vector2 &v ) const { return this->isParallel( Angle( v )); }

		TU inline bool operator|( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return this->isParallel( Angle( angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return    this->isParallel( Angle( angle * DtoR )); } // angle in degrees *
		}

		// NOTE : checks if this a is perpendicular to this ( 0 or 180 degrees )
		inline bool operator^( const Angle   &a ) const { return this->isPerpend( a ); }
		inline bool operator^( const Vector2 &v ) const { return this->isPerpend( Angle( v )); }

		TU inline bool operator^( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return this->isPerpend( Angle( angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return    this->isPerpend( Angle( angle * DtoR )); } // angle in degrees *
		}

		// NOTE : checks if this a is opposite to this ( 180 degrees )
		inline bool operator&( const Angle   &a ) const { return this->isOpposite( a ); }
		inline bool operator&( const Vector2 &v ) const { return this->isOpposite( Angle( v )); }

		TU inline bool operator&( U angle ) const
		{
			if constexpr( std::is_floating_point_v< U > ){ return this->isOpposite( Angle( angle )); } // angle in radians
			else /* std::is_integral_v< U > */ { return    this->isOpposite( Angle( angle * DtoR )); } // angle in degrees *
		}

		inline bool isEqual(    const Angle &a ) const { return Opfx::abs( _angle - a._angle ) < EPS; } //  NOTE : checks if the angles are equal
		inline bool isDiff(     const Angle &a ) const { return Opfx::abs( _angle - a._angle ) > EPS; } //  NOTE : checks if the angles are not equal

		inline bool isLeftOf(   const Angle &a ) const { return Opfx::sin( a._angle - _angle ) < 0.0f; } // NOTE : checks if this is left of a ( -180 to 0 degrees )
		inline bool isSameDir(  const Angle &a ) const { return Opfx::cos( a._angle - _angle ) > 0.0f; } // NOTE : checks if this is in the same direction as a ( -90 to +90 degrees )

		inline bool isRightOf(  const Angle &a ) const { return Opfx::sin( a._angle - _angle ) > 0.0f; } // NOTE : checks if this is right of a ( 0 to +180 degrees )
		inline bool isDiffDir(  const Angle &a ) const { return Opfx::cos( a._angle - _angle ) < 0.0f; } // NOTE : checks if this is in the opposite direction as a ( 90 to 270 degrees )

		inline bool isOpposite( const Angle &a ) const { return Opfx::abs( a._angle - PI ) < EPS ; } //     NOTE : checks if this is opposite to a ( 180 degrees )
		inline bool isComplem(  const Angle &a ) const { return Opfx::abs( a._angle + _angle ) < EPS ; } // NOTE : checks if this is complementary to a ( a1 == -a2 )

		inline bool isParallel( const Angle &a ) const { return Opfx::abs( Opfx::sin( a._angle - _angle )) < EPS; } // NOTE : checks if this is parallel to a ( -90 or 90 degrees )
		inline bool isPerpend(  const Angle &a ) const { return Opfx::abs( Opfx::cos( a._angle - _angle )) < EPS; } // NOTE : checks if this is perpendicular to a ( 0 or 180 degrees )

		inline Angle getAverage(   const Angle &a ) const { return Angle( SMOD(( _angle + a._angle ) / 2.0f, TAU )); } // returns the average ( bisection ) of two angles
		inline Angle getDist(      const Angle &a ) const { return Angle( SMOD( a._angle - _angle, TAU )); } //           returns the true angular distance between two angles ( order dependant )
		inline Angle getShortDist( const Angle &a ) const { return Angle( Opfx::abs( a._angle - _angle )); } //    returns the smallest angular distance between two angles
		inline Angle getLongDist(  const Angle &a ) const { return getShortDist( a ).getComplement(); } //                       returns the largest angular distance between two angles

		// Moves the angle by 45 degrees increments in the given direction ( might conflict with the stream operator )
		//inline Angle operator>>( int n ){ _angle = SMOD( _angle + ( n * ( PI / 4.0f )), TAU ); return *this; } // rotate the angle clockwise
		//inline Angle operator<<( int n ){ _angle = SMOD( _angle - ( n * ( PI / 4.0f )), TAU ); return *this; } // rotate the angle counter-clockwise

		inline Angle operator+() const { return Angle( _angle ); } // returns the angle
		inline Angle operator-() const { return getComplement(); } // return the complementary angle ( -a )
		inline Angle operator!() const { return getOpposite(); } //   returns the opposite angle ( + 180 degrees )

		inline Angle getComplement() const { return Angle( SMOD( -_angle, TAU )); } //      return the flips the angle around 0 ( ex : 37 -> -37)
		inline Angle getOpposite()   const { return Angle( SMOD(  _angle + PI, TAU )); } // returns the opposite angle

		inline Angle getPerpend()  const { return getPerpendP(); } //                                      returns a perpendicular angle
		inline Angle getPerpendP() const { return Angle( SMOD( _angle + ( PI / 2.0f ), TAU )); } // returns the clockwise perpendicular angle
		inline Angle getPerpendN() const { return Angle( SMOD( _angle - ( PI / 2.0f ), TAU )); } // returns the counter clockwise perpendicular angle

		// increments / decrements the angle by 0.1 degrees
		inline Angle operator++(){ _angle = SMOD( _angle + ( 0.1f * DtoR ), TAU ); return *this; }
		inline Angle operator--(){ _angle = SMOD( _angle - ( 0.1f * DtoR ), TAU ); return *this; }

		// increments / decrements the angle by 0.1 degrees and returns the old value
		inline Angle operator++( int ){ Angle a = *this; _angle = SMOD( _angle + ( 0.1f * DtoR ), TAU ); return a; }
		inline Angle operator--( int ){ Angle a = *this; _angle = SMOD( _angle - ( 0.1f * DtoR ), TAU ); return a; }

		inline Angle operator+=( const Angle   &a ){ _angle = SMOD( _angle + a._angle, TAU );          return *this; }
		inline Angle operator+=( const Vector2 &v ){ _angle = SMOD( _angle + Angle( v )._angle, TAU ); return *this; }

		TU inline Angle operator+=( U angle )
		{
			if constexpr( std::is_floating_point_v< U >){   _angle = SMOD( _angle + angle, TAU ); } // angle in radians
			else /* std::is_integral_v< U > */ { _angle = SMOD( _angle + ( angle * DtoR ), TAU ); } // angle in degrees *
			return *this;
		}

		inline Angle operator-=( const Angle   &a ){ _angle = SMOD( _angle - a._angle, TAU );          return *this; }
		inline Angle operator-=( const Vector2 &v ){ _angle = SMOD( _angle - Angle( v )._angle, TAU ); return *this; }

		TU inline Angle operator-=( U angle )
		{
			if constexpr( std::is_floating_point_v< U >){   _angle = SMOD( _angle - angle, TAU ); } // angle in radians
			else /* std::is_integral_v< U > */ { _angle = SMOD( _angle - ( angle * DtoR ), TAU ); } // angle in degrees *
			return *this;
		}

		inline Angle operator*=( const Angle   &a ){ _angle = SMOD( _angle * a._angle, TAU );          return *this; }
		inline Angle operator*=( const Vector2 &v ){ _angle = SMOD( _angle * Angle( v )._angle, TAU ); return *this; }

		TU inline Angle operator*=( U angle )
		{
			if constexpr( std::is_floating_point_v< U >){   _angle = SMOD( _angle * angle, TAU ); } // angle in radians
			else /* std::is_integral_v< U > */ { _angle = SMOD( _angle * ( angle * DtoR ), TAU ); } // angle in degrees *
			return *this;
		}

		inline Angle operator/=( const Angle   &a ){ _angle = SMOD( _angle / a._angle, TAU );          return *this; }
		inline Angle operator/=( const Vector2 &v ){ _angle = SMOD( _angle / Angle( v )._angle, TAU ); return *this; }

		TU inline Angle operator/=( U angle )
		{
			if constexpr( std::is_floating_point_v< U >){   _angle = SMOD( _angle / angle, TAU ); } // angle in radians
			else /* std::is_integral_v< U > */ { _angle = SMOD( _angle / ( angle * DtoR ), TAU ); } // angle in degrees *
			return *this;
		}

		inline Angle operator%=( const Angle   &a ){ _angle = SMOD( _angle, a._angle );          return *this; }
		inline Angle operator%=( const Vector2 &v ){ _angle = SMOD( _angle, Angle( v )._angle ); return *this; }
		TU inline Angle operator%=( U angle )
		{
			if constexpr( std::is_floating_point_v< U >){  _angle = SMOD( _angle, angle ); } // angle in radians
			else /* std::is_integral_v< U > */ { _angle = SMOD( _angle, ( angle * DtoR )); } // angle in degrees *
			return *this;
		}

		// ============================ FRIEND METHODS
		friend std::ostream &operator<<( std::ostream &os, const Angle &a ){ os << a.getDeg() << " degrees"; return os;}
		friend std::string to_string( const Angle &a ){ return to_string( a.getDeg() ); }

		// ============================ STATIC FUNCTIONS

		static inline fixed_t normalizeRad( fixed_t angle ) { return SMOD( angle, TAU ); } //    returns the angle in the range [0, TAU]
		static inline fixed_t normalizeDeg( fixed_t angle ) { return SMOD( angle, 360.0f ); } // returns the angle in the range [0, 360]

		#undef TU
		#undef SMOD
};




// ============================ DEFAULT FANGLE TYPE ( only one possible for now )

typedef Angle angle_t;

#endif // ANGLE_HPP