#ifndef CLOCK_HPP
# define CLOCK_HPP

# include "./_libs.hpp"

extern time_t clock_per_micro;
extern time_t clock_per_milli;
extern time_t clock_per_sec;
extern time_t clock_per_min;
extern time_t clock_per_hour;
extern time_t clock_per_day;
extern time_t clock_per_week;
extern time_t clock_per_year;


// NOTE : always put " if( !clock_started ){ start_clock(); } " at the start of any clock function dependent on clock_start_time
extern struct timeval clock_start_time;
extern bool   clock_started;

struct timeval &start_clock();
struct timeval &get_start_time();

inline ulong timeval_to_ulong( struct timeval &time ){ return time.tv_sec * clock_per_sec + time.tv_usec; } // in microseconds

ulong get_time_diff(  struct timeval &start, struct timeval &end );
ulong get_time_since( struct timeval &then );
ulong get_laptime();  // NOTE : returns the time elapsed since this function was last called

inline ulong get_runtime() { return get_time_since( get_start_time() ); }

string to_time_str( ulong time );
string to_time_str_raw( ulong time );
string get_start_time_str();

inline string to_time_str(     struct timeval &time ){ return to_time_str(     timeval_to_ulong( time )); }
inline string to_time_str_raw( struct timeval &time ){ return to_time_str_raw( timeval_to_ulong( time )); }

inline string get_runtime_str(){      return to_time_str(     get_runtime() ); }
inline string get_runtime_str_raw() { return to_time_str_raw( get_runtime() ); }


#endif // CLOCK_HPP