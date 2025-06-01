#ifndef COMP_BASE_HPP
# define COMP_BASE_HPP

# include "../../base.hpp"

typedef byte_t comp_count_t;
typedef enum : comp_count_t
{
	CT_TRANSFORM, // NOTE : position, rotation, scale
	CT_MOVEMENT, //  NOTE : velocity, acceleration, etc.
	CT_COLLIDES, //  NOTE : collision detection & response
	CT_PHYSICS, //   NOTE : mass, friction, elasticity, etc.

	CT_TEXT, //      NOTE : text rendering ( font, size, color, etc. )
	CT_AUDIO, //     NOTE : sound effects, volume, pitch, etc.
	CT_TEXTURE, //	 NOTE : texture data ( image, size, format, etc. )
	CT_SPRITE, //    NOTE : animated texture ( sprite sheet, frame rate, etc. )
	CT_GRAPHICS, //  NOTE : visual rendering ( sprite, texture, etc. )

	// NOTE : add more component types as needed

	// NOTE : maximum of 253 component types, as the last two values are reserved
	CT_COUNT, //      NOTE : only for internal use
	CT_BASE = 255, // NOTE : only for internal use
} comp_type_e;

inline bool IsValid( id_t id ){ return( id > 0 ); }
inline bool IsValid( comp_type_e type ){ return( type < CT_COUNT ); }
inline bool IsValid( id_t id, comp_type_e type )
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
		inline virtual ~CompBase(){ deinit(); }
		inline CompBase( id_t NttID = 0 )
		{
			if( IsValid( NttID )){ init( NttID ); }
			else { _id = 0; }
		}

		inline CompBase( const CompBase &cpy ){ *this = cpy; }
		inline CompBase &operator=( const CompBase &cpy )
		{
			this->_id = cpy._id;
			return *this;
		}

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getType(){ return CT_BASE; } // NOTE : base type, should be defined in derived classes

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

		 // TODO : move this logic to the EntityMngr, so that it can run in batches
		bool hasSisterComp( comp_type_e type ) const;   bool canTick() const;
};

#endif // COMP_BASE_HPP