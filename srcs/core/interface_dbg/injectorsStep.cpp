#include <raylib.h>
#include "../../../incs/game.hpp"

// ==================== ENGINE STEP INJECTION FUNCTIONS
// called when the engine calls a step method - aka in the game loop of launchLoop()

void OnStartLoop()
{
	flog( 0 );

	// TODO : add game specific code here
}
void OnEndLoop()
{
	flog( 0 );

	// TODO : add game specific code here
}

void OnStartStep()
{
	flog( 0 );

	// TODO : add game specific code here
}
void OnEndStep()
{
	flog( 0 );

	// TODO : add game specific code here
}

void OnReadInputs()
{
	flog( 0 );
	// NOTE : this is called before the tick methods, so you can use it to read inputs and set flags

	// TODO : add game specific code here
}

/*
void OnReadInputs( inputs_s &inp, inputs_s &prev )
{
	flog( 0 );

	if( inp.P && !prev.P )
	{
		GetNG->togglePause();
	}
	if( inp.X && !prev.X )
	{
		if( GetScrnM->isTracking() ){ GetScrnM->untrackEntity(); }
		else { GetScrnM->trackEntity( G_PlayerNtt ); }
	}

	if( inp.CLICK_LEFT )
	{
		if( G_PlayerNtt != nullptr )
		{
			CompPos *cmpPos = G_PlayerNtt->getComponent< CompPos >();
			if ( GetScrnM->getTrackedEntity() == G_PlayerNtt ){ GetScrnM->untrackEntity(); }
			if ( cmpPos != nullptr ){ cmpPos->setPos( GetScrnM->getMouseWorldPos()); }
		}
	}
	if( inp.CLICK_RIGHT )
	{
		if( G_EnemyNtt != nullptr )
		{
			CompPos *cmpPos = G_EnemyNtt->getComponent< CompPos >();
			if ( GetScrnM->getTrackedEntity() == G_EnemyNtt ){ GetScrnM->untrackEntity(); }
			if ( cmpPos != nullptr ){ cmpPos->setPos( GetScrnM->getMouseWorldPos()); }
		}
	}

	if ( inp.E ){ GetScrnM->moveRotation( 1.0f ); }
	if ( inp.Q ){ GetScrnM->moveRotation( -1.0f ); }

	if ( inp.SCROLL_UP   ){ GetScrnM->scaleZoom( 1.1f ); }
	if ( inp.SCROLL_DOWN ){ GetScrnM->scaleZoom( 0.9f ); }
}
*/