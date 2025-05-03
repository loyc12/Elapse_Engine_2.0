#ifndef COMP_MANAGER_HPP
# define COMP_MANAGER_HPP

# include "../../base.hpp"
# include "../entity/Entity.hpp"

# include "../component/BaseComp.hpp"
# include "../component/CompPos.hpp"

typedef std::unordered_map< id_t, Entity* > NttMap_t;

Entity *CpyEntityOver( Entity *src, Entity *dst );

class CompManager
{
	private:
	// ================================ ATTRIBUTES
		NttMap_t _NttMap;
		id_t     _maxID;

	// ================================ CORE METHODS
		inline id_t getMaxID() const { return _maxID; }
		inline id_t getNewID()
		{
			qlog( "getNewID : assigning new ID: " + std::to_string( _maxID + 1 ), DEBUG, 0 );
			return ++_maxID;
		}

		void deleteAllEntities();
		void updateMaxID();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline CompManager(){ _maxID = 0; };
		inline ~CompManager(){ deleteAllEntities(); };

	// ================================ ACCESSORS / MUTATORS

	// ================ ENTITY METHODS
		id_t    getEntityCount() const;
		Entity *getEntity( id_t id ) const;

		inline bool isUsedID( id_t id ) const { return  hasEntity( id ); }
		inline bool isFreeID( id_t id ) const { return !hasEntity( id ); }

		bool hasEntity( id_t id ) const;
		bool addEntity( id_t id ); // NOTE : should only be called by Entity's AddToManager()
		bool delEntity( id_t id, bool freeMem = true );

		bool hasThatEntity( Entity *Ntt ) const;
		bool addThatEntity( Entity *Ntt );
		bool delThatEntity( Entity *Ntt, bool freeMem = true );

		// NOTE : add + copy entity and its components
		bool dupEntity( id_t src );
		bool dupEntity( Entity *src );

	// ================ COMPONENT METHODS
		CompC_t getCompCount( id_t id ) const;

		TTC inline CompT *getComponent( id_t id ) const { return getComponent( id, CompT::getType() ); };
		TTC CompT *getComponent( id_t id, comp_e compType ) const;

		TTC inline bool hasComponent( id_t id ) const { return hasComponent( id, CompT::getType() ); };
		bool hasComponent( id_t id, comp_e compType ) const;

		TTC inline bool addComponent( id_t id ) { return addComponent( id, CompT::getType() ); };
		bool addComponent( id_t id, comp_e compType );

		TTC inline bool delComponent( id_t id, bool freeMem = true ) { return delComponent( id, CompT::getType(), freeMem ); };
		bool delComponent( id_t id, comp_e compType, bool freeMem = true );

	// ================================ UPDATE METHODS
		void updateAllEntities(); //   NOTE : calls the onTick() method of all components in the map ( one entity at a time )
		void updateAllComponents(); // NOTE : calls the onTick() method of all components in the map ( each component type at a time)

		TTC inline void updateComps() { updateCompsByType( CompT::getType() ); };
		void updateCompsByType( comp_e compType ); // NOTE : calls the onTick() method of all components of the given type in the map

	// ================================ STATIC METHODS

		// NOTE : these log errors if the check fails ( aka return false )
		static bool isValidID(   id_t id     ); // NOTE : Checks if the ID is above the current ID use range ( _maxID )

	// ================================ FACTORY METHODS
		// NOTE : if ID is 0, the entity is not supposed to be in CompManager's map
		static Entity *NttFactory( id_t id = 0 ); // NOTE : allocs a new entity with the given ID
		static Entity *NttFactory( Entity *src, id_t id = 0 ); // NOTE : allocs a new entity with the given ID, based on the src entity
};

BaseComp *CompFactory( comp_e compType, id_t id = 0 );

//# include "./CompManagerT.hpp"

#endif // COMP_MANAGER_HPP

