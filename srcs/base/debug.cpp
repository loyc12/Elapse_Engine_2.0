#include "../../incs/base.hpp"


void log_time(){ log( "< clock time", INFO ); }

bool open_log_file( ofstream &log_file ) // orivate function
{
	if( !log_file.is_open() )
	{
		printf( "Generating log file\n" );

		string file_name = "logs/" + get_start_time_str() + ".log";
		printf( "Log file name : %s\n", file_name.c_str() ); // DEBUG

		log_file.open( file_name, std::ios::out | std::ios::app );

		if( !log_file.is_open() ){ return false; }

		printf( "Log file Generated successfully\n" );
	}
	return true;
}

bool log( ostrs msg,       log_level_e lvl, id_t id, const char *file, int line ){ return log( msg.str().c_str(), lvl, id, file, line ); }
bool log( string msg,      log_level_e lvl, id_t id, const char *file, int line ){ return log( msg.c_str(), lvl, id, file, line ); }
bool log( const char *msg, log_level_e lvl, id_t id, const char *file, int line )
{
	if( lvl > LOG_LVL )           return false;
	if( !SHOW_OBJ_MSG && id > 0 ) return false;

	ostream *log_out = &cout;

	static bool disregard_log_file = false;

	// NOTE : logic to determine if to output the messages to the log file or the console
	// TODO : have it display on the console even if when writing to the log file
	if( !disregard_log_file && LOG_FILE )
	{
		static ofstream log_file;
		if( !open_log_file( log_file ) )
		{
			disregard_log_file = true;
			log( "Failed to open log file. Logging to console instead", ERROR );
		}
		else { log_out = &log_file; }
	}

	static bool use_clr = ( log_out == &cout );

	bool use_red = ( lvl == ERROR || ( msg != nullptr && msg[0] == '!' ));
	if( LOG_TIME )
	{
		*log_out << ( use_clr ? ( use_red ? CLR_RED : CLR_LGR ) : "" );

		if ( SHOW_LAP_TIME ){ *log_out << to_time_str_raw( get_laptime()) << " "; }
		else { *log_out << to_time_str( get_runtime()) << " "; }
	}

	switch ( lvl )
	{
		case FUNCT: *log_out << ( use_clr ? CLR_CYN : "" ) << "[FUNCT]"; break;
		case DEBUG: *log_out << ( use_clr ? CLR_BLU : "" ) << "[DEBUG]"; break;
		case INFO:  *log_out << ( use_clr ? CLR_GRN : "" ) << "[INFO] "; break;
		case WARN:  *log_out << ( use_clr ? CLR_YEL : "" ) << "[WARN] "; break;
		case ERROR: *log_out << ( use_clr ? CLR_RED : "" ) << "[ERROR]"; break;
		default:    *log_out << ( use_clr ? CLR_MAG : "" ) << "[???]  "; break;
	}

	*log_out << ( use_clr ? CLR_LGR : "" );

	if( LOG_LINE && file != nullptr ) *log_out << " [" << file << ":" << line << "]";
	if( id > 0 ) *log_out << " [" << id << "]";

	*log_out << ( use_clr ? ( lvl == FUNCT ? CLR_LGR : ( use_red ? CLR_RED : CLR_RST )) : "" ) << " " << msg;
	*log_out << ( use_clr ? CLR_LGR : "" ) << endl;

	return true;
}

bool log_funct( bool unlog, const char *fct, const char *cls, id_t id, const char *file, int line )
{
	if( !SHOW_FCT_PATH )
	{
		if( !unlog )
		{
			if ( cls != nullptr && cls[0] != '\0' ) { log( fct + string( "::" ) + cls, FUNCT, id, file, line ); }
			else {                                    log( fct, FUNCT, id, file, line ); }
		}
		return true;
	}

	static byte_t funct_depth = 0;
	static string funct_path = "";

	if ( unlog ) // NOTE : unloging the previous function from funct_path
	{
		if ( funct_depth <= 0 )
		{
			qlog( "funct_log : funct_depth underflow", DEBUG, 0 );
			funct_depth = 0;
			funct_path = "";
			return false;
		}
		else { funct_depth--; }

		size_t pos = funct_path.find_last_of( FCT_SEPARATOR );

		if( funct_path.size() > 0 && pos != string::npos )
		{
			funct_path.erase( pos );

			// NOTE : we avoid overriding it the lap timer if SHOW_LAP_TIME is true
			//if ( !SHOW_LAP_TIME ){ log( "laptime : " + to_time_str_raw( get_laptime()), FUNCT, id, file, line ); }

			return true;
		}
		else { qlog( "funct_log : unloging failed", ERROR, 0 ); return false; }
	}
	else // NOTE : loging the current function to funct_path
	{
		// NOTE : we avoid overriding it the lap timer if SHOW_LAP_TIME is true
		//if ( !SHOW_LAP_TIME ) get_laptime();

		if( funct_depth >= 255 )
		{
			qlog( "funct_log : funct_depth overflow", DEBUG, 0 );
			return false;
		}
		else { funct_depth++; }

		funct_path += FCT_SEPARATOR;

		if ( FCT_MUL_PREFIX[ 0 ] != '\0' ){ for ( byte_t i = 0; i < funct_depth; i++ ) { funct_path += FCT_MUL_PREFIX; }}

		if ( file != nullptr && file[0] != '\0' ){ funct_path += " [" + string( file ) + ":" + to_string( line ) + "] "; }
		if ( cls  != nullptr && cls[0]  != '\0' ){ funct_path += cls + string( "::" ); }
		if ( fct  != nullptr && fct[0]  != '\0' ){ funct_path += fct + string( "()" ); }

		if ( id > 0 ) { funct_path += "[" + to_string( id ) + "]"; }

		log( funct_path + string( "\n"), FUNCT, id, file, line );
	}
	return true;
}