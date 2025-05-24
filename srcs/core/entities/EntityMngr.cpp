#include "../../../incs/core.hpp"

// ================================ CORE METHODS

void EntityMngr::onAdd()
{
	flog( 0 );

	_maxID = 0; // NOTE : set maxID to 0
	clearAllIDs(); // NOTE : clear all ID sets

	_CmpTbl.fill( nullptr ); // NOTE : fill the component table with nullptrs

	qlog( "onAdd : initialized EntityMngr", DEBUG, 0 );
	fend();
}
void EntityMngr::onDel()
{
	flog( 0 );

	clearAllComponents(); // NOTE : delete all components
	clearAllEntities(); // NOTE : delete all entities
	clearAllIDs(); // NOTE : clear all ID sets & reset maxID to 0

	qlog( "onDel : destroyed EntityMngr", DEBUG, 0 );
	fend();
}

void EntityMngr::updateMaxID()
{
	flog( 0 );

	if( _usedIDs.empty() )
	{
		qlog( "updateMaxID : no used IDs, setting maxID to 0", DEBUG, 0 );
		_freedIDs.clear(); // NOTE : clears the freed IDs, since there are no used IDs
		_maxID = 0;
	}
	else
	{
		_maxID = *std::max_element( _usedIDs.begin(), _usedIDs.end() ); // NOTE : finds new maxID based on the used IDs
		qlog( "updateMaxID : updated maxID to " + std::to_string( _maxID ), DEBUG, 0 );
	}

	auto it = _freedIDs.upper_bound( _maxID ); // NOTE : find the first element greater than _maxID
	if (it != _freedIDs.end())
	{
			_freedIDs.erase( it, _freedIDs.end() ); // NOTE : erase all elements from 'it' to the end
			qlog("updateMaxID : removed freed IDs greater than maxID", DEBUG, 0);
	}
	fend();
}
id_t EntityMngr::getNewID()
{
	flog( 0 );
	id_t newID = 0;

	if ( _freedIDs.empty() ) // NOTE : if there are no previously freed IDs, we need to get a brand a new one
	{
		qlog( "getNewID : no freed ID available, creating a new ID", DEBUG, 0 );
		newID = ++_maxID; // NOTE : preincrementation also prevents giving ID 0, since it is reserved for invalid entities
	}
	else // NOTE : if there are previously freed IDs, we can reuse one of them
	{
		auto it = _freedIDs.begin(); // NOTE : get the first freed ID

		qlog( "getNewID : reused previously freed ID " + std::to_string( newID ), DEBUG, 0 );
		newID = *it;
		_usedIDs.insert( *it );
		_freedIDs.erase(  it );
	}

	fend(); return newID;
}

void EntityMngr::clearAllIDs()
{
	flog( 0 );

	_usedIDs.clear();
//_activeIDs.clear();
//_toAddIDs.clear();
//_toDelIDs.clear();
	_freedIDs.clear();
	_maxID = 0;

	qlog( "clearAllIDs : cleared all ID sets & reset maxID", DEBUG, 0 );
	fend();
}
void EntityMngr::clearAllEntities()
{
	flog( 0 );

	for ( auto &pair : _NttMap ) // NOTE : iterate through the entity map
	{
		( void )pair;
		continue; // TODO : delete the entity
	}
	_NttMap.clear(); // NOTE : clear the entity map

	qlog( "clearAllEntities : cleared all entities", DEBUG, 0 );
	fend();
}
void EntityMngr::clearAllComponents()
{
	flog( 0 );

	for ( auto &comp : _CmpTbl ) // NOTE : iterate through the component table
	{
		if ( comp != nullptr ) // NOTE : if the component is not nullptr
		{
			continue; // TODO : delete the component
		}
	}
	qlog( "clearAllComponents : cleared all components", DEBUG, 0 );
	fend();
}