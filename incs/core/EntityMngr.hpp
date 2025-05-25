#ifndef ENTITY_MNGR_HPP
# define ENTITY_MNGR_HPP

# include "../base.hpp"
# include "./components/CompBase.hpp"

typedef vector< CompBase > CmpVec_t; // NOTE : vector of components
typedef array< CompBase*, COMP_TYPE_COUNT + 1 > CmpArr_t; // NOTE : array of component pointers, indexed by comp_type_e

class Entity // NOTE : ease-of-access class aggregating components of a given entity's ID
{
	private:
	// ================================ ATTRIBUTES
		id_t     _id; //       NOTE : ID of the entity
		bool     _isInMngr; // NOTE : whether the entity itself is saved in the EntityMngr
		CmpArr_t _comps; //    NOTE : array of components, indexed by comp_type_e

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~Entity();   Entity( id_t id, bool addToMngr = true );

		inline Entity( const Entity &cpy ){ *this = cpy; }
		inline Entity &operator=( const Entity &cpy ){ _id = cpy._id; _comps = cpy._comps; return *this; }

	// ================================ ACCESSORS / MUTATORS
		inline id_t getID() const { return _id; }
		inline CmpArr_t getComps(){ return _comps; }

		inline bool hasComp( comp_type_e type ) const { return _comps[ type ] != nullptr && _comps[ type ]->isInit(); }
		inline CompBase *getComp( comp_type_e type ){   return _comps[ type ]; }

		inline bool isInMngr() const { return _isInMngr; }
		inline void setIsInMngr( bool isInMngr ){ _isInMngr = isInMngr; }

	// ================================ COMPONENT METHODS
		inline void initComp( comp_type_e type )
		{
			flog( _id );
			if( _comps[ type ] == nullptr ){ qlog( "addComp : no adress specified : cannot init component of type " + std::to_string( type ), ERROR, 0 ); }
			else
			{
				_comps[ type ]->init( _id );
				qlog( "addComp : initiated component of type " + std::to_string( type ) + " for entity with ID " + std::to_string( _id ), DEBUG, 0 );
			}
		}
		inline void deinitComp( comp_type_e type )
		{
			flog( _id );
			if( _comps[ type ] == nullptr ){ qlog( "delComp : no adress specified : cannot deinit component of type " + std::to_string( type ), ERROR, 0 ); }
			else
			{
				_comps[ type ]->deinit();
				qlog( "delComp : deinitialized component of type " + std::to_string( type ) + " for entity with ID " + std::to_string( _id ), DEBUG, 0 );
			}
		}

		inline bool isValid() const
		{
			flog( _id );
			if( _id == 0 ){ qlog( "isValid : entity with ID 0 is not valid", WARN, 0 ); return false; }

			for( comp_count_t type = 0; type < COMP_TYPE_COUNT; ++type )
			{
				// NOTE : if any component pointer is nullptr, the entity is not valid ( bad initialization )
				if( _comps[ type ] == nullptr ){ return false; }
			}
			return true;
		}

};

typedef unordered_map< id_t, Entity* > NttMap_t;
typedef array< CmpVec_t, COMP_TYPE_COUNT + 1 > CmpTbl_t;
typedef std::set< id_t > id_set_t; // NOTE : set of IDs, used to track specific IDs ( for example, freed IDs )

class EntityMngr
{
	private:
	// ================================ ATTRIBUTES
		CmpTbl_t _CmpTbl; // NOTE : array of component vectors, indexed by comp_type_e and ID
		NttMap_t _NttMap; // NOTE : map of aggregated entities, indexed by ID

		static constexpr id_t GroupSize = 1024; // NOTE : minimum size of the component table, also used for resizing when necessary
		id_t _maxPossibleID;

		id_t     _maxID;
		id_set_t _usedIDs;   // NOTE : IDs of all entities      to track entities that currently exists
		id_set_t _activeIDs; // NOTE : IDs of active entities   to track entities that are currently active
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

		// NOTE : prevent copying of the EntityMngr instance
		inline EntityMngr(            const EntityMngr &cpy ) = delete;
		inline EntityMngr &operator=( const EntityMngr &cpy ) = delete;

	// ================================ ACCESSORS / MUTATORS
		inline id_set_t *getUsedIDs(){   return &_usedIDs; }
		inline id_set_t *getActiveIDs(){ return &_activeIDs; }
		inline id_set_t *getFreedIDs(){  return &_freedIDs; }

	// ================================ ENTITY METHODS
		bool hasID( id_t id ) const;
		bool delID( id_t id );
		id_t addID();

		bool setActivity( id_t id, bool activate );
		bool isActive(    id_t id ) const;
		bool isFreeID(    id_t id ) const;

		Entity *getNewEntity();
		Entity *getEntity( id_t id );

		bool hasNttPtr( id_t id ) const; // NOTE : checks if an entity with the given ID is stored in the NttMap
		bool storeNttPtr( Entity *entity );
		bool removeNttPtr( id_t id );
		void clearAllNtts(); // NOTE : clears the NttMap, deleting all entities stored in it

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

