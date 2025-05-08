#ifndef FIXED_POINT_HPP
# define FIXED_POINT_HPP

# include "../core.hpp"

// TODO : make sure this handles negative values properly
// TODO : make sure this handles under/overflows properly
// TODO : make sure this handles rounding properly
// TODO : use template for int and floats instead of hardcoding them
// TODO : review which modulus fonction to use ( how should negativs behave ? )

# define FP_MODULUS( a, b ) fmod( a, b ) // NOTE : this is not the same as the % operator)

# include <concepts>

template< std::integral T, byte_t D >
class FixedPoint
{
	static_assert( D < sizeof( T ), "FixedPoint : Template error : D >= T" );

	protected:
		T _rawValue; //                     NOTE : can be negative, depending on the template type
		static const byte_t _Digits = D; // NOTE : number of decimal digits
		static const T _Scale = pow( 10, _Digits ); // NOTE : scale factor

		inline void setRawValue( T value ){ _rawValue = value; }

	// ============================ CONSTRUCTORS / DESTRUCTORS
	public:
		inline ~FixedPoint(){};    inline FixedPoint() : _rawValue( 0 ){}

		inline FixedPoint( const FixedPoint &a ){ _rawValue = a._rawValue; }
		inline FixedPoint operator=( const FixedPoint &a ){ _rawValue = a._rawValue; return *this; }

		inline FixedPoint( double value ){ _rawValue = (T) ( value * _Scale ); }
		inline FixedPoint( float  value ){ _rawValue = (T) ( value * _Scale ); }
		inline FixedPoint( long   value ){ _rawValue = (T) ( value * _Scale ); }
		inline FixedPoint( int    value ){ _rawValue = (T) ( value * _Scale ); }

		inline FixedPoint operator=( double value ){ _rawValue = (T) ( value * _Scale ); return *this; }
		inline FixedPoint operator=( float  value ){ _rawValue = (T) ( value * _Scale ); return *this; }
		inline FixedPoint operator=( long   value ){ _rawValue = (T) ( value * _Scale ); return *this; }
		inline FixedPoint operator=( int    value ){ _rawValue = (T) ( value * _Scale ); return *this; }

	// ============================ ACCESSORS / MUTATORS

		inline T getRawValue() const { return _rawValue; } // returns the raw value
		inline T getValue()    const { return (T) (_rawValue / _Scale ); } // returns the value

		inline void setValue( T value ){ _rawValue = (T) ( value * _Scale ); } // sets the value

	// ============================ CASTING METHODS

		explicit inline operator double()  const { return (double)( _rawValue >> _Digits ); }
		explicit inline operator float()   const { return (float )( _rawValue >> _Digits ); }
		explicit inline operator long()    const { return (long  )( _rawValue >> _Digits ); }
		explicit inline operator int()     const { return (int   )( _rawValue >> _Digits ); }

	// ============================ IN-CLASS OPERATORS

		inline FixedPoint operator+() const { return FixedPoint( +_rawValue ); }
		inline FixedPoint operator-() const { return FixedPoint( -_rawValue ); }

		inline FixedPoint operator++(){ _rawValue++; return FixedPoint( _rawValue ); }
		inline FixedPoint operator--(){ _rawValue--; return FixedPoint( _rawValue ); }

		inline FixedPoint operator++( int ){ FixedPoint tmp( _rawValue ); _rawValue++; return tmp; }
		inline FixedPoint operator--( int ){ FixedPoint tmp( _rawValue ); _rawValue--; return tmp; }

		inline FixedPoint operator+( const FixedPoint &a ) const { return FixedPoint( _rawValue + a._rawValue ); }
		inline FixedPoint operator-( const FixedPoint &a ) const { return FixedPoint( _rawValue - a._rawValue ); }
		inline FixedPoint operator*( const FixedPoint &a ) const { return FixedPoint( _rawValue * a._rawValue ); }
		inline FixedPoint operator/( const FixedPoint &a ) const { return FixedPoint( _rawValue / a._rawValue ); }
		inline FixedPoint operator%( const FixedPoint &a ) const { return FixedPoint( FP_MODULUS( _rawValue, a._rawValue )); }

		inline FixedPoint operator+=( const FixedPoint &a ) { _rawValue += a._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator-=( const FixedPoint &a ) { _rawValue -= a._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator*=( const FixedPoint &a ) { _rawValue *= a._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator/=( const FixedPoint &a ) { _rawValue /= a._rawValue; return FixedPoint( _rawValue ); }
		inline FixedPoint operator%=( const FixedPoint &a ) { _rawValue = FP_MODULUS( _rawValue, a._rawValue ); return FixedPoint( _rawValue ); }

		inline bool operator==( const FixedPoint &a ) const { return _rawValue == a._rawValue; }
		inline bool operator!=( const FixedPoint &a ) const { return _rawValue != a._rawValue; }
		inline bool operator<=( const FixedPoint &a ) const { return _rawValue <= a._rawValue; }
		inline bool operator>=( const FixedPoint &a ) const { return _rawValue >= a._rawValue; }
		inline bool operator<(  const FixedPoint &a ) const { return _rawValue <  a._rawValue; }
		inline bool operator>(  const FixedPoint &a ) const { return _rawValue >  a._rawValue; }

		// ============================ INT OPERATORS

		inline FixedPoint operator+( const int &a ) const { return FixedPoint( _rawValue + ( a * _Scale )); }
		inline FixedPoint operator-( const int &a ) const { return FixedPoint( _rawValue - ( a * _Scale )); }
		inline FixedPoint operator*( const int &a ) const { return FixedPoint( _rawValue * ( a * _Scale )); }
		inline FixedPoint operator/( const int &a ) const { return FixedPoint( _rawValue / ( a * _Scale )); }
		inline FixedPoint operator%( const int &a ) const { return FixedPoint( FP_MODULUS( _rawValue, a * _Scale )); }

		inline FixedPoint operator+=( const int &a ){ _rawValue += ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator-=( const int &a ){ _rawValue -= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator*=( const int &a ){ _rawValue *= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator/=( const int &a ){ _rawValue /= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator%=( const int &a ){ _rawValue = FP_MODULUS( _rawValue, a * _Scale ); return FixedPoint( _rawValue ); }

		inline bool operator==( const int &a ) const { return _rawValue == ( a * _Scale ); }
		inline bool operator!=( const int &a ) const { return _rawValue != ( a * _Scale ); }
		inline bool operator<=( const int &a ) const { return _rawValue <= ( a * _Scale ); }
		inline bool operator>=( const int &a ) const { return _rawValue >= ( a * _Scale ); }
		inline bool operator<(  const int &a ) const { return _rawValue <  ( a * _Scale ); }
		inline bool operator>(  const int &a ) const { return _rawValue >  ( a * _Scale ); }

		// ============================ LONG OPERATORS

		inline FixedPoint operator+( const long &a ) const { return FixedPoint( _rawValue + ( a * _Scale )); }
		inline FixedPoint operator-( const long &a ) const { return FixedPoint( _rawValue - ( a * _Scale )); }
		inline FixedPoint operator*( const long &a ) const { return FixedPoint( _rawValue * ( a * _Scale )); }
		inline FixedPoint operator/( const long &a ) const { return FixedPoint( _rawValue / ( a * _Scale )); }
		inline FixedPoint operator%( const long &a ) const { return FixedPoint( FP_MODULUS( _rawValue, a * _Scale )); }

		inline FixedPoint operator+=( const long &a ){ _rawValue += ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator-=( const long &a ){ _rawValue -= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator*=( const long &a ){ _rawValue *= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator/=( const long &a ){ _rawValue /= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator%=( const long &a ){ _rawValue = FP_MODULUS( _rawValue, a * _Scale); return FixedPoint( _rawValue ); }

		inline bool operator==( const long &a ) const { return _rawValue == ( a * _Scale ); }
		inline bool operator!=( const long &a ) const { return _rawValue != ( a * _Scale ); }
		inline bool operator<=( const long &a ) const { return _rawValue <= ( a * _Scale ); }
		inline bool operator>=( const long &a ) const { return _rawValue >= ( a * _Scale ); }
		inline bool operator<(  const long &a ) const { return _rawValue <  ( a * _Scale ); }
		inline bool operator>(  const long &a ) const { return _rawValue >  ( a * _Scale ); }

		// ============================ FLOAT OPERATORS // NOTE : this will lead to precision loss

		inline FixedPoint operator+( const float &a ) const { return FixedPoint( _rawValue + ( a * _Scale )); }
		inline FixedPoint operator-( const float &a ) const { return FixedPoint( _rawValue - ( a * _Scale )); }
		inline FixedPoint operator*( const float &a ) const { return FixedPoint( _rawValue * ( a * _Scale )); }
		inline FixedPoint operator/( const float &a ) const { return FixedPoint( _rawValue / ( a * _Scale )); }
		inline FixedPoint operator%( const float &a ) const { return FixedPoint( FP_MODULUS( _rawValue, a * _Scale )); }

		inline FixedPoint operator+=( const float &a ){ _rawValue += ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator-=( const float &a ){ _rawValue -= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator*=( const float &a ){ _rawValue *= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator/=( const float &a ){ _rawValue /= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator%=( const float &a ){ _rawValue = FP_MODULUS( _rawValue, a * _Scale ); return FixedPoint( _rawValue ); }

		inline bool operator==( const float &a ) const { return _rawValue == ( a * _Scale ); }
		inline bool operator!=( const float &a ) const { return _rawValue != ( a * _Scale ); }
		inline bool operator<=( const float &a ) const { return _rawValue <= ( a * _Scale ); }
		inline bool operator>=( const float &a ) const { return _rawValue >= ( a * _Scale ); }
		inline bool operator<(  const float &a ) const { return _rawValue <  ( a * _Scale ); }
		inline bool operator>(  const float &a ) const { return _rawValue >  ( a * _Scale ); }

		// ============================ DOUBLE OPERATORS // NOTE : this will lead to precision loss

		inline FixedPoint operator+( const double &a ) const { return FixedPoint( _rawValue + ( a * _Scale )); }
		inline FixedPoint operator-( const double &a ) const { return FixedPoint( _rawValue - ( a * _Scale )); }
		inline FixedPoint operator*( const double &a ) const { return FixedPoint( _rawValue * ( a * _Scale )); }
		inline FixedPoint operator/( const double &a ) const { return FixedPoint( _rawValue / ( a * _Scale )); }
		inline FixedPoint operator%( const double &a ) const { return FixedPoint( FP_MODULUS( _rawValue, a * _Scale )); }

		inline FixedPoint operator+=( const double &a ){ _rawValue += ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator-=( const double &a ){ _rawValue -= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator*=( const double &a ){ _rawValue *= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator/=( const double &a ){ _rawValue /= ( a * _Scale ); return FixedPoint( _rawValue ); }
		inline FixedPoint operator%=( const double &a ){ _rawValue = FP_MODULUS( _rawValue, a * _Scale ); return FixedPoint( _rawValue ); }

		inline bool operator==( const double &a ) const { return _rawValue == ( a * _Scale ); }
		inline bool operator!=( const double &a ) const { return _rawValue != ( a * _Scale ); }
		inline bool operator<=( const double &a ) const { return _rawValue <= ( a * _Scale ); }
		inline bool operator>=( const double &a ) const { return _rawValue >= ( a * _Scale ); }
		inline bool operator<(  const double &a ) const { return _rawValue <  ( a * _Scale ); }
		inline bool operator>(  const double &a ) const { return _rawValue >  ( a * _Scale ); }

		// ============================ FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const FixedPoint &a ){ os << (double)a; return os; }
	};

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

typedef fxt_64x32_t fixed_t; // default fixed point type


#endif // FIXED_POINT_HPP