#ifndef COMP_BASE_HPP
# define COMP_BASE_HPP

# include "../../base.hpp"

typedef byte_t comp_count_t;
typedef enum : comp_count_t
{
	COMP_TRANSFORM, // NOTE : position, rotation, scale
	COMP_MOVEMENT, //  NOTE : velocity, acceleration, etc.
	COMP_COLLIDE, //   NOTE : collision detection & response
	COMP_PHYSIC, //    NOTE : mass, friction, elasticity, etc.

	COMP_TEXT, //      NOTE : text rendering ( font, size, color, etc. )
	COMP_SOUND, //     NOTE : sound effects, volume, pitch, etc.
	COMP_GRAPHIC, //   NOTE : visual rendering ( sprite, texture, etc. )
	COMP_ANIM, //      NOTE : animation ( frame, speed, etc )

	COMP_SCRIPT, //    NOTE : script component
	// NOTE : add more component types as needed



	// NOTE : maximum of 253 component types, as the last two values are reserved
	COMP_TYPE_COUNT, //      NOTE : only for internal use
	COMP_TYPE_BASE = 255, // NOTE : only for internal use
} comp_type_e;

inline bool IsValid( id_t id ){ return( id > 0 ); }
inline bool IsValid( comp_type_e type ){ return( type == COMP_TYPE_BASE || type >= COMP_TYPE_COUNT ); }
inline bool IsValid( comp_type_e type, id_t id )
{
	flog( 0 );
	if ( !IsValid( id ) || !IsValid( type ))
	{
		qlog( "IsValid : invalid component type or ID", WARN, 0 );
		return false;
	}
	return true;
}

class CompBase
{
	protected:
	// ================================ ATTRIBUTES
		id_t _id; // NOTE : the entity this component belongs to

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline virtual ~CompBase(){ deinit(); } // NOTE : deinitialize the component on destruction
		inline CompBase( id_t NttID = 0 ) //       NOTE : initializes the component with the given ID if valid
		{
			if( IsValid( NttID )){ init( NttID ); }
			else { _id = 0; }
		}

		inline CompBase( const CompBase &cpy ){ *this = cpy; }
		inline CompBase &operator=( const CompBase &cpy )
		{
			flog( 0 );
			this->_id = cpy._id;
			return *this;
		}

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getType(){ return COMP_TYPE_BASE; } // NOTE : base type, should be overridden in derived classes

		inline bool isInit() const { return _id != 0; }
		inline bool deinit(){ _id = 0; return true; }
		inline bool init( id_t id )
		{
			flog( 0 );
			if( !IsValid( id ))
			{
				qlog( "CompBase::init : invalid ID " + std::to_string( id ), ERROR, 0 );
				return false; // NOTE : if the ID is invalid, return false
			}
			_id = id; return true;
		}

		// ================================ TICK METHODS
		inline bool hasSisterComps() const { return true; } // NOTE : checks is asigned entity has required co-components - override this in derived classes
		inline bool canTick() const { return isInit() && hasSisterComps(); } // NOTE : checks if the component can tick - override this in derived classes
};

#endif // COMP_BASE_HPP