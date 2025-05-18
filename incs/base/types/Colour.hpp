#ifndef COLOUR_HPP
# define COLOUR_HPP

#include <cstddef>
# include <raylib.h>
# include "../core.hpp"

class Colour
{
	public:
		byte_t r, g, b, a;

		inline Colour() : r( 0 ), g( 0 ), b( 0 ), a( 255 ){}
		inline Colour( const byte_t &r_, const byte_t &g_, const byte_t &b_, const byte_t &a_ = 255 ) : r( r_ ), g( g_ ), b( b_ ), a( a_ ){}

		inline Colour( const Colour   &c ) : r( c.r ), g( c.g ), b( c.b ), a( c.a ){}
		inline Colour( const Color    &c ) : r( c.r ), g( c.g ), b( c.b ), a( c.a ){} // RAYLIB COLOR
		inline Colour( const uint32_t &c ) : r(( c >> 24 ) & 0xFF ), g(( c >> 16 ) & 0xFF ), b(( c >> 8 ) & 0xFF ), a( c & 0xFF ){}

		inline Colour operator=( const Colour   &c ){ r = c.r; g = c.g; b = c.b; a = c.a; return *this; }
		inline Colour operator=( const Color    &c ){ r = c.r; g = c.g; b = c.b; a = c.a; return *this; } // RAYLIB COLOR
		inline Colour operator=( const uint32_t &c ){ r = ( c >> 24 ) & 0xFF; g = ( c >> 16 ) & 0xFF; b = ( c >> 8 ) & 0xFF; a = c & 0xFF; return *this; }

		inline operator Color()    const { return ( Color ){ r, g, b, a }; } // RAYLIB COLOR
		inline operator uint32_t() const
		{
			return (( static_cast< uint32_t >( r ) << 24 ) |
			        ( static_cast< uint32_t >( g ) << 16 ) |
			        ( static_cast< uint32_t >( b ) <<  8 ) |
			        ( static_cast< uint32_t >( a )));
		}

		// ============================ BASE OPERATORS

		inline Colour operator+( const byte_t &val ) const { Colour x = Colour( *this ); x += val; return x; } // NOTE : this will ignores alpha
		inline Colour operator-( const byte_t &val ) const { Colour x = Colour( *this ); x -= val; return x; } // NOTE : this will  ignores alpha

		inline Colour operator+( const Color  &c   ) const { Colour x = Colour( *this ); x += c;   return x; } // RAYLIB COLOR
		inline Colour operator-( const Color  &c   ) const { Colour x = Colour( *this ); x -= c;   return x; } // RAYLIB COLOR

		inline Colour operator+( const Colour &c   ) const { Colour x = Colour( *this ); x += c;   return x; }
		inline Colour operator-( const Colour &c   ) const { Colour x = Colour( *this ); x -= c;   return x; }

		inline Colour operator*( const byte_t &val ) const { Colour x = Colour( *this ); x *= val; return x; }
		inline Colour operator/( const byte_t &val ) const { Colour x = Colour( *this ); x /= val; return x; }
		inline Colour operator%( const byte_t &stp ) const { Colour x = Colour( *this ); x %= stp; return x; }

		// ============================ INCREMENTAL OPERATORS

		inline Colour operator+=( const byte_t &val ){ return *this += Colour( r + val, g + val, b + val, 0 ); } // NOTE : this ignores alpha
		inline Colour operator-=( const byte_t &val ){ return *this -= Colour( r - val, g - val, b - val, 0 ); } // NOTE : this ignores alpha

		inline Colour operator+=( const Color  &c   ){ return *this += Colour( r - c.r, g - c.g, b - c.b, a * c.a ); } // RAYLIB COLOR
		inline Colour operator-=( const Color  &c   ){ return *this -= Colour( r - c.r, g - c.g, b - c.b, a * c.a ); } // RAYLIB COLOR

		inline Colour operator+=( const Colour &c   )
		{
			int16_t r_ = int16_t( r ) + c.r;   if ( r_ > 255 ) r_ = 255;   r = byte_t( r_ );
			int16_t g_ = int16_t( g ) + c.g;   if ( g_ > 255 ) g_ = 255;   g = byte_t( g_ );
			int16_t b_ = int16_t( b ) + c.b;   if ( b_ > 255 ) b_ = 255;   b = byte_t( b_ );
			int16_t a_ = int16_t( a ) + c.a;   if ( a_ > 255 ) a_ = 255;   a = byte_t( a_ );

			return *this;
		}

		inline Colour operator-=( const Colour &c   )
		{
			int16_t r_ = int16_t( r ) - c.r;   if ( r_ < 0 ) r_ = 0;       r = byte_t( r_ );
			int16_t g_ = int16_t( g ) - c.g;   if ( g_ < 0 ) g_ = 0;       g = byte_t( g_ );
			int16_t b_ = int16_t( b ) - c.b;   if ( b_ < 0 ) b_ = 0;       b = byte_t( b_ );
			int16_t a_ = int16_t( a ) - c.a;   if ( a_ < 0 ) a_ = 0;       a = byte_t( a_ );

			return *this;
		}

		inline Colour operator*=( const byte_t &val )
		{
			int16_t r_ = int16_t( r ) * val;   if ( r_ > 255 ) r_ = 255;   r = byte_t( r_ );
			int16_t g_ = int16_t( g ) * val;   if ( g_ > 255 ) g_ = 255;   g = byte_t( g_ );
			int16_t b_ = int16_t( b ) * val;   if ( b_ > 255 ) b_ = 255;   b = byte_t( b_ );
			int16_t a_ = int16_t( a ) * val;   if ( a_ > 255 ) a_ = 255;   a = byte_t( a_ );

			return *this;
		}

		inline Colour operator/=( const byte_t &val )
		{
			if ( val == 0 )
			{
				qlog( "Colour : Division by zero : voiding value", ERROR, 0 );
				r = g = b = a = 0;
				return *this;
			}

			int16_t r_ = int16_t( r ) / val;   if ( r_ > 255 ) r_ = 255;   r = byte_t( r_ );
			int16_t g_ = int16_t( g ) / val;   if ( g_ > 255 ) g_ = 255;   g = byte_t( g_ );
			int16_t b_ = int16_t( b ) / val;   if ( b_ > 255 ) b_ = 255;   b = byte_t( b_ );
			int16_t a_ = int16_t( a ) / val;   if ( a_ > 255 ) a_ = 255;   a = byte_t( a_ );

			return *this;
		}

		inline Colour operator%=( const byte_t &stp )
		{
			r -= ( r % stp );
			g -= ( g % stp );
			b -= ( b % stp );
			a -= ( a % stp );

			return *this;
		}

		// ============================ BOOLEAN OPERATORS

		inline bool operator==( const Colour &c ) const { return ( r == c.r && g == c.g && b == c.b && a == c.a ); }
		inline bool operator!=( const Colour &c ) const { return ( r != c.r || g != c.g || b != c.b || a != c.a ); }

		inline bool operator>=( const Colour &c ) const { return ( r >= c.r && g >= c.g && b >= c.b && a >= c.a ); }
		inline bool operator<=( const Colour &c ) const { return ( r <= c.r && g <= c.g && b <= c.b && a <= c.a ); }

		inline bool operator> ( const Colour &c ) const { return ( r >  c.r && g >  c.g && b >  c.b && a >  c.a ); }
		inline bool operator< ( const Colour &c ) const { return ( r <  c.r && g <  c.g && b <  c.b && a <  c.a ); }
};


// ============================ DEFAULT COLOUR TYPE ( only one possible for now )

typedef Colour col_t;

#endif // COLOUR_HPP