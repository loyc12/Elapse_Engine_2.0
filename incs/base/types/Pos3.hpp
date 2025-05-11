#ifndef POS_3_HPP
# define POS_3_HPP

# include <raylib.h>
# include "../core.hpp"

# include "./FixedPoint.hpp"
//# include "./Angle.hpp"

template < typename T >
class Pos3
{
	static_assert( std::integral< T > || std::floating_point< T >, "Pos3 : Template error : T is not a number" );

	#define TU template < typename U, typename = std::enable_if_t< std::is_integral_v< U > || std::is_floating_point_v< U > >>

	public:
		T x;
		T y;
		T z;

	// ============================ CONSTRUCTORS / DESTRUCTORS
		inline ~Pos3(){};

		inline Pos3()                   : x(  0  ), y(  0  ), z(  0  ){} // defaults to a position of ( 0, 0 )
		inline Pos3( const Pos3    &p ) : x( p.x ), y( p.y ), z( p.z ){}
		inline Pos3( const Vector3 &v ) : x( v.x ), y( v.y ), z( v.z ){}
		TU inline Pos3( const U    &v ) : x(  v  ), y(  v  ), z(  z  ){} // defaults to a position of ( val, val )

		TU inline Pos3( const U &x_, const U &y_, const U &z_ ) : x( x_ ), y( y_ ), z( z_ ){}

		inline Pos3 operator=( const Pos3    &p ){ x = p.x; y = p.y; y = p.z; return *this; }
		inline Pos3 operator=( const Vector3 &v ){ x = v.x; y = v.y; y = v.z; return *this; } // angle as a vector

	// ============================ ACCESSORS / MUTATORS
		inline void setX( T x_ ){ x = x_; }
		inline void setY( T y_ ){ y = y_; }
		inline void setZ( T z_ ){ z = z_; }

		inline    void setPos( const T &x_, const T &y_, const T &z_ ){ x = x_;  y = y_; z = z_; }
		TU inline void setPos( const U &x_, const U &y_, const U &z_ ){ x = x_;  y = y_; z = z_; }

		inline    void setPos( const Vector3 &v ){ x = v.x; y = v.y; z = v.z; }
		inline    void setPos( const Pos3    &p ){ x = p.x; y = p.y; z = p.z; }
		TU inline void setPos( const U       &v ){ x = v;   y = v;   z = v;   }

		inline T getX() const { return x; }
		inline T getY() const { return y; }
		inline T getZ() const { return z; }

		inline T getLenSqr() const { return sqrf( x ) + sqrf( y ) + sqrf( z ); } // returns the squared length of the vector
		inline T getLen()    const { return sqrtf( getLenSqr() ); }

		// NOTE : returns the dot product of this and a
		inline fixed_t dotP( const Pos3    &p ) const { return (( x * p.x ) + ( y * p.y ) + ( z * p.z )); }
		inline fixed_t dotP( const Vector3 &v ) const { return (( x * v.x ) + ( y * v.y ) + ( z * v.z )); }

		// NOTE : returns the cross product of this and a
		inline fixed_t crossP( const Pos3    &p ) const { return (( x * p.y ) - ( y * p.x )) + (( y * p.z ) - ( z * p.y )) + (( z * p.x ) - ( x * p.z )); }
		inline fixed_t crossP( const Vector3 &v ) const { return (( x * v.y ) - ( y * v.x )) + (( y * v.z ) - ( z * v.y )) + (( z * v.x ) - ( x * v.z )); }

		// NOTE : returns the angle between this and a // TODO : check if this is correct
		//inline angle_t angle( const Pos3    &p ) const { return acosf( dotP( p ) / ( getLen() * p.getLen() )); }
		//inline angle_t angle( const Vector3 &v ) const { return acosf( dotP( v ) / ( getLen() * sqrtf( sqrf( v.x ) + sqrf( v.y ) + sqrf( v.z )))); }

		inline void normalize()
		{
			fixed_t getLen = this->getLen();

			if ( getLen == 0 ) // NOTE : zero-div protection
			{
				x = y = z = 0;
				qlog( "Pos2::normalize : length is 0 : unable to normalize : reseting values to 0", WARN, 0 );
				return;
			}
			elif ( getLen != 1 )
			{
				x /= getLen;
				y /= getLen;
				z /= getLen;
			}
			else { qlog( "Pos2::normalize : length is 1 : already normalized", DEBUG, 0 ); }
		}

	// ============================ CASTING METHODS

		inline operator Vector3() const { return Vector3{ float( x ), float( y ), float( z )}; }

		TU inline operator U() const { return U( getLen() ); } // returns the vector's lenght

	// ============================ IN-CLASS OPERATORS //                                                  TODO : updated me to use z

		inline Pos3 operator+() const { return Pos3( +x, +y ); }
		inline Pos3 operator-() const { return Pos3( -x, -y ); }

		inline Pos3 operator++(){ x++; y++; return Pos3( x, y ); }
		inline Pos3 operator--(){ x--; y--; return Pos3( x, y ); }

		inline Pos3 operator++( int ){ Pos3 tmp( x, y ); x++; y++; return tmp; }
		inline Pos3 operator--( int ){ Pos3 tmp( x, y ); x--; y--; return tmp; }

		inline Pos3 operator+( const Pos3 &p ) const { return Pos3( x + p.x, y + p.y ); }
		inline Pos3 operator-( const Pos3 &p ) const { return Pos3( x - p.x, y - p.y ); }
		inline Pos3 operator*( const Pos3 &p ) const { return Pos3( x * p.x, y * p.y ); }
		inline Pos3 operator/( const Pos3 &p ) const { return Pos3( x / p.x, y / p.y ); }
		inline Pos3 operator%( const Pos3 &p ) const { return Pos3( fmod( x, p.x ), fmod( y, p.y )); }

		inline Pos3 operator+=( const Pos3 &p ){ x += p.x; y += p.y; return Pos3( x, y ); }
		inline Pos3 operator-=( const Pos3 &p ){ x -= p.x; y -= p.y; return Pos3( x, y ); }
		inline Pos3 operator*=( const Pos3 &p ){ x *= p.x; y *= p.y; return Pos3( x, y ); }
		inline Pos3 operator/=( const Pos3 &p ){ x /= p.x; y /= p.y; return Pos3( x, y ); }
		inline Pos3 operator%=( const Pos3 &p ){ x = fmod( x, p.x ); y = fmod( y, p.y ); return Pos3( x, y ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Pos3 &p ) const { return ( x == p.x && y == p.y ); }
		inline bool operator!=( const Pos3 &p ) const { return ( x != p.x || y != p.y ); }
		inline bool operator<=( const Pos3 &p ) const { return ( x <= p.x && y <= p.y ); }
		inline bool operator>=( const Pos3 &p ) const { return ( x >= p.x && y >= p.y ); }
		inline bool operator<(  const Pos3 &p ) const { return ( x <  p.x && y <  p.y ); }
		inline bool operator>(  const Pos3 &p ) const { return ( x >  p.x && y >  p.y ); }

	// ============================ VECTOR2 OPERATORS ( raylib dependent )

		inline Pos3 operator+( const Vector3 &v ) const { return Pos3( x + v.x, y + v.y ); }
		inline Pos3 operator-( const Vector3 &v ) const { return Pos3( x - v.x, y - v.y ); }
		inline Pos3 operator*( const Vector3 &v ) const { return Pos3( x * v.x, y * v.y ); }
		inline Pos3 operator/( const Vector3 &v ) const { return Pos3( x / v.x, y / v.y ); }
		inline Pos3 operator%( const Vector3 &v ) const { return Pos3( fmod( x, v.x ), fmod( y, v.y )); }

		inline Pos3 operator+=( const Vector3 &v ){ x += v.x; y += v.y; return Pos3( x, y ); }
		inline Pos3 operator-=( const Vector3 &v ){ x -= v.x; y -= v.y; return Pos3( x, y ); }
		inline Pos3 operator*=( const Vector3 &v ){ x *= v.x; y *= v.y; return Pos3( x, y ); }
		inline Pos3 operator/=( const Vector3 &v ){ x /= v.x; y /= v.y; return Pos3( x, y ); }
		inline Pos3 operator%=( const Vector3 &v ){ x = fmod( x, v.x ); y = fmod( y, v.y ); return Pos3( x, y ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Vector3 &v ) const { return ( x == v.x && y == v.y ); }
		inline bool operator!=( const Vector3 &v ) const { return ( x != v.x || y != v.y ); }
		inline bool operator<=( const Vector3 &v ) const { return ( x <= v.x && y <= v.y ); }
		inline bool operator>=( const Vector3 &v ) const { return ( x >= v.x && y >= v.y ); }
		inline bool operator<(  const Vector3 &v ) const { return ( x <  v.x && y <  v.y ); }
		inline bool operator>(  const Vector3 &v ) const { return ( x >  v.x && y >  v.y ); }

	// ============================ TYPENAME OPERATORS

		TU inline Pos3 operator+( const U &val ) const { return Pos3( Operate< T, U >::add( x, val), Operate< T, U >::add( y, val)); }
		TU inline Pos3 operator-( const U &val ) const { return Pos3( Operate< T, U >::sub( x, val), Operate< T, U >::sub( y, val)); }
		TU inline Pos3 operator*( const U &val ) const { return Pos3( Operate< T, U >::mul( x, val), Operate< T, U >::mul( y, val)); }
		TU inline Pos3 operator/( const U &val ) const { return Pos3( Operate< T, U >::div( x, val), Operate< T, U >::div( y, val)); }
		TU inline Pos3 operator%( const U &val ) const { return Pos3( Operate< T, U >::mod( x, val), Operate< T, U >::mod( y, val)); }

		TU inline Pos3 operator+=( const U &val ){ x = Operate< T, U >::add( x, val ); y = Operate< T, U >::add( y, val ); return Pos3( x, y ); }
		TU inline Pos3 operator-=( const U &val ){ x = Operate< T, U >::sub( x, val ); y = Operate< T, U >::sub( y, val ); return Pos3( x, y ); }
		TU inline Pos3 operator*=( const U &val ){ x = Operate< T, U >::mul( x, val ); y = Operate< T, U >::mul( y, val ); return Pos3( x, y ); }
		TU inline Pos3 operator/=( const U &val ){ x = Operate< T, U >::div( x, val ); y = Operate< T, U >::div( y, val ); return Pos3( x, y ); }
		TU inline Pos3 operator%=( const U &val ){ x = Operate< T, U >::mod( x, val ); y = Operate< T, U >::mod( y, val ); return Pos3( x, y ); }

		// NOTE : compare to the length to the absolute value of val
		TU inline bool operator==( const U &val ) const { return ( getLenSqr() == Operate< U >::sqr( val )); } // checks if getLen() == |val|
		TU inline bool operator!=( const U &val ) const { return ( getLenSqr() != Operate< U >::sqr( val )); } // checks if getLen() != |val|
		TU inline bool operator<=( const U &val ) const { return ( getLenSqr() <= Operate< U >::sqr( val )); } // checks if getLen() <= |val|
		TU inline bool operator>=( const U &val ) const { return ( getLenSqr() >= Operate< U >::sqr( val )); } // checks if getLen() >= |val|
		TU inline bool operator<(  const U &val ) const { return ( getLenSqr() <  Operate< U >::sqr( val )); } // checks if getLen() <  |val|
		TU inline bool operator>(  const U &val ) const { return ( getLenSqr() >  Operate< U >::sqr( val )); } // checks if getLen() >  |val|

	// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const Pos3 &p ){ os << "[" << p.x << ":" << p.y << "]"; return os; }
		inline friend std::string to_string( const Pos3 &p ){ return "[" + to_string( p.x ) + ":" + to_string( p.y ) + "]"; }

		# undef TU
};

// ============================ DEFAULT POS2 TYPES

typedef Pos3< double > pos3d_t;
typedef Pos3< float  > pos3f_t;

typedef Pos3< int8_t  > pos3_8_t;
typedef Pos3< int16_t > pos3_16_t;
typedef Pos3< int32_t > pos3_32_t;
typedef Pos3< int64_t > pos3_64_t;

typedef Pos3< uint8_t  > pos3_u8_t;
typedef Pos3< uint16_t > pos3_u16_t;
typedef Pos3< uint32_t > pos3_u32_t;
typedef Pos3< uint64_t > pos3_u64_t;

typedef Pos3< fixed_t > vec3_t; // default position type

#endif // POS_3_HPP