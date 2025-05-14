#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <raylib.h>
# include "../../base.hpp"

# include "../component/CompBase.hpp"

# include "../component/CompPos.hpp"
# include "../component/CompMove.hpp"
# include "../component/CompCollide.hpp"
# include "../component/CompPhys.hpp"

# include "../component/CompText.hpp"
# include "../component/CompSound.hpp"
# include "../component/CompShape.hpp"
# include "../component/CompGraph.hpp"

# include "../component/CompScript.hpp"

TTC CompT *CpyCompOver( CompT *dst, CompT *src );

typedef array< CompBase*, COMP_TYPE_COUNT > CompArray; // NOTE : array of pointers to components

class Entity
{
	private:
	// ================================ ATTRIBUTES
		id_t _id; //     NOTE : if the ID is 0, the entity is not supposed to be in EntityManager's map
		bool _active; // NOTE : if flase, all component are treated as unactive, when possible

		CompArray _components;

	// ================================ CORE METHODS
		// NOTE : mutex these is multithreading is implemented

		bool onAdd();
		bool onDel();
		bool onCpy( const Entity &rhs );

		bool addToManager(); //   NOTE : automatically adds this instance to EntityManager's map
		bool delFromManager(); // NOTE : automatically removes this instance to EntityManager's map

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~Entity();

		Entity();
		Entity( bool addEntityToManager, id_t id = 0); // NOTE : should only be called by EntityManager

		Entity( const Entity &rhs );
		Entity &operator=( const Entity &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline id_t getID() const { return _id; }
		inline bool setID( id_t id ){ _id = id; return true; } // NOTE : should only be called by EntityManager
		inline bool delID(){ _id = 0; return true; } //           NOTE : should only be called by EntityManager

		inline bool isActive() const { return _active; }
		inline bool setActivity( bool activate ){ _active = activate; return _active; }

	// ================ GENERAL COMPONENT METHODS
		inline CompArray &getCompArray(){   return _components; }
		comp_count_t      getCompCount()    const; // NOTE : returns the number of non nullptr components
		comp_count_t      getActCompCount() const; // NOTE : returns the number of active components

		TTC inline CompT *getComponent( comp_type_e compType ) const { ( void )compType; return getComponent< CompT >(); } // NOTE " temporary workaround"
		TTC CompT *getComponent() const;

		bool isCompActive( comp_type_e compType, bool activate );
		bool isCompActive( comp_type_e compType ) const;
		bool hasComponent( comp_type_e compType ) const;

		bool addComponent(  comp_type_e compType );
		bool delComponent(  comp_type_e compType, bool freeMem = true );
		bool tickComponent( comp_type_e compType );

		TTC inline bool isCompActive( bool activate ){ return isCompActive( CompT::getStaticType(), activate ); }
		TTC inline bool isCompActive() const { return isCompActive( CompT::getStaticType() ); }
		TTC inline bool hasComponent() const { return hasComponent( CompT::getStaticType() );
		}
		TTC inline bool addComponent(){  return addComponent(  CompT::getStaticType() ); }
		TTC inline bool delComponent(){  return delComponent(  CompT::getStaticType() ); }
		TTC inline bool tickComponent(){ return tickComponent( CompT::getStaticType() ); }

	// ================ SPECIFIC COMPONENT METHODS ( aka, shortcuts to avoid calling getComponent() over and over again )
		// NOTE : these should handle all failure cases gracefully ( e.g. if the component des not exist )

	// ======== POSITION COMPONENT
		vec2_t getPos() const;
		bool setPos(  vec2_t pos );
		bool movePos( vec2_t delta );

		angle_t getAngle() const;
		bool setAngle(  angle_t angle );
		bool moveAngle( angle_t delta );

		fixed_t getLineDistTo( id_t id ) const;
		fixed_t getLineDistTo( Entity  *other ) const;
		fixed_t getLineDistTo( CompPos *other ) const;
		fixed_t getLineDistTo( vec2_t   other ) const;
		fixed_t getLineDistTo( fixed_t x, fixed_t y ) const;

	// ======== MOVEMENT COMPONENT
		vec2_t getVel() const;
		fixed_t getLinearVel() const;
		bool setVel( vec2_t vel );
		bool moveVel( vec2_t delta );

		vec2_t getAcc() const;
		fixed_t getLinearAcc() const;
		bool setAcc( vec2_t acc );
		bool moveAcc( vec2_t delta );

		angle_t getRotVel() const;
		bool setRotVel(  angle_t rotVel );
		bool moveRotVel( angle_t  delta );

		angle_t getRotAcc() const;
		bool setRotAcc(  angle_t rotAcc );
		bool moveRotAcc( angle_t  delta );

	// ======== PHYSICS COMPONENT
		bool isDynamic() const;
		bool setDynamic( bool isDynamic );

	// ======== COLLISION COMPONENT
		bool isCollidable() const;
		bool setCollidable( bool isCollide );

		fixed_t getHitRad() const;
		bool setHitRad(  fixed_t hitRad );
		bool moveHitRad( fixed_t  delta );

	// ======== GRAPHICS COMPONENT
		Color getCol() const;
		bool setCol( Color col );
		bool moveCol( Color delta );

		fixed_t getCircleRadius() const;
		bool setCircleRadius(  fixed_t radius );
		bool moveCircleRadius( fixed_t  delta );

		//================================ OPERATORS
		CompBase *operator[]( comp_type_e compType ) const;
};

typedef vector< Entity > NttVec;

bool IsValidEntity( Entity *Ntt ); // NOTE : Checks if the entity is valid ( ID != 0 )

# include "./Entity_T.hpp"

#endif // ENTITY_HPP

