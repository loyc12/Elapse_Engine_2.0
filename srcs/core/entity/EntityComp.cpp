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
	if( !IsValidCompType( compType )){ return false; }
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
	if( !hasComponent( compType )){ return false; }
	return _components[ compType ]->onTick();
}

// ================ SPECIFIC COMPONENT METHODS

// ======== POSITION COMPONENT

Vector2 Entity::getPos() const
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return NULL_POS; }
	return getComponent< CompPos >()->getPos();
}
bool Entity::setPos( Vector2 pos )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	return getComponent< CompPos >()->setPos( pos );
}
bool Entity::changePos( Vector2 delta )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	return getComponent< CompPos >()->changePos( delta );
}

angle_t Entity::getAngle() const
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return 0; }
	return getComponent< CompPos >()->getAngle();
}
bool Entity::setAngle( angle_t angle )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	return getComponent< CompPos >()->setAngle( angle );
}
bool Entity::changeAngle( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	return getComponent< CompPos >()->changeAngle( delta );
}

float Entity::getLineDistTo( id_t id ) const
{
	flog( _id );
	return getLineDistTo( GCM->getEntity( id ) );
}
float Entity::getLineDistTo( Entity *other ) const
{
	flog( _id );
	if( other == nullptr ){ return INFINITY; }
	return getLineDistTo( other->getComponent< CompPos >() );
}
float Entity::getLineDistTo( CompPos *other ) const
{
	flog( _id );
	if( other == nullptr ){ return INFINITY; }
	return getLineDistTo( other->getPos() );
}
float Entity::getLineDistTo( Vector2 other ) const
{
	flog( _id );
	return getLineDistTo( other.x, other.y );
}
float Entity::getLineDistTo( float x, float y ) const
{
	flog( _id ); // NOTE : transfers to component side methodes from here
	if( !hasComponent( COMP_POSITION )){ return INFINITY; }
	return getComponent< CompPos >()->getLineDistTo( x, y );
}

// ======== MOVEMENT COMPONENT

Vector2 Entity::getVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return { 0, 0 }; }
	return getComponent< CompMove >()->getVel();
}
float Entity::getLinearVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return 0; }
	return getComponent< CompMove >()->getLinearVel();
}
bool Entity::setVel( Vector2 vel )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->setVel( vel );
}
bool Entity::changeVel( Vector2 delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->changeVel( delta );
}

Vector2 Entity::getAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return { 0, 0 }; }
	return getComponent< CompMove >()->getAcc();
}
float Entity::getLinearAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return 0; }
	return getComponent< CompMove >()->getLinearAcc();
}
bool Entity::setAcc( Vector2 acc )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->setAcc( acc );
}
bool Entity::changeAcc( Vector2 delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->changeAcc( delta );
}

angle_t Entity::getRotVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return 0; }
	return getComponent< CompMove >()->getRotVel();
}
bool Entity::setRotVel( angle_t rotVel )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->setRotVel( rotVel );
}
bool Entity::changeRotVel( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->changeRotVel( delta );
}

angle_t Entity::getRotAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return 0; }
	return getComponent< CompMove >()->getRotAcc();
}
bool Entity::setRotAcc( angle_t rotAcc )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->setRotAcc( rotAcc );
}
bool Entity::changeRotAcc( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->changeRotAcc( delta );
}

// ======== PHYSICS COMPONENT

bool Entity::isDynamic() const
{
	flog( _id );
	if( !hasComponent( COMP_PHYSIC )){ return false; }
	return getComponent< CompPhys >()->isDynamic();
}
bool Entity::setDynamic( bool isDynamic )
{
	flog( _id );
	if( !hasComponent( COMP_PHYSIC )){ return false; }
	return getComponent< CompPhys >()->setDynamic( isDynamic );
}

// ======== COLLISION COMPONENT

bool Entity::isCollidable() const
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return false; }
	return getComponent< CompCollide >()->isCollidable();
}
bool Entity::setCollidable( bool isCollide )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return false; }
	return getComponent< CompCollide >()->setCollidable( isCollide );
}

float Entity::getHitRad() const
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return 0; }
	return getComponent< CompCollide >()->getHitRad();
}
bool Entity::setHitRad( float hitRad )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return false; }
	return getComponent< CompCollide >()->setHitRad( hitRad );
}
bool Entity::changeHitRad( float delta )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return false; }
	return getComponent< CompCollide >()->changeHitRad( delta );
}

// ======== GRAPHIC COMPONENT

Color Entity::getCol() const
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return { 0, 0, 0, 0 }; }
	return getComponent< CompGraph >()->getCol();
}
bool Entity::setCol( Color col )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	return getComponent< CompGraph >()->setCol( col );
}
bool Entity::changeCol( Color delta )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	return getComponent< CompGraph >()->changeCol( delta );
}

float Entity::getCircleRadius() const
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return 0; }
	return getComponent< CompGraph >()->getCircleRadius();
}
bool Entity::setCircleRadius( float radius )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	return getComponent< CompGraph >()->setCircleRadius( radius );
}
bool Entity::changeCircleRadius( float delta )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	return getComponent< CompGraph >()->changeCircleRadius( delta );
}