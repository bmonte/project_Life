#ifndef INPUT_READER_HPP
#define INPUT_READER_HPP

#include <vector>
using std::vector;
#include <utility>
#include <cstring>
#include <cstdlib>
#include <iostream>


namespace libs{

    class inputReader
    {
        public:
            bool cout_output{true};
            bool canvas_output{false};
            bool txt_output{false};  
            //=== Alias
            typedef std::pair< std::string, bool > string_arg_t;
            typedef std::pair< int, bool > int_arg_t;

        public: 
            //==== Special members
            /// Default constructor
            inputReader( int argc, char const **argv )
            : m_imgdir("", false), m_cfg_file("", false), m_outfile("", false), 
              m_bkgcolor("green", false), m_alivecolor("red", false), m_rules("B3/S23", false), 
              m_maxgen(-1, false), m_fps(1, false), m_blocksize(5, false)
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
            /// Set the output option.
            void output( void );

            //=== Attribute accessors members.
            /// Get the image directory
            std::string imgdir( void ) const
            { return m_imgdir.first; }
            /// Get the input file 
            std::string cfg_file( void ) const
            { return m_cfg_file.first; }
            /// Get the rules for the simulation 
            std::string rules( void ) const
            { return m_rules.first; }
            /// Get the filename for the output file
            std::string outfile( void ) const
            { return m_outfile.first; }
            /// Get the name for the background color 
            std::string bkgcolor( void ) const
            { return m_bkgcolor.first; }
            /// Get the name for representing alive cells
            std::string alivecolor( void ) const
            { return m_alivecolor.first; }
            /// Get the numbers of the max generations
            int maxgen( void ) const
            { return m_maxgen.first; }
            /// Get the numbers of generations presented per second
            int fps( void ) const
            { return m_fps.first; }
            /// Get the pixel size of a cell
            int blocksize( void ) const
            { return m_blocksize.first; }

        private:
            string_arg_t m_imgdir; //!< Canvas CHECK
            string_arg_t m_cfg_file; //!< Input file CHECK
            string_arg_t m_outfile; //!< TxT 
            string_arg_t m_bkgcolor; //!< Canvas
            string_arg_t m_alivecolor; //!< Canvas
            string_arg_t m_rules; //!< All CHECK
            int_arg_t m_maxgen; //!< All CHECK
            int_arg_t m_fps; //!< Cout/TxT CHECK
            int_arg_t m_blocksize; //!< Canvas
            vector< std::string > m_args; //!< Input CHECK
    };

} //namespace

#endif