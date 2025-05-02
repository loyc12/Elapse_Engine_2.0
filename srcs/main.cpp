#include "../incs/engine.hpp"

int main()
{
	flog( 0 );

	GNG->switchState( ES_RUNNING );

	//GNG->launchLoop();

	GNG->switchState( ES_CLOSED );

	delete GNG;   GNG = nullptr;

	qlog( "Exiting main()", INFO, 0 );
}