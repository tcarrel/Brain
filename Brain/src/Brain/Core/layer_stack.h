#pragma once



#include "Brain/Core/nucleus.h"
#include "Brain/Core/layer.h"



#include<vector>



namespace Brain
{
    class Layer_Stack
    {
    public:
        Layer_Stack( void ) = default;
        ~Layer_Stack( void );

        void push( Layer* layer );
        void push_overlay( Layer* overlay );
        void pop( Layer* layer );
        void pop_overlay( Layer* overlay );

        std::vector<Layer*>::iterator begin( void );
        std::vector<Layer*>::iterator end( void );
        std::vector<Layer*>::reverse_iterator rbegin( void );
        std::vector<Layer*>::reverse_iterator rend( void );

        std::vector<Layer*>::const_iterator begin( void ) const;
        std::vector<Layer*>::const_iterator end( void ) const;
        std::vector<Layer*>::const_reverse_iterator rbegin( void ) const;
        std::vector<Layer*>::const_reverse_iterator rend( void ) const;



    private:

        std::vector<Layer*> layers_;
        size_t insertion_point_{ 0 };
    };
}
