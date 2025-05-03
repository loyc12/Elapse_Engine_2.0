#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <raylib.h>
# include "../../base.hpp"
# include "../component/BaseComp.hpp"
# include "../component/CompPos.hpp"

TTC CompT *CpyCompOver( CompT *dst, CompT *src );

class Entity
{
	private:
	// ================================ ATTRIBUTES
		id_t _id; //     NOTE : if the ID is 0, the entity is not supposed to be in CompManager's map
		bool _active; // NOTE : if flase, all component are treated as unactive, when possible

		BaseComp *_components[ COMP_TYPE_COUNT ];

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
		inline bool isActive( bool activate ) { _active = activate; return _active; }

		inline BaseComp **getAllComps() { return _components; }

		CompC_t  getCompCount() const;

		TTC inline CompT *getComponent( comp_e compType ) const { ( void )compType; return getComponent< CompT >(); } // NOTE " temporary workaround"
		TTC CompT *getComponent() const;

		TTC inline bool isCompActive() const { return isCompActive( CompT::getType() ); }
		bool isCompActive( comp_e compType ) const;

		TTC inline bool isCompActive( bool activate ){ return isCompActive( CompT::getType(), activate ); }
		bool isCompActive( comp_e compType, bool activate );

		TTC inline bool hasComponent() const { return hasComponent( CompT::getType() ); }
		bool hasComponent( comp_e compType ) const;

		TTC inline bool addComponent(){ return addComponent( CompT::getType() ); }
		bool addComponent( comp_e compType );

		TTC inline bool delComponent(){ return delComponent( CompT::getType() ); }
		bool delComponent( comp_e compType, bool freeMem = true );

		TTC inline bool tickComponent(){ return tickComponent( CompT::getType() ); }
		bool tickComponent( comp_e compType );

		//================================ OPERATORS
		BaseComp  *operator[]( comp_e compType ) const;
};

typedef vector< Entity > NttVec;

bool IsValidEntity( Entity *Ntt ); // NOTE : Checks if the entity is valid ( ID != 0 )

# include "./Entity_T.hpp"

#endif // ENTITY_HPP

