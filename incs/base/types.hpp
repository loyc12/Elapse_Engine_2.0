#ifndef TYPES_HPP
# define TYPES_HPP

# include "./types/Angle.hpp" // float wrapper, to handle the circular nature of angles
//# include "./types/Quaternion.hpp" // NOTE : quaternion class

# include "./types/Colour.hpp" // colour values wrapper
# include "./types/Shape.hpp" //  NOTE : shape class

//# include "./types/Bitarrays.hpp" //  NOTE : wrapper for std::bitset, to allow it to be used as an uint_N_t
# include "./types/FixedPoint.hpp" // NOTE : fixed point number implementation, to allow more precision than float

# include "./types/Pos2.hpp" //    NOTE : vector-like class
# include "./types/Pos3.hpp" //    NOTE : vector-like class
//# include "./types/Matrix.hpp" //  NOTE : matrix class ( multidimensional vector array )

#endif // TYPES_HPP