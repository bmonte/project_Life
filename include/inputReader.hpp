#ifndef INPUT_READER_HPP
#define INPUT_READER_HPP

#include <vector>
using std::vector;
#include <cstring>
#include <cstdlib>
#include <iostream>


namespace libs{

    class inputReader
    {
        public: 
            //==== Special members
            /// Default constructor
            inputReader( int argc, char const **argv )
            : m_imgdir(), m_cfg_file(), m_outfile(), m_bkgcolor("green"),
              m_alivecolor("red"), m_rules("B3/S23"), m_maxgen(), m_fps(1), m_blocksize(5)
            { m_args.assign(argv + 1, argv + argc); }
            /// Default destructor
            virtual ~inputReader( void )
            {
                // Do nothing, RAII (resource acquisition is resource initialization) approach
            }

            //=== Members
            /// Print the help message if needed
            void help_message( void );
            /// Update the members based on argument files
            void update( void );
            
            //=== Attribute accessors members.
            /// Get the image directory
            std::string imgdir( void ) const
            { return m_imgdir; }
            /// Get the input file 
            std::string cfg_file( void ) const
            { return m_cfg_file; }
            /// Get the rules for the simulation 
            std::string rules( void ) const
            { return m_rules; }
            /// Get the filename for the output file
            std::string outfile( void ) const
            { return m_outfile; }
            /// Get the name for the background color 
            std::string bkgcolor( void ) const
            { return m_bkgcolor; }
            /// Get the name for representing alive cells
            std::string alivecolor( void ) const
            { return m_alivecolor; }
            /// Get the numbers of the max generations
            int maxgen( void ) const
            { return m_maxgen; }
            /// Get the numbers of generations presented per second
            int fps( void ) const
            { return m_fps; }
            /// Get the pixel size of a cell
            int blocksize( void ) const
            { return m_blocksize; }

        private:
            std::string m_imgdir; //!< The image width in pixel units.
            std::string m_cfg_file; //!< The image width in pixel units.
            std::string m_outfile; //!< The image width in pixel units.
            std::string m_bkgcolor; //!< The image width in pixel units.
            std::string m_alivecolor; //!< The image width in pixel units.
            std::string m_rules; //!< The image width in pixel units.
            int m_maxgen; //!< The image width in pixel units.
            int m_fps; //!< The image width in pixel units.
            int m_blocksize; //!< The image width in pixel units.
            vector< std::string > m_args; //!< The image width in pixel units.
    };

} //namespace

#endif