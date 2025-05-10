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

vec2_t Entity::getPos() const
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return NULL_POS; }
	return getComponent< CompPos >()->getPos();
}
bool Entity::setPos( vec2_t pos )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	return getComponent< CompPos >()->setPos( pos );
}
bool Entity::movePos( vec2_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	return getComponent< CompPos >()->movePos( delta );
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
bool Entity::moveAngle( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ return false; }
	return getComponent< CompPos >()->moveAngle( delta );
}

fixed_t Entity::getLineDistTo( id_t id ) const
{
	flog( _id );
	return getLineDistTo( GCM->getEntity( id ) );
}
fixed_t Entity::getLineDistTo( Entity *other ) const
{
	flog( _id );
	if( other == nullptr ){ return INFINITY; }
	return getLineDistTo( other->getComponent< CompPos >() );
}
fixed_t Entity::getLineDistTo( CompPos *other ) const
{
	flog( _id );
	if( other == nullptr ){ return INFINITY; }
	return getLineDistTo( other->getPos() );
}
fixed_t Entity::getLineDistTo( vec2_t other ) const
{
	flog( _id );
	return getLineDistTo( other.x, other.y );
}
fixed_t Entity::getLineDistTo( fixed_t x, fixed_t y ) const
{
	flog( _id ); // NOTE : transfers to component side methodes from here
	if( !hasComponent( COMP_POSITION )){ return INFINITY; }
	return getComponent< CompPos >()->getLineDistTo( x, y );
}

// ======== MOVEMENT COMPONENT

vec2_t Entity::getVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return { 0, 0 }; }
	return getComponent< CompMove >()->getVel();
}
fixed_t Entity::getLinearVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return 0; }
	return getComponent< CompMove >()->getLinearVel();
}
bool Entity::setVel( vec2_t vel )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->setVel( vel );
}
bool Entity::moveVel( vec2_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->moveVel( delta );
}

vec2_t Entity::getAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return { 0, 0 }; }
	return getComponent< CompMove >()->getAcc();
}
fixed_t Entity::getLinearAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return 0; }
	return getComponent< CompMove >()->getLinearAcc();
}
bool Entity::setAcc( vec2_t acc )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->setAcc( acc );
}
bool Entity::moveAcc( vec2_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->moveAcc( delta );
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
bool Entity::moveRotVel( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->moveRotVel( delta );
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
bool Entity::moveRotAcc( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ return false; }
	return getComponent< CompMove >()->moveRotAcc( delta );
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

fixed_t Entity::getHitRad() const
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return 0; }
	return getComponent< CompCollide >()->getHitRad();
}
bool Entity::setHitRad( fixed_t hitRad )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return false; }
	return getComponent< CompCollide >()->setHitRad( hitRad );
}
bool Entity::moveHitRad( fixed_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ return false; }
	return getComponent< CompCollide >()->moveHitRad( delta );
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
bool Entity::moveCol( Color delta )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	return getComponent< CompGraph >()->moveCol( delta );
}

fixed_t Entity::getCircleRadius() const
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return 0; }
	return getComponent< CompGraph >()->getCircleRadius();
}
bool Entity::setCircleRadius( fixed_t radius )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	return getComponent< CompGraph >()->setCircleRadius( radius );
}
bool Entity::moveCircleRadius( fixed_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ return false; }
	return getComponent< CompGraph >()->moveCircleRadius( delta );
}