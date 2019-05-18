#include "../include/canvas.h"

    
    life::Canvas::Canvas( const Canvas & c)
    {
        m_width  = c.width(); m_height = c.height(); m_block_size = c.block_size();
        m_pixels.resize( m_width * m_height * image_depth );  
        std::memcpy( m_pixels.data(), c.pixels(), sizeof(component_t)*width()*height()*4 );
    }

    /*!
     * @param source The source object .
     * @return A reference to the 'this' object.
     */
    life::Canvas& life::Canvas::operator=( const Canvas &rhs)
    {
        if ( &rhs != this )
            std::memcpy( m_pixels.data(), rhs.pixels(), sizeof(component_t)*width()*height()*4 );
        return *this;
    }

    void life::Canvas::clear( const Color& color )
    {
        for (size_t x(0); x < width(); x++)
            for (size_t y(0); y < height(); y++)
                set_pixel(Point2(x, y), color);

    }

    void life::Canvas::pixel( const Point2& p,  const Color& c )
    {
        Point2 point{p.x * (long)block_size(), p.y * (long)block_size()};
        
        for (size_t i(0); i <= block_size(); i++)
            for (size_t j(0); j <= block_size(); j++)
            {
                set_pixel(Point2(point.x + i, point.y + j), c);
            }
    }

    void life::Canvas::set_pixel( const Point2& p, const Color& c )
    {
        if(p.x >= (long)width() or p.y >= (long)height())
            return;
        std::memcpy( &m_pixels[4 * (p.y * width() + p.x) ], c.channels, sizeof(component_t)*4 );
    }

    life::Color life::Canvas::pixel( const Point2& p) const
    {
        int R = m_pixels[4 * (p.y * m_width + p.x) + 0];
        int G = m_pixels[4 * (p.y * m_width + p.x) + 1]; 
        int B = m_pixels[4 * (p.y * m_width + p.x) + 2]; 
        int A = m_pixels[4 * (p.y * m_width + p.x) + 3]; 
        return Color( R, G, B, A );
    }

    void life::Canvas::hline( const Point2& p, size_t length, const Color& color )
    {
        for (size_t i(0); i < length; i++)
            //for (size_t j(0); j < block_size(); j++)
                pixel(Point2(p.x + i, p.y), color);
    }

    void life::Canvas::vline( const Point2& p, size_t length, const Color& color )
    {
        for (size_t i(0); i < length; i++)
            //for (size_t j(0); j < block_size(); j++)
                pixel(Point2(p.x, p.y + i), color);
    }