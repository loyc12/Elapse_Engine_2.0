#ifndef POS_2_HPP
# define POS_2_HPP

# include <raylib.h>
# include "../core.hpp"

# include "./FixedPoint.hpp"
# include "./Angle.hpp"

template < typename T = fixed_t >
class Pos2
{
	static_assert( std::integral< T > || std::floating_point< T >, "Pos2 : Template error : T is not a number" );

	#define TU template < typename U, typename = std::enable_if_t< std::is_integral_v< U > || std::is_floating_point_v< U > >>
	#define OTU Operate< T, U >
	#define SMOD Operate< T >::mod

	public:
		T x;
		T y;

	// ============================ CONSTRUCTORS / DESTRUCTORS
		inline ~Pos2(){};

		inline Pos2()                   : x(  0  ), y(  0  ){} // defaults to a position of ( 0, 0 )
		inline Pos2( const Pos2    &p ) : x( p.x ), y( p.y ){}
		inline Pos2( const Vector2 &v ) : x( v.x ), y( v.y ){}
		TU inline Pos2( const U    &v ) : x(  v  ), y(  v  ){} // defaults to a position of ( val, val )

		TU inline Pos2( const U &x_, const U &y_ ) : x( x_ ), y( y_ ){}

		inline Pos2 operator=( const Pos2    &p ){ x = p.x; y = p.y; return *this; }
		inline Pos2 operator=( const Vector2 &v ){ x = v.x; y = v.y; return *this; } // angle as a vector

	// ============================ ACCESSORS / MUTATORS
		inline void setX( T x_ ){ x = x_; }
		inline void setY( T y_ ){ y = y_; }

		inline    void setPos( const T &x_, const T &y_ ){ x = x_; y = y_; }
		TU inline void setPos( const U &x_, const U &y_ ){ x = x_; y = y_; }

		inline    void setPos( const Vector2 &v ){ x = v.x; y = v.y; }
		inline    void setPos( const Pos2    &p ){ x = p.x; y = p.y; }
		TU inline void setPos( const U       &v ){ x = v;   y = v;   }

		inline T getX() const { return x; }
		inline T getY() const { return y; }

		inline fixed_t getLenSqr() const { return sqrf( x ) + sqrf( y ); } // returns the squared length of the vector
		inline fixed_t getLen()    const { return sqrtf( getLenSqr() ); } //  returns the length of the vector

		inline fixed_t getDistSqr( const Pos2 &p ) const { return sqrf( x - p.x ) + sqrf( y - p.y ); } // returns the squared distance to another point
		inline fixed_t getDist(    const Pos2 &p ) const { return sqrtf( getDistSqr( p )); } //           returns the distance to another point

		// NOTE : returns the dot product of this and a
		inline fixed_t dotP( const Pos2    &p ) const { return (( x * p.x ) + ( y * p.y )); }
		inline fixed_t dotP( const Vector2 &v ) const { return (( x * v.x ) + ( y * v.y )); }

		// NOTE : returns the cross product of this and a
		inline fixed_t crossP( const Pos2    &p ) const { return (( x * p.y ) - ( y * p.x )); }
		inline fixed_t crossP( const Vector2 &v ) const { return (( x * v.y ) - ( y * v.x )); }

		// NOTE : returns the angle between this and a // TODO : check if this is correct
		//inline angle_t angle( const Pos2    &p ) const { return acosf( dotP( p ) / ( len() * p.len() )); }
		//inline angle_t angle( const Vector2 &v ) const { return acosf( dotP( v ) / ( len() * sqrtf( sqrf( v.x ) + sqrf( v.y )))); }

		inline Pos2 getNormalizedCpy() const { Pos2 r = Pos2( *this ).normalize(); return r; }
		inline Pos2 &normalize()
		{
			fixed_t len = this->getLen();

			if ( len == 0 ) // NOTE : zero-div protection
			{
				x = y = 0;
				qlog( "Pos2::normalize : length is 0 : unable to normalize : reseting values to 0", WARN, 0 );
			}
			elif ( len != 1 ) // NOTE : skips the math if len is already 1
			{
				x /= len;
				y /= len;
			}
			else { qlog( "Pos2::normalize : length is 1 : already normalized", DEBUG, 0 ); }
			return *this;
		}

		inline Pos2 getRotatedCpy( Angle a ) const { Pos2 r = Pos2( *this ).rotateBy( a ); return r; }
		inline Pos2 &rotateBy(     Angle a )
		{
			if ( a == 0 ) { return *this; } // NOTE : skiping the maths

			a += Angle( *this ); // finding the resulting angle after rotation
			fixed_t len = this->getLen();

			x = len * a.getX();
			y = len * a.getY();

			return *this;
		}


	// ============================ CASTING METHODS

		inline operator Vector2() const { return Vector2{ float( x ), float( y )}; }

		TU inline operator U() const { return U( getLen() ); } // returns the vector's lenght

	// ============================ IN-CLASS OPERATORS

		inline Pos2 operator+() const { return Pos2( +x, +y ); }
		inline Pos2 operator-() const { return Pos2( -x, -y ); }

		inline Pos2 operator++(){ x++; y++; return Pos2( x, y ); }
		inline Pos2 operator--(){ x--; y--; return Pos2( x, y ); }

		inline Pos2 operator++( int ){ Pos2 tmp( x, y ); x++; y++; return tmp; }
		inline Pos2 operator--( int ){ Pos2 tmp( x, y ); x--; y--; return tmp; }

		inline Pos2 operator+( const Pos2 &p ) const { Pos2 r = Pos2( *this ); r += p; return r; }
		inline Pos2 operator-( const Pos2 &p ) const { Pos2 r = Pos2( *this ); r -= p; return r; }
		inline Pos2 operator*( const Pos2 &p ) const { Pos2 r = Pos2( *this ); r *= p; return r; }
		inline Pos2 operator/( const Pos2 &p ) const { Pos2 r = Pos2( *this ); r /= p; return r; }
		inline Pos2 operator%( const Pos2 &p ) const { Pos2 r = Pos2( *this ); r %= p; return r; }

		inline Pos2 operator+=( const Pos2 &p ){ x += p.x; y += p.y; return Pos2( x, y ); }
		inline Pos2 operator-=( const Pos2 &p ){ x -= p.x; y -= p.y; return Pos2( x, y ); }
		inline Pos2 operator*=( const Pos2 &p ){ x *= p.x; y *= p.y; return Pos2( x, y ); }
		inline Pos2 operator/=( const Pos2 &p ){ x /= p.x; y /= p.y; return Pos2( x, y ); }
		inline Pos2 operator%=( const Pos2 &p ){ x = SMOD( x, p.x ); y = SMOD( y, p.y ); return Pos2( x, y ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Pos2 &p ) const { return ( x == p.x && y == p.y ); }
		inline bool operator!=( const Pos2 &p ) const { return ( x != p.x || y != p.y ); }
		inline bool operator<=( const Pos2 &p ) const { return ( x <= p.x && y <= p.y ); }
		inline bool operator>=( const Pos2 &p ) const { return ( x >= p.x && y >= p.y ); }
		inline bool operator<(  const Pos2 &p ) const { return ( x <  p.x && y <  p.y ); }
		inline bool operator>(  const Pos2 &p ) const { return ( x >  p.x && y >  p.y ); }

	// ============================ VECTOR2 OPERATORS ( raylib dependent )

		inline Pos2 operator+( const Vector2 &v ) const { Pos2 r = Pos2( *this ); r += v; return r; }
		inline Pos2 operator-( const Vector2 &v ) const { Pos2 r = Pos2( *this ); r -= v; return r; }
		inline Pos2 operator*( const Vector2 &v ) const { Pos2 r = Pos2( *this ); r *= v; return r; }
		inline Pos2 operator/( const Vector2 &v ) const { Pos2 r = Pos2( *this ); r /= v; return r; }
		inline Pos2 operator%( const Vector2 &v ) const { Pos2 r = Pos2( *this ); r %= v; return r; }

		inline Pos2 operator+=( const Vector2 &v ){ x += v.x; y += v.y; return Pos2( x, y ); }
		inline Pos2 operator-=( const Vector2 &v ){ x -= v.x; y -= v.y; return Pos2( x, y ); }
		inline Pos2 operator*=( const Vector2 &v ){ x *= v.x; y *= v.y; return Pos2( x, y ); }
		inline Pos2 operator/=( const Vector2 &v ){ x /= v.x; y /= v.y; return Pos2( x, y ); }
		inline Pos2 operator%=( const Vector2 &v ){ x = SMOD( x, v.x ); y = SMOD( y, v.y ); return Pos2( x, y ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Vector2 &v ) const { return ( x == v.x && y == v.y ); }
		inline bool operator!=( const Vector2 &v ) const { return ( x != v.x || y != v.y ); }
		inline bool operator<=( const Vector2 &v ) const { return ( x <= v.x && y <= v.y ); }
		inline bool operator>=( const Vector2 &v ) const { return ( x >= v.x && y >= v.y ); }
		inline bool operator<(  const Vector2 &v ) const { return ( x <  v.x && y <  v.y ); }
		inline bool operator>(  const Vector2 &v ) const { return ( x >  v.x && y >  v.y ); }

	// ============================ TYPENAME OPERATORS

		TU inline Pos2 operator+( const U &val ) const { Pos2 r = Pos2( *this ); r += val; return r; }
		TU inline Pos2 operator-( const U &val ) const { Pos2 r = Pos2( *this ); r -= val; return r; }
		TU inline Pos2 operator*( const U &val ) const { Pos2 r = Pos2( *this ); r *= val; return r; }
		TU inline Pos2 operator/( const U &val ) const { Pos2 r = Pos2( *this ); r /= val; return r; }
		TU inline Pos2 operator%( const U &val ) const { Pos2 r = Pos2( *this ); r %= val; return r; }

		TU inline Pos2 operator+=( const U &val ){ x = OTU::add( x, val ); y = OTU::add( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator-=( const U &val ){ x = OTU::sub( x, val ); y = OTU::sub( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator*=( const U &val ){ x = OTU::mul( x, val ); y = OTU::mul( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator/=( const U &val ){ x = OTU::div( x, val ); y = OTU::div( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator%=( const U &val ){ x = OTU::mod( x, val ); y = OTU::mod( y, val ); return Pos2( x, y ); }

		// NOTE : compare to the length to the absolute value of val
		TU inline bool operator==( const U &val ) const { return ( getLenSqr() == Operate< U >::sqr( val )); } // checks if len() == |val|
		TU inline bool operator!=( const U &val ) const { return ( getLenSqr() != Operate< U >::sqr( val )); } // checks if len() != |val|
		TU inline bool operator<=( const U &val ) const { return ( getLenSqr() <= Operate< U >::sqr( val )); } // checks if len() <= |val|
		TU inline bool operator>=( const U &val ) const { return ( getLenSqr() >= Operate< U >::sqr( val )); } // checks if len() >= |val|
		TU inline bool operator<(  const U &val ) const { return ( getLenSqr() <  Operate< U >::sqr( val )); } // checks if len() <  |val|
		TU inline bool operator>(  const U &val ) const { return ( getLenSqr() >  Operate< U >::sqr( val )); } // checks if len() >  |val|

	// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const Pos2 &p ){ os << "[" << p.x << ":" << p.y << "]"; return os; }
		inline friend std::string to_string( const Pos2 &p ){ return "[" + to_string( p.x ) + ":" + to_string( p.y ) + "]"; }

		# undef TU
		# undef OTU
		# undef SMOD
};

// ============================ DEFAULT POS2 TYPES

typedef Pos2< double > pos2d_t;
typedef Pos2< float  > pos2f_t;

typedef Pos2< int8_t  > pos2_8_t;
typedef Pos2< int16_t > pos2_16_t;
typedef Pos2< int32_t > pos2_32_t;
typedef Pos2< int64_t > pos2_64_t;

typedef Pos2< uint8_t  > pos2_u8_t;
typedef Pos2< uint16_t > pos2_u16_t;
typedef Pos2< uint32_t > pos2_u32_t;
typedef Pos2< uint64_t > pos2_u64_t;

typedef Pos2<  fixed_t > vec2_t; //     default position type
typedef vector< vec2_t > vec2_arr_t; // default position array type

#endif // POS_2_HPP