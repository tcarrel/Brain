#pragma once



namespace Brain
{
    enum class Shader_Data_Type
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool,


        Float1 = Float,
        Int1 = Int
    };



    static uint32_t size( Shader_Data_Type type )
    {
        switch( type )
        {
        case Brain::Shader_Data_Type::Float:  return sizeof( float );
        case Brain::Shader_Data_Type::Float2: return 2 * sizeof( float );
        case Brain::Shader_Data_Type::Float3: return 3 * sizeof( float );
        case Brain::Shader_Data_Type::Float4: return 4 * sizeof( float );
        case Brain::Shader_Data_Type::Mat3:   return 3 * 3 * sizeof( float );
        case Brain::Shader_Data_Type::Mat4:   return 4 * 4 * sizeof( float );
        case Brain::Shader_Data_Type::Int:    return sizeof( int );
        case Brain::Shader_Data_Type::Int2:   return 2 * sizeof( int );
        case Brain::Shader_Data_Type::Int3:   return 3 * sizeof( int );
        case Brain::Shader_Data_Type::Int4:   return 4 * sizeof( int );
        case Brain::Shader_Data_Type::Bool:   return sizeof( bool );
        default:
            BR_CORE_ASSERT( false, "Unkown Shader Data Type." );
            return 0;
        }
    }



    struct Buffer_Element
    {
        std::string name{ "" };
        Shader_Data_Type type{ Shader_Data_Type::None };
        uint32_t size{ 0 };
        size_t offset{ 0 };
        bool normalized{ false };
        void* offset_ptr( void ) const
        {
            return (void*)offset;
        }

        int32_t component_count( void ) const
        {
            switch( type )
            {
            case Brain::Shader_Data_Type::Float:  return 1;
            case Brain::Shader_Data_Type::Float2: return 2;
            case Brain::Shader_Data_Type::Float3: return 3;
            case Brain::Shader_Data_Type::Float4: return 4;
            case Brain::Shader_Data_Type::Mat3:   return 3 * 3;
            case Brain::Shader_Data_Type::Mat4:   return 4 * 4;
            case Brain::Shader_Data_Type::Int:    return 1;
            case Brain::Shader_Data_Type::Int2:   return 2;
            case Brain::Shader_Data_Type::Int3:   return 3;
            case Brain::Shader_Data_Type::Int4:   return 4;
            case Brain::Shader_Data_Type::Bool:   return 1;
            default:
                BR_CORE_ASSERT( false, "Unkown Shader Data Type." );
                return 0;
            }
        }

        Buffer_Element( void ) = default;
        Buffer_Element( Shader_Data_Type t, const std::string& n, bool normalize = false )
            :
            name( n ),
            type( t ),
            size( Brain::size( t ) ),
            normalized( normalize )
        {}
        Buffer_Element( const Buffer_Element& other )
            :
            name( other.name ),
            type( other.type ),
            size( other.size ),
            offset( other.offset ),
            normalized( other.normalized )
        {}
        Buffer_Element& operator=( const Buffer_Element& other )
        {
            name = other.name;
            type = other.type;
            size = other.size;
            offset = other.offset;
            normalized = other.normalized;
            return *this;
        }
        bool operator==( const Buffer_Element& other ) const
        {
            return
                type == other.type &&
                size == other.size &&
                normalized == other.normalized &&
                offset == other.offset &&
                name == other.name;
        }
        bool operator!=( const Buffer_Element& other ) const
        {
            return !( *this == other );
        }
        Buffer_Element& operator=( Buffer_Element&& other ) noexcept;
    };



    class Buffer_Layout
    {
    public:
        Buffer_Layout( void ) = default;
        Buffer_Layout( const std::initializer_list<Buffer_Element>& elements )
            :
            elements_( elements )
        {
            calculate_offsets_and_stride();
        }
        Buffer_Layout( const Buffer_Layout& other )
            :
            elements_( other.elements_ )
        {
            calculate_offsets_and_stride();
        }
        Buffer_Layout& operator=( const Buffer_Layout& other )
        {
            elements_ = other.elements_;
            stride_ = other.stride_;
            return *this;
        }
        bool operator==( const Buffer_Layout& rhs ) const
        {
            return stride_ == rhs.stride_ && elements_ == rhs.elements_;
        }
        bool operator!=( const Buffer_Layout& rhs ) const
        {
            return !( *this == rhs );
        }
        Buffer_Layout& operator=( Buffer_Layout&& other ) noexcept;

        const std::vector<Buffer_Element>& elements{ elements_ };

        std::vector<Buffer_Element>::iterator begin() noexcept;
        std::vector<Buffer_Element>::iterator end() noexcept;
        std::vector<Buffer_Element>::const_iterator begin() const noexcept;
        std::vector<Buffer_Element>::const_iterator end() const noexcept;

        const uint32_t& stride{ stride_ };

    private:
        void calculate_offsets_and_stride( void )
        {
            uint32_t offset{ 0 };
            stride_ = 0;
            for( auto& element : elements_ )
            {
                element.offset = offset;
                offset += element.size;
                stride_ += element.size;
            }
        }

        std::vector<Buffer_Element> elements_;
        uint32_t stride_{ 0 };
    };






    class Vertex_Buffer
    {
    public:
        virtual ~Vertex_Buffer( void ) = default;

        virtual void bind( void ) const = 0;
        virtual void unbind( void ) const = 0;


        virtual const Buffer_Layout& get_layout( void ) const = 0; 
        virtual void set_layout( const Buffer_Layout& layout ) = 0;

        static Ref<Vertex_Buffer> create( float* vertices, uint32_t size );
    };



    class Index_Buffer
    {
    public:
        virtual ~Index_Buffer( void ) = default;

        virtual void bind( void ) const = 0;
        virtual void unbind( void ) const = 0;

        virtual uint32_t get_count( void ) const = 0;

        static Ref<Index_Buffer> create( uint32_t* indices, uint32_t count );
    };
}