#ifndef FIXED_POINT_HPP
# define FIXED_POINT_HPP

# include "../core.hpp"

// TODO : make sure this handles negative vals properly
// TODO : make sure this handles under/overflows properly
// TODO : make sure this handles rounding properly
// TODO : use template for int and floats instead of hardcoding them

#ifndef ANGLE_HPP_FORWARD // forward declaration
# define ANGLE_HPP_FORWARD

	class Angle;

	namespace std
	{
		template <> struct is_integral<       Angle > : std::true_type {};
		template <> struct is_floating_point< Angle > : std::true_type {};
	}

#endif // ANGLE_HPP

template< std::integral T, byte_t D >
class FixedPoint
{
	static_assert( D >= sizeof( T ),                                         "FixedPoint : Template error : D is greater than T" );
	static_assert( std::is_integral_v< T > || std::is_floating_point_v< T >, "FixedPoint : Template error : T is not a number" );
	static_assert( std::is_same_v< T, FixedPoint > == false,                 "FixedPoint : Template error : T is a FixedPoint" );

	#define TU template < typename U, typename = std::enable_if_t<( !std::is_same_v< U, FixedPoint > && ( std::is_integral_v< U > || std::is_floating_point_v< U > ))>>

	protected:
		T _scaledValue; //                          NOTE : real value multiplied by _Scale
		static constexpr T _Scale = pow( 2, D ); // NOTE : scale factor

		inline void setRawValue( T val ){ _scaledValue = val; } // NOTE : rawValue is always _Scale times larger than the represented value

	// ============================ CONSTRUCTORS / DESTRUCTORS
	public:
		inline ~FixedPoint(){};      inline FixedPoint() : _scaledValue( 0 ){}

		inline FixedPoint(           const FixedPoint &fix ){ _scaledValue = fix._scaledValue; }
		inline FixedPoint operator=( const FixedPoint &fix ){ _scaledValue = fix._scaledValue; return *this; }

		inline FixedPoint(           const T &val )
		{
			_scaledValue = static_cast< T >( val * _Scale );
		}
		inline FixedPoint operator=( const T &val ){ _scaledValue = static_cast< T >( val * _Scale ); return *this; }

	// ============================ ACCESSORS / MUTATORS

		inline T   getRawValue() const { return         _scaledValue; }
		inline double getValue() const { return double( _scaledValue ) / _Scale; }

		TU inline void setValue( const U &val ){ _scaledValue = static_cast< T >( val * _Scale );; }

	// ============================ CASTING METHODS

		TU inline operator U() const { return static_cast< U >( double( _scaledValue ) / _Scale ); }

	// ============================ IN-CLASS OPERATORS

	// ============== UNARY OPERATORS

		inline FixedPoint operator+() const { return FixedPoint( *this ); }
		inline FixedPoint operator-() const { FixedPoint r = FixedPoint(); r.setRawValue( -_scaledValue ); return r; }

		inline FixedPoint operator++(){ _scaledValue++; return FixedPoint( *this ); }
		inline FixedPoint operator--(){ _scaledValue--; return FixedPoint( *this ); }

		inline FixedPoint operator++( int ){ FixedPoint tmp( this ); _scaledValue++; return tmp; }
		inline FixedPoint operator--( int ){ FixedPoint tmp( this ); _scaledValue--; return tmp; }

		inline FixedPoint operator~() const { return ~FixedPoint( *this ); }

	// ============== BINARY OPERATORS

		inline FixedPoint operator+( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r += fix; return r; }
		inline FixedPoint operator-( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r -= fix; return r; }
		inline FixedPoint operator*( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r *= fix; return r; }
		inline FixedPoint operator/( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r /= fix; return r; }
		inline FixedPoint operator%( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r %= fix; return r; }

		inline FixedPoint operator+=( const FixedPoint &fix ){ _scaledValue += fix._scaledValue; return FixedPoint( *this ); }
		inline FixedPoint operator-=( const FixedPoint &fix ){ _scaledValue -= fix._scaledValue; return FixedPoint( *this ); }
		inline FixedPoint operator*=( const FixedPoint &fix ){ _scaledValue *= fix.getValue();   return FixedPoint( *this ); } // NOTE : doing it like this avoids overflows
		inline FixedPoint operator/=( const FixedPoint &fix ){ _scaledValue /= fix.getValue();   return FixedPoint( *this ); } // NOTE : doing it like this avoids overflows
		inline FixedPoint operator%=( const FixedPoint &fix ){ _scaledValue %= fix.getValue();   return FixedPoint( *this ); } // NOTE : doing it like this avoids overflows

	// ============== COMPARISON OPERATORS

		inline bool operator==( const FixedPoint &fix ) const { return ( _scaledValue == fix._scaledValue ); }
		inline bool operator!=( const FixedPoint &fix ) const { return ( _scaledValue != fix._scaledValue ); }
		inline bool operator<=( const FixedPoint &fix ) const { return ( _scaledValue <= fix._scaledValue ); }
		inline bool operator>=( const FixedPoint &fix ) const { return ( _scaledValue >= fix._scaledValue ); }
		inline bool operator< ( const FixedPoint &fix ) const { return ( _scaledValue <  fix._scaledValue ); }
		inline bool operator> ( const FixedPoint &fix ) const { return ( _scaledValue >  fix._scaledValue ); }

	// ============== BITWISE OPERATORS
		inline FixedPoint operator&( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r &= fix; return r; }
		inline FixedPoint operator|( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r |= fix; return r; }
		inline FixedPoint operator^( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r ^= fix; return r; }

		inline FixedPoint operator&=( const FixedPoint &fix ){ _scaledValue &= fix._scaledValue; return FixedPoint( *this ); }
		inline FixedPoint operator|=( const FixedPoint &fix ){ _scaledValue |= fix._scaledValue; return FixedPoint( *this ); }
		inline FixedPoint operator^=( const FixedPoint &fix ){ _scaledValue ^= fix._scaledValue; return FixedPoint( *this ); }

	// ============== SHIFT OPERATORS
		inline FixedPoint operator<<( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r <<= fix; return r; }
		inline FixedPoint operator>>( const FixedPoint &fix ) const { FixedPoint r = FixedPoint( *this ); r >>= fix; return r; }

		inline FixedPoint operator<<=( const FixedPoint &fix ){ _scaledValue <<= static_cast< ulong >( fix.getValue() ); return FixedPoint( *this ); }
		inline FixedPoint operator>>=( const FixedPoint &fix ){ _scaledValue >>= static_cast< ulong >( fix.getValue() ); return FixedPoint( *this ); }

	// ============================ TEMPLATE METHODES

	// ============== BINARY OPERATORS

		TU inline FixedPoint operator+( const U &val ) const { FixedPoint r = FixedPoint( *this ); r += val; return r; }
		TU inline FixedPoint operator-( const U &val ) const { FixedPoint r = FixedPoint( *this ); r -= val; return r; }
		TU inline FixedPoint operator*( const U &val ) const { FixedPoint r = FixedPoint( *this ); r *= val; return r; }
		TU inline FixedPoint operator/( const U &val ) const { FixedPoint r = FixedPoint( *this ); r /= val; return r; }
		TU inline FixedPoint operator%( const U &val ) const { FixedPoint r = FixedPoint( *this ); r %= val; return r; }

		TU inline FixedPoint operator+=( const U &val ){ _scaledValue += static_cast< T >( val * _Scale ); return FixedPoint( *this ); }
		TU inline FixedPoint operator-=( const U &val ){ _scaledValue -= static_cast< T >( val * _Scale ); return FixedPoint( *this ); }
		TU inline FixedPoint operator*=( const U &val ){ _scaledValue *= static_cast< T >( val * _Scale ); return FixedPoint( *this ); }
		TU inline FixedPoint operator/=( const U &val ){ _scaledValue /= static_cast< T >( val * _Scale ); return FixedPoint( *this ); }
		TU inline FixedPoint operator%=( const U &val ){ _scaledValue %= static_cast< T >( val * _Scale ); return FixedPoint( *this ); }

	// ============== COMPARISON OPERATORS

		TU inline bool operator==( const U &val ) const { return ( _scaledValue == static_cast< T >( val * _Scale )); }
		TU inline bool operator!=( const U &val ) const { return ( _scaledValue != static_cast< T >( val * _Scale )); }
		TU inline bool operator<=( const U &val ) const { return ( _scaledValue <= static_cast< T >( val * _Scale )); }
		TU inline bool operator>=( const U &val ) const { return ( _scaledValue >= static_cast< T >( val * _Scale )); }
		TU inline bool operator< ( const U &val ) const { return ( _scaledValue <  static_cast< T >( val * _Scale )); }
		TU inline bool operator> ( const U &val ) const { return ( _scaledValue >  static_cast< T >( val * _Scale )); }

	// ============== BITWISE OPERATORS

		TU inline FixedPoint operator&( const U &val ) const { FixedPoint r = FixedPoint( *this ); r &= val; return r; }
		TU inline FixedPoint operator|( const U &val ) const { FixedPoint r = FixedPoint( *this ); r |= val; return r; }
		TU inline FixedPoint operator^( const U &val ) const { FixedPoint r = FixedPoint( *this ); r ^= val; return r; }

		TU inline FixedPoint operator&=( const U &val ){ _scaledValue &= static_cast< T >( val * _Scale ); return FixedPoint( *this ); }
		TU inline FixedPoint operator|=( const U &val ){ _scaledValue |= static_cast< T >( val * _Scale ); return FixedPoint( *this ); }
		TU inline FixedPoint operator^=( const U &val ){ _scaledValue ^= static_cast< T >( val * _Scale ); return FixedPoint( *this ); }

	// ============== SHIFT OPERATORS

		TU inline FixedPoint operator<<( const U &val ) const { FixedPoint r = FixedPoint( *this ); r <<= val; return r; }
		TU inline FixedPoint operator>>( const U &val ) const { FixedPoint r = FixedPoint( *this ); r >>= val; return r; }

		TU inline FixedPoint operator<<=( const U &val ){ _scaledValue <<= static_cast< ulong >( val ); return FixedPoint( *this ); }
		TU inline FixedPoint operator>>=( const U &val ){ _scaledValue >>= static_cast< ulong >( val ); return FixedPoint( *this ); }

	// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const FixedPoint &fix ){ os << double( fix ); return os; }
		inline friend std::string to_string( const FixedPoint &fix ){ return to_string( double( fix )); }

		#undef TU

	};

	// ============================ MARKING POS2 AS VALID INTEGRAL / FLOATING POINT TYPE

	namespace std
	{
		template < std::integral T, byte_t D > struct is_integral<       FixedPoint< T, D >> : std::true_type {};
		template < std::integral T, byte_t D > struct is_floating_point< FixedPoint< T, D >> : std::true_type {};
	}

// ============================ SIGNED FIXED POINT TYPES

typedef FixedPoint< int8_t,  4  > fxt_8x4_t;
typedef FixedPoint< int16_t, 4  > fxt_16x4_t;
typedef FixedPoint< int16_t, 8  > fxt_16x8_t;
typedef FixedPoint< int16_t, 12 > fxt_16x12_t;

typedef FixedPoint< int32_t, 8  > fxt_32x8_t;
typedef FixedPoint< int32_t, 12 > fxt_32x12_t;
typedef FixedPoint< int32_t, 16 > fxt_32x16_t;
typedef FixedPoint< int32_t, 20 > fxt_32x20_t;
typedef FixedPoint< int32_t, 24 > fxt_32x24_t;

typedef FixedPoint< int64_t, 16 > fxt_64x16_t;
typedef FixedPoint< int64_t, 24 > fxt_64x24_t;
typedef FixedPoint< int64_t, 32 > fxt_64x32_t;
typedef FixedPoint< int64_t, 40 > fxt_64x40_t;
typedef FixedPoint< int64_t, 48 > fxt_64x48_t;

// ============================ UNSIGNED FIXED POINT TYPES

typedef FixedPoint< uint8_t,  4  > ufx_8x4_t;
typedef FixedPoint< uint16_t, 4  > ufx_16x4_t;
typedef FixedPoint< uint16_t, 8  > ufx_16x8_t;
typedef FixedPoint< uint16_t, 12 > ufx_16x12_t;

typedef FixedPoint< uint32_t, 8  > ufx_32x8_t;
typedef FixedPoint< uint32_t, 12 > ufx_32x12_t;
typedef FixedPoint< uint32_t, 16 > ufx_32x16_t;
typedef FixedPoint< uint32_t, 20 > ufx_32x20_t;
typedef FixedPoint< uint32_t, 24 > ufx_32x24_t;

typedef FixedPoint< uint64_t, 16 > ufx_64x16_t;
typedef FixedPoint< uint64_t, 24 > ufx_64x24_t;
typedef FixedPoint< uint64_t, 32 > ufx_64x32_t;
typedef FixedPoint< uint64_t, 40 > ufx_64x40_t;
typedef FixedPoint< uint64_t, 48 > ufx_64x48_t;

// ============================ DEFAULT FIXED POINT TYPE

typedef fxt_64x32_t fixed_t; // NOTE : default fixed point type


#endif // FIXED_POINT_HPP