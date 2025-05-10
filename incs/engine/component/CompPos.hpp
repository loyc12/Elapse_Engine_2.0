#ifndef COMP_POS_HPP
# define COMP_POS_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_POS vec2_t() // NOTE : { 0, 0 } default position for the component
# define NULL_POS { LONG_MAX, LONG_MAX } // NOTE : means you fucked up bud

class CompPos : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		vec2_t  _pos; //   NOTE : position of the component
		angle_t _angle; // NOTE : angle of the component

	// ================================ CORE METHODS
		void onCpy( const CompPos &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompPos();

		CompPos();
		CompPos( Entity *Ntt,
			bool isActive = COMP_DEF_ACTIVITY,
			vec2_t    pos = COMP_DEF_POS
		);

		CompPos( const CompPos &rhs );
		CompPos &operator=( const CompPos &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_POSITION; }
		inline comp_type_e getType() const override { return COMP_POSITION; }

		// NOTE : checks if the parent entity exists ( no component dependencies for CompPos )
		inline bool hasSisterComps() const override { return hasEntity(); }

	// ================ POSITION METHODS
		inline vec2_t getPos() const { return _pos; }
		inline bool   voidPos(){ _pos = COMP_DEF_POS; return true; }

		inline bool setPos( vec2_t pos ){ _pos = pos; return true; }
		inline bool setPos( fixed_t x, fixed_t y ){ _pos.x = x; _pos.y = y; return true; }

		inline bool movePos( vec2_t delta ){ _pos.x += delta.x; _pos.y += delta.y; return true; }
		inline bool movePos( fixed_t dx, fixed_t dy ){ _pos.x += dx; _pos.y += dy; return true; }

		inline bool scalePos( fixed_t scale ){    _pos.x *= scale; _pos.y *= scale; return true; }
		inline bool scalePos( fixed_t sx, fixed_t sy ){ _pos.x *= sx; _pos.y *= sy; return true; }

	// ================ ROTATION METHODS
		inline angle_t getAngle() const { return _angle; }
		inline bool   voidAngle(){ _angle = 0; return true; }

		inline bool setAngle(   angle_t angle ){ _angle  = angle; return true; }
		inline bool moveAngle(  angle_t delta ){ _angle += delta; return true; }
		inline bool scaleAngle( fixed_t scale ){ _angle *= scale; return true; }

	// ================ DISTANCE METHODS
		// NOTE : returns the distance this would need to travel to reach the other point
		fixed_t getLineDistTo( id_t id ) const;
		fixed_t getLineDistTo( Entity  *other ) const;
		fixed_t getLineDistTo( CompPos *other ) const;
		fixed_t getLineDistTo( vec2_t   other ) const;
		fixed_t getLineDistTo( fixed_t x, fixed_t y ) const;


	// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_POS_HPP