#include "../../incs/base.hpp"

bool Shape::delVert( int16_t i )
{
	if ( i < 0 || i >= getVertC() )
	{
		qlog( "Shape::delVert : index out of bounds", WARN, 0 );
		return false;
	}
	_verts.erase( _verts.begin() + i );
	return true;
}

bool Shape::addVert( const vec2_t &v )
{
	if ( getVertC() >= MAX_VERT_COUNT )
	{
		qlog( "Shape::addVert : MAX_VERT_COUNT reached : cannot add any more", ERROR, 0 );
		return false;
	}
	_verts.push_back( v );
	sortVerts();
	return true;
}

bool Shape::copyVerts( const vec2_arr_t &verts )
{
	bool copiedAll = true;
	for ( int16_t i = 0; i < int16_t (verts.size() ); i++ )
	{
		if ( getVertC() >= MAX_VERT_COUNT )
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

bool Shape::sortVerts() // TODO : make sure this works
{
	if ( getVertC() == 0 ) { return false; }
	std::sort( _verts.begin(), _verts.end(), []( const vec2_t &a, const vec2_t &b ){ return Angle( a ) < Angle( b ); });
	return true;
}

bool Shape::scaleVerts( const fixed_t &scale )
{
	if ( getVertC() == 0 ) { return false; }
	for ( int16_t i = 0; i < getVertC(); i++ ){ _verts[ i ] *= scale; }
	return true;
}

// ============================ SHAPE METHODS

fixed_t Shape::getWidth() const
{
	if ( getVertC() == 0 ) { return 0; }

	fixed_t minX = _verts[ 0 ].x;
	fixed_t maxX = _verts[ 0 ].x;

	for ( int16_t i = 1; i < getVertC(); i++ )
	{
		if ( _verts[ i ].getX() < minX ) { minX = _verts[ i ].getX(); }
		if ( _verts[ i ].getX() > maxX ) { maxX = _verts[ i ].getX(); }
	}
	return maxX - minX;
}
fixed_t Shape::getHeight() const
{
	if ( getVertC() == 0 ) { return 0; }

	fixed_t minY = _verts[ 0 ].y;
	fixed_t maxY = _verts[ 0 ].y;

	for ( int16_t i = 1; i < getVertC(); i++ )
	{
		if ( _verts[ i ].getY() < minY ) { minY = _verts[ i ].getY(); }
		if ( _verts[ i ].getY() > maxY ) { maxY = _verts[ i ].getY(); }
	}
	return maxY - minY;
}

fixed_t Shape::getRotatedWidth() const
{
	if ( getVertC() == 0 ) { return 0; }

	vec2_t  vert = _verts[ 0 ].getRotatedCpy( _angle );
	fixed_t minX = vert.x;
	fixed_t maxX = vert.x;

	for ( int16_t i = 1; i < getVertC(); i++ )
	{
		vert = _verts[ i ].getRotatedCpy( _angle );
		if ( vert.getX() < minX ) { minX = vert.getX(); }
		if ( vert.getX() > maxX ) { maxX = vert.getX(); }
	}
	return maxX - minX;
}
fixed_t Shape::getRotatedHeight() const
{
	if ( getVertC() == 0 ) { return 0; }

	vec2_t  vert = _verts[ 0 ].getRotatedCpy( _angle );
	fixed_t minY = vert.y;
	fixed_t maxY = vert.y;

	for ( int16_t i = 1; i < getVertC(); i++ )
	{
		vert = _verts[ i ].getRotatedCpy( _angle );
		if ( vert.getY() < minY ) { minY = vert.getY(); }
		if ( vert.getY() > maxY ) { maxY = vert.getY(); }
	}
	return maxY - minY;
}

fixed_t Shape::getArea() const
{
	if ( getVertC() == 0 ) { return 0; }
	fixed_t area = 0;

	for ( int16_t i = 0; i < getVertC(); i++ )
	{
		int16_t j = ( i + 1 ) % getVertC();
		area += ( _verts[ i ].getX() * _verts[ j ].getY() ) - ( _verts[ j ].getX() * _verts[ i ].getY() );
	}
	return area / 2;
}
fixed_t Shape::getPerimeter() const
{
	if ( getVertC() == 0 ) { return 0; }
	fixed_t perimeter = 0;

	for ( int16_t i = 0; i < getVertC(); i++ )
	{
		int16_t j = ( i + 1 ) % getVertC();
		perimeter += _verts[ i ].getDist( _verts[ j ] );
	}
	return perimeter;
}

fixed_t Shape::getMinRadius() const
{
	if ( getVertC() == 0 ) { return 0; }
	fixed_t minRadius = _verts[ 0 ].getDist( _centre );

	for ( int16_t i = 1; i < getVertC(); i++ )
	{
		fixed_t radius = _verts[ i ].getDist( _centre );
		if ( radius < minRadius ) { minRadius = radius; }
	}
	return minRadius;
}
fixed_t Shape::getMaxRadius() const
{
	if ( getVertC() == 0 ) { return 0; }
	fixed_t maxRadius = _verts[ 0 ].getDist( _centre );

	for ( int16_t i = 1; i < getVertC(); i++ )
	{
		fixed_t radius = _verts[ i ].getDist( _centre );
		if ( radius > maxRadius ) { maxRadius = radius; }
	}
	return maxRadius;
}
fixed_t Shape::getAvgRadius() const
{
	if ( getVertC() == 0 ) { return 0; }
	fixed_t avgRadius = 0;

	for ( int16_t i = 0; i < getVertC(); i++ )
	{
		avgRadius += _verts[ i ].getDist( _centre );
	}
	return avgRadius / getVertC();
}