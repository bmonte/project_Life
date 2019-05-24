#ifndef LIFE_HPP
#define LIFE_HPP

#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;
#include <cstring>
#include <iomanip>

#include "common.h"
using namespace life;
#include "file.hpp"

class Life
{
    public:
        //=== Alias
        typedef std::string cell_t; //!< Type of a cell
        typedef vector<bool> grid_t; //!< Grid type <bool>
        typedef vector<Point2> log_t; //!< Living cells log type

    public:
        //=== Special members
            /// Constructor
            Life( size_t w=0, size_t h=0, cell_t l_cell="*", cell_t d_cell="~" )
                : m_rows{ w }, m_cols{ h }, m_live_cell{ l_cell }, m_dead_cell{ d_cell }
            {
                // Remember to adjust the virtual size to real dimensions.
                m_grid.resize( m_rows * m_cols );
                // Set all the position with dead cells 
                m_grid.assign( m_grid.size(), false );
            }
            /// Destructor
            virtual ~Life()
            {
                // Do nothing, RAII (resource acquisition is resource initialization) approach
            }

        //=== Members
            /// Reset all the grid
            void reset ( void );
            /// Update the grid 
            void update ( void );
            /// Update the log
            void updateLog ( log_t& );
            /// Print the current generation
            void print ( void );
            /// Print the current generation on a file
            void print_file ( libs::File& f );
            /// Print welcome message
            void welcome_message( void );
            /// Set all the living cells in the grid
            void set_cell_position ( const Point2 &p );
            /// Set the simulation rule
            void set_rule ( int, int, int );
            /// Return the number of neighbors of a cell indexed at Point2(x,y)
            int neighbors(const grid_t &grid, const Point2 &p );
            /// Look to a cell and decide whether it lives or die 
            bool rule( int qnt_neighbors, bool LoD ); //LOD = Live or Dead.
            /// Verify stable condition
            bool stable( void );
            /// Verify ARMAGEDDON!!!!!!!!1
            bool extinct( void );

        //=== Attribute accessors members
            ///Get the grid width
            size_t rows( void ) const
            { return m_rows; }
            ///Get the grid height
            size_t cols( void ) const
            { return m_cols; }
            ///Get the symbol for a living cell
            cell_t l_cell( void ) const
            { return m_live_cell; }
            ///Get the symbol for a dead cell
            cell_t d_cell( void ) const
            { return m_dead_cell; }

    private:
        size_t m_rows; //!< Grid widht 
        size_t m_cols; //!< Grid height
        cell_t m_live_cell; //!< Symbol for a living cell
        cell_t m_dead_cell; //!< Symbol for a dead cell
        grid_t m_grid; //!< Grid of a simulation
        log_t m_curr_generation; //!< Vector with living cells position
        vector < log_t > m_log; //!< Log with all living cells in all gens
        int born_rule, survive_rule[2]; //!< Simulation rule
};


#endif // GRID_H