#ifndef COLOUR_HPP
# define COLOUR_HPP

# include "../defs.hpp"

class Colour
{
	public:
		byte_t r, g, b, a;

	// ============================ CONSTRUCTORS / DESTRUCTORS
		inline Colour() : r( 0 ), g( 0 ), b( 0 ), a( 255 ){}
		inline Colour( const byte_t &r_, const byte_t &g_, const byte_t &b_, const byte_t &a_ = 255 ) : r( r_ ), g( g_ ), b( b_ ), a( a_ ){}

		inline Colour( const Colour   &c ) : r( c.r ), g( c.g ), b( c.b ), a( c.a ){}
		inline Colour( const Color    &c ) : r( c.r ), g( c.g ), b( c.b ), a( c.a ){} // RAYLIB COLOR
		inline Colour( const uint32_t &c ) : r(( c >> 24 ) & 0xFF ), g(( c >> 16 ) & 0xFF ), b(( c >> 8 ) & 0xFF ), a( c & 0xFF ){}

		inline Colour operator=( const Colour   &c ){ r = c.r; g = c.g; b = c.b; a = c.a; return *this; }
		inline Colour operator=( const Color    &c ){ r = c.r; g = c.g; b = c.b; a = c.a; return *this; } // RAYLIB COLOR
		inline Colour operator=( const uint32_t &c ){ r = ( c >> 24 ) & 0xFF; g = ( c >> 16 ) & 0xFF; b = ( c >> 8 ) & 0xFF; a = c & 0xFF; return *this; }

	// ============================ CAST METHODS
		inline operator Color()    const { return ( Color ){ r, g, b, a }; } // RAYLIB COLOR
		inline operator uint32_t() const
		{
			return (( static_cast< uint32_t >( r ) << 24 ) |
			        ( static_cast< uint32_t >( g ) << 16 ) |
			        ( static_cast< uint32_t >( b ) <<  8 ) |
			        ( static_cast< uint32_t >( a )));
		}

	// ============================ ACCESSORS / MUTATORS
		inline byte_t getR() const { return r; }
		inline byte_t getG() const { return g; }
		inline byte_t getB() const { return b; }
		inline byte_t getA() const { return a; }

		inline void setR( const byte_t &r_ ){ r = r_; }
		inline void setG( const byte_t &g_ ){ g = g_; }
		inline void setB( const byte_t &b_ ){ b = b_; }
		inline void setA( const byte_t &a_ ){ a = a_; }

		inline void setRGBA( const Colour   &c ) { r = c.r; g = c.g; b = c.b; a = c.a; }
		inline void setRGBA( const Color    &c ) { r = c.r; g = c.g; b = c.b; a = c.a; } // RAYLIB COLOR
		inline void setRGBA( const uint32_t &c )
		{
			r = ( c >> 24 ) & 0xFF;
			g = ( c >> 16 ) & 0xFF;
			b = ( c >> 8  ) & 0xFF;
			a =   c         & 0xFF;
		}
		inline void setRGBA( const byte_t &r_, const byte_t &g_, const byte_t &b_, const byte_t &a_ )
		{
			r = r_;    g = g_;   b = b_;   a = a_;
		}

		inline void setRGB( const Colour   &c ){ r = c.r; g = c.g; b = c.b; }
		inline void setRGB( const Color    &c ){ r = c.r; g = c.g; b = c.b; } // RAYLIB COLOR
		inline void setRGB( const uint32_t &c )
		{
			r = ( c >> 24 ) & 0xFF;
			g = ( c >> 16 ) & 0xFF;
			b = ( c >> 8  ) & 0xFF;
		}
		inline void setRGB( const byte_t &r_, const byte_t &g_, const byte_t &b_ )
		{
			r = r_; 	g = g_;   b = b_;
		}

	// ============================ BASIC ARITHMETIC OPERATORS //                                            NOTE : these generally ignore alpha
		inline Colour operator+( const byte_t &val ) const { Colour x = Colour( *this ); x += val; return x; }
		inline Colour operator-( const byte_t &val ) const { Colour x = Colour( *this ); x -= val; return x; }
		inline Colour operator%( const byte_t &stp ) const { Colour x = Colour( *this ); x %= stp; return x; }
	//inline Colour operator*( const byte_t &val ) const { Colour x = Colour( *this ); x *= val; return x; }
	//inline Colour operator/( const byte_t &val ) const { Colour x = Colour( *this ); x /= val; return x; }

		inline Colour operator+=( const byte_t &val ) //   NOTE : raises the colour values ( aka makes them brighter )
		{
			int16_t r_ = int16_t( r ) + val;   if ( r_ > 255 ) r_ = 255;   r = byte_t( r_ );
			int16_t g_ = int16_t( g ) + val;   if ( g_ > 255 ) g_ = 255;   g = byte_t( g_ );
			int16_t b_ = int16_t( b ) + val;   if ( b_ > 255 ) b_ = 255;   b = byte_t( b_ );
		//int16_t a_ = int16_t( a ) + val;   if ( a_ > 255 ) a_ = 255;   a = byte_t( a_ );

			return *this;
		}

		inline Colour operator-=( const byte_t &val ) //   NOTE : lowers the colour values ( aka makes them darker )
		{
			int16_t r_ = int16_t( r ) - val;   if ( r_ < 0 ) r_ = 0;   r = byte_t( r_ );
			int16_t g_ = int16_t( g ) - val;   if ( g_ < 0 ) g_ = 0;   g = byte_t( g_ );
			int16_t b_ = int16_t( b ) - val;   if ( b_ < 0 ) b_ = 0;   b = byte_t( b_ );
		//int16_t a_ = int16_t( a ) - val;   if ( a_ < 0 ) a_ = 0;   a = byte_t( a_ );

			return *this;
		}

		inline Colour operator%=( const byte_t &stp ) //   NOTE : this posterizes the colour's values to the nearest step of stp size
		{
			if ( stp == 0 )
			{
				qlog( "Colour : Modulo by zero : voiding value", ERROR, 0 );
				r = g = b = a = 0;
				return *this;
			}

			// NOTE : avoids rounding down the max value, since we will otherwise almost never have it as a result
			if ( r != 255 && r != 0 ){ r -= ( r % stp ); }
			if ( g != 255 && g != 0 ){ g -= ( g % stp ); }
			if ( b != 255 && b != 0 ){ b -= ( b % stp ); }
		//if ( a != 255 && a != 0 ){ a -= ( a % stp ); }

			return *this;
		}
		/*
		inline Colour operator*=( const byte_t &val ) //   NOTE : multiplication and division should handle floating point values
		{
			int16_t r_ = int16_t( r ) * val;   if ( r_ > 255 ) r_ = 255;   r = byte_t( r_ );
			int16_t g_ = int16_t( g ) * val;   if ( g_ > 255 ) g_ = 255;   g = byte_t( g_ );
			int16_t b_ = int16_t( b ) * val;   if ( b_ > 255 ) b_ = 255;   b = byte_t( b_ );
		//int16_t a_ = int16_t( a ) * val;   if ( a_ > 255 ) a_ = 255;   a = byte_t( a_ );

			return *this;
		}

		inline Colour operator/=( const byte_t &val )
		{
			if ( val == 0 )
			{
				qlog( "Colour : Division by zero : voiding value", ERROR, 0 );   NOTE : multiplication and division should handle floating point values
				r = g = b = a = 0;
				return *this;
			}

			int16_t r_ = int16_t( r ) / val;   if ( r_ > 255 ) r_ = 255;   r = byte_t( r_ );
			int16_t g_ = int16_t( g ) / val;   if ( g_ > 255 ) g_ = 255;   g = byte_t( g_ );
			int16_t b_ = int16_t( b ) / val;   if ( b_ > 255 ) b_ = 255;   b = byte_t( b_ );
		//int16_t a_ = int16_t( a ) / val;   if ( a_ > 255 ) a_ = 255;   a = byte_t( a_ );

			return *this;
		}
	*/
	// ============================ BOOLEAN OPERATORS
		inline bool operator==( const Color  &c ) const { return ( r == c.r && g == c.g && b == c.b && a == c.a ); } // RAYLIB COLOR
		inline bool operator==( const Colour &c ) const { return ( r == c.r && g == c.g && b == c.b && a == c.a ); }

		inline bool operator!=( const Color  &c ) const { return ( r != c.r || g != c.g || b != c.b || a != c.a ); } // RAYLIB COLOR
		inline bool operator!=( const Colour &c ) const { return ( r != c.r || g != c.g || b != c.b || a != c.a ); }

		inline bool operator>=( const Color  &c ) const { return ( r >= c.r && g >= c.g && b >= c.b && a >= c.a ); } // RAYLIB COLOR
		inline bool operator>=( const Colour &c ) const { return ( r >= c.r && g >= c.g && b >= c.b && a >= c.a ); }

		inline bool operator<=( const Color  &c ) const { return ( r <= c.r && g <= c.g && b <= c.b && a <= c.a ); } // RAYLIB COLOR
		inline bool operator<=( const Colour &c ) const { return ( r <= c.r && g <= c.g && b <= c.b && a <= c.a ); }

		inline bool operator> ( const Color  &c ) const { return ( r >  c.r && g >  c.g && b >  c.b && a >  c.a ); } // RAYLIB COLOR
		inline bool operator> ( const Colour &c ) const { return ( r >  c.r && g >  c.g && b >  c.b && a >  c.a ); }

		inline bool operator< ( const Color  &c ) const { return ( r <  c.r && g <  c.g && b <  c.b && a <  c.a ); } // RAYLIB COLOR
		inline bool operator< ( const Colour &c ) const { return ( r <  c.r && g <  c.g && b <  c.b && a <  c.a ); }


	// ============================ COLOUR-TO_COLOUR OPERATORS //                                             TODO : make this behave like paint colour mixing

		// NOTE : plus operator will average two colours
		inline Colour operator+( const Colour &c ) const { Colour x = Colour( *this ); x += c;   return x; }
		inline Colour operator+( const Color  &c ) const { Colour x = Colour( *this ); x += c;   return x; } // RAYLIB COLOR

		inline Colour operator+=( const Color  &c ){ return *this += Colour( c ); } // RAYLIB COLOR
		inline Colour operator+=( const Colour &c )
		{
			r = byte_t( int16_t( r ) + c.r ) / 2;
			g = byte_t( int16_t( g ) + c.g ) / 2;
			b = byte_t( int16_t( b ) + c.b ) / 2;
			a = byte_t( int16_t( a ) + c.a ) / 2;

			return *this;
		}
};


// ============================ DEFAULT COLOUR TYPE ( only one possible for now )

typedef Colour col_t;

#endif // COLOUR_HPP