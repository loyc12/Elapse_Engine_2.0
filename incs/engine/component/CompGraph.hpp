#ifndef COMP_GRAPH_HPP
# define COMP_GRAPH_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define DEF_COLOUR { 0, 0, 0, 255 } // NOTE : default color for the component

class CompGraph : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		Color _col;
		float _cirleRadius; // NOTE : radius of the circle to draw ( debug graphics only )

	// ================================ CORE METHODS
		inline void onAdd() override {} // NOTE : No additional behavior for CompGraph
		inline void onDel() override {} // NOTE : No additional behavior for CompGraph
		void onCpy( const CompGraph &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompGraph();

		CompGraph();
		CompGraph( Entity *Ntt, bool isActive = COMP_DEF_ACTIVITY, Color Col = DEF_COLOUR );

		CompGraph( const CompGraph  &rhs );
		CompGraph &operator=( const CompGraph &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_GRAPHIC; }
		inline comp_type_e getType() const override { return COMP_GRAPHIC; } // NOTE : overide this in derived classes

	// ================ COLOR METHODS
		inline Color  dupCol() const { return _col; } // const but slightly more expensive
		inline Color &getCol(){ return _col; }
		inline bool  voidCol(){ _col = DEF_COLOUR; return true; } // NOTE : sets the Color to 0

		inline bool setCol( const Color &Col ){ _col = Col; return true; }
		inline bool setCol( byte_t r, byte_t g, byte_t b, byte_t a ){ _col.r = r; _col.g = g; _col.b = b; _col.a = a; return true; }

		inline bool changeCol( const Color &delta ){ _col.r += delta.r; _col.g += delta.g; _col.b += delta.b; _col.a += delta.a; return true; }
		inline bool changeCol( byte_t r, byte_t g, byte_t b, byte_t a ){ _col.r += r; _col.g += g; _col.b += b; _col.a += a; return true; }

	// ================ CIRCLE RADIUS METHODS
		inline float getCircleRadius() const { return _cirleRadius; }
		inline bool voidCircleRadius(){ _cirleRadius = 0; return true; } // NOTE : sets the Circle Radius to 0

		inline bool setCircleRadius(    float radius ){ _cirleRadius  = radius; return true; }
		inline bool changeCircleRadius( float delta  ){ _cirleRadius += delta; return true; }

	// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_GRAPH_HPP