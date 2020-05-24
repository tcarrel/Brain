#include "br.pch.h"
#include "layer_stack.h"



namespace Brain
{
    Layer_Stack::Layer_Stack( void )
        :
        insert_( layers_.begin() )
    {}



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
        insert_ = layers_.emplace( insert_, layer );
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
            insert_--;
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
}