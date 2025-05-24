#include "../incs/core.hpp"


void test()
{

}

void entry()
{
	GetNG->launchLoop();
}

int main()
{
	GetNG->switchState( ES_RUNNING );

	//test();
	entry();

	GetNG->switchState( ES_CLOSED );

	delete GetNG;   GetNG = nullptr;

	qlog( "Exiting main()", INFO, 0 );
}