#ifndef FIXED_POINT_HPP
# define FIXED_POINT_HPP

# include "../core.hpp"

// TODO : make sure this handles negative vals properly
// TODO : make sure this handles under/overflows properly
// TODO : make sure this handles rounding properly
// TODO : use template for int and floats instead of hardcoding them

template< std::integral T, byte_t D >
class FixedPoint
{
	static_assert( D >= sizeof( T ), "FixedPoint : Template error : D >= T" );
	static_assert( std::integral< T > || std::floating_point< T >, "FixedPoint : Template error : T is not a number" );
	static_assert( std::is_same< T, FixedPoint >::value == false, "FixedPoint : Template error : T is a FixedPoint" );

	#define TU template < typename U >

	protected:
		T _rawValue; //                                   NOTE : can be negative, depending on the template type
		static const byte_t _Digits = D; //               NOTE : number of decimal digits
		static constexpr T _Scale = pow( 2, _Digits ); // NOTE : scale factor

		inline void setRawValue( T val ){ _rawValue = val; }

	// ============================ CONSTRUCTORS / DESTRUCTORS
	public:
		inline ~FixedPoint(){};    inline FixedPoint() : _rawValue( 0 ){}

		inline FixedPoint(           const FixedPoint &fix ){ _rawValue = fix._rawValue; }
		inline FixedPoint operator=( const FixedPoint &fix ){ _rawValue = fix._rawValue; return *this; }

		inline FixedPoint(           const T &val ){ _rawValue = T( val * _Scale ); }
		inline FixedPoint operator=( const T &val ){ _rawValue = T( val * _Scale ); return *this; }

	// ============================ ACCESSORS / MUTATORS

		inline T getRawValue() const { return    _rawValue; } // returns the raw value
		inline T getValue()    const { return T( _rawValue / _Scale ); }

		inline void setValue( T val ){ _rawValue = T( val * _Scale ); }

	// ============================ CASTING METHODS

		explicit inline operator T() const { return _rawValue / _Digits; }

	// ============================ IN-CLASS OPERATORS

		inline FixedPoint operator+() const { return FixedPoint( +_rawValue ); }
		inline FixedPoint operator-() const { return FixedPoint( -_rawValue ); }

		inline FixedPoint operator++(){ _rawValue++; return FixedPoint( _rawValue ); }
		inline FixedPoint operator--(){ _rawValue--; return FixedPoint( _rawValue ); }

		inline FixedPoint operator++( int ){ FixedPoint tmp( _rawValue ); _rawValue++; return tmp; }
		inline FixedPoint operator--( int ){ FixedPoint tmp( _rawValue ); _rawValue--; return tmp; }

		inline FixedPoint operator+( const FixedPoint &fix ) const { return FixedPoint( _rawValue + fix._rawValue ); }
		inline FixedPoint operator-( const FixedPoint &fix ) const { return FixedPoint( _rawValue - fix._rawValue ); }
		inline FixedPoint operator*( const FixedPoint &fix ) const { return FixedPoint( _rawValue * fix._rawValue ); }
		inline FixedPoint operator/( const FixedPoint &fix ) const { return FixedPoint( _rawValue / fix._rawValue ); }
		inline FixedPoint operator%( const FixedPoint &fix ) const { return FixedPoint( fmod( _rawValue, fix._rawValue )); }

		inline FixedPoint operator+=( const FixedPoint &fix ) { _rawValue += fix._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator-=( const FixedPoint &fix ) { _rawValue -= fix._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator*=( const FixedPoint &fix ) { _rawValue *= fix._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator/=( const FixedPoint &fix ) { _rawValue /= fix._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator%=( const FixedPoint &fix ) { _rawValue = fmod( _rawValue, fix._rawValue ); return FixedPoint( _rawValue ); }

		inline bool operator==( const FixedPoint &fix ) const { return _rawValue == fix._rawValue; }
		inline bool operator!=( const FixedPoint &fix ) const { return _rawValue != fix._rawValue; }
		inline bool operator<=( const FixedPoint &fix ) const { return _rawValue <= fix._rawValue; }
		inline bool operator>=( const FixedPoint &fix ) const { return _rawValue >= fix._rawValue; }
		inline bool operator<(  const FixedPoint &fix ) const { return _rawValue <  fix._rawValue; }
		inline bool operator>(  const FixedPoint &fix ) const { return _rawValue >  fix._rawValue; }

		// ============================ TYPENAME OPERATORS

		TU inline FixedPoint operator+( const U &val ) const { return FixedPoint( Operate< T, U >::add( _rawValue, Operate< T, U >::mul( _Scale, val ))); }
		TU inline FixedPoint operator-( const U &val ) const { return FixedPoint( Operate< T, U >::sub( _rawValue, Operate< T, U >::mul( _Scale, val ))); }
		TU inline FixedPoint operator*( const U &val ) const { return FixedPoint( Operate< T, U >::mul( _rawValue, Operate< T, U >::mul( _Scale, val ))); }
		TU inline FixedPoint operator/( const U &val ) const { return FixedPoint( Operate< T, U >::div( _rawValue, Operate< T, U >::mul( _Scale, val ))); }
		TU inline FixedPoint operator%( const U &val ) const { return FixedPoint( Operate< T, U >::mod( _rawValue, Operate< T, U >::mul( _Scale, val ))); }

		TU inline FixedPoint operator+=( const U &val ){ _rawValue = Operate< T, U >::add( _rawValue, Operate< U, T >::mul( val, _Scale )); return FixedPoint( _rawValue ); }
		TU inline FixedPoint operator-=( const U &val ){ _rawValue = Operate< T, U >::sub( _rawValue, Operate< U, T >::mul( val, _Scale )); return FixedPoint( _rawValue ); }
		TU inline FixedPoint operator*=( const U &val ){ _rawValue = Operate< T, U >::mul( _rawValue, Operate< U, T >::mul( val, _Scale )); return FixedPoint( _rawValue ); }
		TU inline FixedPoint operator/=( const U &val ){ _rawValue = Operate< T, U >::div( _rawValue, Operate< U, T >::mul( val, _Scale )); return FixedPoint( _rawValue ); }
		TU inline FixedPoint operator%=( const U &val ){ _rawValue = Operate< T, U >::mod( _rawValue, Operate< U, T >::mul( val, _Scale )); return FixedPoint( _rawValue ); }

		TU inline bool operator==( const U &val ) const { return _rawValue == Operate< T, U >::mul( _Scale, val ); }
		TU inline bool operator!=( const U &val ) const { return _rawValue != Operate< T, U >::mul( _Scale, val ); }
		TU inline bool operator<=( const U &val ) const { return _rawValue <= Operate< T, U >::mul( _Scale, val ); }
		TU inline bool operator>=( const U &val ) const { return _rawValue >= Operate< T, U >::mul( _Scale, val ); }
		TU inline bool operator<(  const U &val ) const { return _rawValue <  Operate< T, U >::mul( _Scale, val ); }
		TU inline bool operator>(  const U &val ) const { return _rawValue >  Operate< T, U >::mul( _Scale, val ); }

		// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const FixedPoint &fix ){ os << double( fix ); return os; }

		#undef TU

	};

	// ============================ MARKING POS2 AS VALID INTEGRAL / FLOATING POINT TYPE

	namespace std
	{
		template < std::integral T, byte_t D >
		struct is_integral< FixedPoint< T, D >> : std::true_type {};

		template < std::integral T, byte_t D >
		struct is_floating_point< FixedPoint< T, D >> : std::true_type {};
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