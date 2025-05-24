#ifndef POS_3_HPP
# define POS_3_HPP

# include "../defs.hpp"

# include "./FixedPoint.hpp"
# include "./Angle.hpp"

template < typename T >
class Pos3
{
	static_assert( std::integral< T > || std::floating_point< T >, "Pos3 : Template error : T is not a number" );

	#define TU template < typename U, typename = std::enable_if_t< std::is_integral_v< U > || std::is_floating_point_v< U > >>
	#define OTU Operate< T, U >
	#define SMOD Operate< T >::mod

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

		inline fixed_t getLenSqr() const { return sqrf( x ) + sqrf( y ) + sqrf( z ); } // returns the squared length of the vector
		inline fixed_t getLen()    const { return sqrtf( getLenSqr() ); } //              returns the length of the vector

		inline fixed_t getDistSqr( const Pos3 &p ) const { return sqrf( x - p.x ) + sqrf( y - p.y ) + sqrf( z - p.z ); } // returns the squared distance to another point
		inline fixed_t getDist(    const Pos3 &p ) const { return sqrtf( getDistSqr( p )); } //                             returns the distance to another point

		// NOTE : returns the dot product of this and a
		inline fixed_t dotP( const Pos3    &p ) const { return (( x * p.x ) + ( y * p.y ) + ( z * p.z )); }
		inline fixed_t dotP( const Vector3 &v ) const { return (( x * v.x ) + ( y * v.y ) + ( z * v.z )); }

		// NOTE : returns the cross product of this and a
		inline fixed_t crossP( const Pos3    &p ) const { return (( x * p.y ) - ( y * p.x )) + (( y * p.z ) - ( z * p.y )) + (( z * p.x ) - ( x * p.z )); }
		inline fixed_t crossP( const Vector3 &v ) const { return (( x * v.y ) - ( y * v.x )) + (( y * v.z ) - ( z * v.y )) + (( z * v.x ) - ( x * v.z )); }

		// NOTE : returns the angle between this and a // TODO : check if this is correct
		//inline angle_t angle( const Pos3    &p ) const { return acosf( dotP( p ) / ( getLen() * p.getLen() )); }
		//inline angle_t angle( const Vector3 &v ) const { return acosf( dotP( v ) / ( getLen() * sqrtf( sqrf( v.x ) + sqrf( v.y ) + sqrf( v.z )))); }

		inline Pos3 getNormalizedCpy() const { Pos3 r = Pos3( *this ); r.normalize(); return Pos3( x, y, z ); }
		inline Pos3 normalize()
		{
			fixed_t len = this->getLen();

			if ( len == 0 ) // NOTE : zero-div protection
			{
				x = y = z = 0;
				qlog( "Pos3::normalize : length is 0 : unable to normalize : reseting values to 0", WARN, 0 );
				return Pos3();
			}
			elif ( len != 1 ) // NOTE : skips the math if len is already 1
			{
				x /= len;
				y /= len;
				z /= len;
			}
			else { qlog( "Pos3::normalize : length is 1 : already normalized", DEBUG, 0 ); }
			return Pos3( x, y, z ); // NOTE : returns a copy of the resulting Pos3, if needed
		}

		/*
		inline Pos3 getRotatedCpy( Angle a, Angle b ) const { Pos3 r = Pos3( *this ); r.rotateBy( a, b ); return Pos3( x, y, z ); }
		inline Pos3 rotateBy( Angle a, Angle b )
		{
			if ( a == 0 && b == 0 ) { return Pos3( x, y, z ); } // NOTE : skiping the maths

			// TODO : check if this is correct
			a += Angle( *this ); // finding the resulting angle after rotation
			b += Angle( *this );

			fixed_t len = this->getLen();

			// NOTE : a nad b both rotate the vector. A does so around the z axis, and b rotates around the y axis

			// TODO : do the maths here

			return Pos3( x, y, z ); // NOTE : returns a copy of the resulting Pos3, if needed
		}
		*/

	// ============================ CASTING METHODS

		inline operator Vector3() const { return Vector3{ float( x ), float( y ), float( z )}; }

		TU inline operator U() const { return U( getLen() ); } // returns the vector's lenght

	// ============================ IN-CLASS OPERATORS

		inline Pos3 operator+() const { return Pos3( +x, +y, +z ); }
		inline Pos3 operator-() const { return Pos3( -x, -y, -z ); }

		inline Pos3 operator++(){ x++; y++; z++; return Pos3( x, y, z ); }
		inline Pos3 operator--(){ x--; y--; z--; return Pos3( x, y, z ); }

		inline Pos3 operator++( int ){ Pos3 tmp( x, y, z ); x++; y++; z++; return tmp; }
		inline Pos3 operator--( int ){ Pos3 tmp( x, y, z ); x--; y--; z--; return tmp; }

		inline Pos3 operator+( const Pos3 &p ) const { Pos3 r = Pos3( *this ); r += p; return r; }
		inline Pos3 operator-( const Pos3 &p ) const { Pos3 r = Pos3( *this ); r -= p; return r; }
		inline Pos3 operator*( const Pos3 &p ) const { Pos3 r = Pos3( *this ); r *= p; return r; }
		inline Pos3 operator/( const Pos3 &p ) const { Pos3 r = Pos3( *this ); r /= p; return r; }
		inline Pos3 operator%( const Pos3 &p ) const { Pos3 r = Pos3( *this ); r %= p; return r; }

		inline Pos3 operator+=( const Pos3 &p ){ x += p.x; y += p.y; z += p.z; return Pos3( x, y, z ); }
		inline Pos3 operator-=( const Pos3 &p ){ x -= p.x; y -= p.y; z -= p.z; return Pos3( x, y, z ); }
		inline Pos3 operator*=( const Pos3 &p ){ x *= p.x; y *= p.y; z *= p.z; return Pos3( x, y, z ); }
		inline Pos3 operator/=( const Pos3 &p ){ x /= p.x; y /= p.y; z /= p.z; return Pos3( x, y, z ); }
		inline Pos3 operator%=( const Pos3 &p ){ x = SMOD( x, p.x ); y = SMOD( y, p.y ), z = SMOD( z, p.z ); return Pos3( x, y, z ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Pos3 &p ) const { return ( x == p.x && y == p.y && z == p.z ); }
		inline bool operator!=( const Pos3 &p ) const { return ( x != p.x || y != p.y || z != p.z ); }
		inline bool operator<=( const Pos3 &p ) const { return ( x <= p.x && y <= p.y && z <= p.z ); }
		inline bool operator>=( const Pos3 &p ) const { return ( x >= p.x && y >= p.y && z >= p.z ); }
		inline bool operator<(  const Pos3 &p ) const { return ( x <  p.x && y <  p.y && z <  p.z ); }
		inline bool operator>(  const Pos3 &p ) const { return ( x >  p.x && y >  p.y && z >  p.z ); }

	// ============================ VECTOR2 OPERATORS ( raylib dependent )

		inline Pos3 operator+( const Vector3 &v ) const { Pos3 r = Pos3( *this ); r += v; return r; }
		inline Pos3 operator-( const Vector3 &v ) const { Pos3 r = Pos3( *this ); r -= v; return r; }
		inline Pos3 operator*( const Vector3 &v ) const { Pos3 r = Pos3( *this ); r *= v; return r; }
		inline Pos3 operator/( const Vector3 &v ) const { Pos3 r = Pos3( *this ); r /= v; return r; }
		inline Pos3 operator%( const Vector3 &v ) const { Pos3 r = Pos3( *this ); r %= v; return r; }

		inline Pos3 operator+=( const Vector3 &v ){ x += v.x; y += v.y; z += v.z; return Pos3( x, y, z ); }
		inline Pos3 operator-=( const Vector3 &v ){ x -= v.x; y -= v.y; z -= v.z; return Pos3( x, y, z ); }
		inline Pos3 operator*=( const Vector3 &v ){ x *= v.x; y *= v.y; z *= v.z; return Pos3( x, y, z ); }
		inline Pos3 operator/=( const Vector3 &v ){ x /= v.x; y /= v.y; z /= v.z; return Pos3( x, y, z ); }
		inline Pos3 operator%=( const Vector3 &v ){ x = SMOD( x, v.x ); y = SMOD( y, v.y ); return Pos3( x, y ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Vector3 &v ) const { return ( x == v.x && y == v.y && z == v.z ); }
		inline bool operator!=( const Vector3 &v ) const { return ( x != v.x || y != v.y || z != v.z ); }
		inline bool operator<=( const Vector3 &v ) const { return ( x <= v.x && y <= v.y && z <= v.z ); }
		inline bool operator>=( const Vector3 &v ) const { return ( x >= v.x && y >= v.y && z >= v.z ); }
		inline bool operator<(  const Vector3 &v ) const { return ( x <  v.x && y <  v.y && z <  v.z ); }
		inline bool operator>(  const Vector3 &v ) const { return ( x >  v.x && y >  v.y && z >  v.z ); }

	// ============================ TYPENAME OPERATORS

		TU inline Pos3 operator+( const U &val ) const { Pos3 r = Pos3( *this ); r += val; return r; }
		TU inline Pos3 operator-( const U &val ) const { Pos3 r = Pos3( *this ); r -= val; return r; }
		TU inline Pos3 operator*( const U &val ) const { Pos3 r = Pos3( *this ); r *= val; return r; }
		TU inline Pos3 operator/( const U &val ) const { Pos3 r = Pos3( *this ); r /= val; return r; }
		TU inline Pos3 operator%( const U &val ) const { Pos3 r = Pos3( *this ); r %= val; return r; }

		TU inline Pos3 operator+=( const U &val ){ x = OTU::add( x, val ); y = OTU::add( y, val ); OTU::add( z, val); return Pos3( x, y ); }
		TU inline Pos3 operator-=( const U &val ){ x = OTU::sub( x, val ); y = OTU::sub( y, val ); OTU::sub( z, val); return Pos3( x, y ); }
		TU inline Pos3 operator*=( const U &val ){ x = OTU::mul( x, val ); y = OTU::mul( y, val ); OTU::mul( z, val); return Pos3( x, y ); }
		TU inline Pos3 operator/=( const U &val ){ x = OTU::div( x, val ); y = OTU::div( y, val ); OTU::div( z, val); return Pos3( x, y ); }
		TU inline Pos3 operator%=( const U &val ){ x = OTU::mod( x, val ); y = OTU::mod( y, val ); OTU::mod( z, val); return Pos3( x, y ); }

		// NOTE : compare to the length to the absolute value of val
		TU inline bool operator==( const U &val ) const { return ( getLenSqr() == Operate< U >::sqr( val )); } // checks if getLen() == |val|
		TU inline bool operator!=( const U &val ) const { return ( getLenSqr() != Operate< U >::sqr( val )); } // checks if getLen() != |val|
		TU inline bool operator<=( const U &val ) const { return ( getLenSqr() <= Operate< U >::sqr( val )); } // checks if getLen() <= |val|
		TU inline bool operator>=( const U &val ) const { return ( getLenSqr() >= Operate< U >::sqr( val )); } // checks if getLen() >= |val|
		TU inline bool operator<(  const U &val ) const { return ( getLenSqr() <  Operate< U >::sqr( val )); } // checks if getLen() <  |val|
		TU inline bool operator>(  const U &val ) const { return ( getLenSqr() >  Operate< U >::sqr( val )); } // checks if getLen() >  |val|

	// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const Pos3 &p ){ os << "[" << p.x << ":" << p.y << ":" << p.z << "]"; return os; }
		inline friend std::string to_string( const Pos3 &p ){ return "[" + to_string( p.x ) + ":" + to_string( p.y ) + ":" + to_string( p.z ) + "]"; }

		# undef TU
		# undef OTU
		# undef SMOD
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

typedef Pos3<  fixed_t > vec3_t; //     default position type
typedef vector< vec3_t > vec3_arr_t; // default position array type

#endif // POS_3_HPP