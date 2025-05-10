#ifndef COMP_SHAPE_HPP
# define COMP_SHAPE_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

typedef byte_t Shape2D; // NOTE : this is a placeholder for the actual shape type

class CompShape : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		Shape2D _shape;

	// ================================ CORE METHODS
		void onCpy( const CompShape &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompShape();

		CompShape();
		CompShape( Entity *Ntt,
			bool    isActive = COMP_DEF_ACTIVITY,
			Shape2D shape    = 0
		);

		CompShape( const CompShape &rhs );
		CompShape &operator=( const CompShape &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_POSITION; }
		inline comp_type_e getType() const override { return COMP_POSITION; } // NOTE : overide this in derived classes

	// ================ POSITION METHODS
		inline Shape2D getShape() const { return _shape; }
		inline bool voidShape(){ _shape = 0; return true; }
		inline bool setShape(    Shape2D shape ){ _shape  = shape; return true; }
		inline bool moveShape( Shape2D delta ){ _shape += delta; return true; }

	// ================================ TICK METHODS
		inline bool onTick() override { return _active; } // NOTE : No additional behavior for CompShape
};

#endif // COMP_SHAPE_HPP

// TODO : implement the shape component