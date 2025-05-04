#include "../../../incs/engine.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ GENERAL COMPONENT METHODS

bool Entity::isCompActive( comp_type_e compType ) const
{
	flog( _id );
	if( !IsValidComponent( _components[ compType ] )){ return false; }

	return _components[ compType ]->isActive();
}

bool Entity::isCompActive( comp_type_e compType, bool activate )
{
	flog( _id );
	if( !IsValidComponent( _components[ compType ] )){ return false; }

	_components[ compType ]->setActivity( activate );
	return _components[ compType ]->isActive();
}

bool Entity::hasComponent( comp_type_e compType ) const
{
	flog( _id );
	if( !IsValidCompType( compType )){        return false; }
	if( _components[ compType ] == nullptr ){ return false; }
	return true;
}

bool Entity::addComponent( comp_type_e compType )
{
	flog( _id );
	qlog( "addComponent : Trying to add component of type: " + std::to_string( compType ) + " to this entity", DEBUG, _id );

	if( !IsValidCompType( compType )){ return false; }
	if( _components[ compType ] != nullptr )
	{
		qlog( "Component of type: " + std::to_string( compType ) + " already exists for this entity", WARN, _id );
		return false;
	}

	qlog( "addComponent : Adding component of type: " + std::to_string( compType ) + " to this entity", INFO, _id );
	_components[ compType ] = CompFactory( compType, this ); // TODO : add the component type to the factory

	return true;
}

bool Entity::delComponent( comp_type_e compType, bool freeMem )
{
	flog( _id );
	if( !IsValidComponent( _components[ compType ] )){ return false; }

	qlog( "delComponent : Deleting component of type: " + std::to_string( compType ) + " from this entity", INFO, _id );
	if( freeMem ){ delete _components[ compType ]; }
	_components[ compType ] = nullptr;

	return true;
}

bool Entity::tickComponent( comp_type_e compType )
{
	flog( _id );
	if( _components[ compType ] == nullptr ){ return false; }

	qlog( "tickComponent : Ticking component of type: " + std::to_string( compType ) + " from this entity", INFO, _id );

	if( !IsValidComponent( _components[ compType ] )){ return false; }

	return _components[ compType ]->onTick();
}

// ================ SPECIFIC COMPONENT METHODS

Vector2 Entity::getPos() const
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return { 0, 0 }; }
	CompPos *cmp = getComponent< CompPos >();
	if( cmp == nullptr ){ return { 0, 0 }; }
	return cmp->getPos();
}
bool Entity::setPos( Vector2 pos )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	CompPos *cmp = getComponent< CompPos >();
	if( cmp == nullptr ){ return false; }
	return cmp->setPos( pos );
}
bool Entity::setPos( float x, float y )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	CompPos *cmp = getComponent< CompPos >();
	if( cmp == nullptr ){ return false; }
	return cmp->setPos( x, y );
}

Vector2 Entity::getVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return { 0, 0 }; }
	CompMove *cmp = getComponent< CompMove >();
	if( cmp == nullptr ){ return { 0, 0 }; }
	return cmp->getVel();
}
bool Entity::setVel( Vector2 vel )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	CompMove *cmp = getComponent< CompMove >();
	if( cmp == nullptr ){ return false; }
	return cmp->setVel( vel );
}
bool Entity::setVel( float x, float y )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	CompMove *cmp = getComponent< CompMove >();
	if( cmp == nullptr ){ return false; }
	return cmp->setVel( x, y );
}

Vector2 Entity::getAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return { 0, 0 }; }
	CompMove *cmp = getComponent< CompMove >();
	if( cmp == nullptr ){ return { 0, 0 }; }
	return cmp->getAcc();
}
bool Entity::setAcc( Vector2 acc )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	CompMove *cmp = getComponent< CompMove >();
	if( cmp == nullptr ){ return false; }
	return cmp->setAcc( acc );
}
bool Entity::setAcc( float x, float y )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	CompMove *cmp = getComponent< CompMove >();
	if( cmp == nullptr ){ return false; }
	return cmp->setAcc( x, y );
}

Color Entity::getCol() const
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return { 0, 0, 0, 0 }; }
	CompGraph *cmp = getComponent< CompGraph >();
	if( cmp == nullptr ){ return { 0, 0, 0, 0 }; }
	return cmp->getCol();
}
bool Entity::setCol( Color col )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	CompGraph *cmp = getComponent< CompGraph >();
	if( cmp == nullptr ){ return false; }
	return cmp->setCol( col );
}
bool Entity::setCol( byte_t r, byte_t g, byte_t b, byte_t a )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	CompGraph *cmp = getComponent< CompGraph >();
	if( cmp == nullptr ){ return false; }
	return cmp->setCol( r, g, b, a );
}

float Entity::getCircleRadius() const
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return 0; }
	CompGraph *cmp = getComponent< CompGraph >();
	if( cmp == nullptr ){ return 0; }
	return cmp->getCircleRadius();
}
bool Entity::setCircleRadius( float radius )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	CompGraph *cmp = getComponent< CompGraph >();
	if( cmp == nullptr ){ return false; }
	return cmp->setCircleRadius( radius );
}