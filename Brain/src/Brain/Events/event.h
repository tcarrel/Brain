#pragma once



#include "Brain/Core/nucleus.h"



namespace Brain
{
	enum class Event_Type
	{
		NONE = 0,
		WIN_CLOSE, WIN_RESIZE, WIN_FOCUS_GAINED, WIN_FOCUS_LOST, WIN_MOVED,
		APP_TICK, APP_UPDATE, APP_RENDER,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPING,
		MSE_BUTTON_PRESSED, MSE_BUTTON_RELEASED, MSE_MOVED, MSE_SCROLL
	};



	enum class Event_Category
	{
		NONE         = 0,
		APPLICATION  = BIT(0),
		INPUT        = BIT(1),
		KEYBOARD     = BIT(2),
		MOUSE        = BIT(3),
		MOUSE_BUTTON = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static Event_Type get_static_type( void ) { return Event_Type::type; }\
                               virtual Event_Type get_event_type( void ) const override { return get_static_type(); }\
                               virtual const char* get_name( void ) const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags( void ) const override { return category; }

	class Event
	{
		friend class Event_Dispatch;
	public:
		virtual Event_Type get_event_type( void ) const = 0;
		virtual const char* get_name( void ) const = 0;
		virtual int get_category_flags( void ) const = 0;
		virtual std::string to_string( void ) const { return get_name(); }

		bool is_in_category( Event_Category category );

		const bool& handled{ handled_ };

	protected:
		bool handled_{ false };
	};



	class Event_Dispatch
	{
		template<typename T>
		using Event_Func = std::function<bool( T& )>;

		Event& event_;

	public:
		Event_Dispatch( Event& evnt )
			:
			event_( evnt )
		{}

		template<typename T>
		bool dispatch( Event_Func<T> function )
		{
			if( event_.get_event_type() == T::get_static_type() )
			{
				event_.handled_ = function( *(T*)&event_ );
				return true;
			}
			return false;
		} 

	};



	std::ostream& operator<<( std::ostream& os, const Event& e );
}