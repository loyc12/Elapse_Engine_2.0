#ifndef POS_2_HPP
# define POS_2_HPP

# include <raylib.h>
# include "../core.hpp"

# include <concepts>

template < typename T >
class Pos2
{
	static_assert( std::integral< T > || std::floating_point< T >, "Pos2 : Template error : T is not a number" );

	public:
		T X;
		T Y;

	// ============================ CONSTRUCTORS / DESTRUCTORS
		inline ~Pos2(){};

		inline Pos2()                : X(   0 ), Y(   0 ){} // defaults to a position of ( 0, 0 )
		inline Pos2( T x, T y )      : X(   x ), Y(   y ){}
		inline Pos2( const Pos2 &p ) : X( p.x ), Y( p.y ){}
		inline Pos2 operator=( const Pos2 &p ){ X = p.x; Y = p.y; return *this; }

		inline Pos2( const Vector2   &v ) : X(  v.x  ), Y(  v.y  ){}
		inline Pos2( double x, double y ) : X( T( x )), Y( T( y )){}
		inline Pos2( float  x, float  y ) : X( T( x )), Y( T( y )){}
		inline Pos2( long   x, long   y ) : X( T( x )), Y( T( y )){}
		inline Pos2( int    x, int    y ) : X( T( x )), Y( T( y )){}

	// ============================ ACCESSORS / MUTATORS
		inline void setX( T x ){ X = x; }
		inline void setY( T y ){ Y = y; }

		inline void setPos( T x, T y ){         X = x;   Y = y;   }
		inline void setPos( const Pos2 &p ){    X = p.x; Y = p.y; }
		inline void setPos( const Vector2 &v ){ X = v.x; Y = v.y; }

		inline T getX() const { return X; }
		inline T getY() const { return Y; }

		inline T len()   const { return sqrtf( sqrf( X ) + sqrf( Y )); }
		inline T lenSqr() const { return sqrf( X ) + sqrf( Y ); } // returns the squared length of the vector

		// NOTE : returns the dot product of this and a
		inline T dotP( const Pos2    &p ) const { return ( X * p.X + Y * p.Y ); }
		inline T dotP( const Vector2 &v ) const { return ( X * v.x + Y * v.y ); }

		// NOTE : returns the cross product of this and a
		inline T crossP( const Pos2    &p ) const { return ( X * p.Y - Y * p.X ); }
		inline T crossP( const Vector2 &v ) const { return ( X * v.y - Y * v.x ); }

		// NOTE : returns the angle between this and a // TODO : check if this is correct
		//nline T angle( const Pos2    &p ) const { return acosf( dotP( p ) / ( len() * p.len() )); }
		//nline T angle( const Vector2 &v ) const { return acosf( dotP( v ) / ( len() * sqrtf( sqrf( v.x ) + sqrf( v.y )))); }

		inline void normalize()
		{
			T len = len();
			if( len != 0 )
			{
				X /= len;
				Y /= len;
			}
			else { qlog( "Pos2::normalize : length is 0 : unable to normalize", DEBUG, 0 ); }
		}

	// ============================ CASTING METHODS

		explicit inline operator Vector2() const { return Vector2{ float( X ), float( Y )}; } // returns the vector as a Vector2
		explicit inline operator double()  const { return double( len() ); } // returns the vector's lenght
		explicit inline operator float()   const { return  float( len() ); } // returns the vector's lenght
		explicit inline operator long()    const { return   long( len() ); } // returns the vector's lenght
		explicit inline operator int()     const { return    int( len() ); } // returns the vector's lenght
		explicit inline operator T()       const { return      T( len() ); } // returns the vector's lenght

	// ============================ IN-CLASS OPERATORS

		inline Pos2 operator+() const { return Pos2( +X, +Y ); }
		inline Pos2 operator-() const { return Pos2( -X, -Y ); }

		inline Pos2 operator++(){ X++; Y++; return Pos2( X, Y ); }
		inline Pos2 operator--(){ X--; Y--; return Pos2( X, Y ); }

		inline Pos2 operator++( int ){ Pos2 tmp( X, Y ); X++; Y++; return tmp; }
		inline Pos2 operator--( int ){ Pos2 tmp( X, Y ); X--; Y--; return tmp; }

		inline Pos2 operator+( const Pos2 &p ) const { return Pos2( X + p.X, Y + p.Y ); }
		inline Pos2 operator-( const Pos2 &p ) const { return Pos2( X - p.X, Y - p.Y ); }
		inline Pos2 operator*( const Pos2 &p ) const { return Pos2( X * p.X, Y * p.Y ); }
		inline Pos2 operator/( const Pos2 &p ) const { return Pos2( X / p.X, Y / p.Y ); }
		inline Pos2 operator%( const Pos2 &p ) const { return Pos2( fmod( X, p.X ), fmod( Y, p.Y )); }

		inline Pos2 operator+=( const Pos2 &p ){ X += p.X; Y += p.Y; return Pos2( X, Y ); }
		inline Pos2 operator-=( const Pos2 &p ){ X -= p.X; Y -= p.Y; return Pos2( X, Y ); }
		inline Pos2 operator*=( const Pos2 &p ){ X *= p.X; Y *= p.Y; return Pos2( X, Y ); }
		inline Pos2 operator/=( const Pos2 &p ){ X /= p.X; Y /= p.Y; return Pos2( X, Y ); }
		inline Pos2 operator%=( const Pos2 &p ){ X = fmod( X, p.X ); Y = fmod( Y, p.Y ); return Pos2( X, Y ); }

		// NOTE : compare to  both x and y individually
		inline bool operator==( const Pos2 &p ) const { return ( X == p.X && Y == p.Y ); }
		inline bool operator!=( const Pos2 &p ) const { return ( X != p.X || Y != p.Y ); }
		inline bool operator<=( const Pos2 &p ) const { return ( X <= p.X && Y <= p.Y ); }
		inline bool operator>=( const Pos2 &p ) const { return ( X >= p.X && Y >= p.Y ); }
		inline bool operator<(  const Pos2 &p ) const { return ( X <  p.X && Y <  p.Y ); }
		inline bool operator>(  const Pos2 &p ) const { return ( X >  p.X && Y >  p.Y ); }

	// ============================ VECTOR2 OPERATORS ( raylib dependent )

		inline Pos2 operator+( const Vector2 &v ) const { return Pos2( X + v.x, Y + v.y ); }
		inline Pos2 operator-( const Vector2 &v ) const { return Pos2( X - v.x, Y - v.y ); }
		inline Pos2 operator*( const Vector2 &v ) const { return Pos2( X * v.x, Y * v.y ); }
		inline Pos2 operator/( const Vector2 &v ) const { return Pos2( X / v.x, Y / v.y ); }
		inline Pos2 operator%( const Vector2 &v ) const { return Pos2( fmod( X, v.x ), fmod( Y, v.y )); }

		inline Pos2 operator+=( const Vector2 &v ){ X += v.x; Y += v.y; return Pos2( X, Y ); }
		inline Pos2 operator-=( const Vector2 &v ){ X -= v.x; Y -= v.y; return Pos2( X, Y ); }
		inline Pos2 operator*=( const Vector2 &v ){ X *= v.x; Y *= v.y; return Pos2( X, Y ); }
		inline Pos2 operator/=( const Vector2 &v ){ X /= v.x; Y /= v.y; return Pos2( X, Y ); }
		inline Pos2 operator%=( const Vector2 &v ){ X = fmod( X, v.x ); Y = fmod( Y, v.y ); return Pos2( X, Y ); }

		// NOTE : compare to  both x and y individually
		inline bool operator==( const Vector2 &v ) const { return ( X == v.x && Y == v.y ); }
		inline bool operator!=( const Vector2 &v ) const { return ( X != v.x || Y != v.y ); }
		inline bool operator<=( const Vector2 &v ) const { return ( X <= v.x && Y <= v.y ); }
		inline bool operator>=( const Vector2 &v ) const { return ( X >= v.x && Y >= v.y ); }
		inline bool operator<(  const Vector2 &v ) const { return ( X <  v.x && Y <  v.y ); }
		inline bool operator>(  const Vector2 &v ) const { return ( X >  v.x && Y >  v.y ); }

	// ============================ TYPENAME OPERATORS

		# define TU template < typename U >

		TU inline Pos2 operator+( const U &val ) const { return Pos2( Operate< T, U >::add( X, val), Operate< T, U >::add( Y, val)); }
		TU inline Pos2 operator-( const U &val ) const { return Pos2( Operate< T, U >::sub( X, val), Operate< T, U >::sub( Y, val)); }
		TU inline Pos2 operator*( const U &val ) const { return Pos2( Operate< T, U >::mul( X, val), Operate< T, U >::mul( Y, val)); }
		TU inline Pos2 operator/( const U &val ) const { return Pos2( Operate< T, U >::div( X, val), Operate< T, U >::div( Y, val)); }
		TU inline Pos2 operator%( const U &val ) const { return Pos2( Operate< T, U >::mod( X, val), Operate< T, U >::mod( Y, val)); }

		TU inline Pos2 operator+=( const U &val ){ X = Operate< T, U >::add( X, val ); Y = Operate< T, U >::add( Y, val ); return Pos2( X, Y ); }
		TU inline Pos2 operator-=( const U &val ){ X = Operate< T, U >::sub( X, val ); Y = Operate< T, U >::sub( Y, val ); return Pos2( X, Y ); }
		TU inline Pos2 operator*=( const U &val ){ X = Operate< T, U >::mul( X, val ); Y = Operate< T, U >::mul( Y, val ); return Pos2( X, Y ); }
		TU inline Pos2 operator/=( const U &val ){ X = Operate< T, U >::div( X, val ); Y = Operate< T, U >::div( Y, val ); return Pos2( X, Y ); }
		TU inline Pos2 operator%=( const U &val ){ X = Operate< T, U >::mod( X, val ); Y = Operate< T, U >::mod( Y, val ); return Pos2( X, Y ); }

		// NOTE : compare to the length to the absolute value of val
		TU inline bool operator==( const T &val ) const { return ( lenSqr() == sqrf( val )); } // checks if len() == |val|
		TU inline bool operator!=( const T &val ) const { return ( lenSqr() != sqrf( val )); } // checks if len() != |val|
		TU inline bool operator<=( const T &val ) const { return ( lenSqr() <= sqrf( val )); } // checks if len() <= |val|
		TU inline bool operator>=( const T &val ) const { return ( lenSqr() >= sqrf( val )); } // checks if len() >= |val|
		TU inline bool operator<(  const T &val ) const { return ( lenSqr() <  sqrf( val )); } // checks if len() <  |val|
		TU inline bool operator>(  const T &val ) const { return ( lenSqr() >  sqrf( val )); } // checks if len() >  |val|

	// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const Pos2 &p ){ os << "(" << p.X << ", " << p.Y << ")"; return os; }
};

// ============================ DEFAULT POS2 TYPES

typedef Pos2< double > pos2d_t;
typedef Pos2< float >  pos2f_t;
typedef Pos2< long >   pos2l_t;
typedef Pos2< int >    pos2i_t;

# include "./FixedPoint.hpp"

typedef Pos2< fixed_t > vec2_t; // default position type

#endif // POS_2_HPP