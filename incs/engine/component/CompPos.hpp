#ifndef COMP_POS_HPP
# define COMP_POS_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

class CompPos : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		Vector2 _pos; // NOTE : position of the component

	// ================================ CORE METHODS
		inline void onAdd() override {} // NOTE : No additional behavior for CompPos
		inline void onDel() override {} // NOTE : No additional behavior for CompPos
		void onCpy( const CompPos &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompPos();

		CompPos();
		CompPos( Entity *Ntt, bool isActive = COMP_DEF_ACTIVITY, Vector2 pos = { 0, 0 });

		CompPos( const CompPos  &rhs );
		CompPos &operator=( const CompPos &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_POSITION; }
		inline comp_type_e getType() const override { return COMP_POSITION; } // NOTE : overide this in derived classes

	// ================ POSITION METHODS
		inline Vector2 getPos() const { return _pos; }
		inline bool voidPos(){ _pos = { 0, 0 }; return true; }

		inline bool setPos( Vector2 pos ){ _pos = pos; return true; }
		inline bool setPos( float x, float y ){ _pos.x = x; _pos.y = y; return true; }

		inline bool changePos( Vector2 pos ){ _pos.x += pos.x; _pos.y += pos.y; return true; }
		inline bool changePos( float x, float y ){ _pos.x += x; _pos.y += y; return true; }

	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompPos
};

#endif // COMP_POS_HPP