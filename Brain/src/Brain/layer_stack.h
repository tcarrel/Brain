#pragma once



#include "Brain/nucleus.h"
#include "layer.h"



#include<vector>



namespace Brain
{
    class BRAIN_API Layer_Stack
    {
    public:
        Layer_Stack( void );
        ~Layer_Stack( void );

        void push( Layer* layer );
        void push_overlay( Layer* overlay );
        void pop( Layer* layer );
        void pop_overlay( Layer* overlay );

        std::vector<Layer*>::iterator begin( void );
        std::vector<Layer*>::iterator end( void );

    private:

        std::vector<Layer*> layers_;
        std::vector<Layer*>::iterator insert_;
    };
}
