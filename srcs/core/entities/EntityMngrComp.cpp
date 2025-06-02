#include "../../../incs/core.hpp"

// ================================ BASECOMP METHODS

bool CompBase::hasSisterComp( comp_type_e type ) const
{
	flog( _id );
	return GetNttM->hasComp( _id, type );
}

bool CompBase::canEntityTick() const
{
	flog( _id );
	return( GetNttM->canEntityTick( _id ));
}

// ================================ COMPONENT METHODS

bool EntityMngr::canEntityTick( id_t id ) const
{
	flog( 0 );

	if( !IsValid( id ))
	{
		qlog( "canTick : ID cannot be 0", WARN, id );
		return false;
	}
	if( !isUsed( id ))
	{
		qlog( "canTick : entity does not exist", ERROR, id );
		return false;
	}
	if( !isActive( id ))
	{
		qlog( "canTick : entity is not active", INFO, id );
		return false;
	}
	return true; // NOTE : if all checks passed, the entity can tick
}

bool EntityMngr::canTick( id_t id, comp_type_e type ) const
{
	flog( id );

	if( !GetNG->canEngineTick() )
	{
		qlog( "CompBase::canTick : Engine cannot tick", INFO, id );
		return false;
	}
	if( !canEntityTick( id ))
	{
		qlog( "CompBase::canTick : entity cannot tick", DEBUG, id );
		return false;
	}
	if( !_CmpTbl[ type ][ id ].isInit() )
	{
		qlog( "CompBase::canTick : component is not initialized", DEBUG, id );
		return false;
	}
	return true; // NOTE : if all checks passed, the component can tick
}

bool EntityMngr::hasComp( id_t id, comp_type_e type ) const
{
	flog( 0 );

	if( !IsValid( id, type )){  return false; }
	bool exists = _CmpTbl[ type ][ id ].isInit();

	qlog( "hasComp : component of type " + to_string( type ) + ( exists ? " exists for entity with ID " + std::to_string( id ) : " does not exist for entity with ID " + std::to_string( id )), DEBUG, 0 );
	return exists;
}

bool EntityMngr::initComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( id, type )){  return false; }
	if( _CmpTbl[ type ][ id ].isInit())
	{
		qlog( "addComp : component of type " + to_string( type ) + " already exists for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return false;
	}

	_CmpTbl[ type ][ id ].init( id );
	return true;
}

bool EntityMngr::deinitComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( id, type )){  return false; }
	if( !_CmpTbl[ type ][ id ].isInit())
	{
		qlog( "delComp : component of type " + to_string( type ) + " does not exist for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return false;
	}

	_CmpTbl[ type ][ id ].deinit();
	return true;
}

CompBase *EntityMngr::getComp( id_t id, comp_type_e type )
{
	flog( 0 );

	if( !IsValid( id, type )){  return nullptr; }
	if( !_CmpTbl[ type ][ id ].isInit())
	{
		qlog( "getComp : component of type " + to_string( type ) + " does not exist for entity with ID " + std::to_string( id ), DEBUG, 0 );
		return nullptr;
	}

	return &( _CmpTbl[ type ][ id ]);
}