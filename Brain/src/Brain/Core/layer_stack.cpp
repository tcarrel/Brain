#include "br.pch.h"
#include "Brain/Core/layer_stack.h"



namespace Brain
{
    Layer_Stack::~Layer_Stack( void )
    {
        for( Layer* layer : layers_ )
        {
            delete layer;
            layer = nullptr;
        }
    }



    void Layer_Stack::push( Layer* layer )
    {
        layers_.emplace( layers_.begin() + insertion_point_++, layer );
    }



    void Layer_Stack::push_overlay( Layer* overlay )
    {
        layers_.emplace_back( overlay );
    }



    void Layer_Stack::pop( Layer* layer )
    {
        auto it = std::find( layers_.begin(), layers_.end(), layer );
        if( it != layers_.end() )
        {
            layers_.erase( it );
            --insertion_point_;
        }
    }



    void Layer_Stack::pop_overlay( Layer* overlay )
    {
        auto it = std::find( layers_.begin(), layers_.end(), overlay );
        if( it != layers_.end() )
        {
            layers_.erase( it );
        }
    }



    std::vector<Layer*>::iterator Layer_Stack::begin( void )
    {
        return layers_.begin();
    }

    std::vector<Layer*>::iterator Layer_Stack::end( void )
    {
        return layers_.end();
    }



    std::vector<Layer*>::reverse_iterator Layer_Stack::rbegin( void )
    {
        return layers_.rbegin();
    }

    std::vector<Layer*>::reverse_iterator Layer_Stack::rend( void )
    {
        return layers_.rend();
    }






    std::vector<Layer*>::const_iterator Layer_Stack::begin( void ) const
    {
        return layers_.begin();
    }



    std::vector<Layer*>::const_iterator Layer_Stack::end( void ) const
    {
        return layers_.end();
    }



    std::vector<Layer*>::const_reverse_iterator Layer_Stack::rbegin( void ) const
    {
        return layers_.rbegin();
    }



    std::vector<Layer*>::const_reverse_iterator Layer_Stack::rend( void ) const
    {
        return layers_.rend();
    }
}