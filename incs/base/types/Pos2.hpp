#ifndef POS_2_HPP
# define POS_2_HPP

# include <raylib.h>
# include "../core.hpp"

template < typename T >
class Pos2
{
	static_assert( std::integral< T > || std::floating_point< T >, "Pos2 : Template error : T is not a number" );

	#define TU template < typename U, typename = std::enable_if_t< std::is_integral_v< U > || std::is_floating_point_v< U > >>

	public:
		T x;
		T y;

	// ============================ CONSTRUCTORS / DESTRUCTORS
		inline ~Pos2(){};

		inline Pos2()                              : x(  0  ), y(  0  ){} // defaults to a position of ( 0, 0 )
		TU inline Pos2( const U &v )               : x(  v  ), y(  v  ){} // defaults to a position of ( val, val )
		TU inline Pos2( const U &x_, const U &y_ ) : x(  x_ ), y(  y_ ){}
		inline Pos2( const Pos2    &p )            : x( p.x ), y( p.y ){}
		inline Pos2( const Vector2 &v )            : x( v.x ), y( v.y ){}

		inline Pos2 operator=( const Pos2    &p ){ x = p.x; y = p.y; return *this; }
		inline Pos2 operator=( const Vector2 &v ){ x = v.x; y = v.y; return *this; } // angle as a vector

	// ============================ ACCESSORS / MUTATORS
		inline void setX( T x_ ){ x = x_; }
		inline void setY( T y_ ){ y = y_; }

		inline void setPos( const T &x_, const T &y_ ){    x = x_;  y = y_;  }
		inline void setPos( const Vector2 &v ){            x = v.x; y = v.y; }
		inline void setPos( const Pos2 &p ){               x = p.x; y = p.y; }

		TU inline void setPos( const U &x_, const U &y_ ){ x = x_;  y = y_; }
		TU inline void setPos( const U &v ){               x = v;   y = v;  }

		inline T getX() const { return x; }
		inline T getY() const { return y; }

		inline T lenSqr() const { return sqrf( x ) + sqrf( y ); } // returns the squared length of the vector
		inline T len()    const { return sqrtf( lenSqr() ); }

		// NOTE : returns the dot product of this and a
		inline T dotP( const Pos2    &p ) const { return ( x * p.x + y * p.y ); }
		inline T dotP( const Vector2 &v ) const { return ( x * v.x + y * v.y ); }

		// NOTE : returns the cross product of this and a
		inline T crossP( const Pos2    &p ) const { return ( x * p.y - y * p.x ); }
		inline T crossP( const Vector2 &v ) const { return ( x * v.y - y * v.x ); }

		// NOTE : returns the angle between this and a // TODO : check if this is correct
		//nline T angle( const Pos2    &p ) const { return acosf( dotP( p ) / ( len() * p.len() )); }
		//nline T angle( const Vector2 &v ) const { return acosf( dotP( v ) / ( len() * sqrtf( sqrf( v.x_ ) + sqrf( v.y_ )))); }

		inline void normalize()
		{
			T len = len();
			if( len != 0 )
			{
				x /= len;
				y /= len;
			}
			else { qlog( "Pos2::normalize : length is 0 : unable to normalize", DEBUG, 0 ); }
		}

	// ============================ CASTING METHODS

		inline operator Vector2() const { return Vector2{ float( x ), float( y )}; } // returns the vector as a Vector2

		TU inline operator U() const { return U( len() ); } // returns the vector's lenght

	// ============================ IN-CLASS OPERATORS

		inline Pos2 operator+() const { return Pos2( +x, +y ); }
		inline Pos2 operator-() const { return Pos2( -x, -y ); }

		inline Pos2 operator++(){ x++; y++; return Pos2( x, y ); }
		inline Pos2 operator--(){ x--; y--; return Pos2( x, y ); }

		inline Pos2 operator++( int ){ Pos2 tmp( x, y ); x++; y++; return tmp; }
		inline Pos2 operator--( int ){ Pos2 tmp( x, y ); x--; y--; return tmp; }

		inline Pos2 operator+( const Pos2 &p ) const { return Pos2( x + p.x, y + p.y ); }
		inline Pos2 operator-( const Pos2 &p ) const { return Pos2( x - p.x, y - p.y ); }
		inline Pos2 operator*( const Pos2 &p ) const { return Pos2( x * p.x, y * p.y ); }
		inline Pos2 operator/( const Pos2 &p ) const { return Pos2( x / p.x, y / p.y ); }
		inline Pos2 operator%( const Pos2 &p ) const { return Pos2( fmod( x, p.x ), fmod( y, p.y )); }

		inline Pos2 operator+=( const Pos2 &p ){ x += p.x; y += p.y; return Pos2( x, y ); }
		inline Pos2 operator-=( const Pos2 &p ){ x -= p.x; y -= p.y; return Pos2( x, y ); }
		inline Pos2 operator*=( const Pos2 &p ){ x *= p.x; y *= p.y; return Pos2( x, y ); }
		inline Pos2 operator/=( const Pos2 &p ){ x /= p.x; y /= p.y; return Pos2( x, y ); }
		inline Pos2 operator%=( const Pos2 &p ){ x = fmod( x, p.x ); y = fmod( y, p.y ); return Pos2( x, y ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Pos2 &p ) const { return ( x == p.x && y == p.y ); }
		inline bool operator!=( const Pos2 &p ) const { return ( x != p.x || y != p.y ); }
		inline bool operator<=( const Pos2 &p ) const { return ( x <= p.x && y <= p.y ); }
		inline bool operator>=( const Pos2 &p ) const { return ( x >= p.x && y >= p.y ); }
		inline bool operator<(  const Pos2 &p ) const { return ( x <  p.x && y <  p.y ); }
		inline bool operator>(  const Pos2 &p ) const { return ( x >  p.x && y >  p.y ); }

	// ============================ VECTOR2 OPERATORS ( raylib dependent )

		inline Pos2 operator+( const Vector2 &v ) const { return Pos2( x + v.x, y + v.y ); }
		inline Pos2 operator-( const Vector2 &v ) const { return Pos2( x - v.x, y - v.y ); }
		inline Pos2 operator*( const Vector2 &v ) const { return Pos2( x * v.x, y * v.y ); }
		inline Pos2 operator/( const Vector2 &v ) const { return Pos2( x / v.x, y / v.y ); }
		inline Pos2 operator%( const Vector2 &v ) const { return Pos2( fmod( x, v.x ), fmod( y, v.y )); }

		inline Pos2 operator+=( const Vector2 &v ){ x += v.x; y += v.y; return Pos2( x, y ); }
		inline Pos2 operator-=( const Vector2 &v ){ x -= v.x; y -= v.y; return Pos2( x, y ); }
		inline Pos2 operator*=( const Vector2 &v ){ x *= v.x; y *= v.y; return Pos2( x, y ); }
		inline Pos2 operator/=( const Vector2 &v ){ x /= v.x; y /= v.y; return Pos2( x, y ); }
		inline Pos2 operator%=( const Vector2 &v ){ x = fmod( x, v.x ); y = fmod( y, v.y ); return Pos2( x, y ); }

		// NOTE : compare to  both x_ and y_ individually
		inline bool operator==( const Vector2 &v ) const { return ( x == v.x && y == v.y ); }
		inline bool operator!=( const Vector2 &v ) const { return ( x != v.x || y != v.y ); }
		inline bool operator<=( const Vector2 &v ) const { return ( x <= v.x && y <= v.y ); }
		inline bool operator>=( const Vector2 &v ) const { return ( x >= v.x && y >= v.y ); }
		inline bool operator<(  const Vector2 &v ) const { return ( x <  v.x && y <  v.y ); }
		inline bool operator>(  const Vector2 &v ) const { return ( x >  v.x && y >  v.y ); }

	// ============================ TYPENAME OPERATORS

		TU inline Pos2 operator+( const U &val ) const { return Pos2( Operate< T, U >::add( x, val), Operate< T, U >::add( y, val)); }
		TU inline Pos2 operator-( const U &val ) const { return Pos2( Operate< T, U >::sub( x, val), Operate< T, U >::sub( y, val)); }
		TU inline Pos2 operator*( const U &val ) const { return Pos2( Operate< T, U >::mul( x, val), Operate< T, U >::mul( y, val)); }
		TU inline Pos2 operator/( const U &val ) const { return Pos2( Operate< T, U >::div( x, val), Operate< T, U >::div( y, val)); }
		TU inline Pos2 operator%( const U &val ) const { return Pos2( Operate< T, U >::mod( x, val), Operate< T, U >::mod( y, val)); }

		TU inline Pos2 operator+=( const U &val ){ x = Operate< T, U >::add( x, val ); y = Operate< T, U >::add( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator-=( const U &val ){ x = Operate< T, U >::sub( x, val ); y = Operate< T, U >::sub( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator*=( const U &val ){ x = Operate< T, U >::mul( x, val ); y = Operate< T, U >::mul( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator/=( const U &val ){ x = Operate< T, U >::div( x, val ); y = Operate< T, U >::div( y, val ); return Pos2( x, y ); }
		TU inline Pos2 operator%=( const U &val ){ x = Operate< T, U >::mod( x, val ); y = Operate< T, U >::mod( y, val ); return Pos2( x, y ); }

		// NOTE : compare to the length to the absolute value of val
		TU inline bool operator==( const T &val ) const { return ( lenSqr() == sqrf( val )); } // checks if len() == |val|
		TU inline bool operator!=( const T &val ) const { return ( lenSqr() != sqrf( val )); } // checks if len() != |val|
		TU inline bool operator<=( const T &val ) const { return ( lenSqr() <= sqrf( val )); } // checks if len() <= |val|
		TU inline bool operator>=( const T &val ) const { return ( lenSqr() >= sqrf( val )); } // checks if len() >= |val|
		TU inline bool operator<(  const T &val ) const { return ( lenSqr() <  sqrf( val )); } // checks if len() <  |val|
		TU inline bool operator>(  const T &val ) const { return ( lenSqr() >  sqrf( val )); } // checks if len() >  |val|

		#undef TU

	// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const Pos2 &p ){ os << "[" << p.x << ":" << p.y << "]"; return os; }
		inline friend std::string to_string( const Pos2 &p ){ return "[" + to_string( p.x ) + ":" + to_string( p.y ) + "]"; }
};

// ============================ DEFAULT POS2 TYPES

typedef Pos2< double > pos2d_t;
typedef Pos2< float >  pos2f_t;
typedef Pos2< long >   pos2l_t;
typedef Pos2< int >    pos2i_t;

# include "./FixedPoint.hpp"

typedef Pos2< fixed_t > vec2_t; // default position type

#endif // POS_2_HPP