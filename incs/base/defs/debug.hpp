#ifndef DEBUG_HPP
# define DEBUG_HPP

# include "./_libs.hpp"
# include "./_clrs.hpp"
# include "./clock.hpp"

typedef enum
{
	NONE = 0,
	ERROR,
	WARN,
	INFO,
	DEBUG,
	FUNCT,
} log_level_e;

# define LOG_LVL_NONE  0 // NOTE : shows no messages
# define LOG_LVL_ERROR 1 // NOTE : shows only error messages
# define LOG_LVL_WARN  2 // NOTE : shows only error and warning messages
# define LOG_LVL_INFO  3 // NOTE : shows error, warning and info messages
# define LOG_LVL_DEBUG 4 // NOTE : shows all messages except function calls
# define LOG_LVL_FUNCT 5 // NOTE : shows all function calls, as well as the functiona; pathing if SHOW_FCT_PATH is true

#	define LOG_LVL 5 //       NONE, DEBUG, INFO, WARN, ERROR, FUNCT ( each level includes the previous ones )


#	define LOG_FILE false //       	NOTE : writes the log messages to a file instead of the console
#	define LOG_LINE true //       	NOTE : shows the src file name and line number in the log messages
#	define LOG_TIME true //       	NOTE : shows the time since start in the log messages
# define SHOW_LAP_TIME false // 	NOTE : shows the time since the last log message, instead of the time since start
#	define SHOW_OBJ_MSG true //   	NOTE : shows or ignores the messages what have a specified t_id
#	define SHOW_FCT_PATH false //  	NOTE : shows the function pathing in the log messages, as opposed to just the function name

# define FCT_SEPARATOR "\n" //    NOTE : this is what will visually separete each function name in the function pathing output
# define FCT_MUL_PREFIX " " //    NOTE : this will be added N times before the function name, where N is the depth of the function call
#	define HERE __FILE__, __LINE__

#	if LOG_LVL > LOG_LVL_NONE //    NOTE : debug functions to activate if loglevel is greater than NONE
#	 define qlog( msg, lvl, id )     log( msg, lvl, id, HERE )
#	 define dtest( dividend, div )   div_test( dividend, div )
#  define BLOCK                    std::cin.get(); //        NOTE : this freezes the program until an input is given. useful for debugging
#	else
#	 define qlog( msg, lvl, id )
#	 define dtest( dividend, div ) true;
#	 define BLOCK
#	endif

#	if LOG_LVL == LOG_LVL_FUNCT //  NOTE : debug functions to activate only if loglevel is FUNCT
#	 define flog( id )   log_funct( false, __FUNCTION__, nullptr, id, HERE )
#	 define fend()       log_funct( true )
#  define freturn      log_funct( true ); return
#	else
#	 define flog( id )
#	 define fend()
#	 define fend(); return return
#	endif

void log_time();

bool log( ostrs msg,       log_level_e lvl = DEBUG, id_t id = 0, const char *file = nullptr, int line = 0 );
bool log( string msg,      log_level_e lvl = DEBUG, id_t id = 0, const char *file = nullptr, int line = 0 );
bool log( const char *msg, log_level_e lvl = DEBUG, id_t id = 0, const char *file = nullptr, int line = 0 );

// TODO : implement/use the "cls" ( class )	parameter
bool log_funct( bool unlog, const char *fct = nullptr, const char *cls = nullptr, id_t id = 0, const char *file = nullptr, int line = 0 );

// ============================ DIVISION TESTS

# define TT template< typename T, typename = typename std::enable_if< std::is_arithmetic< T >::value >::type >

inline bool diverror( const char *dividend, const char *divisor )
{
	qlog( "Trying to divide " + string( dividend ) + " by " + string( divisor ), ERROR, 0 );
	return false;
}

TT inline bool div_test( const char *dividend, T div )
{
	if( div == 0   ){ return diverror( dividend, "ZERO" ); }
	if( div == NAN ){ return diverror( dividend, "NAN" ); }
	return true;
}

# undef TT

#endif // DEBUG_HPP