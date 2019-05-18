#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <vector>
using std::vector;
#include <cstring>
#include <cstdlib>
#include <iostream>


namespace libs{

    class inputReader
    {
        public:
            //=== Alias
            typedef unsigned int int_arg_t;
            typedef std::string string_arg_t;

        public: 
            //==== Special members
            /// Default constructor
            inputReader( int argc, char const **argv )
            : m_imgdir(" "), m_cfg_file(" "), m_outfile(" "), m_bkgcolor("green"), m_alivecolor("red"),
              m_maxgen(0), m_fps(1), m_blocksize(5)
            { m_args.assign(argv + 1, argv + argc); }
            /// Default destructor
            virtual ~inputReader( void )
            {

            }

            //=== Members
            /// Print the help message if needed
            void help_message( void );
            /// Update the members based on argument files
            void update( void );

            //=== Attribute accessors members.
            /// Get the image directory
            string_arg_t imgdir( void ) const
            { return m_imgdir; }
            /// Get the input file 
            string_arg_t cfg_file( void ) const
            { return m_cfg_file; }
            /// Get the filename for the output file
            string_arg_t outfile( void ) const
            { return m_outfile; }
            /// Get the name for the background color 
            string_arg_t bkgcolor( void ) const
            { return m_bkgcolor; }
            /// Get the name for representing alive cells
            string_arg_t alivecolor( void ) const
            { return m_alivecolor; }
            /// Get the numbers of the max generations
            int_arg_t maxgen( void ) const
            { return m_maxgen; }
            /// Get the numbers of generations presented per second
            int_arg_t fps( void ) const
            { return m_fps; }
            /// Get the pixel size of a cell
            int_arg_t blocksize( void ) const
            { return m_blocksize; }

        private:
            string_arg_t m_imgdir;
            string_arg_t m_cfg_file;
            string_arg_t m_outfile;
            string_arg_t m_bkgcolor;
            string_arg_t m_alivecolor;
            int_arg_t m_maxgen;
            int_arg_t m_fps;
            int_arg_t m_blocksize;
            vector< string_arg_t > m_args;
    };

} //namespace

#endif