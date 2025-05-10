#ifndef MATH_HPP
# define MATH_HPP

# include "./_libs.hpp"
# include "./debug.hpp"

# define EUL	2.71828182845904523536f
# define TAU	6.28318530717958647692f
# define PHI	1.61803398874989484820f
# define PI	  3.14159265358979323846f
# define EPS  0.0000000000001f

# define RtoD ( 180.0f / PI )
# define DtoR ( PI / 180.0f )

# define sqrf( a ) ( a * a )
# define cubf( a ) ( a * a * a )

# define powf(  a, b ) std::pow( a, b ) //      NOTE : this is a workaround for the pow function in the Operate class
# define rootf( a, b ) std::pow( a, 1.0f/b ) // NOTE : this is a workaround for the pow function in the Operate class

// NOTE : return value is always of type T
template < typename T, typename U = T, typename V = T >
struct Operate
{
	static_assert( std::integral< T > || std::floating_point< T >, "Operate: T must be a numeric type" );
	static_assert( std::integral< U > || std::floating_point< U >, "Operate: U must be a numeric type" );
	static_assert( std::integral< V > || std::floating_point< V >, "Operate: V must be a numeric type" );

	// ============================ MONADIC FUNCTIONS

	inline static T abs(  const T &a ){ return T( a < 0 ? -a : a ); } //   Absolute value
	inline static T sign( const T &a ){ return T( a < 0 ? -1 : a > 0 ? 1 : 0 ); } // Sign

	inline static T sqr(  const T &a ){ return T( a * a ); } //                  Square
	inline static T sqrt( const T &a ){ return T( std::sqrt( double( a ))); } // Square root

	inline static T cub(  const T &a ){ return T( a * a * a ); } //              Cube
	inline static T cbrt( const T &a ){ return T( std::cbrt( double( a ))); } // Cube root

	inline static T d2r(  const T &a ){ return T( a * DtoR ); } // Degrees to radians
	inline static T r2d(  const T &a ){ return T( a * RtoD ); } // Radians to degrees

	inline static T sin(  const T &a ){ return T( sinf( double( a ) )); } // Sine
	inline static T cos(  const T &a ){ return T( cosf( double( a ) )); } // Cosine
	inline static T tan(  const T &a ){ return T( tanf( double( a ) )); } // Tangent

	inline static T sec(  const T &a ){ return T( 1.0f / cosf( double( a ) )); } // Secant
	inline static T csc(  const T &a ){ return T( 1.0f / sinf( double( a ) )); } // Cosecant
	inline static T cot(  const T &a ){ return T( 1.0f / tanf( double( a ) )); } // Cotangent

	inline static T asin( const T &a ){ return T( asinf( double( a ) )); } // Inverse sine
	inline static T acos( const T &a ){ return T( acosf( double( a ) )); } // Inverse cosine
	inline static T atan( const T &a ){ return T( atanf( double( a ) )); } // Inverse tangent

	// ============================ DIADIC FUNCTIONS

	inline static T atan2( const T &a, const U &b ){ return T( atan2f( double( a ), double( b ))); } //        Inverse tangent of y/x

	inline static T add(  const T &a, const U &b ){ return T( a + b ); } // Addition
	inline static T sub(  const T &a, const U &b ){ return T( a - b ); } // Subtraction
	inline static T mul(  const T &a, const U &b ){ return T( a * b ); } // Multiplication
	inline static T div(  const T &a, const U &b )
	{
		if( b == 0 ) // Ensures this is 0-div safe
		{
			qlog( "Operate : Division by zero : voiding value", ERROR, 0 );
			return T( 0 ); // Avoid division by zero
		}
		return T( a / b );
	} // Division

	inline static T pow(  const T &a, const U &b ){ return T( powf(  double( a ), double( b ))); } // Power
	inline static T root( const T &a, const U &b ){ return T( rootf( double( a ), double( b ))); } // Root

	inline static T avg(  const T &a, const U &b ){ return T( ( a + b ) / 2 ); } // Average
	inline static T min(  const T &a, const U &b ){ return T( a < b ? a : b ); } // Minimum
	inline static T max(  const T &a, const U &b ){ return T( a > b ? a : b ); } // Maximum
	inline static T span( const T &a, const U &b ){ return T( Operate::abs( a - b )); } // Absolute span

	inline static T mod(  const T &a, const U &b ) // Sign variable modulus ( will ltake the sign of a )
	{
		if( b == 0 ) // Ensures this is 0-div safe
		{
			qlog( "Operate : Modulo by zero : voiding value", ERROR, 0 );
			return T( 0 ); // Avoid division by zero
		}
		return T( fmod( double( a ), double( b )));
	}
	inline static T pmod( const T &a, const U &b ) // Strickly positive modulus
	{
		T res = Operate::mod( a, b );
		if( res < 0 ) res += Operate::abs( b ); // Ensures the result is positive
		return res;
	}
	inline static T nmod ( const T &a, const U &b ) // Strickly negative modulus
	{
		T res = Operate::mod( a, b );
		if( res > 0 ) res -= Operate::abs( b ); // Ensures the result is negative
		return res;
	}

	// ============================ TRIDIC FUNCTIONS

	inline static T avg(  const T &a, const U &b, const V &c ){ return T( ( a + b + c ) / 3 ); } //                      Average of 3
	inline static T min(  const T &a, const U &b, const V &c ){ return T( Operate::min( Operate::min( a, b ), c )); } // Minimum of 3
	inline static T max(  const T &a, const U &b, const V &c ){ return T( Operate::max( Operate::max( a, b ), c )); } // Maximum of 3

	inline static T med(  const T &a, const U &b, const V &c ){ return T( a + b + c - Operate::min( a, b, c ) - Operate::max( a, b, c )); } // Median of 3
	inline static T clmp( const T &m, const T &a, const T &M ){ return T( Operate::min( Operate::max( m, a ), M )); } //         Clamping between m and M

	inline static T lerp( const T &a, const T &b, const T &t ){ return T( a + ( t * ( b - a ))); } //  Linear interpolation between a and b base on factor t
	inline static T norm( const T &a, const T &b, const T &v )// Clamps between [0,1] according to v's relative position between a and b
	{
		if(   v <= Operate::min( a, b )) return T( 0 );
		elif( v >= Operate::max( a, b )) return T( 1 );
		elif( a == b ) // Ensures this is 0-div safe
		{
			qlog( "Operate : normalizing to zero-span : voiding value", ERROR, 0 );
			return T( 0 );
		}
		else return T( ( v - Operate::min( a, b )) / Operate::span( a, b )); // Normalizating v between a and b
	}
};

	// ============================ SHORTHAND FUNCTIONS
/*
#define TW template < typename W >

TW inline static W abs(  const W &a ){ return Operate::abs(  a ); } // Absolute value
TW inline static W sign( const W &a ){ return Operate::sign( a ); } // Sign

TW inline static W sqr(  const W &a ){ return Operate::sqr(  a ); } // Square
TW inline static W sqrt( const W &a ){ return Operate::sqrt( a ); } // Square root

TW inline static W cub(  const W &a ){ return Operate::cub(  a ); } // Cube
TW inline static W cbrt( const W &a ){ return Operate::cbrt( a ); } // Cube root

TW inline static W d2r(  const W &a ){ return Operate::d2r( a ); } // Degrees to radians
TW inline static W r2d(  const W &a ){ return Operate::r2d( a ); } // Radians to degrees

TW inline static W sin(  const W &a ){ return Operate::sin(  a ); } // Sine
TW inline static W cos(  const W &a ){ return Operate::cos(  a ); } // Cosine
TW inline static W tan(  const W &a ){ return Operate::tan(  a ); } // Tangent

TW inline static W sec(  const W &a ){ return Operate::sec(  a ); } // Secant
TW inline static W csc(  const W &a ){ return Operate::csc(  a ); } // Cosecant
TW inline static W cot(  const W &a ){ return Operate::cot(  a ); } // Cotangent

TW inline static W asin( const W &a ){ return Operate::asin( a ); } // Inverse sine
TW inline static W acos( const W &a ){ return Operate::acos( a ); } // Inverse cosine
TW inline static W atan( const W &a ){ return Operate::atan( a ); } // Inverse tangent

TW inline static W atan2( const W &a, const W &b ){ return Operate::atan2( a, b ); } // Inverse tangent of y/x

TW inline static W add(  const W &a, const W &b ){ return Operate::add(  a, b ); } // Addition
TW inline static W sub(  const W &a, const W &b ){ return Operate::sub(  a, b ); } // Subtraction
TW inline static W mul(  const W &a, const W &b ){ return Operate::mul(  a, b ); } // Multiplication
TW inline static W div(  const W &a, const W &b ){ return Operate::div(  a, b ); } // Division

TW inline static W pow(  const W &a, const W &b ){ return Operate::pow(  a, b ); } // Power
TW inline static W root( const W &a, const W &b ){ return Operate::root( a, b ); } // Root

TW inline static W min(  const W &a, const W &b ){ return Operate::min(  a, b ); } // Minimum
TW inline static W avg(  const W &a, const W &b ){ return Operate::avg(  a, b ); } // Average
TW inline static W max(  const W &a, const W &b ){ return Operate::max(  a, b ); } // Maximum
TW inline static W span( const W &a, const W &b ){ return Operate::span( a, b ); } // Absolute span

TW inline static W mod(  const W &a, const W &b ){ return Operate::mod(  a, b ); } // Sign variable modulus
TW inline static W pmod( const W &a, const W &b ){ return Operate::pmod( a, b ); } // Strickly positive modulus
TW inline static W nmod( const W &a, const W &b ){ return Operate::nmod( a, b ); } // Strickly negative modulus

TW inline static W min(  const W &a, const W &b, const W &c ){ return Operate::min(  a, b, c ); } // Minimum of 3
TW inline static W avg(  const W &a, const W &b, const W &c ){ return Operate::avg(  a, b, c ); } // Average of 3
TW inline static W max(  const W &a, const W &b, const W &c ){ return Operate::max(  a, b, c ); } // Maximum of 3
TW inline static W med(  const W &a, const W &b, const W &c ){ return Operate::med(  a, b, c ); } // Median of 3

TW inline static W clmp( const W &m, const W &a, const W &M ){ return Operate::clmp( m, a, M ); } // Clamping between m and M
TW inline static W lerp( const W &a, const W &b, const W &t ){ return Operate::lerp( a, b, t ); } // Linear interpolation between a and b base on factor t
TW inline static W norm( const W &a, const W &b, const W &v ){ return Operate::norm( a, b, v ); } // Clamps between [0,1] according to v's relative position between a and b

#undef TW
*/

#endif // MATH_HPP