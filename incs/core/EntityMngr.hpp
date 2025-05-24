#ifndef ENTITY_MNGR_HPP
# define ENTITY_MNGR_HPP

# include "../base.hpp"
# include "./components/CompBase.hpp"

typedef vector< CompBase > CmpVec_t; // NOTE : array of components, indexed by ID
typedef array< CmpVec_t, COMP_TYPE_COUNT + 1 > CmpTbl_t; // NOTE : array of component arrays, indexed by comp_type_e and then ID
typedef std::set< id_t > id_set_t; // NOTE : set of IDs, used to track specific IDs ( for example, freed IDs )

class EntityMngr
{
	private:
	// ================================ ATTRIBUTES
		CmpTbl_t _CmpTbl; // NOTE : array of components, indexed by comp_type_e

		static constexpr id_t GroupSize = 1024; // NOTE : size of the chunk for the component table, can be adjusted as needed
		id_t _maxPossibleID;

		id_t     _maxID;
		id_set_t _usedIDs;   // NOTE : IDs of all entities      to track entities that currently exists
		id_set_t _activeIDs; // NOTE : IDs of active entities   to track entities that are currently active
	//id_set_t _toAddIDs;  // NOTE : IDs to add               to track entities that are marked for addition
	//id_set_t _toDelIDs;  // NOTE : IDs to delete            to track entities that are marked for deletion
		id_set_t _freedIDs;  // NOTE : IDs previously freed		  to update maxID / reuse them later

	// ================================ CORE METHODS
		void onAdd();
		void onDel();

		inline id_t getMaxID() const { return _maxID; }
		void updateMaxID();
		id_t getNewID();

		void clearAllIDs(); //                        NOTE : clears all ID sets
		void clearID( id_t id ); //                   NOTE : clears a specific ID from all ID sets

		void clearAllComps(); //                      NOTE : deletes all components in the component table
		void clearCompsByType( comp_type_e type ); // NOTE : clears all components of a specific type

		void initCompTables(); //                     NOTE : initializes the component table with empty component arrays
		void resizeCompTables(); //                   NOTE : updates the component table, resizing arrays if necessary

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline  EntityMngr(){ onAdd(); };
		inline ~EntityMngr(){ onDel(); };

	// ================================ ACCESSORS / MUTATORS
		inline id_set_t *getUsedIDs(){   return &_usedIDs; }
		inline id_set_t *getActiveIDs(){ return &_activeIDs; }
	//inline id_set_t *getToAddIDs(){  return &_toAddIDs; }
	//inline id_set_t *getToDelIDs(){  return &_toDelIDs; }
		inline id_set_t *getFreedIDs(){  return &_freedIDs; }

	// ================================ ENTITY METHODS
		bool hasEntity( id_t id ) const;
		bool delEntity( id_t id );
		id_t addEntity();

		bool setActivity( id_t id, bool activate );
		bool isActive(    id_t id ) const;
		bool isFreeID(    id_t id ) const;

	// ================================ COMPONENT METHODS
		void updateAllComps();
		void updateCompsByType( comp_type_e type );

		bool hasComp( comp_type_e type, id_t id ) const; // NOTE : checks if a component of a given type for a given ID is activated
		bool delComp( comp_type_e type, id_t id );
		bool addComp( comp_type_e type, id_t id );

		CompBase *getComp( comp_type_e type, id_t id );
		CmpVec_t getAllComps( id_t id ); // NOTE : returns all components for a given ID

	// ================ TICK METHODS
		//void tickMovements(); // NOTE : position update
		//void tickPhysics(); //   NOTE : eg. gravity
		//void tickCollides(); //  NOTE : collision detection

		//void tickSounds(); //    NOTE : sound update
		//void tickShapes(); //    NOTE : shape update
		//void tickGraphics(); //  NOTE : visual rendering

		//void tickScripts(); //   NOTE : script execution

	// ================================ STATIC METHODS

};

#endif // ENTITY_MNGR_HPP

