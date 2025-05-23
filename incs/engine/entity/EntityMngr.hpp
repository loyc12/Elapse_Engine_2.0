#ifndef ENTITY_MNGR_HPP
# define ENTITY_MNGR_HPP

# include "../../base.hpp"
# include "../component/CompBase.hpp"
# include "../entity/Entity.hpp"

typedef std::unordered_map< id_t, Entity* > NttMap_t;

Entity *CpyEntityOver( Entity *src, Entity *dst );

class EntityMngr
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
		inline  EntityMngr(){ _maxID = 0; };
		inline ~EntityMngr(){ deleteAllEntities(); };

	// ================================ ACCESSORS / MUTATORS

	// ================ ENTITY METHODS
		inline id_t getEntityCount() const { return _NttMap.size(); }
		Entity *getEntity( id_t id ) const;

		inline bool isUsedID( id_t id ) const { return  hasEntity( id ); }
		inline bool isFreeID( id_t id ) const { return !hasEntity( id ); }

		bool hasEntity( id_t id ) const;
		bool addEntity( id_t id ); // NOTE : should only be called by Entity's AddToMngr()
		bool delEntity( id_t id, bool freeMem = true );

		bool hasThatEntity( Entity *Ntt ) const;
		bool addThatEntity( Entity *Ntt );
		bool delThatEntity( Entity *Ntt, bool freeMem = true );

		bool defragEntityMap(); // NOTE : removes nullptr entities from the map and recalculates the max ID

		// NOTE : add + copy entity and its components
		inline bool dupEntity( id_t src ) { return dupEntity( getEntity( src )); }
		bool dupEntity( Entity *src );

	// ================ COMPONENT METHODS
		comp_count_t getCompCount( id_t id ) const;
		comp_count_t getActCompCount( id_t id ) const;

		bool hasComponent( id_t id, comp_type_e compType ) const;
		bool addComponent( id_t id, comp_type_e compType );
		bool delComponent( id_t id, comp_type_e compType, bool freeMem = true );

		TTC inline CompT *getComponent( id_t id, comp_type_e compType ) const { ( void )compType; return getComponent< CompT >( id ); };
		TTC CompT *getComponent( id_t id ) const;

		TTC inline bool hasComponent( id_t id ) const { return hasComponent( id, CompT::getStaticType() ); };
		TTC inline bool addComponent( id_t id ){        return addComponent( id, CompT::getStaticType() ); };
		TTC inline bool delComponent( id_t id, bool freeMem = true ){ return delComponent( id, CompT::getStaticType(), freeMem ); };

	// ================================ UPDATE METHODS
		void updateAllEntities(); //   NOTE : calls the onTick() method of all components in the map ( one entity at a time )
		void updateAllComponents(); // NOTE : calls the onTick() method of all components in the map ( each component type at a time)

		TTC inline void updateComps(){ updateCompsByType( CompT::getStaticType() ); };
		void updateCompsByType( comp_type_e compType ); // NOTE : calls the onTick() method of all components of the given type in the map

	// ================ TICK METHODS
		//void tickPositions(); // NOTE : does nothing
		void tickMovements(); //   NOTE : position update
		void tickPhysics(); //     NOTE : eg. gravity
		void tickCollides(); //    NOTE : collision detection

		//void tickTexts(); //  NOTE : does nothing
		void tickSounds(); //   NOTE : sound update
		void tickShapes(); //   NOTE : shape update
		void tickGraphics(); // NOTE : visual rendering

		void tickScripts(); //  NOTE : script execution

	// ================================ STATIC METHODS
		// NOTE : these log errors if the check fails ( aka return false )
		static bool isValidID( id_t id ); // NOTE : Checks if the ID is above the current ID use range ( _maxID )

	// ================================ FACTORY METHODS
		// NOTE : if ID is 0, the entity is not supposed to be in EntityMngr's map
		static Entity *EntityFactory( id_t id = 0 ); // NOTE : allocs a new entity with the given ID
		static Entity *EntityFactory( Entity *src, id_t id = 0 ); // NOTE : allocs a new entity with the given ID, based on the src entity
};

CompBase *CompFactory( comp_type_e compType, Entity *Ntt = nullptr, bool isActive = COMP_DEF_ACTIVITY );

# include "./EntityMngr_T.hpp"

#endif // ENTITY_MNGR_HPP

