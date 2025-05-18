#include "../../../incs/engine.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ GENERAL COMPONENT METHODS

bool Entity::isCompActive( comp_type_e compType ) const
{
	flog( _id );
	if( !IsValidComponent( _components[ compType ] )){ freturn false; }

	freturn _components[ compType ]->isActive();
}

bool Entity::isCompActive( comp_type_e compType, bool activate )
{
	flog( _id );
	if( !IsValidComponent( _components[ compType ] )){ freturn false; }

	_components[ compType ]->setActivity( activate );
	freturn _components[ compType ]->isActive();
}

bool Entity::hasComponent( comp_type_e compType ) const
{
	flog( _id );
	if( !IsValidCompType( compType )){        freturn false; }
	if( _components[ compType ] == nullptr ){ freturn false; }
	freturn true;
}

bool Entity::addComponent( comp_type_e compType )
{
	flog( _id );
	qlog( "addComponent : Trying to add component of type: " + std::to_string( compType ) + " to this entity", DEBUG, _id );

	if( !IsValidCompType( compType )){ freturn false; }
	if( _components[ compType ] != nullptr )
	{
		qlog( "Component of type: " + std::to_string( compType ) + " already exists for this entity", WARN, _id );
		freturn false;
	}

	qlog( "addComponent : Adding component of type: " + std::to_string( compType ) + " to this entity", INFO, _id );
	_components[ compType ] = CompFactory( compType, this ); // TODO : add the component type to the factory

	freturn true;
}

bool Entity::delComponent( comp_type_e compType, bool freeMem )
{
	flog( _id );
	if( !IsValidComponent( _components[ compType ] )){ freturn false; }

	qlog( "delComponent : Deleting component of type: " + std::to_string( compType ) + " from this entity", INFO, _id );
	if( freeMem ){ delete _components[ compType ]; }
	_components[ compType ] = nullptr;

	freturn true;
}

bool Entity::tickComponent( comp_type_e compType )
{
	flog( _id );
	if( !hasComponent( compType )){ freturn false; }
	freturn _components[ compType ]->onTick();
}

// ================ SPECIFIC COMPONENT METHODS

// ======== POSITION COMPONENT

vec2_t Entity::getPos() const
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ freturn NULL_POS; }
	freturn getComponent< CompPos >()->getPos();
}
bool Entity::setPos( vec2_t pos )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ freturn false; }
	freturn getComponent< CompPos >()->setPos( pos );
}
bool Entity::movePos( vec2_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ freturn false; }
	freturn getComponent< CompPos >()->movePos( delta );
}

angle_t Entity::getAngle() const
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ freturn 0; }
	freturn getComponent< CompPos >()->getAngle();
}
bool Entity::setAngle( angle_t angle )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ freturn false; }
	freturn getComponent< CompPos >()->setAngle( angle );
}
bool Entity::moveAngle( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_POSITION )){ freturn false; }
	freturn getComponent< CompPos >()->moveAngle( delta );
}

fixed_t Entity::getLineDistTo( id_t id ) const
{
	flog( _id );
	freturn getLineDistTo( GetNttM->getEntity( id ) );
}
fixed_t Entity::getLineDistTo( Entity *other ) const
{
	flog( _id );
	if( other == nullptr ){ freturn LONG_MAX; }
	freturn getLineDistTo( other->getComponent< CompPos >() );
}
fixed_t Entity::getLineDistTo( CompPos *other ) const
{
	flog( _id );
	if( other == nullptr ){ freturn LONG_MAX; }
	freturn getLineDistTo( other->getPos() );
}
fixed_t Entity::getLineDistTo( vec2_t other ) const
{
	flog( _id );
	freturn getLineDistTo( other.x, other.y );
}
fixed_t Entity::getLineDistTo( fixed_t x, fixed_t y ) const
{
	flog( _id ); // NOTE : transfers to component side methodes from here
	if( !hasComponent( COMP_POSITION )){ freturn LONG_MAX; }
	freturn getComponent< CompPos >()->getLineDistTo( x, y );
}

// ======== MOVEMENT COMPONENT

vec2_t Entity::getVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn vec2_t(); }
	freturn getComponent< CompMove >()->getVel();
}
fixed_t Entity::getLinearVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn 0; }
	freturn getComponent< CompMove >()->getLinearVel();
}
bool Entity::setVel( vec2_t vel )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->setVel( vel );
}
bool Entity::moveVel( vec2_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->moveVel( delta );
}

vec2_t Entity::getAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn vec2_t(); }
	freturn getComponent< CompMove >()->getAcc();
}
fixed_t Entity::getLinearAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn 0; }
	freturn getComponent< CompMove >()->getLinearAcc();
}
bool Entity::setAcc( vec2_t acc )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->setAcc( acc );
}
bool Entity::moveAcc( vec2_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->moveAcc( delta );
}

angle_t Entity::getRotVel() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn 0; }
	freturn getComponent< CompMove >()->getRotVel();
}
bool Entity::setRotVel( angle_t rotVel )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->setRotVel( rotVel );
}
bool Entity::moveRotVel( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->moveRotVel( delta );
}

angle_t Entity::getRotAcc() const
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn 0; }
	freturn getComponent< CompMove >()->getRotAcc();
}
bool Entity::setRotAcc( angle_t rotAcc )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->setRotAcc( rotAcc );
}
bool Entity::moveRotAcc( angle_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_MOVEMENT )){ freturn false; }
	freturn getComponent< CompMove >()->moveRotAcc( delta );
}

// ======== PHYSICS COMPONENT

bool Entity::isDynamic() const
{
	flog( _id );
	if( !hasComponent( COMP_PHYSIC )){ freturn false; }
	freturn getComponent< CompPhys >()->isDynamic();
}
bool Entity::setDynamic( bool isDynamic )
{
	flog( _id );
	if( !hasComponent( COMP_PHYSIC )){ freturn false; }
	freturn getComponent< CompPhys >()->setDynamic( isDynamic );
}

// ======== COLLISION COMPONENT

bool Entity::isCollidable() const
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ freturn false; }
	freturn getComponent< CompCollide >()->isCollidable();
}
bool Entity::setCollidable( bool isCollide )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ freturn false; }
	freturn getComponent< CompCollide >()->setCollidable( isCollide );
}

fixed_t Entity::getHitRad() const
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ freturn 0; }
	freturn getComponent< CompCollide >()->getHitRad();
}
bool Entity::setHitRad( fixed_t hitRad )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ freturn false; }
	freturn getComponent< CompCollide >()->setHitRad( hitRad );
}
bool Entity::moveHitRad( fixed_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_COLLIDE )){ freturn false; }
	freturn getComponent< CompCollide >()->moveHitRad( delta );
}

// ======== GRAPHIC COMPONENT

col_t Entity::getCol() const
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ freturn { 0, 0, 0, 0 }; }
	freturn getComponent< CompGraph >()->getCol();
}
bool Entity::setCol( col_t colour )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ freturn false; }
	freturn getComponent< CompGraph >()->setCol( colour );
}
bool Entity::moveCol( col_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ freturn false; }
	freturn getComponent< CompGraph >()->moveCol( delta );
}

fixed_t Entity::getCircleRadius() const
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ freturn 0; }
	freturn getComponent< CompGraph >()->getCircleRadius();
}
bool Entity::setCircleRadius( fixed_t radius )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ freturn false; }
	freturn getComponent< CompGraph >()->setCircleRadius( radius );
}
bool Entity::moveCircleRadius( fixed_t delta )
{
	flog( _id );
	if( !hasComponent( COMP_GRAPHIC )){ freturn false; }
	freturn getComponent< CompGraph >()->moveCircleRadius( delta );
}