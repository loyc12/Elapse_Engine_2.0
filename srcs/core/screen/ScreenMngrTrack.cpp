#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ ENTITY TRACKING METHODS

void ScreenMngr::setTarget( vec2_t target, bool overrideTracking )
{
	flog( 0 );
	if( _trackedEntity )
	{
		if( !overrideTracking )
		{
			qlog( "setTarget : Already tracking an object", INFO, 0 );
			qlog( "setTarget : Use overrideTracking = true to override", INFO, 0 );
			freturn;
		}
		else { qlog( "setTarget : Overriding tracking", INFO, 0 ); }
	}
	_camera.target = target;
}
void ScreenMngr::moveTarget( vec2_t offset )
{
	flog( 0 );
	_camera.target.x += float( offset.x );
	_camera.target.y += float( offset.y );
	fend();
}

bool ScreenMngr::trackEntity( Entity *Ntt, bool overrideTracking )
{
	flog( 0 );
	if( Ntt == nullptr )
	{
		qlog( "trackEntity : Cannot track a nullptr", INFO, 0 );
		qlog( "trackEntity : Use untrackEntity() to stop tracking", DEBUG, 0 );
		freturn false;
	}

	if( isTracking() )
	{
		if( !overrideTracking )
		{
			qlog( "trackEntity : Already tracking an object", WARN, 0 );
			qlog( "trackEntity : Use overrideTracking = true to override", INFO, 0 );
			freturn false;
		}
		else { qlog( "trackEntity : Overriding tracking", INFO, 0 ); }
	}

	_trackedEntity = Ntt;
	freturn true;
}

bool ScreenMngr::untrackEntity()
{
	flog( 0 );
	if( !isTracking() ){ freturn false; }

	_trackedEntity = nullptr;
	freturn true;
}

