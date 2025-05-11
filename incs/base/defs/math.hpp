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


# ifndef ANGLE_HPP_FORWARD // forward declaration
#  define ANGLE_HPP_FORWARD

	class Angle;

	namespace std
	{
		template <> struct is_integral<       Angle > : std::true_type {};
		template <> struct is_floating_point< Angle > : std::true_type {};
	}

# endif // ANGLE_HPP

# ifndef FIXED_POINT_HPP_FORWARD
#  define FIXED_POINT_HPP_FORWARD

	template< std::integral T, byte_t D >
	class FixedPoint;

	namespace std
	{
		template < std::integral T, byte_t D > struct is_integral<       FixedPoint< T, D >> : std::true_type {};
		template < std::integral T, byte_t D > struct is_floating_point< FixedPoint< T, D >> : std::true_type {};
	}

# endif // FIXED_POINT_HPP


// NOTE : return value is always of type T
template < typename T = FixedPoint< int64_t, 32 >, typename U = T, typename V = U >
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


# define TU template < typename U = FixedPoint< int64_t, 32 >, typename = std::enable_if_t<( std::is_integral_v< U > || std::is_floating_point_v< U > )>>

TU inline static U o_abs(  const U &a ){ return Operate< U >::abs(  a ); } // Absolute value
TU inline static U o_sign( const U &a ){ return Operate< U >::sign( a ); } // Sign

TU inline static U o_sqr(  const U &a ){ return Operate< U >::sqr(  a ); } // Square
TU inline static U o_sqrt( const U &a ){ return Operate< U >::sqrt( a ); } // Square root

TU inline static U o_cub(  const U &a ){ return Operate< U >::cub(  a ); } // Cube
TU inline static U o_cbrt( const U &a ){ return Operate< U >::cbrt( a ); } // Cube root

TU inline static U o_d2r(  const U &a ){ return Operate< U >::d2r( a ); } // Degrees to radians
TU inline static U o_r2d(  const U &a ){ return Operate< U >::r2d( a ); } // Radians to degrees

TU inline static U o_sin(  const U &a ){ return Operate< U >::sin(  a ); } // Sine
TU inline static U o_cos(  const U &a ){ return Operate< U >::cos(  a ); } // Cosine
TU inline static U o_tan(  const U &a ){ return Operate< U >::tan(  a ); } // Tangent

TU inline static U o_sec(  const U &a ){ return Operate< U >::sec(  a ); } // Secant
TU inline static U o_csc(  const U &a ){ return Operate< U >::csc(  a ); } // Cosecant
TU inline static U o_cot(  const U &a ){ return Operate< U >::cot(  a ); } // Cotangent

TU inline static U o_asin( const U &a ){ return Operate< U >::asin( a ); } // Inverse sine
TU inline static U o_acos( const U &a ){ return Operate< U >::acos( a ); } // Inverse cosine
TU inline static U o_atan( const U &a ){ return Operate< U >::atan( a ); } // Inverse tangent

TU inline static U o_atan2( const U &a, const U &b ){ return Operate< U >::atan2( a, b ); } // Inverse tangent of y/x

TU inline static U o_add(  const U &a, const U &b ){ return Operate< U >::add(  a, b ); } // Addition
TU inline static U o_sub(  const U &a, const U &b ){ return Operate< U >::sub(  a, b ); } // Subtraction
TU inline static U o_mul(  const U &a, const U &b ){ return Operate< U >::mul(  a, b ); } // Multiplication
TU inline static U o_div(  const U &a, const U &b ){ return Operate< U >::div(  a, b ); } // Division

TU inline static U o_pow(  const U &a, const U &b ){ return Operate< U >::pow(  a, b ); } // Power
TU inline static U o_root( const U &a, const U &b ){ return Operate< U >::root( a, b ); } // Root

TU inline static U o_min(  const U &a, const U &b ){ return Operate< U >::min(  a, b ); } // Minimum
TU inline static U o_avg(  const U &a, const U &b ){ return Operate< U >::avg(  a, b ); } // Average
TU inline static U o_max(  const U &a, const U &b ){ return Operate< U >::max(  a, b ); } // Maximum
TU inline static U o_span( const U &a, const U &b ){ return Operate< U >::span( a, b ); } // Absolute span

TU inline static U o_mod(  const U &a, const U &b ){ return Operate< U >::mod(  a, b ); } // Sign variable modulus
TU inline static U o_pmod( const U &a, const U &b ){ return Operate< U >::pmod( a, b ); } // Strickly positive modulus
TU inline static U o_nmod( const U &a, const U &b ){ return Operate< U >::nmod( a, b ); } // Strickly negative modulus

TU inline static U o_min(  const U &a, const U &b, const U &c ){ return Operate< U >::min(  a, b, c ); } // Minimum of 3
TU inline static U o_avg(  const U &a, const U &b, const U &c ){ return Operate< U >::avg(  a, b, c ); } // Average of 3
TU inline static U o_max(  const U &a, const U &b, const U &c ){ return Operate< U >::max(  a, b, c ); } // Maximum of 3
TU inline static U o_med(  const U &a, const U &b, const U &c ){ return Operate< U >::med(  a, b, c ); } // Median of 3

TU inline static U o_clmp( const U &m, const U &a, const U &M ){ return Operate< U >::clmp( m, a, M ); } // Clamping between m and M
TU inline static U o_lerp( const U &a, const U &b, const U &t ){ return Operate< U >::lerp( a, b, t ); } // Linear interpolation between a and b base on factor t
TU inline static U o_norm( const U &a, const U &b, const U &v ){ return Operate< U >::norm( a, b, v ); } // Clamps between [0,1] according to v's relative position between a and b

# undef TU


#endif // MATH_HPP