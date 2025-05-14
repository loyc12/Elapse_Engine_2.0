#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ DRAWING METHODS

void ScreenManager::putPoin( vec2_t pos, Color colour )
{
	flog( 0 );
	if ( pos.x < 0 || pos.x > _windowSize.x || pos.y < 0 || pos.y > _windowSize.y )
	{
		qlog( "putPoin : point is out of bounds", WARN, 0 );
		return;
	}
	DrawPixel( pos.x, pos.y, colour );
}
void ScreenManager::putLine( vec2_t start, vec2_t end, Color colour, bool fill )
{
	flog( 0 );
	if ( start == end )
	{
		qlog( "putLine : start and end are the same : drawing a point instead", WARN, 0 );
		putPoin( start, colour );
		return;
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
}
void ScreenManager::putTria( vec2_t p1, vec2_t p2, vec2_t p3, Color colour, bool fill )
{
	flog( 0 );

	if ( p1 == p2 || p1 == p3 || p2 == p3 )
	{
		qlog( "putTria : two vertices are the same : drawing a line instead", WARN, 0 );
		putLine( p1, p2, colour );
		return;
	}

	if( fill ){ DrawTriangle( p1, p2, p3, colour ); }
	else { DrawTriangleLines( p1, p2, p3, colour ); }
}

void ScreenManager::putRectCorn( vec2_t p1, vec2_t p2, Color colour, bool fill )
{
	flog( 0 );
	if ( p1 == p2 )
	{
		qlog( "putRectCorn : two vertices are the same : drawing a point instead", WARN, 0 );
		putPoin( p1, colour );
		return;
	}
	putRect( { p1.x, p1.y }, { p2.x - p1.x, p2.y - p1.y }, colour, fill );
}
void ScreenManager::putRect( vec2_t pos, vec2_t sizes, Color colour, bool fill )
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
		return;
	}
	if( fill ){ DrawRectangle( pos.x, pos.y, sizes.x, sizes.y, colour ); }
	else { DrawRectangleLines( pos.x, pos.y, sizes.x, sizes.y, colour ); }
}
void ScreenManager::putCirc( vec2_t pos, fixed_t radius, Color colour, bool fill )
{
	flog( 0 );
	if( fill ){ DrawCircle( pos.x, pos.y, radius, colour ); }
	else { DrawCircleLines( pos.x, pos.y, radius, colour ); }
}
void ScreenManager::putCircSect( vec2_t pos, fixed_t radius, Angle start, Angle end, Color colour, bool fill )
{
	flog( 0 );

	if ( start == end )
	{
		qlog( "putCircSect : start and end are the same : drawing a circle instead", WARN, 0 );
		putCirc( pos, radius, colour, fill );
		return;
	}
	byte_t sideC = byte_t(( start.getDist( end ).getDeg() * 255 ) / 360.0f ); // TODO : test me
	if ( sideC != 255 ) sideC += 1; //  NOTE : rounds up to prevent zero-div

	if ( fill ){ DrawCircleSector( pos, radius, start.getDeg(), end.getDeg(), sideC, colour ); }
	else {  DrawCircleSectorLines( pos, radius, start.getDeg(), end.getDeg(), sideC, colour ); }
}

void ScreenManager::putOval( vec2_t pos, vec2_t sizes, Angle angle, Color colour, bool fill )
{
	flog( 0 );
	putPoly( pos, sizes, angle, 255, colour, fill ); // NOTE : pretends a 255-gon is a cricle
}
void ScreenManager::putRect( vec2_t pos, vec2_t sizes, Angle angle, Color colour, bool fill )
{
	flog( 0 );
	sizes.rotateBy( angle );
	putRect( pos, sizes, colour, fill ); // TODO : implement me
}
void ScreenManager::putPoly( vec2_t pos, vec2_t sizes, Angle angle, byte_t sideC, Color colour, bool fill )
{
	flog( 0 );
	(void)pos; (void)sizes; (void)angle; (void)sideC; (void)colour; (void)fill;
	// TODO : implement me
}

void ScreenManager::putForm( vec2_arr_t points, Color colour, bool fill )
{
	flog( 0 );
	(void)points; (void)colour; (void)fill;
	// TODO : implement me

}
