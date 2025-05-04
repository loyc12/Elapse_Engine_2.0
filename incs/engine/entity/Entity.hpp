#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <raylib.h>
# include "../../base.hpp"

# include "../component/CompBase.hpp"
# include "../component/CompPos.hpp"
# include "../component/CompMove.hpp"
# include "../component/CompGraph.hpp"

TTC CompT *CpyCompOver( CompT *dst, CompT *src );

typedef array< CompBase*, COMP_TYPE_COUNT > CompArray; // NOTE : array of pointers to components

class Entity
{
	private:
	// ================================ ATTRIBUTES
		id_t _id; //     NOTE : if the ID is 0, the entity is not supposed to be in CompManager's map
		bool _active; // NOTE : if flase, all component are treated as unactive, when possible

		CompArray _components;

	// ================================ CORE METHODS
		// NOTE : mutex these is multithreading is implemented

		bool onAdd();
		bool onDel();
		bool onCpy( const Entity &rhs );

		bool addToManager(); //   NOTE : automatically adds this instance to CompManager's map
		bool delFromManager(); // NOTE : automatically removes this instance to CompManager's map

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~Entity();

		Entity();
		Entity( bool addEntityToManager, id_t id = 0); // NOTE : should only be called by CompManager

		Entity( const Entity &rhs );
		Entity &operator=( const Entity &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline id_t getID() const { return _id; }
		inline bool setID( id_t id ){ _id = id; return true; } // NOTE : should only be called by CompManager
		inline bool delID(){ _id = 0; return true; } //           NOTE : should only be called by CompManager

		inline bool isActive() const { return _active; }
		inline bool setActivity( bool activate ){ _active = activate; return _active; }

	// ================ GENERAL COMPONENT METHODS
		inline CompArray *getCompArray(){   return &_components; }
		comp_count_t      getCompCount()    const; // NOTE : returns the number of non nullptr components
		comp_count_t      getActCompCount() const; // NOTE : returns the number of active components

		TTC inline CompT *getComponent( comp_type_e compType ) const { ( void )compType; return getComponent< CompT >(); } // NOTE " temporary workaround"
		TTC CompT *getComponent() const;

		TTC inline bool isCompActive() const { return isCompActive( CompT::getStaticType() ); }
		bool isCompActive( comp_type_e compType ) const;

		TTC inline bool isCompActive( bool activate ){ return isCompActive( CompT::getStaticType(), activate ); }
		bool isCompActive( comp_type_e compType, bool activate );

		TTC inline bool hasComponent() const { return hasComponent( CompT::getStaticType() ); }
		bool hasComponent( comp_type_e compType ) const;

		TTC inline bool addComponent(){ return addComponent( CompT::getStaticType() ); }
		bool addComponent( comp_type_e compType );

		TTC inline bool delComponent(){ return delComponent( CompT::getStaticType() ); }
		bool delComponent( comp_type_e compType, bool freeMem = true );

		TTC inline bool tickComponent(){ return tickComponent( CompT::getStaticType() ); }
		bool tickComponent( comp_type_e compType );

	// ================ SPECIFIC COMPONENT METHODS
		// NOTE : CompPos
		Vector2 getPos() const;
		bool setPos( Vector2 pos );
		bool setPos( float x, float y );

		// NOTE : CompMove
		Vector2 getVel() const;
		bool setVel( Vector2 vel );
		bool setVel( float x, float y );

		Vector2 getAcc() const;
		bool setAcc( Vector2 acc );
		bool setAcc( float x, float y );

		// NOTE : CompGraph
		Color getCol() const;
		bool setCol( Color col );
		bool setCol( byte_t r, byte_t g, byte_t b, byte_t a );

		float getCircleRadius() const;
		bool setCircleRadius( float radius );
		bool setCircleRadius( float x, float y );

		//================================ OPERATORS
		CompBase  *operator[]( comp_type_e compType ) const;
};

typedef vector< Entity > NttVec;

bool IsValidEntity( Entity *Ntt ); // NOTE : Checks if the entity is valid ( ID != 0 )

# include "./Entity_T.hpp"

#endif // ENTITY_HPP

