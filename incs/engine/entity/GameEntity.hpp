#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

# include <raylib.h>
# include "../component/BaseComp.hpp"
# include "../../base.hpp"

// NOTE : Entities, like Components, are created and destroyed via the CompManager
// NOTE : However, creating an entity anywhere adds calls the apropriate CompManager functions and adds it to the map

class GameEntity
{
	private:
	// ================================ ATTRIBUTES
		id_t _id; //     NOTE : if the ID is 0, the entity is not supposed to be in CompManager's map
		bool _active; // NOTE : if flase, all component are treated as unactive, when possible

		BaseComp *_components[ COMP_TYPE_COUNT ];

	// ================================ CORE METHODS
		// NOTE : mutex these is multithreading is implemented
		bool addToManager(); //   NOTE : automatically adds this instance to CompManager's map
		bool delFromManager(); // NOTE : automatically removes this instance to CompManager's map
		void onCpy( const GameEntity &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~GameEntity();

		GameEntity();
		GameEntity( bool addEntityToManager, id_t id = 0); // NOTE : should only be called by CompManager

		GameEntity( const GameEntity &rhs );
		GameEntity &operator=( const GameEntity &rhs );

	// ================================ ACCESSORS / MUTATORS
		id_t getID() const;
		bool setID( id_t id ); // NOTE : should only be called by CompManager
		bool delID(); //          NOTE : should only be called by CompManager

		bool isActive() const;
		bool isActive( bool activate );

		bool delEntity();
		//bool rmvEntity();

		CompC_t  getCompCount();
		CompArr *getAllComponents();

		TTC bool isComponentActive() const;
		TTC bool isComponentActive( bool activate );

		TTC CompT *getComponent();
		//TTC CompT *cpyComponent();


		TTC bool hasComponent() const;
		TTC bool addComponent();
		TTC bool delComponent();

		//TTC bool hasThatComponent( CompT *component ) const;

};
typedef vector< GameEntity > NttVec;

//# include "./GameEntityT.hpp"

#endif // GAME_ENTITY_HPP

