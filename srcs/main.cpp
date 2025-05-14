#include "../incs/engine.hpp"

int main()
{
	flog( 0 );

	GetNG->switchState( ES_RUNNING );

	GetNG->launchLoop();

	GetNG->switchState( ES_CLOSED );

	delete GetNG;   GetNG = nullptr;

	qlog( "Exiting main()", INFO, 0 );
}