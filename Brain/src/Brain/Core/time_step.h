#pragma once



namespace Brain
{
    class Time_Step
    {
    public:
        Time_Step( float time = 0.0f )
            :
            time_( time )
        {

        }

        operator float() const noexcept
        {
            return time_;
        }

        float get_seconds( void )
        {
            return time_;
        }

        float get_millisecods( void )
        {
            return 1000.0f * time_;
        }

    private:
        float time_;
    };
}