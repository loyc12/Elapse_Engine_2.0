#include "../../../incs/engine.hpp"

id_t CompBase::getEntityID() const
{
	flog( 0 );
	if( _Ntt == nullptr )
	{
		qlog( "CompBase::getEntityID() : Entity is nullptr", WARN, 0 );
		return 0;
	}
	return _Ntt->getID();
}
bool CompBase::isEntityActive() const
{
	flog( 0 );
	if( _Ntt == nullptr )
	{
		qlog( "CompBase::isEntityActive() : Entity is nullptr", WARN, 0 );
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