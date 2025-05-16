#ifndef SHAPE_HPP
# define SHAPE_HPP

# include <raylib.h>
# include "../core.hpp"

# include "./FixedPoint.hpp"
# include "./Angle.hpp"
# include "./Pos2.hpp"

# define MAX_VERT_COUNT 256 // maximum number of vertices in a shape

class Shape
{
	// ============================ ATTRIBUTES
	public:
		vec2_t     _centre; // position of the shape
		Angle      _angle; //  angle of the
		Color      _colour; // colour of the shape
		vec2_arr_t _verts; //  vertices of the shape

	// ============================ CONSTRUCTORS / DESTRUCTORS
	public:
		inline ~Shape(){};
		inline  Shape() : _centre( 0, 0 ), _angle( 0 ), _colour( WHITE ), _verts(){}
		inline  Shape( const vec2_t &center, const Angle &angle = 0, const Color &colour = WHITE, const vec2_arr_t &verts = vec2_arr_t() ):
			_centre( center ),
			_angle(  angle ),
			_colour( colour )
		{
			copyVerts( verts );
		}

		inline  Shape( const Shape &s ){ *this = s; }
		inline  Shape operator=( const Shape &s ){ _centre = s._centre; _angle = s._angle; _colour = s._colour; copyVerts( s._verts ); return *this; }

	// ============================ ACCESSORS / MUTATORS

		inline vec2_t     getCenter() const { return _centre; }
		inline Angle      getAngle()  const { return _angle; }
		inline Color      getColour() const { return _colour; }
		inline vec2_arr_t getVerts()  const { return _verts; }

		inline fixed_t getCenterX()  const { return _centre.getX(); }
		inline fixed_t getCenterY()  const { return _centre.getY(); }

		inline fixed_t getAngleRad() const { return _angle.getRad(); }
		inline fixed_t getAngleDeg() const { return _angle.getDeg(); }

		inline vec2_t getVert( int16_t i ) const { return _verts[ i ]; }

		inline void setCenter( const vec2_t    &center ){ _centre = center; }
		inline void setAngle(  const Angle      &angle ){ _angle  = angle; }
		inline void setColour( const Color     &colour ){ _colour = colour; }
		inline void setVerts(  const vec2_arr_t &verts ){ _verts  = verts; }

		inline void setCenter( const fixed_t &x, const fixed_t &y ){ _centre.setPos( x, y ); }
		inline void setAngle(  const fixed_t &angle ){ _angle.setTo( angle ); }

		inline void move(   const vec2_t &offset ){ _centre += offset; }
		inline void rotate( const Angle   &angle ){ _angle  += angle; }
		inline void scale(  const fixed_t &scale ){ scaleVerts( scale ); }

		inline void nullCenter(){ _centre.setPos( 0, 0 ); }
		inline void nullAngle(){  _angle = 0; }
		inline void nullColour(){ _colour = WHITE; }
		inline void nullVerts(){  _verts.clear(); }

		inline void clearAll(){ nullCenter(); nullAngle(); nullColour(); nullVerts(); }

	// ============================ OPERATORS

		inline vec2_t operator[]( int16_t i ) const
		{
			i = Operate< int16_t >::pmod( i, _verts.size() ); // NOTE : this is to avoid out of bound indexing and allow for wrapping
			return _verts[ i ];
		}

	// ============================ VERTEX METHODS

		inline bool delVert( int16_t i )
		{
			if ( i < 0 || i >= _verts.size() )
			{
				qlog( "Shape::delVert : index out of bounds", WARN, 0 );
				return false;
			}
			_verts.erase( _verts.begin() + i );
			return true;
		}

		inline bool addVert( const vec2_t &v )
		{
			if ( _verts.size() >= MAX_VERT_COUNT )
			{
				qlog( "Shape::addVert : MAX_VERT_COUNT reached : cannot add any more", ERROR, 0 );
				return false;
			}
			_verts.push_back( v );
			sortVerts();
			return true;
		}

		inline bool copyVerts( const vec2_arr_t &verts )
		{
			bool copiedAll = true;
			for ( int16_t i = 0; i < verts.size(); i++ )
			{
				if ( _verts.size() >= MAX_VERT_COUNT )
				{
					qlog( "Shape::copyVerts : MAX_VERT_COUNT reached : cannot add any more", ERROR, 0 );
					copiedAll = false;
					break;
				}
				_verts.push_back( verts[ i ]);
			}
			sortVerts();
			return copiedAll;
		}

		inline bool sortVerts() // TODO : make sure this works
		{
			if ( _verts.size() == 0 ) { return false; }
			std::sort( _verts.begin(), _verts.end(), []( const vec2_t &a, const vec2_t &b ){ return Angle( a ) < Angle( b ); });
			return true;
		}

		inline bool scaleVerts( const fixed_t &scale )
		{
			if ( _verts.size() == 0 ) { return false; }
			for ( int16_t i = 0; i < _verts.size(); i++ ){ _verts[ i ] *= scale; }
			return true;
		}

		// ============================ SHAPE METHODS

		inline vec2_t  getSize()  const { return vec2_t( getWidth(), getHeight() );}
		inline fixed_t getWidth() const
		{
			if ( _verts.size() == 0 ) { return 0; }
			fixed_t minX = _verts[ 0 ].getX();
			fixed_t maxX = _verts[ 0 ].getX();
			for ( int16_t i = 1; i < _verts.size(); i++ )
			{
				if ( _verts[ i ].getX() < minX ) { minX = _verts[ i ].getX(); }
				if ( _verts[ i ].getX() > maxX ) { maxX = _verts[ i ].getX(); }
			}
			return maxX - minX;
		}
		inline fixed_t getHeight() const
		{
			if ( _verts.size() == 0 ) { return 0; }
			fixed_t minY = _verts[ 0 ].getY();
			fixed_t maxY = _verts[ 0 ].getY();
			for ( int16_t i = 1; i < _verts.size(); i++ )
			{
				if ( _verts[ i ].getY() < minY ) { minY = _verts[ i ].getY(); }
				if ( _verts[ i ].getY() > maxY ) { maxY = _verts[ i ].getY(); }
			}
			return maxY - minY;
		}

		inline fixed_t getArea() const
		{
			if ( _verts.size() == 0 ) { return 0; }
			fixed_t area = 0;

			for ( int16_t i = 0; i < _verts.size(); i++ )
			{
				int16_t j = ( i + 1 ) % _verts.size();
				area += ( _verts[ i ].getX() * _verts[ j ].getY() ) - ( _verts[ j ].getX() * _verts[ i ].getY() );
			}
			return area / 2;
		}
		inline fixed_t getPerimeter() const
		{
			if ( _verts.size() == 0 ) { return 0; }
			fixed_t perimeter = 0;

			for ( int16_t i = 0; i < _verts.size(); i++ )
			{
				int16_t j = ( i + 1 ) % _verts.size();
				perimeter += _verts[ i ].getDist( _verts[ j ] );
			}
			return perimeter;
		}

		inline fixed_t getMinRadius() const
		{
			if ( _verts.size() == 0 ) { return 0; }
			fixed_t minRadius = _verts[ 0 ].getDist( _centre );

			for ( int16_t i = 1; i < _verts.size(); i++ )
			{
				fixed_t radius = _verts[ i ].getDist( _centre );
				if ( radius < minRadius ) { minRadius = radius; }
			}
			return minRadius;
		}
		inline fixed_t getMaxRadius() const
		{
			if ( _verts.size() == 0 ) { return 0; }
			fixed_t maxRadius = _verts[ 0 ].getDist( _centre );

			for ( int16_t i = 1; i < _verts.size(); i++ )
			{
				fixed_t radius = _verts[ i ].getDist( _centre );
				if ( radius > maxRadius ) { maxRadius = radius; }
			}
			return maxRadius;
		}
		inline fixed_t getAvgRadius() const
		{
			if ( _verts.size() == 0 ) { return 0; }
			fixed_t avgRadius = 0;

			for ( int16_t i = 0; i < _verts.size(); i++ )
			{
				avgRadius += _verts[ i ].getDist( _centre );
			}
			return avgRadius / _verts.size();
		}

		// ============================= FRIEND METHODS

		inline friend std::ostream &operator<<( std::ostream &os, const Shape &s )
		{
			os << "Shape : [center: " << s._centre << ", angle: " << s._angle << ", colour: " << s._colour.r << ":" << s._colour.g << ":" << s._colour.b << ":" << s._colour.a << ", verts: [";
			for ( int16_t i = 0; i < s._verts.size(); i++ )
			{
				os << s._verts[ i ];
				if ( i != s._verts.size() - 1 ) { os << ", "; }
			}
			os << "]";
			return os;
		}
};




// ============================ DEFAULT FSHAPE TYPE ( only one possible for now )

typedef Shape Shape_t;

#endif // SHAPE_HPP