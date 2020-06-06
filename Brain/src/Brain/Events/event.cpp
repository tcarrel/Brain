#include "br.pch.h"

#include "Brain/Events/event.h"



namespace Brain
{
    bool Event::is_in_category( Event_Category category )
    {
        return static_cast<int>( category ) & get_category_flags();
    }



    std::ostream& operator<<( std::ostream& os, const Event& e )
    {
        return os << e.to_string();
    }
}
