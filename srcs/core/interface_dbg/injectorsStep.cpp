#include <raylib.h>
#include "../../../incs/game.hpp"

// ==================== ENGINE STEP INJECTION FUNCTIONS
// called when the engine calls the game step method - aka in the game loop of launchLoop()

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

void OnReadInputs( inputs_s &inp, inputs_s &prev )
{
	flog( 0 );

	if( inp.P && !prev.P )
	{
		qlog( "P pressed", INFO, 0 );
		GNG->togglePause();
	}

	if( inp.CLICK_LEFT && !prev.CLICK_LEFT )
	{
		qlog( "CLICK_LEFT pressed", INFO, 0 );

	}

}

void OnTickScripts()
{
	flog( 0 );
	// TODO : add game specific code here
}
void OnTickPhysics()
{
	flog( 0 );
	// TODO : add game specific code here
}
void OnTickCollides()
{
	flog( 0 );
	// TODO : add game specific code here
}
void OnTickMovements()
{
	flog( 0 );
	// TODO : add game specific code here
}
void OnTickVisuals()
{
	flog( 0 );
	// TODO : add game specific code here
}

void OnRenderBackground()
{
	flog( 0 );
	// TODO : add game specific code here
}
void OnRenderWorld()
{
	flog( 0 );
	// TODO : add game specific code here
}
void OnRenderUI()
{
	flog( 0 );
	int FontSizeUI = DEBUG_FONT_SIZE;

	// DEBUG : drawing to each corner of the screen for debug purposes
	DrawText( "TL", FontSizeUI,                               FontSizeUI,                               FontSizeUI, WHITE );
	DrawText( "TR", GetScreenWidth() - ( 2.5f * FontSizeUI ), FontSizeUI,                               FontSizeUI, WHITE );
	DrawText( "BL", FontSizeUI,                               GetScreenHeight() - ( 2.0 * FontSizeUI ), FontSizeUI, WHITE );
	DrawText( "BR", GetScreenWidth() - ( 2.5f * FontSizeUI ), GetScreenHeight() - ( 2.0 * FontSizeUI ), FontSizeUI, WHITE );

	string moInfo = "Mouse  : " + to_string( ( int )GVP->getMouseWorldPos().x ) + ":" + to_string( ( int )GVP->getMouseWorldPos().y ) + " | " + to_string( ( int )GVP->getMousePos().x ) + ":" + to_string( ( int )GVP->getMousePos().y );
	qlog( moInfo, INFO, 0 );
	DrawText( moInfo.c_str(), FontSizeUI, ( 2.5f * FontSizeUI ), FontSizeUI, WHITE );

	string caInfo = "Camera : " + to_string( GVP->getZoom() ) + " | " + to_string( ( int )GVP->getRotation() ) + " | " + to_string( ( int )GVP->getTarget().x ) + ":" + to_string( ( int )GVP->getTarget().y );
	qlog( caInfo, INFO, 0 );
	DrawText( caInfo.c_str(), FontSizeUI, ( 4.0f * FontSizeUI ), FontSizeUI, WHITE );

	if( G_PlayerNtt == nullptr )
	{
		qlog( "G_PlayerNtt is nullptr", ERROR, 0 );
		return;
	}

	CompPos *cmpPos = G_PlayerNtt->getComponent< CompPos >();
	if( cmpPos == nullptr )
	{
		qlog( "G_PlayerNtt has no position component", ERROR, 0 );
		return;
	}

	Vector2 playerWorldPos = G_PlayerNtt->getPos();
	Vector2 playerScreenPos = GetWorldToScreen2D( playerWorldPos, *GVP->getCamera() );

	string plInfo = "G_Player  : " + to_string( ( int )playerScreenPos.x ) + ":" + to_string( ( int )playerScreenPos.y ) + " | " + to_string( ( int )playerWorldPos.x ) + ":" + to_string( ( int )playerWorldPos.y );
	qlog( plInfo, INFO, 0 );
	DrawText( plInfo.c_str(), FontSizeUI, ( 5.5f * FontSizeUI ), FontSizeUI, WHITE );
}
