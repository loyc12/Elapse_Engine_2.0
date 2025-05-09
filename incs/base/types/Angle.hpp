#ifndef ANGLE_HPP
# define ANGLE_HPP

# include <raylib.h>
# include "../core.hpp"

# define ANG_MODULUS( a, b ) Operate< float >::pmod( a, b )

typedef float angle_scalar_t;

class Angle
{
	protected: angle_scalar_t _angle; // NOTE : the angle stored in radians and between [0, TAU]

	// ============================ CONSTRUCTORS / DESTRUCTORS
	public:
		inline ~Angle(){};    inline Angle() : _angle( 0.0f ){} // defaults to an angle of 0

		// copy constructors
		inline Angle( const Angle   &a ){ _angle = a._angle; }
		inline Angle( const Vector2 &v ){ _angle = atan2f( v.y, v.x );} //                  angle as a vector
		inline Angle( double    angle ) { _angle = ANG_MODULUS( angle, TAU );} //           angle in radians
		inline Angle( float     angle ) { _angle = ANG_MODULUS( angle, TAU );} //           angle in radians
		inline Angle( long   angleDeg ) { _angle = ANG_MODULUS( angleDeg * DtoR, TAU );} // angle in degrees *
		inline Angle( int    angleDeg ) { _angle = ANG_MODULUS( angleDeg * DtoR, TAU );} // angle in degrees *

		// copy assignment operators
		inline Angle operator=( const Angle   &a ){ _angle = a._angle; return *this; }
		inline Angle operator=( const Vector2 &v ){ _angle = atan2f( v.y, v.x ); return *this; } //                  angle as a vector
		inline Angle operator=( double     angle ){ _angle = ANG_MODULUS( angle, TAU ); return *this; } //           angle in radians
		inline Angle operator=( float      angle ){ _angle = ANG_MODULUS( angle, TAU ); return *this; } //           angle in radians
		inline Angle operator=( long    angleDeg ){ _angle = ANG_MODULUS( angleDeg * DtoR, TAU ); return *this; } // angle in degrees *
		inline Angle operator=( int     angleDeg ){ _angle = ANG_MODULUS( angleDeg * DtoR, TAU ); return *this; } // angle in degrees *

		// ============================ ACCESSORS / MUTATORS
		inline angle_scalar_t normalize() { _angle = ANG_MODULUS( _angle, TAU ); return _angle; } // returns the angle in the range [0, TAU]

		inline angle_scalar_t getRad() const { return _angle; } //                 returns the angle in the range [0, TAU]
		inline angle_scalar_t getDeg() const { return _angle * RtoD; } //          returns the angle in the range [0, 360]
		inline angle_scalar_t getOne() const { return _angle / TAU; } //           returns the angle in the range [0, 1]
		inline angle_scalar_t getTwo() const { return ( _angle / PI ) - 1.0f; } // returns the angle in the range [-1, 1]

		inline angle_scalar_t getRadPos() const { return _angle; } //              returns the angle in the range [0, TAU]
		inline angle_scalar_t getRadCen() const { return _angle - PI; } //         returns the angle in the range [-PI, PI]
		inline angle_scalar_t getRadNeg() const { return _angle - TAU; } //        returns the angle in the range [-TAU, 0]

		inline angle_scalar_t getDegPos() const { return ( _angle * RtoD ); } //       returns the angle in the range [0, 360]
		inline angle_scalar_t getDegCen() const { return ( _angle - PI ) * RtoD; } //  returns the angle in the range [-180, 180]
		inline angle_scalar_t getDegNeg() const { return ( _angle - TAU ) * RtoD; } // returns the angle in the range [-360, 0]

		// returns the angle as a unit vector ( normalized )
		inline Vector2 getVec2() const { Vector2 v = { cosf( _angle ), sinf( _angle )}; return v; }

		inline void setTo( const Vector2 &v ){ _angle = atan2f( v.y, v.x ); } //           angle as a vector
		inline void setTo( double angle ){     _angle = ANG_MODULUS( angle, TAU ); } //           angle in radians
		inline void setTo( float  angle ){     _angle = ANG_MODULUS( angle, TAU ); } //           angle in radians
		inline void setTo( int angleDeg ){     _angle = ANG_MODULUS( angleDeg * DtoR, TAU ); } // angle in degrees *

		inline float cos() const { return cosf( _angle ); }
		inline float sin() const { return sinf( _angle ); }
		inline float tan() const { return tanf( _angle ); }

		inline float cot() const { return 1.0f / tanf( _angle ); }
		inline float sec() const { return 1.0f / cosf( _angle ); }
		inline float csc() const { return 1.0f / sinf( _angle ); }

		inline float acos() const { return acosf( _angle ); }
		inline float asin() const { return asinf( _angle ); }
		inline float atan() const { return atanf( _angle ); }

		explicit inline operator Vector2() const { return getVec2(); } //               Returns the angle as a vector
		explicit inline operator double()  const { return double( _angle ); } //        Returns the angle in radians
		explicit inline operator float()   const { return  float( _angle ); } //        Returns the angle in radians
		explicit inline operator long()    const { return   long( _angle * RtoD ); } // Returns the angle in degrees *
		explicit inline operator int()     const { return    int( _angle * RtoD ); } // Returns the angle in radians *

		// ============================ OPERATORS
		inline Angle operator+( const Angle   &a ) const { return Angle( ANG_MODULUS( _angle + a._angle, TAU )); }
		inline Angle operator+( const Vector2 &v ) const { return Angle( ANG_MODULUS( _angle + Angle( v )._angle, TAU )); } //   angle as a vector
		inline Angle operator+( double     angle ) const { return Angle( ANG_MODULUS( _angle + angle, TAU )); } //               angle in radians
		inline Angle operator+( float      angle ) const { return Angle( ANG_MODULUS( _angle + angle, TAU )); } //               angle in radians
		inline Angle operator+( long    angleDeg ) const { return Angle( ANG_MODULUS( _angle + ( angleDeg * DtoR ), TAU )); } // angle in degrees *
		inline Angle operator+( int     angleDeg ) const { return Angle( ANG_MODULUS( _angle + ( angleDeg * DtoR ), TAU )); } // angle in degrees *

		inline Angle operator-( const Angle   &a ) const { return Angle( ANG_MODULUS( _angle - a._angle, TAU )); }
		inline Angle operator-( const Vector2 &v ) const { return Angle( ANG_MODULUS( _angle - Angle( v )._angle, TAU )); } //   angle as a vector
		inline Angle operator-( double     angle ) const { return Angle( ANG_MODULUS( _angle - angle, TAU )); } //               angle in radians
		inline Angle operator-( float      angle ) const { return Angle( ANG_MODULUS( _angle - angle, TAU )); } //               angle in radians
		inline Angle operator-( long    angleDeg ) const { return Angle( ANG_MODULUS( _angle - ( angleDeg * DtoR ), TAU )); } // angle in degrees *
		inline Angle operator-( int     angleDeg ) const { return Angle( ANG_MODULUS( _angle - ( angleDeg * DtoR ), TAU )); } // angle in degrees *

		//inline Angle operator*( const Angle &a ) const { return Angle( ANG_MODULUS( _angle * a._angle, TAU )); }
		//inline Angle operator/( const Angle &a ) const { return Angle( ANG_MODULUS( _angle / a._angle, TAU )); }
		//inline Angle operator%( const Angle &a ) const { return Angle( ANG_MODULUS( _angle,  a._angle )); }

		//Checks for relative position of the angles // TODO : check if all this is correct

		inline bool operator==( const Angle   &a ) const { return this->isEqual( a ); }
		inline bool operator==( const Vector2 &v ) const { return this->isEqual( Angle( v )); } //        angle as a vector
		inline bool operator==( double     angle ) const { return this->isEqual( Angle( angle )); } //    angle in radians
		inline bool operator==( float      angle ) const { return this->isEqual( Angle( angle )); } //    angle in radians
		inline bool operator==( long    angleDeg ) const { return this->isEqual( Angle( angleDeg )); } // angle in degrees *
		inline bool operator==( int     angleDeg ) const { return this->isEqual( Angle( angleDeg )); } // angle in degrees *

		inline bool operator!=( const Angle   &a ) const { return this->isDiff( a ); }
		inline bool operator!=( const Vector2 &v ) const { return this->isDiff( Angle( v )); } //        angle as a vector
		inline bool operator!=( double     angle ) const { return this->isDiff( Angle( angle )); } //    angle in radians
		inline bool operator!=( float      angle ) const { return this->isDiff( Angle( angle )); } //    angle in radians
		inline bool operator!=( long    angleDeg ) const { return this->isDiff( Angle( angleDeg )); } // angle in degrees *
		inline bool operator!=( int     angleDeg ) const { return this->isDiff( Angle( angleDeg )); } // angle in degrees *

		// NOTE : checks if this a is left of this ( 0 to -180 degrees )
		inline bool operator<( const Angle   &a ) const { return this->isRightOf( a ); }
		inline bool operator<( const Vector2 &v ) const { return this->isRightOf( Angle( v )); } //        angle as a vector
		inline bool operator<( double     angle ) const { return this->isRightOf( Angle( angle )); } //    angle in radians
		inline bool operator<( float      angle ) const { return this->isRightOf( Angle( angle )); } //    angle in radians
		inline bool operator<( long    angleDeg ) const { return this->isRightOf( Angle( angleDeg )); } // angle in degrees *
		inline bool operator<( int     angleDeg ) const { return this->isRightOf( Angle( angleDeg )); } // angle in degrees *

		// NOTE : checks if this a is right of this ( 0 to +180 degrees )
		inline bool operator>( const Angle   &a ) const { return this->isLeftOf( a ); }
		inline bool operator>( const Vector2 &v ) const { return this->isLeftOf( Angle( v )); } //        angle as a vector
		inline bool operator>( double     angle ) const { return this->isLeftOf( Angle( angle )); } //    angle in radians
		inline bool operator>( float      angle ) const { return this->isLeftOf( Angle( angle )); } //    angle in radians
		inline bool operator>( long    angleDeg ) const { return this->isLeftOf( Angle( angleDeg )); } // angle in degrees *
		inline bool operator>( int     angleDeg ) const { return this->isLeftOf( Angle( angleDeg )); } // angle in degrees *

		// NOTE : checks if this a is parallel to this ( 0 to +90 degrees )
		inline bool operator|( const Angle   &a ) const { return this->isParallel( a ); }
		inline bool operator|( const Vector2 &v ) const { return this->isParallel( Angle( v )); } //        angle as a vector
		inline bool operator|( double     angle ) const { return this->isParallel( Angle( angle )); } //    angle in radians
		inline bool operator|( float      angle ) const { return this->isParallel( Angle( angle )); } //    angle in radians
		inline bool operator|( long    angleDeg ) const { return this->isParallel( Angle( angleDeg )); } // angle in degrees *
		inline bool operator|( int     angleDeg ) const { return this->isParallel( Angle( angleDeg )); } // angle in degrees *

		// NOTE : checks if this a is perpendicular to this ( 90 to 270 degrees )
		inline bool operator^( const Angle   &a ) const { return this->isPerpend( a ); }
		inline bool operator^( const Vector2 &v ) const { return this->isPerpend( Angle( v )); } //        angle as a vector
		inline bool operator^( double     angle ) const { return this->isPerpend( Angle( angle )); } //    angle in radians
		inline bool operator^( float      angle ) const { return this->isPerpend( Angle( angle )); } //    angle in radians
		inline bool operator^( long    angleDeg ) const { return this->isPerpend( Angle( angleDeg )); } // angle in degrees *
		inline bool operator^( int     angleDeg ) const { return this->isPerpend( Angle( angleDeg )); } // angle in degrees *

		// NOTE : checks if this a is opposite to this ( 180 degrees )
		inline bool operator&( const Angle   &a ) const { return this->isOpposite( a ); }
		inline bool operator&( const Vector2 &v ) const { return this->isOpposite( Angle( v )); } //        angle as a vector
		inline bool operator&( double     angle ) const { return this->isOpposite( Angle( angle )); } //    angle in radians
		inline bool operator&( float      angle ) const { return this->isOpposite( Angle( angle )); } //    angle in radians
		inline bool operator&( long    angleDeg ) const { return this->isOpposite( Angle( angleDeg )); } // angle in degrees *
		inline bool operator&( int     angleDeg ) const { return this->isOpposite( Angle( angleDeg )); } // angle in degrees *

		inline bool isEqual(    const Angle &a ) const { return fabs( _angle - a._angle ) < EPS; } //        NOTE : checks if the angles are equal
		inline bool isDiff(     const Angle &a ) const { return fabs( _angle - a._angle ) > EPS; } //        NOTE : checks if the angles are not equal
		inline bool isLeftOf(   const Angle &a ) const { return sinf( a._angle - _angle ) < 0.0f; } //      NOTE : checks if this is left of a ( -180 to 0 degrees )
		inline bool isSameDir(  const Angle &a ) const { return cosf( a._angle - _angle ) > 0.0f; } //      NOTE : checks if this is in the same direction as a ( -90 to +90 degrees )
		inline bool isRightOf(  const Angle &a ) const { return sinf( a._angle - _angle ) > 0.0f; } //      NOTE : checks if this is right of a ( 0 to +180 degrees )
		inline bool isDiffDir(  const Angle &a ) const { return cosf( a._angle - _angle ) < 0.0f; } //      NOTE : checks if this is in the opposite direction as a ( 90 to 270 degrees )
		inline bool isParallel( const Angle &a ) const { return fabs( sinf( a._angle - _angle )) < EPS; } // NOTE : checks if this is parallel to a ( -90 or 90 degrees )
		inline bool isPerpend(  const Angle &a ) const { return fabs( cosf( a._angle - _angle )) < EPS; } // NOTE : checks if this is perpendicular to a ( 0 or 180 degrees )
		inline bool isOpposite( const Angle &a ) const { return fabs( a._angle - PI ) < EPS ; } //           NOTE : checks if this is opposite to a ( 180 degrees )
		inline bool isComplem(  const Angle &a ) const { return fabs( a._angle + _angle ) < EPS ; } //       NOTE : checks if this is complementary to a ( a1 == -a2 )

		// Moves the angle by 45 degrees increments in the given direction ( might conflict with the stream operator )
		//inline Angle operator>>( int n ){ _angle = ANG_MODULUS( _angle + ( n * ( PI / 4.0f )), TAU ); return *this; } // rotate the angle clockwise
		//inline Angle operator<<( int n ){ _angle = ANG_MODULUS( _angle - ( n * ( PI / 4.0f )), TAU ); return *this; } // rotate the angle counter-clockwise

		inline Angle operator+() const { return Angle( _angle ); } // returns the angle
		inline Angle operator-() const { return getComplement(); } // return the complementary angle ( -a )
		inline Angle operator!() const { return getOpposite(); } //   returns the opposite angle ( + 180 degrees )

		inline Angle getComplement() const { return Angle( ANG_MODULUS( -_angle, TAU )); } //      return the flips the angle around 0 ( ex : 37 -> -37)
		inline Angle getOpposite()   const { return Angle( ANG_MODULUS(  _angle + PI, TAU )); } // returns the opposite angle

		// increments / decrements the angle by 0.1 degrees
		inline Angle operator++(){ _angle = ANG_MODULUS( _angle + ( 0.1f * DtoR ), TAU ); return *this; }
		inline Angle operator--(){ _angle = ANG_MODULUS( _angle - ( 0.1f * DtoR ), TAU ); return *this; }

		// increments / decrements the angle by 0.1 degrees and returns the old value
		inline Angle operator++( int ){ Angle a = *this; _angle = ANG_MODULUS( _angle + ( 0.1f * DtoR ), TAU ); return a; }
		inline Angle operator--( int ){ Angle a = *this; _angle = ANG_MODULUS( _angle - ( 0.1f * DtoR ), TAU ); return a; }

		inline Angle operator+=( const Angle   &a ){ _angle = ANG_MODULUS( _angle + a._angle, TAU );            return *this; }
		inline Angle operator+=( const Vector2 &v ){ _angle = ANG_MODULUS( _angle + Angle( v )._angle, TAU );   return *this; } // angle as a vector
		inline Angle operator+=( double     angle ){ _angle = ANG_MODULUS( _angle + angle, TAU );               return *this; } // angle in radians
		inline Angle operator+=( float      angle ){ _angle = ANG_MODULUS( _angle + angle, TAU );               return *this; } // angle in radians
		inline Angle operator+=( long    angleDeg ){ _angle = ANG_MODULUS( _angle + ( angleDeg * DtoR ), TAU ); return *this; } // angle in degrees *
		inline Angle operator+=( int     angleDeg ){ _angle = ANG_MODULUS( _angle + ( angleDeg * DtoR ), TAU ); return *this; } // angle in degrees *

		inline Angle operator-=( const Angle   &a ){ _angle = ANG_MODULUS( _angle - a._angle, TAU );            return *this; }
		inline Angle operator-=( const Vector2 &v ){ _angle = ANG_MODULUS( _angle - Angle( v )._angle, TAU );   return *this; } // angle as a vector
		inline Angle operator-=( double     angle ){ _angle = ANG_MODULUS( _angle - angle, TAU );               return *this; } // angle in radians
		inline Angle operator-=( float      angle ){ _angle = ANG_MODULUS( _angle - angle, TAU );               return *this; } // angle in radians
		inline Angle operator-=( long    angleDeg ){ _angle = ANG_MODULUS( _angle - ( angleDeg * DtoR ), TAU ); return *this; } // angle in degrees *
		inline Angle operator-=( int     angleDeg ){ _angle = ANG_MODULUS( _angle - ( angleDeg * DtoR ), TAU ); return *this; } // angle in degrees *

		//inline Angle operator*=( const Angle &a ){ _angle = ANG_MODULUS( _angle * a._angle, TAU ); return *this; }
		//inline Angle operator/=( const Angle &a ){ _angle = ANG_MODULUS( _angle / a._angle, TAU ); return *this; }
		//inline Angle operator%=( const Angle &a ){ _angle = ANG_MODULUS( _angle, a._angle );       return *this; }

		// ============================ FRIEND METHODS
		friend std::ostream &operator<<( std::ostream &os, const Angle &a ){ os << a.getDeg()  << " degrees"; return os;}
		friend std::ostream &operator<<( std::ostream &os, const Angle *a ){ os << a->getDeg() << " degrees"; return os;}

		// ============================ STATIC FUNCTIONS

		static inline angle_scalar_t normalizeRad( angle_scalar_t angle ) { return ANG_MODULUS( angle, TAU ); } //    returns the angle in the range [0, TAU]
		static inline angle_scalar_t normalizeDeg( angle_scalar_t angle ) { return ANG_MODULUS( angle, 360.0f ); } // returns the angle in the range [0, 360]

		static inline Vector2 toVec2( double  angle ){ return Vector2{ cosf( float( angle )), sinf( float( angle ))}; } //                     angle in radians
		static inline Vector2 toVec2( float   angle ){ return Vector2{ cosf( float( angle )), sinf( float( angle ))}; } //                     angle in radians
		static inline Vector2 toVec2( long angleDeg ){ return Vector2{ cosf( float( angleDeg * DtoR )), sinf( float( angleDeg * DtoR ))}; } // angle in degrees *
		static inline Vector2 toVec2( int  angleDeg ){ return Vector2{ cosf( float( angleDeg * DtoR )), sinf( float( angleDeg * DtoR ))}; } // angle in degrees *

		static inline double toDouble( Vector2   vec ){ return atan2f( vec.y, vec.x ); } //    angle as a vector
		static inline double toDouble( float   angle ){ return double( angle ); } //           angle in radians
		static inline double toDouble( long angleDeg ){ return double( angleDeg * DtoR ); } // angle in degrees *
		static inline double toDouble( int  angleDeg ){ return double( angleDeg * DtoR ); } // angle in degrees *

		static inline float toFloat( Vector2   vec ){ return atan2f( vec.y, vec.x ); } //   angle as a vector
		static inline float toFloat( double  angle ){ return float( angle ); } //           angle in radians
		static inline float toFloat( long angleDeg ){ return float( angleDeg * DtoR ); } // angle in degrees *
		static inline float toFloat( int  angleDeg ){ return float( angleDeg * DtoR ); } // angle in degrees *

		static inline long toLong( Vector2   vec ){ return long( atan2f( vec.y, vec.x ) * RtoD ); } // angle as a vector
		static inline long toLong( double  angle ){ return long( angle * RtoD ); } //                  angle in radians
		static inline long toLong( float   angle ){ return long( angle * RtoD ); } //                  angle in radians
		static inline long toLong( int  angleDeg ){ return long( angleDeg ); } //                      angle in degrees *

		static inline int toInt( Vector2   vec ){ return int( atan2f( vec.y, vec.x ) * RtoD ); } // angle as a vector
		static inline int toInt( double  angle ){ return int( angle * RtoD ); } //                  angle in radians
		static inline int toInt( float   angle ){ return int( angle * RtoD ); } //                  angle in radians
		static inline int toInt( long angleDeg ){ return int( angleDeg ); } //                      angle in degrees *

};

// ============================ DEFAULT FANGLE TYPE ( only one possible for now )

typedef Angle angle_t;

#endif // ANGLE_HPP