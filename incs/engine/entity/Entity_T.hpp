#ifndef ENTITY_TPP
# define ENTITY_TPP

# pragma once
# include "./Entity.hpp"

TTC CompT *CpyCompOver( CompT *dst, CompT *src )
{
	flog( 0 );
	if( src == nullptr )
	{
		qlog( "CpyCompOver : src is nullptr", INFO, 0 );
		if( dst != nullptr )
		{
			qlog( "CpyCompOver : dst is not nullptr : deleting dst", INFO, 0 );
			delete dst;
			dst = nullptr;
		}
		else { qlog( "CpyCompOver : dst is nullptr : nothing to do", INFO, 0 ); }
	}
	else
	{
		qlog( "CpyCompOver : src is not nullptr", INFO, 0 );
		if( dst == nullptr )
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
	freturn dst;
}

// ================================ ACCESSORS / MUTATORS

/*
TTC CompT *Entity::getComponent( comp_type_e compType ) const
{
	flog( _id );
	if( compType == COMP_TYPE_BASE )
	{
		qlog( "getComponent : Invalid component type", ERROR, 0 );
		freturn nullptr;
	}
	if( compType >= COMP_TYPE_COUNT )
	{
		qlog( "getComponent : Component type is out of range", ERROR, 0 );
		freturn nullptr;
	}
	freturn _components[ compType ];
}
*/
TTC CompT *Entity::getComponent() const
{
	flog( _id );
	comp_type_e compType = CompT::getStaticType();

	if( compType == COMP_TYPE_BASE )
	{
		qlog( "getComponent : Invalid component type", ERROR, 0 );
		freturn nullptr;
	}
	if( compType >= COMP_TYPE_COUNT )
	{
		qlog( "getComponent : Component type is out of range", ERROR, 0 );
		freturn nullptr;
	}
	// casting to CompT
	freturn static_cast< CompT* >( _components[ compType ] );
}

#endif // ENTITY_TPP

