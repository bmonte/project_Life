#ifndef COMMON_H
#define COMMON_H

#include <cstring> // memset, memcpy
#include <iostream>
#include <map>

namespace life {
   /// Represents a Pixel coordinate
   struct Point2
   {
       typedef long coord_type; //!< The cell coordinate type.
       coord_type x; //!< X coordinate of a point.
       coord_type y; //!< Y coordinate of a point.
       /// Creates a point 2d.
       Point2( coord_type x=0, coord_type y=0 ) : x{x}, y{y} {/*empty*/}
       /// Copy constructor
       Point2( const Point2& clone ) : x{ clone.x }, y{ clone.y } {/*empty*/}
       /// Equality comparison.
       bool operator==( const Point2& rhs ) const
       { return x==rhs.x and y==rhs.y ; }
       /// Difference comparison.
       bool operator!=( const Point2& rhs ) const
       { return not operator==( rhs ) ; }
       /// Decrement the point.
       Point2 operator--()
       {
           --x; --y;
           return *this;
       }
       Point2 operator--(int)
       {
           Point2 temp(*this);
           x--; y--;
           return temp;
       }
       /// Stream extractor
       friend std::ostream& operator<<( std::ostream& os, const Point2& p )
       {
           os << "(x="<< p.x << ", y=" << p.y << ")";
           return os;
       }
   };

   /// Represents a Matrix Coordinate
   struct Location2
   {
       typedef long coord_type; //!< The cell coordinate type.
       coord_type r; //!< row coordinate of a location.
       coord_type c; //!< column coordinate of a location.
       /// Creates a 2D location.
       Location2( coord_type r=0, coord_type c=0 ) : r{r}, c{c} {/*empty*/}
       /// Copy constructor
       Location2( const Location2& clone ) : r{ clone.r }, c{ clone.c } {/*empty*/}
       /// Equality comparison.
       bool operator==( const Location2& rhs ) const
       { return r==rhs.r and c==rhs.c ; }
       /// Difference comparison.
       bool operator!=( const Location2& rhs ) const
       { return not operator==( rhs ) ; }
       bool operator<( const Location2& rhs ) const
       { return (r < rhs.r or ( r == rhs.r and c < rhs.c ) ); }
       /// Decrement the point.
       Location2 operator--()
       {
           --r; --c;
           return *this;
       }
       Location2 operator--(int)
       {
           Location2 temp(*this);
           r--; c--;
           return temp;
       }
       /// Stream extractor
       friend std::ostream& operator<<( std::ostream& os, const Location2& l )
       {
           os << "(row="<< l.r << ", col=" << l.c << ")";

           return os;
       }
   };

   /// Convert location to point
   inline Point2 Location2Point( const Location2 &l )
   { return Point2{ l.c, l.r }; }

   /// Convert point to location.
   inline Location2 Point2Location( const Point2 &p )
   { return Location2{ p.y, p.x }; }

   /// Represents a Color as a RGBA entity.
   struct Color
   {
       //=== Alias
       typedef unsigned char color_t; //!< Type of a color channel.
       /// Identifies each color channel.
       enum channel_e : color_t { R=0, //!< Red channel.
                                  G=1, //!< Green channel.
                                  B=2, //!< Blue channel.
                                  A=3  //!< Alpha channel.
       };

       //=== Members
       color_t channels[4]; //!< Stores each of the color channels, R, G, B and A.
       //=== Methods
       /// Creates a color.
       Color( color_t r=0, color_t g=0, color_t b=0, color_t a=1) : channels{r,g,b,a} {/*empty*/}
       /// Copy constructor.
       Color( const Color& clone )
       {
           std::memcpy( channels, clone.channels, sizeof(color_t)*4 );
       }
       /// Assignment operator.
       Color& operator=( const Color& rhs )
       {
           if ( &rhs != this )
               std::memcpy( channels, rhs.channels, sizeof(color_t)*4 );
           return *this;
       }
       /// Comparison operator.
       bool operator==( const Color& rhs )
       {
           return not std::memcmp( channels, rhs.channels, sizeof(color_t)*4 );
       }
       friend std::ostream& operator<<( std::ostream& os, const Color& c )
       {
           os << "("<< (int)c.channels[0] << ", " << (int)c.channels[1] << ", " 
              << (int)c.channels[2] << ", " << (int)c.channels[3] << ")";
           return os;
       }
   };

   // A basic color pallete.
   static const Color BLACK         = Color{0,0,0}      ; //!< Black.
   static const Color WHITE         = Color{255,255,255}; //!< White.
   static const Color DARK_GREEN    = Color{0,100,0}    ; //!< Dark green.
   static const Color GREEN         = Color{0,250,0}    ; //!< Green.
   static const Color RED           = Color{255,0,0}    ; //!< Red.
   static const Color BLUE          = Color{0,0,255}    ; //!< Blue.
   static const Color ORANGE        = Color{255,165,0}  ; //!< Orange.
   static const Color CRIMSON       = Color{220,20,60}  ; //!< Crimson (kind of red).
   static const Color LIGHT_BLUE    = Color{135,206,250}; //!< Light blue.
   static const Color LIGHT_GREY    = Color{210,210,210}; //!< Light grey.
   static const Color DEEP_SKY_BLUE = Color{0,191,255}  ; //!< Deep blue.
   static const Color DODGER_BLUE   = Color{30,144,255} ; //!< Another bluish color.
   static const Color STEEL_BLUE    = Color{70,130,180} ; //!< Yet another bluish color.
   static const Color YELLOW        = Color{255,255,0}  ; //!< Yellow.
   static const Color LIGHT_YELLOW  = Color{255,255,153}; //!< Light yellow.

   /// A color palette for later use.
   static std::map< std::string, Color > color_palett{
       {  "black",         BLACK },
       {  "white",         WHITE },
       {  "dark_green",    DARK_GREEN },
       {  "red",           RED },
       {  "green",         GREEN },
       {  "blue",          BLUE },
       {  "orange",        ORANGE }, 
       {  "crimson",       CRIMSON },
       {  "light_blue",    LIGHT_BLUE },
       {  "light_grey",    LIGHT_GREY },
       {  "deep_sky_blue", DEEP_SKY_BLUE },
       {  "dodger_blue",   DODGER_BLUE },
       {  "steel_blue",    STEEL_BLUE },
       {  "yellow",        YELLOW },
       {  "light_yellow",  LIGHT_YELLOW }
   };

} // namespace

#endif // COMMON_H
