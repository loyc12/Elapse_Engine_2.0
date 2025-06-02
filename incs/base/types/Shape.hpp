#ifndef SHAPE_HPP
# define SHAPE_HPP

# include "../defs.hpp"

# include "./Colour.hpp"
# include "./FixedPoint.hpp"
# include "./Angle.hpp"
# include "./Pos2.hpp"

# define MAX_VERT_COUNT 256 // maximum number of vertices in a shape

class Shape // TODO : move the large definitions to a .cpp file
{
	// ============================ ATTRIBUTES
	protected:
		inline static constexpr vec2_arr_t NULL_VECTS = vec2_arr_t(); // NOTE : used to avoid unnecessary allocations
		// returns the number of vertices in the shape, for comparisons with the index value
		uint16_t getVertC() const { return uint16_t( _verts.size()); }

	public:
		vec2_t     _centre; // position of the shape
		angle_t    _angle; //  angle of the
		col_t      _colour; // colour of the shape
		vec2_arr_t _verts; //  vertices of the shape

	// ============================ CONSTRUCTORS / DESTRUCTORS
		inline ~Shape(){};
		inline  Shape() : _centre( 0, 0 ), _angle( 0 ), _colour( DEF_COLOUR ), _verts( NULL_VECTS ){}
		inline  Shape( const vec2_t &center, const angle_t &angle = 0, const col_t &colour = DEF_COLOUR, const vec2_arr_t &verts = NULL_VECTS ):
			_centre( center ), _angle(  angle ), _colour( colour )
		{
			if( verts.size() == 0 || verts.size() > MAX_VERT_COUNT )
			{
				qlog( "Shape : invalid number of vertices", ERROR, 0 );
				_verts = NULL_VECTS; // NOTE : reset to empty vector
			}
			else { _verts = verts; }
		}

		inline Shape( const Shape &s ){ *this = s; }
		inline Shape operator=( const Shape &s ){ _centre = s._centre; _angle = s._angle; _colour = s._colour; _verts = s._verts; return *this; }

	// ============================ ACCESSORS / MUTATORS
		inline vec2_t     getCenter() const { return _centre; }
		inline angle_t    getAngle()  const { return _angle;  }
		inline col_t      getColour() const { return _colour; }
		inline vec2_arr_t getVerts()  const { return _verts;  }

		inline fixed_t getCenterX()  const { return _centre.getX(); }
		inline fixed_t getCenterY()  const { return _centre.getY(); }

		inline fixed_t getAngleRad() const { return _angle.getRad(); }
		inline fixed_t getAngleDeg() const { return _angle.getDeg(); }

		inline vec2_t getVert( uint16_t i ) const { return _verts[ i ]; }

		inline void setCenter( const vec2_t    &center ){ _centre = center; }
		inline void setAngle(  const angle_t    &angle ){ _angle  = angle;  }
		inline void setColour( const col_t     &colour ){ _colour = colour; }
		inline void setVerts(  const vec2_arr_t &verts ){ _verts  = verts;  }

		inline void setCenter( const fixed_t &x, const fixed_t &y ){ _centre.setPos( x, y ); }
		inline void setAngle(  const fixed_t &angle ){ _angle.setTo( angle ); }

		inline void move(   const vec2_t &offset ){ _centre += offset; }
		inline void rotate( const angle_t &angle ){ _angle  += angle;  }
		inline void scale(  const fixed_t &scale ){ scaleVerts( scale ); }

		inline void nullCenter(){ _centre.setPos( 0, 0 ); }
		inline void nullAngle(){  _angle = 0; }
		inline void nullColour(){ _colour = DEF_COLOUR; }
		inline void nullVerts(){  _verts.clear(); }

		inline void clearAll(){ nullCenter(); nullAngle(); nullColour(); nullVerts(); }

	// ============================ OPERATORS
		// NOTE : this avoids out of bound indexing and allow for wrapping
		inline vec2_t operator[]( uint16_t i ) const { i = Operate< uint16_t >::pmod( i, getVertC() ); return _verts[ i ]; }

	// ============================ VERTEX METHODS
		bool delVert( uint16_t i );
		bool addVert( const vec2_t &v );
		bool sortVerts();
		bool scaleVerts( const fixed_t &scale );

		vec2_arr_t getWorldVerts() const; // NOTE : returns the vertices in world coordinates, based on the current center and angle

	// ============================ SHAPE METHODS
		// NOTE : these obtain the true maximum distance between the most oposite verticies's position, assuming the shape is not rotated
		inline vec2_t getSize() const { return vec2_t( getWidth(), getHeight() );}
		fixed_t getWidth()      const;
		fixed_t getHeight()     const;

		// NOTE : these obtain the true maximum distance between the most oposite verticies's position, based on the current rotation
		inline vec2_t getRotatedSize() const { return vec2_t( getRotatedWidth(), getRotatedHeight() );}
		fixed_t getRotatedWidth()  const;
		fixed_t getRotatedHeight() const;

		fixed_t getArea()      const;
		fixed_t getPerimeter() const;

		fixed_t getMinRadius() const;
		fixed_t getMaxRadius() const;
		fixed_t getAvgRadius() const;

	// ============================ FACTORY METHODS
		static Shape GetRegPoly( const vec2_t &center, const angle_t &angle, const col_t &colour, uint16_t vertCount, fixed_t radius = 1 )
		{
			flog( 0 );
			vec2_arr_t verts;
			angle_t a;
			vec2_t  p;

			for ( uint16_t i = 0; i < vertCount; i++ )
			{
				a.setTo( fixed_t( i ) * PI * 2 / vertCount );
				p.x = center.getX() + ( radius * a.cos() );
				p.y = center.getY() + ( radius * a.sin() );
				verts.push_back( p );
			}
			return Shape( center, angle, colour, verts );
		}
		static Shape GetDefPoly( uint16_t vertCount = 3, fixed_t radius = 1 ){ return GetRegPoly( { 0, 0 }, 0, DEF_COLOUR, vertCount, radius ); }


	// ============================= FRIEND METHODS
	inline friend std::ostream &operator<<( std::ostream &os, const Shape &s )
	{
		os << "Shape : [center: " << s._centre << ", angle: " << s._angle << ", colour: " << s._colour.r << ":" << s._colour.g << ":" << s._colour.b << ":" << s._colour.a << ", verts: [";

		if ( s.getVertC() == 0 )
		{
			os << " EMPTY ";
			return os;
		}
		for ( uint16_t i = 0; i < s.getVertC(); i++ )
		{
			os << s._verts[ i ];
			if ( i != s.getVertC() - 1 ) { os << ", "; }
		}
		os << "]";
		return os;
	}
};

// ============================ DEFAULT SHAPE TYPE ( only one possible for now )
typedef Shape shape_t;

# define DEF_SHAPE shape_t({ 0, 0 }, 0, DEF_COLOUR, vec2_arr_t()) // NOTE : default shape with no vertices

#endif // SHAPE_HPP