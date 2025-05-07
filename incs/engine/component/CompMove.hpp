#ifndef COMP_MOVE_HPP
# define COMP_MOVE_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_ACC { 0, 0 } // NOTE : default acceleration for the component ( for simple gravity effect )

class CompMove : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		Vector2 _vel;
		Vector2 _acc;

		angle_t _rotVel; // NOTE : rotation velocity
		angle_t _rotAcc; // NOTE : rotation acceleration

	// ================================ CORE METHODS
		void onCpy( const CompMove &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompMove();

		CompMove();
		CompMove( Entity *Ntt,
			bool isActive = COMP_DEF_ACTIVITY,
			Vector2 vel   = { 0, 0 },
			Vector2 acc   = COMP_DEF_ACC
		);

		CompMove( const CompMove &rhs );
		CompMove &operator=( const CompMove &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_MOVEMENT; }
		inline comp_type_e getType() const override { return COMP_MOVEMENT; }

		// NOTE : checks if the parent entity exists and has the needed components ( position )
		bool hasSisterComps() const override;

	// ================ POSITION METHODS
	// ======== VELOCITY METHODS
		inline Vector2 getVel() const { return _vel; }
		inline float getLinearVel() const { return sqrt(( _vel.x * _vel.x ) + ( _vel.y * _vel.y )); }
		inline bool voidVel(){ _vel = { 0, 0 }; return true; }

		inline bool setVel( Vector2 vel ){ _vel = vel; return true; }
		inline bool setVel( float x, float y ){ _vel.x = x; _vel.y = y; return true; }

		inline bool changeVel( Vector2 delta ){ _vel.x += delta.x; _vel.y += delta.y; return true; }
		inline bool changeVel( float dx, float dy ){ _vel.x += dx; _vel.y += dy; return true; }

	// ======== ACCELERATION METHODS
		inline Vector2 getAcc() const { return _acc; }
		inline float getLinearAcc() const { return sqrt(( _acc.x * _acc.x ) + ( _acc.y * _acc.y )); }
		inline bool voidAcc(){ _acc = COMP_DEF_ACC; return true; }

		inline bool setAcc( Vector2 acc ){ _acc = acc; return true; }
		inline bool setAcc( float x, float y ){ _acc.x = x; _acc.y = y; return true; }

		inline bool changeAcc( Vector2 delta ){ _acc.x += delta.x; _acc.y += delta.y; return true; }
		inline bool changeAcc( float dx, float dy ){ _acc.x += dx; _acc.y += dy; return true; }

	// ================ ROTATION METHODS
	// ======== VELOCITY METHODS
		inline angle_t getRotVel() const { return _rotVel; }
		inline bool voidRotVel(){ _rotVel = 0; return true; }

		inline bool setRotVel( angle_t rotVel ){ _rotVel = rotVel; return true; }
		inline bool changeRotVel( angle_t delta ){ _rotVel += delta; return true; }

	// ======== ACCELERATION METHODS
		inline angle_t getRotAcc() const { return _rotAcc; }
		inline bool voidRotAcc(){ _rotAcc = 0; return true; }

		inline bool setRotAcc( angle_t rotAcc ){ _rotAcc = rotAcc; return true; }
		inline bool changeRotAcc( angle_t delta ){ _rotAcc += delta; return true; }

	// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_MOVE_HPP