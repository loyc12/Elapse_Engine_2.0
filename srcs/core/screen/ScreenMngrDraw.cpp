#include "../../../incs/core.hpp"

// ================================ DRAWING METHODS

void ScreenMngr::putPoin( vec2_t pos, col_t colour )
{
	flog( 0 );
	if ( pos.x < 0 || pos.x > _screenSize.x || pos.y < 0 || pos.y > _screenSize.y )
	{
		qlog( "putPoin : point is out of bounds", WARN, 0 );
		fend(); return;
	}
	DrawPixel( pos.x, pos.y, colour );

	fend();
}
void ScreenMngr::putLine( vec2_t start, vec2_t end, col_t colour, bool fill )
{
	flog( 0 );

	if ( start == end )
	{
		qlog( "putLine : start and end are the same : drawing a point instead", WARN, 0 );
		putPoin( start, colour );
		fend(); return;
	}

	if ( fill ) { DrawLine( start.x, start.y, end.x, end.y, colour ); }
	else
	{
		putPoin( start, colour );
		putPoin(( start + end ) / 4, colour );
		putPoin(( start + end ) / 2, colour );
		putPoin(( start + end ) * 3 / 4, colour );
		putPoin( end,   colour );
	}

	fend();
}
void ScreenMngr::putTria( vec2_t p1, vec2_t p2, vec2_t p3, col_t colour, bool fill, bool checkOrder )
{
	flog( 0 );

	if( p1 == p2 || p1 == p3 || p2 == p3 )
	{
		if( p1 == p2 && p2 == p3 )
		{
			qlog( "putTria : all points are the same : drawing a single point instead", WARN, 0 );
			putPoin( p1, colour );
		}
		elif( p1 == p2 )
		{
			qlog( "putTria : p1 and p2 are the same : drawing a line instead", WARN, 0 );
			putLine( p1, p3, colour );
		}
		elif( p1 == p3 )
		{
			qlog( "putTria : p1 and p3 are the same : drawing a line instead", WARN, 0 );
			putLine( p1, p2, colour );
		}
		elif( p2 == p3 )
		{
			qlog( "putTria : p2 and p3 are the same : drawing a line instead", WARN, 0 );
			putLine( p2, p1, colour );
		}
		fend(); return;
	}

	if( checkOrder )
	{
		fixed_t area = ( p1.x * ( p2.y - p3.y ) + p2.x * ( p3.y - p1.y ) + p3.x * ( p1.y - p2.y ));

		if( area == 0 )
		{
			qlog( "putTria : points are colinear : drawing a line instead", WARN, 0 );

			vec2_t min = vec2_t( Opfx::min( p1.x, p2.x, p3.x ), Opfx::min( p1.y, p2.y, p3.y ));
			vec2_t max = vec2_t( Opfx::max( p1.x, p2.x, p3.x ), Opfx::max( p1.y, p2.y, p3.y ));

			putLine( min, max, colour );
			fend(); return;
		}
		if( area < 0 ){ std::swap( p2, p3 ); } // NOTE : this is to make sure the triangle is drawn in a clockwise order
	}

	if( fill ){ DrawTriangle( p1, p2, p3, colour ); }
	else { DrawTriangleLines( p1, p2, p3, colour ); }

	fend();
}

void ScreenMngr::putRectCorn( vec2_t p1, vec2_t p2, col_t colour, bool fill )
{
	flog( 0 );
	if ( p1 == p2 )
	{
		qlog( "putRectCorn : two vertices are the same : drawing a point instead", WARN, 0 );
		putPoin( p1, colour );
		fend(); return;
	}
	putRect( { p1.x, p1.y }, { p2.x - p1.x, p2.y - p1.y }, colour, fill );

	fend();
}
void ScreenMngr::putRect( vec2_t pos, vec2_t sizes, col_t colour, bool fill )
{
	flog( 0 );

	if ( sizes.x <= 0 || sizes.y <= 0 )
	{
		if ( sizes.x > 0 )
		{
			qlog( "putRect : height is 0 : drawing a line instead", WARN, 0 );
			putLine( pos, { pos.x + sizes.x, pos.y }, colour );
		}
		else if ( sizes.y > 0 )
		{
			qlog( "putRect : width is 0 : drawing a line instead", WARN, 0 );
			putLine( pos, { pos.x, pos.y + sizes.y }, colour );
		}
		else
		{
			qlog( "putRect : width and height are 0 : drawing a point instead", WARN, 0 );
			putPoin( pos, colour );
		}
		fend(); return;
	}

	if( fill ){ DrawRectangle( pos.x, pos.y, sizes.x, sizes.y, colour ); }
	else { DrawRectangleLines( pos.x, pos.y, sizes.x, sizes.y, colour ); }

	fend();
}
void ScreenMngr::putCirc( vec2_t pos, fixed_t radius, col_t colour, bool fill )
{
	flog( 0 );

	if( fill ){ DrawCircle( pos.x, pos.y, radius, colour ); }
	else { DrawCircleLines( pos.x, pos.y, radius, colour ); }

	fend();
}
void ScreenMngr::putCircSect( vec2_t pos, fixed_t radius, Angle start, Angle end, col_t colour, bool fill )
{
	flog( 0 );

	if ( start == end )
	{
		qlog( "putCircSect : start and end are the same : drawing a circle instead", WARN, 0 );
		putCirc( pos, radius, colour, fill );
		fend(); return;
	}

	byte_t sideC = byte_t(( start.getDist( end ).getDeg() * 255 ) / 360.0f ); // TODO : test me
	if ( sideC != 255 ) sideC += 1; //  NOTE : rounds up to prevent zero-div

	if ( fill ){ DrawCircleSector( pos, radius, start.getDeg(), end.getDeg(), sideC, colour ); }
	else {  DrawCircleSectorLines( pos, radius, start.getDeg(), end.getDeg(), sideC, colour ); }

	fend();
}
