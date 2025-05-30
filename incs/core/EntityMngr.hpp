#ifndef ENTITY_MNGR_HPP
# define ENTITY_MNGR_HPP

# include "../base.hpp"
# include "./components/CompBase.hpp"
# include "./components/CompTransform.hpp"
# include "./components/CompMovement.hpp"
# include "./components/CompPhysics.hpp"

typedef array< CompBase, CT_COUNT > CmpArr_t; // NOTE : the components of a specific entity, indexed by comp_type_e

class Entity // NOTE : ease-of-access class aggregating components of a given entity's ID
{
	private:
	// ================================ ATTRIBUTES
		id_t     _id; //       NOTE : ID of the entity
		CmpArr_t *_comps; //   NOTE : pointer to the components of the entity, indexed by comp_type_e

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ~Entity() = default;
		inline  Entity( id_t id, CmpArr_t *_comps ) : _id( id ), _comps( _comps )
		{
			flog( _id );
			isValid();
		}

		inline Entity( const Entity &cpy ){ *this = cpy; }
		inline Entity &operator=( const Entity &cpy ){ _id = cpy._id; _comps = cpy._comps; return *this; }

	// ================================ ACCESSORS / MUTATORS
		inline id_t getID() const {  return _id; }
		inline CmpArr_t *getComps(){ return _comps; }

		inline bool     usesComp( comp_type_e type ) const { return  ( *_comps )[ type ].isInit(); }
		inline CompBase *getComp( comp_type_e type ){        return &( *_comps )[ type ]; }

		inline bool isValid() const
		{
			flog( _id );
			if( _id == 0 ){ qlog( "isValid : an ID of 0 is not valid", WARN, 0 ); return false; }
			if( _comps == nullptr ){ qlog( "isValid : entity has no components", WARN, _id ); return false; }
			return true;
		}

	// ================================ COMPONENT METHODS
		inline void initComp( comp_type_e type )
		{
			flog( _id );
			if( !IsValid( type )){ qlog( "initComp : invalid component type " + std::to_string( type ), ERROR, _id ); return; }
			else {( *_comps )[ type ].init( _id ); }
		}
		inline void deinitComp( comp_type_e type )
		{
			flog( _id );
			if( !IsValid( type )){ qlog( "delComp : invalid component type " + std::to_string( type ), ERROR, _id ); return; }
			else {( *_comps )[ type ].deinit(); }
		}

};

typedef vector< CmpArr_t > CmpVec_t; //           NOTE : vector of component arrays, indexed by ID
typedef array<  CmpVec_t, CT_COUNT > CmpTbl_t; // NOTE : component table, indexed first by comp_type_e and then ID
typedef std::set< id_t > id_set_t; //             NOTE : set of IDs for tracking used, active and freed IDs

class EntityMngr
{
	private:
	// ================================ ATTRIBUTES
		static constexpr size_t TblGrpSize = 1024; // NOTE : minimum size of the component table, also used for resizing when necessary

		CmpTbl_t _CmpTbl; // NOTE : array of component vectors, indexed by comp_type_e and ID
		size_t   _CmpTblSize;

		id_t     _maxID;
		id_set_t _usedIDs;   // NOTE : IDs of all entities      to track entities that currently exists
		id_set_t _activeIDs; // NOTE : IDs of active entities   to track entities that are currently active
		id_set_t _freedIDs;  // NOTE : IDs previously freed		  to update maxID / reuse them later

	// ================================ CORE METHODS
		inline id_t getMaxID() const { return _maxID; }
		void updateMaxID();
		id_t getNewID();

		void initTbl(); //   NOTE : (re)initializes the component table, setting the initial size
		void resizeTbl(); // NOTE : updates the component table size, resizing vectors if necessary

		void resetAllComps(); //                        NOTE : resets all components, deinitializing them
		void resetComps( id_t id ); //                  NOTE : resets all components of a given ID
		void resetComps( comp_type_e type ); //         NOTE : resets all components of a given type
		void resetComp( id_t id, comp_type_e type ); // NOTE : resets a specific component of a given type for a given ID

		void clearIDsets(); //      NOTE : clears all ID sets, removing all IDs from used, active and freed sets
		void clearID( id_t id ); // NOTE : clears a specific ID from used and active sets, adds it to freed set

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline  EntityMngr(){ initTbl(); };
		inline ~EntityMngr(){ initTbl(); };

		// NOTE : prevent copying of the EntityMngr instance
		inline EntityMngr(            const EntityMngr &cpy ) = delete;
		inline EntityMngr &operator=( const EntityMngr &cpy ) = delete;

	// ================================ ACCESSORS / MUTATORS
		inline id_set_t *getUsedIDs(){   return &_usedIDs; }
		inline id_set_t *getActiveIDs(){ return &_activeIDs; }
		inline id_set_t *getFreedIDs(){  return &_freedIDs; }

	// ================================ ENTITY METHODS
		bool delID( id_t id );
		id_t addID();

		bool setActiveID( id_t id, bool activate );
		bool isUsedID(    id_t id ) const; // NOTE : checks if an ID is used (   exists in the used IDs set )
		bool isActiveID(  id_t id ) const; // NOTE : checks if an ID is active ( exists in the active IDs set )
		bool isFreeID(    id_t id ) const; // NOTE : checks if an ID is free (   exists in the freed IDs set )

		Entity getEntity( id_t id );

	// ================================ COMPONENT METHODS
		bool hasComp(      id_t id, comp_type_e type ) const; // NOTE : checks if a component of a given type for a given ID is initialized
		bool initComp(     id_t id, comp_type_e type ); //       NOTE : initializes a component of a given type for a given ID
		bool deinitComp(   id_t id, comp_type_e type ); //       NOTE : deinitializes a component of a given type for a given ID
		CompBase *getComp( id_t id, comp_type_e type ); //       NOTE : gets a pointer to a component of a given type for a given ID

	// ================ TICK METHODS
		void tickCompsByType( comp_type_e type );

		//void tickMovement(); // NOTE : tick all movement components
		//void tickCollides(); // NOTE : tick all collidable components
		//void tickPhysics(); //  NOTE : tick all physics components

		//void tickGraphics(); // NOTE : tick all graphics components

	// ================================ STATIC METHODS

};

#endif // ENTITY_MNGR_HPP

