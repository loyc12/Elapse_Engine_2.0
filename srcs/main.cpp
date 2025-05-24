#include "../incs/core.hpp"


void tester()
{

}

void entrypoint()
{
	GetNG->launchLoop();
}

int main()
{
	GetNG->switchState( ES_RUNNING );

	//tester();
	entrypoint();

	GetNG->switchState( ES_CLOSED );

	delete GetNG;   GetNG = nullptr;

	qlog( "Exiting main()", INFO, 0 );
}