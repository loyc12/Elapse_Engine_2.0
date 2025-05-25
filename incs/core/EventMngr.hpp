#ifndef EVENT_MNGR_HPP
# define EVENT_MNGR_HPP

# include "../base.hpp"
#include <sys/types.h>

typedef enum : byte_t
{

	// NOTE : add more event types as needed



	// NOTE : maximum of 253 event types, as the last two values are reserved
	EVENT_TYPE_COUNT, //      NOTE : only for internal use
	EVENT_TYPE_BASE = 255, // NOTE : only for internal use
} event_type_e;

class Event
{
	protected:
		// ================================ ATTRIBUTES
		event_type_e _type; // NOTE : the type of the event
		id_t _id; //           NOTE : the entity this event belongs to, if applicable
		void *_data; //        NOTE : pointer to additional data associated with the event, if applicable

	public:
		// ================================ CONSTRUCTORS / DESTRUCTORS
		inline ~Event(){}
		inline  Event( event_type_e type = EVENT_TYPE_BASE, id_t id = 0 ) : _type( type ), _id( id ){}

		// ================================ ACCESSORS / MUTATORS
		inline event_type_e getType() const { return _type; }
		inline id_t         getID()   const { return _id; }
		inline void        *getData() const { return _data; }

		bool process() const
		{
			// NOTE : process the event based on its type
			switch ( _type )
			{
				// TODO : add more cases for other event types

				default:
					qlog( "Unknown event type", WARN, 0 );
					return false;
			}
		}

};

class EventMngr
{
	private:
		// ================================ ATTRIBUTES
		deque< Event > _eventQueue; // NOTE : queue of events to be processed
		std::mutex  mtx_eventQueue; // NOTE : mutex to protect the event queue from concurrent access

	public:
		// ================================ CONSTRUCTORS / DESTRUCTORS
		inline  EventMngr(){ clearEvents(); }
		inline ~EventMngr(){ clearEvents(); }

		// NOTE : prevent copying of the EventMngr instance
		inline EventMngr(            const EventMngr &cpy ) = delete;
		inline EventMngr &operator=( const EventMngr &cpy ) = delete;

		// ================================ EVENT METHODS
		inline void addEvent( const Event &event ){ flog( 0 ); MLOCK( mtx_eventQueue ); _eventQueue.push_back( event ); }
		inline void clearEvents(){                  flog( 0 ); MLOCK( mtx_eventQueue ); _eventQueue.clear(); }

		bool processEvents( uint32_t amount = 0 ) // NOTE : process a specific amount of events, or all if amount is 0
		{
			flog( 0 );

			MLOCK( mtx_eventQueue );
			if ( _eventQueue.empty() ){  return false; }

			uint32_t processed = 0;
			while ( !_eventQueue.empty() && ( amount == 0 || processed < amount ))
			{
				_eventQueue.front().process();
				_eventQueue.pop_front();
			}
			return true;
		}
};

#endif // EVENT_MNGR_HPP