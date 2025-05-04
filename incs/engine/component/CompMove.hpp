#ifndef COMP_MOVE_HPP
# define COMP_MOVE_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

class CompMove : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		Vector2 _vel;
		Vector2 _acc;

	// ================================ CORE METHODS
		inline void onAdd() override {} // NOTE : No additional behavior for CompMove
		inline void onDel() override {} // NOTE : No additional behavior for CompMove
		void onCpy( const CompMove &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompMove();

		CompMove();
		CompMove( Entity *Ntt, bool isActive = COMP_DEF_ACTIVITY, Vector2 vel = { 0, 0 }, Vector2 acc = { 0, 0 });

		CompMove( const CompMove  &rhs );
		CompMove &operator=( const CompMove &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_MOVEMENT; }
		inline comp_type_e getType() const override { return COMP_MOVEMENT; } // NOTE : overide this in derived classes

	// ================ VELOCITY METHODS
		inline Vector2 getVel() const { return _vel; }
		inline bool voidVel(){ _vel = { 0, 0 }; return true; }

		inline bool setVel( Vector2 vel ){ _vel = vel; return true; }
		inline bool setVel( float x, float y ){ _vel.x = x; _vel.y = y; return true; }

		inline bool changeVel( Vector2 vel ){ _vel.x += vel.x; _vel.y += vel.y; return true; }
		inline bool changeVel( float x, float y ){ _vel.x += x; _vel.y += y; return true; }

	// ================ ACCELERATION METHODS
		inline Vector2 getAcc() const { return _acc; }
		inline bool voidAcc(){ _acc = { 0, 0 }; return true; }

		inline bool setAcc( Vector2 acc ){ _acc = acc; return true; }
		inline bool setAcc( float x, float y ){ _acc.x = x; _acc.y = y; return true; }

		inline bool changeAcc( Vector2 acc ){ _acc.x += acc.x; _acc.y += acc.y; return true; }
		inline bool changeAcc( float x, float y ){ _acc.x += x; _acc.y += y; return true; }

	// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_MOVE_HPP