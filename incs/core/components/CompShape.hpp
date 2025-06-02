#ifndef COMP_SHAPE_HPP
# define COMP_SHAPE_HPP

# include "./CompBase.hpp"

class CompShape : public CompBase
{
	public: // NOTE : public to allow access from EntityMngr
	// ================================ ATTRIBUTES
		inline static shape_t TEMP = shape_t::GetDefPoly();
		shape_t _shape; // relative to the transform component

	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ~CompShape(){}
		inline  CompShape( id_t NttID = 0, const shape_t &shape = TEMP ) :
			CompBase( NttID ), _shape( shape ){ flog( NttID ); }

		inline CompShape( const CompShape &cpy ) : CompBase( cpy ){ *this = cpy; }
		inline CompShape &operator=( const CompShape &cpy )
		{
			if( this != &cpy )
			{
				_shape = cpy._shape;
			}
			return *this;
		}

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getType(){ return CT_SHAPE; }

		inline shape_t &getShape(){ return _shape; }
		inline void  setShape( const shape_t &shape ){ _shape = shape; }

		inline col_t getColour() const { return _shape._colour; }
		inline void  setColour( const col_t &col ){ _shape._colour = col; }
	 	inline void  setR( const byte_t &r ){ _shape._colour.setR( r ); }
		inline void  setG( const byte_t &g ){ _shape._colour.setG( g ); }
		inline void  setB( const byte_t &b ){ _shape._colour.setB( b ); }
		inline void  setA( const byte_t &a ){ _shape._colour.setA( a ); }

	// ================================ FRIEND METHODS
		inline friend std::ostream &operator<<( std::ostream &os, const CompShape &cs )
		{
			os << "CompShape : [ ID: " << cs._id << ", shape: " << cs._shape << " ]";
			return os;
		}
};

#endif // COMP_SHAPE_HPP