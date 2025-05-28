#include <raylib.h>
#include "../../../incs/game.hpp"

// ==================== RENDER INJECTION FUNCTIONS
// called when the engine calls a render method

void OnRenderStart()
{
	flog( 0 );

	// TODO : add game specific code here
}

void OnRenderWorld()
{
	flog( 0 );

	// TODO : add game specific code here
}

void OnRenderEnd()
{
	flog( 0 );
	int FontSizeUI = DEBUG_FONT_SIZE;

	// DEBUG : drawing to each corner of the screen for debug purposes
	DrawText( "TL", FontSizeUI,                               FontSizeUI,                               FontSizeUI, WHITE );
	DrawText( "TR", GetScreenWidth() - ( 2.5f * FontSizeUI ), FontSizeUI,                               FontSizeUI, WHITE );
	DrawText( "BL", FontSizeUI,                               GetScreenHeight() - ( 2.0 * FontSizeUI ), FontSizeUI, WHITE );
	DrawText( "BR", GetScreenWidth() - ( 2.5f * FontSizeUI ), GetScreenHeight() - ( 2.0 * FontSizeUI ), FontSizeUI, WHITE );

	string caInfo = "Camera : " + to_string( GetScrnM->getZoom() ) + " | " + to_string( ( int )GetScrnM->getRotation() ) + " | " + to_string( ( int )GetScrnM->getTarget().x ) + ":" + to_string( ( int )GetScrnM->getTarget().y );
	qlog( caInfo, INFO, 0 );
	DrawText( caInfo.c_str(), FontSizeUI, ( 2.5f * FontSizeUI ), FontSizeUI, WHITE );
/*
	string moInfo = "Mouse  : " + to_string( ( int )GetScrnM->getMouseWorldPos().x ) + ":" + to_string( ( int )GetScrnM->getMouseWorldPos().y ) + " | " + to_string( ( int )GetScrnM->getMouseScreenPos().x ) + ":" + to_string( ( int )GetScrnM->getMouseScreenPos().y );
	qlog( moInfo, INFO, 0 );
	DrawText( moInfo.c_str(), FontSizeUI, ( 4.0f * FontSizeUI ), FontSizeUI, WHITE );

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

	vec2_t playerWorldPos = G_PlayerNtt->getPos();
	vec2_t playerScreenPos = GetWorldToScreen2D( playerWorldPos, *GetScrnM->getCamera() );

	string plInfo = "G_Player  : " + to_string( ( int )playerScreenPos.x ) + ":" + to_string( ( int )playerScreenPos.y ) + " | " + to_string( ( int )playerWorldPos.x ) + ":" + to_string( ( int )playerWorldPos.y );
	qlog( plInfo, INFO, 0 );
	DrawText( plInfo.c_str(), FontSizeUI, ( 5.5f * FontSizeUI ), FontSizeUI, WHITE );
 */
}