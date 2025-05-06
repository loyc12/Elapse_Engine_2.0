#ifndef COMP_POS_HPP
# define COMP_POS_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_POS { 0, 0 } // NOTE : default position for the component

class CompPos : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		Vector2 _pos; // NOTE : position of the component
		//angle_t _angle; // NOTE : angle of the component ( not used yet )

	// ================================ CORE METHODS
		void onCpy( const CompPos &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompPos();

		CompPos();
		CompPos( Entity *Ntt,
			bool    isActive = COMP_DEF_ACTIVITY,
			Vector2 pos      = COMP_DEF_POS
		);

		CompPos( const CompPos &rhs );
		CompPos &operator=( const CompPos &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_POSITION; }
		inline comp_type_e getType() const override { return COMP_POSITION; }

		// NOTE : checks if the parent entity exists ( no component dependencies for CompPos )
		inline bool hasSisterComps() const override { return hasEntity(); }

	// ================ POSITION METHODS
		inline Vector2 getPos() const { return _pos; }
		inline bool   voidPos(){ _pos = COMP_DEF_POS; return true; }

		inline bool setPos( Vector2 pos ){ _pos = pos; return true; }
		inline bool setPos( float x, float y ){ _pos.x = x; _pos.y = y; return true; }

		inline bool changePos( Vector2 delta ){ _pos.x += delta.x; _pos.y += delta.y; return true; }
		inline bool changePos( float dx, float dy ){ _pos.x += dx; _pos.y += dy; return true; }

	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompPos
};

#endif // COMP_POS_HPP