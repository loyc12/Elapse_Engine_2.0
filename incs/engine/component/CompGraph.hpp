#ifndef COMP_GRAPH_HPP
# define COMP_GRAPH_HPP

# include <raylib.h>
# include "../component/CompBase.hpp"

# define COMP_DEF_COLOUR col_t( 0, 0, 0, 255 ) // NOTE : default color for the component
# define COMP_DEF_CIRRAD 0.0f //                   NOTE : default circle radius for the component

class CompGraph : public CompBase
{
	protected:
	// ================================ ATTRIBUTES
		col_t   _col;
		fixed_t _cirRad; // NOTE : radius of the circle to draw ( debug graphics only )

	// ================================ CORE METHODS
		void onCpy( const CompGraph &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~CompGraph();

		CompGraph();
		CompGraph( Entity *Ntt,
			bool  isActive = COMP_DEF_ACTIVITY,
			col_t      col = COMP_DEF_COLOUR,
			fixed_t cirRad = COMP_DEF_CIRRAD
		);

		CompGraph( const CompGraph &rhs );
		CompGraph &operator=( const CompGraph &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getStaticType(){    return COMP_GRAPHIC; }
		inline comp_type_e getType() const override { return COMP_GRAPHIC; }

		// NOTE : checks if the parent entity exists and has the needed components ( position )
		bool hasSisterComps() const override;

	// ================ COLOR METHODS
		inline col_t getCol(){ return _col; }
		inline bool voidCol(){ _col = COMP_DEF_COLOUR; return true; } // NOTE : sets the Colour to 0

		inline bool setCol( const col_t &Col ){ _col = Col; return true; }
		inline bool setCol( byte_t r, byte_t g, byte_t b, byte_t a ){ _col.r = r; _col.g = g; _col.b = b; _col.a = a; return true; }

		inline bool moveCol( const col_t &delta ){ _col.r += delta.r; _col.g += delta.g; _col.b += delta.b; _col.a += delta.a;     return true; }
		inline bool moveCol( byte_t dr, byte_t dg, byte_t db, byte_t da ){ _col.r += dr; _col.g += dg; _col.b += db; _col.a += da; return true; }

	// ================ CIRCLE RADIUS METHODS
		inline fixed_t getCircleRadius() const { return _cirRad; }
		inline bool   voidCircleRadius(){ _cirRad = COMP_DEF_CIRRAD; return true; } // NOTE : sets the Circle Radius to 0

		inline bool setCircleRadius(   fixed_t radius ){ _cirRad = fmax( COMP_DEF_CIRRAD,  radius );        return true; }
		inline bool moveCircleRadius(  fixed_t delta  ){ _cirRad = fmax( COMP_DEF_CIRRAD, _cirRad + delta); return true; }
		inline bool scaleCircleRadius( fixed_t scale  ){ _cirRad = fmax( COMP_DEF_CIRRAD, _cirRad * scale); return true; }

	// ================================ TICK METHODS
		bool onTick() override;
};

#endif // COMP_GRAPH_HPP