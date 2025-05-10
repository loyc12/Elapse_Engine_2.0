#ifndef COMP_BASE_HPP
# define COMP_BASE_HPP

# include <raylib.h>
# include "../../base.hpp"

typedef byte_t comp_count_t;
typedef enum : comp_count_t
{
	COMP_POSITION = 0,
	COMP_MOVEMENT,
	COMP_PHYSIC,
	COMP_COLLIDE,

	COMP_TEXT,
	COMP_SOUND,
	COMP_SHAPE, // TODO : implement the shape component
	COMP_GRAPHIC,

	COMP_SCRIPT,

	COMP_TYPE_COUNT, //      NOTE : should never be used for actual components
	COMP_TYPE_BASE = 255, // NOTE : should never be used for actual components
} comp_type_e;

inline bool IsValidCompType( comp_type_e type )
{
	flog( 0 );
	if( type == COMP_TYPE_BASE )
	{
		qlog( "Component type cannot be COMP_TYPE_BASE", WARN, 0 );
		return false;
	}
	if( type >= COMP_TYPE_COUNT )
	{
		qlog( "IsValidCompType : Component type is out of range", WARN, 0 );
		return false;
	}
	return true;
}

# define COMP_DEF_ACTIVITY true

class Entity; // NOTE : forward declaration

// NOTE : Components, like Entities, are created and destroyed via the Component Manager
class CompBase
{
	protected:
	// ================================ ATTRIBUTES
		Entity *_Ntt; //    NOTE : the entity this component belongs to
		bool    _active; // NOTE : mutex this if we ever multithread onTick() calls

		inline virtual void onCpy( const CompBase &rhs ){ _active = rhs._active; } // NOTE : ovveride this in derived classes

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline virtual ~CompBase(){};

		inline CompBase() : _Ntt( nullptr ), _active( COMP_DEF_ACTIVITY ){}
		inline CompBase( Entity *Ntt, bool isActive = COMP_DEF_ACTIVITY ): _Ntt( Ntt ), _active( isActive ){}

		inline CompBase( const CompBase &rhs ) : CompBase(){ *this = rhs; }
		inline CompBase &operator=( const CompBase &rhs ){ onCpy( rhs ); return *this; }

	// ================================ ACCESSORS / MUTATORS
		inline static  comp_type_e getStaticType(){  return COMP_TYPE_BASE; }
		inline virtual comp_type_e getType() const { return COMP_TYPE_BASE; } // NOTE : override this in derived classes

		inline bool isActive() const { return _active; }
		inline bool setActivity( bool activate ){ _active = activate; return _active; }

		inline virtual bool hasSisterComps() const { return true; } // NOTE : override this in derived classes

	// ================ ENTITY METHODS
		inline Entity *getEntity() const { return _Ntt; }
		inline bool    hasEntity() const { return _Ntt != nullptr; }
		inline bool    setEntity( Entity *Ntt ){  _Ntt = Ntt; return true; }
		inline bool    voidEntity(){ _Ntt = nullptr; return true; }

		id_t getEntityID() const;
		bool isEntityActive() const;
		bool setEntityActivity( bool activate );

	// ================================ TICK METHODS
	bool canTick() const; // NOTE : avoid overriding this one : use follw up checks instead

	// NOTE : use CRTP if onTick() becomes a performance bottleneck
	// NOTE : should return false if the component did not tick ( for example, if the "_active" flag is set to false )
	virtual bool onTick(); // NOTE : override this in derived classes
};

// ================================ TEMPLATES



template <typename CompT>
concept IsCompBase = std::is_base_of<CompBase, CompT>::value; // NOTE : this is a concept to check if a type is derived from CompBase

// NOTE : this is shorthand to define a template that requires the type to be derived from CompBase
# define TTC template <typename CompT> requires IsCompBase< CompT >


TTC inline bool IsValidComponent( CompT *comp )
{
	flog( 0 );
	if( comp == nullptr )
	{
		qlog( "IsValidComponent : Component is nullptr", WARN, 0 );
		return false;
	}
	if( !IsValidCompType( comp->getType() ))
	{
		qlog( "IsValidComponent : Component type is invalid", WARN, 0 );
		return false;
	}
	if( comp->getEntityID() == 0 )
	{
		qlog( "IsValidComponent : Component ID cannot be 0", WARN, 0 );
		return false;
	}
	return true;
}

TTC inline CompT *CompFactory( Entity *Ntt = nullptr, bool isActive = COMP_DEF_ACTIVITY )
{
	flog( 0 );
	CompT *comp = new CompT( Ntt, isActive );
	if( comp == nullptr )
	{
		qlog( "CompFactory : Component creation failed", ERROR, 0 );
		return nullptr;
	}
	return comp;
}

TTC inline CompT *CompFactory( CompT *src, Entity *Ntt = nullptr )
{
	flog( 0 );
	CompT *comp = new CompT( *src );
	if( comp == nullptr )
	{
		qlog( "CompFactory : Component creation failed", ERROR, 0 );
		return nullptr;
	}
	comp->setEntity( Ntt );
	return comp;
}

#endif // COMP_BASE_HPP