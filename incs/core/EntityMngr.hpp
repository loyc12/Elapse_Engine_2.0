#ifndef ENTITY_MNGR_HPP
# define ENTITY_MNGR_HPP

# include "../base.hpp"
# include "./components/CompBase.hpp"
//# include "./Entity.hpp"

class Entity; // NOTE : forward declaration

typedef std::unordered_map< id_t, Entity* > NttMap_t; //      NOTE : map of entities, indexed by id_t ( entity ID )
typedef std::array< CompBase*, COMP_TYPE_COUNT > CmpTbl_t; // NOTE : array of components, indexed by comp_type_e
typedef std::set< id_t > id_set_t; // NOTE : set of IDs, used to track specific IDs ( for example, freed IDs )

class EntityMngr
{
	private:
	// ================================ ATTRIBUTES

		NttMap_t _NttMap;
		CmpTbl_t _CmpTbl; // NOTE : array of components, indexed by comp_type_e

		id_t     _maxID;
		id_set_t _usedIDs;   // NOTE : IDs of all entities      to track entities that currently exists
	//id_set_t _activeIDs; // NOTE : IDs of active entities   to track entities that are currently active
	//id_set_t _toAddIDs;  // NOTE : IDs to add               to track entities that are marked for addition
	//id_set_t _toDelIDs;  // NOTE : IDs to delete            to track entities that are marked for deletion
		id_set_t _freedIDs;  // NOTE : IDs previously freed		  to update maxID / reuse them later

	// ================================ CORE METHODS

		void onAdd();
		void onDel();

		inline id_t getMaxID() const { return _maxID; }
		void updateMaxID();
		id_t getNewID();

		void clearAllIDs(); //        NOTE : clears all ID sets   WARN : clear all entities beforehand !
		void clearAllEntities(); //   NOTE : deletes all entities in the entity map          TODO : IMPLEMENT US
		void clearAllComponents(); // NOTE : deletes all components in the component table   TODO : IMPLEMENT US

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS

		inline  EntityMngr(){ onAdd(); };
		inline ~EntityMngr(){ onDel(); };

	// ================================ ACCESSORS / MUTATORS

		inline id_set_t *getUsedIDs(){   return &_usedIDs; }
	//inline id_set_t *getActiveIDs(){ return &_activeIDs; }
	//inline id_set_t *getToAddIDs(){  return &_toAddIDs; }
	//inline id_set_t *getToDelIDs(){  return &_toDelIDs; }
		inline id_set_t *getFreedIDs(){  return &_freedIDs; }

	// ================ ENTITY METHODS


	// ================ COMPONENT METHODS

		void updateAllComponents();

	// ================ TICK METHODS

		void tickMovements(); // NOTE : position update
		void tickPhysics(); //   NOTE : eg. gravity
		void tickCollides(); //  NOTE : collision detection

		void tickSounds(); //    NOTE : sound update
		void tickShapes(); //    NOTE : shape update
		void tickGraphics(); //  NOTE : visual rendering

		void tickScripts(); //   NOTE : script execution

	// ================================ STATIC METHODS

};

#endif // ENTITY_MNGR_HPP

