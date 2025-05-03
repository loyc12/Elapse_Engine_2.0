#include "../../../incs/engine.hpp"
#include "../../../incs/engine/system/CompManager.hpp"

// ================================ CORE METHODS

bool Entity::addToManager()
{
	flog( _id );
	GCM->addThatEntity( this );
	return true;
}
bool Entity::delFromManager()
{
	flog( _id );
	if ( _id == 0 ){ return false; } // NOTE : if the ID is 0, the entity is not supposed to be in the map

	qlog( "delFromManager : Deleting entity with ID: " + std::to_string( _id ), INFO, 0 );

	GCM->delThatEntity( this, false );
	_id = 0;

	return true;
}
void Entity::onCpy( const Entity &rhs )
{
	flog( _id );
	if( this == &rhs ){ return; } // NOTE : check if the object is the same

	qlog( "Entity : Copying entity with ID: " + std::to_string( rhs._id ) + " to entity with ID: " + std::to_string( _id ), INFO, 0 );

	_active = rhs._active; // NOTE : copy the active state
	for ( CompC_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{ // NOTE : copies each component respective state, allocating or freeing memory as needed
		_components[ i ] = CpyCompOver( _components[ i ], rhs._components[ i ] );
	}
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Entity::~Entity()
{
	flog( _id );
	delFromManager();
}

Entity::Entity() : _id( 0 )
{
	flog( _id );
	addToManager();
}
Entity::Entity( bool addEntityToManager, id_t id ) : _id( id ) // NOTE : should only be called by CompManager
{
	flog( _id );
	if ( addEntityToManager ){ addToManager(); }
	qlog( "Entity : Created entity with ID: " + std::to_string( _id ), INFO, 0 );
}

Entity::Entity( const Entity &rhs ) : _id( 0 )
{
	flog( _id );
	addToManager();
	*this = rhs; // NOTE : calls the copy assignment operator
}
Entity &Entity::operator=( const Entity &rhs )
{
	flog( _id );
	if ( this == &rhs ){ return *this; } // NOTE : check if the object is the same
	onCpy( rhs );
	return *this;
}

// ================================ ACCESSORS / MUTATORS

CompC_t Entity::getCompCount() const
{
	flog( _id );
	CompC_t count = 0;
	for ( CompC_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if ( _components[ i ] != nullptr ){ count++; }
	}
	return count;
}

bool Entity::isCompActive( comp_e compType ) const
{
	flog( _id );
	if ( !IsValidCompType( compType )){ return false; }
	if ( !IsValidComponent( _components[ compType ] )){ return false; }

	return _components[ compType ]->isActive();
}
bool Entity::isCompActive( comp_e compType, bool activate )
{
	flog( _id );
	if ( !IsValidCompType( compType )){ return false; }
	if ( !IsValidComponent( _components[ compType ] )){ return false; }

	_components[ compType ]->isActive( activate );
	return _components[ compType ]->isActive();
}

bool Entity::hasComponent( comp_e compType ) const
{
	flog( _id );
	if ( !IsValidCompType( compType )){ return false; }
	return ( _components[ compType ] != nullptr );
}

bool Entity::addComponent( comp_e compType )
{
	flog( _id );
	if ( !IsValidCompType( compType )){ return false; }
	if ( _components[ compType ] != nullptr )
	{
		qlog( "Component already exists : aborting", INFO, 0 );
		return false;
	}

	qlog( "addComponent : Adding component with ID: " + std::to_string( _id ), INFO, 0 );
	_components[ compType ] = CompFactory( compType, _id ); // TODO : add the component type to the factory

	return true;
}

bool Entity::tickComponent( comp_e compType )
{
	flog( _id );
	if ( !IsValidCompType( compType )){ return false; }
	if ( !IsValidComponent( _components[ compType ] )){ return false; }

	return _components[ compType ]->onTick();
}

//================================== OPERATORS

BaseComp *Entity::operator[]( comp_e compType ) const
{
	flog( _id );
	if ( compType >= COMP_TYPE_COUNT ){ return nullptr; }
	return _components[ compType ];
}

// ================================ ASSOCIATED FUNCTIONS

bool IsValidEntity( Entity *ent )
{
	flog( 0 );
	if ( ent == nullptr )
	{
		qlog( "IsValidEntity : Entity is nullptr", WARN, 0 );
		return false;
	}
	if ( ent->getID() == 0 )
	{
		qlog( "IsValidEntity : Entity ID is 0", WARN, 0 );
		return false;
	}
	return true;
}