#ifndef LIBS_HPP
# define LIBS_HPP

# include <bitset>
# include <cstddef>
# include <cstdio>
# include <cstdlib>
# include <cstdint>
# include <cmath>

# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>

# include <string>
# include <array>
# include <vector>
# include <list>
# include <map>
# include <unordered_map>
# include <iterator>
# include <algorithm>

# include <sys/types.h>
# include <sys/time.h>
# include <memory>
# include <mutex>
# include <unistd.h>
# include <string.h>

using std::cout;
using std::cerr;
using std::endl;

using std::stringstream;
using std::istringstream;
using std::ostringstream;

using std::fstream;
using std::ifstream;
using std::ofstream;

using std::istream;
using std::ostream;

using std::string;
using std::to_string;
using std::array;
using std::vector;
using std::list;
using std::map;
using std::unordered_map;
using std::pair;
using std::iterator;

using std::byte;
using std::bitset;

// ================================ SHORTHAND

# define elif else if
# define ostrs ostringstream

# define tostr( x ) to_string( x )

typedef bool        bit_t; //  NOTE : implement using bitarray class instead
typedef bitset< 4 > word_t; // NOTE : implement using bitarray class instead
typedef uint8_t     byte_t; // NOTE : implement using bitarray class instead

typedef uint32_t     id_t;

#endif // LIBS_HPP
