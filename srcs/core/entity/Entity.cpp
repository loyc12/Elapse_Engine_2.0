#include "../../../incs/engine.hpp"

// ================================ ASSOCIATED FUNCTIONS

bool IsValidEntity( Entity *Ntt )
{
	flog( 0 );
	if( Ntt == nullptr )
	{
		qlog( "IsValidEntity : Entity is nullptr", WARN, 0 );
		freturn false;
	}
	if( Ntt->getID() == 0 )
	{
		qlog( "IsValidEntity : Entity ID is 0", WARN, 0 );
		freturn false;
	}
	freturn true;
}
// ================================ CORE METHODS

bool Entity::onAdd()
{
	flog( 0 );
	qlog( "onAdd : Initializing a new entity", INFO, 0 );
	_active = true; // NOTE : set the active state to true
	_components.fill( nullptr ); // NOTE : set all components to nullptr
	freturn true;
}
bool Entity::onDel()
{
	flog( _id );

	if( GetScrnM != nullptr && GetScrnM->isTracking() && GetScrnM->getTrackedEntity() == this )
	{
		qlog( "delFromMngr : Untracking entity due to deletion", INFO, _id );
		GetScrnM->untrackEntity();
	}

	qlog( "onDel : Deleting this entity", INFO, _id );
for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( _components[ i ] != nullptr )
		{
			qlog( "onDel : Deleting component of type: " + std::to_string( i ), DEBUG, _id );
			delete _components[ i ];
		}
		else { qlog( "onDel : Component of type: " + std::to_string( i ) + " is already a nullptr", DEBUG, _id ); }
	}
	freturn delFromMngr();
}
bool Entity::onCpy( const Entity &rhs )
{
	flog( _id );
	if( this == &rhs ){ freturn false; } // NOTE : check if the object is the same

	qlog( "onCpy : Copying data from entity with ID: " + std::to_string( rhs._id ) + " to this entity", INFO, _id );

	_active = rhs._active; // NOTE : copy the active state
	for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		// NOTE : copies each component respective state, allocating or freeing memory as required
		_components[ i ] = CpyCompOver( _components[ i ], rhs._components[ i ] );
	}
	freturn true;
}

bool Entity::addToMngr()
{
	flog( _id );
	GetNttM->addThatEntity( this );
	freturn true;
}
bool Entity::delFromMngr()
{
	flog( _id );

	qlog( "delFromMngr : Deleting this entity", INFO, _id );
	if( _id != 0 )
	{
		if( GetNttM->hasThatEntity( this ))
		{
			qlog( "delFromMngr : removing entity from mngr", INFO, _id );
			GetNttM->delThatEntity( this, false );
		}
		else { qlog( "delFromMngr : Entity has id but is not in mngr", WARN, _id ); }

		_id = 0;
	}

	freturn true;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Entity::~Entity()
{
	flog( _id );
	onDel();
	qlog( "Entity : Entity deleted", INFO, 0 );
	fend();
}

Entity::Entity() : _id( 0 )
{
	flog( _id );
	onAdd();
	addToMngr();
	fend();
}
Entity::Entity( bool addEntityToMngr, id_t id ) : _id( id ) // NOTE : should only be called by EntityMngr
{
	flog( _id );
	onAdd();
	if( addEntityToMngr ){ addToMngr(); }
	fend();
}

Entity::Entity( const Entity &rhs ) : _id( 0 )
{
	flog( _id );
	onAdd();
	addToMngr();
	*this = rhs; // NOTE : calls the copy assignment operator
	fend();
}
Entity &Entity::operator=( const Entity &rhs )
{
	flog( _id );
	if( this == &rhs ){ freturn *this; } // NOTE : check if the object is the same
	onCpy( rhs );
	freturn *this;
}

// ================================ ACCESSORS / MUTATORS

comp_count_t Entity::getCompCount() const
{
	flog( _id );
	comp_count_t count = 0;
	for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i ){ if( _components[ i ] != nullptr ){ count++; }}
	freturn count;
}
comp_count_t Entity::getActCompCount() const
{
	flog( _id );
	comp_count_t count = 0;
	for ( comp_count_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( _components[ i ] != nullptr && _components[ i ]->isActive() ){ count++; }
	}
	freturn count;
}

//================================== OPERATORS

CompBase *Entity::operator[]( comp_type_e compType ) const
{
	flog( _id );
	if( compType >= COMP_TYPE_COUNT ){ freturn nullptr; }
	freturn _components[ compType ];
}
