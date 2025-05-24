#include "../../../incs/core.hpp"

// ================================ ENTITY TRACKING METHODS

/*
bool ScreenMngr::trackEntity( Entity *Ntt, bool overrideTracking )
{
	flog( 0 );
	if( Ntt == nullptr )
	{
		qlog( "trackEntity : Cannot track a nullptr", INFO, 0 );
		qlog( "trackEntity : Use untrackEntity() to stop tracking", DEBUG, 0 );
		fend(); return false;
	}

	if( isTracking() )
	{
		if( !overrideTracking )
		{
			qlog( "trackEntity : Already tracking an object", WARN, 0 );
			qlog( "trackEntity : Use overrideTracking = true to override", INFO, 0 );
			fend(); return false;
		}
		else { qlog( "trackEntity : Overriding tracking", INFO, 0 ); }
	}

	_trackedEntity = Ntt;
	fend(); return true;
}

bool ScreenMngr::untrackEntity()
{
	flog( 0 );
	if( !isTracking() ){ fend(); return false; }

	_trackedEntity = nullptr;
	fend(); return true;
}
*/