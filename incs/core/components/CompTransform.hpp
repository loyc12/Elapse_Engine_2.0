#ifndef COMP_TRANSFORM_HPP
# define COMP_TRANSFORM_HPP

# include "./CompBase.hpp"

class CompTransform : public CompBase
{
	public: // NOTE : public to allow access from EntityMngr
	// ================================ ATTRIBUTES
		vec2_t  _pos;
		vec2_t  _sizes;
		angle_t _angle;

	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ~CompTransform(){}
		inline CompTransform( id_t NttID = 0, vec2_t pos = { 0, 0 }, vec2_t scale = { 1, 1 }, angle_t angle = 0 ) :
			CompBase( NttID ), _pos( pos ), _sizes( scale ), _angle( angle ){ flog( NttID ); }

		inline CompTransform( const CompTransform &cpy ) : CompBase( cpy ){ *this = cpy; }
		inline CompTransform &operator=( const CompTransform &cpy )
		{
			if( this != &cpy )
			{
				_pos   = cpy._pos;
				_sizes = cpy._sizes;
				_angle = cpy._angle;
			}
			return *this;
		}

	// ================================ ACCESSORS / MUTATORS
		inline static comp_type_e getType(){ return CT_TRANSFORM; }

		inline vec2_t getPosition() const { return _pos; }
		inline void  setPosition( vec2_t   pos ){ _pos  = pos; }
		inline void movePosition( vec2_t delta ){ _pos += delta;; }

		inline vec2_t getSizes() const { return _sizes; }
		inline void setSizes(   vec2_t sizes ){ _sizes  = sizes; }
		inline void moveSizes(  vec2_t delta ){ _sizes += delta; }
		inline void scaleSizes( vec2_t delta ){ _sizes *= delta; }

		inline angle_t getAngle() const { return _angle; }
		inline void setAngle(  angle_t angle ){ _angle  = angle; }
		inline void moveAngle( angle_t delta ){ _angle += delta; }

		// ================================ FRIEND METHODS
		inline friend std::ostream &operator<<( std::ostream &os, const CompTransform &ct )
		{
			os << "CompTransform : [ ID: " << ct._id << ", pos: " << ct._pos << ", sizes: " << ct._sizes << ", angle: " << ct._angle << " ]";
			return os;
		}
};

#endif // COMP_TRANSFORM_HPP