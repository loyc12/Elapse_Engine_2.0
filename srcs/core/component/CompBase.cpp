#include "../../../incs/engine.hpp"

id_t CompBase::getEntityID() const
{
	flog( 0 );
	if( _Ntt == nullptr )
	{
		qlog( "CompBase::getEntityID() : Entity is nullptr", DEBUG, 0 );
		return 0;
	}
	return _Ntt->getID();
}
bool CompBase::isEntityActive() const
{
	flog( 0 );
	if( _Ntt == nullptr )
	{
		qlog( "CompBase::isEntityActive() : Entity is nullptr", DEBUG, 0 );
		return false;
	}
	return _Ntt->isActive();
}
bool CompBase::setEntityActivity( bool activate )
{
	flog( 0 );
	if( _Ntt == nullptr )
	{
		qlog( "CompBase::setEntityActivity() : Entity is nullptr", WARN, 0 );
		return false;
	}
	return _Ntt->setActivity( activate );
}

// =============================== TICK METHODS

bool CompBase::canTick() const
{
	flog( 0 );
	if( !isActive() )
	{
		qlog( "CompPos::canTick() : component is not active", DEBUG, 0 );
		return false;
	}
	if( !hasEntity() )
	{
		qlog( "CompPos::canTick() : no entity found for component", WARN, 0 );
		return false;
	}
	if( !isEntityActive() )
	{
		qlog( "CompPos::canTick() : component's entity is not active", DEBUG, 0 );
		return false;
	}
	if( !hasSisterComps() )
	{
		qlog( "CompPos::canTick() : missing required sister components", INFO, 0 );
		return false;
	}
	if ( !GetNG->canEngineTick() )
	{
		qlog( "CompPos::canTick() : Engine is not in a tickable state", INFO, 0 );
		return false;
	}
	return true;
}

bool CompBase::onTick() // NOTE : override this in derived classes
{ //                       NOTE : onTick() should only be called by EntityMngr
	flog( 0 );
	if( !canTick() ){ return false; }
	// NOTE : CompBase does not do anything on tick
	return true;
}