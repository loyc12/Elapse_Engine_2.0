#ifndef ENTITY_TPP
# define ENTITY_TPP

# pragma once
# include "./Entity.hpp"

TTC CompT *CpyCompOver( CompT *dst, CompT *src )
{
	flog( 0 );
	if ( src == nullptr )
	{
		qlog( "CpyCompOver : src is nullptr", INFO, 0 );
		if ( dst != nullptr )
		{
			qlog( "CpyCompOver : dst is not nullptr : deleting dst", INFO, 0 );
			delete dst;
			dst = nullptr;
		}
		else{ qlog( "CpyCompOver : dst is nullptr : nothing to do", INFO, 0 ); }
	}
	else
	{
		qlog( "CpyCompOver : src is not nullptr", INFO, 0 );
		if ( dst == nullptr )
		{
			qlog( "CpyCompOver : dst is nullptr : creating new dst", INFO, 0 );
			dst = new CompT( *src );
		}
		else
		{
			qlog( "CpyCompOver : dst is not nullptr : copying src to dst", INFO, 0 );
			*dst = *src;
		}
	}
	return dst;
}

// ================================ ACCESSORS / MUTATORS

/*
TTC CompT *Entity::getComponent( comp_e compType ) const
{
	flog( _id );
	if ( compType == COMP_BASE_TYPE )
	{
		qlog( "getComponent : Invalid component type", ERROR, 0 );
		return nullptr;
	}
	if ( compType >= COMP_TYPE_COUNT )
	{
		qlog( "getComponent : Component type is out of range", ERROR, 0 );
		return nullptr;
	}
	return _components[ compType ];
}
*/
TTC CompT *Entity::getComponent() const
{
	flog( _id );
	comp_e compType = CompT::getType();

	if ( compType == COMP_BASE_TYPE )
	{
		qlog( "getComponent : Invalid component type", ERROR, 0 );
		return nullptr;
	}
	if ( compType >= COMP_TYPE_COUNT )
	{
		qlog( "getComponent : Component type is out of range", ERROR, 0 );
		return nullptr;
	}
	// casting to CompT
	return static_cast< CompT* >( _components[ compType ] );
}

#endif // ENTITY_TPP

